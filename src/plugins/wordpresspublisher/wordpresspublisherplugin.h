#ifndef WORDPRESSPUBLISHERPLUGIN_H
#define WORDPRESSPUBLISHERPLUGIN_H

#include <Core/Publisher>
#include <QObject>

class WordPressPublisherPlugin : public QObject, Core::Publisher
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Publisher_iid FILE "wordpresspublisher.json")
    Q_INTERFACES(Core::Publisher)
public:
    explicit WordPressPublisherPlugin(QObject *parent = 0);
    virtual ~WordPressPublisherPlugin();

    virtual QString name() const;
    virtual QString version() const;
    virtual QString vendor() const;

    virtual QString targetName() const;
    virtual QString targetVersion() const;
};

#endif // WORDPRESSPUBLISHERPLUGIN_H
