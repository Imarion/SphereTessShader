#QT += gui-private core-private
QT += gui core widgets opengl

HEADERS += SphereTessShader.h \
    mainwindow.h \
    about.h \
    Icosahedron.h

SOURCES += SphereTessShader.cpp main.cpp \
    mainwindow.cpp \
    about.cpp \
    Icosahedron.cpp

OTHER_FILES += \
    vshader.txt \
    fshader.txt

RESOURCES += \
    shaders.qrc

FORMS += \
    mainwindow.ui \
    about.ui

