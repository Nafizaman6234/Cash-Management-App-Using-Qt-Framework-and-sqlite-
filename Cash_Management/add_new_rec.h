#ifndef ADD_NEW_REC_H
#define ADD_NEW_REC_H

#include <QDialog>
#include "database_manage.h"

namespace Ui {
class Add_new_rec;
}

class Add_new_rec : public QDialog
{
    Q_OBJECT

public:
    explicit Add_new_rec(QWidget *parent = nullptr);
    ~Add_new_rec();

private slots:
    void on_back_btn_clicked();

    void on_add_btn_clicked();

private:
    Ui::Add_new_rec *ui;
};

#endif // ADD_NEW_REC_H
