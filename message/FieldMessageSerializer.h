#ifndef BATTLECITY_FIELDMESSAGESERIALIZER_H
#define BATTLECITY_FIELDMESSAGESERIALIZER_H

#include <string>
#include <map>
#include <variant>
#include <sstream>
#include <cmath>
#include "FieldMessage.h"

class FieldMessageSerializer {

public:
    static constexpr int8_t INT32_TYPE_CODE = 0;
    static constexpr int8_t STRING_TYPE_CODE = 127;

    static constexpr auto kHEADER_SIZE = 16;        // MsgSize + Bitmask length
    static constexpr auto kINT_FIELD_SIZE = 5;      // 1 byte for type, 4 bytes for value
    static constexpr auto kSTRING_HEADER_SIZE = 3;  // 1 byte for type, 2 bytes for length (also need string length)

public:
    FieldMessageSerializer() = delete;

public:
    static std::string Serialize(const FieldMessage &message);

    static FieldMessage Deserialize(const std::string &serialized);
};


#endif //BATTLECITY_FIELDMESSAGESERIALIZER_H
