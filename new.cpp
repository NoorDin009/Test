// =====================================================
// BANKING MANAGEMENT SYSTEM (FUNDAMENTAL C++)
// NO OOP | NO CLASSES | NO INHERITANCE
// Lines ~850
// =====================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

// =====================================================
// CONSTANTS
// =====================================================
const int MAX_ACCOUNTS = 300;

// =====================================================
// STRUCTURE
// =====================================================
struct Account {
    int accountNo;
    char name[50];
    char accountType[20]; // Saving / Current
    float balance;
};

// =====================================================
// GLOBAL VARIABLES
// =====================================================
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// =====================================================
// FUNCTION DECLARATIONS
// =====================================================
void mainMenu();
void addAccount();
void displayAccounts();
void searchAccount();
void depositAmount();
void withdrawAmount();
void deleteAccount();
void saveToFile();
void loadFromFile();
void pause();
void header(const char title[]);

// =====================================================
// MAIN FUNCTION
// =====================================================
int main() {
    loadFromFile();
    int choice;

    do {
        mainMenu();
        cin >> choice;

        switch (choice) {
            case 1: addAccount(); break;
            case 2: displayAccounts(); break;
            case 3: searchAccount(); break;
            case 4: depositAmount(); break;
            case 5: withdrawAmount(); break;
            case 6: deleteAccount(); break;
            case 7: saveToFile(); cout << "\nData Saved Successfully!" << endl; break;
            case 0: saveToFile(); cout << "\nThank you for using Bank System!" << endl; break;
            default: cout << "\nInvalid Choice!" << endl;
        }
        pause();
    } while (choice != 0);

    return 0;
}

// =====================================================
// UI FUNCTIONS
// =====================================================
void header(const char title[]) {
    system("clear"); // use cls for Windows
    cout << "===============================================" << endl;
    cout << "        BANKING MANAGEMENT SYSTEM" << endl;
    cout << "===============================================" << endl;
    cout << "           " << title << endl;
    cout << "===============================================" << endl;
}

void mainMenu() {
    header("MAIN MENU");
    cout << "1. Open New Account" << endl;
    cout << "2. Display All Accounts" << endl;
    cout << "3. Search Account" << endl;
    cout << "4. Deposit Amount" << endl;
    cout << "5. Withdraw Amount" << endl;
    cout << "6. Close Account" << endl;
    cout << "7. Save Data" << endl;
    cout << "0. Exit" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Enter Choice: ";
}

// =====================================================
// ADD ACCOUNT
// =====================================================
void addAccount() {
    header("OPEN NEW ACCOUNT");

    if (accountCount >= MAX_ACCOUNTS) {
        cout << "Account limit reached!" << endl;
        return;
    }

    Account a;

    cout << "Enter Account Number: ";
    cin >> a.accountNo;
    cin.ignore();

    cout << "Enter Account Holder Name: ";
    cin.getline(a.name, 50);

    cout << "Enter Account Type (Saving/Current): ";
    cin.getline(a.accountType, 20);

    cout << "Enter Initial Balance: ";
    cin >> a.balance;

    accounts[accountCount++] = a;

    cout << "\nAccount created successfully!" << endl;
}

// =====================================================
// DISPLAY ACCOUNTS
// =====================================================
void displayAccounts() {
    header("ALL ACCOUNTS LIST");

    if (accountCount == 0) {
        cout << "No accounts found!" << endl;
        return;
    }

    cout << left << setw(12) << "Acc No"
         << setw(25) << "Name"
         << setw(15) << "Type"
         << setw(12) << "Balance" << endl;

    cout << string(64, '-') << endl;

    for (int i = 0; i < accountCount; i++) {
        cout << left << setw(12) << accounts[i].accountNo
             << setw(25) << accounts[i].name
             << setw(15) << accounts[i].accountType
             << setw(12) << accounts[i].balance << endl;
    }
}

// =====================================================
// SEARCH ACCOUNT
// =====================================================
void searchAccount() {
    header("SEARCH ACCOUNT");

    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNo == acc) {
            cout << "\nAccount Found!" << endl;
            cout << "Name: " << accounts[i].name << endl;
            cout << "Type: " << accounts[i].accountType << endl;
            cout << "Balance: " << accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// =====================================================
// DEPOSIT
// =====================================================
void depositAmount() {
    header("DEPOSIT AMOUNT");

    int acc;
    float amount;

    cout << "Enter Account Number: ";
    cin >> acc;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNo == acc) {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            accounts[i].balance += amount;
            cout << "\nAmount Deposited Successfully!" << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// =====================================================
// WITHDRAW
// =====================================================
void withdrawAmount() {
    header("WITHDRAW AMOUNT");

    int acc;
    float amount;

    cout << "Enter Account Number: ";
    cin >> acc;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNo == acc) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (amount > accounts[i].balance) {
                cout << "Insufficient Balance!" << endl;
                return;
            }

            accounts[i].balance -= amount;
            cout << "\nAmount Withdrawn Successfully!" << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// =====================================================
// DELETE ACCOUNT
// =====================================================
void deleteAccount() {
    header("CLOSE ACCOUNT");

    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNo == acc) {
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            cout << "\nAccount closed successfully!" << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

// =====================================================
// FILE HANDLING
// =====================================================
void saveToFile() {
    ofstream file("bank.dat", ios::binary);
    file.write((char*)&accountCount, sizeof(accountCount));
    file.write((char*)accounts, sizeof(Account) * accountCount);
    file.close();
}

void loadFromFile() {
    ifstream file("bank.dat", ios::binary);
    if (!file) return;

    file.read((char*)&accountCount, sizeof(accountCount));
    file.read((char*)accounts, sizeof(Account) * accountCount);
    file.close();
}

// =====================================================
// PAUSE
// =====================================================
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
