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

#ifndef DNS_RR_FACTORY_H
#define DNS_RR_FACTORY_H

#include <dns/Config.h>
#include <dns/ResourceRecord.h>
#include <dns/Name.h>

namespace  dns
{
    class RRFactory
    {
    public:
        virtual ~RRFactory();
        static RRFactory* instance();
        
        // Create RR object with rtype
        ResourceRecord* create(dns::Name& name, int rtype, int rclass, int ttl, int rdlen);
        
    private:
        RRFactory();
        static RRFactory* m_instance;
        
        // Helper class to delete singleton instance
        class Deleter
        {
        public:
            Deleter() {};
            ~Deleter()
            {
                if(RRFactory::m_instance != NULL)
                {
                    delete RRFactory::m_instance;
                }
            }
        };
        friend class Deleter;
        static Deleter m_deleter;
    };
}

#endif