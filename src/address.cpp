#include <cmath>
#include <iostream>
#include "address.hpp"

using namespace std;

int Address::counter=0;

//Constructors

// Pre: cert
// Post: El resultat és una Address amb id autoincremental i la resta d'atributs buits o initzialitzats a 0
Address::Address(){
    id = counter++;
    userId = 0;
    assetSymbol = "";
    address = "";
    label = "";
}

// Pre: cert
// Post: el resultat és una Address amb els seus atributs especificats per paràmetre (exceptuant l'id, ja que és autoincremental)
Address::Address(const int userId, const string assetSymbol, const string address, const string label){
    id=counter++;
    this->userId = userId;
    this->assetSymbol = assetSymbol;
    this->address = address;
    this->label = label;
}

// Pre: cert
// Post: el resultat és una Address amb els valors d'Address a
Address::Address(const Address &a){
    id = a.id;
    userId = a.userId;
    assetSymbol = a.assetSymbol;
    address = a.address;
    label = a.label;
}

//Destructor

// Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
Address::~Address(){
}

//Getters (Consultors)

//Pre: cert
//Post: el resultat és l'id d'Address
int Address::getId(){
    return id;
}

//Pre: cert
//Post: el resultat és l'address d'Address
string Address::getAddress(){
    return address;
}

//Pre: cert
//Post: el resultat és el símbol d'Address
string Address::getAssetSymbol(){
    return assetSymbol;
}

//Operadors

// Pre: cert
// Post: el resultat indica si la a.i i la adreça son iguals o no
bool Address::operator==(const Address &a) const{
    return id == a.id and userId == a.userId and assetSymbol == a.assetSymbol and address == a.address and label == a.label;
}

//Lectura i escriptura

// Pre: cert
// Post: s'han escrit els atributs d'address a al canal estandard de sortida
ostream& operator<<(ostream &os, const Address &a){
os<< a.assetSymbol<< " - "<< a.address<< " - "<< a.label;
    return os;
}
