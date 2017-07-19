#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>

class FindDialog:public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

signals:
    void findTextDataButtonClickedSignal(QString,bool,bool);

private slots:
    void findButtonState();
    void findDataButtonClickedState();

private:
    QLineEdit *find_edit;
    QLabel    *find_label,*ignore_label,*next_label,*back_label;
    QPushButton *find_button;
    QRadioButton *next_radio;
    QRadioButton *back_radio;
    QCheckBox *ignore_flag;
};

#endif // FINDDIALOG_H
