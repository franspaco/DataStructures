//
// Created by franspaco on 12/10/16.
//

#include <cstdlib>
#include "Rectangle.h"

Rectangle::Rectangle() {


}

Rectangle::~Rectangle() {

}

Rectangle::Rectangle(int winX, int winY) {
    srand(time(NULL));
    posX = getRandom(winX);
    posY = getRandom(winY);

    width = getRandom( winX / 2 );
    height = getRandom( winY / 2) ;

    color = sf::Color(getRandom(255), getRandom(255), getRandom(255));
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






