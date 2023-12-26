#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[4096];

    // Создание сокета
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7); // Порт службы echo
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP адрес сервера

    // Подключение к серверу
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    // Отправка данных на сервер
    const char* message = "Echo server says hello to you!";
    send(sockfd, message, strlen(message), 0);
    std::cout << "Message sent to server: " << message << std::endl;

    // Получение ответа от сервера
    int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        std::cerr << "Recv failed\n";
        return 1;
    }

    buffer[bytes_received] = '\0'; // Добавление завершающего символа

    // Вывод полученного сообщения
    std::cout << "Message received from server: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}

