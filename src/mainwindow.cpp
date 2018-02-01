#include "mainwindow.h"

#include <qaction.h>
#include <qboxlayout.h>
#include <qfiledialog.h>
#include <qimage.h>
#include <qimagereader.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qplaintextedit.h>
#include <qtimer.h>
#include <qpushbutton.h>

#include <qapplication.h>
#include <qtranslator.h>

QTranslator appTranslator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

    setMinimumSize(300, 200);
    resize(minimumSizeHint());
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    createWidgets();
    createActions();
    createLanguageMenu();
    createMenus();
    createButtons();
    createLayouts();

    retranslateUi();
}

void MainWindow::createActions()
{
    openImageAction = new QAction(this);
    connect(openImageAction, &QAction::triggered, [=]{
        QString fn = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Image file") + " (*.*)");
        if (fn == QString())
            return;

        QByteArray ba = fn.toLatin1();
        std::string filename = ba.data();
    });

    openVideoAction = new QAction(this);
    connect(openVideoAction, &QAction::triggered, [=]{
    });

    captureAction = new QAction(this);
    connect(captureAction, &QAction::triggered, [=]{
    });
    captureNAction = new QAction(this);
    connect(captureNAction, &QAction::triggered, [=]{
    });

    exitAction = new QAction(this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(this);
    connect(aboutAction, &QAction::triggered, [=]
    {
        /*QMessageBox::information(this, tr("title"),
            tr("Author: 123") + ", 2015\n" + tr("Version") +
            QString(": %1.%2.%3.%4")
            .arg(DBTOOL_VERSION_MAJOR)
            .arg(DBTOOL_VERSION_MINOR)
            .arg(DBTOOL_VERSION_PATCH)
            .arg(DBTOOL_VERSION_BUILD));*/
    });
}

void MainWindow::createLanguageMenu()
{
    languageMenu = new QMenu(this);
    QAction *defaultApplicationLanguage = languageMenu->addAction("English");
    defaultApplicationLanguage->setCheckable(true);
    defaultApplicationLanguage->setData(QString());
    defaultApplicationLanguage->setChecked(true);
    languageActionGroup = new QActionGroup(this);
    languageActionGroup->addAction(defaultApplicationLanguage);
    connect(languageActionGroup, SIGNAL(triggered(QAction *)), SLOT(changeLanguage(QAction *)));

    bool defaultFound = false;
    QString tsDirName = ":/ts/";
    QDir dir(tsDirName);
    QStringList filenames = dir.entryList();
    for (int i = 0; i < filenames.size(); ++i)
    {
        QString filename = tsDirName + filenames[i];

        QTranslator translator;
        translator.load(filename);

        QString language = translator.translate("MainWindow", "English");
        if (language == "English")
            continue;
        QString defaultLanguage = translator.translate("MainWindow", "Default application language",
            "Set this variable to \"1\" to default choose current language");

        QAction *action = new QAction(language, this);
        action->setCheckable(true);
        action->setData(filename);
        languageMenu->addAction(action);
        languageActionGroup->addAction(action);

        if (!defaultFound && defaultLanguage != QString())
        {
            action->setChecked(true);
            defaultFound = true;

            QApplication::installTranslator(&appTranslator);
            appTranslator.load(action->data().toString());
        }
    }
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(this);
    fileMenu->addAction(openImageAction);
    fileMenu->addAction(openVideoAction);
    fileMenu->addAction(captureAction);
    fileMenu->addAction(captureNAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = new QMenu(this);

    settingsMenu = new QMenu(this);
    settingsMenu->addMenu(languageMenu);

    helpMenu = new QMenu(this);
    helpMenu->addAction(aboutAction);

    mainMenu = new QMenuBar(this);
    mainMenu->addMenu(fileMenu);
    //mainMenu->addMenu(editMenu);
    mainMenu->addMenu(settingsMenu);
    mainMenu->addMenu(helpMenu);

    setMenuBar(mainMenu);
}

void MainWindow::createButtons()
{
}

void MainWindow::createLayouts()
{
    leftLayout = new QVBoxLayout;
    //leftLayout->addWidget(imageArea, 3);
    //leftLayout->addWidget(imageArea2, 2);

    logLayout = new QVBoxLayout;
    /*logLayout->addWidget(left);
    logLayout->addWidget(top);
    logLayout->addWidget(right);
    logLayout->addWidget(bottom);*/
    //logLayout->addWidget(logLabel);
    //logLayout->addWidget(log);

    rightLayout = new QVBoxLayout;
    rightLayout->addLayout(logLayout);


    auto x = new QPushButton(this);
    x->setText(tr("something"));
    x->show();
    rightLayout->addWidget(x);

    mainLayout = new QHBoxLayout;
    //mainLayout->addLayout(leftLayout, 4);
    mainLayout->addLayout(rightLayout, 1);

    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::createWidgets()
{
}

void MainWindow::retranslateUi()
{
    fileMenu->setTitle(tr("File"));
    openImageAction->setText(tr("Open image..."));
    openVideoAction->setText(tr("Open video..."));
    captureAction->setText(tr("Start capture..."));
    captureNAction->setText(tr("Start capture from device..."));
    exitAction->setText(tr("Exit"));
    editMenu->setTitle(tr("Edit"));
    settingsMenu->setTitle(tr("Settings"));
    languageMenu->setTitle(tr("Language"));
    helpMenu->setTitle(tr("Help"));
    aboutAction->setText(tr("About"));

    //logLabel->setText(tr("Log"));

    setWindowTitle(tr("title"));
}

void MainWindow::changeLanguage(QAction *action)
{
    QApplication::removeTranslator(&appTranslator);
    if (action->data() != QString())
    {
        QApplication::installTranslator(&appTranslator);
        appTranslator.load(action->data().toString());
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi();
    QMainWindow::changeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //event->ignore();
}
