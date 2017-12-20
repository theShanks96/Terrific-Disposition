#include "Tile.h"

Tile::Tile() {

}
Tile::Tile(std::string description_in) {

}

Tile::~Tile() {

}

std::string Tile::getDescription() {
	return c_description;
}
void Tile::setDescription(std::string description_in) {
	c_description = description_in + c_typeFlavour;
}

std::string Tile::getTypeFlavour() {
	return c_typeFlavour;
}
void Tile::setTypeFlavour(std::string flavour_in) {
	c_typeFlavour = flavour_in;
}