#include "SettingPage.h"
#include "Setting.h"
#include <coreplugin/icore.h>
#include <QList>
#include <QMessageBox>
#include <QLabel>

QWidget* SettingPage::createPage(QWidget* parent)
{
	settingDirty = false;

	dialog = new SettingDlg(parent);
	connect(dialog, SIGNAL(settingChanged()), this, SLOT(onSettingChanged()));
	return dialog;
}

void SettingPage::apply()
{
	if(settingDirty)
	{
		Setting::getInstance()->setTags(dialog->getTags());

		QMessageBox::information(dialog, tr("Information"),
								 tr("The TODO plugin settings change will take effect after a restart of Qt Creator."));
		settingDirty = false;
	}
}

void SettingPage::onSettingChanged() {
	settingDirty = true;
}

//////////////////////////////////////////////////////////////
AboutPage::AboutPage(QObject* parent) : SettingPage(parent) {}

QWidget* AboutPage::createPage(QWidget* parent)
{
	QWidget* widget = new QWidget(parent);
	QLabel* label = new QLabel(tr(
		"<H1 align=\"center\">Todo</H1>"
		"<P align=\"center\">Capturing high-leve awareness with tags</P>"
		"<P align=\"center\">Cong Chen &lt;CongChenUTD@Gmail.com&gt;</P>"
		"<P align=\"center\">Built on %1</P>")
							   .arg(Setting::getInstance()->getCompileDate()), widget);
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->addWidget(label);
	return widget;
}