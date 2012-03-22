#ifndef KEYWORD_H
#define KEYWORD_H

#include <QIcon>
#include <QColor>
#include <QString>
#include <QList>
#include <QMetaType>

class Keyword
{
public:
	Keyword() {}
	Keyword(QString n, QIcon i, QColor c) : name(n), icon(i), warningColor(c) {}
	bool isValid() const { return !name.isEmpty(); }

    QString name;
	QIcon   icon;
	QColor  warningColor;
};

typedef QList<Keyword> KeywordList;

QDataStream& operator<<(QDataStream& out, const Keyword& keyword);
QDataStream& operator>>(QDataStream& in,  Keyword& keyword);

Q_DECLARE_METATYPE(KeywordList)
Q_DECLARE_METATYPE(Keyword)

#endif // KEYWORD_H
