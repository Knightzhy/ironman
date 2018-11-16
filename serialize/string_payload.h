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

#ifndef __IRONMAN_SERIALIZE_STRING_PAYLOAD_H__
#define __IRONMAN_SERIALIZE_STRING_PAYLOAD_H__
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "payload.h"
namespace ironman{
namespace serialize{
class StringPayload : public Payload{
public :
StringPayload();
StringPayload(const char *msg);
~StringPayload(){}
virtual size_t GetPayloadLength();
virtual int Unserialize(const void *buffer, size_t length);
virtual ssize_t Serialize(void *buffer, size_t length);

private :
    char _msg[100];
    static uint32_t _kMaxLength;
}; // end class StringPayload
} // end namespace ironman
} // end namespace serialize
#endif
