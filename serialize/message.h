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
#include <stdint.h>
#include "package.h"
#include "payload.h"
namespace ironman{
namespace serialize{

/*
 * length header payload
 * */

class Message : public Package {
public :
Message(int32_t magic, Payload *payload) :
    _magic(magic), _payload(payload) {}
virtual ~Message(){}

virtual int GetMessageLength(const void *buffer, size_t length);
virtual size_t GetMessageLength();
virtual ssize_t Serialize(void *buffer, size_t length);
virtual ssize_t UnSerialize(const void *buffer, size_t length);

private :
size_t GetMessageLength(Payload *);
ssize_t Serialize(void *buffer, size_t length, Payload *);
ssize_t UnSerialize(const void *buffer, size_t length, Payload *);

private :
#pragma pack(push)
#pragma pack(1)
struct Packet{
    int32_t magic;
    uint32_t length;
    char payload[];
}; // end struct Packet
#pragma pack(pop)
protected :
    int32_t _magic;
public :
    Payload *_payload;
}; // end class

} // end namespace serialize
} // end namespace ironman

#endif
