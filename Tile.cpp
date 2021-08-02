#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape)
{
  this->colour = colour;
  this->shape = shape;
}

Tile::Tile(Tile &otherTile)
{
  colour = otherTile.colour;
  shape = otherTile.shape;
}

Colour Tile::getColour()
{
  return colour;
}

Shape Tile::getShape()
{
  return shape;
}

// Gets tiles codes and returns as a string
std::string Tile::toString()
{
  std::string shapeCode = "";
  if (shape == CIRCLE)
  {
    shapeCode = "1";
  }
  else if (shape == STAR_4)
  {
    shapeCode = "2";
  }
  else if (shape == DIAMOND)
  {
    shapeCode = "3";
  }
  else if (shape == SQUARE)
  {
    shapeCode = "4";
  }
  else if (shape == STAR_6)
  {
    shapeCode = "5";
  }
  else if (shape == CLOVER)
  {
    shapeCode = "6";
  }
  return colour + shapeCode;
}
