# Graph the Wumpus

**A data structures class project: Hunt the Wumpus using graphs**  

---

## Overview

Graph the Wumpus is a game inspired by the classic *Hunt the Wumpus*. Players navigate a network of rooms connected via a graph, trying to avoid hazards like bottomless pits, bats, and the Wumpus itself while strategically moving and shooting arrows.  

This project was created with a partner for my **Data Structures** class, with a focus on implementing and utilizing **graph data structures** for room connections and game logic.

---

## Gameplay

- Navigate through a series of interconnected rooms.  
- Avoid hazards:
  - **Bottomless Pits** — falling in ends the game.  
  - **Bats** — move you to a random connected room.  
  - **The Wumpus** — you must avoid or hunt it with arrows.  
- Players can move or shoot arrows through the graph to try to defeat the Wumpus.  
- The game ends when the player either defeats the Wumpus or encounters a fatal hazard.

---

## Features

- Rooms and hazards are represented using a **graph data structure**.  
- Dynamic hazard placement that avoids the starting room.  
- Arrow shooting and pathfinding across connected rooms.  
- Text-based UI providing room connections and warnings for nearby hazards.  
- Implemented using **C++** with custom classes for `Graph`, `Room`, and hazards.  

---

## Data Structures Used

- **Graph** — represents rooms and connections.  
- **Nodes / Rooms** — each node stores its connections and hazards.  
- **Doubly Linked List** — used for efficient room/hazard management.  
- **Custom classes** — for modularity and encapsulation of game logic.  


