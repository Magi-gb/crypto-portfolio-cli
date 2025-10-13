#include <iostream>
#include <string>

using namespace std;

class Address{

private:

    int id;
    int userId;
    string assetSymbol;
    string address;
    string label;

public:

    static int counter;

    //Constructors

    // Pre: cert
    // Post: El resultat és una Address amb id autoincremental i la resta d'atributs buits o initzialitzats a 0
    Address();

    // Pre: cert
    // Post: el resultat és una Address amb els seus atributs especificats per paràmetre (exceptuant l'id, ja que és autoincremental)
    Address(const int userId, const string assetSymbol, const string address, const string label);


    // Pre: cert
    // Post: el resultat és una Address amb els valors d'Address a
    Address(const Address &a);

    //Destructor

    // Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
    ~Address();

    //Getters (Consultors)

    //Pre: cert
    //Post: el resultat és l'id d'Address
    int getId();

    //Pre: cert
    //Post: el resultat és l'address d'Address
    string getAddress();

    //Pre: cert
    //Post: el resultat és el símbol d'Address
    string getAssetSymbol();

    //Operadors

    // Pre: cert
    // Post: el resultat indica si la a.i i la adreça son iguals o no
    bool operator==(const Address &a) const;
    //Lectura i escriptura

    // Pre: cert
    // Post: s'han escrit els atributs d'address a al canal estandard de sortida
    friend ostream& operator<<(ostream &os, const Address &a);
};
