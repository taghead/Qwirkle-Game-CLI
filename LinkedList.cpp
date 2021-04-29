#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
#include "Node.h"

#include <iostream>

LinkedList::LinkedList() {
  head = nullptr;

  // TODO
}

LinkedList::~LinkedList() {
}

void LinkedList::populateLinkedList(){
  std::string colours = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  std::string shapes = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
  for ( int c=0; c<AMOUNT_OF_COLORS; c++ ){
    for ( int s=0; s<AMOUNT_OF_SHAPES; s++ ){ 
      for ( int amount=0; amount<AMOUNT_OF_TILES_PER; amount++){
        add_front(new Tile(colours[c], shapes[s]));
      }
    }
  }
}

void LinkedList::add_front(Tile* tile){
    Node* node = new Node(tile, head);
    node->next = head;
    head = node;
}

void LinkedList::add_back(Tile* tile){
    Node* node = new Node(tile, head);
    node->tile = tile;
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
