#include <cassert>
#include <iostream>
#include "message/FieldMessage.h"
#include "message/FieldMessageSerializer.h"

/*
    Разработать класс сообщения, которое представляет из себя набор полей.
    Поле может быть строковым(ASCII) или целочисленным(32 бита).
    Набор полей задается вложенным в класс сообщения enum class
    (придумать самостоятельно ориентируясь на параметры которыми могут быть описаны объекты в игре Battle City, например:
    скорость, направление, прочность, позиция и т.п.).

    Каждое сообщение может содержать произвольное количество полей(до 64)
    При этом обязательны:
    одно числовое поле messageSize - хранит размер сообщения
    одно строковое поле corrId - уникальный идентификатор сообщения
 */

int main() {
    using Field = FieldMessage::Field;

    FieldMessage message;

    std::string_view playerName = "Vladimir";
    std::string_view position = "22;58";
    std::string_view direction = "DOWN!";

    message.SetIntField(Field::TankSpeed, 255);
    message.SetIntField(Field::TankHp, 999);
    message.SetIntField(Field::ObstacleDurability, 3);
    message.SetStringField(Field::PlayerName, playerName.data());
    message.SetStringField(Field::Position, position.data());
    message.SetStringField(Field::Direction, direction.data());

    {
        auto serialized = FieldMessageSerializer::Serialize(message);
        auto deserialized = FieldMessageSerializer::Deserialize(serialized);

        assert(message == deserialized);

        assert(message.GetId() != deserialized.GetId());
    }
    {
        assert(message.GetMessageSize() == FieldMessage::kHEADER_SIZE +
                                           3 * FieldMessage::kINT_FIELD_SIZE +
                                           3 * FieldMessage::kSTRING_HEADER_SIZE +
                                           playerName.length() +
                                           position.length() +
                                           direction.length());
    }
    {
        message.DeleteField(Field::Position);
        assert(message.GetMessageSize() == FieldMessage::kHEADER_SIZE +
                                           3 * FieldMessage::kINT_FIELD_SIZE +
                                           2 * FieldMessage::kSTRING_HEADER_SIZE +
                                           playerName.length() +
                                           direction.length());
    }
    {
        message.DeleteField(Field::TankHp);
        assert(!message.Has(Field::TankHp));
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
