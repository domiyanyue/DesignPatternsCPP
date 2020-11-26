#include <iostream>

class ATMState {
  public:
    virtual void insertCard() = 0;
    virtual void ejectCard() = 0;
    virtual void insertPin(int pin) = 0;
    virtual void requestCash(int cashToWithdraw) = 0;
};

class GetATMData {
  public:
    virtual ATMState *getATMData() = 0;
    virtual int getCashInMachine() = 0;
};

class ATMMachine : public GetATMData {
  public:
    ATMState *hasCard;
    ATMState *noCard;
    ATMState *hasCorrectPin;
    ATMState *atomOutOfMoney;

    ATMState *atmState;

    int cashInMachine = 2000;
    bool correctPinEntered = false;

    ATMMachine();

    void setATMState(ATMState *newATMState) { atmState = newATMState; }

    void setCashInMachine(int newCashInMachine) {
        cashInMachine = newCashInMachine;
    }

    void insertCard() { atmState->insertCard(); }

    void ejectCard() { atmState->ejectCard(); }

    void requestCash(int cashToWithdraw) {
        atmState->requestCash(cashToWithdraw);
    }

    void insertPin(int pin) { atmState->insertPin(pin); }

    ATMState *getYesCardState() { return hasCard; }
    ATMState *getNoCardState() { return noCard; }
    ATMState *getHasPin() { return hasCorrectPin; }
    ATMState *getNoCashState() { return atomOutOfMoney; }

    ATMState *getATMData() { return atmState; }

    int getCashInMachine() { return cashInMachine; }
};

class ATMProxy : public GetATMData {
  public:
    ATMState *getATMData() {
        ATMMachine *realMachine = new ATMMachine();
        return realMachine->getATMData();
    }

    int getCashInMachine() {
        ATMMachine *realMachine = new ATMMachine();
        return realMachine->getCashInMachine();
    }
};

class HasCard : public ATMState {
  private:
    ATMMachine &atmMachine;

  public:
    HasCard(ATMMachine &newATMMachine) : atmMachine{newATMMachine} {}

    void insertCard() { std::cout << "You can't enter more than one card\n"; }

    void ejectCard() {
        std::cout << "Card ejected \n";
        atmMachine.setATMState(atmMachine.getNoCardState());
    }

    void insertPin(int pin) {
        if (pin == 1234) {
            std::cout << "Correct PIN \n";
            atmMachine.correctPinEntered = true;
            atmMachine.setATMState(atmMachine.getHasPin());
        } else {
            std::cout << "Wrong PIN \n";
            atmMachine.setATMState(atmMachine.getNoCardState());
            std::cout << "Card Ejected \n";
        }
    }

    void requestCash(int cashToWithdraw) { std::cout << "Enter PIN first \n"; }
};

class NoCard : public ATMState {
  private:
    ATMMachine &atmMachine;

  public:
    NoCard(ATMMachine &newATMMachine) : atmMachine{newATMMachine} {}

    void insertCard() {
        std::cout << "Please Enter a PIN\n";
        atmMachine.setATMState(atmMachine.getYesCardState());
    }

    void ejectCard() { std::cout << "Enter a card first \n"; }

    void insertPin(int pin) { std::cout << "Enter a card first \n"; }

    void requestCash(int cashToWithdraw) {
        std::cout << "Enter a card first \n";
    }
};

class HasPin : public ATMState {
  private:
    ATMMachine &atmMachine;

  public:
    HasPin(ATMMachine &newATMMachine) : atmMachine{newATMMachine} {}

    void insertCard() { std::cout << "You can't enter more than one card\n"; }

    void ejectCard() {
        std::cout << "Card ejected \n";
        atmMachine.setATMState(atmMachine.getNoCardState());
    }

    void insertPin(int pin) { std::cout << "Already entered PIN \n"; }

    void requestCash(int cashToWithdraw) {
        if (cashToWithdraw <= atmMachine.cashInMachine) {
            atmMachine.setCashInMachine(atmMachine.cashInMachine -
                                        cashToWithdraw);
            std::cout << cashToWithdraw << " is provided by the machine \n";
            std::cout << " Card ejected \n";
            atmMachine.setATMState(atmMachine.getNoCardState());
            if (atmMachine.cashInMachine == 0) {
                atmMachine.setATMState(atmMachine.getNoCashState());
            }

        } else {
            std::cout << "Not enough Cash \n";
        }
    }
};

class NoCash : public ATMState {
  private:
    ATMMachine &atmMachine;

  public:
    NoCash(ATMMachine &newATMMachine) : atmMachine{newATMMachine} {}

    void insertCard() { std::cout << "We don't have money\n"; }

    void ejectCard() { std::cout << "We don't have money\n"; }

    void insertPin(int pin) { std::cout << "We don't have money\n"; }

    void requestCash(int cashToWithdraw) {
        std::cout << "We don't have money\n";
    }
};

ATMMachine::ATMMachine() {
    hasCard = new HasCard(*this);
    noCard = new NoCard(*this);
    hasCorrectPin = new HasPin(*this);
    atomOutOfMoney = new NoCash(*this);

    atmState = noCard;
}

int main() {
    ATMMachine atmMachine;
    atmMachine.insertCard();
    atmMachine.ejectCard();
    atmMachine.insertCard();
    atmMachine.insertPin(1235);
    atmMachine.insertCard();
    atmMachine.insertPin(1234);
    atmMachine.requestCash(100);

    atmMachine.insertCard();
    atmMachine.insertPin(1234);
    atmMachine.requestCash(1900);

    atmMachine.insertCard();
    atmMachine.insertPin(1235);

    GetATMData *realATMMachine = new ATMMachine();
    GetATMData *atmProxy = new ATMProxy();

    std::cout << "Current ATM State : " << atmProxy->getATMData() << "\n";
    std::cout << "Current ATM Machine $  : " << atmProxy->getCashInMachine()
              << "\n";

    // Error: Proxy didn't have the interface
    // std::cout << "Current ATM Machine $  : " <<
    // realATMMachine->setCashInMachine(1.0) << "\n";

    return 0;
}