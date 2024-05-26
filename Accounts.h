#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include<Windows.h>

using namespace std;

struct Account {
    string login;
    string password;
    int role; //0-кассир ,1 -админ

};

void MenuTickets();
void Registration();
void GlavnoeMenu();
bool login();
void MenuAccounts();
void writeFileAccounts(Account* arr_of_accounts, int number_of_accounts);
void writeEndFileAccounts(Account new_account);
void readFileAccounts(Account* arr_of_accounts, int& number_of_accounts);
void showAccounts(Account* arr_of_accounts, int number_of_accounts);
void addAccount(Account* arr_of_accounts, int& number_of_accounts);
void delAccount(Account* arr_of_accounts, int& number_of_accounts);
void updateAccount(Account* arr_of_accounts, int number_of_accounts);
string simpleHash(const string& input);

Account current_user;
const int SIZE_ARR_OF_ACCOUNTS = 100; //константа для размера нашего массива в  100 элементов
const string FILE_OF_ACCOUNTS = "Accounts.txt";// ПУТЬ К ФАЙЛУ

void GlavnoeMenu() {

    cout << "Авторизация" << endl;
    cout << "1: войти" << endl;
    cout << "2: Зарегистрироваться" << endl;
    cout << "3: выход" << endl;

}

string simpleHash(const string& input) {
    unsigned long hash = 5381;
    int c;
    for (char i : input) {
        c = i;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return to_string(hash);
}



bool login() {
    string user_login;
    string user_password;

    cout << "Введите ваш логин " << endl;
    cin >> user_login;

    cout << "Введите ваш пароль" << endl;
    cin >> user_password;
    string hashed_password = simpleHash(user_password); // Хеширование пароля

    // Проверка введенных данных
    ifstream file("Accounts.txt");
    string existingLogin, existingPassword;
    int existingRole;
    bool found = false;
    while (file >> existingLogin >> existingPassword >> existingRole) {
        if (existingLogin == user_login && existingPassword == hashed_password) {
            found = true;
            current_user.login = existingLogin;
            current_user.password = existingPassword;
            current_user.role = existingRole;
            break;
        }
    }
    file.close();

    if (found) {
        cout << "Успешный вход в систему!" << endl;

        switch (existingRole) {
        case 0: // кассир
            break;
        case 1: // админ
            break;
        default:
            cout << "Неизвестная роль!" << endl;
            break;
        }
        return true;
    }
    else {
        cout << "Неверный логин или пароль!" << endl;
        return false;
    }

}



void MenuAccounts() {

    cout << "Меню для работы с учётными записями пользователей" << endl;
    cout << "1: показать" << endl;
    cout << "2: добавить" << endl;
    cout << "3: удалить" << endl;
    cout << "4: редактировать" << endl;
    cout << "5: выход" << endl;

}

void readFileAccounts(Account* arr_of_accounts, int& number_of_accounts)
{
    ifstream fin(FILE_OF_ACCOUNTS, ios::in); //открыли файл для чтения

    if (!fin.is_open())
    {
        cout << "Fatal error!" << FILE_OF_ACCOUNTS << endl;
    }
    else
    {
        number_of_accounts = 0;
        while (!fin.eof())
        {
            fin >> arr_of_accounts[number_of_accounts].login >> arr_of_accounts[number_of_accounts].password >> arr_of_accounts[number_of_accounts].role;
            number_of_accounts++;
        }
    }
    fin.close(); // закрыли открытый файл
}

void writeFileAccounts(Account* arr_of_accounts, int number_of_accounts)
{

    ofstream fout(FILE_OF_ACCOUNTS, ios::out);// Открыли файл для записи
    for (int i = 0; i < number_of_accounts; i++)
    {
        if (i < number_of_accounts - 1)
            fout << arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " << arr_of_accounts[i].role << endl;
        else
            fout << arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " << arr_of_accounts[i].role;

    }
    fout.close();
}
void writeEndFileAccounts(Account new_account)
{
    ofstream fout(FILE_OF_ACCOUNTS, ios::app);//открыли файл для дозаписи
    fout << endl;
    fout << new_account.login << " " << new_account.password << " " << new_account.role;

    fout.close();

}
void showAccounts(Account* arr_of_accounts, int number_of_acounts)
{
    cout << "Таблица учётных записей пользователей " << endl;
    for (int i = 0; i < number_of_acounts; i++)
        cout << setw(4) << left << i + 1 <<
        setw(15) << left << arr_of_accounts[i].login <<
        setw(15) << left << arr_of_accounts[i].password <<
        setw(15) << left << arr_of_accounts[i].role << endl;
}

void addAccount(Account* arr_of_accounts, int& number_of_accounts)
{
    number_of_accounts++;
    cout << "Введите данные новой учётки" << endl;
    cout << "Логин ";
    cin >> arr_of_accounts[number_of_accounts - 1].login;
    cout << "пароль ";
    string password;
    cin >> password;
    arr_of_accounts[number_of_accounts - 1].password = simpleHash(password); // Хеширование пароля
    cout << "Роль ";
    cin >> arr_of_accounts[number_of_accounts - 1].role;

    system("cls");
    cout << "Новая учётка добавлена !" << endl;
    cout << endl;
}

void delAccount(Account* arr_of_accounts, int& number_of_accounts)
{
    cout << "Введите номер удаляемой записи ";
    int del_item;
    cin >> del_item;
    for (int i = del_item - 1; i < number_of_accounts; i++)
        arr_of_accounts[i] = arr_of_accounts[i + 1];
    number_of_accounts--;
    system("cls");
    cout << "запись удалена !" << endl;
    cout << endl;

}

void updateAccount(Account* arr_of_accounts, int number_of_accounts)
{
    cout << "Введите номер редактируемой записи ";
    int upd_item;
    cin >> upd_item;

    cout << "отредактируейте данные учётной записи: " << endl;
    cout << "логин:  !";
    cin >> arr_of_accounts[upd_item - 1].login;
    cout << "Пароль:  !";
    string password;
    cin >> password;
    arr_of_accounts[upd_item - 1].password = simpleHash(password); // Хеширование пароля
    cout << "роль:  !";
    cin >> arr_of_accounts[upd_item - 1].role;
    system("cls");
    cout << "запись отредактирована !" << endl;
    cout << endl;
}


void Registration() {
    Account account;
    cout << "Введите логин: ";
    cin >> account.login;
    cout << "Введите пароль: ";
    string password;
    cin >> password;
    account.password = simpleHash(password); // Хеширование пароля
    cout << "Введите роль (0 - студент, 1 - админ): ";
    cin >> account.role;

    // Проверка на существование логина
    std::ifstream checkFile;
    checkFile.open("Accounts.txt");
    std::string existingLogin, existingPassword;
    int existingRole;
    while (checkFile >> existingLogin >> existingPassword >> existingRole) {
        if (existingLogin == account.login) {
            cout << "Такой аккаунт уже существует!" << endl;
            return; // Если логин уже существует, выходим из функции
        }
    }
    checkFile.close();

    // Если такого логина еще нет, добавляем новый аккаунт
    std::ofstream file;
    file.open("Accounts.txt", std::ios::app);
    file << account.login << " " << account.password << " " << account.role << "\n";
    file.close();
}