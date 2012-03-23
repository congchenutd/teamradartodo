#include "TagSetting.h"
#include <QResource>

namespace TeamRadar {

TagSetting::TagSetting(const QString& fileName) : MySetting<TagSetting>(fileName)
{
	if(QFile(this->fileName).size() == 0)   // no setting
		loadDefaults();
}

void TagSetting::setTags(const TagKeywords& tags) {
	setValue("Tags", qVariantFromValue(tags));
}

TagKeywords TagSetting::getTags() const {
	return value("Tags").value<TagKeywords>();
}

TagKeywords TagSetting::getDefaultTags() const
{
	TagKeywords result;
	result << TagKeyword("NOTE",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	result << TagKeyword("INFO",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	result << TagKeyword("TODO",     QIcon(":/Images/Todo"),        QColor("#BFFFC8"));
	result << TagKeyword("WARNING",  QIcon(":/Images/Warning"),     QColor("#FFFFAA"));
	result << TagKeyword("FIXME",    QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	result << TagKeyword("BUG",      QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	result << TagKeyword("Critical", QIcon(":/Images/Critical"),    QColor("#FFBFBF"));
	return result;
}

void TagSetting::loadDefaults() {
	setTags(getDefaultTags());
}

QString TagSetting::getCompileDate() const
{
	// this resource file will be generated after running CompileDate.bat
	QResource resource(":/CompileDate.txt");
	QString result = (char*)resource.data();
	return result.isEmpty() ? "Unknown" : result;
}

}  // namespace TeamRadar
