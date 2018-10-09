#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>

class chat : public QObject
{
    Q_OBJECT
public:
    explicit chat(QObject *parent = nullptr);
    void setWelcomeMsgApplicationName(QString msg);
    void setCommands(QStringList msg);
    void setLineSeparator(QString newSeparator);
    QString replyTo(QString request);
    
    QString welcomeMsg;
    
signals:
    
public slots:
    
private:
    QString lineSeparator = "\n";

    QMap<QString,QString> commands;
    QMap<QString,QString> replies;
};

#endif // CHAT_H
