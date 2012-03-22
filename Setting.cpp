#include "Setting.h"

Setting::Setting(const QString& fileName) : MySetting<Setting>(fileName)
{
	if(QFile(this->fileName).size() == 0)   // no setting
		loadDefaults();
}

void Setting::setKeywords(const KeywordList& keywords) {
	setValue("keywords", qVariantFromValue(keywords));
}

KeywordList Setting::getKeywords() const {
	return value("keywords").value<KeywordList>();
}

void Setting::loadDefaults()
{
	KeywordList defaultKeywords;
	defaultKeywords << Keyword("NOTE",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	defaultKeywords << Keyword("INFO",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	defaultKeywords << Keyword("TODO",     QIcon(":/Images/Todo"),        QColor("#BFFFC8"));
	defaultKeywords << Keyword("WARNING",  QIcon(":/Images/Warning"),     QColor("#FFFFAA"));
	defaultKeywords << Keyword("FIXME",    QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	defaultKeywords << Keyword("BUG",      QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	defaultKeywords << Keyword("Critical", QIcon(":/Images/Critical"),    QColor("#FFBFBF"));
	setKeywords(defaultKeywords);
}
