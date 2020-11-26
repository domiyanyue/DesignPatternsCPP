#include <cstdlib>
#include <iostream>

// Target: EnemyAttacker
// Adapter
// Adpatee: EnemyRobot

// interface
class EnemyAttacker {
  public:
    virtual void fireWeapon() = 0;
    virtual void driveForward() = 0;
    virtual void assignDriver(std::string driverName) = 0;
};

class EnemyTank : public EnemyAttacker {
  public:
    void fireWeapon() {
        int attackDamage = rand() % 100 + 1;
        std::cout << "Enemy Tank Does: " << attackDamage << " damage \n";
    }

    void driveForward() {
        int movement = rand() % 10 + 1;
        std::cout << "Enemy Tank Moves: " << movement << " m \n";
    }

    void assignDriver(std::string driverName) {
        std::cout << driverName << " is driving the tank\n";
    }
};

class EnemyRobot {
  public:
    EnemyRobot() {}

    void smashWithHands() {
        int attackDamage = rand() % 100 + 1;
        std::cout << "Enemy Robot Does: " << attackDamage
                  << " damage with hands \n";
    }

    void walkForward() {
        int movement = rand() % 5 + 1;
        std::cout << "Enemy Robot Walks: " << movement << " m \n";
    }

    void reactToHuman(std::string driverName) {
        std::cout << "Enemy Robot Tramps on " << driverName << "\n";
    }
};

class EnemyRobotAapter : public EnemyAttacker {
  public:
    EnemyRobot *enemyRobot;

    EnemyRobotAapter(EnemyRobot *er) { enemyRobot = er; }

    void fireWeapon() { enemyRobot->smashWithHands(); }

    void driveForward() { enemyRobot->walkForward(); }

    void assignDriver(std::string driverName) {
        enemyRobot->reactToHuman(driverName);
    }
};

int main() {
    EnemyTank *tank = new EnemyTank();
    EnemyRobot *robot = new EnemyRobot();
    EnemyRobotAapter *robotAdapter = new EnemyRobotAapter(robot);

    // in this example, use EnemyRobotAapter with interface of EnemyAttacker

    std::cout << "The Robot \n";

    robot->reactToHuman("Paul");
    robot->walkForward();
    robot->smashWithHands();

    std::cout << "The Tank \n";

    tank->assignDriver("Frank");
    tank->driveForward();
    tank->fireWeapon();

    std::cout << "The Robot with Adapter \n";

    robotAdapter->assignDriver("Mark");
    robotAdapter->driveForward();
    robotAdapter->fireWeapon();

    return 0;
}