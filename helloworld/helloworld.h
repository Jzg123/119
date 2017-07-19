#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QDialog>

namespace Ui {
class helloworld;
}

class helloworld : public QDialog
{
    Q_OBJECT

public:
    explicit helloworld(QWidget *parent = 0);
    ~helloworld();

private:
    Ui::helloworld *ui;
};

#endif // HELLOWORLD_H
