#include<iostream>
#include <vector>

class setList
{
    std::vector<int> vec;

public:

    int getSize();  
    void printSet(); 
    void insert(int x); 
    void withdraw(int x); 
    bool isInSet(int x); 
    setList operator+(setList& obj);  
    setList operator*(setList& obj);   
    setList operator-(setList& obj);
    bool operator==(setList& obj);  
    bool operator<=(setList& obj);
    
};

int setList::getSize(){ //zwraca wielkość zbioru (tablicy)
	//std::cout<<"wielkosc zbioru to: "<< vec.size() <<std::endl;
	return vec.size();
}

void setList::printSet(){ //wypisuje wszystkie elementy zbioru
	if(vec.size()==0){
		std::cout<<"zbior pusty"<<std::endl;
	}
	else{
		std::cout<<" ";
		for(int i=0; i<vec.size(); i++){
			std::cout<<vec[i]<< ", ";
		}
	}	
}

void setList::insert(int x){ //dodaj do zbioru 
    if(isInSet(x)==false){ //jeśli nie ma w zbiorze liczby to ją dodaj
        vec.push_back(x); //dodajemy do listy
    }	
}

void setList::withdraw(int x){ //usuń ze zbioru
    for(int i=0; i<vec.size(); i++){
        if(vec[i]==x){
            vec.erase(vec.begin()+i); //usuwamy pojedynczy element
        }
    }
}

bool setList::isInSet(int x){ //sprawdza czy element jest w zbiorze
    for(int i=0; i<vec.size(); i++){
        if(vec[i]==x){
            return true;
        }
    }
    return false;
}

setList setList::operator+(setList& obj){ //dodawanie dwóch zbiorów do siebie
    setList sum;
    for(int i=0; i<vec.size(); i++){
        sum.insert(vec[i]);
    }
    for(int i=0; i<obj.vec.size(); i++){
        sum.insert(obj.vec[i]);
    }
    return sum;
}

setList setList::operator*(setList& obj){ //przecięcie zbiorów
    setList intersection; //zbiór części wspólnej zbiorów
    if(getSize()>obj.getSize()){ 
        for(int i=0; i<vec.size(); i++){
            if(isInSet(vec[i])==true && isInSet(obj.vec[i])==true){ //jeśli element jest w obu zbiorach
                intersection.insert(vec[i]);
            }
        }
    }
    else {
        for(int i=0; i<obj.vec.size(); i++){
            if(isInSet(vec[i])==true && obj.isInSet(vec[i])==true){ //jeśli element jest w obu zbiorach
                intersection.insert(vec[i]);
            }
        }
    }
    return intersection;
}

setList setList::operator-(setList& obj){ //różnica zbiorów
    setList difference; //zbiór różnicy zbiorów 
    for(int i=0; i<vec.size(); i++){
        if(isInSet(vec[i])==true && obj.isInSet(vec[i])==false){
            difference.insert(vec[i]);
        }
    }
    return difference;
}

bool setList::operator==(setList& obj){
    if(vec == obj.vec){
        return true;
    }
    else {
        return false;
    }
}

bool setList::operator<=(setList& obj){
    for(int i=0; i<vec.size(); i++){
        if(isInSet(vec[i])==true && obj.isInSet(vec[i])==false){
            return false;
        }
    }
    return true;
}

int main(){
    setList a; //zbiór A
	// zbiór pusty
	a.printSet();
	// dodajemy 2 i 3
	a.insert(2); 
	a.insert(3);
	// sprawdzamy czy jest 2 (jeśli jest to true: 1)
    std::cout<<"Czy liczba jest w zbiorze? "  << a.isInSet(2) << std::endl; 	
	// usuńmy 2 
	a.withdraw(2);
	// sprawdzamy czy 2 jest w zbiorze (nie jest więc false: 0)
	std::cout<<"Czy liczba jest w zbiorze? "  << a.isInSet(2) << std::endl; 
	//dodajmy 7 i 9 do zbioru
	a.insert(7);
	a.insert(9);
	//a.insert(13); //sprawdzamy co jeśli zbiór się nie zawiera w zbiorze b
	// wypiszmy zbiór: 3, 7, 9
	a.printSet();

    //stwórzmy kolejne dwa zbiory aby przetestować sumę, część wspólną oraz różnicę dwóch zbiorów
	setList c;
	c.insert(1); c.insert(2); c.insert(3); c.insert(4);	
	setList d;
	d.insert(3); d.insert(4); d.insert(5); d.insert(6);
	//SUMA
	setList suma = c+d;    
	std::cout<<std::endl; std::cout<<"suma zbiorow: "; suma.printSet(); std::cout<<std::endl;
	//CZ. WSPÓLNA
	setList cz_wspolna = c*d;
	std::cout<<"czesc wspolna zbiorow: "; cz_wspolna.printSet(); std::cout<<std::endl;
    //RÓŻNICA
	setList roznica = c-d; //to co nalezy do c, a nie należy do d
	std::cout<<"roznica zbiorow: "; roznica.printSet(); std::cout<<std::endl;

    //stwórzmy zbiór b 
    setList b;
    b.insert(3);
    b.insert(7);
    b.insert(9);
    b.insert(10);
    //sprawdźmy czy operacje na zbiorach działają poprawnie:
	//równość zbiorów
	std::cout<<"Czy zbiory sa sobie rowne? "<<(bool)(a==b)<<std::endl;
	//zawieranie się zbioru
	std::cout<<"Czy zbior a zawiera sie w zbiorze b? "<<(bool)(a<=b)<<std::endl; 
}