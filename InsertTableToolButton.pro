#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T06:48:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InsertTableToolButton
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    InsertTableToolButton.cpp \
    TableSizeSelector.cpp \
    TableSizeSelectorActionWidget.cpp \
    TableSizeConstraintsActionWidget.cpp

HEADERS  += MainWindow.h \
    InsertTableToolButton.h \
    TableSizeSelector.h \
    TableSizeSelectorActionWidget.h \
    TableSizeConstraintsActionWidget.h

FORMS    += MainWindow.ui

greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets
  INCLUDEPATH += $$QT_DIR/include/QtWidgets \
                 $$QT_DIR/QtWidgets
}

RESOURCES += \
    table_icon.qrc
