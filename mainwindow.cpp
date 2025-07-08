#include "mainwindow.h"
#include "startscreen.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>

int MainWindow::kInstanceCount = 0;

MainWindow::MainWindow(int userId, QString userName, std::shared_ptr<Chat> dbPtr, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId(userId),
    m_userName(userName)
{
    ui->setupUi(this);
    kInstanceCount++;
    if(dbPtr) {
        m_dbPtr = dbPtr;
    }
    else {
        m_dbPtr = std::make_shared<Chat>();
    }

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    kInstanceCount--;
    if(kInstanceCount <= 0)
        qApp->exit(0);
}

MainWindow *MainWindow::createClient(std::shared_ptr<Chat> dbPtr)
{
    StartScreen s(dbPtr);
    auto result = s.exec();
    if (result == QDialog::Rejected)
    {
        return nullptr;
    }

    auto w = new MainWindow(s.userId(), s.userName(), s.getDatabase());
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{
    m_dbPtr->sendPublicMessage(m_userName.toStdString(), ui->messageLineEdit->text().toStdString());
}


void MainWindow::on_privateMessageSendButton_clicked()
{
    QDialog dial(this);
    dial.setModal(true);
    auto *l = new QVBoxLayout();
    dial.setLayout(l);
    auto userListWgt = new QListWidget(&dial);
    l->addWidget(userListWgt);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
    l->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);

    auto userList = m_dbPtr->getUserList();
    for (auto user : userList){
        userListWgt->addItem(QString::fromStdString(user));
    }

    userListWgt->setCurrentRow(0);

    auto result = dial.exec();
    if (result == QDialog::Accepted && userListWgt->currentItem()){

        m_dbPtr->sendPrivateMessage(m_userName.toStdString(),
                                   userListWgt->currentItem()->text().toStdString(),
                                   ui->messageLineEdit->text().toStdString());
    }
}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(m_dbPtr);
    if(w)
        w->show();
}


void MainWindow::on_actionClose_this_client_triggered()
{
    this->close();
}

void MainWindow::updateChats()
{
    auto chatMessages = m_dbPtr->getChatMessages(m_userName.toStdString());
    QString chat;
    for (const auto &msg : chatMessages){
        chat.append(QString::fromStdString(msg) + "\n");
    }

    if (ui->commonChatBrowser->toPlainText() != chat)
        ui->commonChatBrowser->setText(chat);

    chat.clear();

    auto privateMessages = m_dbPtr->getPrivateMessage(m_userName.toStdString());
    for (auto &msg : privateMessages){
        chat.append(QString::fromStdString(msg) + "\n");
        }

    if (ui->privateChatBrowser->toPlainText() != chat)
        ui->privateChatBrowser->setText(chat);
}

