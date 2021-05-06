#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
#include "Node.h"

#include <iostream>
#include <string>
#include <random>

LinkedList::LinkedList() {
  head = nullptr;
}

LinkedList::~LinkedList(){
    clear();
}

LinkedList::LinkedList(LinkedList& other){
    head = nullptr;
    for(int i = 0; i < other.size(); ++i){
      Node* node = new Node(*other.getNode(i));
      addNodeBack(node);
    }
}

void LinkedList::populateLinkedList(){
  std::string colours = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  std::string shapes = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
  for ( int c=0; c<AMOUNT_OF_COLORS; c++ ){
    for ( int s=0; s<AMOUNT_OF_SHAPES; s++ ){ 
      for ( int amount=0; amount<AMOUNT_OF_TILES_PER; amount++){
        addFront(new Tile(colours[c], shapes[s]));
      }
    }
  }
}

void LinkedList::shuffleLinkedList(){
  /*
  Set s as LinkedList size
  Set n to the number of times to loop over to as 9
  For loop over s times n
    Generate random number as r greater than 0 and less than LinkedList size
    If r is 0 or greater and r is 0 and less than s
      If head is not null
        Set current to LinkedLists head node
        Set prev to nullptr node

        Set current get node at position r 
        Shift nodes
        Remove current node in LinkedList
        Add current node to front of LinkedList
  */
  int s = size();
  int n = 9;
  for ( int i=0; i < s*n; i++ ){
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, s);
    int r = uniform_dist(randomSeed);

    if(r >= 0 && r < s){
      if(head != nullptr){
        int counter = 0;
        Node* current = head;
        Node* prev = nullptr;

        while(counter != r){
          ++counter;
          prev = current;
          current = current->next;
        }

        if(prev == nullptr){
          head = current->next;
        }
        else{
          prev->next = current->next;
        }

        current->next = head;
        head = current;
      }
    }
  }
}

int LinkedList::size(){
    int length = 0;

    Node* current = head;
    while(current != nullptr){
      ++length;
      current = current->next;
    }
    return length;
}

Tile* LinkedList::getTile(int index){
  Tile* retTile = nullptr;
  if(index >= 0 && index < size()){

    int counter = 0;
    Node* current = head;

    while(counter<index){
      ++counter;
      current = current->next;
    }
    retTile = current->tile;
  }
  return retTile;
}


Node* LinkedList::getNode(int index){
  Node* retNode = nullptr;
  if(index >= 0 && index < size()){

    int counter = 0;
    Node* current = head;

    while(counter<index){
      ++counter;
      current = current->next;
    }
    retNode = current;
  }
  return retNode;
}

void LinkedList::drawTile(LinkedList* tileBag){
  if ( size() < 6 && tileBag->size() != 0){
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, tileBag->size());
    int randomIndex = uniform_dist(randomSeed);
    
    if(randomIndex >= 0 && randomIndex < tileBag->size()){
      if(tileBag->head != nullptr){
        int counter = 0;
        Node* current = tileBag->head;
        Node* prev = nullptr;

        while(counter != randomIndex){
          ++counter;
          prev = current;
          current = current->next;
        }

        if(prev == nullptr){
          tileBag->head = current->next;
        }
        else{
          prev->next = current->next;
        }

        addNodeFront(current);
      }
    }
  }
}

void LinkedList::loadListOfTiles(std::string tileString){
  int count = 0;
    for (std::string::size_type i = 0; i < tileString.size(); i++) {
      // Use every second as a delimeter
      if ( count == 2 ){
        //Convert char to int
        int shapeInt = (int)tileString[i-1] - '0'; 
        addBack(new Tile(tileString[i-2],shapeInt));
        count = 0;
      }
      // Accounts for last tile
      else if ( i == tileString.size()-1){
        //Convert char to int
        int shapeInt = (int)tileString[i] - '0'; 
        addBack(new Tile(tileString[i-1],shapeInt));
      }
      else {
        count++;
      }
    }
}

void LinkedList::testPrintTiles(){
  for ( int i=0; i < size(); i++){
    Node* node = getNode(i);
    std::cout << node->tile->getTileColour() << node->tile->getTileShape() << ",";
  }
}

void LinkedList::addFront(Tile* tile){
  Node* node = new Node(tile, head);
  node->next = head;
  head = node;
}

void LinkedList::addBack(Tile* tile){
  Node* node = new Node(tile, head);
  node->tile = tile;
  node->next = nullptr;

  if(head == nullptr){
      head = node;
  }
  else{
    Node* current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = node;
  }
}

void LinkedList::addNodeFront(Node* node){
  node->next = head;
  head = node;
}

void LinkedList::addNodeBack(Node* node){
  node->next = nullptr;

  if(head == nullptr){
    head = node;
  }else{
    Node* current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = node;
  }
}

void LinkedList::removeFront(){
  Node* toDelete = head;
  head = head->next;

  delete toDelete->tile;
  delete toDelete;
}


void LinkedList::removeBack(){
  if(head != nullptr){
    Node* current = head;
    Node* prev = nullptr;

    while(current->next != nullptr){
      prev = current;
      current = current->next;
    }

    if(prev == nullptr){
      head = nullptr;
    }
    else{
      prev->next = nullptr;
    }

    delete current->tile;
    delete current;
  }
}


void LinkedList::remove(int index){
  if(index >= 0 && index < size()){
    if(head != nullptr){
      int counter = 0;
      Node* current = head;
      Node* prev = nullptr;

      while(counter != index){
        ++counter;
        prev = current;
        current = current->next;
      }

      if(prev == nullptr){
        head = current->next;
      }
      else{
        prev->next = current->next;
      }

      delete current->tile;
      delete current;
    }
  }
}

void LinkedList::clear(){
    while(head != nullptr){
        removeFront();
    }
}