#ifndef BATTLECITY_FIELDMESSAGE_H
#define BATTLECITY_FIELDMESSAGE_H

#include <variant>
#include <unordered_map>
#include <string>

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

    using BitMask = std::underlying_type_t<Field>;
    using SupportedType = std::variant<int32_t, std::string>;

    static constexpr auto kHEADER_SIZE = 16;        // MsgSize + Bitmask length
    static constexpr auto kINT_FIELD_SIZE = 5;      // 1 byte for type, 4 bytes for value
    static constexpr auto kSTRING_HEADER_SIZE = 3;  // 1 byte for type, 2 bytes for length (also need string length)

public:
    FieldMessage();
    explicit FieldMessage(BitMask bitMask);

    bool operator==(const FieldMessage &rhs) const;

public:
    void SetIntField(Field field, int32_t value);

    void SetStringField(Field field, std::string value);

    [[nodiscard]] int32_t GetIntField(Field field) const;

    [[nodiscard]] std::string GetStringField(Field field) const;

    [[nodiscard]] bool Has(Field field) const noexcept;

    void DeleteField(Field field);

    [[nodiscard]] const size_t & GetMessageSize() const;

    [[nodiscard]] BitMask GetBitmask() const;

    [[nodiscard]] const std::unordered_map<Field, SupportedType> & GetFields() const;

    static bool IsStringField(Field field);

    static bool IsStringField(BitMask mask);

    [[nodiscard]] bool GetBitmaskValue(std::uint64_t bits) const;

    [[nodiscard]] bool GetBitmaskValue(Field bits) const;

    [[nodiscard]] std::string_view GetId() const;

private:
    void SetMaskBit(std::uint64_t bits);

    void SetMaskBit(Field bits);

private:
    // Map of fields
    std::unordered_map<Field, SupportedType> fields_;

    // Bit mask for fields
    BitMask bitMask_ = 0B0000'0000;

    // Defines Field quantity (up to 64 in one message)
    std::size_t messageSize_;

    // Unique message id
    std::string id_;
};


#endif //BATTLECITY_FIELDMESSAGE_H
