#include "FieldMessage.h"

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
    std::bitset<8> messageSizeBitset(messageSize_);
    std::string serialized;

    constexpr auto delimiter = "@";
    auto allFieldInBitset = AllFieldsToBitset();

    serialized
            .append(delimiter)
            .append(messageSizeBitset.to_string())
            .append(delimiter)
            .append(allFieldInBitset.to_string());

    auto fieldsAndValueTypes = GetAllFieldsWithTypes();
    for (const auto & fieldAndValue : fieldsAndValueTypes) {
        auto type = fieldAndValue.second;
        serialized.append(delimiter).append(std::to_string(type));
        // If uint64 type
        if (type == UINT64_TYPE_CODE) {
            serialized.append(std::to_string(get<std::uint64_t>(fields_.find(fieldAndValue.first)->second)));
        }
            // If std::string type
        else if (type == STRING_TYPE_CODE) {
            auto strValue = get<std::string>(fields_.find(fieldAndValue.first)->second);
            serialized.append(std::to_string(strValue.size())).append(strValue);
        }
    }
    serialized.append(delimiter);
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
    for (const auto & pair : fields_)
        field_and_type.emplace(pair.first, GetFieldValueType(pair.first));

    return field_and_type;
}
