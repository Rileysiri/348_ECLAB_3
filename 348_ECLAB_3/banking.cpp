#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


class Account {
    protected:
        string account_Number;
        string accountHolder;

    public:
        double balance;

        Account(const string &account_Number, const string &accountHolder, double balance)
            : account_Number(account_Number), accountHolder(accountHolder), balance(balance) {}

        virtual void displayDetails() const {
            cout << fixed << setprecision(2);
            cout << "Account Details for Account (ID: " << account_Number <<"): \n";
            cout << "Holder: " << accountHolder << "\n";
            cout << "Balance: $" << balance << "\n";
        }

        void deposit(double amount) {
            balance += amount;
        }

        virtual void withdraw(double amount) {
            if (balance >= amount) {
                balance -= amount;
            } else {
                cout << "Insufficient funds" << "\n";
            }
        }

        friend ostream &operator<< (ostream &output, const Account &account) {
            account.displayDetails();
            return output;
        }
};

class SavingsAccount: public Account {
    private: 
        double interest;

    public: 
        int transferAmount = 300;

        SavingsAccount(const string &account_Number, const string &accountHolder, double balance, double interest) 
            : Account(account_Number, accountHolder, balance), interest(interest) {}

        void displayDetails() const override {
            cout << fixed << setprecision(2);
            cout << "Account Details for Savings Account (ID: " << account_Number << "): \n";
            cout << "Holder: " << accountHolder << "\n";
            cout << "Balance: $" << balance << "\n";
            cout << "Interest Rate: " << interest * 100 << "%" << "\n";
        }

        void withdraw(double amount) override {
            const double min_Balance = 100;
            if (balance - amount >= min_Balance) {
                balance -= amount;
            } else {
                cout << "Invalid withdrawal. Must meet minimum balance." << "\n";
            }
        }
};

class CurrentAccount: public Account {
    private:
        double Limit;

    public:
        int transferAmount = 300;

        CurrentAccount(const string &account_Number, const string &accountHolder, double balance, double Limit)
            : Account(account_Number, accountHolder, balance), Limit(Limit) {}

        void displayDetails() const override {
            cout << fixed << setprecision(2);
            cout << "Account Details for Current Account (ID: " << account_Number << "): \n";
            cout << "Holder: " << accountHolder << "\n";
            cout << "Balance: $" << balance << "\n";
            cout << "Overdraft Limit: $" << Limit << "\n";
        }

        void withdraw(double amount) override {
            if (balance - amount >= -Limit) {
                balance -= amount;
            } else {
                cout << "Invalid withdrawal. Must meet overdraft limit." << "\n";
            }
        }

    CurrentAccount operator+(const SavingsAccount &savings) const {
        CurrentAccount result = *this;
        if (savings.balance >= transferAmount) {
            result.deposit(transferAmount);
            const_cast<SavingsAccount&>(savings).withdraw(transferAmount);
        } else {
            cout << "Invalid transfer. Insufficient funds" << "\n";
        }
        return result;
    }
};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    cout << savings << "\n";
    cout << current << "\n";

    savings.deposit(500);
    current.withdraw(1000);

    cout << "Account Details after deposit and withdrawal: \n";

    cout << savings << "\n";
    cout << current << "\n";

    current = current + savings;

    cout << "Account Details after transfer: \n";

    cout << savings << "\n";
    cout << current << "\n";

    return 0;
}
