#include "price.hpp"

int Price::counter=0;

//Pre: cert
//Post: el resultat es un Price amb un id autoincremental i la resta d'atributs initzialitzats a 0
Price::Price(){

    id=counter++;
    assetId=0;
    dataISO="0000-00-00";
    price=0;
}

//Pre: cap dels paràmetres pot ser NULL, assetId =! id de EUR, price > 0 en EUR
//Post: el resultat es un Price amb els atributs obtinguts per paràmetre
Price::Price(const int assetId, const string dataISO, const double price){
    id=counter++;
    this->assetId=assetId;
    this->dataISO=dataISO;
    this->price=price;
}

//Pre: cert
//Post: el resultat es una còpia directa de l'objecte Price passat per paràmetre
Price::Price(const Price &p){
    id=p.id;
    assetId=p.assetId;
    dataISO=p.dataISO;
    price=p.price;

}

//Post: esborra automàticament els objectes locals en sortir d'un àmbit de visibilitat
Price::~Price(){

}

//Pre: cert
//Post: el resultat es el id de Price
int Price::getId(){
    return id;
}

//Pre: cert
//Post: el resultat es el id del asset associat a Price
int Price::getPriceAssetId(){
    return assetId;
}

//Pre: cert
//Post: el resultat es la data de Price
string Price::getPriceData(){
    return dataISO;
}

//Pre: cert
//Post: el resultat es el valor de Price
double Price::getPricePrice(){
    return price;
}

//Sortida i entrada

//Pre: cert
//Post: el resultat és l'escriptura per sortida estàndard dels atributs de l'objecte Price
ostream& operator<<(ostream &os, const Price &p){
    os <<p.dataISO<<" "<< p.price;
    return os;
}
