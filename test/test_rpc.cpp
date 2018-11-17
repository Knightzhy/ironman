#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    ironman::serialize::SampleHeader sample_header;
    sample_header.SetMagic(8788);
    sample_header.SetSeq(12990);
    sample_header.SetInterface(33);

    size_t length = sample_header.GetHeaderLength();
    printf("sample_header.length=%d.\n", (int)length);

    void *buffer = malloc(length);
    ssize_t count = sample_header.Serialize(buffer, length);
    printf("sample_header.serialize count=%d.\n", (int)count);

    // UnSerialize
    ironman::serialize::SampleHeader sample_header2;
    count = sample_header2.UnSerialize(buffer, count);
    printf("sample_header.unserialize count=%d.\n", (int)count);
    printf("magic=%d, seq=%d, interface=%d.\n",
            sample_header2.GetMagic(),
            sample_header2.GetSeq(),
            sample_header2.GetInterface());

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
    ironman::serialize::SampleHeader sample_header;
    sample_header.Init();
    sample_header.SetMagic(55443322);
    sample_header.SetSeq(7788231);
    sample_header.SetInterface(118);
    ironman::serialize::Header *header = &sample_header;

    ironman::serialize::StringPayload string_payload("AMND Hello World!");
    ironman::serialize::Payload *payload = &string_payload;

    ironman::serialize::Message message(98120);
    size_t length = message.GetMessageLength(header, payload);
    printf("%d, %d, %d\n", header->GetHeaderLength(),
            payload->GetPayloadLength(), (int)length);

    void *buffer = malloc(length);
    ASSERT_TRUE(buffer != NULL);
    ssize_t l = message.Serialize(buffer, length, header, payload);
    printf("Serialize return %d\n", l);

    // UnSerialize
    ironman::serialize::SampleHeader sample_header_s;
    ironman::serialize::StringPayload string_payload_s;
    ssize_t m = message.UnSerialize(buffer, length,
            (ironman::serialize::Header*)&sample_header_s,
            (ironman::serialize::Payload*)&string_payload_s);
    printf("UnSerialzie return %d\n", m);
    printf("message:magic=%d\n", message.GetMagic());
    printf("header:magic=%d, seq=%d, interface=%d\n",
            sample_header_s.GetMagic(),
            sample_header_s.GetSeq(),
            sample_header_s.GetInterface());
    printf("payload:");
    string_payload_s.PrintMsg();

    free(buffer);
    buffer = NULL;

}

// MessageFactory
//
TEST(RPC, D)
{
}

// Rpc
TEST(RPC, E)
{}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
