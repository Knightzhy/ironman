#include <stdio.h>
#include "rpc.h"
#include "safe_io.h"
#include "message.h"

namespace ironman{
namespace serialize{
namespace rpc{
int RpcBase::OnReceived(const void *buffer, size_t length, RpcFactory *rpc_factory)
{
    const void *ptr = buffer;
    size_t idle = length;

    do{
        ssize_t msg_length = rpc_factory->GetMessageLength(ptr, idle);
        if (msg_length < 0) {
            printf("msg is wrong, return %d.\n", (int)msg_length);
            return (int)msg_length;
        }
        if (msg_length == 0) {
            printf("msg is imcompleted, return %d.\n", (int)msg_length);
            break;
        }
        if ((size_t)msg_length > idle) {
            printf("msg is imcompleted, return %d.\n", (int)msg_length);
            break;
        }

        ssize_t count = rpc_factory->OnMessage(ptr, msg_length);
        printf("RpcFactory.OnMessage count=%d.\n", count);
        idle = idle - (size_t)msg_length;
        ptr = ptr + msg_length;
    } while(idle > 0);
    return (int)idle;
}
int RpcBase::Received(int fd, RpcFactory *rpc_factory)
{
    size_t buffer_length = 1024;
    void *buffer = malloc(buffer_length);
    char *ptr = reinterpret_cast<char*>(buffer);

    ssize_t incompleted = 0;
    ssize_t count = 0;
    do {
        memset(buffer + incompleted, 0, buffer_length - incompleted);
        count = readn(fd, buffer + incompleted, buffer_length - incompleted);
        if (count < 0) {
            printf("connection fd[%d] readn return %d.\n", fd, (int)count);
            free(buffer);
            return (int)count;
        }
        if (count == 0) {
            printf("connection fd[%d] readn return %d.\n", fd, (int)count);
            free(buffer);
            return (int)count;
        }

        // count >0
        printf("connection fd[%d] received [%d]Bytes.\n", fd, (int)count);
        incompleted = incompleted + count;

        ssize_t ret = OnReceived(buffer, incompleted, rpc_factory);
        if (ret < 0) {
            free(buffer);
            return (int)ret;
        }
        if (ret == 0) {
            continue;
        }
        printf("connection fd[%d] received incompleted, [%d]Bytes.\n", fd, (int)ret);
        strncpy(ptr, ptr + incompleted - ret, ret);
        incompleted = ret;
    } while (count > 0);
    free(buffer);
    return 0;
}

int RpcBase::Sended(int fd, RpcFactory *rpc_factory)
{
    size_t length = 1000;
    void *buffer = malloc(length);
    memset(buffer, 0, length);
    ssize_t count = rpc_factory->Serialize(buffer, length);
    if (count <0) {
        printf("Serialize failed ret[%d].\n", count);
        return -1;
    }
    if (buffer == NULL) {
        return 0;
    }
    printf("Serialize [%d]Bytes need send.\n", (int)count);
    count = writen(fd, buffer, count);
    printf("Send [%d]Bytes.\n", (int)count);
    buffer = NULL;
    return 0;
}


} // end namespace rpc
} // end namespace serialize
} // end namespace ironman
