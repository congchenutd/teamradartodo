#ifndef TAGGINGMANAGER_H
#define TAGGINGMANAGER_H

#include "TagKeyword.h"
#include "Communicator.h"
#include <projectexplorer/project.h>
#include <coreplugin/editormanager/editormanager.h>
#include <QObject>
#include <QFuture>

class QListWidgetItem;

namespace TeamRadar {

class TagOutputPane;
struct TaggingEvent;

class TaggingManager : public QObject
{
	Q_OBJECT
public:
	TaggingManager(TagOutputPane* output, QObject* parent = 0);
	
private slots:
	void onGotoRow(QListWidgetItem*);
	void onCurrentEditorChanged(Core::IEditor* editor);
	void onFileChanged();
	void onProjectChanged(ProjectExplorer::Project* project);
	void onRemoteTaggingEvent(const TaggingEvent& event);

private:
	void readFile(const QString& filePath);
	QRegExp generatePattern(const TagKeyword& tag);
	TagKeyword findMatchingTag(const QString& line);
	void formatLine(QString& line, const TagKeyword& tag);

	static void readCurrentProject(QFutureInterface<void>& future, TaggingManager* instance);

private:
	ProjectExplorer::Project* currentProject;
	TagOutputPane* outPane;
	Communicator*  communicator;
	TagKeywords    tags;
	bool           reading;
};

}

#endif // TAGGINGMANAGER_H
