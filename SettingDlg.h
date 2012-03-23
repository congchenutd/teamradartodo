#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QWidget>
#include "Tag.h"
#include "ui_SettingDlg.h"

class SettingDlg : public QWidget
{
	Q_OBJECT

public:
	SettingDlg(QWidget* parent = 0);

	TagList getTags();
	void setTags(const TagList& list);

private:
	void addTag(const Tag& keyword);

signals:
	void settingChanged();

private slots:
	void onAdd();
	void onDel();
	void onReset();

private:
	Ui::SettingDlgClass ui;
};

#endif // SETTINGDLG_H
