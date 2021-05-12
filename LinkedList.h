
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

#include "Node.h"
#include "TileCodes.h"

class LinkedList
{
public:
  LinkedList();
  ~LinkedList();
  LinkedList(LinkedList &other);

  /*
  Create a new tile bag. Qwirkle contains 108 tiles. Colors*Shapes*3.
  Used to populate the Qwirkle Tile Bag to the new game capacity.

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  */
  void populateLinkedList();

  /*
  Shuffles around all the nodes in a LinkedList

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  tileBag->shuffleLinkedList();
  */
  void shuffleLinkedList();

  /*
  Obtains size of LinkedList by counting each node in a LinkedList

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  std::cout << tileBag->size();
  */
  int size();

  /*
  Get the tile from a specific node in the LinkedList based on index position.

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  Tile* tile = tileBag->getTile(5);
  std::cout << tile->getTileColour() << tile->getTileShape();
  */
  Tile *getTile(int index);

  /*
  Get a specific node from the LinkedList based on index position

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  Node* node = tileBag->getNode(5);
  std::cout << node->tile->getTileColour() << node->tile->getTileShape();
  */
  Node *getNode(int index);

  /*
  Migrate a cap of 6 random nodes from the overloaded LinkedList (tileBag).
  
  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  LinkedList* playerHand = new LinkedList();
  playerHand->drawTile(tileBag);
  */
  void drawTile(LinkedList *tileBag);

  /*
  Locate the first instance of a spcified tile and migrate that tile to a
  new LinkedList
  
  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  LinkedList* playerHand = new LinkedList();
  playerHand->drawTile(tileBag);
  playerHand->replaceTile("P5", tilebag);
  */
  void replaceTile(std::string tile, LinkedList *tileBag);

  /*
  Migrate a random node from the overloaded LinkedList.
  
  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  LinkedList* playerHand = new LinkedList();
  playerHand->drawTile(tileBag);
  */
  void drawHand(LinkedList *tileBag);

  /*
    Load an tiles from a string

    LinkedList* playerHand = new LinkedList();
    std::string playerHandTiles = "P2,P3,O6,Y4,B2,O3";
    playerHand->loadListOfTiles(playerHandTiles);
    playerHand->testPrintTiles();
  */
  void loadListOfTiles(std::string tileString);

  /*
  Prints LinkedList in player hand format
  
  LinkedList* playerHand = new LinkedList();
  playerHand->populateLinkedList();
  playerHand->printHand();
  */
  void printHand();

  /*
  Returns LinkedList in player hand format as a string
  
  LinkedList* playerHand = new LinkedList();
  playerHand->populateLinkedList();
  playerHand->printHand();
  */
  std::string printHandToString();

  void remove(int index);
  /*
  FOR TESTING - Print all tiles in a LinkedList

  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();
  tileBag->testPrintTiles();
  */
  void testPrintTiles();

private:
  Node *head;
  void addFront(Tile *tile);
  void addBack(Tile *tile);
  void addNodeBack(Node *node);
  void addNodeFront(Node *node);
  void removeFront();
  void removeBack();
  void clear();
};

#endif // ASSIGN2_LINKEDLIST_H
