#include <stdexcept>
#include <atomic>
#include "FieldMessage.h"

void FieldMessage::SetIntField(FieldMessage::Field field, int32_t value) {
    // If field is not found
    if (!Has(field) &&
        !IsStringField(field)) {
        fields_.emplace(field, value);
        SetMaskBit(field);
        messageSize_ += FieldMessage::kINT_FIELD_SIZE;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

void FieldMessage::SetStringField(FieldMessage::Field field, std::string value) {
    // If field is not found
    if (!Has(field) &&
        IsStringField(field)) {
        auto length = value.length();
        fields_.emplace(field, std::move(value));
        SetMaskBit(field);
        messageSize_ += FieldMessage::kSTRING_HEADER_SIZE + length;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

int32_t FieldMessage::GetIntField(FieldMessage::Field field) const {
    return std::get<int32_t>(fields_.find(field)->second);
}

std::string FieldMessage::GetStringField(FieldMessage::Field field) const {
    return std::get<std::string>(fields_.find(field)->second);
}

bool FieldMessage::Has(FieldMessage::Field field) const noexcept {
    return fields_.contains(field);
}

void FieldMessage::DeleteField(FieldMessage::Field field) {
    if (auto found = fields_.find(field); found != fields_.end()) {
        if (IsStringField(field)) {
            messageSize_ -= (FieldMessage::kSTRING_HEADER_SIZE + get<std::string>(found->second).size());
        } else {
            messageSize_ -= FieldMessage::kINT_FIELD_SIZE;
        }
        fields_.erase(field);
    }
}

const size_t & FieldMessage::GetMessageSize() const { return messageSize_; }

FieldMessage::FieldMessage() : messageSize_(FieldMessage::kHEADER_SIZE) {
    static std::atomic<std::int64_t> idNumber;
    id_ = "message-" + std::to_string(idNumber.fetch_add(1));
}

FieldMessage::FieldMessage(BitMask bitMask) : FieldMessage() {
    bitMask_ = bitMask;
}

bool FieldMessage::IsStringField(FieldMessage::Field field) {
    return field == Field::PlayerName || field == Field::Position || field == Field::Direction;
}

bool FieldMessage::IsStringField(FieldMessage::BitMask mask) {
    return FieldMessage::IsStringField(static_cast<Field>(mask));
}

FieldMessage::BitMask FieldMessage::GetBitmask() const { return bitMask_; }

const std::map<FieldMessage::Field, FieldMessage::SupportedType> & FieldMessage::GetFields() const { return fields_; }

bool FieldMessage::GetBitmaskValue(std::uint64_t bits) const { return bitMask_ & bits; }

bool FieldMessage::GetBitmaskValue(FieldMessage::Field bits) const {
    return GetBitmaskValue(static_cast<std::underlying_type_t<Field>>(bits));
}

void FieldMessage::SetMaskBit(std::uint64_t bits) { bitMask_ |= bits; }

void FieldMessage::SetMaskBit(FieldMessage::Field bits) {
    SetMaskBit(static_cast<std::underlying_type_t<Field>>(bits));
}

bool FieldMessage::operator==(const FieldMessage &rhs) const {
    return fields_ == rhs.fields_ &&
           bitMask_ == rhs.bitMask_ &&
           messageSize_ == rhs.messageSize_;
}

std::string_view FieldMessage::GetId() const { return id_; }
