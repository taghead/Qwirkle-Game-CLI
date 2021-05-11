
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
  this->colour = colour;
  this->shape = shape;
}

char Tile::getTileColour()
{
  return this->colour;
}

int Tile::getTileShape()
{
  return this->shape;
}