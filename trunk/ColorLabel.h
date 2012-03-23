#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QColor>

namespace TeamRadar {

// A label for choosing color
// click to open a color dialog
class ColorLabel : public QLabel
{
	Q_OBJECT
public:
	ColorLabel(QWidget* parent = 0);
	QColor getColor() const { return color; }
	void   setColor(const QColor& clr);

protected:
	void mousePressEvent(QMouseEvent*);

signals:
	void valueChanged();

private:
	QColor color;
};

} // namespace TeamRadar

#endif // COLORLABEL_H
