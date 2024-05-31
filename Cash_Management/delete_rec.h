#ifndef DELETE_REC_H
#define DELETE_REC_H

#include <QDialog>
#include "database_manage.h"

namespace Ui {
class delete_rec;
}

class delete_rec : public QDialog
{
    Q_OBJECT

public:
    explicit delete_rec(QWidget *parent = nullptr);
    ~delete_rec();

private slots:
    void on_back_btn_clicked();

    void on_delete_btn_clicked();

private:
    Ui::delete_rec *ui;
};

#endif // DELETE_REC_H
