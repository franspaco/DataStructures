/*
 * Francisco Huelsz
 * A01019512
 *
 */

#ifndef FINALPROJECT_VERTEX_H
#define FINALPROJECT_VERTEX_H

#include <iostream>
#include <list>
#include "Edge.h"

template <class T, class W>
class Vertex {
private:
    T data;
    bool visited;
    std::list<Edge<T, W> *> edges;
    float x;
    float y;

public:
    //Constructors
    Vertex();
    Vertex(const T & _data);

    //Destructor
    ~Vertex() { clear(); }

    //Clearing
    void clear();

    //Data
    T getData() { return data; }
    void setData(const T & _data) { data = _data; }

    //Visits
    void visit ();
    void unvisit ();
    void visitEdge(Vertex<T,W> * next);
    bool isVisited(){ return visited; }

    //Neighbours
    std::list<Edge<T,W> *> * getEdges() { return &edges; }
    void addEdge( Edge<T,W> * _edge);

    //Graphics
    float getX () { return x; }
    float getY () { return y; }
    void setP ( float _X, float _Y) { x = _X; y = _Y; }
    void setX ( float _X ) { x = _X; }
    void setY ( float _Y ) { y = _Y; }
};

template <class T, class W>
Vertex<T,W>::Vertex() {
    visited = false;
}

template <class T, class W>
Vertex<T,W>::Vertex(const T &_data) {
    data = _data;
    visited = false;
}

template <class T, class W>
void Vertex<T,W>::clear() {}

template <class T, class W>
void Vertex<T,W>::addEdge(Edge<T,W> *_edge) {
    edges.push_back(_edge);
}

template <class T, class W>
void Vertex<T,W>::visit() {
    visited = true;
    for( Edge<T, W> * e : edges){
        e->visit();
    }
}

template <class T, class W>
void Vertex<T,W>::unvisit() {
    visited = false;
    for( Edge<T, W> * e : edges){
        e->unvisit();
    }
}

template <class T, class W>
void Vertex<T,W>::visitEdge(Vertex *next) {
    visited = true;
    if(next != nullptr) {
        for (Edge<T, W> *e : edges) {
            if (e->getDestination() == next)
                e->visit();
        }
    }
}


#endif //FINALPROJECT_VERTEX_H
