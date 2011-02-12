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

#include "Header.h"

dns::Header::Header(bool bResponse)
: m_qdcount(0)
, m_ancount(0)
, m_nscount(0)
, m_arcount(0)
{
    m_id = 0;
    memset(&m_flags, 0, sizeof(m_flags));
    m_flags.qr = bResponse;
    
    if (!bResponse) 
    {
        // Create ID
        assignID();
        
        // Recursive request
        m_flags.rd = 1;
    }
}

dns::Header::~Header()
{
    
}

// Set ID or create a random ID 
int dns::Header::assignID(int id /*= -1*/)
{
    if (id < 0)
    {
        m_id = (int)(65536 * (rand() / (RAND_MAX + 1.0)));
    }
    else
    {
        m_id = id;
    }
    
    return m_id;
}

int dns::Header::toBuffer(unsigned char* buf, size_t size)
{
    int nLen = -1;

    if (size < sizeof(header_fmt))
    {
        //Error log
    }
    else
    {
        header_fmt h;
        h.id = htons(m_id);
        printf("Request Header::ID %d - %x\n", m_id, h.id);
        h.qdcount = htons(m_qdcount);
        h.ancount = htons(m_ancount);
        h.nscount = htons(m_nscount);
        h.arcount = htons(m_arcount);
        flags_enc((unsigned char*)&h.flags);
        
        nLen = sizeof(h);
        memcpy(buf, &h, nLen);
    }
        
    return nLen;
}

bool dns::Header::fromBuffer(unsigned char* buf, size_t size, size_t& offset)
{
    if((size - offset) < sizeof(header_fmt))
    {
        std::cout << "Buffer is too small to decode header" << std::endl;
        return false;
    }

    header_fmt *h = (header_fmt *)(buf + offset);
    m_id = ntohs(h->id);
    printf("Response Header::ID %x - %d\n", h->id, m_id);
    m_qdcount = ntohs(h->qdcount);
    m_ancount = ntohs(h->ancount);
    m_nscount = ntohs(h->nscount);
    m_arcount = ntohs(h->arcount);
    
    flags_dec((unsigned char*)&h->flags);
    offset += sizeof(header_fmt);
        
    printf("Decoding header: \n");
    printf("id: %x\n", h->id);
    printf("flags: %x\n", h->flags);
    printf("qdcount: %x\n", h->qdcount);
    printf("ancount: %x\n", h->ancount);
    printf("arcount: %x\n", h->arcount);
    
    return true;
}

std::string dns::Header::toString()
{
    std::ostringstream oss;
    if(m_flags.qr)
    {
        oss << "Response ";
        
        //enum RCODE
        //{
        //    DNS_NOERROR = 0, DNS_FORMERR, DNS_SERVFAIL, DNS_NXDOMAIN, DNS_NOTIMP, DNS_REFUSED
        //};
        
        switch (m_flags.rcode) 
        {
            case DNS_NOERROR:
                oss << "NOERROR ";
                break;
            case DNS_FORMERR:
                oss << "FORMERR ";
                break;
            case DNS_SERVFAIL:
                oss << "SERVFAIL ";
                break;
            case DNS_NXDOMAIN:
                oss << "NXDOMAIN ";
                break;
            case DNS_NOTIMP:
                oss << "NOTIMP ";
                break;
            case DNS_REFUSED:
                oss << "REFUSED ";
                break;    
                
            default:
                break;
        }
        
        oss << std::endl;
    }
    else
    {
        oss << "Request " << std::endl;;
    }
    
    oss << m_id << " " << m_qdcount << " " << m_ancount << " " << m_nscount << " " << m_arcount;
    
    return oss.str();
}

// Decode flags from 2-tyte buffer
void dns::Header::flags_dec(unsigned char* buf)
{
    m_flags.qr = buf[0] & 0x80;
    m_flags.opcode = (buf[0] & 0x78) >> 3;
    m_flags.aa = buf[0] & 0x04;
    m_flags.tc = buf[0] & 0x02;
    m_flags.rd = buf[0] & 0x01;
    
    m_flags.ra = buf[1] & 0x80;
    m_flags.z = buf[1] & 0x40;
    m_flags.ad = buf[1] & 0x20;
    m_flags.cd = buf[1] & 0x10;
    m_flags.rcode = (RCODE) (buf[1] & 0x0f);
}

// Encode flags into 2-byte buffer
void dns::Header::flags_enc(unsigned char* buf) 
{
    buf[0] = (m_flags.rd
               | (m_flags.tc << 1)
               | (m_flags.aa << 2)
               | (m_flags.opcode << 3)
               | (m_flags.qr << 7));
    
    buf[1] = (m_flags.rcode
               | (m_flags.cd << 4)
               | (m_flags.ad << 5)
               | (m_flags.z << 6)
               | (m_flags.ra << 7));
}



