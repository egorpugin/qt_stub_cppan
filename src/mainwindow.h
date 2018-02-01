#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QWidget;
class QMenuBar;
class QMenu;
class QActionGroup;
class QAction;
class QPushButton;
class QPlainTextEdit;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QScrollArea;

class LabeledEdit;
class TransparentRubberBand;
class ImageWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeLanguage(QAction *action);
    void changeEvent(QEvent* event);
    void closeEvent(QCloseEvent *event);

signals:
private slots:

private:
    void setupUi();
    void retranslateUi();

private: /* data */
private: /* ui functions */
    void createActions();
    void createLanguageMenu();
    void createMenus();
    void createButtons();
    void createLayouts();
    void createWidgets();
private: /* ui components */
    QWidget *centralWidget;

    QMenuBar *mainMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *settingsMenu;
    QMenu *languageMenu;
    QMenu *helpMenu;

    QActionGroup *languageActionGroup;
    QAction *captureAction;
    QAction *captureNAction;
    QAction *openImageAction;
    QAction *openVideoAction;
    QAction *exitAction;
    QAction *aboutAction;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *logLayout;

    QLabel *logLabel;
    QPlainTextEdit *log;
};

#endif // MAINWINDOW_H
