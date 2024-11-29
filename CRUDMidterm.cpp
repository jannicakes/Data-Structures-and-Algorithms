#include <iostream>
#include <map>
#include <string>

using namespace std;

// Global contacts map: name -> details (address, phone, email)
map<string, map<string, string>> contacts;

// Function to add a contact
void createContact() {
    string name, address, phone, email;
    
    while (true) {
        cout << "\nPlease enter the following details:\n";
        cout << "> Name: ";
        getline(cin, name);
        cout << "> Address: ";
        getline(cin, address);
        cout << "> Phone number: ";
        getline(cin, phone);
        cout << "> Email address: ";
        getline(cin, email);

        // Adding details to the map
        contacts[name] = { {"address", address}, {"phone", phone}, {"email", email} };
        cout << "\nContact details saved successfully!\n";

        cout << "Do you want to add another contact (y/n)? ";
        string choice;
        getline(cin, choice);
        if (choice != "y") break;
    }
}

// Function to delete a contact
void deleteContact() {
    if (contacts.empty()) {
        cout << "You don't have any contacts saved! Try adding new contacts.\n";
        return;
    }

    while (true) {
        cout << "\n------- Your Contacts -------\n";
        for (const auto& contact : contacts) {
            cout << "> " << contact.first << endl;
        }

        cout << "\nEnter the name of the contact you want to delete\n[Write 'DEL ALL' to delete all contacts]: ";
        string name_del;
        getline(cin, name_del);

        if (name_del == "DEL ALL") {
            cout << "\nYou are about to delete all contacts. Type 'CONFIRM' to proceed: ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "CONFIRM") {
                contacts.clear();
                cout << "All contacts deleted successfully!\n";
            } else {
                cout << "Contacts were not deleted.\n";
            }
            break;
        } else if (contacts.count(name_del)) {
            contacts.erase(name_del);
            cout << "\nContact deleted!\n";
        } else {
            cout << "The contact name entered does not exist.\n";
        }

        if (contacts.empty()) {
            cout << "You don't have any contacts saved! Try adding new contacts.\n";
            break;
        }

        cout << "Do you want to delete another contact (y/n)? ";
        string choice;
        getline(cin, choice);
        if (choice != "y") break;
    }
}

// Function to update a contact
void updateContact() {
    if (contacts.empty()) {
        cout << "You don't have any contacts saved! Try adding new contacts.\n";
        return;
    }

    while (true) {
        cout << "\n-------- Your Contacts --------\n";
        for (const auto& contact : contacts) {
            cout << "> " << contact.first << endl;
        }

        cout << "\nEnter the name of the contact you want to update: ";
        string name_edit;
        getline(cin, name_edit);

        if (contacts.count(name_edit)) {
            cout << "\n-------- Contact Details for " << name_edit << " --------\n";
            for (const auto& detail : contacts[name_edit]) {
                cout << "> " << detail.first << ": " << detail.second << endl;
            }

            cout << "\nPlease enter the attribute you want to change and the new data in the format: <attribute>|<new_value>\n";
            cout << "\nYou can update the following attributes: address, phone, email\n";

            string input;
            getline(cin, input);
            size_t pos = input.find('|');
            if (pos != string::npos) {
                string attribute = input.substr(0, pos);
                string new_value = input.substr(pos + 1);

                if (contacts[name_edit].count(attribute)) {
                    contacts[name_edit][attribute] = new_value;
                    cout << "\nContact details updated successfully!\n";
                } else {
                    cout << "Invalid attribute.\n";
                }
            }

        } else {
            cout << "The contact name entered does not exist.\n";
        }

        cout << "Do you want to update another contact (y/n)? ";
        string choice;
        getline(cin, choice);
        if (choice != "y") break;
    }
}

// Function to view a contact's details
void readContact() {
    if (contacts.empty()) {
        cout << "You don't have any contacts saved! Try adding new contacts.\n";
        return;
    }

    while (true) {
        cout << "\n-------- Your Contacts --------\n";
        for (const auto& contact : contacts) {
            cout << "> " << contact.first << endl;
        }

        cout << "\nEnter the name of the contact you want to view: ";
        string name_info;
        getline(cin, name_info);

        if (contacts.count(name_info)) {
            cout << "\n---- Contact Details for " << name_info << " ----\n";
            for (const auto& detail : contacts[name_info]) {
                cout << ">> " << detail.first << ": " << detail.second << endl;
            }
        } else {
            cout << "The contact name entered does not exist.\n";
        }

        cout << "Do you want to view another contact (y/n)? ";
        string choice;
        getline(cin, choice);
        if (choice != "y") break;
    }
}

// Main function to run the contact book
int main() {
    while (true) {
        cout << "\n------------ Contact Book ------------\n";
        cout << "Enter:\n";
        cout << "[0] to add a new contact\n";
        cout << "[1] to view your contacts\n";
        cout << "[2] to update an existing contact\n";
        cout << "[3] to delete an existing contact\n";

        string choice;
        getline(cin, choice);

        if (choice == "0") {
            createContact();
        } else if (choice == "1") {
            readContact();
        } else if (choice == "2") {
            updateContact();
        } else if (choice == "3") {
            deleteContact();
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nDo you want to use the Contact Book again (y/n)? ";
        string again;
        getline(cin, again);
        if (again != "y") {
            cout << "\nThank you for using the Contact Book!\n";
            break;
        }
    }

    return 0;
}