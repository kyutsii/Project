#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
int button;
struct sold {
    string name;
    int quantity;
    string serialNumber;
};
void logout(){
    cout << "Вы вышли из аккаунта.";
}
void inputCheck(int& inputNumber, int lowerBound, int upperBound){
    while (!(cin >> inputNumber) || inputNumber < lowerBound || inputNumber > upperBound) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        if(lowerBound == 0 and upperBound == 0){
            cout << "Для выхода нажмите 0";
        }
        else {
            cout << "Произошла ошибка. Введите число от " << lowerBound << " до " << upperBound << endl;
        }
    }
}
void endMenu(){
   
    cout << endl << "0 - для выхода" << endl;
    inputCheck(button, 0, 0);
}
void allAppliences( ){
 ifstream file("appliances.txt"); 
    string line;

    while (getline(file, line)) { 
        cout << line <<endl; 
    }

    file.close();
}
void fileContent(const string& filename, string emptyFileMessage){
    string sales;
    ifstream ReadFile(filename);
    if(ReadFile.peek() == std::ifstream::traits_type::eof()){
        cout << emptyFileMessage << endl;
    }
    else{
        while(getline (ReadFile, sales)){
            cout << sales << endl;
        }
    }
    ReadFile.close();
}
void deleteElement(const string& filename){
    string sold;
    ifstream ReadFile(filename);
    if(ReadFile.peek() == std::ifstream::traits_type::eof()){
        cout << endl;
    }
    else{
        string DeleteOrder;
        cout << "Напишите название товара заказа который вы бы хотели удалить?>>";
        cin >> DeleteOrder;
        string LineDel;
        bool elementFound = false; 
        ifstream ReadFiledelOrder(filename);
        ofstream DeleteOrdertemp("deltempsold.txt");
        while(getline (ReadFiledelOrder, LineDel)){
            if(LineDel.find(DeleteOrder) != string::npos){
                elementFound = true; 
                continue;
            }
            else{
                DeleteOrdertemp << LineDel << endl;
            }
        }
        ReadFiledelOrder.close();
        DeleteOrdertemp.close();
        remove(filename.c_str());
        rename("deltempsold.txt", filename.c_str());
        if (elementFound) { 
            cout << "Ваш запрос принят." << endl; 
        } else { 
            cout << "Запас данного материала закончился, пожалуйста сделайте заказ на поставку!" << endl; 
        } 
    }
    ReadFile.close();
    endMenu();
}
void moveElement(const string& filename1, const string& filename2) { 
    string sales;
    ifstream ReadFile(filename1); 
    if(ReadFile.peek() == std::ifstream::traits_type::eof()){
        cout << endl;
    }
    else{
        cout << "Пожалуйста напишите название техники, которую вы бы хотели продать" << endl; 
        string elementToMove; 
        cin >> elementToMove; 
     
        string currentLineSell; 
        string currentLineSold; 
        bool elementFound = false; 
        ifstream sale(filename1); 
        ofstream saletemp("saletemp.txt"); 
        ifstream sold(filename2); 
        ofstream soldtemp("soldtemp.txt"); 
        while (getline(sold, currentLineSold)) { 
            soldtemp << currentLineSold << endl; 
        } 
        while (getline(sale, currentLineSell)) { 
            if (currentLineSell.find(elementToMove) != string::npos) { 
                elementFound = true; 
                soldtemp << currentLineSell << endl; 
            } else { 
                saletemp << currentLineSell << endl; 
            } 
        } 
        sale.close(); 
        saletemp.close(); 
        sold.close(); 
        soldtemp.close(); 
        remove(filename1.c_str()); 
        rename("saletemp.txt", filename1.c_str()); 
        remove(filename2.c_str()); 
        rename("soldtemp.txt", filename2.c_str()); 
     
        if (elementFound) { 
            cout << "Ваш запрос принят." << endl; 
        } else { 
            cout << "Запас данной техники закончился, пожалуйста сделайте заказ на поставку!" << endl; 
        } 
    }
    ReadFile.close();
    endMenu();
}
void maxMinAppliences(int menuNumber){
    ifstream ReadSold("sold.txt");
    if (ReadSold.peek() == ifstream::traits_type::eof()) {
        cout << "Нет заказов." << endl;
    } else {
        vector<sold> Sold;
        string name;
        int quantity;
        string serialNumber;
    
        while (ReadSold >> name >> quantity >> serialNumber) {
            sold Appliences;
            Appliences.name = name;
            Appliences.quantity = quantity;
            Appliences.serialNumber = serialNumber;
            Sold.push_back(Appliences);
        }
        if (Sold.empty()) {
            cout << "Нет никаких заказов." << endl;
            endMenu();
        }
        
        if (menuNumber == 3) {
            int MaterialWithMaxOrders = INT_MIN;
            for (auto now : Sold) {
                if (now.quantity > MaterialWithMaxOrders) {
                    MaterialWithMaxOrders = now.quantity;
                }
            }
            vector <string> appliencesWithMaxOrders;
            for (auto now : Sold) {
                if (now.quantity == MaterialWithMaxOrders) {
                    appliencesWithMaxOrders.push_back(now.name);
                }
            }
            cout << "Результаты: ";
            for (auto now : appliencesWithMaxOrders) {
                cout << now << endl;
            }
        }
        else if (menuNumber == 4) {
            int MaterialWithMinOrders = INT_MAX;
            for (auto now : Sold) {
                if (now.quantity < MaterialWithMinOrders) {
                    MaterialWithMinOrders = now.quantity;
                }
            }
            vector <string> AppliencesWithMinOrders;
            for (auto now : Sold) {
                if (now.quantity == MaterialWithMinOrders) {
                    AppliencesWithMinOrders.push_back(now.name);
                }
            }
            cout << "Результаты:  ";
            for (auto now : AppliencesWithMinOrders) {
                cout << now << endl;
            }
        }
    }
    ReadSold.close();
    endMenu();
}
void salaryCounter(const string & filename, string emptyFileMessage){
    int stake = 1000;
    string currentLine;
    ifstream ReadFile(filename);
    if (ReadFile.peek() == ifstream::traits_type::eof()) {
        cout << emptyFileMessage << endl;
    } else {
        while(getline (ReadFile, currentLine)){
            cout << currentLine << " - " << stake << "с" << endl;
        }
        int count = 0;
        string lineCount;
        ifstream ReadDelivered(filename);
        while(getline(ReadDelivered, lineCount)){
            count++;
        }
        cout << "Ваш заработок: " << count * stake << "сом";
        ReadDelivered.close();
    }
    ReadFile.close();
}
void searchFromFile(const string& filename){
    int subMenuNumber;
    string nameSearch, searchSerialNumber;
    while(true){
        cout << "Выберите: каким способом хотите искать:" << endl << "1.По названию" << endl << "2.По номеру" << endl;
        inputCheck(subMenuNumber, 1, 2);
        int symbol = 0;
        if(subMenuNumber == 1){
            cout << "Напишите название техники для поиска:";
            cin >> nameSearch;
            cout << "Результаты поиска:" << endl;
            ifstream ReadFile(filename);
            if (ReadFile.peek() == ifstream::traits_type::eof()) {
                cout << "Нет техники для продажи." << endl;
                break;
            }
            else {
                string currentLine;
                while (getline(ReadFile, currentLine)) {
                    if (currentLine.find(nameSearch) != string::npos) {
                        symbol++;
                        cout << currentLine << endl;
                    }
                }
    
                if(symbol != 0) {
                    cout << endl << "0 - для выхода" << endl;
                    inputCheck(button, 0, 0);
                    break;
                }
                else if(symbol == 0){
                    cout << "Не удалось найти товар " << endl;
                    cout << "Попробуйте ввести заново";
                }
            }
            cout << endl << "0 - для выхода" << endl;
            inputCheck(button, 0, 0);
            ReadFile.close();
        }
        else if(subMenuNumber == 2){
            symbol = 0;
            cout << endl << "Напишите номер для поиска:";
            searchSerialNumber:
            cin >> searchSerialNumber;
            cout << "Результаты поиска:" << endl;
            string currentLine;
            ifstream ReadFile("sales.txt");
            if(ReadFile.peek() == std::ifstream::traits_type::eof()){
                cout << "Нет товаров для продажи." << endl;
                break;
            }
            else{
                while (getline(ReadFile, currentLine)) {
                    if (currentLine.find(searchSerialNumber) != string::npos) {
                        symbol++;
                        cout << currentLine << endl;
                    }
                }
                
                
                if(symbol != 0){
                    cout << endl << "0 - для выхода" << endl;
                    inputCheck(button, 0, 0);
                    break;
                }
                else if(symbol == 0){
                    cout << "Не удалось найти товар " << endl;
                    cout << "Попробуйте  заново";
                    goto searchSerialNumber;
                }
            }
            cout << endl << "0 - для выхода" << endl;
            inputCheck(button, 0, 0);
            ReadFile.close();
        }
    }
}
void AppliencesNumber(const string& filename, string emptyFileMessage, string upperBound){
    int count = 0;
        string currentLine;
        ifstream ReadDelivered(filename);
        if (ReadDelivered.peek() == ifstream::traits_type::eof()) {
            cout << emptyFileMessage << endl;
        }
        else {
            while(getline(ReadDelivered, currentLine)){
                count++;
            }
            cout << "Количество " << upperBound << " техники: ";
            cout << count;
        }
        ReadDelivered.close();
}
void directorMenu(){
    int action;
    cout << "1. Show the list of all household appliances" << endl;
    cout << "2. Show the total count of household appliances" << endl;
    cout << "3. Show the household appliance with the maximum count" << endl;
    cout << "4. Show the household appliance with the minimum count" << endl;
    cout << "5. Exit" << endl;
    cin >> action;
    switch(action){
        case 1:
        allAppliences();
        endMenu();
        break;
        case 2:
        AppliencesNumber("material.number","No appliances.", "missing");
        endMenu();
        break;
        case 3:
        case 4:
        maxMinAppliences(action);
        endMenu();
        break;
        case 5:
        logout();
        break;
        default:
        cout << "no such option";
        
    }
}
void menuWorker(){
    int action;
    cout << "1. Show the full list of available appliances" << endl;
    cout << "2. Search for an appliance" << endl;
    cout << "3. Show sales report" << endl << "4. Make a sale" << endl;
    cout << "5. Order missing appliance" << endl;
    cout << "6. Delete an order" << endl;
    cout << "7. logout" << endl;
    cin >> action;
    switch(action) { 
        case 1: 
        fileContent("sales.txt", "No appliance for sale"); 
        endMenu(); 
        break; 
        case 2: 
        searchFromFile("sales.txt"); 
         break; 
         case 3: 
        fileContent("sold.txt", "No sold items."); 
        endMenu(); 
        break; 
        case 4: 
       fileContent("sales.txt", "No appliance for sale"); 
       moveElement("sales.txt", "sold.txt"); 
       break; 
       case 5:
       fileContent("noappliences.txt", "No out-of-stock items.");  
       moveElement("noappliences.txt", "need_appliences.txt"); 
       break; 
       case 6: 
       fileContent("sold.txt", "No orders."); 
       deleteElement("sold.txt"); 
       break; 
       case 7: 
        logout();
       break; 
       default: 
       cout <<"no such option";
       break; 
    }
    
}
void deliverymenu(){
    int action;
    cout << "1. Show list of materials for delivery";
    cout << "2. Show delivered orders";
    cout << "3. Deliver an order";
    cout << "4. Show the amount of delivered equipment";
    cout << "5. Show the amount of ordered equipment";
    cout << "6. Show my earnings";
    cout << "7. logout";
      cin >> action;
    switch(action) { 
        case 1: 
    cout << "If finished, press 0. ";
    fileContent("sold.txt", "No sold items");
    endMenu(); 
    break; 
    case 2: 
    fileContent("delivered.txt", "No delivered items."); 
     endMenu(); 
     break; 
   case 3: 
     fileContent("sold.txt", "No sold items"); 
      moveElement("sold.txt", "delivered.txt"); 
      break; 
    case 4: 
     AppliencesNumber("delivered.txt", "No items delivered.", "delivered"); 
    endMenu(); 
      break; 
     case 5: 
      AppliencesNumber("sold.txt", "No items sold.", "sold"); 
     endMenu(); 
       break; 
     case 6: 
     salaryCounter("delivered.txt", "You have no items delivered"); 
     endMenu(); 
     break; 
     case 7: 
     logout();
     break; 
     default: 
     cout << "no such option";
      break; 
      }
}
void Director(){
   
    string login = "dir123";
    string password = "dir321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
            cout << "you are entered" << endl;
            directorMenu();
    }else{
        while (enteredLogin != login or enteredPassword != password){
            cout << " try again"<< endl;
            cin >> enteredLogin;
            cin >> enteredPassword;
        }
    }
}
void Worker(){
    string login = "work123";
    string password = "work321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
            cout << "you are entered" << endl;
            menuWorker();
    }else{
        while (enteredLogin != login or enteredPassword != password){
            cout << " try again"<< endl;
            cin >> enteredLogin;
            cin >> enteredPassword;
        }
    }
}
void Delivery(){
    string login = "deliv123";
    string password = "deliv321";
    string enteredLogin;
    string enteredPassword;
    cout << "write your login and password" << endl;
    cin >>enteredLogin;
    cin >> enteredPassword;
    if (enteredLogin  == login && enteredPassword == password){
             deliverymenu();
            
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
    cout << " Choose your account: 1(Director), 2(Worker), 3(Delivery)?"<< endl;
    cin >> account;
    switch (account){
        case 1:
            Director();
            break;
        case 2:
            Worker();
            break;
        case 3:
            Delivery() ;
            break;
        default :
            cout << " no account";
    }

    return 0;
}