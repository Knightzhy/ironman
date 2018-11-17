#include "sample_header.h"
#include <stdio.h>

namespace ironman{
namespace serialize{

size_t SampleHeader::GetHeaderLength()
{
    return sizeof(_magic)
         + sizeof(_seq)
         + sizeof(_interface);
}

ssize_t SampleHeader::Serialize(void *buffer, size_t length)
{
    if (length < this->GetHeaderLength()) {
        return -2;
    }
    if (buffer == NULL) {
        return -1;
    }
    SampleHeader::Options *options =
        reinterpret_cast<SampleHeader::Options *>(buffer);
    options->magic = _magic;
    options->seq = _seq;
    options->interface = _interface;
    return (ssize_t)this->GetHeaderLength();
}

ssize_t SampleHeader::UnSerialize(const void *buffer, size_t length)
{
    const SampleHeader::Options *options =
        reinterpret_cast<const SampleHeader::Options *>(buffer);
    _magic = options->magic;
    _seq = options->seq;
    _interface = options->interface;
    if (this->GetHeaderLength() > length) {
        return -1;
    }
    return (ssize_t)this->GetHeaderLength();
}

void SampleHeader::PrintOptions()
{
    printf("options: =======\n");
    printf("magic:%d, seq=%d, interface=%d\n", _magic, _seq, _interface);
    printf("options: =======\n");
}

} // end namespace serialize
} // end namespace ironman
