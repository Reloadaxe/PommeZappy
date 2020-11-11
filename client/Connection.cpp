#include "Connection.hh"

Connection::Connection(const std::string host, const int16_t port)
{
    if (!_socket.connect(sockpp::inet_address(host, port))) {
        std::cerr << _socket.last_error_str() << std::endl;
    }
}

const std::string Connection::Read(void) const
{
    return "yes";
}

void Connection::Send(const std::string command)
{
    (void)command;
}