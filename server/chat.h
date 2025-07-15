#ifndef CHAT_H
#define CHAT_H

#pragma once
#include <vector>
#include "Users.h"
#include "Message.h"
#include "logger.h"
#include "parsing.h"

constexpr auto public_message_server = "C:/Windows/Temp/Chat/public_message_server.txt";
constexpr auto logFile = "C:/Windows/Temp/Chat/log.txt";
constexpr auto getPrvtMsg = "C:/Windows/Temp/Chat/getPrvtMsg.txt";
constexpr auto getChatMsg = "C:/Windows/Temp/Chat/getChatMsg.txt";
constexpr auto UserList = "C:/Windows/Temp/Chat/UserList.txt";	// файл для хранения логинов пользователей
constexpr auto userData = "C:/Windows/Temp/Chat/userData.txt";	// файл для хранения данных пользователей
constexpr auto user_count = "C:/Windows/Temp/Chat/user_count.txt";	// файл для хранения кол-ва зарегистрированных пользователей
constexpr auto private_message = "C:/Windows/Temp/Chat/private_message.txt";	// файл для хранения непросмотренных личных сообщений
constexpr auto public_message = "C:/Windows/Temp/Chat/public_message.txt";	// файл для хранения непрочитанных общих сообщений
constexpr auto prvt_msg_count = "C:/Windows/Temp/Chat/private_message_count.txt";   // файл для хранения кол-ва личных непрочитанных сообщений
constexpr auto pblc_msg_count = "C:/Windows/Temp/Chat/public_message_count.txt";   // файл для хранения кол-ва общих непрочитанных сообщений


extern std::string status_connect;

class Chat
{
private:
    std::vector<Users> allUsers; // все зарегистрированные пользователи
    std::string _recipient; //получатель сообщения
    std::string _sender; // отправитель сообщения
    std::string _login; // логин авторизованного пользователя
    std::string _password; // пароль авторизованного пользователя
    std::vector<Message>allMessage; // все новые приватные сообщения
    std::vector<Message>allPublicMessage; // все новые общие сообщения
    std::vector<Message>viewedMessage; // просмотренные сообщения
    bool _status = false; // если был выполнен вход статус = true, в противном случае - false.
    Logger log;
    std::shared_mutex mutex;
    std::vector<Message> _messages;
    int count_users = 0; // кол-во зарегистрированных пользователей
public:
    Chat(); // конструктор
    ~Chat(); // деструктор
    std::string getLogin() const;
    void writeUsers() const; // метод для записи данных о пользователях в файл
    void writeMessage() const; // метод для записи данных о сообщениях в файл
    void readUsers(); // метод для чтения данных о пользователях из файла
    void readPrivateMessage(); // метод для чтения личных сообщений из файла
    void readPublicMessage(); // метод для чтения общих сообщений из файла
    int getReadUsersStatus(); // метод выводит 1, если есть файл userData, иначе -1
    std::vector<std::string> getChat(); // метод выводит данные пользователя
    void getUserList();
    void getChatMessages(std::string usLog);
    std::vector<std::string> showPrvtMessages();
    std::vector<std::string> showChatMessages();
    std::vector<std::string> showLogs();
    void getPrivateMessage(std::string userName);//показать личные сообщения пользователю username
    int enter(std::string userLogin, std::string userPassword); // авторизация пользователя
    int checkUser(std::string userLogin, std::string userPassword); // прроверка корректности логина и пароля
    int registration(std::string userLogin, std::string userName, std::string userPassword); //  регистрация пользователя
    int sendPrivateMessage(std::string userLogin, std::string userRecipient, std::string text); // отправка личных сообщений
    void sendPublicMessage(std::string userLogin, std::string text); // отправка публичных сообщений
    bool getstatus(); // метод выводит статус авторизации (_status)
    void exit(); // разлогинить авторизованного пользователя
    void printMessage(std::string recipient); // вывод на экран новых сообщений
    void deletePrivateMessage(std::string recipient); // перемещение прочитанных личных сообщений в viewedMessage и их удаление из allMessage
    void deletePublicMessage(std::string recipient); // удаление прочитанных общих сообщений из allPublicMessage
};

#endif // CHAT_H
