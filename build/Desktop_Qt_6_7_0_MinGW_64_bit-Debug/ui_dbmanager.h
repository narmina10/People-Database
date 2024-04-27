/********************************************************************************
** Form generated from reading UI file 'dbmanager.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBMANAGER_H
#define UI_DBMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dbmanager
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *dbmanager)
    {
        if (dbmanager->objectName().isEmpty())
            dbmanager->setObjectName("dbmanager");
        dbmanager->resize(800, 600);
        centralwidget = new QWidget(dbmanager);
        centralwidget->setObjectName("centralwidget");
        dbmanager->setCentralWidget(centralwidget);
        menubar = new QMenuBar(dbmanager);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        dbmanager->setMenuBar(menubar);
        statusbar = new QStatusBar(dbmanager);
        statusbar->setObjectName("statusbar");
        dbmanager->setStatusBar(statusbar);

        retranslateUi(dbmanager);

        QMetaObject::connectSlotsByName(dbmanager);
    } // setupUi

    void retranslateUi(QMainWindow *dbmanager)
    {
        dbmanager->setWindowTitle(QCoreApplication::translate("dbmanager", "dbmanager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dbmanager: public Ui_dbmanager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBMANAGER_H
