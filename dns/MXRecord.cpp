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

#include "MXRecord.h"

dns::MXRecord::MXRecord(dns::Name& name, int rclass, int ttl, int rdlen)
: ResourceRecord(name, DNS_RR_CNAME, rclass, ttl, rdlen)
{
    
}

dns::MXRecord::~MXRecord()
{
    
}

// Parse RDATA of CName record
// RDATA is the A name refered by the alias
bool dns::MXRecord::parse(unsigned char* buf, size_t size, size_t& offset)
{
    m_priority = *(uint16_t*)(buf + offset); // ?
    offset += 2;
    return m_aname.fromBuffer(buf, size, offset);
}

std::string dns::MXRecord::toString()
{
    std::ostringstream oss;
    
    // Resource Record header
    oss << dns::ResourceRecord::toString() << " ";
    
    // Priority
    oss << m_priority << " ";
    
    // A name
    oss << m_aname.toString();
    
    return oss.str();
}
