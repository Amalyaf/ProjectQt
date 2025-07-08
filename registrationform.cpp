#include "registrationform.h"
#include "ui_registrationform.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::setUsers(std::shared_ptr<Chat> dbPtr)
{
    m_dbPtr = dbPtr;
}

void RegistrationForm::on_loginButton_clicked()
{
    emit loginRequested();
}


void RegistrationForm::on_buttonBox_accepted()
{
    if(ui->passwordEdit->text() != ui->passwordConfirmEdit->text())
    {
        QMessageBox::critical(this, tr("Error"), tr("Passwords not match"));
        return;
    }

    auto userId = m_dbPtr->registration(ui->loginEdit->text().toStdString(),
                                    ui->nameEdit->text().toStdString(),
                                    ui->passwordEdit->text().toStdString());

    switch(userId)
    {
    case -1:
        QMessageBox::critical(this, tr("Error"), tr("Incorect login"));
        return;
    case -2:
        QMessageBox::critical(this, tr("Error"), tr("Login already exists"));
        return;
    default:
        emit accepted(userId, ui->loginEdit->text());
    }
}


void RegistrationForm::on_buttonBox_rejected()
{
    emit rejected();
}

