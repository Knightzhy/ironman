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


#ifndef __IRONMAN_SERIALIZE_SAFE_IO_H__
#define __IRONMAN_SERIALIZE_SAFE_IO_H__
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
namespace ironman{
namespace serialize{

extern ssize_t readn(int fd, void *vptr, size_t n);
extern ssize_t writen(int fd, const void *vptr, size_t n);

} // end serialize
} // end ironman
#endif
