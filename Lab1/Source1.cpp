#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    Student() = default;

    Student(char* name, char* surname, char* street, int phoneNum) : phone(phoneNum) {
        strcpy(name1, name);
        strcpy(surname1, surname);
        strcpy(street1, street);
    }

    char name1[50];
    char surname1[50];
    char street1[50];
    int phone;
};

//Запис в бінарний файл
void RW(ofstream& file, const Student* students, int numStudents) {
    file.write((char*)students, sizeof(Student) * numStudents);
}

//Запис в текстовий файл
void RW(ofstream& file, const Student* students, int numStudents, bool isTextFile) {
    for (int i = 0; i < numStudents; ++i) {
        file << students[i].name1 << " " << students[i].surname1 << " " << students[i].street1 << " " << students[i].phone << "\n";
    }
}

//Читання з бінарного файлу
void RD(ifstream& file, Student* students, int numStudents) {
    file.read((char*)students, sizeof(Student) * numStudents);
}

//Читання з текстового файлу
void RD(ifstream& file, Student* students, int numStudents, bool isTextFile) {
    for (int i = 0; i < numStudents; ++i) {
        file >> students[i].name1 >> students[i].surname1 >> students[i].street1 >> students[i].phone;
        file.ignore();
    }
}

int main() {
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cin.ignore();

    Student* students = new Student[numStudents];

    for (int i = 0; i < numStudents; ++i) {
        cout << "\nEnter details for student " << i + 1 << ":\n";

        cout << "First name: ";
        cin.getline(students[i].name1, 50);

        cout << "Last name: ";
        cin.getline(students[i].surname1, 50);

        cout << "Street name: ";
        cin.getline(students[i].street1, 50);

        cout << "Phone number: ";
        cin >> students[i].phone;
        cin.ignore();
    }

    ofstream binFile("INFO.DAT", ios::binary);
    if (binFile.is_open()) {
        RW(binFile, students, numStudents);
        binFile.close();
        cout << "\nWritten to INFO.DAT\n";
    }
    else {
        cout << "Error opening binary file" << endl;
        return 1;
    }

    ofstream textFile("INFO.TXT");
    if (textFile.is_open()) {
        RW(textFile, students, numStudents, true);
        textFile.close();
        cout << "\nWritten to INFO.TXT\n";
    }
    else {
        cout << "Error opening text file" << endl;
        return 1;
    }

    char searchStreet[50];
    cout << "\nEnter the street name to search: ";
    cin.getline(searchStreet, 50);

    ifstream binInFile("INFO.DAT", ios::binary);
    if (binInFile.is_open()) {
        Student* readStudents  = new Student[numStudents];
        RD(binInFile, readStudents, numStudents);
        binInFile.close();

        bool found = false;
        for (int i = 0; i < numStudents; ++i) {
            if (strcmp(readStudents[i].street1, searchStreet) == 0) {
                cout << "\nStudent living on street " << searchStreet << ": ";
                cout << readStudents[i].name1 << " " << readStudents[i].surname1 << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "\n(DAT File) No students found living on " << searchStreet << endl;
        }

        delete[] readStudents;
    }
    else {
        cout << "Error opening binary file" << endl;
    }

    ifstream textInFile("INFO.TXT");
    if (textInFile.is_open()) {
        Student* readStudents = new Student[numStudents];
        RD(textInFile, readStudents, numStudents, true);
        textInFile.close();

        bool found = false;
        for (int i = 0; i < numStudents; ++i) {
            if (strcmp(readStudents[i].street1, searchStreet) == 0) {
                cout << "\nStudent living on street " << searchStreet << ": ";
                cout << readStudents[i].name1 << " " << readStudents[i].surname1 << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "\n(TXT file) No students found living on " << searchStreet << endl;
        }

        delete[] readStudents;
    }
    else {
        cout << "Error opening text file" << endl;
    }

    delete[] students;

    return 0;
}




