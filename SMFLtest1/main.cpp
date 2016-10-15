/*
 * Francisco Huelsz
 * A01019512
 * SFML Test
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
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
std::mutex mtx;

void consoleInput(){
    char inpt = '0';
    int temp = 0;
    Rectangle rektTemp;
    do{
        pln("Select an option:");
        pln("1 - insert random");
        pln("2 - insert manually");
        pln("3 - delete rectangle");
        pln("4 - delete last");
        pln("5 - delete first");
        pln("6 - print rectangle list");
        pln("7 - please give me 100 rectangles!");
        pln("d - drop all");
        pln("q - Quit");

        std::cin >> inpt;

        mtx.lock();
        switch(inpt){
            case '1':
                //Insert Random
                rektTemp.createRandom(WINDOWX, WINDOWY);
                rekts.put(rektTemp);
                break;
            case '2':
                //Inser Manual
                pln("Type in X coordinate:");
                std::cin >> temp;
                rektTemp.setPosX(temp);
                pln("Type in Y coordinate:");
                std::cin >> temp;
                rektTemp.setPosY(temp);
                pln("Type in width:");
                std::cin >> temp;
                rektTemp.setWidth(temp);
                pln("Type in height:");
                std::cin >> temp;
                rektTemp.setHeight(temp);
                rektTemp.randomColor();
                rekts.put(rektTemp);
                break;
            case '3':
                //Delete Rectangle with index
                pln("Select index:");
                std::cin >> temp;
                if( (rekts.getLength() > temp) && (temp >= 0) ){
                    rekts.deleteAtPosition(temp);
                } else{
                    pln("Index out of bounds.");
                }
                break;
            case '4':
                //Delete last
                if(rekts.getLength() > 0) {
                    rekts.popLast();
                }else{
                    pln("No more rectangles!");
                }
                break;
            case '5':
                //Delete first
                if(rekts.getLength() > 0) {
                    rekts.pop();
                }else{
                    pln("No more rectangles!");
                }
                break;
            case '6':
                //Print Rectangles
                rekts.print();
                break;
            case '7':
                //make a hundred because we can!
                for(int i = 0; i < 100; i++){
                    rektTemp.createRandom(WINDOWX, WINDOWY);
                    rekts.put(rektTemp);
                }
                break;
            case 'd':
                //Drop all the rectangles
                rekts.clear();
                break;
            case 'q':
                break;
            default:
                break;
        }
        mtx.unlock();
    }while(inpt != 'q');

    inside = false;
}

int main() {
    std::srand(std::time(0));
    std::thread  thread1(consoleInput);

    std::cout << "INITIALIZING WINDOW" << std::endl;
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "SFML works!");
    sf::Font font;

    if(!font.loadFromFile("/usr/share/fonts/truetype/nanum/NanumGothic.ttf")){
        pln("ERROR LOADING FONT");
        exit(-1);
    }

    window.setFramerateLimit(60);

    while (window.isOpen() && inside)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inside = false;
            }
        }
        window.clear();

        int length = rekts.getLength(); //Get list size
        for (int i = 0; i < length; i++) {
            //Draw from list
            try {
                //Just in case something weird happens
                Rectangle r = rekts.getDataAtPosition(i);
                sf::RectangleShape temp;
                temp.setSize(sf::Vector2f(r.getWidth(), r.getHeight()));
                temp.setFillColor(r.getColor());
                temp.setPosition(r.getPosX(), r.getPosY());
                window.draw(temp);

                sf::Text text(std::to_string(i), font, 20);
                text.setPosition(r.getPosX() + r.getWidth() / 2 - 10, r.getPosY() + r.getHeight() / 2 - 10);
                window.draw(text);
            }catch(std::runtime_error ex){
                //If error was caught assume the for needs to end
                //This is of use when deleting big lists in the other thread while
                // at the middle of this for. So the least is cleared *before* the for is done.
                // This way
                break;
            }
        }


        window.display();
    }

    rekts.clear();
    //thread1->join();
    std::cout << "BYE!\n";

    return 0;
}
