#include "FieldMessageSerializer.h"

std::string FieldMessageSerializer::Serialize(const FieldMessage &message) {
    std::ostringstream oss;

    auto messageSize = message.GetMessageSize();
    auto bitMask = message.GetBitmask();
    oss.write((char *)&messageSize, sizeof(messageSize));
    oss.write((char *)&bitMask, sizeof(bitMask));
    for (const auto & pair : message.GetFields()) {
        auto field = pair.first;
        // If std::string field
        if (FieldMessage::IsStringField(field)) {
            oss.write((char *)&STRING_TYPE_CODE, sizeof(STRING_TYPE_CODE));
            auto str = message.GetStringField(field);
            auto length = static_cast<int16_t>(str.length());
            oss.write((char *)&length, sizeof(length));
            oss.write(str.c_str(), length);
        } else {
            oss.write((char *)&INT32_TYPE_CODE, sizeof(INT32_TYPE_CODE));
            auto value = message.GetIntField(field);
            oss.write((char *)&value, sizeof(value));
        }
    }

    return oss.str();
}

FieldMessage FieldMessageSerializer::Deserialize(const std::string &serialized) {
    std::istringstream iss(serialized);
    std::uint64_t messageSize;
    FieldMessage::BitMask bitmask;
    iss.read((char *)&messageSize, sizeof(messageSize));
    iss.read((char *)&bitmask, sizeof(bitmask));
    FieldMessage message(bitmask);

    auto max = static_cast<int>(pow(2, 8));
    for (int i {1}; i <= max; i <<= 1) {
        // If flag field set
        if (message.GetBitmaskValue(i)) {
            auto field = static_cast<FieldMessage::Field>(i);
            int8_t fieldType;
            // 127 or 0
            iss.read((char *)&fieldType, sizeof(fieldType));
            // If string field set
            if (FieldMessage::IsStringField(i)) {
                int16_t length;
                iss.read((char *)&length, sizeof(length));
                char *str = new char[length];
                iss.read(str, length);
                std::string value(str);

                message.SetStringField(field, value.substr(0, length));
            } else {
                int32_t value;
                iss.read((char *)&value, sizeof(value));

                message.SetIntField(field, value);
            }
        }
    }

    return message;
}
