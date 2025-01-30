#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // Include cstdlib for atof

using namespace std;

struct Transaction {
    string type; // "income" or "expense"
    double amount;
    string description;
};

class FinanceTracker {
private:
    vector<Transaction> transactions;

public:
    void addTransaction(const string type, double amount, const string description) {
        Transaction t;
        t.type = type;
        t.amount = amount;
        t.description = description;
        transactions.push_back(t);
    }

    void viewTransactions() const {
        for (size_t i = 0; i < transactions.size(); ++i) {
            cout << transactions[i].type << ": " << transactions[i].amount << " - " << transactions[i].description << endl;
        }
    }

    double getTotalIncome() const {
        double total = 0;
        for (size_t i = 0; i < transactions.size(); ++i) {
            if (transactions[i].type == "income") total += transactions[i].amount;
        }
        return total;
    }

    double getTotalExpenses() const {
        double total = 0;
        for (size_t i = 0; i < transactions.size(); ++i) {
            if (transactions[i].type == "expense") total += transactions[i].amount;
        }
        return total;
    }

    void saveToFile(const string filename) const {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            for (size_t i = 0; i < transactions.size(); ++i) {
                file << transactions[i].type << "," << transactions[i].amount << "," << transactions[i].description << endl;
            }
            file.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    string type = line.substr(0, pos1);
                    double amount = atof(line.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
                    string description = line.substr(pos2 + 1);
                    addTransaction(type, amount, description);
                }
            }
            file.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    FinanceTracker tracker;
    tracker.loadFromFile("transactions.txt");

    int choice;
    do {
        cout << "1. Add Income\n2. Add Expense\n3. View Transactions\n4. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string description;
            cout << "Enter income amount: ";
            cin >> amount;
            cout << "Enter description: ";
            cin.ignore();
            getline(cin, description);
            tracker.addTransaction("income", amount, description);
        } else if (choice == 2) {
            double amount;
            string description;
            cout << "Enter expense amount: ";
            cin >> amount;
            cout << "Enter description: ";
            cin.ignore();
            getline(cin, description);
            tracker.addTransaction("expense", amount, description);
        } else if (choice == 3) {
            tracker.viewTransactions();
        }
    } while (choice != 4);

    tracker.saveToFile("transactions.txt");
    return 0;
}
