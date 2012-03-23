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
#include "TagOutputPane.h"
#include "TagKeyword.h"
#include "Communicator.h"

namespace TeamRadar {

class Communicator;

class TagPlugin : public ExtensionSystem::IPlugin
{
	Q_OBJECT
public:
	TagPlugin();
	virtual void extensionsInitialized() {}
	virtual bool initialize(const QStringList& arguments, QString* errorString);

private slots:
	void onGotoRow(QListWidgetItem*);
	void onCurrentEditorChanged(Core::IEditor* editor);
	void onFileChanged();
	void onProjectChanged(ProjectExplorer::Project*);
	void onRemoteTaggingEvent(const TaggingEvent& event);

private:
	void readFile(const QString& filePath);

	QRegExp generatePattern(const TagKeyword& tag);
	TagKeyword findMatchingTag(const QString& line);
	void formatLine(QString& line, const TagKeyword& tag);

	static void readCurrentProject(QFutureInterface<void>& future, TagPlugin* instance);

private:
	TagOutputPane*           outPane;
	ProjectExplorer::Project* currentProject;
	Communicator* communicator;
	TagKeywords tags;
	bool    reading;
};

}  // namespace TeamRadar

#endif // TODOPLUGIN_H

