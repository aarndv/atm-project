#include <iostream>
#include "bank.h"

int main()
{
    Users bank;
    bank.loadAccounts();

    Menu ui;
    if (!ui.mainMenuGreetings()) return 0;

    ATMUser *currentUser = NULL;

    while (!currentUser)
    {
        int choice = ui.showLoginMenu();
        bool created;
        switch (choice)
        {
            case 1:
                currentUser = bank.loginPrompt();
                if (!currentUser) {
                    std::cout << "Login failed. Please try again.\n";
                }
                break;
            case 2:
                created = bank.addAccount();
                if (!created) {
                    std::cout << "That username is already taken. Please choose another one.\n";
                }
                break;
            case 3:
                std::cout << "Thank you for banking with HaBank Buhay. Have a great day!\n";
                return 0;
                break;
            default:
                std::cout << "Invalid input. Try again.\n";
                break;
        }
    }

    ui.bankMenu(*currentUser, bank);
    bank.saveAccounts();

    return 0;
}