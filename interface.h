#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlQueryModel>
#include "dbmanager.h"

class Interface : public QWidget {
    Q_OBJECT
public:
    Interface(QWidget *parent = nullptr);
    ~Interface();



private:
    void setupUI();
    void setupConnections();

    QLineEdit *nameLineEdit;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *showDatabaseButton;
    QPushButton *findButton;
    QLineEdit *findLineEdit;
    QTableView *tableView;
    DbManager *dbManager;
    QSqlQueryModel *model;
    QWidget *databaseWindow;
};

#endif // INTERFACE_H


