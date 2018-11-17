#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include "../serialize/string_payload.h"
#include "../serialize/sample_header.h"
#include "../serialize/message.h"
#include "../serialize/rpc.h"
#include "../serialize/message_factory.h"

// Header
//
TEST(RPC, A)
{
    // Serialize
    ironman::serialize::SampleHeader sample_header(8788, 12990, 33);

    size_t length = sample_header.GetHeaderLength();
    printf("sample_header.length=%d.\n", (int)length);

    void *buffer = malloc(length);
    ssize_t count = sample_header.Serialize(buffer, length);
    printf("sample_header.serialize count=%d.\n", (int)count);
    sample_header.PrintOptions();

    // UnSerialize
    ironman::serialize::SampleHeader sample_header2;
    count = sample_header2.UnSerialize(buffer, count);
    printf("sample_header.unserialize count=%d.\n", (int)count);
    sample_header2.PrintOptions();

    free(buffer);
    buffer = NULL;
}

// Payload
//
TEST(RPC, B)
{
    // Serialize
    ironman::serialize::StringPayload string_payload("Tom");
    size_t length = string_payload.GetPayloadLength();
    printf("string_payload.length=%d.\n", (int)length);

    void *buffer = malloc(length);
    ssize_t count = string_payload.Serialize(buffer, length);
    printf("string_payload.serialize count=%d.\n", (int)count);
    string_payload.PrintMsg();

    // UnSerialize
    ironman::serialize::StringPayload string_payload2;
    count = string_payload2.UnSerialize(buffer, count);
    printf("string_payload.unserialize count=%d.\n", (int)count);
    string_payload2.PrintMsg();

    free(buffer);
    buffer = NULL;
}

// Message
//
TEST(RPC, C)
{
    // Serialize
    ironman::serialize::SampleHeader sample_header(55443322, 7788231, 118);
    ironman::serialize::Header *header = &sample_header;

    ironman::serialize::StringPayload string_payload("AMND Hello World!");
    ironman::serialize::Payload *payload = &string_payload;

    ironman::serialize::Message message(98120, header, payload);
    size_t length = message.GetMessageLength();
    printf("%d, %d, %d\n", header->GetHeaderLength(),
            payload->GetPayloadLength(), (int)length);

    void *buffer = malloc(length);
    ASSERT_TRUE(buffer != NULL);
    ssize_t l = message.Serialize(buffer, length);
    printf("Serialize return %d\n", l);
    printf("Before Serialize.\n");
    sample_header.PrintOptions();
    string_payload.PrintMsg();
    printf("-----------------\n");

    // UnSerialize
    ironman::serialize::SampleHeader sample_header_s;
    ironman::serialize::StringPayload string_payload_s;
    ironman::serialize::Message message_s(98120,
            &sample_header_s, &string_payload_s);
    ssize_t m = message_s.UnSerialize(buffer, length);
    printf("UnSerialzie return %d\n", m);
    printf("After Unserialize.\n");
    sample_header_s.PrintOptions();
    string_payload_s.PrintMsg();
    printf("-----------------\n");

    free(buffer);
    buffer = NULL;

}

// MessageFactory
//
TEST(RPC, D)
{
    // Serialize
    ironman::serialize::SampleHeader sample_header(55443322, 7788231, 118);
    ironman::serialize::Header *header = &sample_header;

    ironman::serialize::StringPayload string_payload("AMND Hello World!");
    ironman::serialize::Payload *payload = &string_payload;

    ironman::serialize::Message message(98120, header, payload);
    ironman::serialize::rpc::MessageFactory message_factory(&message);

    void *buffer = malloc(1000);
    size_t length = 1000;
    memset(buffer, 0, length);
    ssize_t count = message_factory.Serialize(buffer, length);
    printf("massage_factory.serialize count=%d, length=%d.\n", (int)count, (int)length);
    printf("Before Serialize.\n");
    sample_header.PrintOptions();
    string_payload.PrintMsg();
    printf("-----------------\n");

    // UnSerialize
    ironman::serialize::SampleHeader sample_header_s;
    ironman::serialize::StringPayload string_payload_s;
    ironman::serialize::Message message_s(98120, &sample_header_s, &string_payload_s);
    ironman::serialize::rpc::MessageFactory s(&message_s);
    count = s.GetMessageLength(buffer, length);
    printf("MessageFactory.GetMessageLength count=%d.\n", (int)count);
    count = s.OnMessage(buffer, count);
    printf("MessageFactory.OnMessage count=%d.\n", (int)count);
    printf("After Unserialize.\n");
    sample_header_s.PrintOptions();
    string_payload_s.PrintMsg();
    printf("-----------------\n");

    free(buffer);
    buffer = NULL;
}

// Rpc.Sended
TEST(RPC, E)
{
    int fd = open("xx", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (fd <0) {
        printf("open error.\m");
        return ;
    }
    // Serialize
    ironman::serialize::SampleHeader sample_header(55443322, 7788231, 118);
    ironman::serialize::Header *header = &sample_header;

    ironman::serialize::StringPayload string_payload("AMND Hello World!");
    ironman::serialize::Payload *payload = &string_payload;

    ironman::serialize::Message message(98120, header, payload);
    ironman::serialize::rpc::MessageFactory message_factory(&message);

    ironman::serialize::rpc::RpcBase rpc_base;
    int ret = rpc_base.Sended(fd, &message_factory);
    printf("RpcBase.Sended ret=%d.\n", ret);
    sample_header.PrintOptions();
    string_payload.PrintMsg();
    close(fd);
}

// Rpc.Received
TEST(RPC, F)
{
    int fd = open("xx", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (fd <0) {
        printf("open error.\m");
        return ;
    }

    ironman::serialize::SampleHeader sample_header;
    ironman::serialize::StringPayload string_payload;
    ironman::serialize::Message message(98120, &sample_header, &string_payload);
    ironman::serialize::rpc::MessageFactory message_factory(&message);
    ironman::serialize::rpc::RpcBase rpc_base;
    int ret = rpc_base.Received(fd, &message_factory);
    printf("RpcBase.Received ret=%d.\n", ret);
    sample_header.PrintOptions();
    string_payload.PrintMsg();
    close(fd);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
