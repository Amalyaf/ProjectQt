/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *showAllUsers;
    QPushButton *showPrvtMessages;
    QPushButton *showChatMessages;
    QPushButton *showLogs;
    QPushButton *blockUser;
    QPushButton *ConnectChats;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(737, 582);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        showAllUsers = new QPushButton(centralwidget);
        showAllUsers->setObjectName("showAllUsers");

        verticalLayout->addWidget(showAllUsers);

        showPrvtMessages = new QPushButton(centralwidget);
        showPrvtMessages->setObjectName("showPrvtMessages");

        verticalLayout->addWidget(showPrvtMessages);

        showChatMessages = new QPushButton(centralwidget);
        showChatMessages->setObjectName("showChatMessages");

        verticalLayout->addWidget(showChatMessages);

        showLogs = new QPushButton(centralwidget);
        showLogs->setObjectName("showLogs");

        verticalLayout->addWidget(showLogs);

        blockUser = new QPushButton(centralwidget);
        blockUser->setObjectName("blockUser");

        verticalLayout->addWidget(blockUser);

        ConnectChats = new QPushButton(centralwidget);
        ConnectChats->setObjectName("ConnectChats");

        verticalLayout->addWidget(ConnectChats);


        horizontalLayout->addLayout(verticalLayout);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");

        horizontalLayout->addWidget(textBrowser);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 737, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        showAllUsers->setText(QCoreApplication::translate("MainWindow", "Show all users", nullptr));
        showPrvtMessages->setText(QCoreApplication::translate("MainWindow", "Show private messages", nullptr));
        showChatMessages->setText(QCoreApplication::translate("MainWindow", "Show chat messages", nullptr));
        showLogs->setText(QCoreApplication::translate("MainWindow", "Show logs", nullptr));
        blockUser->setText(QCoreApplication::translate("MainWindow", "Block user", nullptr));
        ConnectChats->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
