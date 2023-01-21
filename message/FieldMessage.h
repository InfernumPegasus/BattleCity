#ifndef BATTLECITY_FIELDMESSAGE_H
#define BATTLECITY_FIELDMESSAGE_H

#include <variant>
#include <unordered_map>
#include <string>

/*
 * А message class that describes the parameters of entities from the BattleCity game.
 * Each parameter is described by enum flag in nested class Field
 * and can contain either std::string' either std::uint64_t' type value (immutable).
 */
class FieldMessage {
public:
    // Defines field attributes
    enum class Field : uint64_t {
        PlayerName          = 0B0000'0001,       // Only std::string
        Position            = 0B0000'0010,       // Only std::string
        Direction           = 0B0000'0100,       // Only std::string
        TankSpeed           = 0B0000'1000,       // Only uint64_t
        TankHp              = 0B0001'0000,       // Only uint64_t
        ObstacleDurability  = 0B0010'0000        // Only uint64_t
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

    void SetIntField(Field field, int32_t value);
    void SetStringField(Field field, std::string value);
    static bool IsValidField(Field field);

    [[nodiscard]] int32_t GetIntField(Field field) const;
    [[nodiscard]] std::string GetStringField(Field field) const;
    [[nodiscard]] size_t GetMessageSize() const;
    [[nodiscard]] BitMask GetBitmask() const;
    [[nodiscard]] bool GetBitmaskValue(uint64_t bits) const;
    [[nodiscard]] std::string_view GetId() const;

    [[nodiscard]] bool HasField(Field field) const noexcept;

    void DeleteField(Field field);

    static bool IsStringField(Field field);
    static bool IsStringField(BitMask mask);


private:
    void SetMaskBit(uint64_t bits);
    void SetMaskBit(Field bits);

private:
    // Map of fields
    std::unordered_map<Field, SupportedType> fields_;

    // Bit mask for fields
    BitMask bitMask_ = 0B0000'0000;

    // Defines message size in bytes
    std::size_t messageSize_;

    // Unique message id
    std::string id_;
};


#endif //BATTLECITY_FIELDMESSAGE_H
