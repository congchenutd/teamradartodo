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
#include "keyword.h"

class TodoPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
public:
    TodoPlugin();
	virtual void extensionsInitialized() {}
	virtual bool initialize(const QStringList& arguments, QString* errorString);

public slots:
	void onGotoRow(QListWidgetItem*);
	void onCurrentEditorChanged(Core::IEditor* editor);
	void onFileChanged();
	void onProjectChanged(ProjectExplorer::Project*);

private:
	void readFile(const QString& filePath);

	QRegExp generatePattern(const Keyword& keyword);
	Keyword findMatchingKeyword(const QString& line);
	void    formatLine(QString& line, const Keyword& keyword);

	static void readCurrentProject(QFutureInterface<void>& future, TodoPlugin* instance);

private:
	TodoOutputPane*           outPane;
	ProjectExplorer::Project* currentProject;
	KeywordList keywords;
	bool         reading;
};
#endif // TODOPLUGIN_H
 
