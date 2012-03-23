#include "TodoPlugin.h"
#include "SettingPage.h"
#include "Setting.h"
#include <coreplugin/icore.h>
#include <coreplugin/ifile.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/progressmanager/progressmanager.h>
#include <coreplugin/progressmanager/futureprogress.h>
#include <qtconcurrent/runextensions.h>
#include <extensionsystem/pluginmanager.h>
#include <QtPlugin>
#include <QStringList>
#include <QtConcurrentRun>
#include <QFile>
#include <QSettings>
#include <QTextCodec>

TodoPlugin::TodoPlugin()
{
	qRegisterMetaTypeStreamOperators<Tag>("Tag");
	qRegisterMetaTypeStreamOperators<TagList>("TagList");
}

bool TodoPlugin::initialize(const QStringList& args, QString *errMsg)
{
	Q_UNUSED(args);
	Q_UNUSED(errMsg);
	currentProject = 0;
	reading = false;

	tags = Setting::getInstance()->getTags();
	addAutoReleasedObject(new SettingPage(this));
	addAutoReleasedObject(new AboutPage(this));

	outPane = new TodoOutputPane(this);
	addAutoReleasedObject(outPane);
	connect(outPane->getTodoList(), SIGNAL(itemClicked(QListWidgetItem*)),   this, SLOT(onGotoRow(QListWidgetItem*)));
	connect(outPane->getTodoList(), SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onGotoRow(QListWidgetItem*)));

	connect(Core::EditorManager::instance(), SIGNAL(currentEditorChanged(Core::IEditor*)), this, SLOT(onCurrentEditorChanged(Core::IEditor*)));
	connect(ProjectExplorer::ProjectExplorerPlugin::instance(), SIGNAL(currentProjectChanged(ProjectExplorer::Project*)), this, SLOT(onProjectChanged(ProjectExplorer::Project*)));
	return true;
}

void TodoPlugin::onGotoRow(QListWidgetItem* item)
{
	QString filePath = item->data(TodoOutputPane::FilePathRole).toString();
	if(QFileInfo(filePath).exists())
	{
		Core::IEditor* editor = Core::EditorManager::instance()->openEditor(filePath);
		int row = item->data(TodoOutputPane::LineNumberRole).toInt();
		editor->gotoLine(row);
	}
}

void TodoPlugin::onCurrentEditorChanged(Core::IEditor* editor)
{
	if(reading || editor == 0)
		return;

	connect(editor->file(), SIGNAL(changed()), this, SLOT(onFileChanged()));
}

void TodoPlugin::onFileChanged()
{
	if(Core::IFile* file = dynamic_cast<Core::IFile*>(sender()))
	{
		outPane->clearContents(file->fileName());
		readFile(file->fileName());
	}
}

QRegExp TodoPlugin::generatePattern(const Tag& tag) {
	return QRegExp("//\\s*" + tag.name + "(:|\\s)", Qt::CaseInsensitive);
}

Tag TodoPlugin::findMatchingTag(const QString& line)
{
	foreach(const Tag& tag, tags)
		if(line.contains(generatePattern(tag)))
			return tag;
	return Tag();
}

void TodoPlugin::formatLine(QString& line, const Tag& tag)
{
	line.replace("\n", "");
	line.replace("\r", "");
	line.replace(generatePattern(tag), tag.name + ": ");
	line = line.trimmed();
	line = QTextCodec::codecForLocale()->toUnicode(line.toAscii());
}

void TodoPlugin::readFile(const QString& filePath)
{
	QFile file(filePath);
	if(!file.open(QFile::ReadOnly | QFile::Text))
		return;

	for(int lineNumber = 1; !file.atEnd(); ++lineNumber)
	{
		QString line = file.readLine();
		Tag tag = findMatchingTag(line);
		if(tag.isValid())
		{
			formatLine(line, tag);
			outPane->addItem(line, filePath, lineNumber, tag);
			if(!reading)
				outPane->sort();
		}
	}
}

void TodoPlugin::onProjectChanged(ProjectExplorer::Project* project)
{
	if(project == 0 || reading)
		return;

	currentProject = project;
	outPane->clearContents();

	reading = true;
	QFuture<void> result = QtConcurrent::run(&TodoPlugin::readCurrentProject, this);
	Core::ICore::instance()->progressManager()->addTask(result, tr("TodoScan"), "Todo.Plugin.Scanning");
}

void TodoPlugin::readCurrentProject(QFutureInterface<void>& future, TodoPlugin* instance)
{
	QStringList filesList = instance->currentProject->files(
								ProjectExplorer::Project::ExcludeGeneratedFiles);
	future.setProgressRange(0, filesList.count()-1);
	for(int i = 0; i < filesList.count(); ++i)
	{
		instance->readFile(filesList.at(i));
		future.setProgressValue(i);
	}

	instance->outPane->sort();
	instance->reading = false;
	future.reportFinished();
}

Q_EXPORT_PLUGIN(TodoPlugin)


