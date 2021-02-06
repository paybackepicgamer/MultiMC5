#include "AuthSession.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStringList>

QString AuthSession::serializeUserProperties()
{
    QJsonObject userAttrs;
    for (auto key : u.properties.keys())
    {
        auto array = QJsonArray::fromStringList(u.properties.values(key));
        userAttrs.insert(key, array);
    }
    QJsonDocument value(userAttrs);
    return value.toJson(QJsonDocument::Compact);

}

bool AuthSession::MakeOffline(QString offline_playername)
{
    if (status != PlayableOffline && status != PlayableOnline)
    {
        return false;
    }
    session = "-";
    client_token = "ff64ff64ff64ff64ff64ff64ff64ff64";
    access_token = "ff64ff64ff64ff64ff64ff64ff64ff64";
    uuid = QString(QCryptographicHash::hash(offline_playername.toLocal8Bit(), QCryptographicHash::Md5).toHex());
    
    player_name = offline_playername;
    status = PlayableOffline;
    return true;
}
