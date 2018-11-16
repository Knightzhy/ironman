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


#ifndef __IRONMAN_SERIALIZE_HEADER_H__
#define __IRONMAN_SERIALIZE_HEADER_H__
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
namespace ironman{
namespace serialize{
class Header{
public :
Header(){}
virtual ~Header(){}

virtual size_t GetHeaderLength() = 0;
virtual ssize_t Serialize(void *buffer, size_t length) = 0;
virtual ssize_t UnSerialize(const void *buffer, size_t length) = 0;
private :
uint32_t _total_length;
}; // end namespace Header

} // end serialize
} // end ironman

#endif
