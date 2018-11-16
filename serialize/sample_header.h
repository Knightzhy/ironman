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


#ifndef __IRONMAN_SERIALIZE_SAMPLEHEADER_H__
#define __IRONMAN_SERIALIZE_SAMPLEHEADER_H__
#include <stdint.h>
#include "header.h"
namespace ironman{
namespace serialize{
class SampleHeader : public Header {
public :
SampleHeader(){}
~SampleHeader(){}

virtual size_t GetHeaderLength();
virtual ssize_t Serialize(void *buffer, size_t length);
virtual ssize_t UnSerialize(const void *buffer, size_t length);

void Init();

void SetMagic(int32_t magic);
int32_t GetMagic();
void SetSeq(uint64_t seq);
uint64_t GetSeq();
void SetInterface(uint32_t interface);
uint32_t GetInterface();

private :
#pragma pack(push)
#pragma pack(1)
struct Options{
    int32_t magic;
    uint64_t seq;
    uint32_t interface;
}; // end struct Message
#pragma pack(pop)
    int32_t _magic;
    uint64_t _seq;
    uint32_t _interface;
}; // end class SampleHeader

} // end namespace serialize
} // end namespace ironman

#endif
