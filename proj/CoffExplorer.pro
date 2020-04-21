
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../bin

#---------------------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------------------
CONFIG(debug, debug|release) {
TARGET = CoffExplorer_d
DEFINES += DEBUG
} else {
TARGET = CoffExplorer
}

#---------------------------------------------------------------------------------------------------
# Version
#---------------------------------------------------------------------------------------------------
DEFINES += MAJOR_VERSION=1
DEFINES += MINOR_VERSION=0

#---------------------------------------------------------------------------------------------------
# Source files
#---------------------------------------------------------------------------------------------------
SOURCES += \
        src/main.cpp \
        src/MainWindow.cpp \
    src/TreeItem.cpp \
    src/TreeModel.cpp \
    src/TreeItemSymbolTable.cpp \
    src/TreeItemSection.cpp \
    src/TreeItemFileHeader.cpp \
    src/TreeItemFolder.cpp \
    src/TreeItemRoot.cpp \
    src/AboutDialog.cpp \
    src/SymbolTableItem.cpp \
    src/SymbolTableModel.cpp \
    src/TreeItemStringTable.cpp \
    src/StringTableModel.cpp \
    src/Languages.cpp \
    src/RecentFilesMenu.cpp \
    src/RelocationsModel.cpp

HEADERS += \
        src/MainWindow.h \
    src/TreeItem.h \
    src/TreeModel.h \
    src/coff.h \
    src/TreeItemSymbolTable.h \
    src/TreeItemSection.h \
    src/TreeItemFileHeader.h \
    src/TreeItemFolder.h \
    src/TreeItemRoot.h \
    src/AboutDialog.h \
    src/SymbolTableItem.h \
    src/SymbolTableModel.h \
    src/TreeItemStringTable.h \
    src/StringTableModel.h \
    src/Languages.h \
    src/RecentFilesMenu.h \
    src/RelocationsModel.h

FORMS += \
        src/MainWindow.ui \
    src/AboutDialog.ui

#---------------------------------------------------------------------------------------------------
# Resource files
#---------------------------------------------------------------------------------------------------

RESOURCES += res/resource.qrc

win32:RC_FILE = res/resource_win32.rc

#---------------------------------------------------------------------------------------------------
# Translation files
#---------------------------------------------------------------------------------------------------
TRANSLATIONS =  translate/coffexplorer_en.ts \
                translate/coffexplorer_es.ts
