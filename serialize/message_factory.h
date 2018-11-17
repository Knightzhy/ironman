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
#ifndef __IRONMAN_SERIALIZE_MESSAGE_FACTORY_H__
#define __IRONMAN_SERIALIZE_MESSAGE_FACTORY_H__
#include "stdio.h"
#include <stdlib.h>
#include "rpc_factory.h"
#include "message.h"
#include "string_payload.h"
#include "sample_header.h"
namespace ironman{
namespace serialize{
namespace rpc{
class MessageFactory : public RpcFactory{
public :
MessageFactory() : _message(NULL){}
MessageFactory(Message *message) : _message(message){}
~MessageFactory(){}
virtual ssize_t GetMessageLength(const void *buffer, size_t length);
virtual ssize_t OnMessage(const void *buffer, size_t length);
virtual ssize_t Serialize(void *buffer, size_t length);
private :
Message *_message;
};

} // namespace rpc
} // namespace serialize
} // namespace ironman
#endif
