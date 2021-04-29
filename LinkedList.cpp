#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
#include "Node.h"

#include <iostream>

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
    }else{
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
      //pre should point to node before current;
      Node* prev = nullptr;

      while(counter != index){
        ++counter;
        prev = current;
        current = current->next;
      }

      if(prev == nullptr){
        head = current->next;
      }else{
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