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

#ifndef DNS_RESOURCE_RECORD_H
#define DNS_RESOURCE_RECORD_H

#include <dns/Config.h>
#include <dns/Name.h>

namespace dns 
{
    class ResourceRecord 
    {
    public:
        ResourceRecord(dns::Name& name, int rtype, int rclass, int ttl, int rdlen);
        virtual ~ResourceRecord();
        
        static ResourceRecord* fromBuffer(unsigned char* buf, size_t size, size_t& offset);
        
        // Parse RDATA of Resource Record
        // Implemented in sub class
        virtual bool parse(unsigned char* buf, size_t size, size_t& offset);
        
        virtual std::string toString();
                        
    protected:
        dns::Name m_name;
        int m_type;
        int m_class;
        int m_ttl;
        int m_rdlen;
        
        // Memory structure
        struct Header
        {
            int16_t rtype;
            int16_t rclass;
            int32_t ttl;
            uint16_t rdlen;
        } __attribute__((__packed__));
    };
}

#endif