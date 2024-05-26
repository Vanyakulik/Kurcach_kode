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
        std::cout << "Ошибка открытия файла!" << std::endl;
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

    std::cout << "Таблица билетов " << std::endl;
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
    std::cout << "Таблица билетов " << std::endl;
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
    std::cout << "Введите данные нового билета" << std::endl;
    std::cout << "ID билета: ";
    std::cin >> new_ticket.ticketid;
    std::cout << "ФИО: ";
    std::cin >> new_ticket.surname;
    std::cin >> new_ticket.name;
    std::cin >> new_ticket.patronymic;
    std::cout << "Пункт отправления: ";
    std::cin >> new_ticket.departure_point;
    std::cout << "Пункт прибытия: ";
    std::cin >> new_ticket.arrival_point;
    std::cout << "Дата: ";
    std::cin >> new_ticket.date;
    tickets.push_back(new_ticket);
    saveTickets();  // Сохраняем изменения в файл
    std::cout << "Новый билет добавлен!" << std::endl;
}

void delTicket() {
    std::cout << "Введите номер удаляемого билета: ";
    int del_item;
    std::cin >> del_item;
    tickets.erase(tickets.begin() + del_item - 1);
    std::cout << "Билет удален!" << std::endl;
}

void updateTicket() {
    std::cout << "Введите номер редактируемого билета: ";
    int upd_item;
    std::cin >> upd_item;
    std::cout << "Введите новые данные билета: " << std::endl;
    std::cout << "ID билета: ";
    std::cin >> tickets[upd_item - 1].ticketid;
    std::cout << "ФИО: ";
    std::cin >> tickets[upd_item - 1].surname;
    std::cin >> tickets[upd_item - 1].name;
    std::cin >> tickets[upd_item - 1].patronymic;
    std::cout << "Пункт отправления: ";
    std::cin >> tickets[upd_item - 1].departure_point;
    std::cout << "Пункт прибытия: ";
    std::cin >> tickets[upd_item - 1].arrival_point;
    std::cout << "Дата: ";
    std::cin >> tickets[upd_item - 1].date;
    saveTickets();  // Сохраняем изменения в файл
    std::cout << "Билет обновлен!" << std::endl;
}



// Функция для сравнения двух билетов по месту отправления
bool compareByDeparturePoint(const Ticket& a, const Ticket& b) {
    return a.departure_point < b.departure_point;
}

// Функция partition для быстрой сортировки
int partition(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&)) {
    Ticket pivot = tickets[high]; // выбираем последний элемент в качестве опорного
    int i = (low - 1); // индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (compare(tickets[j], pivot)) {
            i++; // увеличиваем индекс меньшего элемента
            std::swap(tickets[i], tickets[j]);
        }
    }
    std::swap(tickets[i + 1], tickets[high]);
    return (i + 1);
}

// Быстрая сортировка
void quickSort(std::vector<Ticket>& tickets, int low, int high, bool (*compare)(const Ticket&, const Ticket&)) {
    if (low < high) {
        int pi = partition(tickets, low, high, compare);
        quickSort(tickets, low, pi - 1, compare);
        quickSort(tickets, pi + 1, high, compare);
    }
}

// Функция для сравнения по фамилии
bool compareByName(const Ticket& a, const Ticket& b) {
    return a.name < b.name;
}

// Функция для сравнения по фамилии
bool compareBySurname(const Ticket& a, const Ticket& b) {
    return a.surname < b.surname;
}

// Функция для сравнения по отчеству
bool compareByPatronymic(const Ticket& a, const Ticket& b) {
    return a.patronymic < b.patronymic;
}

// Функция для сравнения по месту прибытия
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
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchBySurname(const std::string& surname) {
    for (const auto& ticket : tickets) {
        if (ticket.surname == surname) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByName(const std::string& name) {
    for (const auto& ticket : tickets) {
        if (ticket.name == name) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByPatronymic(const std::string& patronymic) {
    for (const auto& ticket : tickets) {
        if (ticket.patronymic == patronymic) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByDeparturePoint(const std::string& departure_point) {
    for (const auto& ticket : tickets) {
        if (ticket.departure_point == departure_point) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByArrivalPoint(const std::string& arrival_point) {
    for (const auto& ticket : tickets) {
        if (ticket.arrival_point == arrival_point) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}

void searchByDate(const std::string& date) {
    for (const auto& ticket : tickets) {
        if (ticket.date == date) {
            // Выводим информацию о билете
            std::cout << ticket.ticketid << " " << ticket.surname << " " << ticket.name << " " << ticket.patronymic << " " << ticket.departure_point << " " << ticket.arrival_point << " " << ticket.date << "\n";
        }
    }
}
void searchTicket() {
    int search_choice;
    std::cout << "Выберите параметр для поиска билета:" << std::endl;
    std::cout << "1: Поиск по ID билета" << std::endl;
    std::cout << "2: Поиск по фамилии" << std::endl;
    std::cout << "3: Поиск по имени" << std::endl;
    std::cout << "4: Поиск по отчеству" << std::endl;
    std::cout << "5: Поиск по пункту отправления" << std::endl;
    std::cout << "6: Поиск по пункту прибытия" << std::endl;
    std::cout << "7: Поиск по дате" << std::endl;
    std::cout << "8: Выход" << std::endl;
    std::cin >> search_choice;

    switch (search_choice) {
    case 1: {
        int id;
        std::cout << "Введите ID билета: ";
        std::cin >> id;
        searchByTicketId(id);
        break;
    }
    case 2: {
        std::string surname;
        std::cout << "Введите фамилию: ";
        std::cin >> surname;
        searchBySurname(surname);
        break;
    }
    case 3: {
        std::string name;
        std::cout << "Введите имя: ";
        std::cin >> name;
        searchByName(name);
        break;
    }
    case 4: {
        std::string patronymic;
        std::cout << "Введите отчество: ";
        std::cin >> patronymic;
        searchByPatronymic(patronymic);
        break;
    }
    case 5: {
        std::string departure_point;
        std::cout << "Введите пункт отправления: ";
        std::cin >> departure_point;
        searchByDeparturePoint(departure_point);
        break;
    }
    case 6: {
        std::string arrival_point;
        std::cout << "Введите пункт прибытия: ";
        std::cin >> arrival_point;
        searchByArrivalPoint(arrival_point);
        break;
    }
    case 7: {
        std::string date;
        std::cout << "Введите дату: ";
        std::cin >> date;
        searchByDate(date);
        break;
    }
    case 8:
        std::cout << "Выход из меню поиска..." << std::endl;
        break;
    default:
        std::cout << "Неверный выбор!" << std::endl;
        break;
    }
}

void MenuTickets() {
    loadTickets();
    int choice;
    do {
        std::cout << "Меню для работы с билетами" << std::endl;
        std::cout << "1: показать" << std::endl;
        std::cout << "2: добавить" << std::endl;
        std::cout << "3: удалить" << std::endl;
        std::cout << "4: редактировать" << std::endl;
        std::cout << "5: сортировать" << std::endl;
        std::cout << "6: искать" << std::endl;
        std::cout << "7: выход" << std::endl;
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
            std::cout << "Выберите тип сортировки:" << std::endl;
            std::cout << "1: сортировать по фамилии (шейкерная сортировка)" << std::endl;
            std::cout << "2: сортировать по имени (быстрая сортировка)" << std::endl;
            std::cout << "3: сортировать по отчеству (шейкерная сортировка)" << std::endl;
            std::cout << "4: сортировать по месту отправления (быстрая сортировка)" << std::endl;
            std::cout << "5: сортировать по месту прибытия (шейкерная сортировка)" << std::endl;
            std::cin >> sort_choice;

            switch (sort_choice) {
            case 1:
                cocktailSort(tickets, compareBySurname);
                std::cout << "Билеты отсортированы по фамилии!" << std::endl;
                break;
            case 2:
                quickSort(tickets, 0, tickets.size() - 1, compareByName);
                std::cout << "Билеты отсортированы по имени!" << std::endl;
                break;
            case 3:
                cocktailSort(tickets, compareByPatronymic);
                std::cout << "Билеты отсортированы по отчеству!" << std::endl;
                break;
            case 4:
                quickSort(tickets, 0, tickets.size() - 1, compareByDeparturePoint);
                std::cout << "Билеты отсортированы по месту отправления!" << std::endl;
                break;
            case 5:
                cocktailSort(tickets, compareByArrival);
                std::cout << "Билеты отсортированы по месту прибытия!" << std::endl;
                break;
            default:
                std::cout << "Неверный выбор сортировки!" << std::endl;
                break;
            }
            break;
        case 6:
            searchTicket();
            break;
        case 7:
            break;
        default:
            std::cout << "Неверный выбор!" << std::endl;
            break;
        }
    } while (choice != 7);
}



