/*
 * Francisco Huelsz
 * A01019512
 *
 */

#ifndef FINALPROJECT_EDGE_H
#define FINALPROJECT_EDGE_H

template <class T, class W>
class Vertex;


template <class T, class W>
class Edge {
private:
    Vertex<T, W> * origin = nullptr;
    Vertex<T, W> * destination = nullptr;
    W weight;

    bool visited;

public:
    Edge(Vertex<T,W> * _origin = nullptr, Vertex<T,W> * _destination = nullptr, const W & _weight = 1) :
            origin(_origin), destination(_destination), weight(_weight) {}


    //Visits
    void visit () { visited = true; }
    void unvisit () { visited = false; }
    bool isVisited(){ return visited; }

    //Weight
    void setWeight(const W & _weight) { weight = _weight; }
    W getWeight() { return weight; }

    //Vertex
    Vertex<T,W> * getOrigin() { return origin; }
    Vertex<T,W> * getDestination() { return destination; };
};

#endif //FINALPROJECT_EDGE_H
