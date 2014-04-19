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

#include "TXTRecord.h"

dns::TXTRecord::TXTRecord()
: ResourceRecord(DNS_TYPE_TXT)
{
    
}

dns::TXTRecord::~TXTRecord()
{
    
}

std::string dns::TXTRecord::toString()
{
    std::ostringstream oss;
    
    // Resource record header
    oss << dns::ResourceRecord::toString() << " ";
    
    // Text value 
    oss << m_text;
    
    return oss.str();
}

// Parse RDATA of TXT record
// Text is a sequence of [count+characters]
bool dns::TXTRecord::dataFromBuffer(unsigned char* buf, size_t size, size_t& offset)
{
    size_t start = offset;
    int count = 0;
    while (offset - start < m_rdlen)
    {
        count = (uint8_t) buf[offset++];
        m_text.append((char*) &(buf[offset]), (int)count);
        offset += count;
    }
    
    return true;
}
