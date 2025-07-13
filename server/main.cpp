#include "server.h"

int main()
{
    std::unique_ptr<Server> server(new Server);
    std::string message;
    message = server->Read();

    while (message != "end") {
        message = server->Read();
    }
    server->exit();
    return 0;
}
