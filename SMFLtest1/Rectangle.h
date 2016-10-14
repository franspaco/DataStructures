//
// Created by franspaco on 12/10/16.
//

#ifndef SMFLTEST1_RECTANGLE_H
#define SMFLTEST1_RECTANGLE_H


#include <SFML/Graphics/Color.hpp>
#include <time.h>

class Rectangle {
private:
    int posX;
    int posY;
    int width;
    int height;
    sf::Color color;
    int getRandom(int max);
public:
    Rectangle();
    ~Rectangle();
    Rectangle(int winX, int winY);
    Rectangle(int _posX, int _posY, int _width, int _height, sf::Color _color);
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();
    sf::Color getColor();
};


#endif //SMFLTEST1_RECTANGLE_H
