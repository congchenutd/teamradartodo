#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include "TeamRadarEvent.h"

namespace TeamRadarTag {

class Tag;

class Communicator : public QObject
{
	Q_OBJECT
public:
	Communicator(QObject* parent = 0);
	void sendTaggingEvent(const QString& text, const QString& filePath, int row);

signals:
	void remoteTagging();

private slots:
	void onTaggingEvent(const TeamRadar::TeamRadarEvent& event);

};

}  // namespace TeamRadarTag

#endif // COMMUNICATOR_H
