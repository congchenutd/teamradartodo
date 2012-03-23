#include "ColorLabel.h"
#include <QColorDialog>

ColorLabel::ColorLabel(QWidget* parent) : QLabel(parent) {}

void ColorLabel::setColor(const QColor& clr)
{
	if(clr.isValid())
	{
		color = clr;
		QPixmap pixmap(size());
		pixmap.fill(color);
		setPixmap(pixmap);
		emit valueChanged();
	}
}

void ColorLabel::mousePressEvent(QMouseEvent* event)
{
	setColor(QColorDialog::getColor(color));   // open a color dialog
	QLabel::mousePressEvent(event);
}