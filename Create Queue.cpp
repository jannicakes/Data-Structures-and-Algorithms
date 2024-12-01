#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Person {
public:
    string name;
    int ticket_number;

    Person(string name, int ticket_number) : name(name), ticket_number(ticket_number) {}
};

class Queue {
private:
    queue<Person> personQueue;
    int ticket_counter = 1;

public:
    void enqueue(const string& name) {
        Person person(name, ticket_counter++);
        personQueue.push(person);
        cout << person.name << " added to the queue with Ticket #" 
             << (person.ticket_number < 10 ? "00" : "0") << person.ticket_number << "\n";
        cout << "Queue size: " << personQueue.size() << "\n\n";
    }

    void autoDequeueWithDelay() {
        if (!personQueue.empty()) {
            // Simulate the "After 1 minute..." delay
            this_thread::sleep_for(chrono::minutes(1));  // Replace with chrono::minutes(1) for a real minute delay
            Person person = personQueue.front();
            personQueue.pop();
            cout << "\nAfter 1 minute...\n";
            cout << "Dequeued: " << person.name << " received a ticket (Ticket #" 
                 << (person.ticket_number < 10 ? "00" : "0") << person.ticket_number << ")\n";
            cout << "Queue size: " << personQueue.size() << "\n\n";
            if (!personQueue.empty()) {
                Person next_person = personQueue.front();
                cout << "Next in line: " << next_person.name << " (Ticket #" 
                     << (next_person.ticket_number < 10 ? "00" : "0") << next_person.ticket_number << ")\n";
            }
            cout << endl;
        } else {
            cout << "Queue is empty, no one to dequeue.\n";
        }
    }

    void position(const string& name_or_ticket) {
        int pos = 1;
        queue<Person> tempQueue = personQueue;
        bool found = false;

        while (!tempQueue.empty()) {
            Person person = tempQueue.front();
            tempQueue.pop();
            if (person.name == name_or_ticket || to_string(person.ticket_number) == name_or_ticket) {
                cout << person.name << " is currently at position " << pos << " in the queue.\n\n";
                found = true;
                break;
            }
            pos++;
        }
        if (!found) {
            cout << "Person or ticket number not found in the queue.\n";
        }
    }

    int size() const {
        return personQueue.size();
    }
};

int main() {
    Queue ticketQueue;
    int choice;
    string name;

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!\n\n";
    while (true) {
        cout << "   1. Enqueue a person\n   2. Check your position in the queue\n   3. Exit\n";
        cout << "\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the name: ";
            cin >> name;
            ticketQueue.enqueue(name);
        } else if (choice == 2) {
            cout << "Enter your name or ticket number: ";
            cin >> name;
            ticketQueue.position(name);
        } else if (choice == 3) {
            break;
        }

        // Simulate auto-dequeue after each enqueue if there are 3 people or more
        if (choice == 1 && ticketQueue.size() >= 3) {
            ticketQueue.autoDequeueWithDelay();
        }
    }

    return 0;
}
