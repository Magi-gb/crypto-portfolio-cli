#include <iostream>

using namespace std;

class Holding{
    private:
        int userId;
        int assetId;
        double amount;
        double avgCost;
    public:

        //Constructors

        //Pre: cert
        //Post: el resultat és un Holding amb initzialitzats a 0 o buits
        Holding();

        //Pre: amount >= 0, avgCost >= 0
        //Post: el resultat és un Holding que te com a valors userId, assetId, amount i avgCost passats per parametre
        Holding(const int userId, const int assetId, const double amount, const double avgCost);
        
        //Pre: cert
        //Post: el resultat és un Holding amb els valors del Holding h
        Holding(const Holding &h);

        //Destructor

        //Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
        ~Holding();

        //Getters (Consultors)

        //Pre: cert
        //Post: Dona el valor del userId associat al Holding
        int getHoldingUserId();

        //Pre: cert
        //Post: Dona el valor del assetId associat al Holding
        int getHoldingAssetId();

        //Pre: cert
        //Post: el resultat és l'amount de Holding 
        double getAmount();

        //Pre: cert
        //Post: el resultat és l'averege cost de Holding
        double getAvgCost();

        //Setters (Modificadors)

        //Pre: amount >= 0
        //Post: el resultat és l'assignació d'un nou amount passat per paràmetre cap al paràmetre implícit
        void setAmount(const double newAmount);

        //Methods

        //Pre: boughtQuantity a de ser > 0, pricePerUnit a de ser > 0
        //Post: s'ha actualitzat amount i avgCost respecte a la nova compra
        void buy(const double boughtQuantity, const double pricePerUnit);

        //Pre: soldQuantity ha de ser menor o igual a amount
        //Post: s'actualitza amount, i avgCost = 0 si amount també ho és
        void sell(const double soldQuantity);

        //Pre: currentPrice >= 0
        //Post: es calcula el valor actua respecte al preu de mercat donat
        double getCurrentValue(const double currentPrice);

        //Pre: currentPrice >= 0
        //Post: es calcula el guany considerant el valor actual i el preu mig de compra
        double getProfit(const double currentPrice);
};
