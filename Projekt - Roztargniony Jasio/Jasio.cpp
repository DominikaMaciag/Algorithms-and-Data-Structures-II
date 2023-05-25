#include <iostream>
#include <vector>
#include <fstream>

/*  Aby zliczyć ilość potrzebnych do zbicia skarbonek musimy się dowiedzieć ile graf ma spójnych składowych,
    w tym celu zmodyfikujemy algorytm DFS służący do przechodzenia grafu.
*/

std::vector<int>* X;
bool *odwiedzone;
//inicjalizujemy licznik spójnych składowych L
int L;

void Funkcja(int n){
    int i = n;
    //std::cout << i << std::endl;
    odwiedzone[n]=true;

    //rekurencyjnie odwiedzamy nieodwiedzonych sąsiadów
    for(int j=0; j<X[i].size(); j++){ 
        if(odwiedzone[X[i].at(j)]==false){
            Funkcja(X[i].at(j));
        }
    } 
}

int main(){
    int n = 0;
    L=0;

    std::fstream plik;
    plik.open("test2.txt",std::ios::in);
    if(!plik.is_open()){
        std::cout << "Nie mozna znalezc pliku! " << std::endl;
    }
    int czytane;
    plik >> n;
    std::vector<int> vec[n+1];
    X = vec;
    odwiedzone = new bool[n+1]; 

    //wypełniamy tablicę odwiedzonych 
    for(int i=0; i<n; i++){
        odwiedzone[i]=false;
    }

    for(int i=1; i<=n ; i++)
    {
        plik >> czytane;
        X[i].push_back(czytane);
        X[czytane].push_back(i);
    }

    plik.close();
    for(int j=1; j<=n ;j++){
        if(odwiedzone[j]==false){            
            L++;
            Funkcja(j); 
        }

    }

    std::cout << " Nalezy stluc " << L << " skarbonek" << std::endl;   
    delete X;
    delete odwiedzone;
}