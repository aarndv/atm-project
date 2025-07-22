
# HaBank Buhay ATM System in C++

A robust console-based ATM system developed in C++ that simulates essential banking operations, with all transactions handled in Philippine Pesos (₱).

This project was created in compliance with the final project requirements for CCS0015 Data Structures and Algorithm.
---

## Features

- **Secure Authentication**: Log in with an encrypted 4-digit alphanumeric PIN for secure account access.
- **Core Banking**: Perform deposits, withdrawals, and check your balance.
- **Comprehensive Transaction Logging**: A detailed history of all account activities is maintained with unique reference IDs.
- **Bills & Transfers**: Conveniently pay bills and send money via internal transfers to other users.
- **Currency Conversion**: View your balance converted to USD, JPY, SKW, or INR.
- **Loan Services**: Apply for and manage loans with a built-in simple interest calculator and payment functionality.
- **Data Persistence**: All user data and transaction logs are securely saved and loaded using CSV files.
- **Organized User Data**: Each user's data is neatly stored in a dedicated data/[userID] folder.- **Secure Authentication**: Log in with an encrypted PIN (4-digit, alphanumeric) for secure access to your account.

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

To compile and run the ATM system, navigate to the project's root directory in your terminal and execute the following commands.

```bash
# For Linux/macOS
g++ -std=c++17 -o atm main.cpp bank.cpp

# For Windows (using MinGW)
g++ -std=c++17 -o atm.exe main.cpp bank.cpp
./atm.exe
```

**Note**: This project requires a C++17-compatible compiler (e.g., g++). 

## Notes

- userID format: ####-####, auto-generated and stored in uid-counter.txt
- Logs are saved in [userID]-log.csv and include transaction type, amount, and recipient info
- PINs are encrypted using a Caesar cipher-like shift

## Sample Test Scenarios
- **Account Creation**: Create a new account and set a PIN (e.g., 1234).
- **Basic Transactions**: Deposit funds (e.g., ₱1000) and then make a withdrawal (e.g., ₱500).
- **Bill Payment**: Pay a hypothetical bill (e.g., "Electricity" for ₱300).
- **Fund Transfer**: Transfer money to another user's account.
- **View History**: Check your transaction log and explore currency-converted balances (e.g., in USD, JPY, SKW, INR).
- **Loan Management**: Apply for a loan, observe the terms, and make a payment.
- **Data Inspection**: Verify the generated user data and log files within the data/ directory.