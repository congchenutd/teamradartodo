#ifndef SETTING_H
#define SETTING_H

#include "MySetting.h"
#include "Tag.h"

class Setting : public MySetting<Setting>
{
public:
	Setting(const QString& fileName);
	void setTags(const TagList& tags);
	TagList getTags() const;
	TagList getDefaultTags() const;
	QString getCompileDate() const;

private:
	void loadDefaults();
};

#endif // SETTING_H
