#include <iostream>
#include <string>
using namespace std;

struct Page{
    string url;
	string title;
	int accessedTime[3];
    Page* next;
    Page* prev;
};

void VisitPage(Page** head, Page** current, string url, string title, int h, int m, int s);
void Back(Page** current);
void Forward(Page** current);
void DeleteEntry(Page** head, Page** current);
void DisplayHistory(Page* head, Page* current);
void clearHistory(Page** head, Page** current);

int main()
{
	Page* head = nullptr;
	Page* current = nullptr;

	string command;

	while (true) {
		cout << "Komut (VISIT, BACK, FORWARD, DELETE, DISPLAY, EXIT): ";
		cin >> command;

		if (command == "VISIT") {
			string url, title;
			int h, m, s;
			cout << "URL: "; cin >> url;
			cout << "Title: "; cin.ignore(); getline(cin, title);
			cout << "Time (HH MM SS): "; cin >> h >> m >> s;
			VisitPage(&head, &current, url, title, h, m, s);
		}
		else if (command == "BACK") Back(&current);
		else if (command == "FORWARD") Forward(&current);
		else if (command == "DELETE") DeleteEntry(&head, &current);
		else if (command == "DISPLAY") DisplayHistory(head, current);
		else if (command == "EXIT") {
			clearHistory(&head, &current);
			cout << "Exiting..." << endl;
			break;
		}
	}
	return 0;
}


void VisitPage(Page** head, Page** current, string url, string title, int h, int m, int s) {
	Page* newPage = new Page;
	newPage->url = url;
	newPage->title = title;
	newPage->accessedTime[0] = h;
	newPage->accessedTime[1] = m;
	newPage->accessedTime[2] = s;
	newPage->next = nullptr;
	newPage->prev = nullptr;

	if (*head == nullptr) {
		*head = newPage;
		*current = newPage;
	}
	else {
		Page* temp = *head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newPage;
		newPage->prev = temp;
		*current = newPage;
		
	}
	cout << "Visited: " << title << endl;
}

void Back(Page** current) {
	if(current == nullptr || (*current)->prev == nullptr) {
		cout << "No previous page." << endl;
	}
	else {
		*current = (*current)->prev;
		cout << "Back to: " << (*current)->title << endl;
	}
}

void Forward(Page** current) {
	if(current == nullptr || (*current)->next == nullptr) {
		cout << "No next page." << endl;
	}
	else {
		*current = (*current)->next;
		cout << "Forward to: " << (*current)->title << endl;
	}
}

void DeleteEntry(Page** head, Page** current) {
	if(current == nullptr) {
		cout << "No current page to delete." << endl;
		return;
	}

	Page* toDelete = *current;
	if(toDelete->prev != nullptr) {
		toDelete->prev->next = toDelete->next;
	}else {
		*head = toDelete->next;
	}

	if(toDelete->next != nullptr) {
		toDelete->next->prev = toDelete->prev;
		*current = toDelete->next;
	}else{
		*current = toDelete->prev;
	}
	cout << "Deleted: " << toDelete->title << endl;
	delete toDelete;
}

void DisplayHistory(Page* head, Page* current) {
	if(head == nullptr) {
		cout << "No browsing history." << endl;
		return;
	}

	Page* temp = head;
	cout << "------------------------------------------" << endl;
	cout << "Browsing History:" << endl;
	
	while(temp != nullptr) {
		if(temp == current) {
			cout << "-> ";
		}
		cout << "Title" << temp->title << ", Time: ";

		for (int i = 0; i < 3; i++) {
			if (temp->accessedTime[i] < 10) cout << "0";
			cout << temp->accessedTime[i];
			if (i < 2) cout << ":";
		}
		cout << endl;
		temp = temp->next;
	}
	cout << "------------------------------------------\n" << endl;
}

void clearHistory(Page** head, Page** current) {
	Page* temp = *head;
	while(temp != nullptr) {
		Page* toDelete = temp;
		temp = temp->next;
		delete toDelete;
	}
	*head = nullptr;
	*current = nullptr;
	cout << "Browsing history cleared." << endl;
}