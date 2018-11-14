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
namespace ironman{
namespace serialize{

class Message{
public :
Message(){}
virtual ~Message(){}
virtual int AttachPayload(const Payload *) = 0;
virtual int DetachPayload(Payload *) = 0;
}; // end class

} // end namespace serialize
} // end namespace ironman

#endif
