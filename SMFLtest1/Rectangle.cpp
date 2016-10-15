/*
 * Francisco Huelsz
 * A01019512
 * SFML Test
 */

#include "Rectangle.h"

Rectangle::Rectangle() {

}

Rectangle::~Rectangle() {

}

Rectangle::Rectangle(int _posX, int _posY, int _width, int _height, sf::Color _color) {
    posX = _posX;
    posY = _posY;
    width = _width;
    height = _height;
    color = _color;
}

void Rectangle::createRandom(int winX, int winY) {
    width  = getRandom( winX - 20) + 20;
    height = getRandom( winY - 20) + 20;

    posX = getRandom(winX - width);
    posY = getRandom(winY - height);

    randomColor();
}

int Rectangle::getRandom(int max) {
    //generar números de 0 a max
    int out = (std::rand() % (max + 1));
    return out;
}

int Rectangle::getHeight() {
    return height;
}

int Rectangle::getWidth() {
    return width;
}

int Rectangle::getPosY() {
    return posY;
}

int Rectangle::getPosX() {
    return posX;
}

sf::Color Rectangle::getColor() {
    return color;
}

void Rectangle::print() {
    std::cout << "[ " << posX << ", " << posY <<" ]\n";
    std::cout << "[ " << width << ", " << height <<" ]\n";
}

std::ostream &operator<<(std::ostream &stream, const Rectangle & rectangle) {
    stream << "[ " << rectangle.posX << ", " << rectangle.posY <<" ] - ";
    stream << "[ " << rectangle.width << ", " << rectangle.height <<" ]";
    return stream;
}

void Rectangle::setHeight(int inpt) {
    height = inpt;
}

void Rectangle::setWidth(int inpt) {
    width = inpt;
}

void Rectangle::setPosY(int inpt) {
    posY = inpt;
}

void Rectangle::setPosX(int inpt) {
    posX = inpt;
}

void Rectangle::randomColor() {
    color = sf::Color(getRandom(255), getRandom(255), getRandom(255));
}






