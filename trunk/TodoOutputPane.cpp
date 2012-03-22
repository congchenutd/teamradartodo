#include "TodoOutputPane.h"
#include <QListWidgetItem>
#include <QFileInfo>

TodoOutputPane::TodoOutputPane(QObject *parent) : IOutputPane(parent)
{
	todoList = new QListWidget;
    todoList->setFlow(QListView::TopToBottom);
    todoList->setFrameStyle(QFrame::NoFrame);
    lastCurrentRow = 0;
}

TodoOutputPane::~TodoOutputPane() {
    delete todoList;
}

void TodoOutputPane::addItem(const QString& text, const QString& filePath, int row,
							 const QIcon& icon, const QColor& color)
{
	QListWidgetItem* item = new QListWidgetItem;
	item->setIcon(icon);
	item->setBackgroundColor(color);
	item->setData(FilePathRole, filePath);
	item->setData(LineNumberRole, row);
	item->setToolTip(filePath + ":" + QString::number(row));
	item->setText(QFileInfo(filePath).fileName() + ":" + QString::number(row) + ": " + text);
	todoList->addItem(item);
}

void TodoOutputPane::clearContents() {
    todoList->clear();
}

void TodoOutputPane::clearContents(const QString& filename)
{
	int i = 0;
	lastCurrentRow = 0;
	while(i < todoList->count())
	{
		if(!filename.compare(todoList->item(i)->data(FilePathRole).toString()))
		{
			if(lastCurrentRow == 0)
				lastCurrentRow = todoList->currentRow();
			todoList->takeItem(i);   // remove row
		}
		else {
			i ++;
		}
	}
}

void TodoOutputPane::visibilityChanged(bool visible) {
    todoList->setVisible(visible);
}

void TodoOutputPane::setFocus() {
    todoList->setFocus();
}

bool TodoOutputPane::hasFocus() const {
    return todoList->hasFocus();
}

bool TodoOutputPane::canNavigate() const {
    return todoList->count() > 1;
}

bool TodoOutputPane::canNext() const {
    return todoList->currentRow() < todoList->count() && todoList->count() > 1;
}

bool TodoOutputPane::canPrevious() const {
    return todoList->currentRow() > 0 && todoList->count() > 1;
}

void TodoOutputPane::goToNext() {
    todoList->setCurrentRow(todoList->currentRow() + 1);
}

void TodoOutputPane::goToPrev() {
    todoList->setCurrentRow(todoList->currentRow() - 1);
}

void TodoOutputPane::sort()
{
    todoList->sortItems(Qt::AscendingOrder);
//    if (todoList->count() > 0)
//        todoList->setCurrentRow(lastCurrentRow < todoList->count() ? lastCurrentRow : todoList->count() - 1);
}
