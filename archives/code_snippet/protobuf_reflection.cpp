#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include <string>

#include <arpa/inet.h>  // htonl, ntohl
#include <stdint.h>

// struct ProtobufTransportFormat __attribute__ ((__packed__))
// {
//   int32_t  len;
//   int32_t  nameLen;
//   char     typeName[nameLen];
//   char     protobufData[len-nameLen-4];
// }

const int32_t kHeaderLen = sizeof(int32_t);
///
/// Encode protobuf Message to transport format defined above
/// returns a std::string.
///
/// returns a empty string if message.AppendToString() fails.
///
inline std::string Encode(const google::protobuf::Message& message)
{
    std::string result;

    result.resize(kHeaderLen);

    const std::string& typeName = message.GetTypeName();
    int32_t nameLen = static_cast<int32_t>(typeName.size() + 1);
    int32_t be32 = ::htonl(nameLen);
    result.append(reinterpret_cast<char*>(&be32), sizeof(be32));
    result.append(typeName.c_str(), nameLen);
    bool succeed = message.AppendToString(&result);

    if (succeed)
    {
        int32_t len = ::htonl(result.size() - kHeaderLen);
        std::copy(reinterpret_cast<char*>(&len),
                reinterpret_cast<char*>(&len) + sizeof(len),
                result.begin());
    }
    else
    {
        result.clear();
    }

    return result;
}

inline google::protobuf::Message* CreateMessage(const std::string& type_name)
{
    google::protobuf::Message* message = nullptr;
    const google::protobuf::Descriptor* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    if (descriptor)
    {
        const google::protobuf::Message* prototype =
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if (prototype)
        {
            message = prototype->New();
        }
    }
    return message;
}

inline int32_t AsInt32(const char* buf)
{
    int32_t be32 = 0;
    ::memcpy(&be32, buf, sizeof(be32));
    return ::ntohl(be32);
}

///
/// Decode protobuf Message from transport format defined above.
/// returns a Message*
///
/// returns nullptr if fails.
///
inline google::protobuf::Message* Decode(const std::string& buf)
{
    google::protobuf::Message* result = nullptr;

    // len(4) + nameLen(4) + typeName(2)
    assert(buf.size() >= (2 * kHeaderLen + 2));
    int32_t len = AsInt32(buf.c_str());
    assert(len == static_cast<int32_t>(buf.size() - kHeaderLen));
    int32_t nameLen = AsInt32(buf.c_str() + kHeaderLen);
    if (nameLen >= 2)
    {
        std::string typeName(buf.begin() + 2 * kHeaderLen,
            buf.begin() + 2 * kHeaderLen + nameLen - 1);
        google::protobuf::Message* message = CreateMessage(typeName);
        if (message)
        {
            const char* data = buf.c_str() + 2 * kHeaderLen + nameLen;
            int32_t dataLen = buf.size() - 2 * kHeaderLen - nameLen;
            if (message->ParseFromArray(data, dataLen))
            {
                result = message;
            }
            else
            {
                // parse error
                delete message;
            }
        }
        else
        {
            // unknown message type
        }
    }
    else
    {
        // invalid name len
    }

    return result;
}

int main()
{
    ClientInfoReq client_info;
    client_info.set_user_type(2);
    client_info.set_client_id(1101);
    client_info.set_enroll_date("2018-06-01 14:22:39");
    client_info.set_client_name("Jack");

    std::string data = Encode(client_info);

    google::protobuf::Message *message = Decode(data);
    if (dynamic_cast<ClientInfoReq *>(message))
    {
        std::cout << "succeed to call decode" << std::endl;
    }

    delete client_info2;
}