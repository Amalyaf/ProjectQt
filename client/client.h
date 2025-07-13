#ifndef CLIENT_H
#define CLIENT_H
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <filesystem>
#include <fstream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define MESSAGE_LENGTH 4096 // Максимальный размер буфера для данных
#define PORT "7777" // Будем использовать этот номер порта


constexpr auto getPrvtMsg = "C:/Windows/Temp/Chat/getPrvtMsg.txt";
constexpr auto getChatMsg = "C:/Windows/Temp/Chat/getChatMsg.txt";
constexpr auto UserList = "C:/Windows/Temp/Chat/UserList.txt";	// файл для хранения логинов пользователей

class Client {
private:
private:
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;
    int answer; // ответ сервера
    std::string status;
    std::string message;
    std::string controlWord;
    std::string sendText;

public:
    Client();
    ~Client();
    int init();
    void Write(std::string msg);
    std::string Read();
    void close_socket();
    int registration(std::string userLogin, std::string userName, std::string userPassword); //  регистрация пользователя
    int enter(std::string userLogin, std::string userPassword); // авторизация пользователя
    void sendPrivateMessage(std::string userLogin, std::string userRecipient, std::string text); // отправка личных сообщений
    void sendPublicMessage(std::string userLogin, std::string text); // отправка публичных сообщений
    std::vector<std::string> getUserList();
    std::vector<std::string> getChatMessages(std::string usLog);
    std::vector<std::string> getPrivateMessage(std::string userName);//показать личные сообщения пользователю username
};

#endif // CLIENT_H
