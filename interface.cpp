#include "interface.h"
#include <QApplication>
#include <QFont>
#include <QDebug>
#include <QWindow>

Interface::Interface(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}

Interface::~Interface() {
    delete dbManager;
    delete model;
}

void Interface::setupUI() {
    QFont font("Times New Roman");
    QApplication::setFont(font);

    setStyleSheet("background-color: lightBlue");
    setWindowIcon(QIcon(":/222.png"));
    setWindowTitle("Add People");
    setGeometry(100, 100, 350, 200);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setGeometry(20, 20, 280, 30);
    nameLineEdit->setStyleSheet("background-color: white");

    addButton = new QPushButton("Add person", this);
    addButton->setGeometry(20, 60, 130, 30);
    addButton->setIcon(QIcon(":/add.png"));
    addButton->setStyleSheet("background-color: white");

    removeButton = new QPushButton("Remove person", this);
    removeButton->setGeometry(170, 60, 130, 30);
    removeButton->setIcon(QIcon(":/remove.png"));
    removeButton->setStyleSheet("background-color: white");

    showDatabaseButton = new QPushButton("Show the database", this);
    showDatabaseButton->setGeometry(85, 100, 155, 30);
    showDatabaseButton->setIcon(QIcon(":/show.png"));
    showDatabaseButton->setStyleSheet("background-color: white");

    dbManager = new DbManager("D:/akhun/People_DB/people.db");

databaseWindow = new QWidget;

databaseWindow->setWindowTitle("People Database");
databaseWindow->setWindowIcon(QIcon(":/lens.png"));
databaseWindow->setGeometry(500, 100, 600, 400);

tableView = new QTableView(databaseWindow);
tableView->setGeometry(30, 30, 560, 360);

model = new QSqlQueryModel;
model->setQuery("SELECT * FROM people");
tableView->setModel(model);

tableView->resizeColumnsToContents();

findButton = new QPushButton("Find...", databaseWindow);
findButton->setGeometry(0, 3, 100, 25);

findLineEdit = new QLineEdit(databaseWindow);
findLineEdit->setGeometry(105, 3, 200, 25);
}


void Interface::setupConnections() {
        connect(addButton, &QPushButton::clicked, [this]() {
            QString name = nameLineEdit->text();
            if (!name.isEmpty()) {
                if (dbManager->addPerson(name)) {
                    qDebug() << "Person added successfully";
                } else {
                    qDebug() << "Failed to add person";
                }
            }
        });

        connect(removeButton, &QPushButton::clicked, [this]() {
            QString name = nameLineEdit->text();
            if (!name.isEmpty()) {
                if (dbManager->removePerson(name)) {
                    qDebug() << "Person removed successfully";
                } else {
                    qDebug() << "Failed to remove person";
                }
            }
        });
        connect(showDatabaseButton, &QPushButton::clicked, [this](){
databaseWindow->show();
        });

        connect(findButton, &QPushButton::clicked, [this]() {
            QString searchText = findLineEdit->text().trimmed();
            if (!searchText.isEmpty()) {
                QString queryStr = QString("SELECT * FROM people WHERE name LIKE '%%1%'").arg(searchText);
                model->setQuery(queryStr);
            } else {

                model->setQuery("SELECT * FROM people");
            }

        });


    }



