#include <stdio.h>
#include "rpc_factory.h"
namespace ironman{
namespace serialize{
namespace rpc{

ssize_t RpcFactory::GetMessageLength(const void *buffer, size_t length)
{
    if (buffer == NULL) {
        printf("GetMessageLength's buffer is NULL.\n");
        return -1;
    }
    ssize_t l = _package->GetMessageLength(buffer, length);
    return l;
}

ssize_t RpcFactory::Serialize(void *buffer, size_t length)
{
    if (_package == NULL) {
        return -1;
    }
    if (buffer == NULL) {
        return -1;
    }
    size_t buffer_length = _package->GetMessageLength();
    printf("package.GetMessage buffer_length=%d.\n", buffer_length);
    if (buffer_length > length) {
        printf("buffer is too smaller.\n");
    }
    ssize_t count = _package->Serialize(buffer, buffer_length);
    printf("package.Serialize count=%d.\n", count);
    return count;
}

} // namespace rpc
} // namespace serialize
} // namespace ironman
