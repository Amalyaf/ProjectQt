#include "Users.h"

Users::Users()
{
    std::cout<<"Constructor Users\n";
    // _login = "-";
    // _password = "-";
    // _name = "-";
}

Users::Users(std::string login, std::string name, std::string password):
    _login(login),
    _name(name),
    _password(password)
{
std::cout<<"Copy constructor Users\n";
}

void Users::setUser()
{
    std::cout << "Введите логин: \n";
    std::cin >> _login;
    std::cout << "Введите пароль: \n";
    std::cin >> _password;
    std::cout << "Введите имя: \n";
    std::cin >> _name;
}

void Users::setLogin(std::string lgn)
{
    std::cout<<"SetLogin\n";
    _login = lgn;
}

void Users::setPassword(std::string pswd)
{
    std::cout<<"SetPassword\n";
    _password = pswd;
}

void Users::setName(std::string nm)
{
    std::cout<<"SetName\n";
    _name = nm;
}

std::string Users::getLogin()
{
    return _login;
}

std::string Users::getPassword()
{
    return _password;
}

std::string Users::getName()
{
    return _name;
}

bool Users::operator==(const Users& user)
{
    return user._login == _login;
}

std::ostream& operator<<(std::ostream& output, const Users& user)
{
    output << "Логин пользователя: " << user._login << '\n' <<
        "Пароль: " << user._password << '\n' <<
        "Имя: " << user._name << "\n\n";
    return output;
}
