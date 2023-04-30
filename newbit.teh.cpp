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
void addAppliance() {
    cout <<"fnd";
// string name, serialNumber;
// int quantity;
// float price;
// cout << "Enter the name of household appliances: "<<  endl;;
// cin >> name;
// cout << "Enter the series number of household appliances: " << endl;
// cin >> serialNumber;
// cout << "Enter the quantity of household appliances:" << endl;
// cin >> quantity;
// cout << "Enter the price of household appliances: ";
// cin >> price;
// fstream appliancesFile("appliances.txt", fstream::out | fstream::app);
// if (!appliancesFile.is_open()) {
//     cout << "Error opening file!" << endl;
//      return;
//  }
// appliancesFile << name << " " << serialNumber << " " << quantity << " " << price << endl;
// appliancesFile.close();
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
    cout << endl << "0 - К главному меню" << endl;
    inputCheck(button, 0, 0);
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
void logout(){
    cout << "Вы вышли из аккаунта.";
}
void fileContent(const string& filename, string emptyFileMessage){
    string sales;
    ifstream ReadFile(filename);
    if(ReadFile.peek() == std::ifstream::traits_type::eof()){ 
        // Метод peek() возвращает следующий символ в потоке, не удаляя его из потока. Если метод peek() возвращает значение traits_type::eof(), то это означает, что достигнут конец файла и файл пуст.
        // eof() возвращает значение true, если при чтении файла дошли до его конца, и false в противном случае.
        cout << emptyFileMessage << endl;
    }
    else{
        while(getline (ReadFile, sales)){
            cout << sales << endl;
        }
    }
    ReadFile.close();
}
void searchFromFile(const string& filename){
    int subMenuNumber;
    string nameSearch, searchSerialNumber;
    while(true){
        cout << "Выберите: каким способом хотите искать:" << endl << "1.По названию" << endl << "2.По дате" << endl;
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
    cin >> action;
    cout << "1. Показать список всех бытовой техники (Показывает список бытовой техники, который есть в магазине";
    cout <<"2. Показать количество бытовой техники (Показывает количество бытовой техники по категории";
    cout << "3. Показать бытовую технику с самым максимальным количеством";
    cout<< "4. Показать бытовую технику с самым минимальным количеством";
    cout << "5. Показать отчет по закупкам об бытовой техники";
    cout << "6. Выход ( Выходит из программы)";
}
void menuWorker();
 inputCheck(action, 1, 8);
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
      cout << "Выбор меню:>>";
    inputCheck(menuNumber, 1, 8);
    switch(menuNumber) { 
        case 1: 
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
    showInstructions();  
     break; 
     case 8: 
     logout;
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