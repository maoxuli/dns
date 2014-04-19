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

#ifndef DNS_HEADER_H
#define DNS_HEADER_H

#include <dns/Config.h>

#define HEADER_LENGTH 12

DNS_BEGIN
	
/*
RFC 1035	Domain Implementation and Specification    November 1987
4.1.1. Header section format

The header contains the following fields:

                                    1  1  1  1  1  1
      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

where:

ID              A 16 bit identifier assigned by the program that
                generates any kind of query.  This identifier is copied
                the corresponding reply and can be used by the requester
                to match up replies to outstanding queries.
	
QR              A one bit field that specifies whether this message is a
                query (0), or a response (1).
	
OPCODE          A four bit field that specifies kind of query in this
                message.  This value is set by the originator of a query
                and copied into the response.  The values are:

                0               a standard query (QUERY)
                1               an inverse query (IQUERY)
                2               a server status request (STATUS)
                3-15            reserved for future use

AA              Authoritative Answer - this bit is valid in responses,
                and specifies that the responding name server is an
                authority for the domain name in question section.

                Note that the contents of the answer section may have
                multiple owner names because of aliases.  The AA bit
                corresponds to the name which matches the query name, or
                the first owner name in the answer section.

TC              TrunCation - specifies that this message was truncated
                due to length greater than that permitted on the
                transmission channel.

RD              Recursion Desired - this bit may be set in a query and
                is copied into the response.  If RD is set, it directs
                the name server to pursue the query recursively.
                Recursive query support is optional.

RA              Recursion Available - this be is set or cleared in a
                response, and denotes whether recursive query support is
                available in the name server.

Z               Reserved for future use.  Must be zero in all queries
                and responses.

RCODE           Response code - this 4 bit field is set as part of
                responses.  The values have the following
                interpretation:

                0               No error condition
                1               Format error - The name server was
                                unable to interpret the query.
                2               Server failure - The name server was
                                unable to process this query due to a
                                problem with the name server.
                3               Name Error - Meaningful only for
                                responses from an authoritative name
                                server, this code signifies that the
                                domain name referenced in the query does
                                not exist.
                4               Not Implemented - The name server does
                                not support the requested kind of query.
                5               Refused - The name server refuses to
                                perform the specified operation for
                                policy reasons.  For example, a name
                                server may not wish to provide the
                                information to the particular requester,
                                or a name server may not wish to perform
                                a particular operation (e.g., zone
                                transfer) for particular data.
                6-15            Reserved for future use.

QDCOUNT         an unsigned 16 bit integer specifying the number of
                entries in the question section.

ANCOUNT         an unsigned 16 bit integer specifying the number of
                resource records in the answer section.

NSCOUNT         an unsigned 16 bit integer specifying the number of name
                server resource records in the authority records
                section.

ARCOUNT         an unsigned 16 bit integer specifying the number of
                resource records in the additional records section.
*/
	
// DNS response code
// RCODE in header
#define DNS_RESPONSE_NO_ERROR			0 
#define DNS_RESPONSE_FORMAT_ERROR 		1
#define DNS_RESPONSE_SERVER_FAILURE		2
#define DNS_RESPONSE_NAME_ERROR			3
#define DNS_RESPONSE_NOT_IMPLEMENTED	4
#define DNS_RESPONSE_REFUSED			5
	
class Header 
{
public:
    Header();
    virtual ~Header();
      
    int toBuffer(unsigned char* buf, size_t size);
    bool fromBuffer(unsigned char* buf, size_t size, size_t& offset);
    std::string toString();
    
    // ID field
    unsigned short idset(unsigned short id = 0);
    unsigned short id() { return m_id; }
	
	// Flag
	void qrset(bool qr) { m_flags.qr = qr; }
	void rdset(bool rd) { m_flags.rd = rd; }
	
    bool qr() { return m_flags.qr; }
    unsigned char rcode() { return m_flags.rcode; }
	
    // Questions and RR counts
    void qdinc() { ++m_qdcount; }
    void aninc() { ++m_ancount; }
    void nsinc() { ++m_nscount; }
    void arinc() { ++m_arcount; }

    void qddec() { --m_qdcount; }
    void andec() { --m_ancount; }
    void nsdec() { --m_nscount; }
    void ardec() { --m_arcount; }
    
    unsigned short qdcount() { return m_qdcount; }
    unsigned short ancount() { return m_ancount; }
    unsigned short nscount() { return m_nscount; }
    unsigned short arcount() { return m_arcount; }
                     
private:
    // ID 
    unsigned short m_id;
    //unsigned short m_flag;
    unsigned short m_qdcount;
    unsigned short m_ancount;
    unsigned short m_nscount;
    unsigned short m_arcount;

    // Flags in m_flag
    struct {
        bool qr;
        unsigned char opcode;
        bool aa;
        bool tc;
        bool rd;
        bool ra;
        unsigned char z;
        unsigned char rcode;
    } m_flags;
    
    // Encode and decode flags
    void flag_dec(uint16_t flag);
    uint16_t flag_enc();
};

DNS_END

#endif