#include "TagPlugin.h"
#include "TagOptionsPage.h"
#include "TagSetting.h"
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

namespace TeamRadar {

TagPlugin::TagPlugin()
{
	qRegisterMetaTypeStreamOperators<TagKeyword> ("TagKeyword");
	qRegisterMetaTypeStreamOperators<TagKeywords>("TagKeywords");
}

bool TagPlugin::initialize(const QStringList& args, QString* errMsg)
{
	Q_UNUSED(args);
	Q_UNUSED(errMsg);
	currentProject = 0;
	reading = false;

	tags = TagSetting::getInstance()->getTags();
	addAutoReleasedObject(new TagOptionsPage(this));
	addAutoReleasedObject(new TagAboutPage(this));

	outPane = new TagOutputPane(this);
	addAutoReleasedObject(outPane);
	connect(outPane->getTodoList(), SIGNAL(itemClicked(QListWidgetItem*)),   this, SLOT(onGotoRow(QListWidgetItem*)));
	connect(outPane->getTodoList(), SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onGotoRow(QListWidgetItem*)));

	communicator = new Communicator(this);
	connect(communicator, SIGNAL(remoteTagging(TaggingEvent)), this, SLOT(onRemoteTaggingEvent(TaggingEvent)));

	connect(Core::EditorManager::instance(), SIGNAL(currentEditorChanged(Core::IEditor*)), this, SLOT(onCurrentEditorChanged(Core::IEditor*)));
	connect(ProjectExplorer::ProjectExplorerPlugin::instance(), SIGNAL(currentProjectChanged(ProjectExplorer::Project*)), this, SLOT(onProjectChanged(ProjectExplorer::Project*)));
	return true;
}

void TagPlugin::onGotoRow(QListWidgetItem* item)
{
	QString filePath = item->data(TagOutputPane::FilePathRole).toString();
	if(QFileInfo(filePath).exists())
	{
		Core::IEditor* editor = Core::EditorManager::instance()->openEditor(filePath);
		int row = item->data(TagOutputPane::LineNumberRole).toInt();
		editor->gotoLine(row);
	}
}

void TagPlugin::onCurrentEditorChanged(Core::IEditor* editor)
{
	if(reading || editor == 0)
		return;

	connect(editor->file(), SIGNAL(changed()), this, SLOT(onFileChanged()));
}

void TagPlugin::onFileChanged()
{
	if(Core::IFile* file = dynamic_cast<Core::IFile*>(sender()))
	{
		outPane->clearContents(file->fileName());
		readFile(file->fileName());
	}
}

QRegExp TagPlugin::generatePattern(const TagKeyword& tag) {
	return QRegExp("//\\s*" + tag.name + "(:|\\s)", Qt::CaseInsensitive);
}

TagKeyword TagPlugin::findMatchingTag(const QString& line)
{
	foreach(const TagKeyword& tag, tags)
		if(line.contains(generatePattern(tag)))
			return tag;
	return TagKeyword();
}

void TagPlugin::formatLine(QString& line, const TagKeyword& tag)
{
	line.replace("\n", "");
	line.replace("\r", "");
	line.replace(generatePattern(tag), tag.name + ": ");
	line = line.trimmed();
	line = QTextCodec::codecForLocale()->toUnicode(line.toAscii());
}

void TagPlugin::readFile(const QString& filePath)
{
	QFile file(filePath);
	if(!file.open(QFile::ReadOnly | QFile::Text))
		return;

	for(int lineNumber = 1; !file.atEnd(); ++lineNumber)
	{
		QString line = file.readLine();
		TagKeyword tag = findMatchingTag(line);
		if(tag.isValid())
		{
			formatLine(line, tag);
			outPane->addItem(line, filePath, lineNumber, tag);
			communicator->sendTaggingEvent(line, filePath, lineNumber);
			if(!reading)
				outPane->sort();
		}
	}
}

void TagPlugin::onProjectChanged(ProjectExplorer::Project* project)
{
	if(project == 0 || reading)
		return;

	currentProject = project;
	outPane->clearContents();

	reading = true;
	QFuture<void> result = QtConcurrent::run(&TagPlugin::readCurrentProject, this);
	Core::ICore::instance()->progressManager()->addTask(result, tr("TodoScan"), "Todo.Plugin.Scanning");
}

void TagPlugin::onRemoteTaggingEvent(const TaggingEvent& event)
{
	TagKeyword tag = findMatchingTag(event.tag);
	outPane->addItem(event.tag, event.fileName, event.lineNumber, tag);
}

void TagPlugin::readCurrentProject(QFutureInterface<void>& future, TagPlugin* instance)
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

}  // namespace TeamRadar

Q_EXPORT_PLUGIN(TeamRadar::TagPlugin)


