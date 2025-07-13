#include "Client.h"

Client::Client()
{
    init();
}

Client::~Client()
{
    close_socket();
}

int Client::init()
{
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("localhost", PORT, &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        std::cout << "Unable to connect to server!\n";
        WSACleanup();
        return 1;
    }
    return 0;
}

void Client::Write(std::string msg)
{
    int bytes = send(ConnectSocket, msg.c_str(), msg.size(), 0);
}

std::string Client::Read()
{
    message.clear();
    // Буфер для получения данных от сервера
    char buffer[MESSAGE_LENGTH];
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(ConnectSocket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';  // Завершаем строку нулевым символом
        message = buffer;
    }
    return message;
}

void Client::close_socket()
{
    Write("end");
    std::cout << "Close socket!" << std::endl;
    closesocket(ConnectSocket);
    WSACleanup();
}

int Client::registration(std::string userLogin, std::string userName, std::string userPassword)
{
    controlWord = "registration";
    sendText = controlWord + " " + userLogin + " " + userName + " " + userPassword;
    Write(sendText);

    std::string answerServer;
    answerServer = Read();
    int n = atoi(answerServer.c_str());
    return n;
}

int Client::enter(std::string userLogin, std::string userPassword)
{
    controlWord = "enter";
    sendText = controlWord + " " + userLogin + " " + " " + userPassword;
    Write(sendText);
    std::string answerServer;
    answerServer = Read();
    int n = atoi(answerServer.c_str());
    return n;
}

void Client::sendPrivateMessage(std::string userLogin, std::string userRecipient, std::string text)
{
    controlWord = "sendPrivateMessage";
    sendText = controlWord + " " + userLogin + " " + userRecipient + " " + text;
    Write(sendText);
}

void Client::sendPublicMessage(std::string userLogin, std::string text)
{
    controlWord = "sendPublicMessage";
    sendText = controlWord + " " + userLogin + " " + " " + text;
    Write(sendText);
}

std::vector<std::string> Client::getUserList()
{
    controlWord = "getUserList";
    sendText = controlWord;
    Write(sendText);
    Read();

    std::fstream file = std::fstream(UserList, std::ios::in);
    std::vector<std::string> strings;

    if (file.is_open()) {
        std::string str;
        while (file >> str) { strings.push_back(str); }
    }
    file.close();
    return strings;
}

std::vector<std::string> Client::getChatMessages(std::string usLog)
{
    controlWord = "getChatMessages";
    sendText = controlWord + " " + usLog;
    Write(sendText);
    Read();

    std::fstream file = std::fstream(getChatMsg, std::ios::in);
    std::vector<std::string> strings;

    if (file.is_open()) {
        std::string str;
        while (std::getline(file, str)) { strings.push_back(str); }
        }
    file.close();
    return strings;
}

std::vector<std::string> Client::getPrivateMessage(std::string userName)
{
    controlWord = "getPrivateMessage";
    sendText = controlWord + " " + userName;
    Write(sendText);
    Read();

    std::fstream file = std::fstream(getPrvtMsg, std::ios::in);
    std::vector<std::string> strings;

    if (file.is_open()) {
        std::string str;
        while (std::getline(file, str)) { strings.push_back(str);}
    }
    file.close();
    return strings;
}
