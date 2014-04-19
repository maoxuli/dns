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

#include "Question.h"

dns::Question::Question(const std::string& qname, unsigned short qtype)
: m_name(qname)
, m_type(qtype)
, m_class(DNS_CLASS_IN)
{

}

dns::Question::Question(const dns::Name& qname, unsigned short qtype, unsigned short qclass)
: m_name(qname)
, m_type(qtype)
, m_class(qclass)
{
    
}

dns::Question::~Question()
{
    
}

std::string dns::Question::toString()
{
    std::ostringstream oss;
    oss << "Question: " << m_name.toString() << " " << m_type << " " << m_class;
    
    return oss.str();
}

int dns::Question::toBuffer(unsigned char *buf, size_t size)
{   
    int nLen = -1;
    
    // Encode name
    nLen = m_name.toBuffer(buf, size);
    if (nLen <= 0)
    {
        //Error
    }
    else
    {
        // Copy type and class
        *(uint16_t*)(buf + nLen) = htons(m_type);
        nLen += 2;
        *(uint16_t*)(buf + nLen) = htons(m_class);
        nLen += 2;
    }
    
    return nLen;
}

// From buffer
dns::Question* dns::Question::fromBuffer(unsigned char* buf, size_t size, size_t &offset)
{
    dns::Question* question = NULL;
    
    //Parse name first
    dns::Name name;
    if (!name.fromBuffer(buf, size, offset))
    {
        //Error log
    }
    else
    {
        // type and class
        if (size - offset >= 4)
        {
            unsigned short qtype = ntohs(*(uint16_t*)(buf + offset));
            offset += 2;
            unsigned short qclass = ntohs(*(uint16_t*)(buf + offset));
            offset += 2;

            question = new dns::Question(name, qtype, qclass);
        }
    }
    
    return question;
}



