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

#ifndef DNS_PACKET_H
#define DNS_PACKET_H

#include <dns/Config.h>
#include <dns/Header.h>
#include <dns/Question.h>
#include <dns/ResourceRecord.h>

namespace dns 
{
    
    //
    // On top level, DNS defines a unified packet structure for
    // request and response between client and server, and 
    // between servers.
    // A flag in header indicates a request or a response packet
    // Following header, a request packet has a questions section
    // while response packet has questions, answers, and other
    // two sections. This implementation only process questions
    // and answers section.
    //
    class Packet 
    {
    public:
        Packet(bool bResponse);
        virtual ~Packet();
        
        // Add a question to a request packet
        bool addQuestion(dns::Question* question);
        
        // Encode a request packet
        int toBuffer(unsigned char* buf, size_t size);
        
        // Decode a response packet
        bool fromBuffer(unsigned char* buf, size_t size);
        
        // Access header and sections
        inline dns::Header& header() {return m_header; };
        inline std::list<dns::Question*>& questions() {return m_questions; };
        inline std::list<dns::ResourceRecord*>& answers() {return m_answers; };
        
        std::string toString();
        
    private:
        //Header
        dns::Header m_header;
        
        //Questions
        std::list<dns::Question*> m_questions;
        
        //Answers
        std::list<dns::ResourceRecord*> m_answers;
        
        void clearList();
    };
}

#endif