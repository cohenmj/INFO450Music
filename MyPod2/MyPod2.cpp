// Assignment #5 My-Pod
// Michael Cohen

//Kristoff (Louie) assisted me in fixing my unworkable code to something functional


#include "stdafx.h" 
#include <iostream>
#include <fstream>
#include "windows.h"
#include <stdio.h>

using namespace std;


//List node Class
class node
{
	int data;
	char artistName[30];
	char songName[30];
	node *next;
public:
	node(char a[30], char s[30]);
	friend class linkedList;
};

node::node(char a[30], char s[30])
{
	strcpy_s(artistName, a);
	strcpy_s(songName, s);
	next = NULL;
}

//Linked List Class
class linkedList
{
	char filename[30];
	node *head;
	node *tail;
public:
	linkedList();
	void addNodeToEnd(node *nptr);
	void setFileName(char f[]);
	void showList();
	int readList(char y[]);
	int removeSong();
	void playCurrentSong();
	void skipCurrentSong();

};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

void linkedList::addNodeToEnd(node *ptr)
{
	// if lists is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkedList::setFileName(char f[])
{
	strcpy_s(filename, f);
}

void linkedList::showList()
{
	node *ptr;
	ptr = head;

	cout << "\nMyPod Contents:\n" << endl;

	if (ptr == NULL)
	{
		cout << "No songs have been loaded in!\n" << endl;
		return;
	}
	while (ptr != NULL) // to display all songs
	{
		printf("Artist:	%s\tSong: %s\n", ptr->artistName, ptr->songName);
		ptr = ptr->next;
	}
	cout << endl;
}

int linkedList::readList(char y[])
{
	char filename[30];

	ifstream infile(y);

	if (!infile)
	{
		return -1;
	}
	while (!infile.eof())
	{
		char artistName[30];
		char songName[30];

		infile.getline(artistName, 30, ',');
		infile.getline(songName, 30);

		node * newnode = new node(artistName, songName);
		this->addNodeToEnd(newnode);
	}
	infile.close();
}

int linkedList::removeSong()
{
	char songToDelete[30];
	node *ptr = head;

	cout << "\nEnter the song you would like to remove from your list (Case Sensitive)" << endl;
	cout << "*TIP* to remove empty entry -> hit 'enter" << endl;
	cin.clear();
	cin.ignore();
	gets_s(songToDelete);

	if (ptr == NULL) // empty list
	{
		return -1;
	}
	//if node is at the head
	if (strcmp(songToDelete, ptr->songName) == 0)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = head->next;
		}
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->songName, songToDelete) == 0))
		{
			if (tail == ptr->next)
			{
				tail = ptr;
			}
			node *aNode = ptr->next;
			ptr->next = (ptr->next)->next;
			delete aNode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

void linkedList::playCurrentSong() 
{
	char songToPlay[30];
	node *ptr = head;

	cout << "\nEnter the song you want to play (Case Sensitive)" << endl;
	cin.clear();
	cin.ignore();
	gets_s(songToPlay);
	
	while (ptr != NULL)
	{
		if (strcmp(songToPlay, ptr->songName) == 0)
		{
			cout << "\nCurrently Playing:" << endl;
			printf("Artist: %s\nSong: %s\n", ptr->artistName, ptr->songName);
		}
		ptr = ptr->next;
	}
}

void linkedList::skipCurrentSong() //Not 100% but will work for the 1st song on the list
{
	char songToSkip[30];
	node *ptr = head;

	cout << "\nEnter the song you want to skip (Use #1 on list for functionality)" << endl; 
	cin.clear();
	cin.ignore();
	gets_s(songToSkip);

	while (ptr != NULL)
	{
		if (strcmp(songToSkip, ptr->songName) == 0)
		{
			cout << "\nSkipping:" << ptr->songName << endl;
			printf("Artist: %s\nSong: %s", ptr->artistName, ptr->songName);
			ptr = ptr->next;
			if (ptr->songName)
			{
				cout << "\n\nCurrently Playing:" << endl;
				printf("Artist: %s\nSong: %s", ptr->artistName, ptr->songName);
				break;
			}
		}
	}
}

int main()
{
	linkedList *mylist = new linkedList();

	char fileName[30];
	char answer;

	cout << "Enter File Name: (SongList.txt) " << endl;
	gets_s(fileName);

	mylist->readList(fileName);

	while (true)
	{
		mylist->showList();

		cout << "Welcome to MyPod!!\nHow would you like to proceed?\n" << endl;
		cout << "Play Song -----> [P]" << endl;
		cout << "Skip Song -----> [S]" << endl;
		cout << "Remove Song ---> [R]" << endl;
		cout << "Exit Program --> [E]" << endl;
		cin >> answer;

		if ((answer == 'P') || (answer == 'p'))
		{
			mylist->playCurrentSong();
		}
		else if ((answer == 'S') || (answer == 's'))
		{
			mylist->skipCurrentSong();
		}
		else if ((answer == 'R') || (answer == 'r'))
		{
			if (mylist->removeSong())
			{
				mylist->showList();
			}
		}
		else if ((answer == 'E') || (answer == 'e'))
		{
			break;
		}
		else
		{
			cout << "INVALID RESPONSE!!" << endl;
		}
	}

	return 0;
}