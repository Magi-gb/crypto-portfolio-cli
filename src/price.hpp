#include <iostream>
#include <string>

using namespace std;

class Price{
    private:
        int id;
        int assetId;
        string dataISO;
        double price;

    public:

        static int counter;

        //Constructors

        //Pre: cert
        //Post: el resultat es un Price amb un id autoincremental i la resta d'atributs initzialitzats a 0
        Price();

        //Pre: cap dels paràmetres pot ser NULL, assetId > 0, price > 0 en EUR
        //Post: el resultat es un Price amb els atributs obtinguts per paràmetre
        Price(const int assetId, const string dataISO, const double price);

        //Pre: cert
        //Post: el resultat és una còpia directa de l'objecte Price passat per paràmetre
        Price(const Price &p);

        //Destructor

        //Post: esborra automàticament els objectes locals en sortir d'un àmbit de visibilitat
        ~Price();

        //Getters (Consultors)

        //Pre: cert
        //Post: el resultat es el id de Price
        int getId();

        //Pre: cert
        //Post: el resultat es el id del asset associat a Price
        int getPriceAssetId();

        //Pre: cert
        //Post: el resultat es la data de Price
        string getPriceData();

        //Pre: cert
        //Post: el resultat es el price de Price
        double getPricePrice();

        //Operators

        //Pre: cert
        //Post: el resultat és l'escriptura per sortida estàndard dels atributs de l'objecte Price
        friend ostream& operator<<(ostream &os, const Price &p);
};
