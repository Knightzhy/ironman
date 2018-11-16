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
    packet->magic = 345543;
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

    size_t packet_length = packet->length;
    if (packet_length > length) {
        return -1;
    }

    // TODO check magic and length
    // ,,,


    size_t offset = 0;
    offset += sizeof(Packet);
    ssize_t header_length = header->UnSerialize(buffer + offset, length - offset);
    if (header_length < 0) {
        return -1;
    }
    offset += (size_t)header_length;
    ssize_t payload_length = payload->UnSerialize(buffer + offset, length - offset);
    if (payload_length < 0) {
        return -1;
    }
    offset += (size_t)header_length;

    return (ssize_t)offset;
}

} // end namespace serialize
} // end namespace ironman
