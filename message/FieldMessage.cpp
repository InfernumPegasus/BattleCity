#include "FieldMessage.h"
#include <cmath>

void FieldMessage::SetIntField(FieldMessage::Field field, uint64_t value) {
    // If field is not found
    if (!Has(field) &&
        field != Field::PlayerName &&
        field != Field::Position &&
        field != Field::Direction &&
        messageSize_ < MAX_FIELDS) {
        fields_.emplace(field, value);
        messageSize_++;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

void FieldMessage::SetStringField(FieldMessage::Field field, std::string value) {
    if (value.length() > 99) {
        throw std::logic_error("Value length cannot be more than 99!");
    }

    // If field is not found
    if (!Has(field) &&
        (field == Field::PlayerName ||
         field == Field::Position ||
         field == Field::Direction) &&
        messageSize_ < MAX_FIELDS) {
        fields_.emplace(field, value);
        messageSize_++;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

uint64_t FieldMessage::GetIntField(FieldMessage::Field field) const {
    if (!fields_.contains(field))
        throw std::logic_error("No such field!");
    auto found = fields_.find(field);

    if (std::holds_alternative<std::string>(found->second))
        throw std::logic_error("Wrong type!");

    return std::get<uint64_t>(found->second);
}

std::string FieldMessage::GetStringField(FieldMessage::Field field) const {
    if (!fields_.contains(field))
        throw std::logic_error("No such field!");
    auto found = fields_.find(field);

    if (std::holds_alternative<uint64_t>(found->second)) {
        throw std::logic_error("Wrong type!");
    }
    return std::get<std::string>(found->second);
}

bool FieldMessage::Has(FieldMessage::Field field) const {
    return fields_.contains(field);
}

void FieldMessage::DeleteField(FieldMessage::Field field) {
    if (fields_.contains(field)) {
        fields_.erase(field);
        messageSize_--;
    }
}

void FieldMessage::Print() const {
    for (const auto &item: fields_) {
        std::cout << "Attribute: " << static_cast<std::uint64_t>(item.first) << " | Value type: "
                  << (item.second.index() == 0 ? "uint_64_t" : "string") << std::endl;
    }
}

std::int64_t FieldMessage::GetMessageIdNumber() const { return idNumber_; }

std::string FieldMessage::GetId() const { return id_; }

std::int64_t FieldMessage::GetMessageSize() const { return messageSize_; }

FieldMessage::FieldMessage() : messageSize_(0) {
    static std::int64_t idNumber;
    idNumber_ = idNumber;
    id_ = "message-" + std::to_string(idNumber++);
}

std::string FieldMessage::Serialize() const {
    std::string serialized;
    std::bitset<8> messageSizeBitset(messageSize_);
    auto allFieldInBitset = AllFieldsToBitset();

    serialized
            .append(messageSizeBitset.to_string())
            .append(allFieldInBitset.to_string());

    auto fieldsAndValueTypes = GetAllFieldsWithTypes();
    for (const auto &fieldAndValue: fieldsAndValueTypes) {
        auto type = fieldAndValue.second;
        serialized.append(std::to_string(type));
        // If uint64 type
        if (type == UINT64_TYPE_CODE) {
            serialized.append(std::to_string(get<std::uint64_t>(fields_.find(fieldAndValue.first)->second)));
        }
        // If std::string type
        else if (type == STRING_TYPE_CODE) {
            auto strValue = get<std::string>(fields_.find(fieldAndValue.first)->second);
            auto length = strValue.length();
            auto lengthStr = length < 10 ? "0" + std::to_string(length) : std::to_string(length);
            serialized.append(lengthStr).append(strValue);
        }
    }
    return serialized;
}

std::bitset<8> FieldMessage::FieldToBitset(FieldMessage::Field field) {
    std::bitset<8> bitset(static_cast<uint64_t>(field));
    return bitset;
}

std::bitset<8> FieldMessage::AllFieldsToBitset() const {
    std::bitset<8> bitset;
    for (const auto &item: fields_)
        bitset.operator^=(FieldToBitset(item.first));

    return bitset;
}

int FieldMessage::GetFieldValueType(FieldMessage::Field field) const {
    auto found = fields_.find(field);
    if (found == fields_.end()) {
        throw std::runtime_error("Cannot find field!");
    } else if (holds_alternative<std::string>(found->second)) {
        return 127;
    } else if (holds_alternative<std::uint64_t>(found->second)) {
        return 0;
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
}