#include "string_payload.h"
namespace ironman{
namespace serialize{
uint32_t StringPayload::_kMaxLength = 100;
StringPayload::StringPayload()
{
    memset(_msg, 0, _kMaxLength);
}

StringPayload::StringPayload(const char *msg)
{
    memset(_msg, 0, _kMaxLength);
    strcpy(_msg, msg);
}
size_t StringPayload::GetPayloadLength()
{
    return strlen(_msg) + 1;
}
ssize_t StringPayload::Serialize(void *buffer, size_t length)
{
    size_t msg_length = this->GetPayloadLength();
    if (msg_length > length) {
        return -1;
    }
    buffer = (void *)strncpy((char *)buffer, _msg, msg_length);
    if (buffer == NULL) {
        return -1;
    }
    return (ssize_t)msg_length;
}

int StringPayload::UnSerialize(const void *buffer, size_t length)
{
    memset(_msg, 0, _kMaxLength);
    if (length >= _kMaxLength) {
        return -1;
    }
    strncpy(_msg,reinterpret_cast<const char *>(buffer), length);
    return 0;
}
}
}
