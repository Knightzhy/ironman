#include "sample_header.h"

namespace ironman{
namespace serialize{

size_t SampleHeader::GetHeaderLength()
{
    return sizeof(_magic)
         + sizeof(_seq)
         + sizeof(_interface);
}

void SampleHeader::Init()
{
    _magic = 0;
    _seq = 0;
    _interface = 0;
}

void SampleHeader::SetMagic(int32_t magic)
{
    _magic = magic;
}

int32_t SampleHeader::GetMagic()
{
    return _magic;
}

void SampleHeader::SetSeq(uint64_t seq)
{
    _seq = seq;
}

uint64_t SampleHeader::GetSeq()
{
    return _seq;
}

void SampleHeader::SetInterface(uint32_t interface)
{
    _interface = interface;
}

uint32_t SampleHeader::GetInterface()
{
    return _interface;
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
    this->Init();
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

} // end namespace serialize
} // end namespace ironman
