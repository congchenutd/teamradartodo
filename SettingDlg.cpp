#include "SettingDlg.h"
#include "TagDlg.h"
#include "TodoSetting.h"

namespace TeamRadarTag {

SettingDlg::SettingDlg(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btAdd,   SIGNAL(clicked()), this, SLOT(onAdd()));
	connect(ui.btDel,   SIGNAL(clicked()), this, SLOT(onDel()));
	connect(ui.btReset, SIGNAL(clicked()), this, SLOT(onReset()));
	setTags(Setting::getInstance()->getTags());
}

void SettingDlg::addTag(const Tag& keyword)
{
	QListWidgetItem* item = new QListWidgetItem(keyword.icon, keyword.name);
	item->setBackgroundColor(keyword.bgColor);
	ui.listWidgetTags->addItem(item);
}

void SettingDlg::setTags(const TagList& tagList)
{
	if(tagList.isEmpty())
	{
		onReset();
		return;
	}

	foreach(const Tag& tag, tagList)
		addTag(tag);
}

TagList SettingDlg::getTags()
{
	TagList result;
	for(int i = 0; i < ui.listWidgetTags->count(); ++i)
		result.append(Tag(ui.listWidgetTags->item(i)->text(),
						  ui.listWidgetTags->item(i)->icon(),
						  ui.listWidgetTags->item(i)->backgroundColor()));
	return result;
}

void SettingDlg::onAdd()
{
	TagDlg dlg(this);
	if(dlg.exec() == QDialog::Accepted)
	{
		addTag(Tag(dlg.getName(),
				   dlg.getIcon(),
				   dlg.getColor()));
		emit settingChanged();
	}
}

void SettingDlg::onDel()
{
	ui.listWidgetTags->takeItem(ui.listWidgetTags->currentRow());
	emit settingChanged();
}

void SettingDlg::onReset()
{
	ui.listWidgetTags->clear();                         // clear the list
	setTags(Setting::getInstance()->getDefaultTags());  // add default tags
	emit settingChanged();
}

}  // namespace TeamRadarTag
