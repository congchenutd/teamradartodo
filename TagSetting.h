#ifndef SETTING_H
#define SETTING_H

#include "MySetting.h"
#include "TagKeyword.h"

namespace TeamRadar {

class TagSetting: public MySetting<TagSetting>
{
public:
	TagSetting(const QString& fileName);
	void setTags(const TagKeywords& tags);
	TagKeywords getTags() const;
	TagKeywords getDefaultTags() const;
	QString getCompileDate() const;

private:
	void loadDefaults();
};

}  // namespace TeamRadar

#endif // SETTING_H
