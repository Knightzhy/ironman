#include <stdio.h>
#include "rpc.h"
#include "readn.cpp"
#include "writen.cpp"
#include "message.h"

namespace ironman{
namespace serialize{
namespace rpc{
int RpcBase::OnReceived(const void *buffer, size_t length, RpcFactory *rpc_factory)
{
    const void *ptr = buffer;
    size_t idle = length;

    do{
        ssize_t msg_length = rpc_factory.GetMessageLength(ptr, idle);
        if (msg_length < 0) {
            printf("connection fd[%d], msg is wrong, return %d.\n", fd, msg_length);
            return msg_length;
        }
        if (msg_length == 0) {
            printf("connection fd[%d], msg is imcompleted, return %d.\n", fd, msg_length);
            break;
        }
        if (msg_length > idle) {
            printf("connection fd[%d], msg is imcompleted, return %d.\n", fd, msg_length);
            break;
        }
        idle = idle - msg_length;
        ptr = ptr + msg_length;

        msg_length = rpc_factory.OnMessage(ptr, msg_length);
    } while(idle > 0);
    return (int)idle;
}
int RpcBase::Received(int fd, RpcFactory *rpc_factory)
{
    size_t buffer_length = 1024;
    void *buffer = malloc(buffer_length);
    unsigned char *ptr = reinterpret_cast<unsigned char*>(buffer);

    ssize_t incompleted = 0;
    do {
        memset(buffer + incompleted, 0, buffer_length - incompleted);
        ssize_t count = readn(fd, buffer + incompleted, buffer_length - incompleted);
        if (count < 0) {
            printf("connection fd[%d] readn return %d.\n", fd, count);
            return count;
        }
        if (count == 0) {
            printf("connection fd[%d] readn return %d.\n", fd, count);
            return count;
        }

        // count >0
        printf("connection fd[%d] received [%d]Bytes.\n", fd, count);
        incompleted = incompleted + count;

        ssize_t ret = OnReceived(buffer, incompleted, rpc_factory);
        if (incompleted < 0) {
            return incompleted;
        }
        if (incompleted == 0) {
            continue;
        }
        printf("connection fd[%d] received incompleted, [%d]Bytes.\n", fd, ret);
        strncpy(ptr, ptr + incompleted - ret, ret);
        incompleted = ret;
    } while (count > 0);
    return 0;
}

int RpcBase::Sended(int fd, RpcFactory *rpc_factory)
{
    void *buffer;
    size_t length;
    int ret = rpc_factory.Serialize(buffer, &length);
    if (ret <0) {
        printf("Serialize failed ret[%d].\n", ret);
        return -1;
    }
    if (buffer == NULL) {
        return 0;
    }
    printf("Serialize [%d]Bytes need send.\n", length);
    ssize_t count = writen(fd, buffer, length);
    printf("Send [%d]Bytes.\n", count);
    buffer = NULL;
}


} // end namespace rpc
} // end namespace serialize
} // end namespace ironman
