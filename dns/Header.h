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

#ifndef DNS_HEADER_H
#define DNS_HEADER_H

#include <dns/Config.h>

#define HEADER_LENGTH 12

namespace dns 
{
    class Header 
    {
    public:
        Header(bool bResponse);
        virtual ~Header();
          
        int toBuffer(unsigned char* buf, size_t size);
        bool fromBuffer(unsigned char* buf, size_t size, size_t& offset);
        std::string toString();
        
        // ID field
        unsigned short assignID(unsigned short id = 0);
        inline unsigned short id() { return m_id; }
        
        // Questions and RR counts
        inline void qdinc() { ++m_qdcount; }
        inline void aninc() { ++m_ancount; }
        inline void nsinc() { ++m_nscount; }
        inline void arinc() { ++m_arcount; }

        inline void qddec() { --m_qdcount; }
        inline void andec() { --m_ancount; }
        inline void nsdec() { --m_nscount; }
        inline void ardec() { --m_arcount; }
        
        inline int qdcount() { return m_qdcount; }
        inline int ancount() { return m_ancount; }
        inline int nscount() { return m_nscount; }
        inline int arcount() { return m_arcount; }
        
        // Flags
        enum RCODE
        {
            DNS_NOERROR = 0, DNS_FORMERR, DNS_SERVFAIL, DNS_NXDOMAIN, DNS_NOTIMP, DNS_REFUSED
        };
        
        inline bool qr() { return m_flags.qr; }
        inline RCODE rcode() { return m_flags.rcode; }
                         
    private:
        // ID 
        unsigned short m_id;
        unsigned short m_flag;
        unsigned short m_qdcount;
        unsigned short m_ancount;
        unsigned short m_nscount;
        unsigned short m_arcount;

        // Flags
        struct {
            bool qr;
            unsigned opcode;
            bool aa;
            bool tc;
            bool rd;
            bool ra;
            unsigned z;
            bool ad;
            bool cd;
            bool auth;
            RCODE rcode;
        } m_flags;
        
        // Encode and decode flags
        void flags_dec(unsigned char* buf);
        void flags_enc(unsigned char* buf);
    };
}

#endif