/*
 * Francisco Huelsz
 * A01019512
 *
 */


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "Graph.h"

#define WINDOWX  800
#define WINDOWY  800

#define PI_1 3.141592
#define PI_2 6.283185

#define RADIUS 15

int getRandom(int max) {
    //generar números de 0 a max
    int out = (std::rand() % (max + 1));
    return out;
}

//GLOBAL VARIABLES
bool inside = true;
Graph<int, int> graph;
double xmid = WINDOWX / 2.0;
double ymid = WINDOWY / 2.0;
double pRad = WINDOWX / 2.0 - 100;

//FUNCTION DECLARATION (Main Thread)
void drawVertex(std::list<Vertex<int,int> * > * list, sf::RenderWindow *window, sf::Font font);
void drawArrows(std::list<Vertex<int,int> * > * list, sf::RenderWindow *window);
void generateLocation(std::list<Vertex<int,int> * > * list, int length);
void drawBackground(sf::RenderWindow *pWindow);
sf::ConvexShape fillConvex();

//FUNCTION DECLARATION (Input Thread)
void consoleInput();
void printOptions();
void insertManual();
void insertEdge();
void findPath();
int getStart();


//MAIN FUNCTION
int main(){
    std::srand(std::time(0));



    std::cout << "INITIALIZING WINDOW" << std::endl;
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "The Graph!");
    sf::Font font;

    if(!font.loadFromFile("/usr/share/fonts/truetype/nanum/NanumGothic.ttf")){
        pln("ERROR LOADING FONT");
        exit(-1);
    }

    window.setFramerateLimit(24);

    std::thread userThread(consoleInput);

    while (window.isOpen() && inside) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                inside = false;
            }
        }

        //Clear Window
        window.clear();

        //Draw white background
        drawBackground (&window);

        //Lock the mutex to avoid errors
        mtx lock(graph.getMutex());

        //Set the locations of every node
        graph.generateLocation(xmid, ymid, pRad);

        //Retrieve vertex list
        std::list<Vertex<int,int> * > * list = graph.getVertixList();

        //Draw arrows representing edges
        drawArrows(list, &window);

        //Draw Vertex list
        drawVertex(list, &window, font);

        graph.getMutex().unlock();

        window.display();
    }

    userThread.join();
    std::cout << "BYE!\n";

    return 0;
}

//Used to generate the triangle component of arrows
sf::ConvexShape fillConvex() {
    sf::ConvexShape convex;
    convex.setPointCount(3);
    convex.setPoint(0, sf::Vector2f(15, 0));
    convex.setPoint(1, sf::Vector2f(10, 30));
    convex.setPoint(2, sf::Vector2f(20, 30));
    convex.setFillColor(sf::Color::Black);
    return convex;
}

//Draws a white background
void drawBackground(sf::RenderWindow *window) {
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(WINDOWX, WINDOWY));
    temp.setFillColor(sf::Color::White);
    temp.setPosition(0, 0);
    window->draw(temp);
}

//Draw the arroys representing the edges
void drawArrows(std::list<Vertex<int,int> * > * list, sf::RenderWindow *window){
    // Create an arrow triangle
    sf::ConvexShape convex = fillConvex();

    //Draw every arrow
    for (Vertex<int,int> * v : *(list)){
        for( Edge<int,int> * e: *(v->getEdges()) ){
            float origin[] {
                    v->getX(),
                    v->getY()
            };
            float destination[] {
                    e->getDestination()->getX(),
                    e->getDestination()->getY()
            };
            float vector[] {
                    destination[0] - origin[0],
                    destination[1] - origin[1]
            };

            sf::Color color = (e->isVisited())? sf::Color::Red : sf::Color::Black;

            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(origin[0], origin[1]), color),
                    sf::Vertex(sf::Vector2f(destination[0], destination[1]), color)
            };
            window->draw(line, 2, sf::Lines);

            double dir_rad = PI_1 - atan2( vector[0], vector[1]);
            double direction = dir_rad * (180/PI_1);

            double x = destination[0] - ((double)RADIUS * cos(dir_rad));
            double y = destination[1] - ((double)RADIUS * sin(dir_rad));

            convex.setPosition(x, y);
            convex.setRotation((float)direction);
            convex.setFillColor(color);

            window->draw(convex);

        }
    }
}

//Draw vertex list
void drawVertex(std::list<Vertex<int,int> * > * list, sf::RenderWindow *window, sf::Font font){
    for (Vertex<int,int> * v : *(list)){
        sf::CircleShape c(RADIUS);
        c.setPosition( v->getX() - (float)RADIUS, v->getY() - (float)RADIUS );
        if ( v->isVisited() ){
            c.setFillColor(sf::Color::Red);
        }else {
            c.setFillColor(sf::Color::Blue);
        }

        window->draw(c);
        sf::Text text(std::to_string(v->getData()), font, 15);
        text.setPosition(v->getX() - (float)RADIUS + 5, v->getY() - (float)RADIUS);
        window->draw(text);
    }
}

//Test data insertion
void fill(){
    for( int i = 1; i <= 10; i++){
        graph.addVertex(i);
    }

    for(int i = 1; i < graph.getLength(); i++){
        graph.addEdge(i,i+1,1);
    }
    graph.addEdge(graph.getLength(),1,1);

    graph.setStart(1);

    graph.addEdge(1,5,1);
    graph.addEdge(5,9,1);
    graph.addEdge(9,3,1);
    graph.addEdge(3,7,1);
    graph.addEdge(7,1,1);
    graph.clearVisits();
}

void consoleInput(){
    char inpt = '0';
    do{
        printOptions();

        std::cin >> inpt;

        switch(inpt){
            case '1':
                //Inser Manual Vertex
                insertManual();
                break;
            case '2':
                //Insert Edge
                insertEdge();
                break;
            case '3':
                //Delete last

                break;
            case '4':
                //Delete first

                break;
            case '5':
                //Print Breath First
                graph.setStart(getStart());
                graph.printBreadthFirst();
                break;
            case '6':
                //Print Depth First
                graph.setStart(getStart());
                graph.printDepthFirst();
                break;
            case 'p':
                findPath();
                break;
            case 'f':
                //Fill with test data
                fill();
                break;
            case 'd':
                graph.clear();
                break;
            case 'm':
                graph.debug();
                break;
            case 'q':
                break;
            default:
                break;
        }

    }while(inpt != 'q');

    inside = false;
}

int getStart(){
    int strt;
    pln("Select start node");
    std::cin >> strt;
    return strt;
}

void printOptions(){
    pln("Select an option:");
    pln("1 - insert Vertex manually");
    pln("2 - insert Edge");
    pln("3 - delete Vertex");
    pln("4 - delete Edge");
    pln("5 - print breath first");
    pln("6 - print depth first");
    pln("p - find a bath between two vertex");
    pln("f - Fill with test data");
    pln("d - drop all");
    pln("q - Quit");
}

void insertManual(){
    pln("Insert Vertex value (int):");
    int inpt;
    std::cin >> inpt;
    graph.addVertex(inpt);
}

void insertEdge(){
    int orig, dest, weight;
    pln("Type in the origin vertex:");
    std::cin >> orig;
    pln("Type in the destination vertex:");
    std::cin >> dest;
    pln("Type in the Edge weight:");
    std::cin >> weight;

    graph.addEdge(orig, dest, weight);
}

void findPath(){
    int orig, dest;
    pln("Type in the origin vertex:");
    std::cin >> orig;
    pln("Type in the destination vertex:");
    std::cin >> dest;

    std::list<Vertex<int, int> *> * path = nullptr;

    path = graph.findPath(orig, dest);
    std::cout << "Resulting path [ " << orig << " -> " << dest << " ]:"<< std::endl << "\t";
    if(path != nullptr) {
        graph.printPath(path);
        path->clear();
        delete path;
    }
}