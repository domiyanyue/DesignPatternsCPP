#include <iostream>
#include <string>

class Fly {
  public:
    virtual std::string fly() = 0;
};

class ItFlys : public Fly {
  public:
    std::string fly() { return "Flying High!"; }
};

class CantFly : public Fly {
  public:
    std::string fly() { return "I can't fly!"; }
};

class Animal {
  private:
    std::string name;
    double height;
    int weight;
    std::string favFood;
    double speed;
    std::string sound;

  public:
    Fly *flyingType;

  public:
    void setName(std::string newName) { name = newName; }

    std::string getName() { return name; }

    void setHeight(double newHeight) { height = newHeight; }

    double getHeight() { return height; }

    int setWeight(int newWeight) { weight = newWeight; }

    std::string getSound() { return sound; }

    void setSound(std::string newSound) { sound = newSound; }

    std::string tryToFly() { return flyingType->fly(); }

    void setFlyingAbility(Fly *newFlyType) { flyingType = newFlyType; }
};

class Dog : public Animal {
  public:
    Dog() {
        setSound("Bark");
        flyingType = new CantFly();
    }
};

class Bird : public Animal {
  public:
    Bird() {
        setSound("Tweet");
        flyingType = new ItFlys();
    }
};

int main() {
    Animal *dog = new Dog();
    Animal *bird = new Bird();

    std::cout << "Dog: " << dog->tryToFly() << "\n";
    std::cout << "Bird: " << bird->tryToFly() << "\n";

    dog->setFlyingAbility(new ItFlys());
    std::cout << "Dog: " << dog->tryToFly() << "\n";

    return 0;
}