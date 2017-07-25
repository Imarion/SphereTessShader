#QT += gui-private core-private
QT += gui core widgets opengl

HEADERS += SphereTessShader.h \
    mainwindow.h \
    about.h

SOURCES += SphereTessShader.cpp main.cpp \
    mainwindow.cpp \
    about.cpp \

OTHER_FILES += \
    vshader.txt \
    fshader.txt

RESOURCES += \
    shaders.qrc

FORMS += \
    mainwindow.ui \
    about.ui

