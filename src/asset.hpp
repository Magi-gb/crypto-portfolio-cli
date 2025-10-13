#include <iostream>
#include <string>
#include <vector>
#include "price.hpp"

using namespace std;

class Asset {
    private:
        int id;
        string assetSymbol;
        string name;
        int num_decimals;
        vector<Price> vec_prices;

    public:

        static int counter;

        //Constructors

        //Pre: cert
        //Post: El resultat és un Asset amb id autoincremental i la resta d'atributs buits o initzialitzats a 0
        Asset(); //Constructor per defecte

        //Pre: assetSymbol != NULL i únic, num_decimals ha de ser entre 0 y 18, ambdós inclosos
        //Post: el resultat és un asset amb els seus atributs especificats per paràmetre
        Asset(const string assetSymbol, const string name, const int num_decimals); //Constructor per paràmetres

        //Pre: cert
        //Post: el resultat és una còpia directa de l'objecte asset passat per paràmetre
        Asset(const Asset &a); //Constructor per còpia

        //Destructor

        //Post: esborra automàticament els objectes locals en sortir d'un àmbit de visibilitat
        ~Asset();

        //Getters (Consultors)

        //Pre: cert
        //Post: el resultat es el id del Asset
        int getAssetId();

        //Pre: cert
        //Post: el resultat es el símbol del Asset
        string getAssetSymbol();

        //Pre: cert
        //Post: el resultat es el nom del Asset
        string getAssetName();

        //Pre: cert
        //Post: el resultat es el nombre de decimals del Asset
        int getAssetNumDecimals();

        //Pre: cert
        //Post: el resultat es el vector de preus del Asset
        vector<Price> getAssetVecPrice() const;

        //Pre: cert
        //Post: el resultat és l'últim Price guardat a vec_prices
        double getAssetLastPrice();

        //Methods

        //Pre: dataISO ha de tenir un format vàlid
        //Post: el resultat troba si Asset té un preu per la data especificada per paràmetre
        bool hasDataISO(string dataISO);

        //Pre: Price vàlid i existent
        //Post: el resultat és un nou element passat per paràmetre inclós al vector de Price del paràmetre implícit
        void addPrice(const Price &p);

        //Sobrecàrrega d'operacions

        //Pre: cert
        //Post: el resultat és l'escriptura per sortida estàndard dels atributs de l'objecte Asset
        friend ostream& operator<<(ostream &os, const Asset &a);

        //Pre: cert
        //Post: Asset passa a tenir els atributs llegits del canal estandard d'entrada
        friend istream& operator>>(istream &is, Asset &a);

        //Pre: cert
        //Post: el resultat és un Asset amb els atributs de a
        Asset& operator=(const Asset &a);
};
