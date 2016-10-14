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
    int temp = 0;
    do{
        pln("Select an option:");
        pln("1 - insert random");
        pln("2 - insert manually");
        pln("3 - delete rectangle");
        pln("4 - delete last");
        pln("5 - print rectangle list");
        pln("d - drop all");
        pln("q - Quit");
        std::cin >> inpt;
        switch(inpt){
            case '1':
                rekts.put(Rectangle(WINDOWX, WINDOWY));
                break;
            case '2':

                break;
            case '3':
                pln("Select index:");
                std::cin >> temp;
                if( (rekts.getLength() > temp) && (temp >= 0) ){
                    rekts.deleteAtPosition(temp);
                } else{
                    pln("Index out of bounds.");
                }
                break;
            case '4':
                if(rekts.getLength() > 0) {
                    rekts.popLast();
                }else{
                    pln("No more rectangles!");
                }
                break;
            case '5':
                rekts.print();
                break;
            case 'd':
                rekts.clear();
                break;
            case 'q':
                break;
            default:
                break;
        }
    }while(inpt != 'q');
    inside = false;
}

int main() {
    std::thread * thread1 = new std::thread(consoleInput);

    std::cout << "INITIALIZING WINDOW" << std::endl;
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "SFML works!");

    window.setFramerateLimit(60);

    while (window.isOpen() && inside)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inside = false;
                //delete thread1;
            }
        }
        window.clear();

        int length = rekts.getLength();

        for(int i = 0; i < length; i++){
            //Draw from list
            Rectangle r = rekts.getDataAtPosition(i);
            sf::RectangleShape temp;
            temp.setSize(sf::Vector2f(r.getWidth(), r.getHeight()));
            temp.setFillColor(r.getColor());
            temp.setPosition(r.getPosX(), r.getPosY());
            window.draw(temp);
        }

        window.display();
    }

    //thread1->join();
    std::cout << "BYE!\n";

    return 0;
}
