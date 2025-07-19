#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Users;

class Log
{
private:
    string type, message, refNumber, recipientID;
    double amount;

public:
    Log();
    Log(string type, double amount, string message="", string ref="", string recipient="");

    void displayReceipt() const;

    string getType() const;
    double getAmount() const;
    string getMessage() const;
    string getRefNumber() const;
    string getRecipientID() const;

    void setType(const string &type);
    void setAmount(double amount);
    void setMessage(const string &msg);
    void setRefNumber(const string &ref);
    void setRecipientID(const string &rid);
};

class ATMUser {
private:
    string username, userID, PIN;
    double bal;
    vector<Log> logs;
    static const int pinShift = 11;

    double calculateLoan(double principal, double rate, double durationYears);

    string encryptPin(const string &plainPin) const;
    string decryptPin(const string &cipheredPin) const;

public:
    ATMUser();
    ATMUser(string id, string username, string pin, double initialBal=0);

    string getID() const;
    string getUsername() const;
    string getPIN() const;
    double getBalance() const;
    vector<Log> getLogs() const;

    void setID(const string &id);
    void setUsername(const string &username);
    void setPIN(const string &plainPin);
    void setEncryptedPIN(const string &cipheredPIN);
    string getEncryptedPIN() const;
    void setBalance(double balance);
    void setLogs(const vector<Log> &logList);

    bool validatePin(const string &inputPin);

    void deposit();
    void withdraw();
    void payBills();
    void transferMoney(Users &users);
    void loanCash();
    void displayBalance();
    void convertBalanceToOtherCurrency(string currency);

    void displayReceipt(string type, string ref, string recipientID, double amount);
    void viewLogs();
    void addLog(string type, double amount, string message="", string referenceID="");

    void save();
    void load();
    void saveLogs();
    void loadLogs();
};

class Users {
private:
    vector<ATMUser> userList;
    int refCounter;

    void loadRefCounter();
    void saveRefCounter();

public:
    Users();
    bool addAccount(); // Returns false if name is already taken
    void saveAccounts();
    void loadAccounts();
    void addToAccountList(const string &id);
    ATMUser *loginPrompt();
    ATMUser *findUserByID(const string &id);
    string getNextUserID();
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