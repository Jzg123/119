#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MiniText"));
    mini_text = new QTextEdit;
    this->setCentralWidget(mini_text);
    resize(900,500);
    cur_file_name = tr("");

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
   if(file_menu){
       delete file_menu;
   }
   if(edit_menu){
       delete edit_menu;
   }
   if(new_act){
       delete new_act;
   }
   if(open_act){
       delete open_act;
   }
   if(save_act){
       delete save_act;
   }
   if(exit_act){
       delete exit_act;

   }
   if(find_act){
       delete find_act;

   }
   if(replace_act){
       delete replace_act;
   }

   if(mini_text){
       delete mini_text;
   }
   if(find_dialog){
       delete find_dialog;
   }
   if(replace_dialog){
       delete replace_dialog;
   }
   if(another_save_act){
       delete another_save_act;
   }
}

void MainWindow::createMenus()
{

    file_menu = menuBar()->addMenu(tr("&文件"));
    file_menu->setStyleSheet("color:blue");
    file_menu->addAction(new_act);
    file_menu->addAction(open_act);
    file_menu->addAction(save_act);
    file_menu->addAction(another_save_act);
    file_menu->addSeparator();
    file_menu->addAction(exit_act);
    edit_menu = menuBar()->addMenu(tr("&编辑"));
    edit_menu->setStyleSheet("color:blue");
    edit_menu->addAction(find_act);
    edit_menu->addAction(replace_act);

    QToolBar *tool_bar = addToolBar(tr("file"));
    tool_bar->addAction(new_act);
    tool_bar->addAction(open_act);
    tool_bar->addAction(save_act);
    tool_bar->addAction(another_save_act);
    tool_bar->addAction(find_act);
    tool_bar->addAction(replace_act);
    tool_bar->addAction(exit_act);

}

void MainWindow::createActions()
{
    find = false;
    find_dialog = new FindDialog(this);
    replace_dialog = new ReplaceDialog(this);
    //Action响应file_menu
    new_act = new QAction(QIcon(tr(":/images/new")),tr("&新建"),this);
    new_act->setShortcut(QKeySequence::New);

    open_act = new QAction(QIcon(tr(":/images/open")),tr("&打开"),this);
    open_act->setShortcut(QKeySequence::Open);

    save_act = new QAction(QIcon(tr(":/images/save")),tr("&保存"),this);
    save_act->setShortcut(QKeySequence::Save);

    another_save_act = new QAction(QIcon(tr(":/images/another_save")),tr("另存为"),this);


    exit_act = new QAction(QIcon(tr(":/images/exit")),tr("&退出"),this);
    exit_act->setShortcut(QKeySequence::Quit);

    find_act = new QAction(QIcon(tr(":/images/find")),tr("&查找"),this);
    find_act->setShortcut(QKeySequence::Find);

    replace_act = new QAction(QIcon(tr(":/images/replace")),tr("&替换"),this);
    replace_act->setShortcut(QKeySequence::Replace);


    connect(new_act,SIGNAL(triggered()),this,SLOT(newAct()));
    connect(open_act,SIGNAL(triggered()),this,SLOT(openAct()));
    connect(save_act,SIGNAL(triggered()),this,SLOT(saveAct()));
    connect(another_save_act,SIGNAL(triggered()),this,SLOT(anotherSaveAct()));
    connect(exit_act,SIGNAL(triggered()),this,SLOT(exitAct()));
    connect(find_act,SIGNAL(triggered()),this,SLOT(showFindDialog()));
    connect(replace_act,SIGNAL(triggered()),this,SLOT(showReplaceDialog()));


    connect(find_dialog,SIGNAL(findTextDataButtonClickedSignal(QString,bool,bool)),
            this,SLOT(findAct(QString,bool,bool)));
    connect(replace_dialog,SIGNAL(findReplaceStr(QString,bool)),
            this,SLOT(findReplace(QString,bool)));
    connect(replace_dialog,SIGNAL(replaceCurOneStr(QString,QString)),
            this,SLOT(replaceCur(QString,QString)));
    connect(replace_dialog,SIGNAL(replaceAllStr(QString,QString,bool)),
            this,SLOT(replaceAll(QString,QString,bool)));
}

void MainWindow::newAct()
{
    if (mini_text->document()->isModified())
    {
        QMessageBox::StandardButton button = QMessageBox::information(this,
                                          "尚未保存", "是否要保存?",QMessageBox::Save |
                                           QMessageBox::Discard | QMessageBox::Cancel);
        switch(button)
        {
            case QMessageBox::Save:{
                saveAct();
                if (mini_text->document()->isModified()){
                    return;
                }
            }
            case QMessageBox::Cancel:{
                return;
            }
            case QMessageBox::Discard:{
                break;
            }
        }
    }
    mini_text->clear();
}

//打开文件
void MainWindow::openAct()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("打开文件"),QString(),
                          tr("文本文件(*.txt) ;; C++文件(*.h *.cpp *.hpp)"));
    cur_file_name = file_name;
    if(!file_name.isEmpty()){
       QFile file(file_name);
       if(!file.open(QIODevice::ReadOnly)){
          QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
          return;
       }
       QTextStream ins(&file);
       mini_text->setText(ins.readAll());
       file.close();
    }
}

//保存文件
void MainWindow::saveAct()
{
    if(cur_file_name.isEmpty()){
        QString file_name = QFileDialog::getSaveFileName(this,tr("保存文件"),QString(),
                               tr("文本文件(*.txt) ;; C++文件(*.h *.cpp *.hpp)"));
        if(!file_name.isEmpty()){
            QFile file(file_name);
            if(!file.open(QIODevice::WriteOnly)){
                QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
                return;
            }
            QTextStream outs(&file);
            outs<<mini_text->toPlainText();
            outs.flush();
            file.close();
        }
    }
    else{
        QFile file(cur_file_name);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
            return;
        }
        QTextStream outs(&file);
        outs<<mini_text->toPlainText();
        outs.flush();
        file.close();
    }
}

void MainWindow::anotherSaveAct()
{
    QString file_name = QFileDialog::getSaveFileName(this,tr("保存文件"),QString(),
                           tr("文本文件(*.txt) ;; C++文件(*.h *.cpp *.hpp)"));
    if(!file_name.isEmpty()){
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
            return;
        }
        QTextStream outs(&file);
        outs<<mini_text->toPlainText();
        outs.flush();
        file.close();
    }

}

void MainWindow::findReplace(QString find_str, bool flg)
{
    bool find_flag;
    if(flg){
        find_flag = mini_text->find(find_str,QTextDocument::FindCaseSensitively);
    }
    else{
        find_flag = mini_text->find(find_str);
    }
    if(!find_flag){
        QMessageBox::information(this,tr("结果"),tr("没有找到查找内容"),QMessageBox::Yes);
    }
    else{
        find = true;
    }


}

void MainWindow::replaceCur(QString find_str, QString replace_str)
{
    if(find){
        QTextCursor text_cursor = mini_text->textCursor();
        text_cursor.insertText(replace_str);
    }
    else{
        QMessageBox::information(this,tr("结果"),tr("没有内容不能替换")+find_str,QMessageBox::Yes);
    }
    find = false;
}

void MainWindow::replaceAll(QString find_str, QString replace_str,bool flg)
{
    if(!flg){
        bool haf = mini_text->find(find_str);
        if(haf){
            QTextCursor text_cursor = mini_text->textCursor();
            text_cursor.insertText(replace_str);
            while(mini_text->find(find_str)){
                text_cursor = mini_text->textCursor();
                text_cursor.insertText(replace_str);
            }
            while(mini_text->find(find_str,QTextDocument::FindBackward)){
                text_cursor = mini_text->textCursor();
                text_cursor.insertText(replace_str);
            }
        }
        else{
             QMessageBox::information(this,tr("结果"),tr("没有内容不能替换 ")+find_str,QMessageBox::Yes);
        }
    }
    else{
        bool haf = mini_text->find(find_str,QTextDocument::FindCaseSensitively);
        if(haf){
            QTextCursor text_cursor = mini_text->textCursor();
            text_cursor.insertText(replace_str);
            while(mini_text->find(find_str,QTextDocument::FindCaseSensitively)){
                text_cursor = mini_text->textCursor();
                text_cursor.insertText(replace_str);
            }
            while(mini_text->find(find_str,QTextDocument::FindCaseSensitively|QTextDocument::FindBackward)){
                text_cursor = mini_text->textCursor();
                text_cursor.insertText(replace_str);
            }
        }
        else{
            QMessageBox::information(this,tr("结果"),tr("没有内容不能替换")+find_str,QMessageBox::Yes);
        }
    }

}



void MainWindow::findAct(QString str,bool ignore,bool choose)
{
    QString text = str;
    bool find_flag;
    if(!text.isEmpty()){
        if(choose){
            if(ignore){
              find_flag = mini_text->find(text,QTextDocument::FindCaseSensitively);
            }
            else{
                find_flag = mini_text->find(text);

            }
        }
        else{
            if(ignore){
                find_flag = mini_text->find(text,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively);
            }
            else{
                find_flag = mini_text->find(text,QTextDocument::FindBackward);

            }
        }
        if(!find_flag){
            QMessageBox::information(this,tr("结果"),tr("没有找到查找内容"),QMessageBox::Yes);
        }
    }

}


void MainWindow::showFindDialog()
{
    find_dialog->show();
}

void MainWindow::showReplaceDialog()
{
    replace_dialog->show();
}

void MainWindow::exitAct()
{
    this->close();

}






