#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtest/gtest.h>
#include "../serialize/string_payload.h"

TEST(PAYLOAD, A)
{
    ironman::serialize::StringPayload string_payload("AMND");
    size_t length = string_payload.GetMessageLength();
    char *buffer = (char *)malloc(length);
    ssize_t l = string_payload.Serialize(buffer, length);
    if (l < 0) {
        printf("Serialize error\n");
        return;
    }
    printf("length=%d, l=%d,msg=%s\n",
            (int)length, (int)l, buffer);

    ironman::serialize::Payload *string_payload2 =
        new ironman::serialize::StringPayload;
    string_payload2->Unserialize(buffer, (size_t)l);
    size_t length2 = string_payload2->GetMessageLength();
    char *buffer2 = (char *)malloc(length2);
    ssize_t w = string_payload2->Serialize(buffer2, length2);
    if (w < 0) {
        printf("Serialize error\n");
        return;
    }
    printf("length=%d, l=%d,msg=%s\n",
            (int)length2, (int)w, buffer2);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
