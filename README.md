
# ATM System in C++

A console-based ATM system built in C++ that simulates basic banking operations. The system supports account creation, PIN-encrypted login, deposits, withdrawals, bill payments, loan calculations, and transaction logging — all organized in a modular and team-friendly structure.

---

## Features

- Encrypted PIN-based login system
- Deposit, Withdraw, and Balance checking
- Transaction logging with reference IDs
- Bill payment and internal transfers
- Currency conversion (USD, JPY, EUR)
- Loan calculator with simple interest
- File-based data persistence (`CSV` format)
- Organized user data in `data/[userID]` folders

---

## Folder Structure

├── data/
│ ├── accounts.csv
│ ├── ref.txt
│ ├── uid-counter.txt
│ └── [userID]/
│ ├── [userID]-data.csv
│ └── [userID]-log.csv
├── bank.cpp
├── bank.h
├── main.cpp
├── utility.cpp
└── utility.h

---

## Contributors and Responsibilities

- **Enriquez & Coo**: Deposit, Withdraw, Pay Bills, Check Balance
- **Verceles**: PIN encryption, Login system, File I/O, Project leader, integration, ID system, and file structure
- **Grutas**: Transaction logs, Currency conversion
- **Sinang**: Loan system (UI and interest calculation)

---

## Build Instructions

```bash
g++ -std=c++17 -o atm main.cpp bank.cpp utility.cpp
./atm
```
Requires a C++17-compatible compiler. Tested on MinGW & Linux g++.

## Notes

- userID format: ####-####, auto-generated and stored in uid-counter.txt
- Logs are saved in [userID]-log.csv and include transaction type, amount, and recipient info
- PINs are encrypted using a Caesar cipher-like shift

## Sample Test Scenarios

- Create an account with PIN 1234
- Deposit 1000, withdraw 500
- Pay a bill named Electricity worth 300a
- View transaction log and currency-converted balances
- Check file contents inside data/ directory
