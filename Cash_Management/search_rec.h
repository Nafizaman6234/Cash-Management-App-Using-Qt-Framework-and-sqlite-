#ifndef SEARCH_REC_H
#define SEARCH_REC_H

#include <QDialog>
#include "database_manage.h"

namespace Ui {
class search_rec;
}

class search_rec : public QDialog
{
    Q_OBJECT

public:
    explicit search_rec(QWidget *parent = nullptr);
    ~search_rec();

private slots:
    void on_back_btn_clicked();

    void on_search_btn_clicked();

private:
    Ui::search_rec *ui;
};

#endif // SEARCH_REC_H
