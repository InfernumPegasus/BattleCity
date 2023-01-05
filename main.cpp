#include <iostream>
#include <cassert>
#include "message/FieldMessage.h"

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

    try {
        FieldMessage message1;

        std::string_view playerName = "Vladimir";
        std::string_view position = "22;58";

        message1.SetIntField(Field::TankSpeed, 255);
        message1.SetIntField(Field::TankHp, 999);
//        message1.SetIntField(Field::ObstacleDurability, 3);
        message1.SetStringField(Field::PlayerName, playerName.data());
        message1.SetStringField(Field::Position, position.data());
        message1.Print();

        auto c = message1.Serialize();
        std::cout << c << std::endl;

        assert(message1.GetMessageSize() == FieldMessage::kHEADER_SIZE +
                                            2*FieldMessage::kINT_FIELD_SIZE +
                                            2*FieldMessage::kSTRING_HEADER_SIZE +
                                            playerName.length() +
                                            position.length());


        message1.DeleteField(Field::Position);
        assert(message1.GetMessageSize() == FieldMessage::kHEADER_SIZE +
                                            2*FieldMessage::kINT_FIELD_SIZE +
                                            1*FieldMessage::kSTRING_HEADER_SIZE +
                                            playerName.length());

        message1.DeleteField(Field::TankHp);
        auto d = message1.GetIntField(Field::TankHp);
        std::cout << d << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    FieldMessage message2;
    std::cout << "Id: " << message2.GetId() << " MessageIdNumber: " << message2.GetMessageIdNumber() << std::endl;

    FieldMessage message3;
    std::cout << "Id: " << message3.GetId() << " MessageIdNumber: " << message3.GetMessageIdNumber() << std::endl;

    return 0;
}
