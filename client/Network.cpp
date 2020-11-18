#include "Network.hh"

Network *Network::_network = nullptr;

Network *Network::Get(void)
{
    if (_network == nullptr)
        _network = new Network();
    return _network;
}

Network::Network()
{
    _socket = new QTcpSocket(this);
}

void Network::Connect(const QString host, const quint16 port)
{
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sendError(QAbstractSocket::SocketError)));
    _socket->connectToHost(host, port);
    if (_socket->waitForConnected(5000))
        std::cout << "Connected" << std::endl;
    else
        std::cerr << "Not connected" << std::endl;
}

void Network::Send(const QString message)
{
    if(!message.isEmpty()) {
        _socket->write(QString (message + "\n").toUtf8());
    }
}

QString Network::Read(void)
{
    QString message = _socket->readAll();
    return message;
}

void Network::sendError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            std::cerr << "Remote host closed" << std::endl;
            break;
        case QAbstractSocket::HostNotFoundError:
            std::cerr << "Host not found" << std::endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            std::cerr << "Connection refused" << std::endl;
            break;
        default:
            std::cerr << "An error occured" << std::endl;
    }
    exit(1);
}