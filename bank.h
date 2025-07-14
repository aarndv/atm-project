#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include <string>

// LOG CLASS ====================================

class Users;

class Log
{
private:
    std::string type, message, refNumber, recipientID;
    double amount;

public:
    Log();
    Log(std::string type, 
        double amount, 
        std::string message="",
        std::string ref="",
        std::string recipient="");

    void displayReceipt() const;

    std::string getType() const;
    double getAmount() const;
    std::string getMessage() const;
    std::string getRefNumber() const;
    std::string getRecipientID() const;

    void setType(const std::string &type);
    void setAmount(double amount);
    void setMessage(const std::string &msg);
    void setRefNumber(const std::string &ref);
    void setRecipientID(const std::string &rid);
};

class ATMUser {
private:
    std::string username, userID, PIN;
    double bal;
    std::vector<Log> logs;
    const int pinShift = 11;

    double calculateLoan(double principal, double rate, double durationYears);

    std::string encryptPin(const std::string &plainPin) const;
    std::string decryptPin(const std::string &cipheredPin) const;

public:
    ATMUser();
    ATMUser(std::string id, std::string username, std::string pin, double initialBal=0);

    std::string getID() const;
    std::string getUsername() const;
    std::string getPIN() const;
    double getBalance() const;
    std::vector<Log> getLogs() const;

    void setID(const std::string &id);
    void setUsername(const std::string &username);
    void setPIN(const std::string &plainPin);
    void setEncryptedPIN(const std::string &cipheredPIN);
    std::string getEncryptedPIN() const;
    void setBalance(double balance);
    void setLogs(const std::vector<Log> &logList);

    bool validatePin(const std::string &inputPin);

    void deposit();
    void withdraw();
    void payBills();
    void transferMoney(Users &users);
    void loanCash();
    void displayBalance();
    void convertBalanceToOtherCurrency(std::string currency);

    void displayReceipt(std::string type, std::string ref, std::string recipientID);
    void viewLogs();
    void addLog(std::string type, double amount, std::string message="", std::string referenceID="");

    void save();
    void load();
    void saveLogs();
    void loadLogs();
};

class Users {
private:
    std::vector<ATMUser> userList;
    int refCounter;

    void loadRefCounter();
    void saveRefCounter();

public:
    Users();
    bool addAccount(); // Returns false if name is already taken
    void saveAccounts();
    void loadAccounts();
    void addToAccountList(const std::string &id);
    ATMUser *loginPrompt();
    ATMUser *findUserByID(const std::string &id);
    std::string getNextUserID();
};

class Menu {
public:
    Menu();
    bool mainMenuGreetings();
    void bankMenu(ATMUser &user, Users &users);
    void myAccount(ATMUser &user);
    void billsAndTransfer(ATMUser &user, Users &users);
    void loanMenu(ATMUser &user);
    void transactionLog(ATMUser &user);
    int showLoginMenu();
};


#endif