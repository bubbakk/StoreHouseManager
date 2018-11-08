#include "chat.h"

chat::chat(QObject *parent) : QObject(parent)
{
    // setting commands
    this->_commands.insert("HELLOCOMMAND",     "HELLO");
    this->_commands.insert("HELLOCOMMAND_",    "HELO");
    this->_commands.insert("HELPCOMMAND",      "HELP");
    this->_commands.insert("STARTMSGCOMMAND",  "SHM_MSG_STA");
    this->_commands.insert("ENDMSGCOMMAND",    "SHM_MSG_STO");
    this->_commands.insert("PRINTALL",         "PRINTALL");
    this->_commands.insert("QUITCOMMAND",      "QUIT");
    this->_commands.insert("QUITCOMMAND_",     "BYE");

    /*
         this->_commands.insert("HELLO",       "HELLOCOMMAND");
         this->_commands.insert("HELP",        "HELPCOMMAND");
         this->_commands.insert("SHM_MSG_STA", "STARTMSGCOMMAND");
         this->_commands.insert("SHM_MSG_STO", "ENDMSGCOMMAND");
         this->_commands.insert("QUIT",        "QUITCOMMAND");
         this->_commands.insert("BYE",         "BYECOMMAND");
    */

    // setting commands
    this->replies.insert("HELLO",       "Hello");
    this->replies.insert("HELO",        "Hello");
    this->replies.insert("HELP",        "custom");
    this->replies.insert("SHM_MSG_STA", "Tell me...");
    this->replies.insert("SHM_MSG_STO", "ok.");
    this->replies.insert("PRINTALL",    "data printed in the server logfile");
    this->replies.insert("QUIT",        "Bye");
    this->replies.insert("BYE",         "Bye");
}

void chat::setWelcomeMsgApplicationName(QString msg)
{
    this->welcomeMsg = "Connected to " + msg + this->_lineSeparator;
}

void chat::setLineSeparator(QString newSeparator)
{
    this->_lineSeparator = newSeparator;
}

QString chat::replyTo(QString request)
{
    // custom reply
    // HELP
    if ( request.compare(this->_commands["HELPCOMMAND"], Qt::CaseInsensitive) == 0 )
    {
        QStringList reply = {"Available commands:"};

        foreach(QString key, this->_commands.keys())
        {
            if ( !key.endsWith("_") )
            {
                reply.append(" * " + this->_commands[key]);
            }
        }

        reply.append("All commands are case sentitive but " + this->_commands["HELPCOMMAND"] + this->_lineSeparator + this->_lineSeparator);

        return reply.join(this->_lineSeparator);
    }

    // ritorna la risposta se c'è, oppure stringa vuota
    return (this->replies.keys().indexOf(request) == -1 ? "" : this->replies[request]);
}

QMap<QString, QString> chat::getCommands() const
{
    return _commands;
}
