#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "home_page.h"//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_button_clicked()
{
    QString username = ui->User_lineEdit->text();
    QString password = ui->Pass_lineEdit->text();

    if(username =="Your login username" && password == "Your login password") /// Enter your Username and password inside the double quotation.....
    {

        this->hide();
        Home_page *home_page = new Home_page();
        home_page->show();


    }
    else
    {

        QMessageBox::warning(this,"Error!!", "Wrong Username or Password!");
    }

}


void MainWindow::on_Quit_buttton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"QUIT Application","Are you sure to close the application?", QMessageBox::Yes | QMessageBox::No);

    if (reply ==QMessageBox::Yes)
    {
        QApplication::quit();
    }

}

