#ifndef SERVER_H
#define SERVER_H

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "chat.h"


// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")

#define MESSAGE_LENGTH 4096 // Максимальный размер буфера для данных
#define PORT "7777" // Будем использовать этот номер порта


class Server {
private:
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    int iResult;
    int answerChat;
    std::string msg;
    bool check = true;
    Chat* chat = new Chat();
public:
    Server();
    ~Server();
    int init_socket(); // инициализация сокета
    void Write(std::string text); // отправка данных клиенту
    std::string Read(); // чтение данных от клиента
    void exit(); // закрытие сокета
};

#endif // SERVER_H
