#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::setUsers(std::shared_ptr<Chat> dbPtr)
{
    m_dbPtr = dbPtr;
}

void LoginForm::on_buttonBox_accepted()
{
    auto userId = m_dbPtr->enter(ui->loginEdit->text().toStdString(),
                                         ui->passwordEdit->text().toStdString());

    switch(userId)
    {
    case -1:
        QMessageBox::critical(this, tr("Error"), tr("A user with this login does not exist"));
        return;
    case -2:
        QMessageBox::critical(this, tr("Error"), tr("Password is wrong"));
        return;
    default:
        emit accepted(userId, ui->loginEdit->text());
    }
}

void LoginForm::on_registrationPushButton_clicked()
{
    emit registerRequested();
}

void LoginForm::on_buttonBox_rejected()
{
    emit rejected();
}

