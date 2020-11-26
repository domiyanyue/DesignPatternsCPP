// In class-based programming, the factory method pattern
// is a creational pattern that uses factory methods to deal
// with the problem of creating objects without having to
// specify the exact class of the object that will be created.
// This is done by creating objects by calling a factory method.

#include <iostream>
#include <string>

class EnemyShip {
  private:
    std::string name;
    double amtDamage;

  public:
    EnemyShip() {}

    std::string getName() { return name; }

    void setName(const std::string &str) { name = str; }

    double getDamage() { return amtDamage; }
    void setDamage(double d) { amtDamage = d; }

    void followHeroShip() {
        std::cout << getName() << " is following the hero \n";
    }

    void displayEnemyShip() {
        std::cout << getName() << " is displayed on screen \n";
    }

    void enemyShipShoots() {
        std::cout << getName() << " attack " << getDamage() << "\n";
    }
};

class UFOEnemyShip : public EnemyShip {
  public:
    UFOEnemyShip() {
        setName("UFO Enemy Ship");
        setDamage(20.0);
    }
};

class RocketEnemyShip : public EnemyShip {
  public:
    RocketEnemyShip() {
        setName("Rocket Enemy Ship");
        setDamage(10.0);
    }
};

class BigUFOEnemyShip : public UFOEnemyShip {
  public:
    BigUFOEnemyShip() {
        setName("Big UFO Enemy Ship");
        setDamage(40.0);
    }
};

class EnemyShipFactory {
  public:
    EnemyShipFactory() {}
    static EnemyShip *makeEnemyShip(std::string shipType) {
        EnemyShip *newShip = nullptr;
        if (shipType == "U") {
            newShip = new UFOEnemyShip();
        } else if (shipType == "R") {
            newShip = new RocketEnemyShip();
        } else if (shipType == "B") {
            newShip = new BigUFOEnemyShip();
        }
        return newShip;
    }
};

void doStuffEnemy(EnemyShip *ship) {
    ship->displayEnemyShip();
    ship->followHeroShip();
    ship->enemyShipShoots();
}

int main() {
    // without factory pattern
    // need to use "new" and call constructor explicitly
    EnemyShip *ufoship = new UFOEnemyShip();
    doStuffEnemy(ufoship);

    // use factory pattern
    EnemyShip *shi1 = EnemyShipFactory::makeEnemyShip("U");
    doStuffEnemy(shi1);

    EnemyShip *shi2 = EnemyShipFactory::makeEnemyShip("R");
    doStuffEnemy(shi2);

    EnemyShip *shi3 = EnemyShipFactory::makeEnemyShip("B");
    doStuffEnemy(shi3);

    return 0;
}