#ifndef KEYWORDDLG_H
#define KEYWORDDLG_H

#include <QDialog>
#include "ui_KeywordDlg.h"

class KeywordDlg : public QDialog
{
    Q_OBJECT

public:
	KeywordDlg(QWidget *parent = 0);
	QString getName();
	QColor  getColor();
	QIcon   getIcon();
	void    setName (const QString& name);
	void    setColor(const QColor&  color);
	void    setIcon (const QString& iconType);

private:
	Ui::KeywordDlgClass ui;
};

#endif // KEYWORDDLG_H
