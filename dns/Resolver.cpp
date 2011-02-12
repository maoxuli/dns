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
// li@maoxuli.com
//
// ***************************************************************************

#include "Resolver.h"

#define DEFAULT_DNS_SERVER  "192.168.1.1"
#define DEFAULT_RETRIES     10
#define DNS_MAX_PACKET_SIZE 512

dns::Resolver::Resolver()
: m_server(DEFAULT_DNS_SERVER)
{
    init();
}

dns::Resolver::Resolver(std::string& ip)
: m_server(ip)
{
    init();
}

dns::Resolver::Resolver(const char* ip)
: m_server(ip)
{
    init();
}

dns::Resolver::~Resolver()
{
    close(m_socket);
}

bool dns::Resolver::init()
{
    m_retries = DEFAULT_RETRIES; 
    
    memset(&m_sin, 0, sizeof(m_sin));
    if(0 != inet_aton(m_server.c_str(), &m_sin.sin_addr))
    {
        m_sin.sin_port = htons(53);
        m_sin.sin_family = AF_INET;
    }
    
    if(-1 == (m_socket = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        //Log error
    }
    
    return true;
}

bool dns::Resolver::query(const char* name, int type, dns::Packet& response)
{
    std::string sName(name);
    return query(sName, type, response);
}


bool dns::Resolver::query(std::string& name, int type, dns::Packet& response)
{   
    //Question
    Question* question = new Question(name, type);

    //Request packet
    dns::Packet request(false);
    request.addQuestion(question);
    
    return query(request, response);
}

bool dns::Resolver::query(dns::Packet& request, dns::Packet& response)
{
    bool bRet = false;
    
    // Buffer for request packet encoding
    unsigned char buf[DNS_MAX_PACKET_SIZE];
    size_t size = DNS_MAX_PACKET_SIZE;
    
    // Encoding, return packet data length
    int len = request.toBuffer(buf, size);
    
    if (len <= 0)
    {
        std::cout << "Request packet encoding error, len: " << len << std::endl;
    }
    else
    {
        printf("Reuqest packet, len: %d \n", len);
        printf("id: %x %x \n", buf[0], buf[1]);
        printf("flags: %x %x \n", buf[2], buf[3]);
        printf("qdcount: %x %x \n", buf[4], buf[5]);
        printf("ancount: %x %x \n", buf[6], buf[7]);
        printf("nscount: %x %x \n", buf[8], buf[9]);
        printf("arcount: %x %x \n", buf[10], buf[11]);
        printf("name: ... \n");
        printf("type: %x %x \n", buf[len-4], buf[len-3]);
        printf("class: %x %x \n", buf[len-2], buf[len-1]);
                
        // Receiving packet
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        socklen_t addr_len = sizeof(struct sockaddr);
        
        fd_set fds;
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        
        unsigned char buf_in[DNS_MAX_PACKET_SIZE];
        size_t size_in = DNS_MAX_PACKET_SIZE;
        long len_in = 0;
        
        // Retry to send until receive response packet
        bool bSend = true;
        for (int i = 0; i < m_retries; i++)
        {
            if (m_socket <= 0)
            {
                std::cout << "Invalid socket for request sending" << std::endl;
                continue;
            }
            else if (bSend
                     && sendto(m_socket, buf, len, 0, (struct sockaddr*)&m_sin, sizeof(m_sin)) <= 0)
            {
                std::cout << "Send request packet error" << std::endl;
                continue;
            }
            else
            {
                bSend = true;
                
                // Select to receive packet
                FD_ZERO(&fds);
                FD_SET(m_socket, &fds);
                
                int rc = select(sizeof(fds)*8, &fds, NULL, NULL, &timeout);
                
                if (rc < 0 )
                {
                    std::cout << "Select to receive packet failed, stop query." << std::endl;
                    break;
                }
                else if (FD_ISSET(m_socket, &fds))
                {
                    memset(buf_in, 0, size_in);
                    len_in = recvfrom(m_socket, buf_in, size_in, 0, (struct sockaddr*)&sin, &addr_len);
                    printf("Receive data len_in: %ld \n", len_in);
                    
                    if (len_in <= 0)
                    {
                        std::cout << "Receive data failed, resend request" << std::endl;
                    }
                    else if (sin.sin_addr.s_addr != m_sin.sin_addr.s_addr)
                    {
                        std::cout << "Receive a wrong packet from different server, waiting for next..." << std::endl;                      
                        i--;
                        bSend = false;
                    }
                    else if (!response.fromBuffer(buf_in, len_in))
                    {
                        std::cout << "Decoding response packet error, resend request" << std::endl;
                    }
                    else if (response.header().id() != request.header().id())
                    {
                        std::cout << "Receive a wrong packet with different id, waiting for next..." << std::endl;                        
                        i--;
                        bSend = false;
                    }
                    else
                    {
                        std::cout << "Receive response packet successfully." << std::endl;
                        bRet = true;
                        break;
                    }
                }
            }
        }
    }
    
    return bRet;
}
