#include "gtest/gtest.h"
#include "../message/FieldMessageSerializer.h"

using Field = FieldMessage::Field;

TEST(SerializationTests, SerializedSizeTest) {
    FieldMessage message;

    message.SetIntField(Field::TankSpeed, 255);
    message.SetIntField(Field::TankHp, 999);
    message.SetIntField(Field::ObstacleDurability, 3);
    message.SetStringField(Field::PlayerName, "Vladimir");
    message.SetStringField(Field::Position, "22;58");
    message.SetStringField(Field::Direction, "DOWN");

    auto serialized = FieldMessageSerializer::Serialize(message);

    EXPECT_EQ(message.GetMessageSize(), serialized.size());
}

TEST(SerializationTests, DeserializedEqualityTest) {
    FieldMessage message;

    message.SetIntField(Field::TankSpeed, 255);
    message.SetIntField(Field::ObstacleDurability, 3);
    message.SetStringField(Field::Direction, "22;58");

    auto serialized = FieldMessageSerializer::Serialize(message);
    auto deserialized = FieldMessageSerializer::Deserialize(serialized);

    EXPECT_EQ(message.GetMessageSize(), deserialized.GetMessageSize());
    EXPECT_EQ(message, deserialized);
}

TEST(MessageSizeTests, EmptyMessageSizeTest) {
    FieldMessage message;
    EXPECT_EQ(message.GetMessageSize(), FieldMessage::kHEADER_SIZE);
}

TEST(MessageSizeTests, FilledMessageSizeTest) {
    FieldMessage message;

    std::string playerName = "Vladimir";
    std::string position = "22;58";
    std::string direction = "DOWN";

    message.SetIntField(Field::TankSpeed, 255);
    message.SetIntField(Field::TankHp, 999);
    message.SetIntField(Field::ObstacleDurability, 3);
    message.SetStringField(Field::PlayerName, playerName);
    message.SetStringField(Field::Position, position);
    message.SetStringField(Field::Direction, direction);

    EXPECT_EQ(message.GetMessageSize(),
              FieldMessage::kHEADER_SIZE +
              3 * FieldMessage::kINT_FIELD_SIZE +
              3 * FieldMessage::kSTRING_HEADER_SIZE +
              playerName.length() +
              position.length() +
              direction.length());

    message.DeleteField(Field::TankSpeed);
    EXPECT_EQ(message.GetMessageSize(),
              FieldMessage::kHEADER_SIZE +
              2 * FieldMessage::kINT_FIELD_SIZE +
              3 * FieldMessage::kSTRING_HEADER_SIZE +
              playerName.length() +
              position.length() +
              direction.length());
}

TEST(MessageModificationTests, AddInvalidFieldTest) {
    FieldMessage message;
    EXPECT_ANY_THROW(message.SetIntField(static_cast<Field>(0b00000000), 10));
}

TEST(MessageModificationTests, AddInvalidParameterTypeTest) {
    FieldMessage message;
    EXPECT_ANY_THROW(message.SetIntField(Field::PlayerName, 93));
    EXPECT_ANY_THROW(message.SetStringField(Field::TankHp, "30"));
}
