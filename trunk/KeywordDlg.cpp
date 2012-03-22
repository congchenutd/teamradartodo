#include "KeywordDlg.h"
#include <QColorDialog>

KeywordDlg::KeywordDlg(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
}

QString KeywordDlg::getName() {
	return ui.leKeyword->text();
}

QColor KeywordDlg::getColor() {
	return ui.labelColor->getColor();
}

QIcon KeywordDlg::getIcon() {
	return ui.listWidget->currentItem()->icon();
}

void KeywordDlg::setName(const QString& name){
	ui.leKeyword->setText(name);
}

void KeywordDlg::setColor(const QColor& color) {
	ui.labelColor->setColor(color);
}

void KeywordDlg::setIcon(const QString& iconType)
{
	static QStringList iconTypes(
				QStringList() << "information" << "warning" << "error" << "todo");
	ui.listWidget->setCurrentRow(iconTypes.indexOf(iconType.toLower()));
}
