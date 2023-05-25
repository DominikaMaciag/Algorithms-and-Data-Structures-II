#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

/* Implementacja grafu skierowanego za pomocą listy sąsiedztwa */

class Graf
{
    std::vector<int> vertexList[2000];
    int numberOfVertices; //ilość wierzchołków

public:
    Graf();
    void createVertices(int ile);    
    void addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);    
    void removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    bool checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2);
    int vertexDegree(int idx); 
    std::vector<int> getNeighbourIndices(int idx);
    void printNeighbourIndices(int idx);
    int getNumberOfEdges();
    void readFromFile(std::string path); 
};

//konstruktor 
Graf::Graf(){ 
    numberOfVertices = 2000;
}

//Tworzy wierchołki (ilość wierzchołków podajemy w argumencie)
void Graf::createVertices(int ile){
    if(ile<2000){
        numberOfVertices = ile;
    }
    else {
        std::cout << "Podano zbyt duza liczbe wierzcholkow! " << std::endl;
    }
}

//Tworzy krawędź pomiędzy podanymi wierzchołkami
void Graf::addEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
    vertexList[i_Vertex_Index_1].push_back(i_Vertex_Index_2); //krawędź z pierwszego wierzchołka do drugiego
}

//Usuwa krawędź pomiędzy podanymi wierzchołkami
void Graf::removeEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
    for(int i=0; i<numberOfVertices; i++){
        if(vertexList[i_Vertex_Index_1][i] == i_Vertex_Index_2){
            vertexList[i_Vertex_Index_1].erase(vertexList[i_Vertex_Index_1].begin() + i);
        }
    }
}

//Sprawdza czy krawędź pomiędzy podanymi wierzchołkami istnieje
bool Graf::checkEdge(int i_Vertex_Index_1, int i_Vertex_Index_2){
    for(int i=0; i<vertexList[i_Vertex_Index_1].size(); i++){
        if(vertexList[i_Vertex_Index_1].at(i)==i_Vertex_Index_2){
            return true;
        }
    }
    return false;
}

//Sprawdza stopień wierzchołka
int Graf::vertexDegree(int idx){ 
    return vertexList[idx].size();
}

//Zwraca sąsiednie wierzchołki
std::vector<int> Graf::getNeighbourIndices(int idx){
    return vertexList[idx];
}

//Wypisuje sąsiednie wierzchołki
void Graf::printNeighbourIndices(int idx){
    for(int i=0; i<numberOfVertices;i++){
        if(checkEdge(idx,i)==true){
            std::cout << i << ", ";
        }
    }
}

//Zwraca ilość krawędzi grafu
int Graf::getNumberOfEdges(){
    int number = 0;
    for(int i=0; i<numberOfVertices; i++){
        number+=vertexList[i].size(); 
    }
    std::cout<<"Ilosc krawedzi wynosi: " << number << std::endl;
    return number;
}

//Odczytuje dane z pliku tekstowego
void Graf::readFromFile(std::string path){
    std::ifstream file;
    int n_vertices;
    file.open(path); //otwieramy plik
    file >> n_vertices;
    createVertices(n_vertices);
    int edge1, edge2;
    while(file >> edge1){
        file >> edge2;
        addEdge(edge1, edge2);
    }
    file.close(); //zamykamy strumień
}

int main(){
    //Mój własny test
    Graf graph;
    //utwórzmy graf z 6 wierzchołkami
    graph.createVertices(5);
    //dodajmy kilka krawędzi 
    std::cout<<"Dodajemy trzy krawedzie... " <<std::endl;
    graph.addEdge(1,2);
    graph.addEdge(1,4);
    graph.addEdge(3,0);
    //sprawdźmy ilość krawędzi (jest ich 3)
    graph.getNumberOfEdges();
    //sprawdźmy czy krawędź między 1 a 4 istnieje - true
    std::cout<<"Sprawdzmy czy krawedz 1->4 istnieje: " << graph.checkEdge(1,4) <<std::endl; 
    //sprawdźmy czy krawędź między 4 a 1 istnieje - false bo graf skierowany
    std::cout<<"Sprawdzmy czy krawedz 4->1 istnieje: " << graph.checkEdge(4,1) <<std::endl;
    std::cout<<"Usuwamy krawedz 1->4... " <<std::endl;
    graph.removeEdge(1,4);
    std::cout<<"Sprawdzmy czy krawedz 1->4 istnieje po jej usunieciu: " << graph.checkEdge(1,4) <<std::endl; 
    std::cout<<"Sprawdzamy stopien macierzy... " << graph.vertexDegree(3) <<std::endl;
    std::cout<<"Wektor sasiednich wierzcholkow: "<< std::endl;
    graph.addEdge(3,4);
    graph.printNeighbourIndices(3); std::cout<< std::endl;

    //test wczytujący dane z pliku 
    Graf graph2;
    std::cout<< "Graf wczytany z pliku Graf1.txt" << std::endl;
    graph2.readFromFile("Graf1.txt");
    graph2.printNeighbourIndices(1);
    std::cout<< std::endl;
    graph2.getNumberOfEdges(); 
}