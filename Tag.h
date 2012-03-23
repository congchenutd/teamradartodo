#ifndef TAG_H
#define TAG_H

#include <QIcon>
#include <QColor>
#include <QString>
#include <QList>
#include <QMetaType>

namespace TeamRadarTag {

class Tag
{
public:
	Tag() {}
	Tag(QString n, QIcon i, QColor c) : name(n), icon(i), bgColor(c) {}
	bool isValid() const { return !name.isEmpty(); }

	QString name;
	QIcon   icon;
	QColor  bgColor;
};

typedef QList<Tag> TagList;

QDataStream& operator<<(QDataStream& out, const Tag& tag);
QDataStream& operator>>(QDataStream& in,  Tag& tag);

Q_DECLARE_METATYPE(TagList)
Q_DECLARE_METATYPE(Tag)

}  // namespace TeamRadarTag

#endif // TAG_H
