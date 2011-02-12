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

#include "Packet.h"

dns::Packet::Packet(bool bResponse)
: m_header(bResponse)
{

}

dns::Packet::~Packet()
{
    
}

void dns::Packet::clearList()
{
    for(std::list<dns::Question*>::iterator it = m_questions.begin(); it != m_questions.end(); ++it)
    {
        dns::Question* p = *it;
        if(p != NULL)
        {
            delete p;
        }
    }
    
    for(std::list<dns::ResourceRecord*>::iterator it = m_answers.begin(); it != m_answers.end(); ++it)
    {
        dns::ResourceRecord* p = *it;
        if(p != NULL)
        {
            delete p;
        }
    }
}

// Add a question to a request packet
bool dns::Packet::addQuestion(dns::Question* question)
{
   if(header().qr())
    {
        return false;
    }
    
    m_questions.push_back(question);
    
    m_header.qdinc();
    
    return true;
}

// Encode a request packet
int dns::Packet::toBuffer(unsigned char *buf, size_t size)
{
    if(header().qr())
    {
        std::cout << "Can not encode a response packet" << std::endl;
        return -1;
    }
    
    int nRet = -1;
    memset(buf, 0, size);
    
    // Header
    nRet = m_header.toBuffer(buf, size);
    if (nRet <= 0)
    {
        std::cout << "Encoding header error." << std::endl;
    }
    else
    {
        printf("Encoding header, length: %d \n", nRet);
        
        size -= nRet;
        buf += nRet;    
    
        // Questions
        for (std::list<dns::Question*>::iterator it = m_questions.begin(); it != m_questions.end(); ++it) 
        {
            int nLen = (*it)->toBuffer(buf, size);
            
            if(nLen <= 0)
            {
                std::cout << "Encoding question error. " << std::endl; 
            }
            else
            {
                printf("Encoding question, length: %d \n", nLen);
                
                nRet += nLen;
            }
        }
    }
    
    printf("Encoding request packet, length: %d \n", nRet);
    return nRet;
}

// Decode a response packet
bool dns::Packet::fromBuffer(unsigned char* buf, size_t size)
{
    if(!header().qr())
    {
        std::cout << "Can not refill a request packet." << std::endl;
        return false;
    }
    
    bool bRet = true;
    size_t offset = 0;
        
    if (!m_header.fromBuffer(buf, size, offset))
    {
        std::cout << "Decode header error, offset: " << offset << std::endl;
        bRet = false;
    }
    else
    {
        // Question and answers pointer is relative to the end of header
        std::cout << "Decode header, offset: " << offset << std::endl;
        clearList();
        
        // questions
        for (int i = 0; bRet && i < m_header.qdcount(); ++i)
        {
            dns::Question* question = dns::Question::fromBuffer(buf, size, offset);
            if (question == NULL)
            {
                std::cout << "Decode question error, offset: " << offset << std::endl;
                bRet = false;
            }
            else
            {
                std::cout << "Decode question, offset: " << offset << std::endl;
                m_questions.push_back(question);
            }
        }
        
        // answers
        for (int i = 0; bRet && i < m_header.ancount(); ++i)
        {
            dns::ResourceRecord* rr = dns::ResourceRecord::fromBuffer(buf, size, offset);
            if (rr == NULL)
            {
                std::cout << "Decode answer error, offset: " << offset << std::endl;
                bRet = false;
            }
            else
            {
                std::cout << "Decode answer, offset: " << offset << std::endl;
                m_answers.push_back(rr);
            }
        }
    }
    
    return bRet;
}

std::string dns::Packet::toString()
{
    std::ostringstream oss;
    oss << m_header.toString() << std::endl;
    
    for(std::list<dns::Question*>::iterator it = m_questions.begin(); it != m_questions.end(); ++it)
    {
        dns::Question* q = *it;
        if(q != NULL)
        {
            oss << q->toString() << std::endl;
        }
    }
    
    for(std::list<dns::ResourceRecord*>::iterator it = m_answers.begin(); it != m_answers.end(); ++it)
    {
        dns::ResourceRecord* rr = *it;
        if(rr != NULL)
        {
            oss << rr->toString() << std::endl;
        }
    }
    
    return oss.str();
}
