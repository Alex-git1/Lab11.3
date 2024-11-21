#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Friend {
    string surname;
    string name;
    string phoneNumber;
    int birthDay;
    int birthMonth;
    int birthYear;
};

void displayMenu();
string getFileName();
void createList(const string& filename);
void viewList(const string& filename);
void addFriend(const string& filename);
void findFriendsByMonth(const string& filename, int month);
bool parseDate(const string& dateStr, int& day, int& month, int& year);
bool isValidDate(int day, int month, int year);

int main() {
    SetConsoleCP(1251);  
    SetConsoleOutputCP(1251);
    string filename = getFileName();
    int choice;

    do {
        displayMenu();
        cout << "Оберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createList(filename);
            break;
        case 2:
            viewList(filename);
            break;
        case 3:
            addFriend(filename);
            break;
        case 4: {
            int month;
            cout << "Введіть номер місяця (1-12): ";
            while (!(cin >> month) || month < 1 || month > 12) {
                cout << "Невірний номер місяця. Спробуйте ще раз: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            findFriendsByMonth(filename, month);
            break;
        }
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\n--- Меню ---" << endl;
    cout << "1. Створити новий список" << endl;
    cout << "2. Переглянути список" << endl;
    cout << "3. Додати друга до списку" << endl;
    cout << "4. Пошук друзів за місяцем народження" << endl;
    cout << "0. Вихід" << endl;
}

string getFileName() {
    string filename;
    cout << "Введіть ім'я файлу: ";
    cin >> filename;
    return filename;
}

void createList(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "Новий список створено." << endl;
    }
    else {
        cerr << "Помилка створення файлу." << endl;
    }
}

void viewList(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл." << endl;
        return;
    }

    string line;
    cout << "\nСписок друзів:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void addFriend(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Не вдалося відкрити файл для запису." << endl;
        return;
    }

    Friend newFriend;
    cout << "Введіть прізвище: ";
    cin >> newFriend.surname;
    cout << "Введіть ім'я: ";
    cin >> newFriend.name;
    cout << "Введіть номер телефону: ";
    cin >> newFriend.phoneNumber;

    string dateStr;
    cout << "Введіть дату народження (дд.мм.рррр): ";
    cin >> dateStr;

    if (!parseDate(dateStr, newFriend.birthDay, newFriend.birthMonth, newFriend.birthYear)) {
        cerr << "Невірний формат дати. Друг не доданий." << endl;
        return;
    }

    file << newFriend.surname << " " << newFriend.name << " "
        << newFriend.phoneNumber << " "
        << newFriend.birthDay << "." << newFriend.birthMonth << "." << newFriend.birthYear << endl;

    cout << "Друг доданий до списку." << endl;
}

void findFriendsByMonth(const string& filename, int month) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream iss(line);
        Friend friendData;
        string dateStr;
        iss >> friendData.surname >> friendData.name >> friendData.phoneNumber >> dateStr;

        if (parseDate(dateStr, friendData.birthDay, friendData.birthMonth, friendData.birthYear) && friendData.birthMonth == month) {
            cout << friendData.surname << " " << friendData.name << " " << friendData.phoneNumber
                << " " << friendData.birthDay << "." << friendData.birthMonth << "." << friendData.birthYear << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Немає друзів, що народилися в цьому місяці." << endl;
    }
}

bool parseDate(const string& dateStr, int& day, int& month, int& year) {
    char dot1, dot2;
    istringstream iss(dateStr);
    if (iss >> day >> dot1 >> month >> dot2 >> year && dot1 == '.' && dot2 == '.' && isValidDate(day, month, year)) {
        return true;
    }
    return false;
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (isLeap ? 29 : 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return true;
}
