/* Copyright 2018 wuzhy.dk@gmail.com (Knightzhy)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */

#ifndef __IRONMAN_SERIALIZE_MESSAGE_H__
#define __IRONMAN_SERIALIZE_MESSAGE_H__
#include "header.h"
#include "payload.h"
namespace ironman{
namespace serialize{

/*
 * length header payload
 * */

class Message{
public :
Message() {}
Message(int32_t magic) : _magic(magic), _header(NULL), _payload(NULL){}
Message(int32_t magic, Header *header, Payload *payload) :
    _magic(magic), _header(header), _payload(payload) {}

virtual ~Message(){}

static int GetMessageLength(const void *buffer, size_t length);
static int OnMessage(void *buffer, size_t length);
size_t GetMessageLength(Header *, Payload *);
size_t GetMessageLength();
ssize_t Serialize(void *buffer, size_t length, Header *, Payload *);
ssize_t UnSerialize(const void *buffer, size_t length, Header *, Payload *);
ssize_t Serialize(void *buffer, size_t length);
ssize_t UnSerialize(const void *buffer, size_t length);

void SetMagic(int32_t magic) { _magic = magic;}
int32_t GetMagic() { return _magic;}
private :
#pragma pack(push)
#pragma pack(1)
struct Packet{
    int32_t magic;
    uint32_t length;
    char header[];
    char payload[];
}; // end struct Packet
#pragma pack(pop)
protected :
    int32_t _magic;
    Header *_header;
    Payload *_payload;
}; // end class

} // end namespace serialize
} // end namespace ironman

#endif
