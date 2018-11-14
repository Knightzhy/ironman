#include "sample_message.h"
namespace ironman{
namespace serialize{

uint32_t SampleMessage::_max_length = 65535;
uint32_t SampleMessage::_magic = 55443322;

int SampleMessage::AttachPayload(const Payload *)
{
    return 0;
}

int SampleMessage::DetachPayload(Payload *)
{
    return 0;
}


} // end namespace ironman
} // end namespace serialize

