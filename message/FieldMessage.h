#ifndef BATTLECITY_FIELDMESSAGE_H
#define BATTLECITY_FIELDMESSAGE_H

#include <variant>
#include <map>
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

public:
    FieldMessage();
    explicit FieldMessage(BitMask bitMask);

    bool operator==(const FieldMessage &rhs) const;
    bool operator!=(const FieldMessage &rhs) const;

public:
    void SetIntField(Field field, int32_t value);

    void SetStringField(Field field, const std::string &value);

    [[nodiscard]] int32_t GetIntField(Field field) const;

    [[nodiscard]] std::string GetStringField(Field field) const;

    [[nodiscard]] bool Has(Field field) const;

    void DeleteField(Field field);

    [[nodiscard]] std::uint64_t GetMessageSize() const;

    [[nodiscard]] BitMask GetBitmask() const;

    [[nodiscard]] std::map<Field, SupportedType> GetFields() const;

    static bool IsStringField(Field field);

    static bool IsStringField(BitMask mask);

    [[nodiscard]] bool GetBitmaskValue(std::uint64_t bits) const;

    [[nodiscard]] bool GetBitmaskValue(Field bits) const;

    [[nodiscard]] std::string_view GetId() const;

private:
    void SetBitmaskField(std::uint64_t bits);

    void SetBitmaskField(Field bits);

private:
    // Map of fields
    std::map<Field, SupportedType> fields_;

    // Bit mask for fields
    BitMask bitMask_ = 0B00'000'000;

    // Defines Field quantity (up to 64 in one message)
    std::uint64_t messageSize_;

    // Unique message id
    std::string id_;

    // ID number which is used for generating id
    std::int64_t idNumber_;
};


#endif //BATTLECITY_FIELDMESSAGE_H
