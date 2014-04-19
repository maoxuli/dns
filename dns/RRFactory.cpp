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

#include "RRFactory.h"
#include "ResourceRecord.h"
#include "ARecord.h"
#include "CNameRecord.h"
#include "TXTRecord.h"
#include "MXRecord.h"

DNS_BEGIN
	
ResourceRecord* RRFactory::fromBuffer(unsigned char* buf, size_t size, size_t& offset)
{
    ResourceRecord* rr = NULL;
    unsigned short rtype = ResourceRecord::checkType(buf, size, offset);
    switch (rtype) 
    {
        case DNS_TYPE_A: // A record
            rr = new ARecord();
            break;
        case DNS_TYPE_CNAME: // CNAME record
            rr = new CNameRecord();
            break;
        case DNS_TYPE_TXT: // TXT value record
            rr = new TXTRecord();
            break;
        case DNS_TYPE_MX: // MX record
            rr = new MXRecord();
            break;
            
        default:
            rr = new ResourceRecord(rtype);
            break;
    }
    assert(rr != NULL);
    rr->fromBuffer(buf, size, offset);
    return rr;
}

DNS_END
