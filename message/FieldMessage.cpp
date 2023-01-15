#include <stdexcept>
#include <atomic>
#include "FieldMessage.h"

FieldMessage::FieldMessage() : messageSize_(FieldMessage::kHEADER_SIZE) {
    static std::atomic<std::int64_t> idNumber;
    id_ = "message-" + std::to_string(idNumber.fetch_add(1));
}

FieldMessage::FieldMessage(BitMask bitMask) : FieldMessage() {
    bitMask_ = bitMask;
}

bool FieldMessage::operator==(const FieldMessage &rhs) const {
    return fields_ == rhs.fields_ &&
           bitMask_ == rhs.bitMask_ &&
           messageSize_ == rhs.messageSize_;
}

void FieldMessage::SetIntField(FieldMessage::Field field, int32_t value) {
    if (!IsValidField(field)) {
        throw std::runtime_error("Invalid field!");
    }
    // If field is not found
    if (!HasField(field) &&
        !IsStringField(field)) {
        fields_.emplace(field, value);
        SetMaskBit(field);
        messageSize_ += FieldMessage::kINT_FIELD_SIZE;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

void FieldMessage::SetStringField(FieldMessage::Field field, std::string value) {
    if (!IsValidField(field)) {
        throw std::runtime_error("Invalid field!");
    }
    // If field is not found
    if (!HasField(field) &&
        IsStringField(field)) {
        auto length = value.length();
        fields_.emplace(field, std::move(value));
        SetMaskBit(field);
        messageSize_ += FieldMessage::kSTRING_HEADER_SIZE + length;
    } else {
        throw std::logic_error("Cannot set value!");
    }
}

bool FieldMessage::IsValidField(FieldMessage::Field field) {
    return field == Field::PlayerName ||
           field == Field::Position ||
           field == Field::Direction ||
           field == Field::TankSpeed ||
           field == Field::TankHp ||
           field == Field::ObstacleDurability;
}

int32_t FieldMessage::GetIntField(FieldMessage::Field field) const {
    if (!IsValidField(field)) {
        throw std::runtime_error("Invalid field!");
    }
    return std::get<int32_t>(fields_.find(field)->second);
}

std::string FieldMessage::GetStringField(FieldMessage::Field field) const {
    if (!IsValidField(field)) {
        throw std::runtime_error("Invalid field!");
    }
    return std::get<std::string>(fields_.find(field)->second);
}

size_t FieldMessage::GetMessageSize() const {
    return messageSize_;
}

FieldMessage::BitMask FieldMessage::GetBitmask() const {
    return bitMask_;
}

bool FieldMessage::GetBitmaskValue(std::uint64_t bits) const {
    return bitMask_ & bits;
}

std::string_view FieldMessage::GetId() const {
    return id_;
}

bool FieldMessage::HasField(FieldMessage::Field field) const noexcept {
    if (!IsValidField(field)) {
        return false;
    }
    return fields_.contains(field);
}

void FieldMessage::DeleteField(FieldMessage::Field field) {
    if (!IsValidField(field)) {
        throw std::runtime_error("Invalid field!");
    }
    if (auto found = fields_.find(field); found != fields_.end()) {
        if (IsStringField(field)) {
            messageSize_ -= (FieldMessage::kSTRING_HEADER_SIZE + get<std::string>(found->second).size());
        } else {
            messageSize_ -= FieldMessage::kINT_FIELD_SIZE;
        }
        fields_.erase(field);
    }
}

bool FieldMessage::IsStringField(FieldMessage::Field field) {
    if (!IsValidField(field)) {
        return false;
    }
    return field == Field::PlayerName || field == Field::Position || field == Field::Direction;
}

bool FieldMessage::IsStringField(FieldMessage::BitMask mask) {
    return FieldMessage::IsStringField(static_cast<Field>(mask));
}

void FieldMessage::SetMaskBit(std::uint64_t bits) {
    bitMask_ |= bits;
}

void FieldMessage::SetMaskBit(FieldMessage::Field bits) {
    SetMaskBit(static_cast<std::underlying_type_t<Field>>(bits));
}
