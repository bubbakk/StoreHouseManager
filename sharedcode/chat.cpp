#include "chat.h"

chat::chat(QObject *parent) : QObject(parent)
{
    // setting commands
    this->commands.insert("HELLOCOMMAND",     "HELLO");
    this->commands.insert("HELLOCOMMAND_",    "HELO");
    this->commands.insert("HELPCOMMAND",      "HELP");
    this->commands.insert("STARTMSGCOMMAND",  "SHM_MSG_STA");
    this->commands.insert("ENDMSGCOMMAND",    "SHM_MSG_STO");
    this->commands.insert("QUITCOMMAND",      "QUIT");
    this->commands.insert("QUITCOMMAND_",     "BYE");
    
    // setting commands
    this->replies.insert("HELLO",       "Hello");
    this->replies.insert("HELO",        "Hello");
    this->replies.insert("HELP",        "custom");
    this->replies.insert("SHM_MSG_STA", "Tell me...");
    this->replies.insert("SHM_MSG_STO", "ok.");
    this->replies.insert("QUIT",        "Bye");
    this->replies.insert("BYE",         "Bye");
}

void chat::setWelcomeMsgApplicationName(QString msg)
{
    this->welcomeMsg = "Connected to " + msg + this->lineSeparator;
}

void chat::setLineSeparator(QString newSeparator)
{
    this->lineSeparator = newSeparator;
}

QString chat::replyTo(QString request)
{
    // custom reply
    // HELP
    if ( request.compare(commands["HELPCOMMAND"], Qt::CaseInsensitive) )
    {
        QStringList reply = {this->lineSeparator, "Available commands:"};
        for ( int i = 0 ; i < this->commands.count() ; i++ ) {
            foreach(QString key, this->commands.keys())
            {
                if ( !key.endsWith("_") )
                {
                    reply.append(this->commands[key]);
                }
            }
        }
        reply.append("All commands are case sentitive but " + this->commands[0]);
        
        return reply.join(this->lineSeparator);
    }
    
    // verifica che il comando sia in lista
    this->replies.values();
    return this->replies[request];
}
