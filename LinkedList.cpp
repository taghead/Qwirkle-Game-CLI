#include "LinkedList.h"

LinkedList::LinkedList()
{
  head = nullptr;
  tail = nullptr;
  size = 0;
}

LinkedList::~LinkedList()
{
  // clear();
  // delete head;
  // delete tail;
}

void LinkedList::addFront(Tile *tile)
{
  Node *tmp = new Node(tile, head, nullptr);
  if (head == nullptr)
  {
    head = tmp;
    tail = tmp;
  }
  else
  {
    head = tmp;
  }
  size++;
}

void LinkedList::addBack(Tile *tile)
{
  Node *tmp = new Node(tile, nullptr, tail);
  if (head == nullptr)
  {
    head = tmp;
    tail = tmp;
    tmp = nullptr;
  }
  else
  {
    tail->next = tmp;
    tail = tmp;
  }
  size++;
}

void LinkedList::deleteFront()
{
  Node *tmp = head;
  head = head->next;
  delete tmp;
  size--;
}

void LinkedList::deleteBack()
{
  Node *tmp = tail;
  tail = tail->prev;
  delete tmp;
  size--;
}

void LinkedList::deleteAt(int pos)
{
  if (pos > size)
  {
    return;
  }
  if (pos == 0)
  {
    deleteFront();
  }
  else if (pos == size - 1)
  {
    deleteBack();
  }
  else
  {
    Node *curr = head;
    for (int i = 0; i < pos; i++)
    {
      curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    size--;
  }
}

int LinkedList::getSize()
{
  return size;
}

Node *LinkedList::getNode(Tile *tile)
{
  Node *foundNode = nullptr;
  Node *curr = head;
  while (curr != nullptr && foundNode == nullptr)
  {
    if (curr->getTile() == tile)
    {
      foundNode = curr;
    }
    curr = curr->next;
  }
  return foundNode;
}

Node *LinkedList::getNodeAt(int index)
{
  Node *foundNode = nullptr;
  Node *curr = head;
  int i = 0;
  while (i < index)
  {
    curr = curr->next;
    i++;
  }
  foundNode = curr;
  return foundNode;
}

Tile *LinkedList::getTileAt(int index)
{
  int i = 0;
  Node *curr = head;
  Tile *tile;
  while (i < index)
  {
    curr = curr->next;
    i++;
  }
  tile = curr->getTile();
  return tile;
}

std::string LinkedList::toStringBoard()
{
  std::string listString;
  Node *curr = head;
  if (size > 0)
  {
    for (int i = 0; i < size; i++)
    {
      listString += (curr->getTile()->toString() + " ");
      curr = curr->next;
    }
  }
  return listString;
}

std::string LinkedList::toStringHand()
{
  std::string listString;
  Node *curr = head;
  if (size > 0)
  {
    for (int i = 0; i < size - 1; i++)
    {
      listString += (curr->getTile()->toString() + ",");
      curr = curr->next;
    }
    listString += curr->getTile()->toString();
  }

  return listString;
}

void LinkedList::clear()
{
  while (this->head != nullptr)
  {
    Node *toDelete = this->head;
    head = toDelete->next;
    delete toDelete;
  }
  tail = nullptr;
}
