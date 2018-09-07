# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = MRCEditor
DESTDIR = ./debug
QT += core opengl gui widgets
CONFIG += debug console
DEFINES += _UNICODE WIN64 QT_DEPRECATED_WARNINGS QT_CHARTS_LIB QT_OPENGL_LIB QT_WIDGETS_LIB
DEPENDPATH += .


QMAKE_CXXFLAGS+= -openmp
QMAKE_LFLAGS+= -openmp


HEADERS +=./widgets/doubleslider.h \
    ./widgets/TF1DEditor.h \
    ./widgets/TF1DMappingCanvas.h \
    ./widgets/TF1DTextureCanvas.h \
    ./abstract/abstractplugin.h \
    ./widgets/histogramwidget.h \
    ./widgets/sliceeditorwidget.h \
    ./widgets/mainwindow.h \
    ./widgets/markcategorydialog.h \
    ./widgets/markinfowidget.h \
    ./model/markmodel.h \
    ./widgets/fileinfowidget.h \
    ./widgets/pixelwidget.h \
    ./widgets/profilewidget.h \
    ./widgets/slicewidget.h \
    ./widgets/titledsliderwithspinbox.h \
    ./widgets/zoomwidget.h \
    ./algorithm/CImg.h \
    ./widgets/TF1DMappingKey.h \
    ./abstract/abstractslicedatamodel.h \
    ./3drender/geometry/camera.h \
    ./model/categoryitem.h \
    ./globals.h \
    ./model/markitem.h \
    ./widgets/marktreeviewwidget.h \
    ./model/mrc.h \
    ./model/mrcdatamodel.h \
    ./model/sliceitem.h \
    ./model/treeitem.h \
    ./widgets/renderwidget.h \
    ./widgets/renderoptionwidget.h \
    ./widgets/slicetoolwidget.h \
    ./3drender/shader/shaderdatainterface.h \
    ./3drender/shader/shaderprogram.h \
    ./algorithm/gradientcalculator.h \
    ./3drender/shader/raycastingshader.h \
    ./3drender/geometry/mesh.h \
    ./3drender/geometry/geometry.h \
    ./3drender/geometry/volume.h
SOURCES +=./widgets/doubleslider.cpp \
    ./widgets/TF1DEditor.cpp \
    ./widgets/TF1DMappingCanvas.cpp \
    ./widgets/TF1DTextureCanvas.cpp \
    ./abstract/abstractplugin.cpp \
    ./abstract/abstractslicedatamodel.cpp \
    ./model/categoryitem.cpp \
    ./widgets/histogramwidget.cpp \
    ./widgets/sliceeditorwidget.cpp \
    ./main.cpp \
    ./widgets/mainwindow.cpp \
    ./widgets/markcategray.cpp \
    ./widgets/markinfowidget.cpp \
    ./model/markitem.cpp \
    ./model/markmodel.cpp \
    ./widgets/marktreeviewwidget.cpp \
    ./model/mrc.cpp \
    ./model/mrcdatamodel.cpp \
    ./widgets/fileinfowidget.cpp \
    ./widgets/pixelwidget.cpp \
    ./widgets/profilewidget.cpp \
    ./model/sliceitem.cpp \
    ./widgets/slicewidget.cpp \
    ./widgets/titledsliderwithspinbox.cpp \
    ./model/treeitem.cpp \
    ./widgets/renderwidget.cpp \
    ./widgets/zoomwidget.cpp \
    ./widgets/renderoptionwidget.cpp \
    ./widgets/slicetoolwidget.cpp \
    ./algorithm/gradientcalculator.cpp \
    ./3drender/shader/shaderprogram.cpp \
    ./3drender/shader/raycastingshader.cpp \
    ./3drender/geometry/mesh.cpp \
    ./3drender/geometry/volume.cpp
RESOURCES += resources.qrc


