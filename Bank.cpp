#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

// ─────────────────────────────────────────
//  Utility
// ─────────────────────────────────────────
static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void printHeader(const string& title) {
    cout << "\n  ╔══════════════════════════════════════╗\n";
    cout <<   "  ║  " << left << setw(36) << title << "║\n";
    cout <<   "  ╚══════════════════════════════════════╝\n";
}

// ─────────────────────────────────────────
//  Private helpers
// ─────────────────────────────────────────
int Bank::findIndex(int accNo) const {
    for (int i = 0; i < (int)accounts.size(); ++i)
        if (accounts[i].getAccountNumber() == accNo) return i;
    return -1;
}

bool Bank::accNoExists(int accNo) const {
    return findIndex(accNo) != -1;
}

int Bank::generateAccNo() const {
    if (accounts.empty()) return 1001;
    int maxAcc = 0;
    for (const auto& a : accounts)
        maxAcc = max(maxAcc, a.getAccountNumber());
    return maxAcc + 1;
}

void Bank::saveAll() const {
    ofstream out(DATA_FILE, ios::trunc);
    if (!out) { cerr << "  [ERROR] Cannot write to file.\n"; return; }
    for (const auto& a : accounts) a.writeToFile(out);
    out.close();
}

void Bank::loadAll() {
    ifstream in(DATA_FILE);
    if (!in) return;
    Account a;
    while (a.readFromFile(in))
        accounts.push_back(a);
    in.close();
}

// ─────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────
Bank::Bank() { loadAll(); }

// ─────────────────────────────────────────
//  Create Account
// ─────────────────────────────────────────
void Bank::createAccount() {
    printHeader("CREATE NEW ACCOUNT");

    string name, phone, type;
    double initial;

    cout << "  Enter Full Name       : ";
    getline(cin, name);
    if (name.empty()) { cout << "  [!] Name cannot be empty.\n"; return; }

    cout << "  Enter Phone Number    : ";
    getline(cin, phone);

    cout << "  Account Type\n";
    cout << "    1. Savings\n";
    cout << "    2. Current\n";
    cout << "  Choose (1/2)          : ";
    int t;
    while (!(cin >> t) || (t != 1 && t != 2)) {
        cout << "  [!] Enter 1 or 2: ";
        clearInput();
    }
    clearInput();
    type = (t == 1) ? "Savings" : "Current";

    cout << "  Initial Deposit (Rs.) : ";
    while (!(cin >> initial) || initial < 0) {
        cout << "  [!] Invalid amount. Try again: ";
        clearInput();
    }
    clearInput();

    int accNo = generateAccNo();
    Account newAcc(accNo, name, phone, type, initial);
    accounts.push_back(newAcc);
    saveAll();

    cout << "\n  ✓ Account created successfully!\n";
    cout << "  ✦ Your Account Number : " << accNo << "\n";
}

// ─────────────────────────────────────────
//  Deposit
// ─────────────────────────────────────────
void Bank::deposit() {
    printHeader("DEPOSIT AMOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    while (!(cin >> accNo)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(accNo);
    if (idx == -1) { cout << "  [!] Account not found.\n"; return; }

    double amount;
    cout << "  Enter Amount (Rs.)   : ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "  [!] Amount must be > 0. Try again: ";
        clearInput();
    }
    clearInput();

    if (accounts[idx].deposit(amount)) {
        saveAll();
        cout << "\n  ✓ Deposit successful!\n";
        cout << "  New Balance : Rs. "
             << fixed << setprecision(2) << accounts[idx].getBalance() << "\n";
    }
}

// ─────────────────────────────────────────
//  Withdraw
// ─────────────────────────────────────────
void Bank::withdraw() {
    printHeader("WITHDRAW AMOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    while (!(cin >> accNo)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(accNo);
    if (idx == -1) { cout << "  [!] Account not found.\n"; return; }

    cout << "  Current Balance : Rs. "
         << fixed << setprecision(2) << accounts[idx].getBalance() << "\n";

    double amount;
    cout << "  Enter Amount (Rs.)   : ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "  [!] Amount must be > 0. Try again: ";
        clearInput();
    }
    clearInput();

    if (accounts[idx].withdraw(amount)) {
        saveAll();
        cout << "\n  ✓ Withdrawal successful!\n";
        cout << "  Remaining Balance : Rs. "
             << fixed << setprecision(2) << accounts[idx].getBalance() << "\n";
    } else {
        cout << "\n  [!] Insufficient balance.\n";
    }
}

// ─────────────────────────────────────────
//  Check Balance
// ─────────────────────────────────────────
void Bank::checkBalance() {
    printHeader("CHECK BALANCE");

    int accNo;
    cout << "  Enter Account Number : ";
    while (!(cin >> accNo)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(accNo);
    if (idx == -1) { cout << "  [!] Account not found.\n"; return; }

    const Account& a = accounts[idx];
    cout << "\n  Account Holder : " << a.getHolderName() << "\n";
    cout << "  Account Type   : " << a.getAccountType() << "\n";
    cout << "  Balance        : Rs. "
         << fixed << setprecision(2) << a.getBalance() << "\n";
}

// ─────────────────────────────────────────
//  Display All
// ─────────────────────────────────────────
void Bank::displayAll() {
    printHeader("ALL CUSTOMER ACCOUNTS");
    if (accounts.empty()) {
        cout << "  No accounts found.\n"; return;
    }
    cout << "  Total accounts: " << accounts.size() << "\n\n";
    for (const auto& a : accounts) a.display();
}

// ─────────────────────────────────────────
//  Search Account
// ─────────────────────────────────────────
void Bank::searchAccount() {
    printHeader("SEARCH ACCOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    while (!(cin >> accNo)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(accNo);
    if (idx == -1) { cout << "  [!] Account not found.\n"; return; }

    cout << "\n  Account Details:\n";
    accounts[idx].display();
}

// ─────────────────────────────────────────
//  Delete Account
// ─────────────────────────────────────────
void Bank::deleteAccount() {
    printHeader("DELETE ACCOUNT");

    int accNo;
    cout << "  Enter Account Number : ";
    while (!(cin >> accNo)) { clearInput(); cout << "  Invalid. Try again: "; }
    clearInput();

    int idx = findIndex(accNo);
    if (idx == -1) { cout << "  [!] Account not found.\n"; return; }

    cout << "\n  Account to delete:\n";
    accounts[idx].display();
    cout << "  Confirm delete? (y/n): ";
    char ch; cin >> ch; clearInput();

    if (ch == 'y' || ch == 'Y') {
        accounts.erase(accounts.begin() + idx);
        saveAll();
        cout << "\n  ✓ Account deleted successfully!\n";
    } else {
        cout << "  Operation cancelled.\n";
    }
}
