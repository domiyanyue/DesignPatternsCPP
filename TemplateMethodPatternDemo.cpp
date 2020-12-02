#include <iostream>
#include <string>
#include <vector>

class Hoagie {
  public:
    Hoagie() {}
    virtual ~Hoagie() {}
    void makeSandwich() {
        cutBun();
        if (customerWantsMeat()) {
            addMeat();
        }
        if (customerWantsCheese()) {
            addCheese();
        }
        if (customerWantsVegetables()) {
            addVegetables();
        }
        wrapTheHoggie();
    }

    void cutBun() { std::cout << "The Hoagie is cut\n"; }

    void wrapTheHoggie() { std::cout << "The Hoagie is wrapped\n"; }

    virtual void addMeat() = 0;
    bool customerWantsMeat() { return true; }
    virtual void addCheese() = 0;
    bool customerWantsCheese() { return true; }
    virtual void addVegetables() = 0;
    bool customerWantsVegetables() { return true; }
};

class ItalianHoagie : public Hoagie {
  private:
    std::vector<std::string> meatUsed = {"Salami", "Pepperoni", "Capicola Ham"};
    std::vector<std::string> cheeseUsed = {"Provolone"};
    std::vector<std::string> veggieUsed = {"Lettuce", "Tomatoes", "Onions",
                                           "Sweet Peppers"};

  public:
    void addMeat() {
        std::cout << "Adding the meat: ";
        for (auto s : meatUsed) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
    void addCheese() {
        std::cout << "Adding the cheese: ";
        for (auto s : cheeseUsed) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
    void addVegetables() {
        std::cout << "Adding the vegetables: ";
        for (auto s : veggieUsed) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
};

class VeggieHoagie : public Hoagie {
  private:
    std::vector<std::string> veggieUsed = {"Lettuce", "Tomatoes", "Onions",
                                           "Sweet Peppers"};

  public:
    bool customerWantsMeat() { return false; }
    bool customerWantsCheese() { return false; }
    void addMeat() {}
    void addCheese() {}
    void addVegetables() {
        std::cout << "Adding the vegetables: ";
        for (auto s : veggieUsed) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    Hoagie *hoagie1 = new ItalianHoagie();
    hoagie1->makeSandwich();

    std::cout << "\n";

    Hoagie *hoagie2 = new VeggieHoagie();
    hoagie2->makeSandwich();
    return 0;
}