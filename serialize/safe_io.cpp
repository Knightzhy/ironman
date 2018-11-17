#include "safe_io.h"
namespace ironman{
namespace serialize{

ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwriten;
    const void * ptr = vptr;
    nleft = n;
    while (nleft >0) {
        nwriten = write(fd, ptr, nleft);
        printf("write fd Bytes[%d]\n", (int)nwriten);
        if (nwriten < 0) {
            return -1;
        }
        nleft -= (size_t)nwriten;
        ptr += nwriten;
    }
    return (ssize_t)n;
}

ssize_t readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    void *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR 
             || errno == EWOULDBLOCK 
             || errno == EAGAIN) {
                break;
            }

            printf("error, return nread=%d, errno=%d. error=%s\n",
                    (int)nread, errno, strerror(errno));
            return -1;
        }
        printf("read xx=%d\n", (int)nread);
        if (nread == 0) {
            break;
        }
        nleft -= (size_t)nread;
        ptr = ptr + (int)nread;
    }
    return ssize_t(n - nleft);
}
} // end serialize
} // end ironman
