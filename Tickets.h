#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include<Windows.h>


struct Ticket {
    int ticketid;
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string departure_point;
    std::string arrival_point;
    std::string date;
};

void loadTickets();
void saveTickets();
void showTickets();
void showTicketsAdmin();
void addTicket();
void delTicket();
void updateTicket();
bool compareByDeparturePoint(const Ticket& a, const Ticket& b);
int partition(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&));
void quickSort(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&));
bool compareByName(const Ticket& a, const Ticket& b);
bool compareBySurname(const Ticket& a, const Ticket& b);
bool compareByPatronymic(const Ticket& a, const Ticket& b);
bool compareByArrival(const Ticket& a, const Ticket& b);
void cocktailSort(std::vector<Ticket>& tickets, bool (*compare)(const Ticket&, const Ticket&));
void searchByTicketId(int id);
void searchBySurname(const std::string& surname);
void searchByName(const std::string& name);
void searchByPatronymic(const std::string& patronymic);
void searchByDeparturePoint(const std::string& departure_point);
void searchByArrivalPoint(const std::string& arrival_point);
void searchByDate(const std::string& date);


std::vector<Ticket> tickets;


void loadTickets() {
    std::ifstream fin("Tickets.txt", std::ios::in);
    if (!fin.is_open()) {
        std::cout << "������ �������� �����!" << std::endl;
        return;
    }
    Ticket ticket;
    while (fin >> ticket.ticketid >> ticket.surname >> ticket.name >> ticket.patronymic >> ticket.departure_point >> ticket.arrival_point >> ticket.date) {
        tickets.push_back(ticket);
    }
    fin.close();
}

void saveTickets() {
    std::ofstream fout("Tickets.txt", std::ios::out);
    for (const auto& ticket : tickets) {
        fout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
    }
    fout.close();
}

void showTickets() {

    std::cout << "������� ������� " << std::endl;
    for (int i = 0; i < tickets.size(); i++)
        std::cout << std::setw(4) << std::left << i + 1 <<
        std::setw(15) << std::left << tickets[i].surname <<
        std::setw(15) << std::left << tickets[i].name <<
        std::setw(15) << std::left << tickets[i].patronymic <<
        std::setw(15) << std::left << tickets[i].departure_point <<
        std::setw(15) << std::left << tickets[i].arrival_point <<
        std::setw(15) << std::left << tickets[i].date << std::endl;
}
void showTicketsAdmin() {
    std::cout << "������� ������� " << std::endl;
    for (int i = 0; i < tickets.size(); i++)
        std::cout << std::setw(4) << std::left << i + 1 <<
        std::setw(15) << std::left << tickets[i].ticketid <<
        std::setw(15) << std::left << tickets[i].surname <<
        std::setw(15) << std::left << tickets[i].name <<
        std::setw(15) << std::left << tickets[i].patronymic <<
        std::setw(15) << std::left << tickets[i].departure_point <<
        std::setw(15) << std::left << tickets[i].arrival_point <<
        std::setw(15) << std::left << tickets[i].date << std::endl;
}

void addTicket() {
    Ticket new_ticket;
    std::cout << "������� ������ ������ ������" << std::endl;
    std::cout << "ID ������: ";
    std::cin >> new_ticket.ticketid;
    std::cout << "���: ";
    std::cin >> new_ticket.surname;
    std::cin >> new_ticket.name;
    std::cin >> new_ticket.patronymic;
    std::cout << "����� �����������: ";
    std::cin >> new_ticket.departure_point;
    std::cout << "����� ��������: ";
    std::cin >> new_ticket.arrival_point;
    std::cout << "����: ";
    std::cin >> new_ticket.date;
    tickets.push_back(new_ticket);
    saveTickets();  // ��������� ��������� � ����
    std::cout << "����� ����� ��������!" << std::endl;
}

void delTicket() {
    std::cout << "������� ����� ���������� ������: ";
    int del_item;
    std::cin >> del_item;
    tickets.erase(tickets.begin() + del_item - 1);
    std::cout << "����� ������!" << std::endl;
}

void updateTicket() {
    std::cout << "������� ����� �������������� ������: ";
    int upd_item;
    std::cin >> upd_item;
    std::cout << "������� ����� ������ ������: " << std::endl;
    std::cout << "ID ������: ";
    std::cin >> tickets[upd_item - 1].ticketid;
    std::cout << "���: ";
    std::cin >> tickets[upd_item - 1].surname;
    std::cin >> tickets[upd_item - 1].name;
    std::cin >> tickets[upd_item - 1].patronymic;
    std::cout << "����� �����������: ";
    std::cin >> tickets[upd_item - 1].departure_point;
    std::cout << "����� ��������: ";
    std::cin >> tickets[upd_item - 1].arrival_point;
    std::cout << "����: ";
    std::cin >> tickets[upd_item - 1].date;
    saveTickets();  // ��������� ��������� � ����
    std::cout << "����� ��������!" << std::endl;
}



// ������� ��� ��������� ���� ������� �� ����� �����������
bool compareByDeparturePoint(const Ticket& a, const Ticket& b) {
    return a.departure_point < b.departure_point;
}

// ������� partition ��� ������� ����������
int partition(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&)) {
    Ticket pivot = tickets[high]; // �������� ��������� ������� � �������� ��������
    int i = (low - 1); // ������ �������� ��������

    for (int j = low; j <= high - 1; j++) {
        // ���� ������� ������� ������ ��� ����� ��������
        if (compare(tickets[j], pivot)) {
            i++; // ����������� ������ �������� ��������
            std::swap(tickets[i], tickets[j]);
        }
    }
    std::swap(tickets[i + 1], tickets[high]);
    return (i + 1);
}

// ������� ����������
void quickSort(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&)) {
    if (low < high) {
        int pi = partition(tickets, low, high, compare);
        quickSort(tickets, low, pi - 1, compare);
        quickSort(tickets, pi + 1, high, compare);
    }
}

// ������� ��� ��������� �� �������
bool compareByName(const Ticket& a, const Ticket& b) {
    return a.name < b.name;
}

// ������� ��� ��������� �� �������
bool compareBySurname(const Ticket& a, const Ticket& b) {
    return a.surname < b.surname;
}

// ������� ��� ��������� �� ��������
bool compareByPatronymic(const Ticket& a, const Ticket& b) {
    return a.patronymic < b.patronymic;
}

// ������� ��� ��������� �� ����� ��������
bool compareByArrival(const Ticket& a, const Ticket& b) {
    return a.arrival_point < b.arrival_point;
}

void cocktailSort(std::vector<Ticket>& tickets, bool (*compare)(const Ticket&, const Ticket&)) {
    bool swapped = true;
    int start = 0;
    int end = tickets.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (compare(tickets[i], tickets[i + 1])) {
                std::swap(tickets[i], tickets[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (compare(tickets[i], tickets[i + 1])) {
                std::swap(tickets[i], tickets[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}
void searchByTicketId(int id) {
    for (const auto& ticket : tickets) {
        if (ticket.ticketid == id) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchBySurname(const std::string& surname) {
    for (const auto& ticket : tickets) {
        if (ticket.surname == surname) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByName(const std::string& name) {
    for (const auto& ticket : tickets) {
        if (ticket.name == name) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByPatronymic(const std::string& patronymic) {
    for (const auto& ticket : tickets) {
        if (ticket.patronymic == patronymic) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByDeparturePoint(const std::string& departure_point) {
    for (const auto& ticket : tickets) {
        if (ticket.departure_point == departure_point) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByArrivalPoint(const std::string& arrival_point) {
    for (const auto& ticket : tickets) {
        if (ticket.arrival_point == arrival_point) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByDate(const std::string& date) {
    for (const auto& ticket : tickets) {
        if (ticket.date == date) {
            // ������� ���������� � ������
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}
void searchTicket() {
    int search_choice;
    std::cout << "�������� �������� ��� ������ ������:" << std::endl;
    std::cout << "1: ����� �� ID ������" << std::endl;
    std::cout << "2: ����� �� �������" << std::endl;
    std::cout << "3: ����� �� �����" << std::endl;
    std::cout << "4: ����� �� ��������" << std::endl;
    std::cout << "5: ����� �� ������ �����������" << std::endl;
    std::cout << "6: ����� �� ������ ��������" << std::endl;
    std::cout << "7: ����� �� ����" << std::endl;
    std::cout << "8: �����" << std::endl;
    std::cin >> search_choice;

    switch (search_choice) {
    case 1: {
        int id;
        std::cout << "������� ID ������: ";
        std::cin >> id;
        searchByTicketId(id);
        break;
    }
    case 2: {
        std::string surname;
        std::cout << "������� �������: ";
        std::cin >> surname;
        searchBySurname(surname);
        break;
    }
    case 3: {
        std::string name;
        std::cout << "������� ���: ";
        std::cin >> name;
        searchByName(name);
        break;
    }
    case 4: {
        std::string patronymic;
        std::cout << "������� ��������: ";
        std::cin >> patronymic;
        searchByPatronymic(patronymic);
        break;
    }
    case 5: {
        std::string departure_point;
        std::cout << "������� ����� �����������: ";
        std::cin >> departure_point;
        searchByDeparturePoint(departure_point);
        break;
    }
    case 6: {
        std::string arrival_point;
        std::cout << "������� ����� ��������: ";
        std::cin >> arrival_point;
        searchByArrivalPoint(arrival_point);
        break;
    }
    case 7: {
        std::string date;
        std::cout << "������� ����: ";
        std::cin >> date;
        searchByDate(date);
        break;
    }
    case 8:
        std::cout << "����� �� ���� ������..." << std::endl;
        break;
    default:
        std::cout << "�������� �����!" << std::endl;
        break;
    }
}

void MenuTickets() {
    loadTickets();
    int choice;
    do {
        std::cout << "���� ��� ������ � ��������" << std::endl;
        std::cout << "1: ��������" << std::endl;
        std::cout << "2: ��������" << std::endl;
        std::cout << "3: �������" << std::endl;
        std::cout << "4: �������������" << std::endl;
        std::cout << "5: �����������" << std::endl;
        std::cout << "6: ������" << std::endl;
        std::cout << "7: �����" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            showTickets();
            break;
        case 2:
            addTicket();
            break;
        case 3:
            delTicket();
            break;
        case 4:
            updateTicket();
            break;
        case 5:
            int sort_choice;
            std::cout << "�������� ��� ����������:" << std::endl;
            std::cout << "1: ����������� �� ������� (��������� ����������)" << std::endl;
            std::cout << "2: ����������� �� ����� (������� ����������)" << std::endl;
            std::cout << "3: ����������� �� �������� (��������� ����������)" << std::endl;
            std::cout << "4: ����������� �� ����� ����������� (������� ����������)" << std::endl;
            std::cout << "5: ����������� �� ����� �������� (��������� ����������)" << std::endl;
            std::cin >> sort_choice;

            switch (sort_choice) {
            case 1:
                cocktailSort(tickets, compareBySurname);
                std::cout << "������ ������������� �� �������!" << std::endl;
                break;
            case 2:
                quickSort(tickets, 0, tickets.size() - 1, compareByName);
                std::cout << "������ ������������� �� �����!" << std::endl;
                break;
            case 3:
                cocktailSort(tickets, compareByPatronymic);
                std::cout << "������ ������������� �� ��������!" << std::endl;
                break;
            case 4:
                quickSort(tickets, 0, tickets.size() - 1, compareByDeparturePoint);
                std::cout << "������ ������������� �� ����� �����������!" << std::endl;
                break;
            case 5:
                cocktailSort(tickets, compareByArrival);
                std::cout << "������ ������������� �� ����� ��������!" << std::endl;
                break;
            default:
                std::cout << "�������� ����� ����������!" << std::endl;
                break;
            }
            break;
        case 6:
            searchTicket();
            break;
        case 7:
            break;
        default:
            std::cout << "�������� �����!" << std::endl;
            break;
        }
    } while (choice != 7);
}



