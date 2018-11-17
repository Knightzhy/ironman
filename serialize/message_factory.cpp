#include "message_factory.h"
namespace ironman{
namespace serialize{
namespace rpc{
ssize_t MessageFactory::OnMessage(const void *buffer, size_t length)
{
    ssize_t m = _package->UnSerialize(buffer, length);
    printf("UnSerialzie return %d\n", m);
    return m;
}

} // namespace rpc
} // namespace serialize
} // namespace ironman
