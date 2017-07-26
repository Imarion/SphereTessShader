#include "SphereTessShader.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>

#include <qmath.h>
#include <QGenericMatrix>

#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

GlWindow::~GlWindow()
{
    mFuncs->glDeleteVertexArrays(1, &mVAOIcosahedron);
    if (mProgram)      delete   mProgram;
    if (mContext)      delete   mContext;
    if (mRepaintTimer) delete   mRepaintTimer;
    if (mElapsedTimer) delete   mElapsedTimer;
    if (mObjVertices)  delete[] mObjVertices;
    if (mObjNormals)   delete[] mObjNormals;
    if (mObjIndices)   delete[] mObjIndices;
    if (mObjMaterials) delete[] mObjMaterials;
}

GlWindow::GlWindow() : currentTimeMs(0), currentTimeS(0)
{
    mObjVertices  = NULL;
    mObjNormals   = NULL;
    mObjIndices   = NULL;
    mObjMaterials = NULL;
    mScaleX       = mScaleY = mScaleZ = 1.0f;
    mRotX         = mRotY   = mRotZ   = 0.0f;
    mRotAuto      = true;
    mTransX       = mTransY = mTransZ = 0.0f;

    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    resize(800, 600);

    mContext = new QOpenGLContext(this);
    mContext->setFormat(format);
    mContext->create();

    mContext->makeCurrent( this );

    mFuncs = mContext->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if ( !mFuncs )
    {
        qWarning( "Could not obtain OpenGL versions object" );
        exit( 1 );
    }
    if (mFuncs->initializeOpenGLFunctions() == GL_FALSE)
    {
        qWarning( "Could not initialize core open GL functions" );
        exit( 1 );
    }

    initializeOpenGLFunctions();

    mRepaintTimer = new QTimer(this);
    connect(mRepaintTimer, &QTimer::timeout, this, &GlWindow::render);
    //mRepaintTimer->start(20);

    mElapsedTimer = new QTimer(this);
    connect(mElapsedTimer, &QTimer::timeout, this, &GlWindow::modCurTime);
    mElapsedTimer->start(1);
}

void GlWindow::modCurTime()
{
    currentTimeMs++;
    currentTimeS=currentTimeMs/1000.0f;    
}

void GlWindow::setObjFile(QString filename)
{
    mObjFileName = filename;
    qDebug() << "file selected " << mObjFileName;
}

void GlWindow::displayObj()
{
    mRepaintTimer->start(20);
}

void GlWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_P:
            break;
        case Qt::Key_Up:
            mRotX+=degRotSteps;
            break;
        case Qt::Key_Down:
            mRotX-=degRotSteps;
            break;
        case Qt::Key_Left:
            mRotY+=degRotSteps;
            break;
        case Qt::Key_Right:
            mRotY-=degRotSteps;
            break;
        case Qt::Key_Delete:
            mRotZ+=degRotSteps;
            break;
        case Qt::Key_PageDown:
            mRotZ-=degRotSteps;
            break;
        case Qt::Key_Home:
            mRotX   = mRotY   = mRotZ   = 0.0f;
            mTransX = mTransY = mTransZ = 0.0f;
            break;
        case Qt::Key_Z:
            mTransZ -= transSteps;
            break;
        case Qt::Key_S:
            mTransZ += transSteps;
            break;
        case Qt::Key_Q:
            mTransX -= transSteps;
            break;
        case Qt::Key_D:
            mTransX += transSteps;
            break;
        case Qt::Key_A:
            mTransY -= transSteps;
            break;
        case Qt::Key_E:
            mTransY += transSteps;
            break;
        default:
            break;
    }
}

void GlWindow::initialize()
{
    CreateVertexBuffer();
    initShaders();
    //initMatrices();

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
}

void GlWindow::CreateVertexBuffer()
{
    // *** Icosahedron
    mFuncs->glGenVertexArrays(1, &mVAOIcosahedron);
    mFuncs->glBindVertexArray(mVAOIcosahedron);

    mIcosahedron = new Icosahedron();

    // Create and populate the buffer objects
    unsigned int IcosahedronHandles[2];
    glGenBuffers(2, IcosahedronHandles);

    glBindBuffer(GL_ARRAY_BUFFER, IcosahedronHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, (3 * mIcosahedron->getnVerts()) * sizeof(float), mIcosahedron->getv(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IcosahedronHandles[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mIcosahedron->getnFaces() * sizeof(unsigned int), mIcosahedron->getel(), GL_STATIC_DRAW);

    // Setup the VAO
    // Vertex positions
    mFuncs->glBindVertexBuffer(0, IcosahedronHandles[0], 0, sizeof(GLfloat) * 3);
    mFuncs->glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    mFuncs->glVertexAttribBinding(0, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IcosahedronHandles[1]);

    mFuncs->glBindVertexArray(0);
}

void GlWindow::initMatrices()
{
    ViewMatrix.lookAt(QVector3D(1.0f, 1.25f, 1.25f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
}

void GlWindow::resizeEvent(QResizeEvent *)
{
    mUpdateSize = true;
}

void GlWindow::render()
{
    if(!isVisible() || !isExposed())
        return;

    if (!mContext->makeCurrent(this))
        return;

    static bool initialized = false;
    if (!initialized) {
        initialize();
        initialized = true;
    }

    if (mUpdateSize) {
        glViewport(0, 0, size().width(), size().height());
        mUpdateSize = false;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mFuncs->glBindVertexArray(mVAOIcosahedron);

    glEnableVertexAttribArray(0);
    mProgram->bind();
    {
        glDrawElements(GL_TRIANGLES, 3 * mIcosahedron->getnFaces(), GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
        glDisableVertexAttribArray(0);
    }
    mProgram->release();    

    mContext->swapBuffers(this);
}

void GlWindow::initShaders()
{
    QOpenGLShader vShader(QOpenGLShader::Vertex);
    QOpenGLShader fShader(QOpenGLShader::Fragment);

    QFile vertShaderFile(":/vshader.txt");
    vertShaderFile.open(QIODevice::ReadOnly);
    QByteArray vertShaderSource = vertShaderFile.readAll();
    vertShaderFile.close();

    QFile fragShaderFile(":/fshader.txt");
    fragShaderFile.open(QIODevice::ReadOnly);
    QByteArray fragShaderSource = fragShaderFile.readAll();
    fragShaderFile.close();

    qDebug() << "vertex 1 compile: " << vShader.compileSourceCode(vertShaderSource);
    qDebug() << "frag   1 compile: " << fShader.compileSourceCode(fragShaderSource);

    mProgram = new (QOpenGLShaderProgram);
    mProgram->addShader(&vShader);    
    mProgram->addShader(&fShader);
    qDebug() << "shader link: " << mProgram->link();
}


void GlWindow::setScaleX(double scale)
{
    mScaleX = (float)scale;
}

void GlWindow::setScaleY(double scale)
{
    mScaleY = (float)scale;
}

void GlWindow::setScaleZ(double scale)
{
    mScaleZ = (float)scale;
}

void GlWindow::setAutoScale()
{
    mScaleX  = mScaleY = mScaleZ = 1.0f;
}

float GlWindow::getAutoScale()
{
    return mScaleX;
}

void GlWindow::setRotAuto(bool ctrl)
{
    mRotAuto = ctrl;
}
