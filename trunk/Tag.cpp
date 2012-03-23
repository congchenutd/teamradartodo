#include "Tag.h"

QDataStream& operator<<(QDataStream& os, const Tag& tag)
{
	os << tag.name;
	os << tag.icon;
	os << tag.bgColor;
	return os;
}

QDataStream& operator>>(QDataStream& is,  Tag& tag)
{
	is >> tag.name;
	is >> tag.icon;
	is >> tag.bgColor;
	return is;
}
