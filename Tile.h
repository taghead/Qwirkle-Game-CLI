#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
  Tile(Colour colour, Shape shape);
  Tile(Tile &otherTile);

  // Getters
  Colour getColour();
  Shape getShape();

  // To String
  std::string toString();

private:
  Colour colour;
  Shape shape;
};

#endif