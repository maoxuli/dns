// ***************************************************************************
//
// Copyright (c) 2010, MAOXU LI. All rights reserved.
//
// This copy of software is provided to you under the terms of the GNU General
// Public License version 2 as published by the Free Software Foundation. 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ***************************************************************************

#ifndef DNS_RESOLVER_H
#define DNS_RESOLVER_H

#include <dns/Message.h>
#include <dns/Network.h>

#define DEFAULT_DNS_HOST    	"8.8.8.8"
#define DEFAULT_DNS_PORT    	53
#define DEFAULT_RETRY_TIMES 	10
#define DEFAULT_SOCKET_TIMEOUT	200 // ms
#define MAX_DNS_PACKET_SIZE 	512

DNS_BEGIN
	  
class Resolver
{        
public:
    Resolver(); // Use default DNS server
    Resolver(const char* host, unsigned short port = DEFAULT_DNS_PORT); // DNS server
    Resolver(const std::string& host, unsigned short port = DEFAULT_DNS_PORT); // DNS server
    virtual ~Resolver();
                    
    bool resolve(const char* name, unsigned short type, Message& response);
    bool resolve(const std::string& name, unsigned short type, Message& response);
    bool resolve(Message& query, Message& response);
    
private:
	network::UdpSocket m_socket;
};

DNS_END

#endif