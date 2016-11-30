//
// Created by franspaco on 29/11/16.
//

#ifndef FINALPROJECT_INFONODE_H
#define FINALPROJECT_INFONODE_H

#include "Vertex.h"

template<class T, class W>
class InfoNode{
private:
    Vertex<T,W> * vertex = nullptr;
    Vertex<T,W> * previous = nullptr;
    bool visited;
    W cost;

public:
    //Constructors
    InfoNode () :
            vertex(nullptr), previous(nullptr), visited(false), cost(-1) {}

    InfoNode (Vertex<T,W> * _vertex, Vertex<T,W> * _previous = nullptr, const W & _cost = -1) :
            vertex(_vertex), previous(_previous), cost(_cost) {}


    //Visits
    void visit() { visited = true; }
    bool isVisited() { return visited; }

    //Vertex
    Vertex<T,W> * getVertex() { return vertex; }
    Vertex<T,W> * getPrevious() { return previous; }
    void setVertex (Vertex<T,W> * _vertex) { vertex = _vertex; }
    void setPrevious (Vertex<T,W> * _previous) { previous = _previous; }

    //Cost
    W getCost () { return cost; }
    void setCost (const W & _cost) { cost = _cost; }

    template<class R, class S>
    friend std::ostream & operator<< (std::ostream & stream, const InfoNode<R,S> & info_node);
};

template<class R, class S>
std::ostream &operator<<(std::ostream &stream, const InfoNode<R, S> &info_node) {
    stream << info_node.vertex->getData() << " " << info_node.visited << " " << info_node.cost << " ";
    if(info_node.previous != nullptr ){
        stream << info_node.previous->getData();
    }
    stream << std::endl;
    return stream;
}


#endif //FINALPROJECT_INFONODE_H
