#include <QWindow>
#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QString>

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

//class MyWindow : public QWindow, protected QOpenGLFunctions_4_3_Core
class GlWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GlWindow();
    virtual  ~GlWindow();
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    void    setObjFile(QString filename);
    void    displayObj();

    // scale
    void    setScaleX(double scale);
    void    setScaleY(double scale);
    void    setScaleZ(double scale);
    void    setAutoScale();
    float   getAutoScale();

    // rotate
    void    setRotAuto(bool ctrl);

private slots:
    void render();

private:    
    void   initialize();
    void   modCurTime();
    void   initShaders();

protected:
    void resizeEvent(QResizeEvent *);

private:
    // the opengl framework
    QOpenGLContext            *mContext;
    QOpenGLFunctions_3_3_Core *mFuncs;
    QOpenGLShaderProgram      *mProgram;

    QTimer *mRepaintTimer;
    QTimer *mElapsedTimer;

    double currentTimeMs;
    double currentTimeS;
    bool   mUpdateSize;

    // opengl display data
    GLuint mVAO; // Vertex array object

    QMatrix4x4 proj_matrix;
    //GLint mv_location, proj_location;
    GLint model_location, camera_location, campos_location;
    GLint ka_location, kd_location, ks_location, ns_location;

    GLfloat  *mObjVertices;
    GLfloat  *mObjNormals;
    GLuint   *mObjIndices;
    GLfloat  *mObjMaterials;
    GLuint   mVerticesBuffer, mIndicesBuffer, mNormalsBuffer, mColorsBuffer;

    GLfloat  mScaleX, mScaleY, mScaleZ;
    const float degRotSteps = 1.0f;
    GLfloat  mRotX,   mRotY,   mRotZ;
    bool     mRotAuto;
    const float transSteps  = 0.1f;
    GLfloat  mTransX, mTransY, mTransZ;

    // object data
    static const int numDataPerFace = 3;  // only manages triangles
    QString          mObjFileName;
};
