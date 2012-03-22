#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QWidget>
#include "keyword.h"
#include "ui_SettingDlg.h"

class SettingDlg : public QWidget
{
    Q_OBJECT

public:
	SettingDlg(QWidget* parent = 0);

	KeywordList getKeywords();
	void setKeywordsList(const KeywordList& list);

private:
	void addKeyword(const Keyword& keyword);

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
