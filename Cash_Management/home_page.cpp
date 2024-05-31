#include "home_page.h"
#include "ui_home_page.h"
#include "add_new_rec.h"
#include "search_rec.h"
#include "update_rec.h"
#include "delete_rec.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

Home_page::Home_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home_page)
{
    ui->setupUi(this);

    // Set column count for the table widget
    ui->record_table->setColumnCount(3); // Assuming you have 3 columns: NAME, CASH, DATE
}

Home_page::~Home_page()
{
    delete ui;
}

void Home_page::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event); // Call the base class implementation

    populateTableWidget(); // Call your function to populate the table widget
}

void Home_page::populateTableWidget()
{
    // Clear the existing data in the table
    ui->record_table->clearContents();
    ui->record_table->setRowCount(0); // Reset row count before populating

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
    if (!query.exec("SELECT NAME, CASH, DATE FROM cash_management"))
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Determine the number of rows based on the number of records returned by the query
    int rowCount = 0;
    while (query.next())
    {
        ++rowCount;
    }

    // Set the row count of the table widget
    ui->record_table->setRowCount(rowCount);

    // Populate the table widget with data
    int row = 0;
    query.first(); // Move to the first record
    do
    {
        QString name = query.value(0).toString();
        QString cash = query.value(1).toString();
        QString date = query.value(2).toString();

        ui->record_table->setItem(row, 0, new QTableWidgetItem(name));
        ui->record_table->setItem(row, 1, new QTableWidgetItem(cash));
        ui->record_table->setItem(row, 2, new QTableWidgetItem(date));

        ++row;
    } while (query.next());

    // Close the database connection
    database.close();
}

void Home_page::on_add_new_button_clicked()
{
    this -> hide();

    Add_new_rec *add_new_page = new Add_new_rec();
    add_new_page->show();
}

void Home_page::on_Search_rec_button_clicked()
{
    this -> hide();

    search_rec *search_rec_page = new search_rec();
    search_rec_page->show();
}

void Home_page::on_update_rec_button_clicked()
{
    this -> hide();

    update_rec *update_rec_page = new update_rec();
    update_rec_page->show();
}

void Home_page::on_delete_rec_button_clicked()
{
    this -> hide();

    delete_rec *delete_rec_page = new delete_rec();
    delete_rec_page->show();
}

void Home_page::on_refresh_rec_button_2_clicked()
{
    populateTableWidget();
}

void Home_page::on_quit_btn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "QUIT Application", "Are you sure to close the application?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
