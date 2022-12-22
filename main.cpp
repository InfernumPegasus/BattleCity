/*
 * TODO Создать объектную модель игры BattleCity
 * 3. Используя средства языка описать объектную модель игры BattleCity.
 * (Танк, Снаряд, Штаб, Препятствие: {Лед, Вода, Стена: {Железная, Каменная}}.
 * Реализовать pure abstract классы (интерфейсы, описание методов без реализации а данных).
 * Описания в отдельных *.h файлах с защитой от включения (pragma or #define).
 * По возможности использовать наследование.
 */

#include "entity/tank/PlayerTank.h"
#include "entity/tank/EnemyTank.h"
#include "Point2D.h"
#include "entity/obstacle/Obstacle.h"
#include "entity/Headquarters.h"
#include "entity/obstacle/IceObstacle.h"
#include "entity/obstacle/WaterObstacle.h"
#include "entity/obstacle/WallObstacle.h"
#include "entity/obstacle/ironWallObstacle.h"
#include "entity/obstacle/StoneWallObstacle.h"

int main() {
    Headquarters headquarters;
    Point2D point2D;
//    PlayerTank tank;
    return 0;
}
