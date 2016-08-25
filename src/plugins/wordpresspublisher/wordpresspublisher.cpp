#include "wordpresspublisher.h"

WordPressPublisher::WordPressPublisher()
{

}

WordPressPublisher::~WordPressPublisher()
{

}

QString WordPressPublisher::name() const
{
    return QStringLiteral("WordPressPublisher");
}

QString WordPressPublisher::version() const
{
    return QStringLiteral("1.0.0");
}

QString WordPressPublisher::vendor() const
{
    return QStringLiteral("galaxyworld.org");
}

QString WordPressPublisher::targetName() const
{
    return QStringLiteral("WordPress");
}

QString WordPressPublisher::targetVersion() const
{
    return QStringLiteral("4.5");
}
