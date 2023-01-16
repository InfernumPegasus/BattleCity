#include <cmath>
#include <sstream>
#include "FieldMessageSerializer.h"

std::string FieldMessageSerializer::Serialize(const FieldMessage &message) {
    std::ostringstream oss;

    auto messageSize = message.GetMessageSize();
    auto bitMask = message.GetBitmask();
    oss.write(reinterpret_cast<char *>(&messageSize), sizeof(messageSize));
    oss.write(reinterpret_cast<char *>(&bitMask), sizeof(bitMask));

    for (int val {1}, pos {1}; pos <= kBITMASK_LENGTH_BYTES; val <<= 1, pos++) {
        auto field = static_cast<FieldMessage::Field>(val);
        if (!FieldMessage::IsValidField(field)) {
            break;
        }
        if (message.HasField(field)) {
            if (FieldMessage::IsStringField(field)) {
                oss.write((char *)&kSTRING_TYPE_CODE, sizeof(kSTRING_TYPE_CODE));
                auto str = message.GetStringField(field);
                auto length = static_cast<int16_t>(str.length());
                oss.write(reinterpret_cast<char *>(&length), sizeof(length));
                oss.write(str.c_str(), length);
            } else {
                oss.write((char *)&kINT32_TYPE_CODE, sizeof(kINT32_TYPE_CODE));
                auto value = message.GetIntField(field);
                oss.write(reinterpret_cast<char *>(&value), sizeof(value));
            }
        }
    }

    return oss.str();
}

FieldMessage FieldMessageSerializer::Deserialize(const std::string &serialized) {
    std::istringstream iss(serialized);
    std::size_t messageSize;
    FieldMessage::BitMask bitmask;
    iss.read(reinterpret_cast<char *>(&messageSize), sizeof(messageSize));
    iss.read(reinterpret_cast<char *>(&bitmask), sizeof(bitmask));
    FieldMessage message(bitmask);

    if (bitmask == 0 && messageSize == FieldMessage::kHEADER_SIZE) {
        return message;
    }

    for (int val {1}, pos {1}; pos <= kBITMASK_LENGTH_BYTES; val <<= 1, pos++) {
        // If flag field set
        if (message.GetBitmaskValue(val)) {
            auto field = static_cast<FieldMessage::Field>(val);
            if (!FieldMessage::IsValidField(field)) {
                throw std::runtime_error("Wrong serialized string provided!");
            }
            int8_t fieldType;
            iss.read(reinterpret_cast<char *>(&fieldType), sizeof(fieldType));
            if (fieldType != kINT32_TYPE_CODE && fieldType != kSTRING_TYPE_CODE) {
                throw std::runtime_error("Cannot identify field type!");
            }
            // If string field set
            if (FieldMessage::IsStringField(val)) {
                int16_t length;
                iss.read(reinterpret_cast<char *>(&length), sizeof(length));
                auto value = std::string(length, '\0');
                iss.read(&value.at(0), length);

                message.SetStringField(field, value);
            } else {
                int32_t value;
                iss.read(reinterpret_cast<char *>(&value), sizeof(value));

                message.SetIntField(field, value);
            }
        }
    }

    if (message.GetMessageSize() != messageSize && message.GetMessageSize() != serialized.size()) {
        throw std::runtime_error("Wrong message size!");
    }

    return message;
}
