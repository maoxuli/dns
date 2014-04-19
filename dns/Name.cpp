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

#include "Name.h"

const char* dns::Name::s_szValidChars = "0123456789abcdefghijklmnopqrstuvwxyz-_/.";

dns::Name::Name()
: m_length(0)
{
    
}

dns::Name::Name(const char* name)
: m_length(0)
{
    std::string sName(name);
    parse(sName);
}

dns::Name::Name(std::string name)
: m_length(0)
{
    parse(name);
}

dns::Name::Name(const dns::Name* name)
: m_length(name->m_length)
{    
    for (std::list<std::string>::const_iterator it = name->m_parts.begin(); it != name->m_parts.end(); ++it)
    {
        m_parts.push_back(std::string(*it));
    }
}
              
dns::Name::~Name()
{

}

// Parse a dot-divided name
void dns::Name::parse(std::string& name)
{
    try
    {
        //Validate the name first
        std::string sName = name;
        std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);
        if (sName.size() > 255)
        {
            // Log error of too long name
            
        }
        else if (std::string::npos != sName.find_first_not_of(s_szValidChars, 0))
        {
            // Log error of invalid characters
            
        }
        else
        {
            // Divided domain into parts
            m_length = name.length() + 1;
            if (name.length() > 0
                && name != "")
            {
                size_t last = name.rfind(".");
                if (std::string::npos == last || (name.length() - 1) != last)
                {
                    name.append(".");
                    ++m_length;
                }
            }
            
            size_t index = 0, pos;
            while ((pos = name.find_first_of(".", index)) != std::string::npos)
            {
                std::string part;
                part.append(name, index, pos - index);
                m_parts.push_back(part);
                index = pos + 1;
            }
        }
    }
    catch (...)
    {
        // Log error
    }
}

// Decode domain name into a string lsit
// and create a new Name instance
bool dns::Name::fromBuffer(unsigned char* buf, size_t size, size_t& offset)
{
    return decode(buf, size, offset, m_parts, m_length);
}

//
// Recursively decode the name in DNS packet
// One byte followed by string
// if two high bits are 00, then the rest 6 bits is the length of following string (0-63).
// if two high bits are 11, then the rest 6 bits and the following one byte is a pointer 
// value of pointer is the offset from header
// 
bool dns::Name::decode(unsigned char* buf, size_t size, size_t &offset,std::list<std::string>& parts, size_t &len)
{
    bool bRet = true;

    for ( ; ; )
    {
        if (offset >= size)
        {
            // Error of beyond buffer
            
            bRet = false;
            break;
        }
        
        // Length of next section
        unsigned char nLen = buf[offset++];
        
        // '/0' is the termination
        if (nLen == 0)
        {
            break;
        }
        
        // Is a pointer of two bytes?
        if (nLen > 63)
        {
            if (nLen < 192 || offset == size)
            {
                // Error of a compression pointer 
                
                bRet = false;
                break;
            }
            
            size_t jump_to = ((nLen & 63) << 8) + buf[offset++];
            if (!decode(buf, size, jump_to, parts, len))
            {
                // Error
                
                bRet = false;
            }
            break;
        }
        
        len += nLen + 1;
        std::string part;
        part.reserve(nLen);
        for ( ; nLen > 0; --nLen, ++offset)
        {
            part.append(1, (char)tolower(buf[offset]));
        }
        
        parts.push_back(part);
    }
    
    return bRet;
}

// Encode domain name into a buffer
// Multiple sections, character number followed by the characters in each section
int dns::Name::toBuffer(unsigned char* buf, size_t size)
{
    int nLen = -1;
    
    if (size >= m_length)
    {
        nLen = 0;        
        for (std::list<std::string>::iterator it = m_parts.begin(); it != m_parts.end(); ++it)
        {
            std::string& p = *it;
            
            if (0 < p.size()
                && p != ".")
            {
                //Length and following string
                buf[nLen++] = p.length();
                for (unsigned int j = 0; j < p.length(); ++j)
                {
                    buf[nLen++] = tolower(p.at(j));
                }
            }
        }
        
        // Termination
        buf[nLen++] = 0;
    }
    
    return nLen;
}

std::string dns::Name::toString()
{
    std::ostringstream oss;
    for(std::list<std::string>::iterator it = m_parts.begin(); it != m_parts.end(); ++it)
    {
        oss << *it << ".";
    }
    
    return oss.str();
}
