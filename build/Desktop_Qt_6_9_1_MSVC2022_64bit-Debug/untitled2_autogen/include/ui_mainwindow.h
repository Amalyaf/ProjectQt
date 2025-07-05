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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_another_client;
    QAction *actionClose_this_client;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *messageLineEdit;
    QPushButton *sendMessageButton;
    QPushButton *privateMessageSendButton;
    QSplitter *splitter;
    QTextBrowser *commonChatBrowser;
    QTextBrowser *privateChatBrowser;
    QMenuBar *menubar;
    QMenu *menuMain_menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(547, 468);
        actionOpen_another_client = new QAction(MainWindow);
        actionOpen_another_client->setObjectName("actionOpen_another_client");
        actionClose_this_client = new QAction(MainWindow);
        actionClose_this_client->setObjectName("actionClose_this_client");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        messageLineEdit = new QLineEdit(centralwidget);
        messageLineEdit->setObjectName("messageLineEdit");

        horizontalLayout->addWidget(messageLineEdit);

        sendMessageButton = new QPushButton(centralwidget);
        sendMessageButton->setObjectName("sendMessageButton");

        horizontalLayout->addWidget(sendMessageButton);

        privateMessageSendButton = new QPushButton(centralwidget);
        privateMessageSendButton->setObjectName("privateMessageSendButton");

        horizontalLayout->addWidget(privateMessageSendButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        commonChatBrowser = new QTextBrowser(splitter);
        commonChatBrowser->setObjectName("commonChatBrowser");
        splitter->addWidget(commonChatBrowser);
        privateChatBrowser = new QTextBrowser(splitter);
        privateChatBrowser->setObjectName("privateChatBrowser");
        splitter->addWidget(privateChatBrowser);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 547, 26));
        menuMain_menu = new QMenu(menubar);
        menuMain_menu->setObjectName("menuMain_menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMain_menu->menuAction());
        menuMain_menu->addAction(actionOpen_another_client);
        menuMain_menu->addSeparator();
        menuMain_menu->addAction(actionClose_this_client);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_another_client->setText(QCoreApplication::translate("MainWindow", "Open another client", nullptr));
        actionClose_this_client->setText(QCoreApplication::translate("MainWindow", "Close this client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Your message:", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("MainWindow", "Send to all", nullptr));
        privateMessageSendButton->setText(QCoreApplication::translate("MainWindow", "Send private", nullptr));
        menuMain_menu->setTitle(QCoreApplication::translate("MainWindow", "Main menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
