#include <iostream>

class setArr {
    int size;
    const int universeSize = 100;
    bool* table; 
    bool checkRangeCorrectness(int x); 
    public:
	setArr(); 
	void insert(int x); 
	void withdraw(int x); 
	bool isInSet(int i); 
	int getSize(); 
	void clearSet(); 
	void printSet(); 
	setArr operator+(setArr& object);
	setArr operator*(setArr& object);
	setArr operator-(setArr& object);
	bool operator==(setArr& object);
	bool operator <= (setArr& object);
};

bool setArr::checkRangeCorrectness(int x){ //sprawdzamy czy dana liczba nie wychodzi poza skalę uniwersum
	if(x>= universeSize){
		std::cout << "liczba " << x << " wychodzi poza skale naszego uniwersum" << std::endl;
		return false;
	}
	return true;
}

setArr::setArr(){ //konstruktor tworzy zbiór pusty, wszędzie ustawiamy wartość false
	table = new bool[universeSize]; //tworzymy tablicę o podanej wielkości
	size = 0; //rozmiar pustej tablicy to 0
	for(int i=0; i<universeSize; i++){
		table[i]=false;
	}
}

void setArr::insert(int x){ //dodaj do zbioru (tablicy)
	if(checkRangeCorrectness(x)==true){ //czy liczba znajduje się w uniwersum
		if(table[x]==false){ //jeśli elementu nie ma w tablicy to wtedy go dodajemy (ustawiamy na wartość true)
			table[x]=true;
			size += 1;
		}
	}	
}


void setArr::withdraw(int x){ //usuń ze zbioru (tablicy)
	if(checkRangeCorrectness(x)==true){ //czy liczba znajduje się w uniwersum
		if(table[x]==true){ //jeśli element jest w tablicy to usuwamy (ustawiamy false)
			table[x]=false;
			size -= 1;
		}
	}	
}

bool setArr::isInSet(int i){ //sprawdza czy element jest w zbiorze
	if(checkRangeCorrectness(i)==true){
		if(table[i]==true){
			std::cout<<"liczba "<<i<<" jest w zbiorze"<<std::endl;
			return true;
		}

		else {
			std::cout<<"liczba "<<i<<" nie jest w zbiorze"<<std::endl;
			return false;
		}
	}	
	else{
		return false;
	}
}

int setArr::getSize(){ //zwraca wielkość zbioru (tablicy)
	std::cout<<"wielkosc zbioru to: "<< size <<std::endl;
	return size;
}

void setArr::clearSet(){ //czyści zbiór = czyni go pustym
	for( int i=0; i<universeSize; i++){
		table[i]=false;
	}
	size = 0;
}

void setArr::printSet(){ //wypisuje wszystkie elementy zbioru
	if(size==0){
		std::cout<<"zbior pusty"<<std::endl;
	}
	else{
		std::cout<<"elementy zbioru:";
		for(int i=0; i<universeSize; i++){
			if(table[i]==true){
				std::cout<<i<< ", ";
			}
		}
	}	
}

setArr setArr::operator+(setArr& object){ //dodawanie dwóch zbiorów do siebie
	setArr sum; //zbiór sumy dwóch zbiorów
	for(int i=0; i<universeSize; i++){
		if(table[i]==true || object.table[i]==true){
			sum.insert(i);
		}
	}
	return sum;
}

setArr setArr::operator*(setArr& object){ //przecięcie zbiorów
	setArr intersection; //zbiór części wspólnej zbiorów
	for(int i=0; i<universeSize; i++){
		if(table[i]==true && object.table[i]==true){
			intersection.insert(i);
		}
	}
	return intersection;
}

setArr setArr::operator-(setArr& object){ //różnica zbiorów
	setArr difference; //zbiór różnicy zbiorów 
	for(int i=0; i<universeSize; i++){
		if(table[i]==true && object.table[i]==false){ //część która należy do pierwszego, ale nie należy do drugiego
			difference.insert(i);
		}
	}
	return difference;
}

bool setArr::operator==(setArr& object){ //równość zbiorów
	for(int i=0; i<universeSize; i++){
		if( (table[i]==true && object.table[i]==false) || (table[i]==false && object.table[i]==true)){
			return false;
		}
	}
	return true;
}

bool setArr::operator<=(setArr& object){ //zawieranie
	for(int i=0; i<universeSize; i++){
		if(table[i]==true && object.table[i]==false){
			return false;
		}
	}
	return true;
}

int main(){
	//wywołujemy konstruktor i dalej resztę metod
	setArr a; //zbiór A
	// zbiór pusty
	a.printSet();
	// dodajemy 2 i 3
	a.insert(2); 
	a.insert(3);
	// sprawdzamy czy jest 2 (jeśli jest to true: 1)
	a.isInSet(2); 
	// usuńmy 2 
	a.withdraw(2);
	// sprawdzamy czy 2 jest w zbiorze ( nie jest więc false: 0)
	a.isInSet(2);
	//dodajmy 7 i 9 do zbioru
	a.insert(7);
	a.insert(9);
	//a.insert(13); //sprawdzamy co jeśli zbiór się nie zawiera w zbiorze b
	// wypiszmy zbiór: 3, 7, 9
	a.printSet();
	//dodajmy 107 do zbioru i zobaczmy co się stanie (nie możemy takiej liczby dodać)
	std::cout<<std::endl;
	a.insert(107);


	setArr b; //zbiór B
	//dodajmy te same elemnty co poprzednio: 3,7,9
	b.insert(3);
	b.insert(7);
	b.insert(9);
	//b.insert(1); //dla tego zwraca 0 czyli fałsz bo wtedy zbiory nie są równe

	//sprawdźmy czy operacje na zbiorach działają poprawnie:
	//równość zbiorów
	std::cout<<"Czy zbiory sa sobie rowne? "<<(bool)(a==b)<<std::endl;
	//zawieranie się zbioru
	std::cout<<"Czy zbior a zawiera sie w zbiorze b? "<<(bool)(a<=b)<<std::endl; 

	//stwórzmy kolejne dwa zbiory aby przetestować sumę, część wspólną oraz różnicę dwóch zbiorów
	setArr c;
	c.insert(1); c.insert(2); c.insert(3); c.insert(4);	
	setArr d;
	d.insert(3); d.insert(4); d.insert(5); d.insert(6);
	//SUMA
	setArr suma = c+d;
	std::cout<<"suma zbiorow: "; suma.printSet(); std::cout<<std::endl;
	//RÓŻNICA
	setArr roznica = c-d; //to co nalezy do c, a nie należy do d
	std::cout<<"roznica zbiorow: "; roznica.printSet(); std::cout<<std::endl;
	//CZ. WSPÓLNA
	setArr cz_wspolna = c*d;
	std::cout<<"czesc wspolna zbiorow: "; cz_wspolna.printSet(); std::cout<<std::endl;
}