/* Implementacja minimalnego kopca binarnego, zaleznosc: rodzic mniejszy od dzieci */

#include <array>
#include <iostream>

class KolejkaPriorytetowa
{
    private:
    int size=0;
    std::array<int, 100> table;
    public:
    void swap(int *ElemA, int *ElemB);
    void insert(int x); //wstawia element 
    int RemoveRootElem(); //usuwa element z korzenia
    void print();   
    int getRootElem(); //zwraca korzeń    
};

void KolejkaPriorytetowa::swap(int *ElemA, int *ElemB){ //zamieniamy elementy
    int tmp = *ElemA;
    *ElemA = *ElemB;
    *ElemB = tmp;
}

void KolejkaPriorytetowa::insert(int x){
    //najpierw dodajemy na dostępne miejsce nasz element 
    table[size]=x;
    size++;
    //porównujemy dodany element z jego rodzicem, jeśli jest mniejszy robimy zamianę miejscami
    //zamianiamy tak długo jak element będzie mniejszy od rodzica
    for(int i=size-1; i>=0; i=(i-1)/2){ //przechodzimy po kolejnych rodzicach
        if(table[i]<table[(i-1)/2]){
            swap(&table[i], &table[(i-1)/2]);
        }  
        else {
            break;
        } 
    }
}

int KolejkaPriorytetowa::RemoveRootElem(){
    if(size==0){
        std::cout<<"Kopiec jest pusty!" << std::endl;
    }

    int tmp = table[size-1];
    swap(&table[0], &tmp); //zamieniamy obecny root z ostatnim elementem (najniższy lvl i najbardziej na prawo)
    size--; //usunęliśmy root, musimy jeszcze poprawić nasz kopiec by spełniał wszystkie założenia
    for(int i=0; i<size; i=(i*2)+2){ //przechodzimy po kolejnych rodzicach
        if(table[i]>table[(i*2)+2]){ //jeśli prawe dziecko mniejsze
            swap(&table[i], &table[(i*2)+2]);
        }  
        else if(table[i]>table[(i*2)+1]){ //jeśli lewe dziecko mniejsze
            swap(&table[i], &table[(i*2)+1]);
        }
        else { //jeśli żadne dziecko roota nie jest mniejsze to kończymy pętlę
            break;
        } 
    }
    return tmp;
}

int KolejkaPriorytetowa::getRootElem(){
    if(size==0){
        std::cout<<"Kopiec jest pusty!"<<std::endl;
    }

    else{
        std::cout<<"Element znajdujacy sie w korzeniu to: " << table[0]<< std::endl;        
    }
    return table[0];
}

void KolejkaPriorytetowa::print(){
    for(int i=0; i<=size-1; i++){
        std::cout<< table[i] << ", ";
    }
}

int main(){
    KolejkaPriorytetowa heap;

    heap.getRootElem();
    //dodajmy po kolei liczby: 100, 70, 50, 125, 45, 60 oraz 10
    std::cout<<"Dodajmy liczby do kopca binarnego: " <<std::endl;
    heap.insert(100);     
    heap.insert(70); 
    heap.insert(50); 
    heap.insert(125);
    heap.insert(45);
    heap.insert(60);
    heap.insert(10);

    //wypisujemy całą tablicę i nasz root
    heap.print();
    std::cout<< std::endl;
    heap.getRootElem();
    std::cout<< std::endl;
    std::cout<< std::endl;

    //testujemy usuwanie root'a
    KolejkaPriorytetowa heap_2;
    std::cout<<"Kopiec binarny przed usunieciem korzenia: " <<std::endl;
    heap_2.insert(10);     
    heap_2.insert(30); 
    heap_2.insert(15); 
    heap_2.insert(100);
    heap_2.insert(50);
    heap_2.insert(75);
    heap_2.insert(90);
    heap_2.print();
    std::cout<< std::endl;
    heap_2.getRootElem(); 

    std::cout<<"Kopiec binarny po usunieciu korzenia: " <<std::endl;
    heap_2.RemoveRootElem();
    heap_2.print();
    std::cout<< std::endl;
    heap_2.getRootElem();
}