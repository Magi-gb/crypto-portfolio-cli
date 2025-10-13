#include <iostream>
#include <regex>
#include "user.hpp"

int User::counter=0;

//Constructors

//Pre: cert
//Post: el resultat es un User amb un id autoincremental i la resta d'atributs initzialitzats a 0 o buits
User::User(){
    id = counter++;
    name = "";
    email = "";
    password="";
}

//Pre: name no buit i email amb format +@+
//Post: el resultat es un User que te com a valors id, name i email passats per parametre
User::User(const string name, const string email, const string password){
    id=counter++;
    this->name = name;
    this->email = email;
    this->password=password;
}

//Pre: cert
//Post: el resultat es un User amb els valors del User u
User::User(const User &u){
    id = u.id;
    name = u.name;
    email = u.email;
    password = u.password;
    vec_addresses = u.vec_addresses;
}

//Destructor

//Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
User::~User(){
}

//Getters (Consultors)

//Pre: cert
//Post: Dona el valor del atribut ID
int User::getId() const{
    return id;
}

//Pre: cert
//Post: Dona el valor del atribut name
string User::getName() const{
    return name;
}

//Pre: cert
//Post: Dona el valor del atribut email
string User::getEmail() const{
    return email;
}

//Pre: cert
//Post: Dona el valor del atribut password
string User::getPassword() const{
    return password;
}
//Pre: cert
//Post: el resultat és el vector d'Address de l'usuari
vector<Address> User::getVec_addresses() const{
    return vec_addresses;
}

//Pre: Address vàlid i existent
//Post: el resultat és un nou element passat per paràmetre inclós al vector de Address del paràmetre implícit
void User::addAddress(const Address &ad){
    vec_addresses.push_back(ad);
}

//Operadors

//Lectura i escriptura

//Pre: cert
//Post: el resultat és l'escriptura per sortida estàndard dels atributs de l'objecte User
ostream& operator<<(ostream &os, const User &u){
    os<< u.name<<" - "<< u.email<<endl;
    return os;
}
// Pre: cert
// Post: User passa a tenir els atributs llegits del canal estandard d'entrada
istream& operator>>(istream &is, User &u){
    is>>u.name>>u.email>>u.password;
    return is;
}
