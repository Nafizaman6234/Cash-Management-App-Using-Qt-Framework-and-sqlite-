#include "add_new_rec.h"
#include "home_page.h"
#include "ui_add_new_rec.h"

#include <QMessageBox>

Add_new_rec::Add_new_rec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_new_rec)
{
    ui->setupUi(this);
}

Add_new_rec::~Add_new_rec()
{
    delete ui;
}

void Add_new_rec::on_back_btn_clicked()
{
    this->hide();
    Home_page *home_page = new Home_page();
    home_page->show();
}

void Add_new_rec::on_add_btn_clicked()
{
    QString name = ui->name_input->text();
    QString amount = ui->amount_input->text();

    // Get the current date
    QDate currentDate = QDate::currentDate();
    QString currentDateStr = currentDate.toString("yyyy-MM-dd"); // Format the date as YYYY-MM-DD

    // Establish connection to the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("I:/Qt_Projects/Cash_management/Cash_Management/Database/cash_management_database.db"); // Adjust the path here

    if (!database.open())
    {
        qDebug() << "Error: Unable to open Database";
        return;
    }

    // Check if the name already exists in the database
    QSqlQuery query(database);
    query.prepare("SELECT NAME FROM cash_management WHERE NAME = :name");
    query.bindValue(":name", name);
    if (query.exec() && query.next())
    {
        // Name already exists, prompt the user to change the name
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Duplicate Name", "A record with this name already exists. Do you want to change the name?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            // User wants to change the name, return without adding the record
            return;
        }
        // If the user clicks "No", continue with adding the record
    }

    // Continue with adding the record to the database
    query.prepare("INSERT INTO cash_management (NAME, CASH, DATE) VALUES (:name, :amount, :date)");
    query.bindValue(":name", name);
    query.bindValue(":amount", amount);
    query.bindValue(":date", currentDateStr);

    if (!query.exec())
    {
        qDebug() << "Error adding record:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Record added successfully";
        QMessageBox::information(this, "Success!", "Record Added Successfully....");
    }

    database.close();
}
