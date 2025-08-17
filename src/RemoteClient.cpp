#include "WiFiManager.h"
#include "UserManager.h"
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(server, 3);

    std::cout << "Server running on http://localhost:8080\n";

    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET client = accept(server, (sockaddr*)&clientAddr, &clientSize);

        char buffer[256];
        int received = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            std::string input(buffer); // format: "username|SSID"
            std::string username = input.substr(0, input.find('|'));
            std::string ssid = input.substr(input.find('|') + 1);

            UserManager users;
            WiFiManager wifi;
            std::string response;
            if (users.isAuthorized(username)) {
                bool connected = wifi.connectToNetwork(ssid);
                response = connected ? "SUCCESS" : "FAILURE";
            }
            else {
                response = "UNAUTHORIZED";
            }
            send(client, response.c_str(), response.size(), 0);
        }

        closesocket(client);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
