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

#include "ARecord.h"
 
dns::ARecord::ARecord()
: ResourceRecord(DNS_TYPE_A)
{

}

dns::ARecord::~ARecord()
{
    
}

std::string dns::ARecord::toString()
{
    std::ostringstream oss;
    
    // Resourse Record header
    oss << dns::ResourceRecord::toString() << " ";
    
    // IPv4 address of A record
    struct in_addr ia = {m_ip};
    std::string ip = inet_ntoa(ia);
    oss << ip;
    
    return oss.str();
}

// Parse RDATA of A record
// RDATA is 4-bytes value of IPv4 address 
bool dns::ARecord::dataFromBuffer(unsigned char* buf, size_t size, size_t& offset)
{
    if(size - offset >= 4)
    {
        m_ip = ntohl(*(uint32_t *)(buf+offset));
        offset += 4;
        return true;
    }
    return false;
}

