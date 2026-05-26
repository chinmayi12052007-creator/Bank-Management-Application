#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    int    accountNumber;
    string holderName;
    string phone;
    string accountType;   // "Savings" or "Current"
    double balance;

public:
    // Constructors
    Account();
    Account(int accNo, const string& name, const string& phone,
            const string& type, double initialDeposit);

    // Getters
    int    getAccountNumber() const;
    string getHolderName()    const;
    string getPhone()         const;
    string getAccountType()   const;
    double getBalance()       const;

    // Banking operations
    bool deposit(double amount);
    bool withdraw(double amount);

    // Display
    void display() const;

    // File serialization helpers
    void   writeToFile(ofstream& out)  const;
    bool   readFromFile(ifstream& in);
};

#endif // ACCOUNT_H
