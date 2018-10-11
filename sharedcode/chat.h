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
    QMap<QString,QString> _commands;

    explicit chat(QObject *parent = nullptr);
    void setWelcomeMsgApplicationName(QString msg);
    void setCommands(QStringList msg);
    void setLineSeparator(QString newSeparator);
    QString replyTo(QString request);
    
    QString welcomeMsg;
    
    QMap<QString, QString> getCommands() const;

signals:
    
public slots:
    
private:
    QString _lineSeparator = "\n";
    QMap<QString,QString> replies;
};

#endif // CHAT_H
