#include <iostream>

using namespace std;
void yourAcc(){
    cout << "your acc";
}
void Dir(){
   
    string login = "dir123";
    string password = "dir321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
            cout << "you are entered" << endl;
    }else{
        while (enteredLogin != login or enteredPassword != password){
            cout << " try again"<< endl;
            cin >> enteredLogin;
            cin >> enteredPassword;
        }
    }
}
void Work(){
    string login = "work123";
    string password = "work321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
            cout << "you are entered" << endl;
    }else{
        while (enteredLogin != login or enteredPassword != password){
            cout << " try again"<< endl;
            cin >> enteredLogin;
            cin >> enteredPassword;
        }
    }
}
void Deliv(){
    string login = "deliv123";
    string password = "deliv321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
             yourAcc();
            
    }else{
        while (enteredLogin != login or enteredPassword != password){
            cout << " try again"<< endl;
            cin >> enteredLogin;
            cin >> enteredPassword;
        }
    }
}

int main()
{
    int account;
    cout << " 1 2 3?"<< endl;
    cin >> account;
    switch (account){
        case 1:
            Dir();
            break;
        case 2:
            Work();
            break;
        case 3:
            Deliv() ;
            break;
        default :
            cout << " no account";
    }

    return 0;
}