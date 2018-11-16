#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtest/gtest.h>
#include "../serialize/string_payload.h"
#include "../serialize/sample_header.h"
#include "../serialize/sample_message.h"

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

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
