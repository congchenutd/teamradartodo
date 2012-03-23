#include "TodoOutputPane.h"
#include <QListWidget>
#include <QFileInfo>

TodoOutputPane::TodoOutputPane(QObject* parent) : IOutputPane(parent) {
	todoList = new QListWidget;
}

TodoOutputPane::~TodoOutputPane() {
	delete todoList;
}

void TodoOutputPane::addItem(const QString& text, const QString& filePath, int row, const Tag& tag)
{
	QListWidgetItem* item = new QListWidgetItem;
	item->setIcon(tag.icon);
	item->setBackgroundColor(tag.bgColor);
	item->setData(FilePathRole,   filePath);   // hide meta data here
	item->setData(LineNumberRole, row);
	item->setToolTip(filePath + ":" + QString::number(row));
	item->setText(text + " (" + QFileInfo(filePath).fileName() + ":" + QString::number(row) + ") ");
	todoList->addItem(item);
}

// clear all
void TodoOutputPane::clearContents() {
	todoList->clear();
}

// only clear items from the file
void TodoOutputPane::clearContents(const QString& filePath)
{
	for(int i = 0; i < todoList->count();)
	{
		QString storedPath = todoList->item(i)->data(FilePathRole).toString();
		if(filePath.compare(storedPath, Qt::CaseInsensitive) == 0)
			todoList->takeItem(i);   // remove row
		else
			i ++;
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

void TodoOutputPane::sort() {
	todoList->sortItems(Qt::AscendingOrder);
}
