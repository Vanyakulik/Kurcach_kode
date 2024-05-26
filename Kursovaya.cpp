#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<string>
#include<Windows.h>
#include "Tickets.h"
#include"Accounts.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    bool is_logged_in = false;
    Account arr_of_accounts[SIZE_ARR_OF_ACCOUNTS]; // массив для структуры состоящей из 100 элементов
    int number_of_accounts = 0;

    readFileAccounts(arr_of_accounts, number_of_accounts);//чтение из файла в массив 
    
    

    while (!is_logged_in) // цикл выполняется, пока пользователь не вошел в систему
    {
        GlavnoeMenu();
        int item;
        cin >> item;

        system("cls");
        switch (item){

        case 1:
            is_logged_in = login(); // если функция login возвращает true, то пользователь вошел в систему
            break;
        case 2:
            Registration();
            break;
        case 3: cout << "Выход из программы..." << endl;
            return 0; // выход из программы
        }
    }
    

    while(current_user.role == 1 ) { // Если роль - админ
        int item;
        cout << "1:Работа с аккаунтами" << endl << "2:Работа с билетами"<< endl<< "3:Выход"<< endl;
        cin >> item;
        system("cls");
        
            switch (item) {
            case 1: MenuAccounts();
                int menu;
                cin >> menu;
                switch (menu) {
                case 1: showAccounts(arr_of_accounts, number_of_accounts);
                    break;
                case 2: addAccount(arr_of_accounts, number_of_accounts);
                    break;
                case 3: delAccount(arr_of_accounts, number_of_accounts);
                    break;
                case 4: updateAccount(arr_of_accounts, number_of_accounts);
                case 5: 
                    break;
                }
                writeFileAccounts(arr_of_accounts, number_of_accounts);
                break;
            case 2: MenuTickets();
                break;
            case 3: cout << "Выход из программы..." << endl;
                return(0);
                break;
            default: cout << "Неверный выбор!" << endl;
                break;
            }
             
        
    }
    while (current_user.role == 0) { // Если роль - кассир
        int item;
        cout << "1:Работа с билетами" << endl << "2:Выход" << endl;
        cin >> item;
        system("cls");
        switch (item) {
        case 1:  MenuTickets();
            break;
        case 2:cout << "Выход из программы..." << endl;
            return(0);
            break;
        default: std::cout << "Неверный выбор!" << std::endl;
            break;
        }
        
    }
    
}

