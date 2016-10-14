#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "LinkedList.h"
#include "Rectangle.h"

#define WINDOWX  600
#define WINDOWY  600

template<class T>
void pln(T thing) {
    //lazy printing method
    std::cout << thing << std::endl;
}

bool inside = true;
LinkedList<Rectangle> rekts;
LinkedList<sf::RectangleShape> sfrekts;

void consoleInput(){
    char inpt = '0';
    do{
        pln("Select an option:");
        pln("1 - insert random");
        pln("2 - insert manually");
        pln("q - Quit");
        std::cin >> inpt;
        sf::RectangleShape temp;
        switch(inpt){
            case '1':
                rekts.put(Rectangle(WINDOWX, WINDOWY));
                break;
            case '2':

                break;
            case 'q':
                break;
            default:
                break;
        }
    }while(inpt != 'q');
    inside = false;
}

int main()
{
    std::thread * thread1 = new std::thread(consoleInput);

    std::cout << "INITIALIZING WINDOW" << std::endl;
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "SFML works!");

    window.setFramerateLimit(60);

    while (window.isOpen() && inside)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                delete thread1;

            }
        }
        window.clear();
        //window.draw(shape);

        int length = rekts.getLength();

        for(int i = 0; i < length; i++){
            Rectangle r = rekts.getDataAtPosition(i);
            sf::RectangleShape temp;
            temp.setSize(sf::Vector2f(r.getWidth(), r.getHeight()));
            temp.setFillColor(r.getColor());
            temp.setPosition(r.getPosX(), r.getPosY());
            window.draw(temp);
        }

        Rectangle r(50, 50, 50, 50, sf::Color(255, 0, 0));
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(r.getWidth(), r.getHeight()));
        rectangle.setFillColor(r.getColor());
        rectangle.setPosition(r.getPosX(), r.getPosY());

        window.draw(rectangle);

        window.display();
    }

    thread1->join();
    std::cout << "BYE!\n";
    return 0;
}
