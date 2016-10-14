//
// Created by franspaco on 12/10/16.
//

#include <cstdlib>
#include <iostream>
#include "Rectangle.h"

Rectangle::Rectangle() {


}

Rectangle::~Rectangle() {

}

Rectangle::Rectangle(int winX, int winY) {
    srand(time(NULL));

    width = getRandom( winX - 20) + 20;
    height = getRandom( winY - 20) +20 ;

    posX = getRandom(winX - width);
    posY = getRandom(winY - height);

    color = sf::Color(getRandom(155)+100, getRandom(255), getRandom(255));
}

Rectangle::Rectangle(int _posX, int _posY, int _width, int _height, sf::Color _color) {
    posX = _posX;
    posY = _posY;
    width = _width;
    height = _height;
    //color = new sf::Color(R, G, B);
    color = _color;
}

int Rectangle::getRandom(int max) {
    //generar números de 0 a max
    return rand() % (max + 1);
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






