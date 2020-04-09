#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <math.h>
#include <stdlib.h>

using namespace std;

class edge {
    public:
        edge(int i, double v) : index(i), weight(v) {}
        ~edge() {}

        int getIndex() const { return index; }    //getter method for index of edge
    
        double getWeight() const {  return weight; }    //getter method for weight of edge
   
        string toString() { return "" + to_string(index) + ": Weight= " + to_string(weight) + " "; }

    private:
        int index;
        double weight;
};

class vertex {
    public:
        vertex() : degree(0) {}
        ~vertex() {}

        void addEdge(edge edge) { edges.push_back(edge); degree++; }
        int getDegree() const { return degree; }
        list <edge> getEdges() const { return edges; }
        string toString();
        
        bool operator < (const vertex &n) const { return degree > n.degree; }   //this enables the sort mechanism to sort them
                                                                              //so that first one is of largest degree.
    private:
        list <edge> edges; 
        int degree;

};

string vertex::toString() {
    string s = "";
    list <edge>::const_iterator nzit;
    for(nzit = edges.begin(); nzit != edges.end(); nzit++) {
        edge n = *nzit;
        s += n.toString();
    }
    return s;
}



class matrix {
    public:
        matrix() : countVertices(0), largestVertexDegree(0), epsilon(0.0), sumVertexDegree(0) {}

        ~matrix() {}

        void addRow(vertex row) { 
            vertices.push_back(row); 
            countVertices++; 
            int deg = row.getDegree();
            sumVertexDegree += deg; 

            if(deg > largestVertexDegree) largestVertexDegree = deg;
        };

        int getLargestVertexDeg();
        int getAverageVertexDeg();

        list <vertex> getRows() { return vertices; }
        void formatz(int eps);
        void sortVertices() { vertices.sort(); }  //do not use
        string toString();

        list <vertex> getNeighbours(int edge_distance = 1);
        list <vertex> shortestPath(vertex v1, vertex v2);
        list <vertex> shortestEdgeCount(vertex v1, vertex v2);

    private:
        list <vertex> vertices;
        double epsilon;

        int countVertices;
        int sumVertexDegree;
        int largestVertexDegree;


};

int matrix::getLargestVertexDeg() {
    return largestVertexDegree;
}

int matrix::getAverageVertexDeg() {  
    return round(sumVertexDegree / countVertices);   //divides sum of all vertex degrees by number of vertexes
}

string matrix::toString() {
    list <vertex>::const_iterator vIt;
    string s = "";
    for(vIt = vertices.begin(); vIt != vertices.end(); vIt++) {
        vertex n = *vIt;
        s += n.toString() + "\n";
    }
    return s;

}

void matrix::formatz(int eps) {
    string line;
    int countNonZeros = 0;

    while (getline(cin, line)) { // get next full line of text; NB: text
  
        std::istringstream lstream(line);
        vertex vert;
        int index = 0; // index of element of row
        double val;
        
        while (lstream >> val) {  // peel off values in this line, one at a time
    
            ++index;
            if (fabs(val) > eps)
                vert.addEdge(edge(index, val));
        
        }        

        addRow(vert);         //add this row to the list of other rows
        countNonZeros += vert.getDegree(); //add the number of new non-zeros to the total amount
    }

    list <vertex> ::const_iterator rowsIterator;   //making an iterator for a list of nodes
    
    for (rowsIterator = vertices.begin(); rowsIterator != vertices.end(); rowsIterator++) {
    
        vertex row = *rowsIterator;                    //dereferencing where the iterator is pointing to to get a node  
        list <edge> edges = row.getEdges();
        list<edge>::const_iterator ei;                 //making an iterator for the edges of a node
        for (ei = edges.begin(); ei != edges.end(); ei++) {
            cout << ei->getIndex() << " " << ei->getWeight() << " ";        //print out the index and value of each nz
        }

        cout << endl;
    }

    cout << "number of nodes/vertices = " << vertices.size() << endl;
    cout << "number of edges = " << countNonZeros << endl;

    cout << "largest vertex degree = " << to_string(getLargestVertexDeg()) << endl;  //the first element of the rows list has the largest degree
    cout << "average vertex degree = " << to_string(getAverageVertexDeg()) << endl;  //the first element of the rows list has the largest degree

}



int main(int argc, char * argv[]) {
    double epsilon = 0.0;
    if (argc > 1 && string(argv[1]) == "-e") {
        epsilon = fabs(strtod(argv[2], 0));
    }

    matrix mat;
    mat.formatz(epsilon);

    //cout << endl;

    

}