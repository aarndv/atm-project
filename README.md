
# HaBank Buhay ATM System in C++

A robust console-based ATM system developed in C++ that simulates essential banking operations, with all transactions handled in Philippine Pesos (₱). This project was created in compliance with the final project requirements for CCS0015 Data Structures and Algorithm.

**This is created in compliance for CCS0015 Data Structures and Algorithm's final project.**

---

## Features

- **Secure Authentication**: Log in with an encrypted PIN (4-digit, alphanumeric) for secure access to your account.
- **Deposit, Withdraw, and Balance checking**: Core banking functionalities.
- **Transaction logging with reference IDs**: Keeps a detailed history of all account activities.
- **Bill payment and internal transfers**: Facilitates paying bills and sending money to other users.
- **Currency conversion (USD, JPY, SKW, INR)**: Allows users to see their balance in different currencies.
- **Loan calculator with simple interest**: Enables users to calculate potential loan payments.
- **File-based data persistence (`CSV` format)**: All user data and transaction logs are saved and loaded from files.
- **Organized user data**: Each user's data is stored in a dedicated `data/[userID]` folder.

---

## Folder Structure

|- data/ <br>
|-   |- accounts.csv <br>
|-   |- ref.txt <br>
|-   |- uid-counter.txt <br>
|-   |- [userID]/ <br>
|         |- [userID]-data.csv <br>
|         |- [userID]-log.csv <br>
|- bank.cpp <br>
|- bank.h <br>
|- main.cpp <br>
|- utility.h <br>

---

## Contributors

- **Verceles**
- **Enriquez**
- **Coo**
- **Grutas**
- **Sinang**

---

## Build Instructions

Navigate to the installation directory and run the following:

```bash
g++ -std=c++17 -o atm main.cpp bank.cpp utility.cpp # Assuming utility.cpp exists for utility.h functions
./atm
```

Note: utility.h contains function definitions. If these functions are not inline or template functions, you'll need to compile a utility.cpp file that includes utility.h and defines these functions. If they are intended to be header-only, they should be marked inline. For this setup, assuming a utility.cpp for best practice.

Requires a C++17-compatible compiler. Tested on MinGW & Linux g++.

If you're using cmd:
```bash
g++ main.cpp bank.cpp utility.cpp -o atm.exe
atm.exe
```

## Notes

- userID format: ####-####, auto-generated and stored in uid-counter.txt
- Logs are saved in [userID]-log.csv and include transaction type, amount, and recipient info
- PINs are encrypted using a Caesar cipher-like shift

## Sample Test Scenarios
- Create a new account and set a PIN (e.g., 1234).
- Deposit money (e.g., ₱1000) and then withdraw some (e.g., ₱500).
- Pay a hypothetical bill (e.g., "Electricity" for ₱300).
- View your transaction log and explore currency-converted balances (e.g., in USD, JPY, SKW, INR).
- Inspect the generated user data and log files within the data/ directory.- Create an account with PIN 1234