#include "SettingDlg.h"
#include "KeywordDlg.h"
#include "Setting.h"

SettingDlg::SettingDlg(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btAdd,   SIGNAL(clicked()), this, SLOT(onAdd()));
	connect(ui.btDel,   SIGNAL(clicked()), this, SLOT(onDel()));
	connect(ui.btReset, SIGNAL(clicked()), this, SLOT(onReset()));
	setKeywordsList(Setting::getInstance()->getKeywords());
}

void SettingDlg::addKeyword(const Keyword& keyword)
{
	QListWidgetItem* item = new QListWidgetItem(keyword.icon, keyword.name);
    item->setBackgroundColor(keyword.warningColor);
	ui.keywords->addItem(item);
}

void SettingDlg::setKeywordsList(const KeywordList& list)
{
	if(list.isEmpty()) {
		onReset();
    }
	else {
		for(int i = 0; i < list.count(); ++i)
			addKeyword(list.at(i));
    }
}

KeywordList SettingDlg::getKeywords()
{
	KeywordList result;
	for (int i = 0; i < ui.keywords->count(); ++i)
		result.append(Keyword(ui.keywords->item(i)->text(),
							  ui.keywords->item(i)->icon(),
							  ui.keywords->item(i)->backgroundColor()));
	return result;
}

void SettingDlg::onAdd()
{
	KeywordDlg dlg(this);
	if(dlg.exec() == QDialog::Accepted)
    {
		addKeyword(Keyword(dlg.getName(),
						   dlg.getIcon(),
						   dlg.getColor()));
		emit settingChanged();
    }
}

void SettingDlg::onDel()
{
	ui.keywords->takeItem(ui.keywords->currentRow());
	emit settingChanged();
}

void SettingDlg::onReset()
{
	ui.keywords->clear();
	addKeyword(Keyword("NOTE",     QIcon(":/Images/Information"), QColor("#E2DFFF")));
	addKeyword(Keyword("INFO",     QIcon(":/Images/Information"), QColor("#E2DFFF")));
	addKeyword(Keyword("TODO",     QIcon(":/Images/Todo"),        QColor("#BFFFC8")));
	addKeyword(Keyword("WARNING",  QIcon(":/Images/Warning"),     QColor("#FFFFAA")));
	addKeyword(Keyword("FIXME",    QIcon(":/Images/Bug"),         QColor("#FFDFDF")));
	addKeyword(Keyword("BUG",      QIcon(":/Images/Bug"),         QColor("#FFDFDF")));
	addKeyword(Keyword("Critical", QIcon(":/Images/Critical"),    QColor("#FFBFBF")));

	emit settingChanged();
}
