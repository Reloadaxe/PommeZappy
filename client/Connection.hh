#ifndef _CONNECTION_HH
#define _CONNECTION_HH

#include <iostream>
#include <sockpp/tcp_connector.h>

class Connection {
    public:
        Connection(const std::string host, const int16_t port);
        const std::string Read(void) const;
        void Send(const std::string command);

    private:
        sockpp::tcp_connector _socket;
};

#endif