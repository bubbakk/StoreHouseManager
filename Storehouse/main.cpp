#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QFileInfo>
#include <QFile>
#include <QVariantList>

#include "../sharedcode/shmrequestparser.h"
#include "../sharedcode/tcpServer.h"
#include "../sharedcode/messagehandler.h"
#include "../sharedcode/tcpchat.h"
#include "../sharedcode/webserver.h"

#include "warehouse.h"
#include "warehousemajordomo.h"

#define TCP_port  12000
#define HTTP_port 12001

void print_usage(char* appname)
{
    QTextStream qout(stdout);
    QFileInfo fi(appname);

    qout << fi.fileName() << " usage:" << endl;
    qout << endl;
    qout << "  -d           [daemon mode]     accepts TCP requests on port " << TCP_port << endl;
    qout << "  -f filename  [file mode]       accepts requests from a file" << endl;
    qout << "  -r request   [request mode]    accepts a request string" << endl;

    qout << endl;
}

int main(int argc, char *argv[])
{
    QTextStream qout(stdout);

    shmRequestParser *requestsParser;
    warehouseMajordomo* majordomo = new warehouseMajordomo();;
    wareHouse *warehouse = new wareHouse(10,10);

    majordomo->setWareHouse(warehouse);

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("SHM Suite - storehouse");
    QCoreApplication::setApplicationVersion("0.2.0");

    // print application info into terminal
    qout << endl << QCoreApplication::applicationName() << " (c) 2018" << endl;
    qout << "Version " << QCoreApplication::applicationVersion() << endl;
    qout << "Design and development: Andrea Ferroni <andrea.ferroni.76@gmail.com>" << endl;
    qout << "Developed for: elite s.c.p.a. <info@elitetech.it>" << endl << endl;

    qInstallMessageHandler(SHMMessagesHandler);                     // install message handler defined in messagehandler.h file
    SHMMessagesHandlerPrintHeader();                                // print log header info

    // TODO
    // valutare i parametri in questo modo
    // http://doc.qt.io/qt-5/qcommandlineparser.html
    qInfo() << "◌ Implementare parsing dei parametri per bene in main.cpp: http://doc.qt.io/qt-5/qcommandlineparser.html";

    // nessun argomento
    if (argc == 1)
    {
        print_usage(argv[0]);                         // show usage
        QTimer::singleShot(5000, &app, SLOT(quit())); // stop after 5 seconds
    } else
    // valuta argomenti
    {
        // OPZIONE -f: apre il file passato come argomento
        // eg: shm_storehouse -f nomefile.json
        if ( QString::compare(argv[1], "-f", Qt::CaseSensitive) == 0 && argc > 2 )
        {
            qInfo() << "Application launched in FILE MODE";

            qout << "File mode" << endl << endl;

            // read file content
            qInfo() << "Opening " << argv[2] << " file";
            QString fileContent;
            QFile file;
            file.setFileName(argv[2]);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            fileContent = file.readAll();
            file.close();

            // parse requests included in the file
            requestsParser = new shmRequestParser();
            requestsParser->parse(fileContent);

            // execute the requests
            majordomo->dispatchRequests(requestsParser->getSHMRequestsList());

            // debug purposes only
            qout << fileContent;

            // quit application
            QTimer::singleShot(1000, &app, SLOT(quit()));               // stop application after 5 seconds
        }
        else
        // OPZIONE -d: apre un canale TCP in ascolto
        // eg: shm_storehouse -d
        if ( QString::compare(argv[1], "-d", Qt::CaseSensitive) == 0 && argc == 2 )
        {
            qInfo() << "Application launched in DAEMON MODE";
            qout << "Daemon mode" << endl << endl;

            // start TCP chat server
            tcpChat* chat = new tcpChat(TCP_port);
            chat->startChat();

            // start telnet-like server
            // using namespace qhttp::client;
            // prepare to parse data and dispatch requests
            majordomo->listenTo(chat);

            webServer webserver(&app);
            webserver.start(HTTP_port);

        }
    }

    return app.exec();
}

