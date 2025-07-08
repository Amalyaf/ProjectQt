#include "startscreen.h"
#include "ui_startscreen.h"
#include "loginform.h"
#include "registrationform.h"

StartScreen::StartScreen(std::shared_ptr<Chat> dbPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    if(dbPtr) {
        m_dbPtr = dbPtr;
    }
    else {
        m_dbPtr = std::make_shared<Chat>();
    }
    ui->loginWidget->setUsers(m_dbPtr);
    ui->registerWidget->setUsers(m_dbPtr);

    connect(ui->loginWidget, &LoginForm::registerRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->loginWidget, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->loginWidget, &LoginForm::rejected, this, &StartScreen::onRejectRequested);
    connect(ui->registerWidget, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->registerWidget, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->registerWidget, &RegistrationForm::rejected, this, &StartScreen::onRejectRequested);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

int StartScreen::userId() const
{
    return m_userId;
}

QString StartScreen::userName() const
{
    return m_userName;
}

std::shared_ptr<Chat> StartScreen::getDatabase() const
{
    return m_dbPtr;
}

void StartScreen::onLoggedIn(uint userId, QString userName)
{
    m_userId = userId;
    m_userName = userName;
    accept();
}

void StartScreen::onRejectRequested()
{
    reject();
}
