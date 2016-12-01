/*
 * Francisco Huelsz
 * A01019512
 *
 */

#ifndef FINALPROJECT_GRAPH_H
#define FINALPROJECT_GRAPH_H

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include "Vertex.h"
#include "InfoNode.h"

#define PI_1 3.141592
#define PI_2 6.283185

#define WAITMILIS 1000


template<class T>
void pln(T thing) {
    //lazy printing method
    std::cout << thing << std::endl;
}

using mtx = std::lock_guard<std::mutex>;

template <class T, class W>
class Graph {
private:
    std::list<Vertex<T,W> * > vertices;
    std::list<Edge<T,W> * > edges;
    Vertex<T,W> * start;

    std::mutex v_mutex;

    std::list<InfoNode<T, W> *> dijkstra;

    //Dijkstra
    InfoNode<T,W> * initDijkstra ( std::list<InfoNode<T,W> * > * dijkstra, Vertex<T,W> * origin);
    InfoNode<T,W> * getCheapest( std::list<InfoNode<T,W> * > * dijkstra);
    void clearDijkstra( std::list<InfoNode<T,W> * > * dijkstra);
    std::list<Vertex<T,W> * > * recoverPath(  std::list<InfoNode<T,W> * > * dijkstra, InfoNode<T,W> * current_vertex_info_node);

public:
    Graph() { start = nullptr; }
    ~Graph() { clear(); }

    //Clear
    void clear();

    //Graph and display
    void generateLocation(double xmid, double ymid, double pRad);
    int getLength() { return (int)vertices.size(); }
    std::list<Vertex<T,W> * > * getVertixList() { return &vertices; }

    //Mutex
    std::mutex& getMutex(){ return v_mutex; }

    //Vertex Ops
    void addVertex(const T & _data);
    void addVertexPtr(Vertex<T,W> * _vertex);

    Vertex<T,W> * getStart() { return start; }
    void setStart(const T & _data);
    void setStart(Vertex<T,W> * _start) { start = _start; }

    //Edge Ops
    void addEdge(const T & origin_data, const T & destination_data, const W & _weight = 1);
    void addEdgePtr(Vertex<T, W> *_origin, Vertex<T, W> *_destination, const W &_weight = 1);
    void addEdge(Edge<T,W> * _edge);

    //Visits
    void clearVisits();

    //Printing
    void printBreadthFirst();
    void printDepthFirst();
    void debug();

    //Path Ops
    std::list<Vertex<T,W> *> * findPath(const T & origin, const T & destination);
    std::list<Vertex<T,W> *> * findPathPtr(Vertex<T,W> * origin, Vertex<T,W> * destination);
    void printPath(std::list<Vertex<T,W> *> * path);
};

template <class T, class W>
void Graph<T,W>::clear() {
    mtx lock(v_mutex);
    while(!vertices.empty()){
        vertices.front()->clear();
        delete vertices.front();
        vertices.pop_front();
    }

    while(!edges.empty()){
        delete edges.front();
        edges.pop_front();
    }
    start = nullptr;
}

template <class T, class W>
void Graph<T,W>::addVertex(const T & _data) {
    Vertex<T,W> * new_vertex = new Vertex<T,W>(_data);
    addVertexPtr(new_vertex);
}

template<class T, class W>
void Graph<T,W>::addVertexPtr(Vertex<T,W> * _vertex) {
    mtx lock(v_mutex);
    vertices.push_back(_vertex);
}

template<class T, class W>
void Graph<T,W>::addEdge(const T & origin_data, const T & destination_data, const W & _weight) {
    Vertex<T,W> * _origin = nullptr;
    Vertex<T,W> * _destination = nullptr;
    //Look for the vertex that matches the data
    for (Vertex<T,W> * v : vertices){
        if ( v->getData() == origin_data){
            _origin = v;
        }
        if ( v->getData() == destination_data){
            _destination = v;
        }
    }
    addEdgePtr(_origin, _destination, _weight);
}

template<class T, class W>
void Graph<T,W>::addEdgePtr(Vertex<T, W> *_origin, Vertex<T, W> *_destination, const W & _weight) {
    if (_origin != nullptr && _destination != nullptr) {
        mtx lock(v_mutex);
        //create the object edge
        Edge<T,W> * new_edge = new Edge<T,W>(_origin, _destination, _weight);
        addEdge(new_edge);
    }
}

template<class T, class W>
void Graph<T,W>::addEdge(Edge<T,W> *_edge) {
    if (_edge != nullptr) {
        // Insert the edge to the list in the graph
        edges.push_back(_edge);
        // Add the edge to the list in the origin vertex
        _edge->getOrigin()->addEdge(_edge);
    }
}

template<class T, class W>
void Graph<T,W>::setStart(const T & _data) {
    // Look for the vertices that contain the data specified
    for (Vertex<T,W> * v : vertices){
        if ( v->getData() == _data){
            setStart(v);
        }
    }
}

template<class T, class W>
void Graph<T,W>::printBreadthFirst() {
    if (start == nullptr)
        return;

    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    std::list<Edge<T, W> *> * edge_list;
    std::list<Vertex<T, W> *> queue;

    std::cout << "Breadth First Traversal:" << std::endl;
    // Make sure all vertices are marked as not visited
    clearVisits();
    // Add the initial node to the queue
    queue.push_back(start);
    mtx lock(v_mutex);

    while ( !queue.empty() ){
        v_mutex.lock();
        current_vertex = queue.front();
        queue.pop_front();

        if(current_vertex->isVisited())
            continue;

        std::cout << current_vertex->getData() << " -> ";

        // Mark the vertex as visited
        current_vertex->visit();

        // Get the list of edges
        edge_list = current_vertex->getEdges();

        for (Edge<T,W> * e : *(edge_list)){
            neighbour = e->getDestination();
            // If the neighbour has not been visited, add it to the queue
            if (!neighbour->isVisited()) {
                queue.push_back(neighbour);

            }
        }
        v_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAITMILIS));
    }
    std::cout << std::endl;
}

template<class T, class W>
void Graph<T,W>::printDepthFirst() {
    if (start == nullptr)
        return;

    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    std::list<Edge<T, W> *> * edge_list;
    std::list<Vertex<T, W> *> stack;

    std::cout << "Depth First Traversal:" << std::endl;

    // Make sure all vertices are marked as not visited
    clearVisits();
    // Add the initial node to the stack
    stack.push_back(start);
    mtx lock(v_mutex);

    while ( !stack.empty() ){
        v_mutex.lock();
        current_vertex = stack.back();
        stack.pop_back();

        if(current_vertex->isVisited())
            continue;

        std::cout << current_vertex->getData() << " -> ";

        // Mark the vertex as visited
        current_vertex->visit();

        // Get the list of edges
        edge_list = current_vertex->getEdges();

        for (Edge<T,W> * e : *(edge_list)){
            neighbour = e->getDestination();
            // If the neighbour has not been visited, add it to the stack
            if (!neighbour->isVisited())
            {
                stack.push_back(neighbour);
            }
        }
        v_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAITMILIS));
    }
    std::cout << std::endl;
}

template<class T, class W>
void Graph<T,W>::clearVisits() {
    for (Vertex<T,W> * v : vertices){
        v->unvisit();
    }
}

template<class T, class W>
std::list<Vertex<T,W> *> * Graph<T,W>::findPath(const T & origin_data, const T & destination_data) {
    Vertex<T,W> * _origin = nullptr;
    Vertex<T,W> * _destination = nullptr;

    //Look for the vertex that matches the data
    for (Vertex<T,W> * v : vertices){
        if ( v->getData() == origin_data){
            _origin = v;
        }
        if ( v->getData() == destination_data){
            _destination = v;
        }
    }

    // Find the path from the origin vertex to the destination vertex
    try {
        return findPathPtr(_origin, _destination);
    }
    catch (std::runtime_error r_e){
        pln(r_e.what());
        return nullptr;
    }
}

template<class T, class W>
std::list<Vertex<T,W> *> *Graph<T,W>::findPathPtr(Vertex<T,W> *origin, Vertex<T,W> *destination) {
    if( origin == nullptr || destination == nullptr)
        return nullptr;
    clearVisits();
    //std::list<InfoNode<T, W> *> dijkstra;
    InfoNode<T, W> * current_vertex_info_node = nullptr;
    Vertex<T, W> * current_vertex = nullptr;
    Vertex<T, W> * neighbour = nullptr;
    std::list<Edge<T, W> *> * edge_list = nullptr;
    std::list<Vertex<T, W> *> * path = nullptr;

    // Set the current_vertex vertex to the starting point (origin)
    current_vertex = origin;
    // Initialize the "table" for the Dijkstra algorithm
    current_vertex_info_node = initDijkstra(&dijkstra, origin);

    mtx lock(v_mutex);

    // Loop until the destination is reached
    while (current_vertex_info_node != nullptr and current_vertex != destination){
        v_mutex.lock();
        // Get the list of edges
        edge_list = current_vertex->getEdges();
        // Get the node with the first edge
        // Loop over the neighbours of the current vertex
        for(Edge<T,W> * e : *(edge_list)){
            // Get the destination of the edge stored in the node
            neighbour = e->getDestination();
            // Update the cost for each neighbour
            // TODO: This is very inefficient. The Dijkstra list is searched each time
            for(InfoNode<T, W> * info_node : dijkstra){
                if (info_node->getVertex() == neighbour)
                {
                    // Add cost of the current_vertex node and the edge weight to the neighbour
                    W new_cost = current_vertex_info_node->getCost() + e->getWeight();
                    // If the new cost is lower, than the previous, or if no cost has been determined yet
                    if (info_node->getCost() == -1 or new_cost < info_node->getCost())
                    {
                        info_node->setCost(new_cost);
                        info_node->setPrevious(current_vertex);
                    }
                }
            }
        }
        // Continue by checking the next cheapest item in the dijkstra list
        current_vertex_info_node = getCheapest(&dijkstra);
        if(current_vertex_info_node != nullptr) {
            current_vertex_info_node->getVertex()->visit();
            current_vertex_info_node->visit();
            current_vertex = current_vertex_info_node->getVertex();
        }else{
            clearDijkstra(&dijkstra);
            v_mutex.unlock();
            throw std::runtime_error("No path available");
        }

        v_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAITMILIS));
    }

    // Recover the path from origin to destination
    path = recoverPath(&dijkstra, current_vertex_info_node);

    // Clear the memory used by the Dijkstra list
    clearDijkstra(&dijkstra);

    return path;
}

template<class T, class W>
void Graph<T,W>::printPath(std::list<Vertex<T,W> *> * path) {
    mtx lock(v_mutex);

    clearVisits();

    Vertex<T,W> * last = nullptr;

    for(Vertex<T,W> * ver : *(path)){
        std::cout << ver->getData();

        if (ver != path->front())
            last->visitEdge(ver);

        if (ver != path->back())
            std::cout << " -> ";
        else
            std::cout << std::endl;

        last = ver;
    }
    last->visitEdge(nullptr);
}


template<class T, class W>
InfoNode<T,W> *Graph<T,W>::initDijkstra(std::list<InfoNode<T,W> *> *dijkstra, Vertex<T,W> * origin) {
    InfoNode<T, W> * info_node = nullptr;
    InfoNode<T, W> * origin_info_node = nullptr;

    // Fill the dijkstra list with info nodes
    for(Vertex<T, W> * v : vertices){
        info_node = new InfoNode<T, W> (v);
        if (v == origin)
        {
            origin_info_node = info_node;
            info_node->setCost(0);
        }
        dijkstra->push_back(info_node);
    }
    return origin_info_node;
}

template<class T, class W>
InfoNode<T,W> *Graph<T,W>::getCheapest(std::list<InfoNode<T,W> *> *dijkstra) {
    InfoNode<T, W> * lowest_vertex = nullptr;

    // TODO: Find a better way to initialize the cost
    W lowest_cost = 99999999;

    for(InfoNode<T, W> * info_node : *(dijkstra)){
        //std::cout << "Comparing with: " << *info_node << std::endl;
        if (info_node->getCost() != -1 and info_node->getCost() < lowest_cost and !info_node->isVisited()) {
            lowest_cost = info_node->getCost();
            lowest_vertex = info_node;
        }
    }
    return lowest_vertex;
}

template<class T, class W>
void Graph<T,W>::clearDijkstra(std::list<InfoNode<T,W> *> * dijkstra) {
    //Delete all nodes in the Dijkstra list
    while(!dijkstra->empty()){
        delete dijkstra->front();
        dijkstra->pop_front();
    }

    for(InfoNode<T,W> * in : *(dijkstra)) {
        std::cout << in->getVertex() << std::endl;
    }

}

template<class T, class W>
std::list<Vertex<T,W> *> *
Graph<T,W>::recoverPath(std::list<InfoNode<T,W> *> *dijkstra, InfoNode<T,W> * current_vertex_info_node) {
    std::list<Vertex<T, W> *> * path = new std::list<Vertex<T, W> *>;

    // Search the previous vertices in the Dijkstra list
    while(current_vertex_info_node->getPrevious() != nullptr)
    {
        // Insert the vertex in to the path list
        path->push_front(current_vertex_info_node->getVertex());
        // Look in the list of info nodes for the previous vertex
        for(InfoNode<T, W> * info_node : *(dijkstra)){
            // Get the vertex that is marked as previous in this info node
            if (info_node->getVertex() == current_vertex_info_node->getPrevious())
            {
                current_vertex_info_node = info_node;
                break;
            }
        }
    }
    // Insert the origin vertex in the list
    path->push_front(current_vertex_info_node->getVertex());

    return path;
}

template<class T, class W>
void Graph<T,W>::generateLocation(double xmid, double ymid, double pRad){
    double degrees = PI_2 / vertices.size();
    int count = 0;
    double theta, x, y;
    for (Vertex<int,int> * v : vertices){
        theta = count * degrees;
        x = xmid + pRad * sin(theta);
        y = ymid - pRad * cos(theta);

        v->setP( (float)x, (float)y);
        count++;
    }
}

template<class T, class W>
void Graph<T,W>::debug(){
    for (Vertex<T,W> * v : vertices){
        std::cout << v->getData() << ", ";
    }
    std::cout << std::endl;

    for (Edge<T,W> * e : edges){
        std::cout << e->getOrigin()->getData() << " -> " << e->getDestination()->getData() <<  " : " << e->getWeight() << std::endl;
    }
    std::cout << std::endl;
    for(InfoNode<T,W> * in : dijkstra) {
        std::cout << in->getVertex() << std::endl;
    }
}


#endif //FINALPROJECT_GRAPH_H
