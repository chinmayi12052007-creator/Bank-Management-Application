#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <vector>
#include <string>
using namespace std;

class Bank {
private:
    vector<Account> accounts;
    const string    DATA_FILE = "bank_data.dat";

    // Internal helpers
    int  findIndex(int accNo) const;
    bool accNoExists(int accNo) const;
    int  generateAccNo() const;

    void saveAll() const;
    void loadAll();

public:
    Bank();   // loads data on construction

    // Menu operations
    void createAccount();
    void deposit();
    void withdraw();
    void checkBalance();
    void displayAll();
    void searchAccount();
    void deleteAccount();
};

#endif // BANK_H
