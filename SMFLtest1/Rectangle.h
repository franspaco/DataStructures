/*
 * Francisco Huelsz
 * A01019512
 * SFML Test
 */

#ifndef SMFLTEST1_RECTANGLE_H
#define SMFLTEST1_RECTANGLE_H


#include <SFML/Graphics/Color.hpp>
#include <ctime>
#include <iostream>
#include <cstdlib>

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
    Rectangle(int _posX, int _posY, int _width, int _height, sf::Color _color);

    void createRandom(int winX, int winY);
    void setPosX(int inpt);
    void setPosY(int inpt);
    void setWidth(int inpt);
    void setHeight(int inpt);
    int getPosX();
    int getPosY();
    int getWidth();
    int getHeight();

    void randomColor();

    sf::Color getColor();
    void print();
    friend std::ostream & operator << (std::ostream & stream, const Rectangle & rectangle);
};


#endif //SMFLTEST1_RECTANGLE_H
