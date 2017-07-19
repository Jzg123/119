#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QToolBar>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPageSetupDialog>

#include <finddialog.h>

#include <replacedialog.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
private slots:
    void createMenus();
    void createActions();
    void newAct();
    void openAct();
    void saveAct();
    void exitAct();
    void findAct(QString,bool,bool);
    void anotherSaveAct();
    void showFindDialog();
    void showReplaceDialog();
    void findReplace(QString,bool);
    void replaceCur(QString,QString);
    void replaceAll(QString,QString,bool);

private:
    //菜单
    bool   find;
    QMenu *file_menu;
    QMenu *edit_menu;
    QMenu *about_menu;
    //Action响应file_menu
    QAction *new_act;
    QAction *open_act;
    QAction *save_act;
    QAction *another_save_act;
    QAction *exit_act;
    //Action响应edit_menu
    QAction *find_act;
    QAction *replace_act;
    //Action响应help_menu
    //Edit
    QTextEdit *mini_text;

    FindDialog *find_dialog;
    ReplaceDialog *replace_dialog;
    QString cur_file_name;

};

#endif // MAINWINDOW_H
