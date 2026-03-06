#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

class Account{
protected:
    int accountId;
    string accountName;
    double bal;
    unsigned int permissions;
    vector<double> transactionHistory;
    
public:
    Account(int aid, string aname, double balance, unsigned int perm){
        accountId = aid;
        accountName = aname;
        bal = balance;
        permissions = perm;
    }
    
    virtual ~Account(){}
    
    virtual string getType() = 0;
    
    int getId(){ return accountId; }
    double getBalance(){ return bal; }
    
    bool checkWithdrawPermission(){
        return (permissions & 1) != 0;
    }
    
    bool checkDepositPermission(){
        return (permissions & 2) != 0;
    }
    
    bool checkTransferPermission(){
        return (permissions & 4) != 0;
    }
    
    virtual void deposit(double amount){
        if(!checkDepositPermission()){
            cout << "Error: You don't have deposit permission" << endl;
            return;
        }
        bal = bal + amount;
        transactionHistory.push_back(amount);
        cout << "Deposit successful! Amount: " << amount << endl;
        cout << "Current Balance: " << bal << endl;
    }
    
    virtual void withdraw(double amount){
        if(!checkWithdrawPermission()){
            cout << "Error: You don't have withdraw permission" << endl;
            return;
        }
        if(amount > bal){
            cout << "Error: Not enough balance" << endl;
            return;
        }
        bal = bal - amount;
        transactionHistory.push_back(-amount);
        cout << "Withdrawal successful! Amount: " << amount << endl;
        cout << "Remaining Balance: " << bal << endl;
    }
    
    void displayAccount(){
        cout << "Account Type: " << getType() << endl;
        cout << "Account ID: " << accountId << endl;
        cout << "Account Holder: " << accountName << endl;
        cout << "Balance: " << bal << endl;
    }
    
    virtual void saveToFile(ofstream& outFile){
        outFile << "ACCOUNT " << getType() << endl;
        outFile << accountId << " " << accountName << " " << bal << " " << permissions << endl;
        outFile << "TRANSACTIONS" << endl;
        for(int i = 0; i < (int)transactionHistory.size(); i++){
            outFile << transactionHistory[i] << endl;
        }
    }
    
    virtual void loadFromFile(ifstream& inFile){
        string line;
        getline(inFile, line);
        if(line == "TRANSACTIONS"){
            while(getline(inFile, line)){
                if(line.empty()) break;
                if(line.find("ACCOUNT") == 0) break;
                double trans = atof(line.c_str());
                transactionHistory.push_back(trans);
            }
        }
    }
    
    void calculateMonthlyReport(double monthlyData[12]){
        for(int i = 0; i < 12; i++){
            monthlyData[i] = 0;
        }
        int currentMonth = 0;
        for(int i = 0; i < (int)transactionHistory.size(); i++){
            if(i % 10 == 0 && i > 0){
                currentMonth++;
            }
            if(currentMonth >= 12){
                currentMonth = 11;
            }
            monthlyData[currentMonth] += transactionHistory[i];
        }
    }
};

class SavingsAccount : public Account{
public:
    SavingsAccount(int aid, string aname, double balance, unsigned int perm) 
        : Account(aid, aname, balance, perm){}
    
    string getType(){
        return "Savings";
    }
};

class CurrentAccount : public Account{
public:
    CurrentAccount(int aid, string aname, double balance, unsigned int perm) 
        : Account(aid, aname, balance, perm){}
    
    string getType(){
        return "Current";
    }
};

int main(){
    vector<Account*> allAccounts;
    
    cout << "=====================================" << endl;
    cout << "    Banking Management System" << endl;
    cout << "=====================================" << endl;
    
    while(true){
        cout << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. View All Accounts" << endl;
        cout << "5. Save Data to File" << endl;
        cout << "6. Load Data from File" << endl;
        cout << "7. Exit Program" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        cout << endl;
        
        if(choice == 1){
            int accId, accType, permissionFlags;
            string holderName;
            double initialBalance;
            
            cout << "Enter Account ID: ";
            cin >> accId;
            cin.ignore();
            
            cout << "Enter Account Holder Name: ";
            getline(cin, holderName);
            
            cout << "Enter Initial Balance: ";
            cin >> initialBalance;
            
            cout << "Select Account Type:" << endl;
            cout << "  1 - Savings Account" << endl;
            cout << "  2 - Current Account" << endl;
            cout << "Enter choice: ";
            cin >> accType;
            
            cout << "Set Permissions (use bitwise OR):" << endl;
            cout << "  1 - Withdraw Permission" << endl;
            cout << "  2 - Deposit Permission" << endl;
            cout << "  4 - Transfer Permission" << endl;
            cout << "Enter permission value: ";
            cin >> permissionFlags;
            
            Account* newAccount = NULL;
            
            if(accType == 1){
                newAccount = new SavingsAccount(accId, holderName, initialBalance, permissionFlags);
            }
            else if(accType == 2){
                newAccount = new CurrentAccount(accId, holderName, initialBalance, permissionFlags);
            }
            else{
                cout << "Invalid account type!" << endl;
                continue;
            }
            
            allAccounts.push_back(newAccount);
            cout << endl << "Account created successfully!" << endl;
        }
        else if(choice == 2){
            int searchId;
            double depositAmount;
            
            cout << "Enter Account ID: ";
            cin >> searchId;
            
            cout << "Enter Deposit Amount: ";
            cin >> depositAmount;
            
            bool accountFound = false;
            for(int i = 0; i < (int)allAccounts.size(); i++){
                if(allAccounts[i]->getId() == searchId){
                    allAccounts[i]->deposit(depositAmount);
                    accountFound = true;
                    break;
                }
            }
            
            if(!accountFound){
                cout << "Account not found!" << endl;
            }
        }
        else if(choice == 3){
            int searchId;
            double withdrawAmount;
            
            cout << "Enter Account ID: ";
            cin >> searchId;
            
            cout << "Enter Withdrawal Amount: ";
            cin >> withdrawAmount;
            
            bool accountFound = false;
            for(int i = 0; i < (int)allAccounts.size(); i++){
                if(allAccounts[i]->getId() == searchId){
                    allAccounts[i]->withdraw(withdrawAmount);
                    accountFound = true;
                    break;
                }
            }
            
            if(!accountFound){
                cout << "Account not found!" << endl;
            }
        }
        else if(choice == 4){
            if(allAccounts.size() == 0){
                cout << "No accounts available!" << endl;
            }
            else{
                cout << "========== All Accounts ==========" << endl;
                for(int i = 0; i < (int)allAccounts.size(); i++){
                    cout << endl;
                    allAccounts[i]->displayAccount();
                    cout << "-----------------------------------" << endl;
                }
            }
        }
        else if(choice == 5){
            string fileName;
            cout << "Enter file name to save: ";
            cin >> fileName;
            
            ofstream outputFile(fileName);
            
            for(int i = 0; i < (int)allAccounts.size(); i++){
                allAccounts[i]->saveToFile(outputFile);
            }
            
            outputFile.close();
            cout << "Data saved successfully!" << endl;
        }
        else if(choice == 6){
            string fileName;
            cout << "Enter file name to load: ";
            cin >> fileName;
            
            ifstream inputFile(fileName);
            
            if(!inputFile.is_open()){
                cout << "Error: File not found!" << endl;
                continue;
            }
            
            for(int i = 0; i < (int)allAccounts.size(); i++){
                delete allAccounts[i];
            }
            allAccounts.clear();
            
            string line;
            while(getline(inputFile, line)){
                if(line.find("ACCOUNT") == 0){
                    char buffer[256];
                    strcpy(buffer, line.c_str());
                    
                    char* token = strtok(buffer, " ");
                    token = strtok(NULL, " ");
                    
                    string accountType = token;
                    
                    int accId;
                    char accName[100];
                    double accBalance;
                    unsigned int accPerms;
                    
                    inputFile >> accId >> accName >> accBalance >> accPerms;
                    inputFile.ignore();
                    
                    Account* loadedAccount = NULL;
                    
                    if(accountType == "Savings"){
                        loadedAccount = new SavingsAccount(accId, accName, accBalance, accPerms);
                    }
                    else if(accountType == "Current"){
                        loadedAccount = new CurrentAccount(accId, accName, accBalance, accPerms);
                    }
                    
                    if(loadedAccount != NULL){
                        loadedAccount->loadFromFile(inputFile);
                        allAccounts.push_back(loadedAccount);
                    }
                }
            }
            
            inputFile.close();
            cout << "Data loaded successfully!" << endl;
            cout << "Total accounts loaded: " << allAccounts.size() << endl;
        }
        else if(choice == 7){
            cout << "Thank you for using Banking System!" << endl;
            cout << "Exiting program..." << endl;
            break;
        }
        else{
            cout << "Invalid choice! Please select 1-7" << endl;
        }
    }
    
    for(int i = 0; i < (int)allAccounts.size(); i++){
        delete allAccounts[i];
    }
    
    return 0;
}
