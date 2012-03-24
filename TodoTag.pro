TEMPLATE = lib
TARGET = TodoTag
QT += network
PROVIDER = CongChen

#include(../TeamRadar/TeamRadar.pri)
include(TodoTag_dependencies.pri)

LIBS += -L$$IDE_LIBRARY_PATH \
		-L$$IDE_PLUGIN_PATH/Nokia

INCLUDEPATH += ../MySetting \
	../TeamRadar

HEADERS += \
	ColorLabel.h \
	TagDlg.h \
	Communicator.h \
    TagKeyword.h \
    TagOutputPane.h \
    TagPlugin.h \
    TagOptionsDlg.h \
    TagOptionsPage.h \
    TagSetting.h \
    TaggingManager.h

SOURCES += \
	ColorLabel.cpp \
	TagDlg.cpp \
	Communicator.cpp \
    TagKeyword.cpp \
    TagOutputPane.cpp \
    TagPlugin.cpp \
    TagOptionsDlg.cpp \
    TagOptionsPage.cpp \
    TagSetting.cpp \
    TaggingManager.cpp

RESOURCES += Resource.qrc

FORMS += \
	TagDlg.ui \
    TagOptionsDlg.ui

OTHER_FILES += \
    TodoTag.pluginspec
