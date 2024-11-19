#include <iostream>
#include <string>
#include <limits>

class Patient {
public:
    std::string name;      // Patient's name
    int age;               // Patient's age
    std::string symptoms;  // Patient's symptoms
    std::string contact;   // Patient's contact information
    int priority;          // Priority level (1: serious, 2: medium, 3: general)
    Patient* next;         // Pointer to the next patient in the queue

    // Constructor to initialize a new patient
    Patient(std::string n, int a, std::string s, std::string c, int p)
        : name(n), age(a), symptoms(s), contact(c), priority(p), next(nullptr) {}
};

class PriorityQueue {
private:
    Patient* head; // Head of the linked list

public:
    // Constructor to initialize the priority queue
    PriorityQueue() : head(nullptr) {}

    // Check if the queue is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Add a patient to the queue based on their priority
    void enqueue(std::string name, int age, std::string symptoms, std::string contact, int priority) {
        Patient* newPatient = new Patient(name, age, symptoms, contact, priority);
        
        if (isEmpty() || head->priority > newPatient->priority) {
            newPatient->next = head;
            head = newPatient;
        } else {
            Patient* current = head;
            while (current->next != nullptr && current->next->priority <= newPatient->priority) {
                current = current->next;
            }
            newPatient->next = current->next;
            current->next = newPatient;
        }
    }

    // Remove and return the patient with the highest priority
    Patient* dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty.");
        }

        Patient* patientToServe = head;
        head = head->next; // Move the head to the next patient
        return patientToServe; // Return the patient to be served
    }

    // Display the patients in the priority queue
    void display() {
        Patient* current = head;
        while (current != nullptr) {
            std::cout << "Patient Name: " << current->name
                      << ", Age: " << current->age
                      << ", Symptoms: " << current->symptoms
                      << ", Contact: " << current->contact
                      << ", Priority: " << current->priority << std::endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~PriorityQueue() {
        while (!isEmpty()) {
            Patient* temp = dequeue();
            delete temp; // Free the memory of the dequeued patient
        }
    }
};

// Function to get valid input for patient priority
int getValidPriority() {
    int priority;
    while (true) {
        std::cout << "Enter priority (1: Serious, 2: Medium, 3: General): ";
        std::cin >> priority;

        if (std::cin.fail() || priority < 1 || priority > 3) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
            std::cout << "Invalid input. Please enter a valid priority." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            return priority; // Return valid priority
        }
    }
}

// Main function to demonstrate the priority queue
int main() {
    PriorityQueue pq; // Create a priority queue
    std::string name; // Variable to hold patient name
    int age;          // Variable to hold patient age
    std::string symptoms; // Variable to hold patient symptoms
    std::string contact;  // Variable to hold patient contact information
    int priority;     // Variable to hold patient priority

   
    std::cout << "Enter patient details (type 'done' as name to finish):" << std::endl;

    // Loop to input patient details
    while (true) {
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << "Enter patient name: ";
        std::getline(std::cin, name); // Use getline to allow spaces in names

        if (name == "done") {
            break; // Exit the loop if the user types 'done'
        }

        std::cout << "Enter patient age: ";
        std::cin >> age;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        std::cout << "Enter patient symptoms: ";
        std::getline(std::cin, symptoms); // Use getline for symptoms

        std::cout << "Enter patient contact information: ";
        std::getline(std::cin, contact); // Use getline for contact information

        priority = getValidPriority(); // Get valid priority input

        pq.enqueue(name, age, symptoms, contact, priority); // Enqueue the patient
    }
std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "\nPatients in the priority queue:" << std::endl;
    pq.display(); // Display all patients in the queue
std::cout << "-----------------------------------------------------------------" << std::endl;
    // Serve patients based on priority
    while (!pq.isEmpty()) {
        Patient* servedPatient = pq.dequeue(); // Dequeue the highest priority patient
       
        std::cout << "Serving patient: " << servedPatient->name << std::endl;
        delete servedPatient; // Free the memory of the served patient
    }

    return 0; // End of the program
}
