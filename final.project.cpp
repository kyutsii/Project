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
        cin.clear(); // clear the error flags
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the input
        if(lowerBound == 0 and upperBound == 0){
            cout << "Для выхода в главное меню введите 0:>>";
        }
        else {
            cout << "Произошла ошибка. Введите число от " << lowerBound << " до " << upperBound << endl;
        }
    }
}
void goToMenu(){
    int action;
    cin >> action;
    cout << endl << "0 - для выхода" << endl;
    inputCheck(button, 0, 0);
    if (action == 0){
         logout();
    }
   else{
       cout << endl;
   }
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

void showInstructions(){
    cout << "Инструкция:" << endl;
    fileContent("instructions.txt", " ");
    goToMenu();
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
    goToMenu();
}
void numberOfMaterials(const string& filename, string emptyFileMessage, string upperBound){
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
            cout << "Количество " << upperBound << " товаров: ";
            cout << count;
        }
        ReadDelivered.close();
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
    goToMenu();
}
void maxMinOfMaterials(int menuNumber){
    ifstream ReadSold("sold.txt");
    if (ReadSold.peek() == ifstream::traits_type::eof()) {
        cout << "Нет заказов." << endl;
    } else {
        vector<sold> Sold;
        string name;
        int quantity;
        string serialNumber;
    
        while (ReadSold >> name >> quantity >> serialNumber) {
            sold materials;
            materials.name = name;
            materials.quantity = quantity;
            materials.serialNumber = serialNumber;
            Sold.push_back(materials);
        }
        if (Sold.empty()) {
            cout << "Нет никаких заказов." << endl;
            goToMenu();
        }
        
        if (menuNumber == 3) {
            int MaterialWithMaxOrders = INT_MIN;
            for (auto now : Sold) {
                if (now.quantity > MaterialWithMaxOrders) {
                    MaterialWithMaxOrders = now.quantity;
                }
            }
            vector <string> MaterialsWithMaxOrders;
            for (auto now : Sold) {
                if (now.quantity == MaterialWithMaxOrders) {
                    MaterialsWithMaxOrders.push_back(now.name);
                }
            }
            cout << "Результаты: ";
            for (auto now : MaterialsWithMaxOrders) {
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
            vector <string> MaterialsWithMinOrders;
            for (auto now : Sold) {
                if (now.quantity == MaterialWithMinOrders) {
                    MaterialsWithMinOrders.push_back(now.name);
                }
            }
            cout << "Результаты:  ";
            for (auto now : MaterialsWithMinOrders) {
                cout << now << endl;
            }
        }
    }
    ReadSold.close();
    goToMenu();
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
        cout << "Ваш заработок: " << count * stake << "сомов";
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
            cout << "Напишите название материала для поиска:>>";
            cin >> nameSearch;
            cout << "Результаты поиска:" << endl;
            ifstream ReadFile(filename);
            if (ReadFile.peek() == std::ifstream::traits_type::eof()) {
                cout << "Нет товаров для продажи." << endl;
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
                    cout << endl << "0 - К главному меню" << endl;
                    inputCheck(button, 0, 0);
                    break;
                }
                else if(symbol == 0){
                    cout << "Не удалось найти товар " << endl;
                    cout << "Попробуйте ввести заново";
                }
            }
            cout << endl << "0 - К главному меню" << endl;
            inputCheck(button, 0, 0);
            ReadFile.close();
        }
        else if(subMenuNumber == 2){
            symbol = 0;
            cout << endl << "Напишите дату для поиска:>>";
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
                    cout << endl << "0 - К главному меню" << endl;
                    inputCheck(button, 0, 0);
                    break;
                }
                else if(symbol == 0){
                    cout << "Не удалось найти товар " << endl;
                    cout << "Попробуйте  заново:>>";
                    goto searchSerialNumber;
                }
            }
            cout << endl << "0 - К главному меню" << endl;
            inputCheck(button, 0, 0);
            ReadFile.close();
        }
    }
}
void DirectorAcc(){
    int action;
    
    cout << "1. Показать список всей бытовой техники ";
    cout <<"2. Показать количество бытовой техники ";
    cout << "3. Показать бытовую технику с самым максимальным количеством";
    cout<<  "4. Показать бытовую технику с самым минимальным количеством";
    cout << "5. Показать отчет по закупкам об бытовой техники";
    cout << "6. Выход ( Выходит из программы)";
    cin >> action;
    switch(action){
        case 1:
        
    }
}
void menuWorker(){
    int action;
    cin >> action;
    cout << " 1.Показать весь список материалов для продажи" << endl;
    cout <<"2.Искать материал" << endl;
    cout << "3.Показать отчет по продаже" << endl << "4.Выполнить продажу оборудований" << endl;
    cout << "5.Сделать заказ отсутствующего товара" << endl ;
    cout<< "6.Удалить заказ" << endl;
    cout << "7.Выход" << endl;
    switch(action) { 
        case 1: 
        fileContent("sales.txt", "Нет товаров для продажи."); 
        goToMenu(); 
        break; 
        case 2: 
        searchFromFile("sales.txt"); 
         break; 
         case 3: 
        fileContent("sold.txt", "Нет проданных товаров."); 
        goToMenu(); 
        break; 
        case 4: 
       fileContent("sales.txt", "Нет товаров для продажи."); 
       moveElement("sales.txt", "sold.txt"); 
       break; 
       case 5:
       fileContent("nomaterials.txt", "Нет отсутствующих товаров.");  
       moveElement("nomaterials.txt", "need_materials.txt"); 
       break; 
       case 6: 
       fileContent("sold.txt", "Нет заказов."); 
       deleteElement("sold.txt"); 
       break; 
       case 7: 
        showInstructions();
       break; 
       case 8: 
        logout();
       break; 
       default: 
       cout <<"no such option";
       break; 
    }
    
}
void deliverymenu(){
    int action;
     cout << "1.Показать список материалов для доставки";
      cout << "2.Показать доставленные заказы" ;
      cout << "3.Доставить заказ";
      cout << "4.количествотво доставленной техники";
      cout<< "5.Показать количество заказанной";
      cout << "6.Показать мой заработок" ;
      cout << "7.Выход";
      cin >> action;
    // inputCheck(menuNumber, 1, 8);
    switch(action) { 
        case 1: 
    cout << "если закончили нажмите 0 ";
    fileContent("sold.txt", "Нет проданных товаров.");
    goToMenu(); 
    break; 
    case 2: 
    fileContent("delivered.txt", "Нет доставленных товаров."); 
     goToMenu(); 
     break; 
   case 3: 
     fileContent("sold.txt", "Нет проданных товаров."); 
      moveElement("sold.txt", "delivered.txt"); 
      break; 
    case 4: 
     numberOfMaterials("delivered.txt", "Нет доставленных товаров.", "доставленнных"); 
    goToMenu(); 
      break; 
     case 5: 
      numberOfMaterials("sold.txt", "Нет проданных товаров.", "проданных"); 
     goToMenu(); 
       break; 
     case 6: 
     salaryCounter("delivered.txt", "У вас нет доставленных товаров."); 
     goToMenu(); 
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
            DirectorAcc();
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