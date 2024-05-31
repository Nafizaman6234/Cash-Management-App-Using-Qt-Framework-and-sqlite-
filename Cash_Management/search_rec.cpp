#include "search_rec.h"
#include "home_page.h"
#include "ui_search_rec.h"

#include <QMessageBox>

search_rec::search_rec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search_rec)
{
    ui->setupUi(this);
}

search_rec::~search_rec()
{
    delete ui;
}

void search_rec::on_back_btn_clicked()
{
    this->hide();
    Home_page *home_page = new Home_page();
    home_page->show();
}


void search_rec::on_search_btn_clicked()
{
    QString name = ui->search_input->text();

    // Clear existing data in the table widget
    ui->search_result_table->clearContents();
    ui->search_result_table->setRowCount(0);

    // Establish connection to the database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("I:/Qt_Projects/Cash_management/Cash_Management/Database/cash_management_database.db");

    if (!database.open())
    {
        qDebug() << "Error: Unable to open Database";
        return;
    }

    // Execute SQL query to retrieve data from the database
    QSqlQuery query(database);
    query.prepare("SELECT NAME, CASH, DATE FROM cash_management WHERE NAME = :name");
    query.bindValue(":name", name);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Limit the maximum number of rows to display
    const int maxRows = 10; // Change this value to set the maximum number of rows
    int rowCount = 0;

    // Populate the table widget with data
    while (query.next() && rowCount < maxRows)
    {
        QString name = query.value(0).toString();
        QString cash = query.value(1).toString();
        QString date = query.value(2).toString();

        ui->search_result_table->insertRow(rowCount);
        ui->search_result_table->setItem(rowCount, 0, new QTableWidgetItem(name));
        ui->search_result_table->setItem(rowCount, 1, new QTableWidgetItem(cash));
        ui->search_result_table->setItem(rowCount, 2, new QTableWidgetItem(date));

        ++rowCount;
    }

    // Close the database connection
    database.close();

    if (rowCount == 0)
    {
        QMessageBox::information(this, "No Records Found", "No records found for the given name.");
    }
}


