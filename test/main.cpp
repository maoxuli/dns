
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

#include <dns/Message.h>
#include <dns/Resolver.h>
#include <iostream>

int main (int argc, const char * argv[])
{
    std::cout <<
    "//\n"
    "// DNS resolver, v0.1.1\n"
    "// Copyright 2012 LIM Labs.\n"
    "//\n"
    "\n";
    
    if(argc < 2)
    {
        std::cout <<
        "// Please input a domain name as agument.\n"
        "// Usage: dns [domain name]\n";
        return 0;
    }
    
    std::string domain = argv[1];
    
    std::cout <<
    "Resolve(" << domain << ")\n"
    "{\n";
    
    dns::Message response;
    dns::Resolver resolver;
    resolver.resolve(domain, DNS_TYPE_A, response);
    std::cout << response.toString();
    resolver.resolve(domain, DNS_TYPE_CNAME, response);
    std::cout << response.toString();
    resolver.resolve(domain, DNS_TYPE_MX, response);
    std::cout << response.toString();
    resolver.resolve(domain, DNS_TYPE_TXT, response);
    std::cout << response.toString();
    
    std::cout << "}\n";
    //getchar();
    return 0;
}

