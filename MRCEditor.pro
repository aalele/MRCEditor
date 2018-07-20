# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = MRCEditor
DESTDIR = ./debug
QT += core opengl gui widgets
CONFIG += debug console
DEFINES += _UNICODE WIN64 QT_DEPRECATED_WARNINGS QT_CHARTS_LIB QT_OPENGL_LIB QT_WIDGETS_LIB
INCLUDEPATH +=  . \
    ./volume/GL/include \
    ./debug \
    $(QTDIR)/mkspecs/win32-msvc
LIBS += -L"./volume/GL/lib/Release/x64" \
    -lshell32 \
    -l./volume/GL/lib/Release/x64/glew32d \
    -lopengl32 \
    -lglu32
DEPENDPATH += .


HEADERS += ./volume/BasicControlWidget.h \
    ./volume/DoubleSlider.h \
    ./ItemContext.h \
    ./volume/TF1DEditor.h \
    ./volume/TF1DMappingCanvas.h \
    ./volume/TF1DTextureCanvas.h \
    ./volume/TF2DEditor.h \
    ./volume/TF2DMappingCanvas.h \
    ./volume/TransferFunction1DWidget.h \
    ./volume/VolumeRenderWidget.h \
    ./volume/VolumeRenderingWindow.h \
    ./abstractplugin.h \
    ./histogram.h \
    ./imageviewer.h \
    ./mainwindow.h \
    ./markcategorydialog.h \
    ./markinfowidget.h \
    ./markmodel.h \
    ./mrcfileinfoviewer.h \
    ./pixelviewer.h \
    ./profileview.h \
    ./sliceview.h \
    ./titledsliderwithspinbox.h \
    ./zoomviwer.h \
    ./volume/BMPWriter.h \
    ./CImg.h \
    ./volume/ClassificationWidget.h \
    ./volume/Rendering/MIPRender.h \
    ./volume/ModelData.h \
    ./volume/Rendering/Shader.h \
    ./volume/ShaderData.h \
    ./volume/Rendering/ShaderProgram.h \
    ./volume/TF1DMappingKey.h \
    ./volume/TF2DPrimitive.h \
    ./volume/Rendering/Vector.h \
    ./volume/Volume.h \
    ./volume/Rendering/VolumeLightingRenderTF1D.h \
    ./volume/Rendering/VolumeLightingRenderingTF2D.h \
    ./volume/Rendering/VolumeRenderingTF1D.h \
    ./abstractslicedatamodel.h \
    ./volume/Healpix/arr.h \
    ./volume/camera.h \
    ./categoryitem.h \
    ./volume/Healpix/constants.h \
    ./volume/Healpix/cxxutils.h \
    ./volume/framebufferObject.h \
    ./globals.h \
    ./volume/Healpix/healpix_base.h \
    ./markitem.h \
    ./marktreeview.h \
    ./volume/Rendering/matrix2.h \
    ./volume/Rendering/matrix3.h \
    ./volume/Rendering/matrix4.h \
    ./volume/Healpix/message_error.h \
    ./mrc.h \
    ./mrcdatamodel.h \
    ./volume/Healpix/pointing.h \
    ./volume/renderview.h \
    ./sliceitem.h \
    ./treeitem.h \
    ./volume/Healpix/vec3.h \
    ./volumewidget.h \
    ./RenderParameterWidget.h
SOURCES += ./volume/BMPWriter.cpp \
    ./volume/BasicControlWidget.cpp \
    ./volume/ClassificationWidget.cpp \
    ./volume/DoubleSlider.cpp \
    ./ItemContext.cpp \
    ./volume/Rendering/Shader.cpp \
    ./volume/Rendering/ShaderProgram.cpp \
    ./volume/TF1DEditor.cpp \
    ./volume/TF1DMappingCanvas.cpp \
    ./volume/TF1DTextureCanvas.cpp \
    ./volume/TF2DEditor.cpp \
    ./volume/TF2DMappingCanvas.cpp \
    ./volume/TF2DPrimitive.cpp \
    ./volume/TransferFunction1DWidget.cpp \
    ./volume/Volume.cpp \
    ./volume/VolumeRenderWidget.cpp \
    ./volume/VolumeRenderingWindow.cpp \
    ./abstractplugin.cpp \
    ./abstractslicedatamodel.cpp \
    ./volume/camera.cpp \
    ./categoryitem.cpp \
    ./volume/Healpix/cxxutils.cpp \
    ./volume/framebufferObject.cpp \
    ./volume/Healpix/healpix_base.cpp \
    ./histogram.cpp \
    ./imageviewer.cpp \
    ./main.cpp \
    ./mainwindow.cpp \
    ./markcategray.cpp \
    ./markinfowidget.cpp \
    ./markitem.cpp \
    ./markmodel.cpp \
    ./marktreeview.cpp \
    ./mrc.cpp \
    ./mrcdatamodel.cpp \
    ./mrcfileinfoviewer.cpp \
    ./pixelviewer.cpp \
    ./profileview.cpp \
    ./volume/renderview.cpp \
    ./sliceitem.cpp \
    ./sliceview.cpp \
    ./titledsliderwithspinbox.cpp \
    ./treeitem.cpp \
    ./volumewidget.cpp \
    ./zoomviwer.cpp \
    ./RenderParameterWidget.cpp
RESOURCES += resources.qrc
