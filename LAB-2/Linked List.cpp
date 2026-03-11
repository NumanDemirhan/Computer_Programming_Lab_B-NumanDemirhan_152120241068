#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string songTitle;
    Node* next;
};

void addSong(Node*& header, string title)
{
    Node* newNode = new Node;
    newNode->songTitle = title;
    newNode->next = header;
	header = newNode;
}
void searchSong(Node* header, string title)
{
    Node* current = header;
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

void displaySongs(Node* header)
{
    Node* current = header;
    while (current != nullptr)
    {
        cout << current->songTitle << "\n";
        current = current->next;
    }
}

int main()
{
	Node* myPlayList = nullptr;
	int choice;
	string title;

    do {
		cout << "1. Add Song\n2. Search Song\n3. Display Playlist\n4. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1){
            cout << "Enter song title to add: ";
            getline(cin, title);
            addSong(myPlayList, title);
        }else if (choice == 2) {
            cout << "Enter song title to search: ";
            getline(cin, title);
            searchSong(myPlayList, title);
        }else if(choice == 3){
            cout << "\n";
            cout << "Playlist:\n";
            displaySongs(myPlayList);
            cout << "\n";
		}
	} while (choice != 4);
}

