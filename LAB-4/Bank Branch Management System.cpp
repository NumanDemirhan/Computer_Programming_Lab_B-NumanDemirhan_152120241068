#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber, currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string name, transactionType;
};

const int MAX_QUEUE = 5;
Customer queue[MAX_QUEUE];
int front = -1, rear = -1;

void pushMoneyBundle(MoneyBundle*& top) {
    string sn, type;
    int c100, c50, c20;
    cout << "Serial Number: "; cin >> sn;
    cout << "Currency: "; cin >> type;
    cout << "Enter counts (100/50/20): "; cin >> c100 >> c50 >> c20;
    
    MoneyBundle* node = new MoneyBundle{sn, type, {c100, c50, c20}, top};
    top = node;
}

void popMoney(MoneyBundle*& top) {
    if (!top) { cout << "ERROR: Cash vault is empty!\n"; return; }
    MoneyBundle* temp = top;
    top = top->next;
    delete temp;
    cout << "=> One bundle removed from vault.\n";
}

void enqueueCustomer(Customer queue[], int& front, int& rear) {
    if ((rear + 1) % MAX_QUEUE == front) { cout << "ERROR: Queue is full!\n"; return; }
    string name, type;
    cout << "Customer Name: "; cin >> name;
    cout << "Transaction Type: "; cin >> type;
    if (front == -1) front = 0;
    queue[(rear = (rear + 1) % MAX_QUEUE)].name = name;
    queue[rear].transactionType = type;
}

void dequeueCustomer(int& front, int& rear) {
    if (front == -1) return;
    front = (front == rear) ? -1 : (front + 1) % MAX_QUEUE;
    if (front == -1) rear = -1;
}

void processTransaction(MoneyBundle*& top, Customer queue[], int& front, int& rear) {
    if (front == -1) { cout << "\nERROR: No customer in queue!\n"; return; }
    if (!top) { cout << "\nERROR: No money bundle in vault!\n"; return; }
    
    cout << "\n>>> TRANSACTION COMPLETED <<<\n";
    cout << "Customer: " << queue[front].name << " [" << queue[front].transactionType << "]\n";
    cout << "Bundle Used: " << top->serialNumber << " (" << top->currencyType << ")\n";
    popMoney(top);
    dequeueCustomer(front, rear);
    cout << "-----------------------------\n";
}

void displayAll(MoneyBundle* top, Customer queue[], int front, int rear) {
    cout << "\n========== BANK STATUS ==========\n";
    cout << "VAULT (Stack): ";
    if (!top) cout << "[EMPTY]";
    else for (auto t = top; t; t = t->next) cout << "<- [" << t->serialNumber << "] ";
    
    cout << "\nQUEUE: ";
    if (front == -1) cout << "[EMPTY]";
    else {
        for (int i = front; ; i = (i + 1) % MAX_QUEUE) {
            cout << "-> " << queue[i].name << " ";
            if (i == rear) break;
        }
    }
    cout << "\n==================================\n";
}

int main() {
    MoneyBundle* stackTop = nullptr;
    int choice=NULL;
    
    while (choice != 5) {
        cout << "1. Add Money Bundle (Push)\n2. Enqueue Customer\n3. Process Transaction\n";
        cout << "4. View Status\n5. Exit\nChoice: ";
        cin >> choice;
        
        switch (choice) {
        case 1: pushMoneyBundle(stackTop); break;
        case 2: enqueueCustomer(queue, front, rear); break;
        case 3: processTransaction(stackTop, queue, front, rear); break;
        case 4: displayAll(stackTop, queue, front, rear); break;
        case 5: cout << "Program terminated.\n"; break;
        default: cout << "Invalid choice!\n";
        }
    }
    return 0;
}