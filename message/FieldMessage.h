#ifndef BATTLECITY_FIELDMESSAGE_H
#define BATTLECITY_FIELDMESSAGE_H

#include <variant>
#include <map>
#include <string>
#include <iostream>
#include <bitset>

class FieldMessage {

private:
    using SupportedType = std::variant<uint64_t, std::string>;

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

    [[maybe_unused]]
    friend Field operator|(const Field &first, const Field &second) {
        return static_cast<Field>(
                static_cast<std::underlying_type_t<Field>>(std::to_underlying(first)) |
                static_cast<std::underlying_type_t<Field>>(std::to_underlying(second)));
    }

public:
    FieldMessage();

public:

    void SetIntField(Field field, uint64_t value);

    void SetStringField(Field field, std::string value);

    [[nodiscard]] uint64_t GetIntField(Field field) const;

    [[nodiscard]] std::string GetStringField(Field field) const;

    [[nodiscard]] bool Has(Field field) const;

    void DeleteField(Field field);

    void Print() const;

    [[nodiscard]] std::int64_t GetMessageIdNumber() const;

    [[nodiscard]] std::string GetId() const;

    [[nodiscard]] std::int64_t GetMessageSize() const;

    [[nodiscard]] std::string Serialize() const;

private:
    static std::bitset<8> FieldToBitset(Field field);

    [[nodiscard]] std::bitset<8> AllFieldsToBitset() const;

    [[nodiscard]] int GetFieldValueType(Field field) const;

    [[nodiscard]] std::map<Field, int> GetAllFieldsWithTypes() const;

private:
    static constexpr int MAX_FIELDS = 64;
    static constexpr int UINT64_TYPE_CODE = 0;
    static constexpr int STRING_TYPE_CODE = 127;

    // Map of fields
    std::map<Field, SupportedType> fields_;

    // Defines Field quantity (up to 64 in one message)
    std::int64_t messageSize_;

    // Unique message id
    std::string id_;

    // ID number which is used for generating id
    std::int64_t idNumber_;
};


#endif //BATTLECITY_FIELDMESSAGE_H
