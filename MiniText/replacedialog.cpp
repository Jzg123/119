#include "replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    :QDialog(parent)
{
    find_label          = new QLabel(tr("查找内容"));
    replace_label       = new QLabel(tr("替换为"));
    find_str            = new QLineEdit();
    replace_str         = new QLineEdit();
    find_next_button    = new QPushButton(tr("查找下一个"));
    replaced_one_button = new QPushButton(tr("替换"));
    replaced_all_button = new QPushButton(tr("全部替换"));
    cancle_button       = new QPushButton(tr("取消"));
    ignore_flag         = new QCheckBox(tr("区分大小写"));

    QGridLayout *grdly  = new QGridLayout(this);
    QVBoxLayout *vboxly = new QVBoxLayout(this);

    vboxly->addWidget(replaced_all_button);
    vboxly->addWidget(cancle_button);
    grdly->addWidget(find_label,0,0);
    grdly->addWidget(find_str,0,1);
    grdly->addWidget(find_next_button,0,2);
    grdly->addWidget(replace_label,1,0);
    grdly->addWidget(replace_str,1,1);
    grdly->addWidget(replaced_one_button,1,2);
    grdly->addWidget(ignore_flag,2,1);
    grdly->addLayout(vboxly,2,2);

    find_str->setText(tr(""));
    replace_str->setText(tr(""));
    find_next_button->setEnabled(false);
    replaced_one_button->setEnabled(false);
    replaced_all_button->setEnabled(false);

    this->setMaximumSize(300,100);

    connect(find_str,SIGNAL(textChanged(QString)),this,SLOT(chooseStrSlot()));
    connect(cancle_button,SIGNAL(clicked()),this,SLOT(close()));
    connect(find_next_button,SIGNAL(clicked()),this,SLOT(findButtonStateSlot()));
    connect(replaced_one_button,SIGNAL(clicked()),this,SLOT(replaceOneButtonStateSlot()));
    connect(replaced_all_button,SIGNAL(clicked()),this,SLOT(replaceAllButtonStateSlot()));
}

ReplaceDialog::~ReplaceDialog()
{
    if(find_str){
        delete find_str;
    }
    if(replace_str){
        delete replace_str;
    }
    if(find_next_button){
        delete find_next_button;
    }
    if(replaced_one_button){
        delete replaced_one_button;
    }
    if(replaced_all_button){
        delete replaced_all_button;
    }
    if(cancle_button){
        delete cancle_button;
    }
    if(ignore_flag){
        delete ignore_flag;
    }
    if(find_label){
        delete find_label;
    }
    if(replace_label){
        delete replace_label;
    }
}

void ReplaceDialog::chooseStrSlot()
{
    if(!find_str->text().isEmpty()){
        find_next_button->setEnabled(true);
        replaced_one_button->setEnabled(true);
        replaced_all_button->setEnabled(true);
    }
    else{
        find_next_button->setEnabled(false);
        replaced_one_button->setEnabled(false);
        replaced_all_button->setEnabled(false);
    }
}

void ReplaceDialog::findButtonStateSlot()
{
    if(ignore_flag->isChecked()){
        emit findReplaceStr(find_str->text(),true);
    }
    else{
        emit findReplaceStr(find_str->text(),false);
    }
}

void ReplaceDialog::replaceOneButtonStateSlot()
{
    emit replaceCurOneStr(find_str->text(),replace_str->text());

}

void ReplaceDialog::replaceAllButtonStateSlot()
{
    if(ignore_flag->isChecked()){
        emit replaceAllStr(find_str->text() , replace_str->text(),true);
    }
    else{
        emit replaceAllStr(find_str->text() , replace_str->text(),false);
    }


}
