#include "bank.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#define MAX_DEPOSIT 200000
#define MAX_WITHDRAW 50000
#define MIN_DEPOSIT 100
#define MIN_WTIHDRAW 100
#define BAR "========================="
#define BANK_NAME "HaBank Buhay"

// Constructors 

ATMUser::ATMUser() {
    this->username = "";
    this->userID = "";
    this->PIN = "";
    this->bal = 0;
}

ATMUser::ATMUser(std::string id, std::string username, std::string pin, double initialBal) {
    this->userID = id;
    this->username = username;
    this->bal = initialBal;
    setPIN(pin); // This will encrypt and set the PIN
}

Log::Log() {
    this->type = "";
    this->amount = 0;
    this->message = "";
    this->refNumber = "";
    this->recipientID = "";
}

Log::Log(std::string type, double amount, std::string message, std::string ref, std::string recipient) {
    this->type = type;
    this->amount = amount;
    this->message = message;
    this->refNumber = ref;
    this->recipientID = recipient;
}

Users::Users() {
    this->refCounter = 1;
}

Menu::Menu() {}

// PIN ENCRYPTION HELPERS

std::string ATMUser::encryptPin(const std::string &plainPin) const {
    std::string encrypted = plainPin;
    for (char &c : encrypted)   
        c += pinShift;
    return encrypted;
}

std::string ATMUser::decryptPin(const std::string &cipheredPin) const {
    std::string decrypted = cipheredPin;
    for (char &c : decrypted)
        c -= pinShift;
    return decrypted;
}

// Getter
std::string ATMUser::getID() const { return userID; }
std::string ATMUser::getUsername() const { return username; }
std::string ATMUser::getPIN() const { return decryptPin(PIN); }
double ATMUser::getBalance() const { return bal; }
std::vector<Log> ATMUser::getLogs() const { return logs; }

std::string Log::getType() const { return type; }
double Log::getAmount() const { return amount; }
std::string Log::getMessage() const { return message; }
std::string Log::getRefNumber() const { return refNumber; }
std::string Log::getRecipientID() const { return recipientID; }
std::string ATMUser::getEncryptedPIN() const { return PIN; }

// Setter
void ATMUser::setID(const std::string &id) { userID = id; }
void ATMUser::setUsername(const std::string &uname) { username = uname; }
void ATMUser::setPIN(const std::string &plainPin) { PIN = encryptPin(plainPin); }
void ATMUser::setEncryptedPIN(const std::string &cipheredPin) { PIN = cipheredPin; }
void ATMUser::setBalance(double balance) { bal = balance; }
void ATMUser::setLogs(const std::vector<Log> &logList) { logs = logList; }

void Log::setType(const std::string &t) { type = t; }
void Log::setAmount(double amt) { amount = amt; }
void Log::setMessage(const std::string &msg) { message = msg; }
void Log::setRefNumber(const std::string &ref) { refNumber = ref; }
void Log::setRecipientID(const std::string &rid) { recipientID = rid; }

// ==================== @Enriquez & @Coo ======================
// Handles: Withdraw, Deposit, Pay Bills, and Display of Balance

// deposit()
// Example call: user.deposit();
void ATMUser::deposit() {
    double amount;
    // TODO:
    
    // Prompts the user for an amount
    // Check if amount is within MIN/MAX deposit bounds
    // Show an error if not valid and then return
    // If valid, get current balance "double bal = getBalance();"
    // ADD amount to current balance
    // Use the method setBalance() to set it back. e.g., setBalance(bal)
    // Display confirmation
    
    addLog("deposit", amount);
}

// withdraw()
// Example call: user.withdraw();
void ATMUser::withdraw() {
    double amount;
    // TODO:

    // Show the balance by calling the show balance method
    // Prompts the user how much they want to withdraw
    // Check if amount is within MIN/MAX deposit limits
    // Show an error if not valid and then return
    // If valid, get current balance using getBalance();
    // Subtract amount to current balance
    // Use the method setBalance() to set it back. e.g., setBalance(bal)
    // Display confirmation
    
    addLog("withdraw", amount);
}

// payBills()
// Description: Prompts for bill type and amount, deducts if valid
void ATMUser::payBills() {
    // TODO:
    std::string billName;
    double amount;


    // Ask for bill name and amount
    // Check if the user has sufficient balance
    // If not, print error and return
    // Deduct the amount and update balance
    // Display confirmation

    addLog(billName, amount);
}

// displayBalance()
// Description: Prints current balance to terminal
// Example Output: "Your current balance is: $12500.50"
void ATMUser::displayBalance() {
    // Fetch current Balance
    // Output formatted balance (e.g. $1234.50)
}

// transferMoney()
// Description: Transfer an amount to a recipientID (that exists)
// recipientID: an std::string in the form of ####-#### 
// amount: amount to be transferred
void ATMUser::transferMoney(std::string recipientID, std::string message, double amount) {
    return;
}

// ====================== @Verceles ======================
// Handles: User Login, FILE I/O, Saving/Loading, and Internal Transfers

bool ATMUser::validatePin(const std::string &inputPin) {
    return decryptPin(PIN) == inputPin;
}

void ATMUser::save() {
    std::string folder = "data/" + userID;
    std::string path = folder + "/" + userID + "-data.csv";

    if (!std::filesystem::exists(folder)) {
        std::filesystem::create_directories(folder);
    }

    std::ofstream fout(path);
    if (fout.is_open()) {
        fout << userID << ","
                << username << ","
                << getEncryptedPIN() << ","
                << bal << "\n";
        fout.close();
    } else {
        std::cerr << "[ERROR] Failed to save user data for " << userID;
    }
    return;   
}

void ATMUser::load() {
    std::string path = "data/" + userID + "/" + userID + "-data.csv";

    std::ifstream fin(path);
    if (fin.is_open()) {
        std::string line;
        getline(fin, line);
        std::stringstream ss(line);
        std::string encPin, balStr;

        getline(ss, userID, ',');
        getline(ss, username, ',');
        getline(ss, encPin, ',');
        getline(ss, balStr, ',');

        setEncryptedPIN(encPin);
        bal = std::stod(balStr);

        fin.close();
    } else {
        std::cerr << "[ERROR] Could not load data for " << userID << "\n";
    }
    return;
}

void ATMUser::saveLogs() {
    std::string folder = "data/" + userID;
    std::string path = folder + "/" + userID + "-log.csv";

    if (std::filesystem::exists(folder)) {
        std::filesystem::create_directories(folder);
    }

    std::ofstream fout(path);
    if (fout.is_open()) {
        for (const Log &log : logs) {
            fout << log.getType() << ","
                << log.getAmount() << ","
                << log.getMessage() << ","
                << log.getRefNumber() << ","
                << log.getRecipientID() << "\n";
        }
        fout.close();
    } else {
        std::cerr << "[ERROR] Could not save logs for " << userID << "\n";
    }
}

void ATMUser::loadLogs() {
    logs.clear();

    std::string path = "data/" + userID + "/" + userID + "-log.csv";
    std::ifstream fin(path);
    if (fin.is_open()) {
        std::string line;
        while (getline(fin, line)) {
            std::stringstream ss(line);
            std::string type, amountStr, message, ref, recipient;
            getline(ss, type, ',');
            getline(ss, amountStr, ',');
            getline(ss, message, ',');
            getline(ss, ref, ',');
            getline(ss, recipient, ',');

            double amount = std::stod(amountStr);

            Log log(type, amount, message, ref, recipient);
            logs.push_back(log);
        }
        fin.close();
    } else {
        std::cerr << "[INFO] No log file found for " << userID << ". Skipping load.\n";
    }
}

ATMUser *Users::loginPrompt() {
    std::string userID, enteredPIN;
    bool idFound = false, PINCorrect = false;
    ATMUser *user;
    int tries = 0;

    do {
        std::cout << "Enter userID (####): ";
        std::cin >> userID;

        user = findUserByID(userID);
        if (!user)
            std::cout << "userID does not exist.\n";
        else 
            idFound = true;
    } while (!idFound);

    do {
        std::cout << "Enter PIN (####): ";
        std::cin >> enteredPIN;
    
        if (user && user->validatePin(enteredPIN)) {
            std::cout << "Login successful.\n";
            PINCorrect = true;
        } else {
            std::cout << "Invalid PIN.\n";
        }
    } while (!PINCorrect);

    return user;
}

std::string Users::getNextUserID() {
    int lastSerial = 0;
    std::ifstream fin("data/uid-counter.txt");

    if (fin.is_open()) {
        fin >> lastSerial;
        fin.close();
    }

    int newSerial = lastSerial + 1;

    std::ofstream fout("data/uid-counter.txt");
    if (fout.is_open()) {
        fout << newSerial;
        fout.close();
    }

    int batchPrefix = 1;
    return formatID(batchPrefix, newSerial);
}

ATMUser *Users::findUserByID(const std::string &id) {
    for (ATMUser &user : userList) {
        if (user.getID() == id) 
            return &user;
    }
    return NULL;
}

bool Users::addAccount() {
    std::string name, pin;
    std::cout << "Enter desired username: ";
    std::getline(std::cin>>std::ws, name);

    for (ATMUser &user : userList) {
        if (user.getUsername() == name)
            return false;
    }

    std::cout << "Enter PIN (####): ";
    std::cin >> pin;

    std::string newID = getNextUserID();

    std::cout << "Your userID is " << newID << "\n";

    ATMUser newUser(newID, name, pin);
    userList.push_back(newUser);

    newUser.save();
    newUser.saveLogs();

    addToAccountList(newID);

    return true;
}

void Users::saveAccounts() {
    for (ATMUser &user : userList) {
        user.save();
        user.saveLogs();
    }

    std::ofstream fout("data/ref.txt");
    if (fout.is_open()) {
        fout << refCounter << "\n";
        fout.close(); 
    } else {
        std::cerr << "[ERROR] Could not save reference number.\n";
    }
}

void Users::loadAccounts() {
    userList.clear();

    std::ifstream fin("data/accounts.csv");
    if (!fin.is_open()) {
        std::cerr << "[ERROR] Cannot open accounts list\n";
        return;
    }

    std::string id;
    while (getline(fin, id)) {
        ATMUser user;
        user.setID(id);
        user.load();
        user.loadLogs();
        userList.emplace_back(user);
    }
    fin.close();

    std::ifstream refIn("data/ref.txt");
    if (refIn.is_open()) {
        refIn >> refCounter;
        refIn.close();
    } else {
        refCounter = 1;
    }
}

void Users::addToAccountList(const std::string &id) {
    std::ofstream fout("data/accounts.csv", std::ios::app);
    if (fout.is_open()) {
        fout << id << "\n";
        fout.close();
    }
}

// ====================== @Grutas ====================== 
// Handles: Transaction Logs and Currency Conversion

// viewLogs()
// Description: Displays list of previous logs (withdrawals, deposits, etc)
void ATMUser::viewLogs() {
     return;
}

// addLog(type, amount, message (optional), ref (optional))
// type: string label ("Withdraw", "Deposit")
// amount: the amount involved
// message: optional message for context
// ref: transaction reference ID (don't mind)
void ATMUser::addLog(std::string type, double amount, std::string message, std::string ref) {
    
    return;
}

// convertBalanceToOtherCurrency(currency)
// currency: a string representing a currency code (e.g., "USD", "JPY", "PHP")
// Output: prints equivalent amount in that currency
void ATMUser::convertBalanceToOtherCurrency(std::string currency) {
    return;
}

// ==================== @Sinang ====================
// Handles: Loan System (calculation and interface)

// LoanCash()
// Description: Prompts user for principal, rate, duration, Calculates payable amount.
// Output:: Print payable amount with interest
void ATMUser::loanCash() {
    return;
}

// calculateLoan(principal, rate, durationYears)
// Returns total loan payment due using simple interest formula
// Output: double (total payable amount)
double ATMUser::calculateLoan(double principal, double rate, double durationYears) {
    return 0.0;
}

void Menu::loanMenu(ATMUser &user) {
    return;
}

// ====================================================================

// mainMenuGreetings()
// Description: Prints welcome message go to mainMenu when Y and quits when N
// <greetings>
// Would you like to use the <name>'s ATM (Y/N): 
bool Menu::mainMenuGreetings() {
    char choice;

    std::cout << "===" << BANK_NAME <<"===\n"; 
    do {
        std::cout << "Use ATM (Y/N): ";
        std::cin >> choice;
        
        if (input_validation()) {
            std::cout << "Invalid Input.\n";
            continue;
        }

        if (tolower(choice) == 'y') 
            return true;
        else if (tolower(choice) == 'n')
            return false;
        
    } while (tolower(choice) != 'y' && tolower(choice) != 'n');

    return false;
}

// showLoginMenu()
// Returns user choice: 1 = login, 2 = Create Account, 3 = Exit
// Main Menu
// [1] - Login
// [2] - Create Account
// [3] - Exit
int Menu::showLoginMenu() {
    int choice;
    do {
        std::cout << "[1] - Login\n";
        std::cout << "[2] - Create Account\n";
        std::cout << "[3] - Exit\n";
        std::cout << "Choose an Option: ";
        std::cin >> choice;

        if (input_validation()) {
            std::cout << "Invalid input\n";
            continue;
        }        
        if (choice > 3 || choice < 1) 
            std::cout << "Invalid option\n";
    } while (choice > 3 || choice < 1);
    
    return choice;
}

// bankMenu()
// [1] - My Account 
// [2] - Bills & Transfer
// [3] - Loan Services
// [4] - Transaction Log
// [5] - Exit
void Menu::bankMenu(ATMUser &user, Users &users) {
    int choice;
    do {
        std::cout << BAR << '\n';
        std::cout << "[1] - My Account\n";
        std::cout << "[2] - Bills & Transfer\n";
        std::cout << "[3] - Loan Services\n";
        std::cout << "[4] - Transaction Log\n";
        std::cout << "[5] - Exit\n";
        std::cout << "Choose an Option: ";
        std::cin >> choice;

        if (input_validation()) {
            std::cout << "Invalid Input.\n";
            continue;
        }
        if (choice > 5 || choice < 1) 
            std::cout << "Invalid Option.\n";
    } while (choice > 5 || choice < 1);

    switch (choice)
    {
        case 1: 
            myAccount(user);
            break;
        case 2:
            billsAndTransfer(user, users);
            break;
        case 3:
            loanMenu(user);
            break;
        case 4:
            transactionLog(user);
            break;
        case 5:
            return;
    }

    bankMenu(user, users);
}

// myAccount()
// [1] - Withdraw
// [2] - Deposit
// [3] - Balance
// [4] - Return
void Menu::myAccount(ATMUser &user) {
    int choice;
    float amount;

    do {
        std::cout << "MY ACCOUNT OPTIONS\n";
        std::cout << BAR << "\n";
        std::cout << "[1] - Withdraw\n";
        std::cout << "[2] - Deposit\n";
        std::cout << "[3] - Check Balance\n";
        std::cout << "[4] - Return\n";
        std::cout << "Choose an Option: "; 
        std::cin >> choice;

        if (input_validation()) {
            std::cout << "Invalid input\n";
            continue;
        }

        if (choice > 4 || choice < 1)
            std::cout << "Invalid option.\n";

    } while (choice > 4 || choice < 1);

    switch (choice) 
    {
        case 1:
            user.withdraw();
            break;
        case 2:
            user.deposit();
            break;
        case 3:
            user.displayBalance();
            break;
        case 4:
            return;
    }
}

// ===== @Coo & @Enriquez =====

void Menu::billsAndTransfer(ATMUser &user, Users &users) {
    // TODO
}

void Menu::transactionLog(ATMUser &user) {
    // TODO
}

void ATMUser::displayReceipt(std::string type, std::string ref, std::string recipientID) {
    // TODO
}
