#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showAllUsers_clicked()
{
        auto allUsers = server->chat->getChat();
        QString browser;
        for (const auto &usrs : allUsers){
            browser.append(QString::fromStdString(usrs) + "\n");
        }
        if (ui->textBrowser->toPlainText() != browser)
            ui->textBrowser->setText(browser);
}


void MainWindow::on_showPrvtMessages_clicked()
{
    auto allPrvtMessages = server->chat->showPrvtMessages();
    QString browser;
    for (const auto &msgs : allPrvtMessages){
        browser.append(QString::fromStdString(msgs) + "\n");
    }
    if (ui->textBrowser->toPlainText() != browser)
        ui->textBrowser->setText(browser);
}


void MainWindow::on_showChatMessages_clicked()
{
    auto allUsers = server->chat->showChatMessages();
    QString browser;
    for (const auto &usrs : allUsers){
        browser.append(QString::fromStdString(usrs) + "\n");
    }
    if (ui->textBrowser->toPlainText() != browser)
        ui->textBrowser->setText(browser);
}


void MainWindow::on_showLogs_clicked()
{
    auto logs = server->chat->showLogs();
    QString browser;
    for (const auto &log : logs){
        browser.append(QString::fromStdString(log) + "\n");
    }
    if (ui->textBrowser->toPlainText() != browser)
        ui->textBrowser->setText(browser);
}


void MainWindow::on_blockUser_clicked()
{
}


void MainWindow::on_ConnectChats_clicked()
{
    if (server->chek() != 1){
        server->init_socket();
        initServer = true;
    }
    std::string message = server->Read();

    while (message != "end") {
        message = server->Read();
    }
    if (message == "end"){
        initServer = false;
        server->exit();
    }
}

