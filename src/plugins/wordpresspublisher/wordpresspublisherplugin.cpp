#include "wordpresspublisherplugin.h"

WordPressPublisherPlugin::WordPressPublisherPlugin(QObject *parent) : QObject(parent)
{

}

WordPressPublisherPlugin::~WordPressPublisherPlugin()
{

}

QString WordPressPublisherPlugin::name() const
{
    return QStringLiteral("WordPressPublisher");
}

QString WordPressPublisherPlugin::version() const
{
    return QStringLiteral("1.0.0");
}

QString WordPressPublisherPlugin::vendor() const
{
    return QStringLiteral("galaxyworld.org");
}

QString WordPressPublisherPlugin::targetName() const
{
    return QStringLiteral("WordPress");
}

QString WordPressPublisherPlugin::targetVersion() const
{
    return QStringLiteral("4.5");
}
