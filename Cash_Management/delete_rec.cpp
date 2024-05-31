#include "delete_rec.h"
#include "home_page.h"
#include "ui_delete_rec.h"

#include <QMessageBox>

delete_rec::delete_rec(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::delete_rec)
{
    ui->setupUi(this);
}

delete_rec::~delete_rec()
{
    delete ui;
}

void delete_rec::on_back_btn_clicked()
{
    this->hide();
    Home_page *home_page = new Home_page();
    home_page->show();
}




void delete_rec::on_delete_btn_clicked()
{
    QString name = ui->name_input->text();

    // Establish connection to the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("I:/Qt_Projects/Cash_management/Cash_Management/Database/cash_management_database.db");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open Database";
        return;
    }

    // Execute SQL query to check if the name exists in the database
    QSqlQuery checkQuery(database);
    checkQuery.prepare("SELECT COUNT(*) FROM cash_management WHERE NAME = :name");
    checkQuery.bindValue(":name", name);

    if (!checkQuery.exec() || !checkQuery.first())
    {
        qDebug() << "Error checking record existence:" << checkQuery.lastError().text();
        database.close();
        return;
    }

    int recordCount = checkQuery.value(0).toInt();
    if (recordCount == 0)
    {
        // Display a message box indicating that the name was not found
        QMessageBox::information(this, "Name Not Found", "The name does not exist in the database.");
        database.close();
        return;
    }

    // If the name exists, proceed with deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "Delete Record", "Are you sure you want to delete this record?",
                                 QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        database.close();
        return; // If user clicks "No", do nothing
    }

    QSqlQuery deleteQuery(database);

    // Modify the SQL query to delete the record matching the provided name
    deleteQuery.prepare("DELETE FROM cash_management WHERE NAME = :name");
    deleteQuery.bindValue(":name", name);
    QMessageBox::information(this, "Success!","Record Deleted Successfully....");

    if (!deleteQuery.exec())
    {
        qDebug() << "Error deleting record:" << deleteQuery.lastError().text();
        database.close();
        return;
    }

    qDebug() << "Record deleted successfully";
    database.close();
}



