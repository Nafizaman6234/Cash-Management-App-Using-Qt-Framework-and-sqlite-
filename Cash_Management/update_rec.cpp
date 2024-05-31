#include "update_rec.h"
#include "home_page.h"
#include "qregularexpression.h"
#include "ui_update_rec.h"

#include <QMessageBox>

update_rec::update_rec(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::update_rec)
{
    ui->setupUi(this);
}

update_rec::~update_rec()
{
    delete ui;
}

void update_rec::on_back_btn_clicked()
{
    this->hide();
    Home_page *home_page = new Home_page();
    home_page->show();
}




void update_rec::on_update_btn_clicked()
{
    QString name = ui->name_input->text();
    QString amountInput = ui->amount_input->text();

    // Extract the sign and the actual amount from the input
    QRegularExpression re("([-+]?)(\\d+)");
    QRegularExpressionMatch match = re.match(amountInput);

    if (!match.hasMatch())
    {
        qDebug() << "Invalid amount format";
        return;
    }

    QString sign = match.captured(1); // Get the sign (+ or -)
    QString amountStr = match.captured(2); // Get the actual amount

    // Convert the amount to an integer
    int amount = amountStr.toInt();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("I:/Qt_Projects/Cash_management/Cash_Management/Database/cash_management_database.db");

    if (QFile::exists(":/cash_management_database.db"))
    {
        qDebug() << "Database file Exists";
    }
    else
    {
        qDebug() << "Database file doesn't  Exists";
        return;
    }

    if (!database.open())
    {
        qDebug() << "Error: Unable to open Database";
        return;
    }
    else
    {
        qDebug() << "Database Opened Successfully...";
    }

    QSqlQuery query(database);

    // Check if the name exists in the database
    query.prepare("SELECT CASH FROM cash_management WHERE NAME = :name");
    query.bindValue(":name", name);
    if (!query.exec())
    {
        qDebug() << "Error selecting record:" << query.lastError().text();
        return;
    }

    if (query.next())
    {
        // Name exists, update the amount and date
        int previousAmount = query.value(0).toInt();
        int newAmount = previousAmount + (sign == "+" ? amount : -amount);

        // Get the current date
        QDate currentDate = QDate::currentDate();
        QString currentDateStr = currentDate.toString("yyyy-MM-dd"); // Format the date as YYYY-MM-DD

        // Update the amount and date in the database
        query.prepare("UPDATE cash_management SET CASH = :amount, DATE = :date WHERE NAME = :name");
        query.bindValue(":amount", newAmount);
        query.bindValue(":date", currentDateStr);
        query.bindValue(":name", name);
        if (!query.exec())
        {
            qDebug() << "Error updating record:" << query.lastError().text();
        }
        else
        {
            qDebug() << "Record updated successfully";
            QMessageBox::information(this, "Success!","Record Updated Successfully....");
        }
    }
    else
    {
        // Name does not exist in the database
        qDebug() << "Name does not exist in the database";
        QMessageBox::information(this, "No Records Found", "No records found for the given name.");
    }

    database.close();
}




