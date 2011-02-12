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

#include "ResourceRecord.h"
#include "RRFactory.h"

dns::ResourceRecord::ResourceRecord(dns::Name& name, int rtype, int rclass, int ttl, int rdlen)
: m_name(name)
, m_type(rtype)
, m_class(rclass)
, m_ttl(ttl)
, m_rdlen(rdlen)
{
    
}

dns::ResourceRecord::~ResourceRecord()
{
    
}

// General Resource Record class does not parse RDATA
// Sub class will do it
bool dns::ResourceRecord::parse(unsigned char* buf, size_t size, size_t& offset)
{
    return true;
}

// From buffer
dns::ResourceRecord* dns::ResourceRecord::fromBuffer(unsigned char* buf, size_t size, size_t &offset)
{
    dns::ResourceRecord* rr = NULL;
    
    //Parse name first
    dns::Name name;
    
    if (!name.fromBuffer(buf, size, offset))
    {
        std::cout << "Decode name error, offset: %d " << offset << std::endl;
        //Error log
    }
    else
    {
        printf("Decode RR name, offset: %ld \n", offset);
        
        // Answer::Header
        if (size - offset >= sizeof(dns::ResourceRecord::Header))
        {
            dns::ResourceRecord::Header* header = (dns::ResourceRecord::Header*)(buf + offset);
            int rtype = ntohs(header->rtype);
            int rclass = ntohs(header->rclass);
            int rdlen = ntohs(header->rdlen);
            uint32_t uttl = ntohl(header->ttl);
            int ttl = *(int *)&uttl;
            offset += sizeof(dns::ResourceRecord::Header);
            
            printf("Decode RR header, offset: %ld \n", offset);
            
            // rdata
            if (size - offset >= rdlen)
            {
                rr = dns::RRFactory::instance()->create(name, rtype, rclass, ttl, rdlen);
                if(rr != NULL)
                {
                    if(!rr->parse(buf, size, offset))
                    {
                        delete rr;
                        rr = NULL;
                    }
                }
            }
        }
    }
    
    return rr;
}

std::string dns::ResourceRecord::toString()
{
    std::ostringstream oss;
    oss << "RR: " << m_name.toString() << " " << m_type << " " << m_class << " " << m_ttl << " " << m_rdlen;
    
    return oss.str();
}
