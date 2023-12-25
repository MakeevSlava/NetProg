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
    socklen_t addr_len = sizeof(server_addr);
    char buffer[4096];

    // Создание сокета
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13); // Порт службы daytime
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP адрес сервера

    // Отправка запроса на сервер
    if (sendto(sockfd, "GET TIME", strlen("GET TIME"), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
        std::cerr << "Sendto failed\n";
        return 1;
    }

    // Получение ответа от сервера
    int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (bytes_received < 0) {
        std::cerr << "Recvfrom failed\n";
        return 1;
    }

    buffer[bytes_received] = '\0'; // Добавление завершающего символа

    // Вывод полученного времени
    std::cout << "Time received from server: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}

