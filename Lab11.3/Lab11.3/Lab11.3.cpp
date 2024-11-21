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
        cout << "������ �����: ";
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
            cout << "������ ����� ����� (1-12): ";
            while (!(cin >> month) || month < 1 || month > 12) {
                cout << "������� ����� �����. ��������� �� ���: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            findFriendsByMonth(filename, month);
            break;
        }
        case 0:
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���." << endl;
        }
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    cout << "\n--- ���� ---" << endl;
    cout << "1. �������� ����� ������" << endl;
    cout << "2. ����������� ������" << endl;
    cout << "3. ������ ����� �� ������" << endl;
    cout << "4. ����� ����� �� ������ ����������" << endl;
    cout << "0. �����" << endl;
}

string getFileName() {
    string filename;
    cout << "������ ��'� �����: ";
    cin >> filename;
    return filename;
}

void createList(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "����� ������ ��������." << endl;
    }
    else {
        cerr << "������� ��������� �����." << endl;
    }
}

void viewList(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
        return;
    }

    string line;
    cout << "\n������ �����:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void addFriend(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "�� ������� ������� ���� ��� ������." << endl;
        return;
    }

    Friend newFriend;
    cout << "������ �������: ";
    cin >> newFriend.surname;
    cout << "������ ��'�: ";
    cin >> newFriend.name;
    cout << "������ ����� ��������: ";
    cin >> newFriend.phoneNumber;

    string dateStr;
    cout << "������ ���� ���������� (��.��.����): ";
    cin >> dateStr;

    if (!parseDate(dateStr, newFriend.birthDay, newFriend.birthMonth, newFriend.birthYear)) {
        cerr << "������� ������ ����. ���� �� �������." << endl;
        return;
    }

    file << newFriend.surname << " " << newFriend.name << " "
        << newFriend.phoneNumber << " "
        << newFriend.birthDay << "." << newFriend.birthMonth << "." << newFriend.birthYear << endl;

    cout << "���� ������� �� ������." << endl;
}

void findFriendsByMonth(const string& filename, int month) {
    ifstream file(filename);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
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
        cout << "���� �����, �� ���������� � ����� �����." << endl;
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
