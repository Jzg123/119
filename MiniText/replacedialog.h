#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>

class ReplaceDialog:public QDialog
{
    Q_OBJECT
public:
    ReplaceDialog(QWidget *parent = 0);
    ~ReplaceDialog();
signals:
    void replaceAllStr(QString , QString,bool);
    void replaceCurOneStr(QString,QString);
    void findReplaceStr(QString,bool);
private slots:
    void chooseStrSlot();
    void findButtonStateSlot();
    void replaceOneButtonStateSlot();
    void replaceAllButtonStateSlot();
private:
    QLineEdit *find_str;
    QLineEdit *replace_str;
    QPushButton *find_next_button;
    QPushButton *replaced_one_button;
    QPushButton *replaced_all_button;
    QPushButton *cancle_button;
    QCheckBox *ignore_flag;
    QLabel  *find_label;
    QLabel  *replace_label;
};

#endif // REPLACEDIALOG_H
