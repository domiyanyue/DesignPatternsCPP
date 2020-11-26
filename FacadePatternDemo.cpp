#include <iostream>

class WelcomeToBank {
  public:
    WelcomeToBank() {
        std::cout << "Welcome to ABC bank\n";
        std::cout << "We are happy to serve you\n";
    }
};

class AccountNumberCheck {
  private:
    int accountNumber = 12345678;

  public:
    AccountNumberCheck() {}

    int getAccountNumber() { return accountNumber; }

    bool accountActive(int acctNum) { return acctNum == getAccountNumber(); }
};

class SecurityCodeCheck {
  private:
    int securityCode = 1234;

  public:
    SecurityCodeCheck(){};

    int getSecurityCode() { return securityCode; }

    bool isCodeCorrect(int code) { return code == getSecurityCode(); }
};

class FundsCheck {
  private:
    double cashInAccount = 1000.00;

  public:
    double getCashInAccount() { return cashInAccount; }

    void decraseCashInAccount(double cashWithdrawn) {
        cashInAccount -= cashWithdrawn;
    }

    void increaseCashInAccount(double cashDeposit) {
        cashInAccount += cashDeposit;
    }

    bool withdrawMoney(double cashToWithdraw) {
        if (cashToWithdraw > getCashInAccount()) {
            std::cout << "You don't have enough money, can't withdraw\n";
            return false;
        }

        decraseCashInAccount(cashToWithdraw);
        return true;
    }

    void depositMoney(double cashToDeposit) {
        increaseCashInAccount(cashToDeposit);
    }
};

class BankAccountFacade {
  private:
    int accountNumber;
    int securityCode;

    AccountNumberCheck acctChecker;
    SecurityCodeCheck securityChecker;
    FundsCheck fundChecker;
    WelcomeToBank backWelcome;

  public:
    BankAccountFacade(int acctNumber, int newSecCode) {
        accountNumber = acctNumber;
        securityCode = newSecCode;
    }

    int getAccountNumber() { return accountNumber; }

    int getSecurityCode() { return securityCode; }

    void withdrawCash(double cashToGet) {
        std::cout << "Try withdraw cash: " << cashToGet << "\n";
        if (acctChecker.accountActive(getAccountNumber()) &&
            securityChecker.isCodeCorrect(getSecurityCode()) &&
            fundChecker.withdrawMoney(cashToGet)) {
            std::cout << "Transaction complete\n";
        } else {
            std::cout << "Transaction failed\n";
        }
    }

    void depositCash(double cashToGet) {
        std::cout << "Try deposit cash: " << cashToGet << "\n";
        if (acctChecker.accountActive(getAccountNumber()) &&
            securityChecker.isCodeCorrect(getSecurityCode())) {
            fundChecker.depositMoney(cashToGet);
            std::cout << "Transaction complete\n";
        } else {
            std::cout << "Transaction failed\n";
        }
    }
};

int main() {
    BankAccountFacade accessBank(12345678, 1234);
    accessBank.withdrawCash(50.00);
    accessBank.withdrawCash(900.00);
    accessBank.withdrawCash(100.00);
    accessBank.depositCash(200.00);
    accessBank.withdrawCash(100.00);
    return 0;
}