# Bank Management Application

A console-based **Bank Management Application** built in **C++** using **Object-Oriented Programming** concepts and **file handling** to simulate core banking operations with persistent customer data storage.

---

## Features

| Feature | Description |
|---|---|
| 🏦 Create Account | Open a new Savings or Current account with auto-generated account number |
| 💰 Deposit | Add funds to any existing account |
| 💸 Withdraw | Withdraw funds with balance validation |
| 📊 Check Balance | View current balance for any account |
| 📋 Display All | List all customer accounts with full details |
| 🔍 Search Account | Find an account by account number |
| 🗑️ Delete Account | Remove an account with confirmation |
| 💾 Persistent Storage | All data saved to `bank_data.dat` using file I/O |

---

## Project Structure

```
bank_management/
├── main.cpp        # Entry point — menu loop
├── Account.h       # Account class declaration
├── Account.cpp     # Account class implementation
├── Bank.h          # Bank class declaration
├── Bank.cpp        # Bank class implementation (all operations)
├── Makefile        # Build automation
├── bank_data.dat   # Auto-generated data file (on first run)
└── README.md       # Project documentation
```

---

## OOP Concepts Used

| Concept | Where Applied |
|---|---|
| **Class & Object** | `Account` and `Bank` classes |
| **Encapsulation** | Private data members with public getter methods |
| **Data Hiding** | Balance and account details protected via private access |
| **Abstraction** | `Bank` class exposes clean menu operations, hiding file I/O |
| **File Handling** | `fstream` for persistent read/write of account records |

---

## How to Compile & Run

### Using Makefile (Linux / macOS)
```bash
make          # Compile all source files
make run      # Compile and run
make clean    # Remove binaries and data file
```

### Using g++ directly
```bash
g++ -std=c++17 -Wall -o bank_management main.cpp Account.cpp Bank.cpp
./bank_management
```

### On Windows (MinGW / MSYS2)
```bash
g++ -std=c++17 -Wall -o bank_management.exe main.cpp Account.cpp Bank.cpp
bank_management.exe
```

---

## Usage

On launch, the main menu appears:

```
  ╔══════════════════════════════════════╗
  ║      BANK MANAGEMENT APPLICATION     ║
  ╠══════════════════════════════════════╣
  ║  1. Create New Account               ║
  ║  2. Deposit Amount                   ║
  ║  3. Withdraw Amount                  ║
  ║  4. Check Balance                    ║
  ║  5. Display All Accounts             ║
  ║  6. Search Account                   ║
  ║  7. Delete Account                   ║
  ║  8. Exit                             ║
  ╚══════════════════════════════════════╝
```

- Account numbers are **auto-generated** starting from 1001.
- All changes are **saved immediately** to `bank_data.dat`.
- Data **persists** between sessions.

---

## Account Record Fields

| Field | Type | Description |
|---|---|---|
| Account Number | int | Auto-generated unique ID (starts at 1001) |
| Holder Name | string | Full name of the customer |
| Phone | string | Contact number |
| Account Type | string | "Savings" or "Current" |
| Balance | double | Current balance in Rs. |

---

## File Handling

Records are stored in `bank_data.dat` (plain text, one record per 5 lines):

```
1001
Jane Doe
9876543210
Savings
15000.00
```

The file is read at startup and updated after every create, deposit, withdraw, or delete operation.

---

## Technologies Used

- **Language**: C++ (C++17)
- **OOP Concepts**: Classes, Encapsulation, Abstraction, Data Hiding
- **File I/O**: `ifstream` / `ofstream` for persistent storage
- **STL**: `vector`, `string`, `algorithm`

---

## Author

> Submitted as part of the C++ OOP-based application project.
