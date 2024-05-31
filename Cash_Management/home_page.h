#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QMainWindow>

namespace Ui {
class Home_page;
}

class Home_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home_page(QWidget *parent = nullptr);
    ~Home_page();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void populateTableWidget();
    void on_add_new_button_clicked();
    void on_Search_rec_button_clicked();
    void on_update_rec_button_clicked();
    void on_delete_rec_button_clicked();
    void on_refresh_rec_button_2_clicked();

    void on_quit_btn_clicked();

private:
    Ui::Home_page *ui;
};

#endif // HOME_PAGE_H
