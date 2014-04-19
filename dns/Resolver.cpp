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

#include "Resolver.h"

dns::Resolver::Resolver()
: m_socket(DEFAULT_DNS_HOST, DEFAULT_DNS_PORT)
{

}

dns::Resolver::Resolver(const char* host, unsigned short port)
: m_socket(host, port)
{

}

dns::Resolver::Resolver(const std::string& host, unsigned short port)
: m_socket(host, port)
{

}

dns::Resolver::~Resolver()
{

}

bool dns::Resolver::resolve(const char* name, unsigned short type, dns::Message& response)
{
    std::string sName(name);
    return resolve(sName, type, response);
}


bool dns::Resolver::resolve(const std::string& name, unsigned short type, dns::Message& response)
{
    // Request
    dns::Message query(name, type);
    return resolve(query, response);
}

bool dns::Resolver::resolve(dns::Message& query, dns::Message& response)
{
    // Output request packet for debug
    std::cout << query.toString();
    
    // Buffer for request packet
    unsigned char buf_out[MAX_DNS_PACKET_SIZE];
    int size_out = query.toBuffer(buf_out, MAX_DNS_PACKET_SIZE);
    if (size_out <= 0)
    {
        std::cout << "Query message encoding error." << std::endl;
        return false;
    }

    // Buffer for response packet
    unsigned char buf_in[MAX_DNS_PACKET_SIZE];
    size_t size_in = 0;
    
    // Retry to send until receive response packet
    bool bRet = false;
    for (int i = 0; i < DEFAULT_RETRY_TIMES; i++)
    {
        if (m_socket.write(buf_out, size_out) <= 0)
        {
            std::cout << "Send query message error." << std::endl;
            continue;
        }
        
        size_in = m_socket.read(buf_in, MAX_DNS_PACKET_SIZE, DEFAULT_SOCKET_TIMEOUT);
        if(size_in > 0 && response.fromBuffer(buf_in, size_in))
        {
            //std::cout << "Receive response message successfully." << std::endl;
            bRet = true;
            break;
        }
    }
    
    return bRet;
}
