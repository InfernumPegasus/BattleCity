#ifndef BATTLECITY_FIELDMESSAGEFIXTURE_CPP
#define BATTLECITY_FIELDMESSAGEFIXTURE_CPP

#include "gtest/gtest.h"
#include "../message/FieldMessageSerializer.h"

using Field = FieldMessage::Field;

class FieldMessageFixture : public ::testing::Test {
public:
    ~FieldMessageFixture() override {
        delete message;
    }

protected:
    FieldMessage *message {};

    void SetUp() override {
        message = new FieldMessage();
    }
};


TEST_F(FieldMessageFixture, SerializedSize) {
    message->SetIntField(Field::TankSpeed, 255);
    message->SetIntField(Field::TankHp, 999);
    message->SetIntField(Field::ObstacleDurability, 3);
    message->SetStringField(Field::PlayerName, "Vladimir");
    message->SetStringField(Field::Position, "22;58");
    message->SetStringField(Field::Direction, "DOWN");

    auto serialized = FieldMessageSerializer::Serialize(*message);

    EXPECT_EQ(message->GetMessageSize(), serialized.size());
}

TEST_F(FieldMessageFixture, DeserializedEquality) {
    message->SetIntField(Field::TankSpeed, 255);
    message->SetIntField(Field::ObstacleDurability, 3);
    message->SetStringField(Field::Direction, "22;58");

    auto serialized = FieldMessageSerializer::Serialize(*message);
    auto deserialized = FieldMessageSerializer::Deserialize(serialized);

    EXPECT_EQ(message->GetMessageSize(), deserialized.GetMessageSize());
    EXPECT_EQ(*message, deserialized);
}

TEST_F(FieldMessageFixture, EmptyMessageSize) {
    EXPECT_EQ(message->GetMessageSize(), FieldMessage::kHEADER_SIZE);
    EXPECT_EQ(message->GetBitmask(), 0);
}

TEST_F(FieldMessageFixture, FilledMessageSize) {
    std::string playerName = "Vladimir";
    std::string position = "22;58";
    std::string direction = "DOWN";

    message->SetIntField(Field::TankSpeed, 255);
    message->SetIntField(Field::TankHp, 999);
    message->SetIntField(Field::ObstacleDurability, 3);
    message->SetStringField(Field::PlayerName, playerName);
    message->SetStringField(Field::Position, position);
    message->SetStringField(Field::Direction, direction);

    EXPECT_EQ(message->GetMessageSize(),
              FieldMessage::kHEADER_SIZE +
              3 * FieldMessage::kINT_FIELD_SIZE +
              3 * FieldMessage::kSTRING_HEADER_SIZE +
              playerName.length() +
              position.length() +
              direction.length());

    message->DeleteField(Field::TankSpeed);
    EXPECT_EQ(message->GetMessageSize(),
              FieldMessage::kHEADER_SIZE +
              2 * FieldMessage::kINT_FIELD_SIZE +
              3 * FieldMessage::kSTRING_HEADER_SIZE +
              playerName.length() +
              position.length() +
              direction.length());
}

TEST_F(FieldMessageFixture, AddInvalidField) {
    EXPECT_ANY_THROW(message->SetIntField(static_cast<Field>(0b0000'0000'0000), 10));
    EXPECT_ANY_THROW(message->SetIntField(static_cast<Field>(0b1000'0000'0000), 10));
    EXPECT_ANY_THROW(message->SetIntField(static_cast<Field>(0b0000'0000'1100), 10));
    EXPECT_ANY_THROW(message->SetIntField(static_cast<Field>(0b1000'0010'0011), 10));
}

TEST_F(FieldMessageFixture, AddInvalidParameterType) {
    EXPECT_ANY_THROW(message->SetIntField(Field::PlayerName, 93));
    EXPECT_ANY_THROW(message->SetStringField(Field::TankHp, "30"));
}

TEST_F(FieldMessageFixture, UniqueIds) {
    FieldMessage other;
    EXPECT_NE(message->GetId(), other.GetId());
}


#endif //BATTLECITY_FIELDMESSAGEFIXTURE_CPP
