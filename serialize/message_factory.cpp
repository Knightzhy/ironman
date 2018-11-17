namespace ironman{
namespace serialize{
namespace rpc{
ssize_t MessageFactory::GetMessageLength(const void *buffer, size_t length)
{
    ssize_t l = Message::GetMessageLength(buffer, length);
    printf("MessageLength [%d].\n", (int)l);
    return l;
}

ssize_t MessageFactory::OnMessage(const void *buffer, size_t length)
{
    ironman::serialize::Message message();
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
    string_payload_s.PrintMsg();
    return 0;
}

virtual ssize_t MessageFactory::Serialize(void *buffer, size_t *length)
{
    size_t buffer_length = _message.GetMessageLength();
    void *buffer = malloc(length);
    *length = _message.Serialize(buffer, buffer_length);
    return *length;
}

} // namespace rpc
} // namespace serialize
} // namespace ironman
