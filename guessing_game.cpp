#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

// Function prototypes
void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void saveContactsToFile(const vector<Contact>& contacts, const string& filename);
void loadContactsFromFile(vector<Contact>& contacts, const string& filename);

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";
    loadContactsFromFile(contacts, filename);

    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To ignore the leftover newline character

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                saveContactsToFile(contacts, filename);
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phone);
    cout << "Enter email address: ";
    getline(cin, newContact.email);
    contacts.push_back(newContact);
    cout << "Contact added successfully.\n";
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "\nContact " << (i + 1) << ":\n";
        cout << "Name: " << contacts[i].name << "\n";
        cout << "Phone: " << contacts[i].phone << "\n";
        cout << "Email: " << contacts[i].email << "\n";
    }
}

void editContact(vector<Contact>& contacts) {
    viewContacts(contacts);
    int index;
    cout << "Enter the contact number to edit: ";
    cin >> index;
    cin.ignore();  // To ignore the leftover newline character

    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Invalid contact number.\n";
        return;
    }

    index--;  // Adjust for 0-based index
    cout << "Enter new name (leave blank to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) contacts[index].name = newName;

    cout << "Enter new phone number (leave blank to keep current): ";
    string newPhone;
    getline(cin, newPhone);
    if (!newPhone.empty()) contacts[index].phone = newPhone;

    cout << "Enter new email address (leave blank to keep current): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) contacts[index].email = newEmail;

    cout << "Contact updated successfully.\n";
}

void deleteContact(vector<Contact>& contacts) {
    viewContacts(contacts);
    int index;
    cout << "Enter the contact number to delete: ";
    cin >> index;
    cin.ignore();  // To ignore the leftover newline character

    if (index < 1 || index > static_cast<int>(contacts.size())) {
        cout << "Invalid contact number.\n";
        return;
    }

    index--;  // Adjust for 0-based index
    contacts.erase(contacts.begin() + index);
    cout << "Contact deleted successfully.\n";
}

void saveContactsToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
    }
    file.close();
}

void loadContactsFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No previous contacts found. Starting a new contact list.\n";
        return;
    }

    Contact contact;
    string line;
    while (getline(file, line)) {
        contact.name = line;
        getline(file, contact.phone);
        getline(file, contact.email);
        contacts.push_back(contact);
    }
    file.close();
}




