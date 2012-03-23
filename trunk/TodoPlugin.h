#ifndef TODOPLUGIN_H
#define TODOPLUGIN_H
#include <QFuture>
#include <QList>
#include <extensionsystem/iplugin.h>
#include <coreplugin/editormanager/editormanager.h>
#include <projectexplorer/task.h>
#include <projectexplorer/taskhub.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>
#include "todooutputpane.h"
#include "Tag.h"

namespace TeamRadarTag {

class Communicator;

class TodoPlugin : public ExtensionSystem::IPlugin
{
	Q_OBJECT
public:
	TodoPlugin();
	virtual void extensionsInitialized() {}
	virtual bool initialize(const QStringList& arguments, QString* errorString);

private slots:
	void onGotoRow(QListWidgetItem*);
	void onCurrentEditorChanged(Core::IEditor* editor);
	void onFileChanged();
	void onProjectChanged(ProjectExplorer::Project*);
//	void onRemoteTaggingEvent();

private:
	void readFile(const QString& filePath);

	QRegExp generatePattern(const Tag& tag);
	Tag findMatchingTag(const QString& line);
	void formatLine(QString& line, const Tag& tag);

	static void readCurrentProject(QFutureInterface<void>& future, TodoPlugin* instance);

private:
	TodoOutputPane*           outPane;
	ProjectExplorer::Project* currentProject;
	Communicator* communicator;
	TagList tags;
	bool    reading;
};

}  // namespace TeamRadarTag

#endif // TODOPLUGIN_H

