//
//  Network.cpp
//
//  Created by Maoxu Li on 8/10/10.
//  Copyright (c) 2010 LIM Labs. All rights reserved.
//

#include "Network.h"
#include <cassert>

NETWORK_BEGIN

UdpSocket::UdpSocket()
{
    memset(&_sin, 0, sizeof(_sin));
	_sin.sin_family = AF_INET;

    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	assert(_socket != INVALID_SOCKET);
}

UdpSocket::UdpSocket(const std::string& host, unsigned short port)
{
    memset(&_sin, 0, sizeof(_sin));
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sin.sin_addr.s_addr = inet_addr(host.c_str());
 
    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	assert(_socket != INVALID_SOCKET);
}

UdpSocket::~UdpSocket()
{
#if defined(_WIN32)
    int error = WSAGetLastError();
    closesocket(_socket);
    WSASetLastError(error);
#else
    int error = errno;
    close(_socket);
    errno = error;
#endif
}

long UdpSocket::write(char* buf, int size)
{
	return ::sendto(_socket, buf, size, 0, (struct sockaddr*)&_sin, sizeof(_sin));
}

long UdpSocket::read(char* buf, int size)
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    socklen_t len = sizeof(sin);
	return recvfrom(_socket, buf, size, 0, (struct sockaddr*)&sin, &len);
}

long UdpSocket::read(char* buf, int size, int timeout)
{
    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
	
	fd_set fds;
    FD_ZERO(&fds);
    FD_SET(_socket, &fds);
    
    int rc = select(sizeof(fds)*8, &fds, NULL, NULL, &tv);
    if(rc > 0 && FD_ISSET(_socket, &fds))
    {
	    struct sockaddr_in sin;
	    memset(&sin, 0, sizeof(sin));
	    socklen_t len = sizeof(sin);
		return recvfrom(_socket, buf, size, 0, (struct sockaddr*)&sin, &len);
	}
	
	return -1;
}

NETWORK_END
