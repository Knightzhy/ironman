#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtest/gtest.h>
#include "../serialize/string_payload.h"
#include "../serialize/sample_header.h"
#include "../serialize/message.h"

TEST(PAYLOAD, A)
{
    ironman::serialize::StringPayload string_payload("AMND");
    size_t length = string_payload.GetPayloadLength();
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
    string_payload2->UnSerialize(buffer, (size_t)l);
    size_t length2 = string_payload2->GetPayloadLength();
    char *buffer2 = (char *)malloc(length2);
    ssize_t w = string_payload2->Serialize(buffer2, length2);
    if (w < 0) {
        printf("Serialize error\n");
        return;
    }
    printf("length=%d, l=%d,msg=%s\n",
            (int)length2, (int)w, buffer2);
}

TEST(PAYLOAD, B)
{
    ironman::serialize::SampleHeader sample_header;
    sample_header.Init();
    sample_header.SetMagic(55443322);
    sample_header.SetSeq(7788231);
    sample_header.SetInterface(118);
    ironman::serialize::Header *header = &sample_header;
    printf("header:%p, %p, %d, %d, %ld, %d\n",
            header, &sample_header,
            (int)header->GetHeaderLength(),
            sample_header.GetMagic(),
            sample_header.GetSeq(),
            sample_header.GetInterface());
    void *buffer = malloc(header->GetHeaderLength());
    ssize_t length = header->Serialize(buffer, header->GetHeaderLength());
    printf("buffer:%p, %d\n", buffer, (int)length);

    ironman::serialize::SampleHeader *sample =
        new ironman::serialize::SampleHeader;
    sample->Init();
    ironman::serialize::Header *header2 = sample;
    header2->UnSerialize(buffer, (size_t)length);
    printf("sample:%p, %p, %d, %ld, %d\n",
            sample, header2,
            sample->GetMagic(),
            sample->GetSeq(), sample->GetInterface());

    free(buffer);
    buffer = NULL;
    delete sample;
    sample = NULL;
    header2 = NULL;
}

TEST(MSG, A)
{
    ironman::serialize::SampleHeader sample_header;
    sample_header.Init();
    sample_header.SetMagic(55443322);
    sample_header.SetSeq(7788231);
    sample_header.SetInterface(118);
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

    /*************/
    ironman::serialize::SampleHeader sample_header_s;
    ironman::serialize::StringPayload string_payload_s;
    ironman::serialize::Message message_s(98120,
            &sample_header_s, &string_payload_s);
    ssize_t m = message_s.UnSerialize(buffer, length);
    printf("UnSerialzie return %d\n", m);
    printf("header:magic=%d, seq=%d, interface=%d\n",
            sample_header_s.GetMagic(),
            sample_header_s.GetSeq(),
            sample_header_s.GetInterface());
    printf("payload:");

    free(buffer);
    buffer = NULL;

    buffer = malloc(100);
    memset(buffer, 0 , 100);
    string_payload_s.Serialize(buffer, 100);
    printf("string_payload:msg=%s\n", buffer);
    free(buffer);
    buffer = NULL;
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
