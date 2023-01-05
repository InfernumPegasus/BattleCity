#include "FieldMessage.h"
#include <cmath>

void FieldMessage::SetIntField(FieldMessage::Field field, int32_t value) {
    // If field is not found
    if (!Has(field) &&
        field != Field::PlayerName &&
        field != Field::Position &&
        field != Field::Direction &&
        !GetBitmaskValue(field)) {
        fields_.emplace(field, value);
        SetBitmaskField(field);
        messageSize_ += kINT_FIELD_SIZE;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

void FieldMessage::SetStringField(FieldMessage::Field field, const std::string &value) {
    // If field is not found
    if (!Has(field) &&
        (field == Field::PlayerName ||
         field == Field::Position ||
         field == Field::Direction) &&
        !GetBitmaskValue(field)) {
        fields_.emplace(field, value);
        SetBitmaskField(field);
        messageSize_ += kSTRING_HEADER_SIZE + value.length();
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

int32_t FieldMessage::GetIntField(FieldMessage::Field field) const {
    if (!fields_.contains(field))
        throw std::logic_error("No such field!");
    auto found = fields_.find(field);

    if (std::holds_alternative<std::string>(found->second))
        throw std::logic_error("Wrong type!");

    return std::get<int32_t>(found->second);
}

std::string FieldMessage::GetStringField(FieldMessage::Field field) const {
    if (!fields_.contains(field))
        throw std::logic_error("No such field!");
    auto found = fields_.find(field);

    if (std::holds_alternative<int32_t>(found->second)) {
        throw std::logic_error("Wrong type!");
    }
    return std::get<std::string>(found->second);
}

bool FieldMessage::Has(FieldMessage::Field field) const {
    return fields_.contains(field);
}

void FieldMessage::DeleteField(FieldMessage::Field field) {
    auto found = fields_.find(field);
    if (found != fields_.end()) {
        if (IsStringField(field)) {
            messageSize_ -= (kSTRING_HEADER_SIZE + get<std::string>(found->second).size());
        } else {
            messageSize_ -= kINT_FIELD_SIZE;
        }
        fields_.erase(field);
    }
}

std::ostream &operator<<(std::ostream &os, std::variant<int32_t, std::string> const &v) {
    std::visit([&os](auto const &x) { os << x; }, v);
    return os;
}

void FieldMessage::Print() const {
    for (const auto &item: fields_) {
        std::string typeStr = item.second.index() == 0 ? "uint_64_t" : "string";
        std::cout << "Attribute: " << static_cast<std::uint64_t>(item.first)
                  << " | Value type: " << typeStr
                  << " | Value: " << item.second << std::endl;
    }
}

std::int64_t FieldMessage::GetMessageIdNumber() const { return idNumber_; }

std::string FieldMessage::GetId() const { return id_; }

std::uint64_t FieldMessage::GetMessageSize() const { return messageSize_; }

FieldMessage::FieldMessage() : messageSize_(kHEADER_SIZE) {
    static std::int64_t idNumber;
    idNumber_ = idNumber;
    id_ = "message-" + std::to_string(idNumber++);
}

std::string FieldMessage::Serialize() const {
    std::string serialized;
    std::bitset<kHEADER_SIZE / 2> size(messageSize_);
    std::bitset<kHEADER_SIZE / 2> mask(bitMask_);

//    std::cout << "size: " << size.to_string() << " mask: " << mask.to_string() << std::endl;
    serialized
    .append(size.to_string())
//    .append("[")
    .append(mask.to_string());
//    .append("]");

    for (const auto &pair : fields_) {
//        serialized.append("[");
        if (IsStringField(pair.first)) {
            std::bitset<8> t(STRING_TYPE_CODE);
            auto typeStr = t.to_string();
            auto value = get<std::string>(pair.second);
            std::bitset<16> length(value.length());

            serialized
            .append(typeStr)
//            .append(" ")
            .append(length.to_string())
//            .append(" ")
            .append(value);
        } else {
            std::bitset<8> t(INT32_TYPE_CODE);
            auto typeStr = t.to_string();
            std::bitset<32> value(get<std::int32_t>(pair.second));
            serialized
            .append(typeStr)
//            .append(" ")
            .append(value.to_string());
        }
//        serialized.append("]");
    }
//    std::cout << "Length: " << serialized.length() << ", length % 8: " << serialized.length() % 8 << std::endl;
    return serialized;
}


    }
    throw std::runtime_error("Cannot identify field value type!");
}

std::map<FieldMessage::Field, int> FieldMessage::GetAllFieldsWithTypes() const {
    std::map<Field, int> field_and_type;
    for (const auto &pair: fields_)
        field_and_type.emplace(pair.first, GetFieldValueType(pair.first));

    return field_and_type;
}

std::bitset<8> StringToBits(const std::string_view &string) {
    std::bitset<8> bits(string.data());
    return bits;
}

FieldMessage FieldMessage::Deserialize(const std::string_view &serialized) {
    FieldMessage message;
    std::bitset<8> msgSize(std::string_view{serialized.substr(0, 7)}.data());
    auto size = msgSize.to_ullong();
    std::bitset<8> bitMask(std::string_view{serialized.substr(8, 15)}.data());

    std::cout << "Size from string (bin): " << msgSize << std::endl;
    std::cout << "Bitmask: " << bitMask << std::endl;

    for (auto pos {0}; pos < bitMask.size(); pos++) {
//        auto field = static_cast<Field>(pos);
        if (bitMask.test(pos)) {
            auto bitValue = static_cast<uint64_t>(pow(2, pos));
            auto field = static_cast<Field>(bitValue);

            switch (field) {
                case Field::PlayerName:
                case Field::Position:
                case Field::Direction:
                    message.SetStringField(field, "value-" + std::to_string(pos));
                    std::cout << "SetStringField to: " << pos << std::endl;
                    break;

                case Field::TankSpeed:
                case Field::TankHp:
                case Field::ObstacleDurability:
                    message.SetIntField(field, pos);
                    std::cout << "SetIntField to: " << pos << std::endl;
                    break;
            }
        }
    }

    std::cout << "Size from string: " << size << " , actual size: " << message.GetMessageSize() << std::endl;
    if (message.GetMessageSize() != size) {
        throw std::range_error("Message sizes are not equal!");
    }

    return message;
}bool FieldMessage::IsStringField(FieldMessage::Field field) {
    return field == Field::PlayerName || field == Field::Position || field == Field::Direction;
}

FieldMessage::BitMask FieldMessage::GetBitmask() const  { return bitMask_; }
