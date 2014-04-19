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

#include "ResourceRecord.h"

DNS_BEGIN
	
ResourceRecord::ResourceRecord(unsigned short rtype, unsigned short rdlen)
: m_type(rtype)
, m_class(0)
, m_ttl(0)
, m_rdlen(rdlen)
{
    
}

ResourceRecord::~ResourceRecord()
{
    
}

std::string ResourceRecord::toString()
{
    std::ostringstream oss;
    oss << "Resource Record: " << m_name.toString() << " " << m_type << " " << m_class << " " << m_ttl << " " << m_rdlen;
    return oss.str();
}

unsigned short ResourceRecord::checkType(unsigned char* buf, size_t size, size_t offset)
{
    Name name;
    name.fromBuffer(buf, size, offset);
    return ntohs(*(uint16_t*)(buf + offset));
}

// From buffer
bool ResourceRecord::fromBuffer(unsigned char* buf, size_t size, size_t &offset)
{
    // Header 
    if (m_name.fromBuffer(buf, size, offset))
    {       
        if (size - offset >= 10)
        {
            m_type = ntohs(*(uint16_t*)(buf + offset));
            offset += 2;
            m_class = ntohs(*(uint16_t*)(buf + offset));
            offset += 2;
            m_ttl = ntohl(*(uint32_t*)(buf + offset));
            offset += 4;
            m_rdlen = ntohs(*(uint16_t*)(buf + offset));
            offset += 2;

            return dataFromBuffer(buf, size, offset);
        }
    }
    return false;
}

bool ResourceRecord::dataFromBuffer(unsigned char* buf, size_t size, size_t &offset)
{
    if(size - offset >= m_rdlen)
    {
        offset += m_rdlen;
        return true;
    }
    return false;
}

DNS_END