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
#ifndef __IRONMAN_SERIALIZE_RPC_FACTORY_H__
#define __IRONMAN_SERIALIZE_RPC_FACTORY_H__
#include <unistd.h>
#include <sys/types.h>
#include "message.h"
namespace ironman{
namespace serialize{
namespace rpc{

class RpcFactory{
public :
RpcFactory() : _package(NULL){}
RpcFactory(Message *package) : _package(package){}
virtual ~RpcFactory(){}

virtual ssize_t Serialize(void *buffer, size_t length);
virtual ssize_t GetMessageLength(const void *buffer, size_t length);
virtual ssize_t OnMessage(const void *buffer, size_t length) = 0;

protected :
Message *_package;
}; // end class RpcFactory

} // namespace rpc
} // namespace serialize
} // namespace ironman
#endif
