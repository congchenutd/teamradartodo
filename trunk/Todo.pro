TEMPLATE = lib
TARGET = TODO
PROVIDER = CongChen
QT += network

include(EV.pri)
include($$IDE_SOURCE_TREE/src/qtcreatorplugin.pri)
include($$IDE_SOURCE_TREE/src/plugins/coreplugin/coreplugin.pri)
include($$IDE_SOURCE_TREE/src/plugins/projectexplorer/projectexplorer.pri)
include($$IDE_SOURCE_TREE/src/plugins/texteditor/texteditor.pri)

LIBS += -L$$IDE_LIBRARY_PATH \
		-L$$IDE_PLUGIN_PATH/Nokia \
		-L$$IDE_SOURCE_TREE/lib/qtcreator

INCLUDEPATH += ../MySetting

HEADERS += \
    ColorLabel.h \
    SettingDlg.h \
    SettingPage.h \
    TodoOutputPane.h \
    TodoPlugin.h \
    ../MySetting/MySetting.h \
    Setting.h \
    Tag.h \
    TagDlg.h

SOURCES += \
    ColorLabel.cpp \
    SettingDlg.cpp \
    SettingPage.cpp \
    TodoOutputPane.cpp \
    TodoPlugin.cpp \
    Setting.cpp \
    Tag.cpp \
    TagDlg.cpp

RESOURCES += Resource.qrc

FORMS += \
    SettingDlg.ui \
    TagDlg.ui

OTHER_FILES += Todo.pluginspec
