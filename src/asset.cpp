#include <stdexcept>
#include "asset.hpp"

int Asset::counter=0;

//Pre: cert
//Post: El resultat és un Asset amb id autoincremental i la resta d'atributs buits o initzialitzats a 0
Asset::Asset(){
    id=counter++;
    assetSymbol="";
    name="";
    num_decimals=0;
}

//Pre: assetSymbol != NULL i únic, num_decimals ha de ser entre 0 y 18, ambdós inclosos
//Post: el resultat és un asset amb els seus atributs especificats per paràmetre
Asset::Asset(const string assetSymbol, const string name, const int num_decimals){
    id=counter++;
    this->assetSymbol=assetSymbol;
    this->name=name;
    this->num_decimals=num_decimals;
}

//Pre: cert
//Post: el resultat és una còpia directa de l'objecte asset passat per paràmetre
Asset::Asset(const Asset &a){
    id=a.id;
    assetSymbol=a.assetSymbol;
    name=a.name;
    num_decimals=a.num_decimals;
    vec_prices=a.vec_prices;
}
//Post: esborra automàticament els objectes locals en sortir d'un àmbit de visibilitat
Asset::~Asset(){

}

//Pre: cert
//Post: el resultat es el id del Asset
int Asset::getAssetId(){
    return id;
}

//Pre: cert
//Post: el resultat es el símbol del Asset
string Asset::getAssetSymbol(){
    return assetSymbol;
}

//Pre: cert
//Post: el resultat es el nom del Asset
string Asset::getAssetName(){
    return name;
}

//Pre: cert
//Post: el resultat es el nombre de decimals del Asset
int Asset::getAssetNumDecimals(){
    return num_decimals;
}

//Pre: cert
//Post: el resultat es el vector de preus del Asset
vector<Price> Asset::getAssetVecPrice() const{

    return vec_prices;
}

//Pre: cert
//Post: el resultat és l'últim Price guardat a vec_prices
double Asset::getAssetLastPrice(){
    int size=(int)vec_prices.size();
    return vec_prices[size-1].getPricePrice();
}

//Pre: dataISO ha de tenir un format vàlid
//Post: el resultat troba si Asset té un preu per la data especificada per paràmetre
bool Asset::hasDataISO(const string dataISO){
    bool found = false;
    int i=0;

    while(!found && i<(int)vec_prices.size()){
        if(vec_prices[i].getPriceData()==dataISO){
            found=true;
        }
        else{
            i++;
        }
    }

    return found;
}

//Pre: Price vàlid i existent
//Post: el resultat és un nou element passat per paràmetre inclós al vector de Price del paràmetre implícit
void Asset::addPrice(const Price &p){
    vec_prices.push_back(p);
}

//Pre: cert
//Post: el resultat és l'escriptura per sortida estàndard dels atributs de l'objecte Asset
ostream& operator<<(ostream &os, const Asset &a){
    os<<a.assetSymbol << " - "<<a.name<<" - Decimals: "<< a.num_decimals<<endl;
    return os;
}

//Pre: cert
//Post: Asset passa a tenir els atributs llegits del canal estandard d'entrada
istream& operator>>(istream &is, Asset &a){
    is>>a.assetSymbol>>a.name;
    if(!(is>>a.num_decimals)){
        throw runtime_error("Error al crear Actiu "+a.assetSymbol+". Nomre de decimals en format incorrecte\n");
    }
    return is;
}

//Pre: cert
//Post: el resultat és un Asset amb els atributs de a
Asset& Asset::operator=(const Asset &a){
    this->id=a.id;
    this->assetSymbol=assetSymbol;
    this->name=name;
    this->num_decimals=num_decimals;
    return *this;
}
