#include "FieldMessage.h"
#include "FieldMessageSerializer.h"

void FieldMessage::SetIntField(FieldMessage::Field field, int32_t value) {
    // If field is not found
    if (!Has(field) &&
        !IsStringField(field)) {
        fields_.emplace(field, value);
        SetBitmaskField(field);
        messageSize_ += FieldMessageSerializer::kINT_FIELD_SIZE;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

void FieldMessage::SetStringField(FieldMessage::Field field, const std::string &value) {
    // If field is not found
    if (!Has(field) &&
        IsStringField(field)) {
        fields_.emplace(field, value);
        SetBitmaskField(field);
        messageSize_ += FieldMessageSerializer::kSTRING_HEADER_SIZE + value.length();
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
            messageSize_ -= (FieldMessageSerializer::kSTRING_HEADER_SIZE + get<std::string>(found->second).size());
        } else {
            messageSize_ -= FieldMessageSerializer::kINT_FIELD_SIZE;
        }
        fields_.erase(field);
    }
}

std::uint64_t FieldMessage::GetMessageSize() const { return messageSize_; }

FieldMessage::FieldMessage() : messageSize_(FieldMessageSerializer::kHEADER_SIZE) {
    static std::int64_t idNumber;
    idNumber_ = idNumber;
    id_ = "message-" + std::to_string(idNumber++);
}

FieldMessage::FieldMessage(BitMask bitMask) : FieldMessage() {
    bitMask_ = bitMask;
}

bool FieldMessage::IsStringField(FieldMessage::Field field) {
    return field == Field::PlayerName || field == Field::Position || field == Field::Direction;
}

bool FieldMessage::IsStringField(FieldMessage::BitMask mask) {
    auto field = static_cast<Field>(mask);
    return field == Field::PlayerName || field == Field::Position || field == Field::Direction;
}

FieldMessage::BitMask FieldMessage::GetBitmask() const  { return bitMask_; }

std::map<FieldMessage::Field, FieldMessage::SupportedType> FieldMessage::GetFields() const { return fields_; }

bool FieldMessage::GetBitmaskValue(std::uint64_t bits) const { return bitMask_ & bits; }

bool FieldMessage::GetBitmaskValue(FieldMessage::Field bits) const {
    return GetBitmaskValue(static_cast<std::underlying_type_t<Field>>(bits));
}

void FieldMessage::SetBitmaskField(std::uint64_t bits) { bitMask_ |= bits; }

void FieldMessage::SetBitmaskField(FieldMessage::Field bits) {
    SetBitmaskField(static_cast<std::underlying_type_t<Field>>(bits));
}

bool FieldMessage::operator==(const FieldMessage &rhs) const {
    return fields_ == rhs.fields_ &&
           bitMask_ == rhs.bitMask_ &&
           messageSize_ == rhs.messageSize_;
}

bool FieldMessage::operator!=(const FieldMessage &rhs) const {
    return !(rhs == *this);
}

std::string_view FieldMessage::GetId() const {
    return id_;
}
