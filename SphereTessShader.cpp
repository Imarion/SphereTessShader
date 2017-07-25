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
    mFuncs->glDeleteVertexArrays(1, &mVAO);
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
    format.setMajorVersion(3);
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

    mFuncs = mContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
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
    mRepaintTimer->start(20);

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
#if 0
    {
        mRepaintTimer->stop();
        convertWFOObjectToGl();

        setAutoScale();

        /* Cette partie en commentaire fonctionne bien en indexed draw */
        /*
        glBufferData(GL_ARRAY_BUFFER, mWaveFrontObject.getInstance().getNumVertices() * WaveFrontObject::getNumDataPerVertex() * sizeof(GLfloat), mObjVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mWaveFrontObject.getInstance().getNumIndices() * sizeof(GLint), mObjIndices, GL_STATIC_DRAW);
        */

        glBindBuffer(GL_ARRAY_BUFFER, mVerticesBuffer);
        glBufferData(GL_ARRAY_BUFFER, mWaveFrontObject.getInstance().getNumIndices() * WaveFrontObject::getNumDataPerVertex() * sizeof(GLfloat), mObjVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, mColorsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mWaveFrontObject.getInstance().getNumIndices() * MaterialData::getRawDataSize(), mObjMaterials, GL_STATIC_DRAW);
        for (int i=0; i<3; i++) // Ka=loc 3, Kd=loc 4, Ks=loc 5
        {
            glVertexAttribPointer (i+3, 3, GL_FLOAT, GL_FALSE, MaterialData::getRawDataSize(), (GLvoid *)(i*3*sizeof(GLfloat)));
            glEnableVertexAttribArray(i+3);
        }

        // Ns: loc = 6        
        glVertexAttribPointer (6, 1, GL_FLOAT, GL_FALSE, MaterialData::getRawDataSize(), (GLvoid *)(9*sizeof(GLfloat)));
        glEnableVertexAttribArray(6);

        glBindBuffer(GL_ARRAY_BUFFER, mNormalsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mWaveFrontObject.getInstance().getNumIndices() * Normal::getNumData() * sizeof(GLfloat), mObjNormals, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);

        mRepaintTimer->start(20);
    }
    else
    {
        qDebug() << "error loading " << mObjFileName;
    }
#endif
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
    initShaders();
    //mv_location       = glGetUniformLocation(mProgram->programId(), "mv_matrix");
    //proj_location     = glGetUniformLocation(mProgram->programId(), "proj_matrix");
    model_location    = glGetUniformLocation(mProgram->programId(), "model");
    camera_location   = glGetUniformLocation(mProgram->programId(), "camera"); // camera-lookat
    campos_location   = glGetUniformLocation(mProgram->programId(), "cameraPosition"); // camera position
    ka_location       = glGetUniformLocation(mProgram->programId(), "material.Ka");
    kd_location       = glGetUniformLocation(mProgram->programId(), "material.Kd");
    ks_location       = glGetUniformLocation(mProgram->programId(), "material.Ks");
    ns_location       = glGetUniformLocation(mProgram->programId(), "material.Ns");

    mFuncs->glGenVertexArrays(1, &mVAO);
    mFuncs->glBindVertexArray(mVAO);

    glGenBuffers(1, &mVerticesBuffer);
    glGenBuffers(1, &mNormalsBuffer);
    glGenBuffers(1, &mColorsBuffer);

    glGenBuffers(1, &mIndicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesBuffer);

//    glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CW);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);

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

    //static const GLfloat backCol[] = { 0.6f, 0.4f, 0.1f, 1.0f }; // orange
    static const GLfloat backCol[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    mFuncs->glClearBufferfv(GL_COLOR, 0, backCol);

    static const GLfloat one = 1.0f;
    mFuncs->glClearBufferfv(GL_DEPTH, 0, &one);

    mProgram->bind();
    {
        QMatrix4x4 modelViewMatrix;
        QMatrix4x4 cameraMatrix;
        QVector3D  cameraPos(0.0f, 0.0f, 4.0f);

        cameraMatrix.perspective(50.0f, this->width()/this->height(), 0.1f, 1000.0f);        
        cameraMatrix.lookAt(cameraPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(camera_location, 1, GL_FALSE, cameraMatrix.constData());
        glUniform3f(campos_location, cameraPos.x(), cameraPos.y(), cameraPos.z());

        //modelViewMatrix.translate(0.0f, 0.0f, -4.0f);
        modelViewMatrix.translate(mTransX, mTransY, mTransZ);
        if (mRotAuto)
        {
            modelViewMatrix.rotate((float)currentTimeS * -21.0f, 1.0f, 0.0f, 0.0f);
            modelViewMatrix.rotate((float)currentTimeS * -45.0f, 0.0f, 1.0f, 0.0f);
        }
        else
        {
            modelViewMatrix.rotate(mRotX, 1.0f, 0.0f, 0.0f);
            modelViewMatrix.rotate(mRotY, 0.0f, 1.0f, 0.0f);
            modelViewMatrix.rotate(mRotZ, 0.0f, 0.0f, 1.0f);
        }
        modelViewMatrix.scale(mScaleX, mScaleY, mScaleZ);

        glUniformMatrix4fv(model_location, 1, GL_FALSE, modelViewMatrix.constData());

        /* Cette partie en commentaire fonctionne bien en indexed draw */
        /*
        glDrawElements(GL_TRIANGLES, mWaveFrontObject.getInstance().getNumIndices(), GL_UNSIGNED_INT, (GLvoid *)(sizeof(GLuint)*0));
        */        

        //glDrawArrays(GL_TRIANGLE_FAN, 0, mWaveFrontObject.getInstance().getNumIndices());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
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
