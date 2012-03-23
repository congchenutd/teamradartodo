#include "Communicator.h"
#include "Connection.h"

namespace TeamRadarTag {

Communicator::Communicator(QObject* parent) : QObject(parent)
{
	TeamRadar::Setting* teamRadarSetting = TeamRadar::Setting::getInstance();
	TeamRadar::Connection* connection = TeamRadar::Connection::getInstance();
	connection->setUserName(teamRadarSetting->getUserName());
	connection->connectToHost(teamRadarSetting->getServerAddress(), teamRadarSetting->getServerPort());

	connect(TeamRadar::Receiver::getInstance(), SIGNAL(newEvent(TeamRadarEvent)),
			this, SLOT(onTaggingEvent(TeamRadarEvent)));
}

void Communicator::sendTaggingEvent(const QString& text, const QString& filePath, int row)
{
	TeamRadar::Sender::getInstance()->sendEvent("TAGGING", text + ": " + filePath + ": " + QString::number(row));
}

void Communicator::onTaggingEvent(const TeamRadar::TeamRadarEvent& event)
{
	if(event.eventType == "TAGGING")
		emit remoteTagging(event.userName, event.parameters);
}

}  // namespace TeamRadarTag
