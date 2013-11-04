#include "truck_client.h"

const char *TruckClient::PLAYER1_PORT = "4321";
const char *TruckClient::PLAYER2_PORT = "4322";
const char *TruckClient::DEFAULT_HOST = "localhost";
const char *TruckClient::DEFAULT_PORT = PLAYER1_PORT;

TruckClient::TruckClient() : _socketfd(-1), _debug(false) {};

void TruckClient::setDebug(bool debug) {
    _debug = debug;
}

void TruckClient::conn(const char *host, const char *port) {
    int status;
    struct addrinfo host_info;
    struct addrinfo *host_info_list;

    memset(&host_info, 0, sizeof host_info);
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(host, port, &host_info, &host_info_list);
    if (status != 0) {
        throw(TruckClientException(gai_strerror(status)));
    }

    this->_socketfd = socket(
        host_info_list->ai_family,
        host_info_list->ai_socktype,
        host_info_list->ai_protocol
    );
    if (this->_socketfd == -1) {
        throw(TruckClientException("socket error"));
    }

    status = connect(
        this->_socketfd,
        host_info_list->ai_addr,
        host_info_list->ai_addrlen
    );
    if (status == -1) {
        throw(TruckClientException("connect error"));
    }
}

ServerResposePackage TruckClient::getTruckData() {
    if(_socketfd == -1) {
        throw(TruckClientException("socket error"));
    }

    const char *msg = "r\r\n";
    int len = strlen(msg);

    send(this->_socketfd, msg, len, 0);
    ssize_t bytes_recieved;
    char incoming_data_buffer[200];
    bytes_recieved = recv(this->_socketfd, incoming_data_buffer, 200, 0);
    if (bytes_recieved == 0) {
        if(_debug) std::cout << "host shut down." << std::endl;
        return ServerResposePackage();
    }
    if (bytes_recieved == -1) {
        if(_debug) std::cout << "recieve error!" << std::endl;
        return ServerResposePackage();
    }

    return _parseTruckData((char *)incoming_data_buffer);
}

void TruckClient::sendTruckInstruction(double instruction) {
    if(_socketfd == -1) {
        throw(TruckClientException("socket error"));
    }

    std::ostringstream msg;
    msg << instruction << "\r\n";
    const char *cmsg = msg.str().c_str();
    if(_debug) std::cout << "Sending: " << cmsg << std::endl;
    int s = send(this->_socketfd, cmsg, strlen(cmsg), 0);
    if(_debug) std::cout << "message sent: " << s << std::endl;
}

inline ServerResposePackage TruckClient::_parseTruckData(char *raw_data) {
    int i, j;
    char buff[50];
    ServerResposePackage response;

    i = 0;
    for(j = 0, buff[j] = raw_data[i];
        raw_data[i] != '\t';
        i++, j++, buff[j] = raw_data[i]);
    response.x = atof(buff);
    i++;

    for(j = 0, buff[j] = raw_data[i];
        raw_data[i] != '\t';
        i++, j++, buff[j] = raw_data[i]);
    response.y = atof(buff);
    i++;

    for(j = 0, buff[j] = raw_data[i];
        raw_data[i] != '\0';
        i++, j++, buff[j] = raw_data[i]);
    response.angle = atof(buff);

    return response;
}
