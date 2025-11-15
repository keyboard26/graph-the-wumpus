#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <random>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //seed for random stuff

	//create graph and all the rooms
	Graph dungeon;

	dungeon.generateConnections();
	

	//put the player and the wumpus in a room to start
	int currentRoom = 0;
	int wumpusRoom = rand() % 11 + 8;

	//player has 3 arrows
	int quiver[3]{}; //array to keep track of where they are
		// -21 means the arrow is unretrievable
		// negative version of room number mean player doesn't have it on them

	int arrows = 3; //int keeps track of how many the player actually has

	//list to keep the connections
	DoubleLinkedList<Room*>* connections;


	// ~~ title caaard ~~
	std::cout <<
	"========================================" <<
	"\n\n               welcome to\n\n" <<
	"       !! ~~ HUNT THE WUMPUS ~~ !!" <<
	"\n\n                 a game\n\n" <<
	"========================================\n\n\n";

	


	bool reset = true;
	int choice{};

	while (true) {
		if (reset) {
			dungeon.assignHazards(); //new game, assign hazards 

			currentRoom = 0;

			std::cout << "\n\nYou are standing at the entrance to a cave.\n" <<
				"There are multiple dark tunnels ahead of you.\n\n";


			reset = false;
		}



		std::cout << "You are in room " << currentRoom << "\n";
		std::cout << "Tunnels lead to ";
		dungeon.printConnections(currentRoom);
		//std::cout << "\n";

		//what do they want to do
		std::cout << "You can...\n" <<
			"   1. Move to another room\n" <<
			"   2. Attack (" << arrows << " arrows remaining)\n" <<
			"   3. Observe the tunnels\n";
		std::cin >> choice;

		//invalid choice
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
			std::cout << "\nInvalid choice, try again. ";
			std::cin >> choice;
		}





		// === MOVE ===
		if (choice == 1) {
			/*
			Rules for Move
				What each room means:
					bottomless pit = lose immediately
					bats = disoriented, put into a random connected room
					wumpus = it attacks you
						if you have arrows, you fire one
						if you have none, you lose
			*/

			connections = dungeon.inEdges(currentRoom);

			//pick a room to move to
			std::cout << "Pick a room: ";
			std::cin >> choice;

			//invalid choice
			while ((*connections).find(dungeon.getRoom(choice)) == nullptr) {
				std::cout << "Invalid choice, please enter one of the following: "; 
				dungeon.printConnections(currentRoom);
				std::cin >> choice;
			}

			currentRoom = choice;

			//move the arrows the person has with them
			for (int i = 0; i < 3; i++) {
				if (quiver[i] >= 0) {
					quiver[i] = currentRoom;
				}
			}

			// === Move into Bat Room ===
			if (dungeon.getRoom(currentRoom)->data == "BAT") {
				//get disoriented, move to random connected room

				int index = rand() % connections->size(); //random connection
				//move there
				currentRoom = connections->seeAt(index)->getData()->num; 

				std::cout << "Uh oh! There's swarm of bats in here!\n" <<
					"You get disoriented and run to room " << currentRoom << "!\n";
			}

			// === Move into Bottomless Pit ===
			else if (dungeon.getRoom(currentRoom)->data == "PIT") {
				//fall in and die

				std::cout << "Oh no! You fell into a bottomless pit!\n";

				// Play again?
				std::string answer = "";
				std::cout << "\n\nPlay again? (y/n) ";
				std::cin >> answer;

				if (answer == "y") {
					reset = true;
					continue;  
				}
				else {
					//game over
					break;
				}
			}

			// === Move into Wumpus Room ===
			else if (currentRoom == wumpusRoom) {
				//it attacks you, see what happens

				std::cout << "Woah! You found the wumpus!\n" <<
					"It attacks you!!\n";

				if (arrows == 0) {
					std::cout << "But oh no! You're out of arrows!\n";

					// Play again?
					std::string answer = "";
					std::cout << "\n\nPlay again? (y/n) ";
					std::cin >> answer;

					if (answer == "y") {
						reset = true;
						continue;  
					}
					else {
						//game over
						break;
					}
				}
				else {
					//update player's arrows
					arrows--;
					quiver[arrows] = -21; //should this arrow be lost forever? i think so but idk

					std::cout << "You fire an arrow! (" << arrows << " remaining)\n" <<
						"It misses, but it scares off the Wumpus.\n";
				}
			}

			// === empty room ===
			else {
				bool arrowFound = false;
				//see if there's an arrow in here for the player to pick up
				for (int i = 0; i < 3; i++) {
					if ((-1 * quiver[i]) == currentRoom) {
						arrows++;
						quiver[i] = currentRoom;
						arrowFound = true;
						std::cout << "The room is empty, but...\n";
						std::cout << "You found one of your arrows!\n" << 
							"You now have " << arrows << "arrow" << (arrows == 1 ? "" : "s") << "\n";
					}
				}
				if (!arrowFound && arrows!= 3) {
					std::cout << "The room is completely empty, none of your arrows landed here.\n";
				}
				else if(arrows == 3){
					std::cout << "The room is completely empty.\n";
				}

				//now the wumpus has to move around
				connections = dungeon.inEdges(wumpusRoom);
				int moveto{};

				for (int i = 0; i < connections->size(); i++) {
					//make sure it doesn't move into the player
					if (connections->seeAt(i)->getData()->num != currentRoom) {
						moveto = connections->seeAt(i)->getData()->num;
						wumpusRoom = moveto;
						break;
					}
					else {
					}
				}

			}


			

			
		}
		// === END MOVE ===




		// === ATTACK ===
		else if (choice == 2) {
			/*
			Arrow rules:
				can go 2-4 rooms
				cannot circle back / travel through a room it's been in
				if it goes through the wumpus room, you win

				You can retrive arrows UNLESS:
					if falls in a bat room
					or into a bottomless pit
			*/

			//arrow can go 2 - 4 rooms
			//cannot circle back

			if (arrows == 0) {
				std::cout << "You are out of arrows, you can't attack.\n";
			}
			else {
				arrows--;

				connections = dungeon.inEdges(currentRoom);


				std::cout << "Which room do you want to shoot towards? ";
				std::cin >> choice;

				//invalid choice
				while ((*connections).find(dungeon.getRoom(choice)) == nullptr) {
					std::cout << "Invalid choice, try again. ";
					std::cin >> choice;
				}


				//tell the player how many rooms the arrow goes through
				int distance = 1;
				int maxDistance = rand() % 3 + 2; //gives [2,4]

				int roomNum = choice;


				// === IMMEDIATE CHECK ON FIRST ROOM ===
				std::string thing = dungeon.getRoom(roomNum)->data;
				if (roomNum == wumpusRoom) {
					std::cout << "You shot the Wumpus!!\nYou win!\n";
					quiver[arrows] = -21;
					std::string answer;
					std::cout << "\n\nPlay again? (y/n) ";
					std::cin >> answer;
					if (answer == "y") {
						reset = true;
						continue;
					}
					else {
						break;
					}
				}
				else if (thing == "BAT") {
					std::cout << "Your arrow hit some bats and broke.\n";
					quiver[arrows] = -21;
					continue; // skip rest of arrow flight
				}
				else if (thing == "PIT") {
					std::cout << "Your arrow fell into a bottomless pit and is gone forever.\n";
					quiver[arrows] = -21;
					continue;
				}

				//now check the rooms to could move into....

				//keep track of the rooms it's been in
				int hitRooms[4]{};
				hitRooms[0] = currentRoom;
				hitRooms[1] = choice;
				int hitCount = 2;


				bool stopArrow = false;
				while (distance < maxDistance && !stopArrow) {
					connections = dungeon.inEdges(roomNum);
					bool moved = false, hitSomething = false;

					for (int i = 0; i < connections->size(); i++) { //go through each connected room
						int nextNum = (*connections).seeAt(i)->getData()->num; //store a possible room to move to

						bool alreadyVisited = false;

						//see if arrow has been there already
						for (int j = 0; j < hitCount; j++) {
							if (hitRooms[j] == nextNum) {
								alreadyVisited = true; //so can't go into this room
								break;
							}
						}

						if (!alreadyVisited) {
							roomNum = nextNum;
							hitRooms[distance] = roomNum;
							distance++;
							hitCount++;
							moved = true;

							//put the arrow in the new room 
							quiver[arrows] = -1 * nextNum; // negative so i can tell the player doesn't have it

							//see if anyhting happens to the arrow
							std::string thing = dungeon.getRoom(roomNum)->data;
							if (roomNum == wumpusRoom) {
								//yay you win the game 
								stopArrow = true;
								std::cout << "You shot the Wumpus!!\nYou win!\n";
								
								// Play again?
								std::string answer = "";
								std::cout << "\n\nPlay again? (y / n) ";
								std::cin >> answer;

								if (answer == "y") {
									reset = true;
									continue;  
								}
								else {
									//game over
									break;
								}
							}
							else if (thing == "BAT") {
								std::cout << "Your arrow hit some bats and broke.\n";
								quiver[arrows] = -21;
								hitSomething = true;
								stopArrow = true;
							}
							else if (thing == "PIT") {
								std::cout << "Your arrow fell into a bottomless pit and is gone forever.\n";
								quiver[arrows] = -21;
								hitSomething = true;
								stopArrow = true;
							}
							break;
						}
					}


					if (hitSomething) {
						break;
					}
					else if (!moved) {
						std::cout << "The arrow fell to the ground.\n";
						break;
					}			

				}
				std::cout << "Your arrow flew through " << distance << " room" << (distance == 1 ? "" : "s") << ".\n";

			}
		}
		// === END ATTACK ===






		// === OBSERVE ===
		else if (choice == 3) {
			/*
			Observing stuff
				get feedback on what could be in neighboring rooms
				does not give specific tunnel

				What info you can get:
					Bats = screeching noise
					Pit = feel a breeze
					Wumpus = stinky
			*/

			connections = dungeon.inEdges(currentRoom);
			bool something = false;

			if (currentRoom == wumpusRoom) {
				std::cout << "You smell something stinky...\n";
				something = true;
			}
			for (int i = 0; i < connections->size(); i++) {
				if (connections->seeAt(i)->getData()->data == "PIT") {
					std::cout << "You feel a breeze.\n";
					something = true;
				}
				else if (connections->seeAt(i)->getData()->data == "BAT") {
					std::cout << "You hear screeching.\n";
					something = true;
				}
			}

			if (!something) {
				std::cout << "You don't notice anything.\n";
			}
		}
		// === END OBSERVE ===



		// === QUIT ===
		else if (choice == 4) {
			break;
		}
		std::cout << "\n\n";
	}
}