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

#ifndef __IRONMAN_SERIALIZE_SAMPLE_MESSAGE_H__
#define __IRONMAN_SERIALIZE_SAMPLE_MESSAGE_H__
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "payload.h"
#include "message.h"

namespace ironman{
namespace serialize{


class SampleMessage : public Message {
public :
    SampleMessage(){}
    ~SampleMessage(){}
    virtual int AttachPayload(const Payload *);
    virtual int DetachPayload(Payload *);
private:
#pragma pack(push)
#pragma pack(1)
struct Message{
    int32_t magic;
    uint32_t length;
    uint64_t seq;
    char payload[];
}; // end struct Message
#pragma pack(pop)
    Message * _message;
    Payload *_payload;
    static uint32_t _max_length;
    static uint32_t _magic;
}; // end class SampleMessage


} // end namespace serialize
} // end namespace ironman

#endif
