#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string lastName;
    string firstName;
    string address;
    string phone;
};

void writeString(ofstream& outFile, const string& str) {
    outFile << str << endl;
}

void readString(ifstream& inFile, string& str) {
    getline(inFile, str);
}

int main1() {

    int n;

    cout << "Enter the number of students: ";
    cin >> n;
    cin.get();

    Student* students = new Student[n];

    for (int i = 0; i < n; i++) {
        cout << "Student info " << i + 1 << ":\n";
        cout << "Last name: "; getline(cin, students[i].lastName);
        cout << "First name: "; getline(cin, students[i].firstName);
        cout << "Street: "; getline(cin, students[i].address);
        cout << "Phone number: "; getline(cin, students[i].phone);
    }

    //бінарний файл
    ofstream outFile("INFO2.DAT", ios::binary);
    if (outFile.is_open()) {
        for (int i = 0; i < n; i++) {
            size_t len;
            len = students[i].lastName.size();
            outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
            outFile.write(students[i].lastName.c_str(), len);

            len = students[i].firstName.size();
            outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
            outFile.write(students[i].firstName.c_str(), len);

            len = students[i].address.size();
            outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
            outFile.write(students[i].address.c_str(), len);

            len = students[i].phone.size();
            outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
            outFile.write(students[i].phone.c_str(), len);
        }
        outFile.close();
        cout << "Info is written\n";
    }
    else {
        cout << "Couldn't open the file for writing\n";
    }

    ifstream inFile("INFO2.DAT", ios::binary);
    if (inFile.is_open()) {
        cout << "\nInfo from file:\n";
        for (int i = 0; i < n; i++) {
            Student s;

            size_t len;

            inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            s.lastName.resize(len);
            inFile.read(&s.lastName[0], len);

            inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            s.firstName.resize(len);
            inFile.read(&s.firstName[0], len);

            inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            s.address.resize(len);
            inFile.read(&s.address[0], len);

            inFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            s.phone.resize(len);
            inFile.read(&s.phone[0], len);

            cout << s.lastName << " " << s.firstName << " "
                << s.address << " " << s.phone << endl;
        }
        inFile.close();
    }
    else {
        cout << "Couldn't open the file for reading\n";
    }

    string street;
    cout << "\nEnter the name of street for searching: ";
    getline(cin, street);

    bool found = false;
    cout << "\nStudents living on street " << street << ":\n";
    for (int i = 0; i < n; i++) {
        if (students[i].address == street) {
            cout << students[i].lastName << " " << students[i].firstName << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "There are no students on this street\n";
    }
    delete[] students;

    return 0;
}


