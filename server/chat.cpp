#include "Chat.h"
#include <algorithm>
#include "bad_login.h"
#include "bad_password.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <shared_mutex>
#include <chrono>


std::string status_connect = "No";
using namespace std::chrono_literals;

Chat::Chat()
{
    //// если есть файл с данными ранее зарегистрированных пользователей, то вызвать методы для считывания данных из файлов
    if (getReadUsersStatus() == 1) {
        readUsers();
        readPrivateMessage();
        readPublicMessage();
    }
    std::thread t1(&Logger::WriteLog, std::ref(log), "Chat opened successfully!");
    std::thread t2(&Logger::ReadLog, std::ref(log));
    t1.join();
    t2.join();
}

Chat::~Chat() {
    deletePrivateMessage(_login);
    deletePublicMessage(_login);
    writeUsers(); // метод для записи данных зарегистрированных пользователей в файл
    writeMessage(); // метод для записи личных и публичных сообщений в отдельные файлы
    std::thread t1(&Logger::WriteLog, std::ref(log), "Закрытие чата!\n");
    std::thread t2(&Logger::ReadLog, std::ref(log));
    t1.join();
    t2.join();
}

std::string Chat::getLogin() const
{
    return _login;
}


void Chat::getPrivateMessage(std::string userName)
{
    std::vector<std::string> strings;
    for (auto &m : allMessage)
    {
        if(userName == m.getRecipient()){
            if (userName == m.getSender()){
                strings.push_back("<Self message>: " + m.getText());
            }
            else {
                strings.push_back("<" + m.getSender() + "> say to you: " + m.getText());
            }
        }
        else if (userName != m.getRecipient() && userName == m.getSender()){
            strings.push_back("Message to <" + m.getRecipient() + ">: " + m.getText());
        }
    }

    std::fstream file = std::fstream(getPrvtMsg, std::ios::in | std::ios::out | std::ios::trunc);
    for (int i = 0; i < strings.size(); i++) {
        file << strings[i]<<std::endl;
    }
    file.close();
}


void Chat:: getChatMessages(std::string usLog)
{
    std::vector<std::string> strings;
    for (auto &m: allPublicMessage)
    {
        if (usLog == m.getRecipient()){
            if (usLog == m.getSender()){
                strings.push_back("<You sent>: " + m.getText());
            }
            else {
                strings.push_back("<" + m.getSender() + ">: " + m.getText());
            }
        }
    }

    std::fstream file = std::fstream(getChatMsg, std::ios::in | std::ios::out | std::ios::trunc);
    for (int i = 0; i < strings.size(); i++) {
        file << strings[i]<<std::endl;
    }
    file.close();
}

void Chat::getUserList()
{
    std::fstream file = std::fstream(UserList, std::ios::in | std::ios::out | std::ios::trunc);
    for (int i = 0; i < allUsers.size(); i++) {
        file << allUsers[i]._login << "\n";
    }
    file.close();
}

int Chat::enter(std::string userLogin, std::string userPassword)
{
    try
    {
        _login = userLogin;
        Users user;
        user._login = _login;

        std::thread t1(&Logger::WriteLog, std::ref(log), "Попытка входа под учётной записью " + _login);
        t1.join();

        // При чтении из файла
        std::vector<Users>::iterator result = find(allUsers.begin(), allUsers.end(), user);
        if (result == allUsers.end())
        {
            throw BadLogin();
        }

        else
        {
            user = *result;
            _password = userPassword;

            // При чтении из файла
            if (user._password != _password)
            {
                throw BadPassword();
            }
            else
            {
                _status = true;
                std::thread t1(&Logger::WriteLog, std::ref(log), "Выполнен вход под учётной записью пользователя " + _login);
                t1.join();
                return 0;
            }
        }
    }
    catch (BadLogin& e)
    {
        log.WriteLog("Пользователь с логином " + _login + " не существует");
        return -1;
    }
    catch (BadPassword& e)
    {
        log.WriteLog("Введён неправильный пароль для учётной записи пользователя " + _login);
        return -2;
    }
}

int Chat::checkUser(std::string userLogin, std::string userPassword)
{
    _login = userLogin;
    Users user;
    user._login = _login;

    std::thread t1(&Logger::WriteLog, std::ref(log), "Попытка входа под учётной записью " + _login);
    t1.join();

    // При чтении из файла
    std::vector<Users>::iterator result = find(allUsers.begin(), allUsers.end(), user);
    if (result == allUsers.end())
    {
        return -1;
    }

    else
    {
        user = *result;
        _password = userPassword;

        // При чтении из файла
        if (user._password != _password)
        {
            log.WriteLog("Введён неправильный пароль для учётной записи пользователя " + _login);
            return -2;
        }
        else
        {
            _status = true;
            std::thread t1(&Logger::WriteLog, std::ref(log), "Выполнен вход под учётной записью пользователя " + _login);
            t1.join();
            return 0;
        }
    }

    return 0;
}

int Chat::registration(std::string userLogin, std::string userName, std::string userPassword)
{
    Users user(userLogin, userName, userPassword);

    std::vector<Users>::iterator result = find(allUsers.begin(), allUsers.end(), user);

    std::thread t1(&Logger::WriteLog, std::ref(log), "Регистрация нового пользователя");
    t1.join();

    if (!correctName(userLogin)) {
        std::cout<<"1 if"<<std::endl;
        return -1;
    }

    // При чтении из файла
    if (result != allUsers.end())
    {
        std::thread t1(&Logger::WriteLog, std::ref(log), "Пользователь с логином " + userLogin + " уже существует!");
        t1.join();
        return -2;

    }
    else
    {
        count_users++;
        allUsers.push_back(user);
        writeUsers();
        std::thread t1(&Logger::WriteLog, std::ref(log), "Пользователь с логином " + userLogin + " успешно зарегистрирован");
        t1.join();
        return 0;
    }
}

int Chat::sendPrivateMessage(std::string userLogin, std::string userRecipient, std::string text)
{
    _sender = userLogin;
    _recipient = userRecipient;
    Users user;
    user._login = _recipient;
    std::vector<Users>::iterator result = find(allUsers.begin(), allUsers.end(), user);
    if (result == allUsers.end())
    {
        return -1;
    }

    else
    {
        Message message;
        message._recipient = _recipient;
        message._sender = _sender;
        message.setMessage(text);
        allMessage.push_back(message);
        std::thread t1(&Logger::WriteLog, std::ref(log), "Пользователь " + _sender + " успешно отправил сообщение пользователю " + _recipient);
        t1.join();
        return 1;
    }
}

void Chat::sendPublicMessage(std::string userLogin, std::string text)
{
    Message message;
    message._sender = userLogin;
    message.setMessage(text);

    for (std::vector<Users>::iterator it = allUsers.begin(); it < allUsers.end(); it++)
    {
            message._recipient = it->_login;
            allPublicMessage.push_back(message);
    }

    viewedMessage.push_back(message);
    std::thread t1(&Logger::WriteLog, std::ref(log), "Пользователь " + userLogin + " успешно отправил групповое сообщение");
    t1.join();
}

void Chat::printMessage(std::string recipient)
{
    int count = 0;
    for (std::vector<Message>::iterator it = allMessage.begin(); it < allMessage.end(); it++)
    {
        if (it->_recipient == recipient)
        {
            count++;
        }

    }
    if (count != 0)
    {
        deletePrivateMessage(recipient);
    }
    count = 0;
    for (std::vector<Message>::iterator it = allPublicMessage.begin(); it < allPublicMessage.end(); it++)
    {
        if (it->_recipient == recipient)
        {
            count++;
        }

    }
    if (count != 0)
    {
        deletePublicMessage(recipient);
    }
}


void Chat::deletePrivateMessage(std::string recipient)
{
    for (std::vector<Message>::iterator it = allMessage.begin(); it < allMessage.end();)
    {
        if (it->_recipient == recipient)
        {
            viewedMessage.push_back(*it);
            it = allMessage.erase(it);
        }
        else
            ++it;
    }
}

void Chat::deletePublicMessage(std::string recipient)
{
    for (std::vector<Message>::iterator it = allPublicMessage.begin(); it < allPublicMessage.end();)
    {
        if (it->_recipient == recipient)
        {
            it = allPublicMessage.erase(it);
        }
        else
            ++it;
    }
}


bool Chat::getstatus()
{
    return _status;
}

void Chat::exit()
{
    _status = false;
    _login.clear();
    _password.clear();
}

void Chat::readUsers() {

    std::fstream file = std::fstream(userData, std::ios::in);

    if (!file)
    {
        return;
    }

    const std::string delimiter = ":";

    if (file.is_open()) {
        std::string line;
        std::string title;
        std::string value;
        int user_cnt = 0;

        std::fstream user_cnt_file(user_count, std::ios::in);
        if (user_cnt_file.is_open()) {
            std::string line;
            std::getline(user_cnt_file, line);
            user_cnt = stoi(line);
        }
        for (int i = 0; i < user_cnt; i++) {
            Users user;
            int count = 0;
            while (count < 3 && getline(file, line)) {
                size_t delimiterPosition = line.find(delimiter);
                if (delimiterPosition > 0) {
                    title = line.substr(0, delimiterPosition);
                    value = line.substr(delimiterPosition + 1);

                    if (title == "Name") {
                        user._name = value;
                    }
                    else if (title == "Login") {
                        user._login = value;
                    }
                    else if (title == "Password") {
                        user._password = value;
                    }
                    count++;
                }
            }
            allUsers.push_back(user);
        }
        file.close();
    }
}


int Chat::getReadUsersStatus() {

    std::fstream file(userData, std::ios::in);
    if (!file) {
        return -1;
    }

    std::fstream user_cnt_file(user_count, std::ios::in);
    if (!user_cnt_file) {
        return -1;
    }

    else if (user_cnt_file.is_open()) {
        std::string line;
        int user_cnt = 0;
        getline(user_cnt_file, line);
        user_cnt = stoi(line);
        if (user_cnt == 0) {
            return -1;
        }
    }
    return 1;
}


void Chat::writeUsers() const {

    std::fstream file = std::fstream(userData, std::ios::in | std::ios::out | std::ios::trunc);
    for (int i = 0; i < allUsers.size(); i++) {
        file << "Name:" << allUsers[i]._name << "\n";
        file << "Login:" << allUsers[i]._login << "\n";
        file << "Password:" << allUsers[i]._password << "\n";
    }

    file.close();

    std::fstream user_cnt_file = std::fstream(user_count, std::ios::in | std::ios::out | std::ios::trunc);

    user_cnt_file << allUsers.size();
    user_cnt_file.close();
}

void Chat::writeMessage() const {

    std::fstream file_prvt_msg = std::fstream(private_message, std::ios::in | std::ios::out | std::ios::trunc);

    for (int i = 0; i < allMessage.size(); i++) {
        file_prvt_msg << "Recipient:" << allMessage[i]._recipient << "\n";
        file_prvt_msg << "Sender:" << allMessage[i]._sender << "\n";
        file_prvt_msg << "Message:" << allMessage[i]._message << "\n";
    }
    file_prvt_msg.close();

    std::fstream file_pblc_msg = std::fstream(public_message, std::ios::in | std::ios::out | std::ios::trunc);

    for (int i = 0; i < allPublicMessage.size(); i++) {
        file_pblc_msg << "Recipient:" << allPublicMessage[i]._recipient << "\n";
        file_pblc_msg << "Sender:" << allPublicMessage[i]._sender << "\n";
        file_pblc_msg << "Message:" << allPublicMessage[i]._message << "\n";
    }

    file_pblc_msg.close();

    std::fstream prvt_msg_cnt_file = std::fstream(prvt_msg_count, std::ios::in | std::ios::out | std::ios::trunc);

    prvt_msg_cnt_file << allMessage.size();
    prvt_msg_cnt_file.close();

    std::fstream pblc_msg_cnt_file = std::fstream(pblc_msg_count, std::ios::in | std::ios::out | std::ios::trunc);

    pblc_msg_cnt_file << allPublicMessage.size();
    pblc_msg_cnt_file.close();
}

void Chat::readPrivateMessage() {

    std::fstream file = std::fstream(private_message, std::ios::in);

    if (!file) {
        return;
    }

    const std::string delimiter = ":";

    if (file.is_open()) {
        std::string line;
        std::string title;
        std::string value;
        int prvt_msg_cnt = 0;

        std::fstream prvt_msg_cnt_file(prvt_msg_count, std::ios::in);
        if (prvt_msg_cnt_file.is_open()) {
            std::string line;
            std::getline(prvt_msg_cnt_file, line);
            prvt_msg_cnt = stoi(line);
        }
        for (int i = 0; i < prvt_msg_cnt; i++) {
            Message msg;
            int count = 0;
            while (count < 3 && getline(file, line)) {
                size_t delimiterPosition = line.find(delimiter);
                if (delimiterPosition > 0) {
                    title = line.substr(0, delimiterPosition);
                    value = line.substr(delimiterPosition + 1);

                    if (title == "Recipient") {
                        msg._recipient = value;
                    }
                    else if (title == "Sender") {
                        msg._sender = value;
                    }
                    else if (title == "Message") {
                        msg._message = value;
                    }
                    count++;
                }
            }
            allMessage.push_back(msg);
        }
        file.close();
    }
}


void Chat::readPublicMessage() {
    std::fstream file = std::fstream(public_message, std::ios::in);

    if (!file) {
        return;
    }

    const std::string delimiter = ":";

    if (file.is_open()) {
        std::string line;
        std::string title;
        std::string value;
        int pblc_msg_cnt = 0;

        std::fstream pblc_msg_cnt_file(pblc_msg_count, std::ios::in);
        if (pblc_msg_cnt_file.is_open()) {
            std::string line;
            std::getline(pblc_msg_cnt_file, line);
            pblc_msg_cnt = stoi(line);
        }
        for (int i = 0; i < pblc_msg_cnt; i++) {
            Message msg;
            int count = 0;
            while (count < 3 && getline(file, line)) {
                size_t delimiterPosition = line.find(delimiter);
                if (delimiterPosition > 0) {
                    title = line.substr(0, delimiterPosition);
                    value = line.substr(delimiterPosition + 1);

                    if (title == "Recipient") {
                        msg._recipient = value;
                    }
                    else if (title == "Sender") {
                        msg._sender = value;
                    }
                    else if (title == "Message") {
                        msg._message = value;
                    }
                    count++;
                }
            }
            allPublicMessage.push_back(msg);
        }
        file.close();
    }
}
