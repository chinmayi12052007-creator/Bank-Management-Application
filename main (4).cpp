#include "Bank.h"
#include <iostream>
#include <limits>
using namespace std;

void showMenu() {
    cout << "\n  ╔══════════════════════════════════════╗\n";
    cout <<   "  ║      BANK MANAGEMENT APPLICATION     ║\n";
    cout <<   "  ╠══════════════════════════════════════╣\n";
    cout <<   "  ║  1. Create New Account               ║\n";
    cout <<   "  ║  2. Deposit Amount                   ║\n";
    cout <<   "  ║  3. Withdraw Amount                  ║\n";
    cout <<   "  ║  4. Check Balance                    ║\n";
    cout <<   "  ║  5. Display All Accounts             ║\n";
    cout <<   "  ║  6. Search Account                   ║\n";
    cout <<   "  ║  7. Delete Account                   ║\n";
    cout <<   "  ║  8. Exit                             ║\n";
    cout <<   "  ╚══════════════════════════════════════╝\n";
    cout <<   "  Enter your choice: ";
}

int main() {
    Bank bank;   // loads existing data from file
    int choice;

    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Please enter a number between 1 and 8.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit();       break;
            case 3: bank.withdraw();      break;
            case 4: bank.checkBalance();  break;
            case 5: bank.displayAll();    break;
            case 6: bank.searchAccount(); break;
            case 7: bank.deleteAccount(); break;
            case 8:
                cout << "\n  Thank you for using Bank Management System!\n"
                     << "  All records saved. Goodbye!\n\n";
                return 0;
            default:
                cout << "  [!] Invalid choice. Enter 1-8.\n";
        }
    }
}
