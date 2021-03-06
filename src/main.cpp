#include <time.h>

#ifdef WIN32
#include <QtPlugin>
// for static
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

#include "mainwindow.h"
#include <QApplication>
#include <qglobal.h>

#ifdef WIN32
#include <Windows.h>
#endif

void win32_hacks();

int main(int argc, char *argv[])
{
    win32_hacks();
    qsrand(time(0));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void win32_hacks()
{
#ifdef WIN32
    //SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#endif
}
