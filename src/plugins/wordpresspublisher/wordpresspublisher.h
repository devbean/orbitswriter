#ifndef WORDPRESSPUBLISHER_H
#define WORDPRESSPUBLISHER_H

#include <Core/Publisher>
#include <QObject>

class WordPressPublisher : public Core::Publisher
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Publisher_iid FILE "wordpresspublisher.json")
    Q_INTERFACES(Core::Publisher)
public:
    explicit WordPressPublisher();
    virtual ~WordPressPublisher();

    virtual QString name() const;
    virtual QString version() const;
    virtual QString vendor() const;

    virtual QString targetName() const;
    virtual QString targetVersion() const;
};

#endif // WORDPRESSPUBLISHER_H
