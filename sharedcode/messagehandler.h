#ifndef MESSAGEHANDLER_C
#define MESSAGEHANDLER_C

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <qlogging.h>

#define LOGGING_DIR     "/tmp"
#define LOGGER_INFO     "[I]: "
#define LOGGER_DEBUG    "[D]: "
#define LOGGER_WARNING  "[W]: "
#define LOGGER_CRITICAL "[C]: "
#define LOGGER_FATAL    "[F]: "

/*!
  \fn void SHMMessagesHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)

  Define a message handler that logs messages in the \c {LOGGING_DIR / applicationName .log} file.
  The file name is the application name dot log, and is lowercase using undescore character instead of spaces.
  */
void SHMMessagesHandler(QtMsgType type, const QMessageLogContext &CTX, const QString & msg)
{
    //
    QString logFileName = QCoreApplication::applicationName().replace(' ', '_') + ".log";
    QString logFile = (QDir(LOGGING_DIR).filePath(logFileName)).toLower();

    QFileInfo fi(CTX.file);
    QString txt, details;

    switch (type) {
    case QtInfoMsg:
        txt = QString("%1 %2").arg(LOGGER_INFO,msg);
    break;
    case QtDebugMsg:
        txt = QString("%1 %2").arg(LOGGER_DEBUG,msg);
        break;
    case QtWarningMsg:
        txt = QString("%1 %2").arg(LOGGER_WARNING,msg);
        details = QString(" File:      %1\n Function:  %2\n Line:      %3\n").
                arg(fi.fileName(),
                    QString(CTX.function),
                    QString::number(CTX.line));
    break;
    case QtCriticalMsg:
        txt = QString("%1 %2").arg(LOGGER_CRITICAL,msg);
    break;
    case QtFatalMsg:
        txt = QString("%1 %2").arg(LOGGER_FATAL,msg);
    break;
    }

    QFile outFile(logFile);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
    if ( details.length() != 0 ) {
        ts << details << endl;
    }
}

void SHMMessagesHandlerPrintHeader() {
    qInfo();
    qInfo();
    qInfo();
    qInfo();
    qInfo().noquote() << QCoreApplication::applicationName();
    QString underline;
    for (int i = 0 ; i < QCoreApplication::applicationName().length() + 1 ; i++ ) {
        underline.append("=");
    }
    qInfo().noquote() << underline;
    qInfo().noquote() << "Started at " << QDateTime::currentDateTime().toString();
    qInfo();
}
#endif // MESSAGEHANDLER_C
