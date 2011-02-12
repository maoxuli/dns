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

#ifndef DNS_CONFIG_H
#define DNS_CONFIG_H

//
// C++ standard and STL
//
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>

#if defined(_WIN32)
#   include <process.h>
#else
#   include <pthread.h>
#   include <errno.h>
#   include <sys/types.h>
#   include <unistd.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <netdb.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#endif
         
#define DNS_RR_A 1
#define DNS_RR_NS 2
#define DNS_RR_MD 3
#define DNS_RR_MF 4
#define DNS_RR_CNAME 5
#define DNS_RR_SOA 6
#define DNS_RR_MB 7
#define DNS_RR_MG 8
#define DNS_RR_MR 9
#define DNS_RR_NULL 10
#define DNS_RR_WKS 11
#define DNS_RR_PTR 12
#define DNS_RR_HINFO 13
#define DNS_RR_MINFO 14
#define DNS_RR_MX 15
#define DNS_RR_TXT 16
#define DNS_RR_RP 17
#define DNS_RR_AFSDB 18
#define DNS_RR_X25 19
#define DNS_RR_ISDN 20
#define DNS_RR_RT 21
#define DNS_RR_NSAP 22
#define DNS_RR_NSAP_PTR 23
#define DNS_RR_SIG 24
#define DNS_RR_KEY 25
#define DNS_RR_PX 26
#define DNS_RR_GPOS 27
#define DNS_RR_AAAA 28
#define DNS_RR_LOC 29
#define DNS_RR_NXT 30
#define DNS_RR_EID 31
#define DNS_RR_NIMLOC 32
#define DNS_RR_SRV 33
#define DNS_RR_ATMA 34
#define DNS_RR_NAPTR 35
#define DNS_RR_KX 36
#define DNS_RR_CERT 37
#define DNS_RR_A6 38
#define DNS_RR_DNAME 39
#define DNS_RR_SINK 40
#define DNS_RR_OPT 41
#define DNS_RR_APL 42
#define DNS_RR_DS 43
#define DNS_RR_SSHFP 44
#define DNS_RR_IPSECKEY 45
#define DNS_RR_RRSIG 46
#define DNS_RR_NSEC 47
#define DNS_RR_DNSKEY 48
#define DNS_RR_DHCID 49
#define DNS_RR_NSEC3 50
#define DNS_RR_NSEC3PARAM 51
#define DNS_RR_HIP 55
#define DNS_RR_NINFO 56
#define DNS_RR_RKEY 57
#define DNS_RR_TALINK 58
#define DNS_RR_SPF 99
#define DNS_RR_UINFO 100
#define DNS_RR_UID 101
#define DNS_RR_GID 102
#define DNS_RR_UNSPEC 103
#define DNS_RR_TKEY 249
#define DNS_RR_TSIG 250
#define DNS_RR_IXFR 251
#define DNS_RR_AXFR 252
#define DNS_RR_MAILB 253
#define DNS_RR_MAILA 254

#define DNS_CLASS_IN 1
#define DNS_CLASS_CH 3
#define DNS_CLASS_ANY 255

#endif