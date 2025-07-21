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
    Log(string type, double amount, string message="", string ref="", string referenceID="");

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

    bool hasOutstandingLoan() const;
    void getLoanDetails(double &principal, double &durationYears);
    bool presentLoanAndConfirm(double principal, double totalPayable, double monthlyPayment, double durationYears) const;
    void processApprovedLoan(double principal, Users &users);

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

    void deposit(Users &users);
    void withdraw(Users &users);
    void payBills(Users &users);
    void transferMoney(Users &users);
    void loanCash(Users &users);
    void displayBalance();
    void convertBalanceToOtherCurrency(string currency);

    void displayReceipt();
    void viewLogs();
    void addLog(Users &users, string type, double amount, string message="", string referenceID="");

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
    string generateRefNumber();
};

class Menu {
public:
    Menu();
    bool mainMenuGreetings();
    void bankMenu(ATMUser &user, Users &users);
    void myAccount(ATMUser &user, Users &users);
    void billsAndTransfer(ATMUser &user, Users &users);
    void loanMenu(ATMUser &user, Users &users);
    void transactionLog(ATMUser &user, Users &users);
    int showLoginMenu();
};

#endif