#ifndef BATTLECITY_FIELDMESSAGESERIALIZER_H
#define BATTLECITY_FIELDMESSAGESERIALIZER_H

#include "FieldMessage.h"

// Serializer for FieldMessage class
class FieldMessageSerializer {

public:
    static constexpr int8_t INT32_TYPE_CODE = 0;
    static constexpr int8_t STRING_TYPE_CODE = 127;

public:
    FieldMessageSerializer() = delete;

public:
    /*
     * Creates FieldMessage object's binary representation.
     * Encoding format:
     * [Message size (8b)] [Bit mask (8b)] [fields...].
     * std::string field is encoded in such a format:
     * [127 (1b)] [string.length() (2b)] [content]
     * std::int32_t field is encoded in a such format:
     * [0 (1b)] [content (4b)]
     */
    static std::string Serialize(const FieldMessage &message);

    /*
     * Creates FieldMessage object from serialized string
     * and fulfills all serialized fields. If serialized
     * string is not correct throws exception.
     */
    static FieldMessage Deserialize(const std::string &serialized);
};


#endif //BATTLECITY_FIELDMESSAGESERIALIZER_H
