#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QIcon>
#include <coreplugin/dialogs/ioptionspage.h>
#include "SettingDlg.h"

class SettingPage: public Core::IOptionsPage
{
    Q_OBJECT
public:

	SettingPage(QObject* parent = 0) : IOptionsPage(parent) {}

	virtual QString id()              const { return "TodoSetting"; }
	virtual QString category()        const { return "TODO"; }
	virtual QString displayName()     const { return "TODO"; }
	virtual QString displayCategory() const { return "TODO"; }
	virtual QIcon   categoryIcon()    const { return QIcon(":/Images/Tag"); }
	virtual QWidget* createPage(QWidget *parent);
	virtual void apply();
	virtual void finish() {}

public slots:
	void onSettingChanged();

private:
	SettingDlg* dialog;
	bool        settingDirty;
};

class AboutPage : public SettingPage
{
public:
	AboutPage(QObject* parent = 0);

	QString  id() const { return tr("About"); }
	QString  displayName() const { return tr("About"); }
	QWidget* createPage(QWidget* parent);
	void apply() {}
};

#endif // SETTINGPAGE_H
