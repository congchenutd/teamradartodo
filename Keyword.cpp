#include "Keyword.h"

QDataStream& operator<<(QDataStream& os, const Keyword& keyword)
{
	os << keyword.name;
	os << keyword.icon;
	os << keyword.warningColor;
	return os;
}

QDataStream& operator>>(QDataStream& is,  Keyword& keyword)
{
	is >> keyword.name;
	is >> keyword.icon;
	is >> keyword.warningColor;
	return is;
}
