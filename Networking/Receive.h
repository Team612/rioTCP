#pragma once

//C garbage
#include <sys/socket.h>
#include <arpa/inet.h>
//Make C garbage work
#include <unistd.h>

#include <string>
#include <iostream>
#include <tuple>

class ReceiveData {
public:
    inline ReceiveData(const unsigned short& port) {
        m_port = port;

        m_sock = socket(AF_INET, SOCK_STREAM, 0);
        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(m_port);
        m_address.sin_addr.s_addr = INADDR_ANY;

        if(m_sock < 0)
            std::cerr << "Receive.h: Failed to open socket at line " << __LINE__ << std::endl;
    }

    inline bool establish() {
        if (bind(m_sock, (struct sockaddr *) &m_address, sizeof(m_address)) < 0) {
            std::cerr << "Receive.h: failed to bind port at line " << __LINE__ << std::endl;
            return false;
        }
        listen(m_sock, 5);
        return true;
    }

    inline std::string receiveChunk(size_t size) {
        char* buffer = static_cast<char*>(malloc(size * sizeof(char)));

        size_t len = sizeof(m_client);
        int clientfd = accept(m_sock, (struct sockaddr*)(&m_client), &len);
        if(clientfd < 0) {
            std::cerr << "Receive.h: Error accepting socket at line " << __LINE__ << std::endl;
            return "";
        }
        recv(clientfd, buffer, size, MSG_WAITALL);
        return std::string(buffer);
    }

    inline auto get_info() {
        return std::tuple<unsigned short, int>(m_port, m_sock);
    }
private:
    unsigned short m_port;
    int m_sock;
    sockaddr_in m_address, m_client;
};
