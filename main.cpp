#include <iostream>
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

        message1.SetIntField(Field::TankSpeed, 10);
//        message1.SetIntField(Field::TankHp, 1);
        message1.SetIntField(Field::ObstacleDurability, 3);
//        message1.SetStringField(Field::Direction, " UP ");
        message1.SetStringField(Field::PlayerName, " Vladimir ");
        message1.SetStringField(Field::Position, " sad ");
        message1.Print();

        std::cout << "Msg size | Bit mask | Type | Length(string only) | Value |" << std::endl;
        auto c = message1.Serialize();
        std::cout << c << std::endl;

        auto d = FieldMessage::Deserialize(c);
        d.Print();

//        message1.DeleteField(Field::TankHp);
//        auto d = message1.GetIntField(Field::TankHp);
//        std::cout << d << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

//    FieldMessage message2;
//    std::cout << "Id: " << message2.GetId() << " MessageIdNumber: " << message2.GetMessageIdNumber() << std::endl;
//
//    FieldMessage message3;
//    std::cout << "Id: " << message3.GetId() << " MessageIdNumber: " << message3.GetMessageIdNumber() << std::endl;

    return 0;
}
