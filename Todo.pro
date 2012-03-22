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
    KeywordDlg.h \
    ColorLabel.h \
    SettingDlg.h \
    SettingPage.h \
    TodoOutputPane.h \
    TodoPlugin.h \
    Keyword.h \
    ../MySetting/MySetting.h \
    Setting.h

SOURCES += \
    KeywordDlg.cpp \
    ColorLabel.cpp \
    SettingDlg.cpp \
    SettingPage.cpp \
    TodoOutputPane.cpp \
    TodoPlugin.cpp \
    Keyword.cpp \
    Setting.cpp

RESOURCES += Resource.qrc

FORMS += \
    KeywordDlg.ui \
    SettingDlg.ui

OTHER_FILES += Todo.pluginspec
