#ifndef UPDATE_REC_H
#define UPDATE_REC_H

#include <QDialog>
#include "database_manage.h"

namespace Ui {
class update_rec;
}

class update_rec : public QDialog
{
    Q_OBJECT

public:
    explicit update_rec(QWidget *parent = nullptr);
    ~update_rec();

private slots:
    void on_back_btn_clicked();

    void on_update_btn_clicked();

private:
    Ui::update_rec *ui;
};

#endif // UPDATE_REC_H
