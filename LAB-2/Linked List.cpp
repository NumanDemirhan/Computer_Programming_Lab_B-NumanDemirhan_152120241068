#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string songTitle;
    Node* next;
};

void addSong(Node*& head, string title)
{
    Node* newNode = new Node;
    newNode->songTitle = title;
    newNode->next = head;
	head = newNode;
}
void searchSong(Node* head, string title)
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->songTitle == title)
        {
            cout << "Song found: " << current->songTitle << "\n";
            return;
        }
        current = current->next;
    }
    cout << "Song dont found: " << title << "\n";
}

void displaySongs(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        cout << current->songTitle << "\n";
        current = current->next;
    }
}

int main()
{
	Node* playList = nullptr;
	int choice;
	string title;

    do {
		cout << "1. Add Song\n2. Search Song\n3. Display Playlist\n4. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1){
            cout << "Enter song title to add: ";
            getline(cin, title);
            addSong(playList, title);
        }else if (choice == 2) {
            cout << "Enter song title to search: ";
            getline(cin, title);
            searchSong(playList, title);
        }else if(choice == 3){
            cout << "Playlist:\n";
            displaySongs(playList);
		}
	} while (choice != 4);
}

