#ifndef BATTLECITY_FIELDMESSAGESERIALIZER_H
#define BATTLECITY_FIELDMESSAGESERIALIZER_H

#include "FieldMessage.h"

class FieldMessageSerializer {

public:
    static constexpr int8_t INT32_TYPE_CODE = 0;
    static constexpr int8_t STRING_TYPE_CODE = 127;

public:
    FieldMessageSerializer() = delete;

public:
    static std::string Serialize(const FieldMessage &message);

    static FieldMessage Deserialize(std::string &&serialized);
};


#endif //BATTLECITY_FIELDMESSAGESERIALIZER_H
