#ifndef BATTLECITY_FIELDMESSAGE_H
#define BATTLECITY_FIELDMESSAGE_H

#include <variant>
#include <map>
#include <string>
#include <iostream>
#include <bitset>
#include <vector>

class FieldMessage {
public:
    // Defines field attributes
    enum class Field : std::uint64_t {
        PlayerName          = 0B00000001,       // Only std::string
        Position            = 0B00000010,       // Only std::string
        Direction           = 0B00000100,       // Only std::string
        TankSpeed           = 0B00001000,       // Only std::uint64_t
        TankHp              = 0B00010000,       // Only std::uint64_t
        ObstacleDurability  = 0B00100000        // Only std::uint64_t
    };

private:
    using SupportedType = std::variant<int32_t, std::string>;
    using BitMask = std::underlying_type_t<Field>;

public:
    FieldMessage();

    void SetIntField(Field field, int32_t value);

    void SetStringField(Field field, const std::string &value);

    [[nodiscard]] int32_t GetIntField(Field field) const;

    [[nodiscard]] std::string GetStringField(Field field) const;

    [[nodiscard]] bool Has(Field field) const;

    void DeleteField(Field field);

    void Print() const;

    [[nodiscard]] std::int64_t GetMessageIdNumber() const;

    [[nodiscard]] std::string GetId() const;

    [[nodiscard]] std::uint64_t GetMessageSize() const;

    [[nodiscard]] BitMask GetBitmask() const;

    static bool IsStringField(Field field);

    [[nodiscard]] std::string Serialize() const;

    static FieldMessage Deserialize(const std::string_view &serialized);

private:

    [[nodiscard]] bool GetBitmaskValue(std::uint64_t bit) const {
        return bitMask_ & bit;
    }

    [[nodiscard]] bool GetBitmaskValue(Field bit) const {
        return GetBitmaskValue(static_cast<std::underlying_type_t<Field>>(bit));
    }

    void SetBitmaskField(std::uint64_t bit) {
        bitMask_ |= bit;
    }

    void SetBitmaskField(Field bit) {
        SetBitmaskField(static_cast<std::underlying_type_t<Field>>(bit));
    }

public:
    static constexpr auto kHEADER_SIZE = 16;            // MsgSize + Bitmask length
    static constexpr auto kINT_FIELD_SIZE = 5;          // 1 byte for type, 4 bytes for value
    static constexpr auto kSTRING_HEADER_SIZE = 3;      // 1 byte for type, 2 bytes for length (also need string length)

private:
    static constexpr int INT32_TYPE_CODE = 0;
    static constexpr int STRING_TYPE_CODE = 127;

    // Map of fields
    std::map<Field, SupportedType> fields_;

    // Bit mask for fields
    BitMask bitMask_ = 0b00'000'000;

    // Defines Field quantity (up to 64 in one message)
    std::uint64_t messageSize_;

    // Unique message id
    std::string id_;

    // ID number which is used for generating id
    std::int64_t idNumber_;
};


#endif //BATTLECITY_FIELDMESSAGE_H
