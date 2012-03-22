#ifndef SETTING_H
#define SETTING_H

#include "MySetting.h"
#include "Keyword.h"

class Setting : public MySetting<Setting>
{
public:
	Setting(const QString& fileName);
	void setKeywords(const KeywordList& keywords);
	KeywordList getKeywords() const;

private:
	void loadDefaults();
};

#endif // SETTING_H
