#include "server.h"


Server::Server()
{
    init_socket();
}

Server::~Server()
{

}


int Server::init_socket()
{
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, PORT, &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}


void Server::Write(std::string text)
{
    //msg.clear();
    // Ввод сообщения от сервера
    //std::cout << "Enter the message you want to send to the client: " << std::endl;
    //std::getline(std::cin, msg);  // Используем getline для ввода строки с пробелами

    // Отправка данных клиенту
    int bytes_sent = send(ClientSocket, text.c_str(), text.size(), 0);
    if (bytes_sent < 0) {
        std::cout << "Failed to send data to the client!" << std::endl;
    }
    else {
        std::cout << "Succes to send data to the client! " << std::endl;
    }
    text.clear();
}

std::string Server::Read()
{
    msg.clear();
    // Чтение данных от клиента
    char buffer[MESSAGE_LENGTH];
    //memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(ClientSocket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {

        buffer[bytes_received] = '\0';  // Завершаем строку нулевым символом
        msg = buffer;
        std::string controlWord = msg.substr(0, msg.find(" "));

        if (controlWord == "registration"){
            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;
            std::string name;
            std::string password;

            login = words[1];
            name = words[2];
            password = words[3];

            answerChat = chat->registration(login, name, password);

            std::cout<<"Registration in server"<<std::endl;
            std::cout<<"answerChat: "<<answerChat<<std::endl;

            switch(answerChat){
            case -1:
                Write("-1");
                break;
            case -2:
                Write("-2");
                break;
            case 0:
                Write("0");
                break;
            }
        }

        else if (controlWord == "enter"){

            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;
            std::string password;

            login = words[1];
            password = words[2];

            answerChat = chat->enter(login, password);

            switch(answerChat){
            case -1:
                Write("-1");
                break;
            case -2:
                Write("-2");
                break;
            case 0:
                Write("0");
                break;
            }
        }

        else if (controlWord == "sendPrivateMessage"){

            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;
            std::string recipient;
            std::string text;

            login = words[1];
            recipient = words[2];
            for (int i = 3; i < words.size(); i++){
                text += words[i];
                text += " ";
            }

            chat->sendPrivateMessage(login, recipient, text);
        }

        else if (controlWord == "sendPublicMessage"){

            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;
            std::string text;

            login = words[1];
            for (int i = 2; i < words.size(); i++){
                text += words[i];
                text += " ";
            }

            chat->sendPublicMessage(login, text);
        }

        else if (controlWord == "getChatMessages"){

            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;

            login = words[1];
            chat->getChatMessages(login);
            Write("0");
        }

        else if (controlWord == "getPrivateMessage"){

            std::vector<std::string> words;
            std::istringstream stream(msg);

            // Read values into vector.
            copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(),
                 back_inserter(words));

            std::string login;

            login = words[1];
            chat->getPrivateMessage(login);
            Write("0");
        }

        else if (controlWord == "getUserList"){
            chat->getUserList();
            Write("0");
        }
    }
    return msg;
}

void Server::exit()
{
    std::cout << "Exit" << std::endl;
    closesocket(ClientSocket);
}



