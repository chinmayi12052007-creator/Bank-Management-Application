#include "Account.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────
//  Constructors
// ─────────────────────────────────────────
Account::Account()
    : accountNumber(0), holderName(""), phone(""),
      accountType("Savings"), balance(0.0) {}

Account::Account(int accNo, const string& name, const string& ph,
                 const string& type, double initialDeposit)
    : accountNumber(accNo), holderName(name), phone(ph),
      accountType(type), balance(initialDeposit) {}

// ─────────────────────────────────────────
//  Getters
// ─────────────────────────────────────────
int    Account::getAccountNumber() const { return accountNumber; }
string Account::getHolderName()    const { return holderName;    }
string Account::getPhone()         const { return phone;         }
string Account::getAccountType()   const { return accountType;   }
double Account::getBalance()       const { return balance;       }

// ─────────────────────────────────────────
//  Banking operations
// ─────────────────────────────────────────
bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0)       return false;
    if (amount > balance)  return false;
    balance -= amount;
    return true;
}

// ─────────────────────────────────────────
//  Display
// ─────────────────────────────────────────
void Account::display() const {
    cout << "  ┌─────────────────────────────────────────\n";
    cout << "  │  Account No : " << accountNumber << "\n";
    cout << "  │  Name       : " << holderName    << "\n";
    cout << "  │  Phone      : " << phone         << "\n";
    cout << "  │  Type       : " << accountType   << "\n";
    cout << "  │  Balance    : Rs. "
         << fixed << setprecision(2) << balance   << "\n";
    cout << "  └─────────────────────────────────────────\n";
}

// ─────────────────────────────────────────
//  File serialization
// ─────────────────────────────────────────
void Account::writeToFile(ofstream& out) const {
    out << accountNumber << "\n"
        << holderName    << "\n"
        << phone         << "\n"
        << accountType   << "\n"
        << balance       << "\n";
}

bool Account::readFromFile(ifstream& in) {
    if (!(in >> accountNumber)) return false;
    in.ignore();
    getline(in, holderName);
    getline(in, phone);
    getline(in, accountType);
    in >> balance;
    in.ignore();
    return true;
}
