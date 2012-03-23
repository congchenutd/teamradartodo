TEMPLATE = lib
TARGET = TODO
QT += network

#include(../TeamRadar/TeamRadar.pri)
include(Todo_dependencies.pri)

LIBS += -L$$IDE_LIBRARY_PATH \
		-L$$IDE_PLUGIN_PATH/Nokia \
		-L$$IDE_PLUGIN_PATH/CongChen

INCLUDEPATH += ../MySetting \
	../TeamRadar

HEADERS += \
	ColorLabel.h \
	SettingDlg.h \
	SettingPage.h \
	TodoOutputPane.h \
	TodoPlugin.h \
	Tag.h \
	TagDlg.h \
	Communicator.h \
	../TeamRadar/Connection.h \
	../TeamRadar/TeamRadarEvent.h \
    ../TeamRadar/Setting.h \
    TodoSetting.h

SOURCES += \
	ColorLabel.cpp \
	SettingDlg.cpp \
	SettingPage.cpp \
	TodoOutputPane.cpp \
	TodoPlugin.cpp \
	Tag.cpp \
	TagDlg.cpp \
	Communicator.cpp \
	../TeamRadar/Connection.cpp \
    ../TeamRadar/Setting.cpp \
    TodoSetting.cpp

RESOURCES += Resource.qrc

FORMS += \
	SettingDlg.ui \
	TagDlg.ui

OTHER_FILES += Todo.pluginspec
