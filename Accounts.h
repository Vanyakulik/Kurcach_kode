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
    int role; //0-������ ,1 -�����

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
const int SIZE_ARR_OF_ACCOUNTS = 100; //��������� ��� ������� ������ ������� �  100 ���������
const string FILE_OF_ACCOUNTS = "Accounts.txt";// ���� � �����

void GlavnoeMenu() {

    cout << "�����������" << endl;
    cout << "1: �����" << endl;
    cout << "2: ������������������" << endl;
    cout << "3: �����" << endl;

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

    cout << "������� ��� ����� " << endl;
    cin >> user_login;

    cout << "������� ��� ������" << endl;
    cin >> user_password;
    string hashed_password = simpleHash(user_password); // ����������� ������

    // �������� ��������� ������
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
        cout << "�������� ���� � �������!" << endl;

        switch (existingRole) {
        case 0: // ������
            break;
        case 1: // �����
            break;
        default:
            cout << "����������� ����!" << endl;
            break;
        }
        return true;
    }
    else {
        cout << "�������� ����� ��� ������!" << endl;
        return false;
    }

}



void MenuAccounts() {

    cout << "���� ��� ������ � �������� �������� �������������" << endl;
    cout << "1: ��������" << endl;
    cout << "2: ��������" << endl;
    cout << "3: �������" << endl;
    cout << "4: �������������" << endl;
    cout << "5: �����" << endl;

}

void readFileAccounts(Account* arr_of_accounts, int& number_of_accounts)
{
    ifstream fin(FILE_OF_ACCOUNTS, ios::in); //������� ���� ��� ������

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
    fin.close(); // ������� �������� ����
}

void writeFileAccounts(Account* arr_of_accounts, int number_of_accounts)
{

    ofstream fout(FILE_OF_ACCOUNTS, ios::out);// ������� ���� ��� ������
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
    ofstream fout(FILE_OF_ACCOUNTS, ios::app);//������� ���� ��� ��������
    fout << endl;
    fout << new_account.login << " " << new_account.password << " " << new_account.role;

    fout.close();

}
void showAccounts(Account* arr_of_accounts, int number_of_acounts)
{
    cout << "������� ������� ������� ������������� " << endl;
    for (int i = 0; i < number_of_acounts; i++)
        cout << setw(4) << left << i + 1 <<
        setw(15) << left << arr_of_accounts[i].login <<
        setw(15) << left << arr_of_accounts[i].password <<
        setw(15) << left << arr_of_accounts[i].role << endl;
}

void addAccount(Account* arr_of_accounts, int& number_of_accounts)
{
    number_of_accounts++;
    cout << "������� ������ ����� ������" << endl;
    cout << "����� ";
    cin >> arr_of_accounts[number_of_accounts - 1].login;
    cout << "������ ";
    string password;
    cin >> password;
    arr_of_accounts[number_of_accounts - 1].password = simpleHash(password); // ����������� ������
    cout << "���� ";
    cin >> arr_of_accounts[number_of_accounts - 1].role;

    system("cls");
    cout << "����� ������ ��������� !" << endl;
    cout << endl;
}

void delAccount(Account* arr_of_accounts, int& number_of_accounts)
{
    cout << "������� ����� ��������� ������ ";
    int del_item;
    cin >> del_item;
    for (int i = del_item - 1; i < number_of_accounts; i++)
        arr_of_accounts[i] = arr_of_accounts[i + 1];
    number_of_accounts--;
    system("cls");
    cout << "������ ������� !" << endl;
    cout << endl;

}

void updateAccount(Account* arr_of_accounts, int number_of_accounts)
{
    cout << "������� ����� ������������� ������ ";
    int upd_item;
    cin >> upd_item;

    cout << "��������������� ������ ������� ������: " << endl;
    cout << "�����:  !";
    cin >> arr_of_accounts[upd_item - 1].login;
    cout << "������:  !";
    string password;
    cin >> password;
    arr_of_accounts[upd_item - 1].password = simpleHash(password); // ����������� ������
    cout << "����:  !";
    cin >> arr_of_accounts[upd_item - 1].role;
    system("cls");
    cout << "������ ��������������� !" << endl;
    cout << endl;
}


void Registration() {
    Account account;
    cout << "������� �����: ";
    cin >> account.login;
    cout << "������� ������: ";
    string password;
    cin >> password;
    account.password = simpleHash(password); // ����������� ������
    cout << "������� ���� (0 - �������, 1 - �����): ";
    cin >> account.role;

    // �������� �� ������������� ������
    std::ifstream checkFile;
    checkFile.open("Accounts.txt");
    std::string existingLogin, existingPassword;
    int existingRole;
    while (checkFile >> existingLogin >> existingPassword >> existingRole) {
        if (existingLogin == account.login) {
            cout << "����� ������� ��� ����������!" << endl;
            return; // ���� ����� ��� ����������, ������� �� �������
        }
    }
    checkFile.close();

    // ���� ������ ������ ��� ���, ��������� ����� �������
    std::ofstream file;
    file.open("Accounts.txt", std::ios::app);
    file << account.login << " " << account.password << " " << account.role << "\n";
    file.close();
}