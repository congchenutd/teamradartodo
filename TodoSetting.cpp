#include "TodoSetting.h"
#include <QResource>

namespace TeamRadarTag {

Setting::Setting(const QString& fileName) : MySetting<Setting>(fileName)
{
	if(QFile(this->fileName).size() == 0)   // no setting
		loadDefaults();
}

void Setting::setTags(const TagList& tags) {
	setValue("Tags", qVariantFromValue(tags));
}

TagList Setting::getTags() const {
	return value("Tags").value<TagList>();
}

TagList Setting::getDefaultTags() const
{
	TagList result;
	result << Tag("NOTE",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	result << Tag("INFO",     QIcon(":/Images/Information"), QColor("#E2DFFF"));
	result << Tag("TODO",     QIcon(":/Images/Todo"),        QColor("#BFFFC8"));
	result << Tag("WARNING",  QIcon(":/Images/Warning"),     QColor("#FFFFAA"));
	result << Tag("FIXME",    QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	result << Tag("BUG",      QIcon(":/Images/Bug"),         QColor("#FFDFDF"));
	result << Tag("Critical", QIcon(":/Images/Critical"),    QColor("#FFBFBF"));
	return result;
}

void Setting::loadDefaults() {
	setTags(getDefaultTags());
}

QString Setting::getCompileDate() const
{
	// this resource file will be generated after running CompileDate.bat
	QResource resource(":/CompileDate.txt");
	QString result = (char*)resource.data();
	return result.isEmpty() ? "Unknown" : result;
}

}  // namespace TeamRadarTag
