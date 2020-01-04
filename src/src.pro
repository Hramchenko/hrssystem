SOURCES += main.cpp \
 hvoxel.cpp \
 hmainwindow.cpp \
 hglscreen.cpp \
 hmodelviewer.cpp \
 hmodelviewerc.cpp \
 hvirtualtrackball.cpp \
 hframe.cpp \
 hframelist.cpp \
 hframeparam.cpp \
 hframeparamlist.cpp \
 hframeparamlookat.cpp \
 hworkspaceloader.cpp \
 hreconstruction.cpp \
 hcomparator.cpp \
 hmodelviewert.cpp \
 hobjectconvertertotrianglemesh.cpp \
 hobjectconvertertovoxelvolume.cpp \
 hworkspacesaver.cpp \
 hmodel.cpp \
 hprojectfilesdock.cpp \
 hglulookatparamsdock.cpp \
 hglmatrixparamsdock.cpp \
 hframeparamsdock.cpp \
 heditdescriptiondialog.cpp \
 hdocumentstab.cpp \
 hframeparammatrix.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = hrssystem
DESTDIR = ../bin/
QT += opengl xml widgets

LIBS += -L/usr/local/lib -lGLU

HEADERS += hvoxel.h \
 hmainwindow.h \
 hglscreen.h \
 hmodelviewer.h \
 hmodelviewerc.h \
 hvirtualtrackball.h \
 hframe.h \
 hframelist.h \
 hframeparam.h \
 hframeparamlist.h \
 hframeparamlookat.h \
 hworkspaceloader.h \
 hreconstruction.h \
 hcomparator.h \
 hmodelviewert.h \
 hobjectconvertertotrianglemesh.h \
 hobjectconvertertovoxelvolume.h \
 hworkspacesaver.h \
 hmodel.h \
 hprojectfilesdock.h \
 hglulookatparamsdock.h \
 hglmatrixparamsdock.h \
 hframeparamsdock.h \
 heditdescriptiondialog.h \
 hdocumentstab.h \
 hframeparammatrix.h

FORMS += HMainWindow.ui \
 HEditDescriptionDialog.ui

RESOURCES += ../data/HMainWindow.qrc

CONFIG+=debug
