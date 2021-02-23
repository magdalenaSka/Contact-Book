#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

string fileName = "ContactsBook.txt";

struct Person {
    int id = 0;
    string name = "";
    string surname = "";
    string email = "";
    string adress = "";
    string telephoneNumber = "";
};

Person assignToStructure (string line) {

    Person contactDetails;
    string name, surname, email, adress, telephoneNumber;
    int id;
    string word = "";
    string separateWords[6];
    int k = 0;

    for (int i = 0; i <= line.size(); i++) {

        if (line[i] != '|') {
            word += line[i];
        } else {
            separateWords[k] = word;
            k++;
            word = "";
        }
    }
    contactDetails.id = atoi(separateWords[0].c_str());
    contactDetails.name = separateWords[1];
    contactDetails.surname = separateWords[2];
    contactDetails.telephoneNumber = separateWords[3];
    contactDetails.email = separateWords[4];
    contactDetails.adress = separateWords[5];

    return contactDetails;
}

void loadContactsFromFile (vector <Person> &contacts) {

    string name, surname, email, adress, telephoneNumber;
    int id;
    Person contactDetails;
    int contactsAmount = 0;
    string line = "";

    fstream file;
    file.open(fileName.c_str(), ios::in);

    if (file.good() == true) {

        while(!file.eof()) {
            getline(file, line);

            contactDetails = assignToStructure(line);
            contacts.push_back(contactDetails);
        }
    contacts.erase(contacts.end());
    }
    file.close();
}

void addPersonToFile (Person contactDetails) {

    fstream file;
    file.open(fileName.c_str(), ios::out | ios::app);

    if (file.good() == true) {
        file << contactDetails.id << '|';
        file << contactDetails.name << '|';
        file << contactDetails.surname << '|';
        file << contactDetails.telephoneNumber << '|';
        file << contactDetails.email << '|';
        file << contactDetails.adress << '|' << endl;
        file.close();

        cout << endl << "Kontakt zostal zapisany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void addPerson (vector <Person> &contacts) {

    Person contactDetails;
    string name, surname, email, adress, telephoneNumber;
    int id;

    system("cls");
    if (contacts.empty() == true) {
        contactDetails.id = 1;
    } else {
        contactDetails.id = contacts.back().id + 1;
    }

    cout << "Wrowadz imie: ";
    cin >> contactDetails.name;

    cout << "Wrowadz nazwisko: ";
    cin >> contactDetails.surname;

    cout << "Wrowadz numer telefonu: ";
    cin.sync();
    getline (cin, contactDetails.telephoneNumber);

    cout << "Wrowadz e-mail: ";
    cin >> contactDetails.email;

    cout << "Wrowadz adres: ";
    cin.sync();
    getline(cin, contactDetails.adress);

    contacts.push_back(contactDetails);
    addPersonToFile (contactDetails);
}

void searchByName(vector <Person> &contacts) {

    string name;

    cout << "Wprowadz imie: ";
    cin >> name;

    for (int i = 0; i < contacts.size(); i++) {

        if (contacts[i].name == name) {
            cout << contacts[i].id << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].telephoneNumber << "|" << contacts[i].email << "|" << contacts[i].adress << "|" << endl;
        }
    }
    cout << endl;
}

void searchBySurname(vector <Person> &contacts) {

    string surname;

    cout << "Wprowadz nazwisko: ";
    cin >> surname;

    for(int i = 0; i < contacts.size(); i++) {

        if (contacts[i].surname == surname) {
            cout << contacts[i].id << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].telephoneNumber << "|" << contacts[i].email << "|" << contacts[i].adress << "|" << endl;
        }
    }
    cout << endl;
}

void schowAllContacts(vector <Person> &contacts) {

    system("cls");
    if (!contacts.empty()) {
        for (vector<Person>::iterator itr = contacts.begin(); itr != contacts.end(); itr++) {
            cout << itr->id << '|';
            cout << itr->name << '|';
            cout << itr->surname << '|';
            cout << itr->telephoneNumber << '|';
            cout << itr->email << '|';
            cout << itr->adress <<'|' << endl;
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
}

void editData (string path, vector <Person> &contacts) {

    vector <string> temporary;

    ifstream in(path);
    string line;
    while (getline(in, line))
        temporary.push_back(line);
    in.close();

    ofstream out(path);
    for (int i = 0; i < contacts.size(); ++i) {
        out << contacts[i].id << '|';
        out << contacts[i].name << '|';
        out << contacts[i].surname << '|';
        out << contacts[i].telephoneNumber << '|';
        out << contacts[i].email << '|';
        out << contacts[i].adress << '|' << endl;
    }
    out.close();
}

void deleteContact (vector <Person> &contacts) {

    int personID;
    char yes;

    cout << "Kontakty obecnie zapisane w ksiazce:" << endl;
    schowAllContacts(contacts);
    cout << endl;
    cout << "Podaj ID kontaktu do usuniecia: ";
    cin >> personID;

    cout << "Jesli jestes pewnien, ze chcesz usunac kontakt wybierz 't' z klawiatury: ";
    cin >> yes;

    if (yes == 't') {
        for (int i = 0 ; i < contacts.size(); i++) {
            if (personID == contacts[i].id) {
                contacts.erase(contacts.begin()+ i);
                editData(fileName.c_str(), contacts);
            }
        }
        cout << "Kontakt zostal usuniety." << endl;
    } else
        cout << "Kontak nie zostal usuniety!" << endl;
}

void editContact (vector <Person> &contacts) {

    char option;
    int personID;
    string name, surname, telephoneNumber, email, adress;

    cout << "Kontakty obecnie zapisane w ksiazce:" << endl;
    schowAllContacts(contacts);
    cout << endl;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> personID;

    for (int i = 0 ; i < contacts.size(); i++) {

        if (personID == contacts[i].id ) {

            system("cls");
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;

            cout << "Wybierz cyfre z menu, ktore dane chcesz edytowac: ";
            cin >> option;

            if (option == '1') {
                cout << "Wpisz nowe imie: ";
                cin >> contacts[i].name;
                editData(fileName.c_str(), contacts);

            } else if (option == '2') {
                cout << "Wpisz nowe nazwisko: ";
                cin >> contacts[i].surname;
                editData(fileName.c_str(), contacts);
            } else if (option == '3') {
                cout << "Wpisz nowy numer telefonu: ";
                cin.sync();
                getline(cin, contacts[i].telephoneNumber);
                editData(fileName.c_str(), contacts);
            } else if (option == '4') {
                cout << "Wpisz nowy e-mail: ";
                cin >> contacts[i].email;
                editData(fileName.c_str(), contacts);
            } else if (option == '5') {
                cout << "Wpisz nowy adres: ";
                cin.sync();
                getline(cin, contacts[i].adress);
                editData(fileName.c_str(), contacts);
            } else if (option == '6') {
                getchar();
            }
        }
    }
}

int main() {
    vector <Person> contacts;
    int contactID = 0;
    char choice;

    loadContactsFromFile(contacts);

    while(1) {

        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> choice;

        if (choice == '1') {
            addPerson(contacts);
            system("pause");
        } else if (choice == '2') {
            searchByName(contacts);
            system("pause");
        } else if (choice == '3') {
            searchBySurname(contacts);
            system("pause");
        } else if (choice == '4') {
            schowAllContacts(contacts);
            system("pause");
        } else if (choice == '5') {
            deleteContact(contacts);
            system("pause");
        } else if (choice == '6') {
            editContact(contacts);
            system("pause");
        } else if (choice == '9') {
            exit(0);
        }
    }
    return 0;
}
