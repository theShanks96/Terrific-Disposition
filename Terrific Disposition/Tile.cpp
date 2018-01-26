#include "Tile.h"

Tile::Tile() {

}
Tile::Tile(std::string description_in) {

}

Tile::~Tile() {

}

std::string Tile::getDescription() {
	return c_descriptionString;
}
void Tile::setDescription(std::string description_in) {
	c_descriptionString = description_in + c_typeFlavourString;
}

std::string Tile::getTypeFlavour() {
	return c_typeFlavourString;
}
void Tile::setTypeFlavour(std::string flavour_in) {
	c_typeFlavourString = flavour_in;
}