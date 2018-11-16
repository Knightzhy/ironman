#include "message.h"

namespace ironman{
namespace serialize{

ssize_t Message::Serialize(void *buffer, size_t length,
        const Header *header, const Payload *payload)
{
    if (header == NULL) {
        return -1;
    }
    if (payload == NULL) {
        return -1;
    }

    size_t offset = 0;
    size_t packet_length = sizeof(Packet) + header->GetHeaderLength()
        + payload->GetMessageLength();

    if (length < packet_length) {
        return -1;
    }

    Packet *packet = reinterpret_cast<Packet *>(buffer);
    packet->magic = 345543;
    packet->length = packet_length;
    offset += sizeof(Packet);

    ssize_t header_length = header->Serialize(buffer + offset, length - offset);
    if (header_length < 0) {
        return -1;
    }
    if (header_length != header->GetHeaderLength()) {
        return -1;
    }
    offset += header_length;

    ssize_t payload_length = payload->Serialize(buffer + offset, length - offset);
    if (payload_length < 0) {
        return -1;
    }
    if (payload_length != payload->GetPayloadLength()) {
        return -1;
    }
    offset += payload_length;
    return (ssize_t)offset;

}

ssize_t Message::UnSerialize(const void *buffer, size_t length,
        Header *header, Payload *payload)
{
    const Packet *packet = reinterpret_cast<const Packet *>(buffer);
    _magic = packet->magic;
    size_t packet_length = packet->length;

    // TODO check magic and length
    // ,,,


    size_t offset = 0;
    offset += sizeof(Packet);
    ssize_t header_length = header->UnSerialize(buffer + offset, length - offset);
    if (header_length < 0) {
        return -1;
    }
    offset += header_length;
    ssize_t payload_length = payload->UnSerialize(buffer + offset, length - offset);
    if (payload_length < 0) {
        return -1;
    }
    offset += header_length;

    return (ssize_t)offset;
}

} // end namespace serialize
} // end namespace ironman
