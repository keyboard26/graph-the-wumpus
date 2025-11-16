#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "linkedList.h"

const int NUM_ROOMS = 20;

class Room {
public:
	int num{};
	std::string data;
	DoubleLinkedList<Room*> tunnels;

	// === Constructors ===
	Room() {
		data = "";
		num = 0;
	}

	Room(int i, std::string s) {
		data = s;
		num = i;
	}

	void setRoomData(std::string s) {
		data = s;
	}

	// === Operator Overloads ===
	bool operator ==(const Room& a) {
		return num == a.num;
	}
	bool operator !=(const Room& a) {
		return num != a.num; //throwing a read access violation because "this was nullptr"
	}

	bool operator >(const Room& a) {
		return num > a.num;
	}

	bool operator <(const Room& a) {
		return num < a.num;
	}
};



class Graph {
private:
	DoubleLinkedList<Room*> rooms;

public:
	// === Destructor ===
	~Graph() {
		for(int i = 0; i < rooms.size(); i++) {
			delete rooms.seeAt(i)->getData();
		}
	}

	// === addTunnel ===
	bool addTunnel(Room* A, Room* B) {
		if (!hasTunnel(A, B) && A->tunnels.size() < 4 && B->tunnels.size() < 4) {
			A->tunnels.addItem(B);
			B->tunnels.addItem(A);
			return true;
		}
		return false;
	}

	// === removeTunnel ===
	void removeTunnel(Room* A, Room* B) {
		if (hasTunnel(A, B)) {
			A->tunnels.remove(B);
			B->tunnels.remove(A);
		}
	}

	// === hasTunnel ===
	bool hasTunnel(Room* A, Room* B) {
		if (A == nullptr || B == nullptr) {
			return false;
		}
		return A->tunnels.find(B) != nullptr;
	}

	// === addRoom ===
	void addRoom(Room* A) {
		rooms.addItem(A);
	}

	// === inEdges / outEdges ===
	//returns a list of all tunnels that go into a room
	DoubleLinkedList<Room*>* inEdges(int index) {
		DoubleNode<Room*>* A = rooms.seeAt(index);

		//return a pointer to the actual list of rooms so that i can mess with it in main
		DoubleLinkedList<Room*>* temp = new DoubleLinkedList<Room*>(A->getData()->tunnels);
		return temp;
	}

	// === setRoom ===
	void setRoom(int index, const std::string& str) {
		DoubleNode<Room*>* temp = rooms.seeAt(index);
		if (temp) {
			temp->getData()->setRoomData(str);
		}
	}

	// === getRoom ===
	Room* getRoom(int index) {
		DoubleNode<Room*>* temp = rooms.seeAt(index);

		if (temp) {
			return temp->getData();
		}
		return nullptr;
	}

	// === generateConnections ===
	void generateConnections() {
		//make sure we have 20 rooms
		for (int i = 0; i < NUM_ROOMS; i++) {
			addRoom(new Room(i, ""));

		}

		// 0: 1, 7, 5
		addTunnel(getRoom(0), getRoom(1));
		addTunnel(getRoom(0), getRoom(7));
		addTunnel(getRoom(0), getRoom(5));


		// 1: 0, 2, 6
		addTunnel(getRoom(1), getRoom(0));
		addTunnel(getRoom(1), getRoom(2));
		addTunnel(getRoom(1), getRoom(6));

		// 2: 1, 3, 8
		addTunnel(getRoom(2), getRoom(1));
		addTunnel(getRoom(2), getRoom(3));
		addTunnel(getRoom(2), getRoom(8));

		// 3: 2, 8, 4
		addTunnel(getRoom(3), getRoom(2));
		addTunnel(getRoom(3), getRoom(8));
		addTunnel(getRoom(3), getRoom(4));

		// 4: 3, 9, 14
		addTunnel(getRoom(4), getRoom(3));
		addTunnel(getRoom(4), getRoom(9));
		addTunnel(getRoom(4), getRoom(14));

		// 5: 0, 12, 10
		addTunnel(getRoom(5), getRoom(0));
		addTunnel(getRoom(5), getRoom(12));
		addTunnel(getRoom(5), getRoom(10));

		// 6: 1, 7, 11
		addTunnel(getRoom(6), getRoom(1));
		addTunnel(getRoom(6), getRoom(7));
		addTunnel(getRoom(6), getRoom(11));

		// 7: 0, 6
		addTunnel(getRoom(7), getRoom(0));
		addTunnel(getRoom(7), getRoom(6));

		// 8: 2, 3, 13
		addTunnel(getRoom(8), getRoom(2));
		addTunnel(getRoom(8), getRoom(3));
		addTunnel(getRoom(8), getRoom(13));

		// 9: 4, 19
		addTunnel(getRoom(9), getRoom(4));
		addTunnel(getRoom(9), getRoom(19));

		// 10: 5, 11, 15
		addTunnel(getRoom(10), getRoom(5));
		addTunnel(getRoom(10), getRoom(11));
		addTunnel(getRoom(10), getRoom(15));

		// 11: 6, 10, 12, 17
		addTunnel(getRoom(11), getRoom(6));
		addTunnel(getRoom(11), getRoom(10));
		addTunnel(getRoom(11), getRoom(12));
		addTunnel(getRoom(11), getRoom(17));

		// 12: 5, 11, 13, 17
		addTunnel(getRoom(12), getRoom(5));
		addTunnel(getRoom(12), getRoom(11));
		addTunnel(getRoom(12), getRoom(13));
		addTunnel(getRoom(12), getRoom(17));

		// 13: 12, 8, 14, 18
		addTunnel(getRoom(13), getRoom(12));
		addTunnel(getRoom(13), getRoom(8));
		addTunnel(getRoom(13), getRoom(14));
		addTunnel(getRoom(13), getRoom(18));

		// 14: 13, 4
		addTunnel(getRoom(14), getRoom(13));
		addTunnel(getRoom(14), getRoom(4));

		// 15: 10, 16
		addTunnel(getRoom(15), getRoom(10));
		addTunnel(getRoom(15), getRoom(16));

		// 16: 15, 12
		addTunnel(getRoom(16), getRoom(15));
		addTunnel(getRoom(16), getRoom(17));

		// 17: 11, 12, 18
		addTunnel(getRoom(17), getRoom(11));
		addTunnel(getRoom(17), getRoom(12));
		addTunnel(getRoom(17), getRoom(18));

		// 18: 13, 17, 19
		addTunnel(getRoom(18), getRoom(13));
		addTunnel(getRoom(18), getRoom(17));
		addTunnel(getRoom(18), getRoom(19));

		// 19: 14, 18
		addTunnel(getRoom(19), getRoom(9));
		addTunnel(getRoom(19), getRoom(18));
	}


	// === printConnections ===
	void printConnections(int index) {
		Room* r = getRoom(index);

		//std::cout << "Room: " << r->num << " \t-->\t";

		if (r->tunnels.size() == 0) {
			std::cout << "None";
		}
		else {
			for (int i = 0; i < r->tunnels.size(); i++) {
				std::cout << r->tunnels.seeAt(i)->getData()->num << "  ";
			}
		}
		std::cout << "\n";		
	}

	// === assignHazards ===
	void assignHazards() {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		int pit{}, bat{}, wumpus{};

		//get three unique ints
		while (pit == bat || pit == wumpus || bat == wumpus) {
			pit = rand() % 19 + 1;
			bat = rand() % 19 + 1;
			wumpus = rand() % 19 + 1;
		}

		//label the rooms at those indeces
		auto node = rooms.seeAt(pit);
		if (node) {
			node->getData()->setRoomData("PIT");
		}
		node = rooms.seeAt(bat);
		if (node) {
			node->getData()->setRoomData("BAT");
		}
	}
};
