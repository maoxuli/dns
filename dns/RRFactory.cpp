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

#include "RRFactory.h"
#include "ResourceRecord.h"
#include "ARecord.h"
#include "CNameRecord.h"
#include "TXTRecord.h"

dns::RRFactory* dns::RRFactory::m_instance = NULL;

dns::RRFactory::RRFactory()
{
    
}

dns::RRFactory::~RRFactory()
{
    
}

dns::RRFactory* dns::RRFactory::instance()
{
    if(m_instance == NULL)
    {
        m_instance = new dns::RRFactory();
    }
    
    return m_instance;
}

dns::ResourceRecord* dns::RRFactory::create(dns::Name& name, int rtype, int rclass, int ttl, int rdlen)
{
    switch (rtype) 
    {
        case DNS_RR_A: // A record
            return new ARecord(name, rclass, ttl, rdlen);
            break;
        case DNS_RR_CNAME: // CNAME record
            return new CNameRecord(name, rclass, ttl, rdlen);
            break;
        case DNS_RR_TXT: // TXT value record
            return new TXTRecord(name, rclass, ttl, rdlen);
            break;
            
        default:
            return new ResourceRecord(name, rtype, rclass, ttl, rdlen);
            break;
    }
    return NULL;
}
