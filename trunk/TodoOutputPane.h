#ifndef TODOOUTPUTPANE_H
#define TODOOUTPUTPANE_H

#include "keyword.h"
#include <coreplugin/ioutputpane.h>
#include <QListWidget>

class TodoOutputPane : public Core::IOutputPane
{
public:
    TodoOutputPane(QObject *parent);
    ~TodoOutputPane();

	virtual QWidget *outputWidget(QWidget*) { return todoList; }
	virtual QList<QWidget*> toolBarWidgets() const { return QList<QWidget*>(); }
	virtual QString displayName() const { return "TODO"; }
	virtual int priorityInStatusBar() const { return 1; }

	virtual void clearContents();
	virtual void clearContents(const QString& filename);
	virtual void visibilityChanged(bool visible);

	virtual void setFocus();
	virtual bool hasFocus() const;
	virtual bool canFocus() const { return true; }

	virtual bool canNavigate() const;
	virtual bool canNext()     const;
	virtual bool canPrevious() const;
	virtual void goToNext();
	virtual void goToPrev();

    void sort();
	void addItem(const QString& text, const QString& filePath, int row,
				 const QIcon& icon, const QColor& color);
	QListWidget* getTodoList() const { return todoList; }

public:
	enum {FilePathRole = Qt::UserRole + 1, LineNumberRole};

private:
	QListWidget* todoList;
    int lastCurrentRow;
};

#endif // TODOOUTPUTPANE_H
