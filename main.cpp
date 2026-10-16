#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Transaction {
    string type;
    double amount;
    string note;
};

class Account {
private:
    string owner;
    string accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(string name, string number, double openingBalance)
        : owner(name), accountNumber(number), balance(openingBalance) {
        history.push_back({"Account opened", openingBalance, "Opening balance"});
    }

    string getNumber() const { return accountNumber; }
    string getOwner() const { return owner; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return;
        }
        balance += amount;
        history.push_back({"Deposit", amount, "Cash deposit"});
        cout << "Deposit successful.\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        history.push_back({"Withdrawal", amount, "Cash withdrawal"});
        cout << "Withdrawal successful.\n";
        return true;
    }

    bool transferTo(Account& recipient, double amount) {
        if (&recipient == this) {
            cout << "You cannot transfer to the same account.\n";
            return false;
        }
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        recipient.balance += amount;
        history.push_back({"Transfer out", amount, "To account " + recipient.accountNumber});
        recipient.history.push_back({"Transfer in", amount, "From account " + accountNumber});
        cout << "Transfer successful.\n";
        return true;
    }

    void showDetails() const {
        cout << "\nAccount holder: " << owner
             << "\nAccount number: " << accountNumber
             << "\nBalance: " << fixed << setprecision(2) << balance << '\n';
    }

    void showHistory() const {
        cout << "\n--- Transaction History for " << accountNumber << " ---\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (size_t i = 0; i < history.size(); ++i) {
            cout << i + 1 << ". " << history[i].type
                 << " | Amount: " << fixed << setprecision(2) << history[i].amount
                 << " | " << history[i].note << '\n';
        }
    }
};

int findAccount(const vector<Account>& accounts, const string& number) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getNumber() == number) return static_cast<int>(i);
    }
    return -1;
}

int main() {
    vector<Account> accounts;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       CODEALPHA BANKING SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Create account\n2. Deposit\n3. Withdraw\n";
        cout << "4. Transfer funds\n5. Account details\n6. Transaction history\n7. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string number, name, recipientNumber;
        double amount;
        int index, recipientIndex;

        switch (choice) {
            case 1: {
                cout << "Account holder name (one word): ";
                cin >> name;
                cout << "Create a unique account number: ";
                cin >> number;
                if (findAccount(accounts, number) != -1) {
                    cout << "That account number already exists.\n";
                    break;
                }
                cout << "Opening balance (0 or more): ";
                if (!(cin >> amount) || amount < 0) {
                    cout << "Invalid opening balance.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                accounts.emplace_back(name, number, amount);
                cout << "Account created successfully.\n";
                break;
            }
            case 2:
            case 3: {
                cout << "Account number: ";
                cin >> number;
                index = findAccount(accounts, number);
                if (index == -1) {
                    cout << "Account not found.\n";
                    break;
                }
                cout << "Amount: ";
                if (!(cin >> amount)) {
                    cout << "Invalid amount.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (choice == 2) accounts[index].deposit(amount);
                else accounts[index].withdraw(amount);
                break;
            }
            case 4: {
                cout << "From account number: ";
                cin >> number;
                index = findAccount(accounts, number);
                if (index == -1) {
                    cout << "Source account not found.\n";
                    break;
                }
                cout << "To account number: ";
                cin >> recipientNumber;
                recipientIndex = findAccount(accounts, recipientNumber);
                if (recipientIndex == -1) {
                    cout << "Recipient account not found.\n";
                    break;
                }
                cout << "Amount: ";
                if (!(cin >> amount)) {
                    cout << "Invalid amount.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                accounts[index].transferTo(accounts[recipientIndex], amount);
                break;
            }
            case 5: {
                cout << "Account number: ";
                cin >> number;
                index = findAccount(accounts, number);
                if (index == -1) cout << "Account not found.\n";
                else accounts[index].showDetails();
                break;
            }
            case 6: {
                cout << "Account number: ";
                cin >> number;
                index = findAccount(accounts, number);
                if (index == -1) cout << "Account not found.\n";
                else accounts[index].showHistory();
                break;
            }
            case 7:
                cout << "Thank you for using the demo banking system.\n";
                break;
            default:
                cout << "Invalid choice. Select 1–7.\n";
        }
    } while (choice != 7);

    return 0;
}
