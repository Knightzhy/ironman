#include <stdio.h>
#include "message.h"

namespace ironman{
namespace serialize{

ssize_t Message::Serialize(void *buffer, size_t length,
        Header *header, Payload *payload)
{
    if (header == NULL) {
        return -1;
    }
    if (payload == NULL) {
        return -1;
    }

    size_t offset = 0;
    void *remind_buffer = buffer;
    size_t packet_length = sizeof(Packet) + header->GetHeaderLength()
        + payload->GetPayloadLength();

    if (length < packet_length) {
        return -1;
    }

    Packet *packet = reinterpret_cast<Packet *>(buffer);
    packet->magic = _magic;
    packet->length = (uint32_t)packet_length;
    offset += sizeof(Packet);

    remind_buffer = buffer + (int)offset;
    ssize_t header_length = header->Serialize(remind_buffer, length - offset);
    if (header_length < 0) {
        return -1;
    }
    if ((size_t)header_length != header->GetHeaderLength()) {
        return -1;
    }
    offset += (size_t)header_length;

    remind_buffer = buffer + (int)offset;
    ssize_t payload_length = payload->Serialize(remind_buffer, length - offset);
    if (payload_length < 0) {
        return -1;
    }
    if ((size_t)payload_length != payload->GetPayloadLength()) {
        return -1;
    }
    offset += (size_t)payload_length;
    return (ssize_t)offset;

}

ssize_t Message::UnSerialize(const void *buffer, size_t length,
        Header *header, Payload *payload)
{
    const Packet *packet = reinterpret_cast<const Packet *>(buffer);
    _magic = packet->magic;

    if (_magic != packet->magic) {
        printf("magic error.\n");
        return -1;
    }
    size_t packet_length = packet->length;
    if (packet_length > length) {
        return -1;
    }

    size_t offset = 0;
    offset += sizeof(Packet);
    printf("Packet sizeof = %d, remind length = %d\n", (int)offset, (int)(length - offset));
    ssize_t header_length = header->UnSerialize(buffer + offset, length - offset);
    if (header_length < 0) {
        return -1;
    }
    offset += (size_t)header_length;
    printf("Packet + Header Length = %d, remind length = %d\n", (int)offset, (int)(length - offset));
    ssize_t payload_length = payload->UnSerialize(buffer + offset, length - offset);
    if (payload_length < 0) {
        return -1;
    }
    offset += (size_t)payload_length;
    printf("Packet + Header + Payload = %d\n", (int)offset);

    return (ssize_t)offset;
}

int Message::GetMessageLength(const void *buffer, size_t length)
{
    if (buffer == NULL) {
        return -1;
    }
    const Packet *packet = reinterpret_cast<const Packet *>(buffer);
    if (_magic != packet->magic) {
        printf("magic error.\n");
        return -1;
    }
    return packet->length;
}

size_t Message::GetMessageLength(Header *header, Payload *payload)
{
    return sizeof(Packet) + header->GetHeaderLength()
        + payload->GetPayloadLength();
}
size_t Message::GetMessageLength()
{
    return this->GetMessageLength(_header, _payload);
}

ssize_t Message::Serialize(void *buffer, size_t length)
{
    return this->Serialize(buffer, length, _header, _payload);
}

ssize_t Message::UnSerialize(const void *buffer, size_t length)
{
    return this->UnSerialize(buffer, length, _header, _payload);
}
} // end namespace serialize
} // end namespace ironman
