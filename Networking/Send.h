#pragma once

//C garbage
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
//Make C garbage work
#include <unistd.h>

#include <string>
#include <iostream>
#include <tuple>

class SendData {
public:
    inline SendData(const unsigned short& port, const std::string& ip) {
        m_port = port;
        m_ip = ip;

        m_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(m_sock < 0)
            std::cerr << "Send.h: Error opening socket at line " << __LINE__ << std::endl;
            
        m_address.sin_family = AF_INET;
        m_address.sin_port = htons(m_port);
        if(inet_pton(AF_INET, m_ip.c_str(), &m_address.sin_addr))
            std::cerr << "Send.h Error getting set hostname (inet_pton) at line " << __LINE__ << std::endl;
    }

    inline bool establish() {
        if(connect(m_sock, (struct sockaddr *)&m_address, sizeof(m_address)) < 0) {
            std::cerr << "Send.h: Error connecting socket at line " << __LINE__ << std::endl;
            return false;
        }
        return true;
    }

    inline bool sendString(std::string data) {
        return send(data.c_str(), data.size());
    }

    inline auto getInfo() {
        return std::tuple<unsigned short, std::string, int>(m_port, m_ip, m_sock);
    }

private:
    unsigned short m_port;
    std::string m_ip;
    int m_sock;
    sockaddr_in m_address;

    inline bool send(const char* raw, size_t size) {
        const char* buffer = static_cast<char*>(malloc(size * sizeof(char)));
        buffer = raw;
        if(write(m_sock, buffer, size + 1) < 0) {
            std::cerr << "Send.h: Failed to write data to socket at line " << __LINE__ << std::endl;
            return false;
        }
        return true;
    }
};
