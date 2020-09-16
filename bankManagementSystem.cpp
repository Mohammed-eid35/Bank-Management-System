/****************************************
 *
 * Auther : Muhammad Eid - Mohammed-eid35.
 * Bank management system.
 * Version 01.
 * cpp Project.
 * First Year FCI, First Semester.
 *
****************************************/

/// Start Header Files ///

#include <bits/stdc++.h>
using namespace std;

/// End Header Files ///


/// Start Helper Functions ///

vector<string> ReadFileLines(string path){
    vector<string> lines;

    fstream file(path.c_str());

    if(file.fail()){
        cout << "\nERROR: Can not open the file!!\n\n";
        return lines;
    }

    string line;

    while(getline(file, line))
        if(line.size() != 0)
            lines.push_back(line);

    file.close();

    return lines;
}

void WriteFileLines(string path, vector<string> lines, bool append = true){
    auto status = ios::in | ios::out | ios::app;

    if(!append)
        status = ios::in | ios::out | ios::trunc;

    fstream file(path.c_str(), status);

    if(file.fail()){
        cout << "\nERROR: Can not open the file!!\n\n";
        return;
    }

    for(auto line : lines)
        file << line << "\n";

    file.close();
}

vector<string> SpiltString(string line, string delimeter = ","){
    vector<string> subs;
    string subStr;
    int pos = 0;

    while((pos = (int)line.find(delimeter)) != -1){
        subStr = line.substr(0, pos);
        subs.push_back(subStr);
        line.erase(0, pos+delimeter.size());
    }
    subs.push_back(subStr);
    return subs;
}

int StringTOInteger(string num){
    istringstream iss(num);
    int val;
    iss >> val;
    return val;
}

int ValidChoice(int lft, int rit){
    int choice; cin >> choice;

    if(choice >= lft && choice <= rit)
        return choice;

    cout << "\nChoose number in range "<< lft << " - " << rit << " : ";
    ValidChoice(lft, rit);
}

int ShowMenu(vector<string> menu){
    cout << "\n\n";

    for(int i=0; i<menu.size(); ++i)
        cout << (i+1) << "- " << menu[i] << "\n";

    cout << "Choose number to continue: ";
    return ValidChoice(1, menu.size());
}

/// End Helper Functions ///


/// Start Structs ///

struct AdminAccount{
    string user_name;
    string password;
    string name;
    string phone_number;
    int age;

    AdminAccount(){
        user_name = password = name = phone_number = "";
        age = 0;
    }

    AdminAccount(string line){
        vector<string> user_data = SpiltString(line);

        assert(user_data.size() == 5);

        user_name = user_data[0];
        password = user_data[1];
        name = user_data[2];
        phone_number = user_data[3];
        age = StringTOInteger(user_data[4]);
    }

    string toString(){
        ostringstream oss;
        oss << user_name << ","
            << password << ","
            << name << ","
            << phone_number << ","
            << age;
        return oss.str();
    }

    void printData(){
        cout << "\n\n"
             << "User Name: " << user_name << "\n"
             << "Password: " << password << "\n"
             << "Name: " << name << "\n"
             << "Phone Number: " << phone_number << "\n"
             << "Age: " << age << "\n\n";
    }

    void setData(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, user_name);
        cout << "Enter password: "; getline(cin, password);
        cout << "Enter name: "; getline(cin, name);
        cout << "Enter phone number: "; getline(cin, phone_number);
        cout << "Enter age: "; cin >> age;
        cout << "\n\n";
    }
};

struct UserAccount{
    string user_name;
    string password;
    string name;
    string phone_number;
    int age;
    int amount_of_money;

    UserAccount(){
        user_name = password = name = phone_number = "";
        age = amount_of_money = 0;
    }

    UserAccount(string line){
        vector<string> user_data = SpiltString(line);

        assert(user_data.size() == 6);

        user_name = user_data[0];
        password = user_data[1];
        name = user_data[2];
        phone_number = user_data[3];
        age = StringTOInteger(user_data[4]);
        amount_of_money = StringTOInteger(user_data[5]);
    }

    string toString(){
        ostringstream oss;
        oss << user_name << ","
            << password << ","
            << name << ","
            << phone_number << ","
            << age << ","
            << amount_of_money;
        return oss.str();
    }

    void printData(){
        cout << "\n\n"
             << "User Name: " << user_name << "\n"
             << "Password: " << password << "\n"
             << "Name: " << name << "\n"
             << "Phone Number: " << phone_number << "\n"
             << "Age: " << age << "\n"
             << "Money: $" << amount_of_money << "\n\n";
    }

    void setData(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, user_name);
        cout << "Enter password: "; getline(cin, password);
        cout << "Enter name: "; getline(cin, name);
        cout << "Enter phone number: "; getline(cin, phone_number);
        cout << "Enter age: "; cin >> age;
        cout << "Enter amount of money: "; cin >> amount_of_money;
        cout << "\n\n";
    }
};

struct AdminManager{
    map<string, AdminAccount> admins_data_map;
    AdminAccount cur_admin;

    void loadDatabase(){
        admins_data_map.clear();

        vector<string> lines = ReadFileLines("admins.txt");

        for(auto &line : lines){
            AdminAccount admin(line);
            admins_data_map[admin.user_name] = admin;
        }
    }

    void login(){
        cin.ignore();
        while(true){
            cout << "\n\n";
            cout << "Enter user name: "; getline(cin, cur_admin.user_name);
            cout << "Enter Password: "; getline(cin, cur_admin.password);

            if(!adminExist()){
                cout << "\n\nWrong user name!!";
                continue;
            }

            AdminAccount ext_admin = admins_data_map[cur_admin.user_name];

            if(ext_admin.password != cur_admin.password){
                cout << "\n\nWrong Password!!";
                continue;
            }

            cur_admin  = ext_admin;
            break;
        }
    }

    bool adminExist(){
        return admins_data_map.count(cur_admin.user_name);
    }

    void insertAdmin(){
        vector<string> lines(1, cur_admin.toString());

        WriteFileLines("admins.txt", lines);
    }

    void deleteAdmin(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_admin.user_name);

        if(adminExist())
            admins_data_map.erase(cur_admin.user_name);
        else
            cout << "\nThe user name is not exsist\n\n";
    }

    void updateDatabase(){
        vector<string> lines;

		for(auto &pair : admins_data_map)
			lines.push_back(pair.second.toString());

		WriteFileLines("admins.txt", lines, false);
    }

    void updateAdmin(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_admin.user_name);

        if(!adminExist()){
            cout << "\nThe user name is not exsist";
            return;
        }

        cout << "\n\n";
        cout << "Enter password: "; getline(cin, cur_admin.password);
        cout << "Enter name: "; getline(cin, cur_admin.name);
        cout << "Enter phone number: "; getline(cin, cur_admin.phone_number);
        cout << "Enter age: "; cin >> cur_admin.age;

        admins_data_map[cur_admin.user_name] = cur_admin;
    }

    void searchAdmin(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_admin.user_name);

        if(!adminExist()){
            cout << "\nThe user name is not exist";
            return;
        }

        admins_data_map[cur_admin.user_name].printData();
    }
};

struct UsersManager{
    map<string, UserAccount> users_data_map;
    UserAccount cur_user;

    void loadDatabase(){
        users_data_map.clear();

        vector<string> lines = ReadFileLines("users.txt");

        for(auto &line : lines){
            UserAccount user(line);
            users_data_map[user.user_name] = user;
        }
    }

    void login(){
        cin.ignore();
        while(true){
            cout << "\n\n";
            cout << "Enter user name: "; getline(cin, cur_user.user_name);
            cout << "Enter Password: "; getline(cin, cur_user.password);

            if(!userExist()){
                cout << "\n\nWrong user name!!";
                continue;
            }

            UserAccount ext_user = users_data_map[cur_user.user_name];

            if(ext_user.password != cur_user.password){
                cout << "\n\nWrong Password!!";
                continue;
            }

            cur_user  = ext_user;
            break;
        }
    }

    void depositMoney(){
        cout << "\n\n";
        cout << "Your money = $" << cur_user.amount_of_money << "\n";
        cout << "Enter the value: ";
        int depositMoney; cin >> depositMoney;

        cur_user.amount_of_money += depositMoney;

        users_data_map[cur_user.user_name] = cur_user;
    }

    void withdrawMoney(){
        cout << "\n\n";
        cout << "Your money = $" << cur_user.amount_of_money << "\n";
        cout << "Enter the value: ";
        int withdraw_money = ValidChoice(0, cur_user.amount_of_money);

        cur_user.amount_of_money -= withdraw_money;

        users_data_map[cur_user.user_name] = cur_user;
    }

    void updateDatabase(){
        vector<string> lines;

		for(auto &pair : users_data_map)
			lines.push_back(pair.second.toString());

		WriteFileLines("users.txt", lines, false);
    }

    void insertUser(){
        vector<string> lines(1, cur_user.toString());

        WriteFileLines("users.txt", lines);
    }

    bool userExist(){
        return users_data_map.count(cur_user.user_name);
    }

    void deleteUser(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_user.user_name);

        if(userExist())
            users_data_map.erase(cur_user.user_name);
        else
            cout << "\nThe user name is not exist";
    }

    void updateUser(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_user.user_name);

        if(!userExist()){
            cout << "\nThe user name is not exist";
            return;
        }

        cout << "\n\n";
        cout << "Enter password: "; getline(cin, cur_user.password);
        cout << "Enter name: "; getline(cin, cur_user.name);
        cout << "Enter phone number: "; getline(cin, cur_user.phone_number);
        cout << "Enter age: "; cin >> cur_user.age;
        cout << "Enter amount of money: "; cin >> cur_user.amount_of_money;

        users_data_map[cur_user.user_name] = cur_user;
    }

    void searchUser(){
        cin.ignore();
        cout << "\n\n";
        cout << "Enter user name: "; getline(cin, cur_user.user_name);

        if(!userExist()){
            cout << "\nThe user name is not exist";
            return;
        }

        users_data_map[cur_user.user_name].printData();
    }
};

struct BankSystem{
    AdminManager admin_manager;
    AdminManager newAdmin;
    UsersManager user_manager;

    void loadDatabase(){
        admin_manager.loadDatabase();
        newAdmin.loadDatabase();
        user_manager.loadDatabase();
    }

    vector<string> adminOrUser(){
        vector<string> menu;
        menu.push_back("Admin");
        menu.push_back("User");

        return menu;
    }

    bool main_admin = false;
    vector<string> adminMenu(){
        vector<string> menu;
        menu.push_back("Display your data");
        menu.push_back("Create new user account");
        menu.push_back("Delete user account");
        menu.push_back("Update user account");
        menu.push_back("Search for user account");

        if(admin_manager.cur_admin.user_name == "Admin"){
            main_admin = true;
            menu.push_back("Craete new admin account");
            menu.push_back("Delete admin account");
            menu.push_back("Update admin account");
            menu.push_back("Search for admin account");
        }
        menu.push_back("Logout");

        return menu;
    }

    vector<string> userMenu(){
        vector<string> menu;
        menu.push_back("Display your data");
        menu.push_back("Withdraw money");
        menu.push_back("Deposit money");
        menu.push_back("Logout");

        return menu;
    }

    void run(){
        loadDatabase();

        int choice = ShowMenu(adminOrUser());

        if(choice == 1){
            admin_manager.login();

            while(true){
                loadDatabase();
                choice = ShowMenu(adminMenu());

                if(choice == 1)
                    admin_manager.cur_admin.printData();
                else if(choice == 2){
                    while(true){
                        user_manager.cur_user.setData();

                        if(user_manager.userExist()){
                            cout << "\nThe user name is already exist!!\n\n";
                            continue;
                        }

                        user_manager.insertUser();
                        break;
                    }
                }
                else if(choice == 3){
                    user_manager.deleteUser();
                    user_manager.updateDatabase();
                }
                else if(choice == 4){
                    user_manager.updateUser();
                    user_manager.updateDatabase();
                }
                else if(choice == 5)
                    user_manager.searchUser();
                else if(choice == 6 && main_admin){
                    while(true){
                        newAdmin.cur_admin.setData();

                        if(newAdmin.adminExist()){
                            cout << "\nThe user name is already exist!!\n\n";
                            continue;
                        }

                        newAdmin.insertAdmin();
                        break;
                    }
                }
                else if(choice == 7 && main_admin){
                    newAdmin.deleteAdmin();
                    newAdmin.updateDatabase();
                }
                else if(choice == 8 && main_admin){
                    newAdmin.updateAdmin();
                    newAdmin.updateDatabase();
                }
                else if(choice == 9 && main_admin){
                    newAdmin.searchAdmin();
                }
                else{
                    main_admin = false;
                    break;
                }
            }
        }
        else {
            user_manager.login();

            while(true){
                loadDatabase();
                choice = ShowMenu(userMenu());

                if(choice == 1)
                    user_manager.cur_user.printData();
                else if(choice == 2){
                    user_manager.withdrawMoney();
                    user_manager.updateDatabase();
                }
                else if(choice == 3){
                    user_manager.depositMoney();
                    user_manager.updateDatabase();
                }
                else
                    break;
            }
        }
        run();
    }

};

/// End Structs ///


/// Start Main ///

int main(){

    BankSystem bank;

    bank.run();

return 0;
}

/// End Main ///
