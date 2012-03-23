#ifndef TODOOUTPUTPANE_H
#define TODOOUTPUTPANE_H

#include "Tag.h"
#include <coreplugin/ioutputpane.h>
#include <QListWidget>

namespace TeamRadarTag {

class TodoOutputPane : public Core::IOutputPane
{
public:
	TodoOutputPane(QObject* parent);
	~TodoOutputPane();

	virtual QWidget* outputWidget(QWidget*) { return todoList; }
	virtual QList<QWidget*> toolBarWidgets() const { return QList<QWidget*>(); }
	virtual QString displayName() const { return "TODO"; }
	virtual int priorityInStatusBar() const { return 1; }
	virtual void clearContents();                           // clear all
	virtual void clearContents(const QString& filePath);    // clear tags from the file
	virtual void visibilityChanged(bool visible);
	virtual void setFocus();
	virtual bool hasFocus()    const;
	virtual bool canFocus()    const { return true; }
	virtual bool canNavigate() const;
	virtual bool canNext()     const;
	virtual bool canPrevious() const;
	virtual void goToNext();
	virtual void goToPrev();

	void sort();
	void addItem(const QString& text, const QString& filePath, int row, const Tag& tag);
	QListWidget* getTodoList() const { return todoList; }

public:
	enum {FilePathRole = Qt::UserRole + 1, LineNumberRole};

private:
	QListWidget* todoList;
};

}  // namespace TeamRadarTag

#endif // TODOOUTPUTPANE_H
