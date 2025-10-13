#include <stdexcept>
#include "holding.hpp"

//Constructors

//Pre: cert
//Post: el resultat és un Holding amb initzialitzats a 0 o buits
Holding::Holding(){

    userId=0;
    assetId=0;
    amount = 0;
    avgCost = 0;
}

//Pre: amount >= 0, avgCost >= 0
//Post: el resultat és un Holding que te com a valors userId, assetId, amount i avgCost passats per parametre
Holding::Holding(const int userId, const int assetId, const double amount, const double avgCost){
    this->userId = userId;
    this->assetId = assetId;
    this->amount = amount;
    this->avgCost = avgCost;
}

//Pre: cert
//Post: el resultat és un Holding amb els valors del Holding h
Holding::Holding(const Holding &h){
    userId = h.userId;
    assetId = h.assetId;
    amount = h.amount;
    avgCost = h.avgCost;
}

//Destructor

//Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
Holding::~Holding(){
}

//Getters (Consultors)

//Pre: cert
//Post: Dona el valor del userId associat al Holding
int Holding::getHoldingUserId(){
    return userId;
}

//Pre: cert
//Post: Dona el valor del assetId associat al Holding
int Holding::getHoldingAssetId(){
    return assetId;
}

//Pre: cert
//Post: el resultat és l'amount de Holding 
double Holding::getAmount(){
    return amount;
}

//Pre: cert
//Post: el resultat és l'averege cost de Holding
double Holding::getAvgCost(){
    return avgCost;
}

//Setters (Modificadors)

//Pre: amount >= 0
//Post: el resultat és l'assignació d'un nou amount passat per paràmetre cap al paràmetre implícit
void Holding::setAmount(const double newAmount){
    amount = newAmount;
}

//Methods

//Pre: boughtQuantity a de ser > 0, pricePerUnit a de ser > 0
//Post: s'ha actualitzat amount i avgCost respecte a la nova compra
void Holding::buy(const double boughtQuantity, const double pricePerUnit){

    double oldAmount=amount;
    double oldAvgCost=avgCost;

    double newAmount= oldAmount+boughtQuantity;
    double newAvgCost=(oldAmount*oldAvgCost+boughtQuantity*pricePerUnit)/newAmount;

    amount = newAmount;
    avgCost= newAvgCost;

}

//Pre: soldQuantity ha de ser menor o igual a amount
//Post: s'actualitza amount, i avgCost = 0 si amount també ho és
void Holding::sell(const double soldQuantity) {

    amount=amount-soldQuantity;

    if(amount <= 0.0){
        avgCost=0.0;
    }
}

//Pre: currentPrice >= 0
//Post: es calcula el valor actua respecte al preu de mercat donat
double Holding::getCurrentValue(const double currentPrice){
    double currentValue = amount * currentPrice;
    return currentValue;
}

//Pre: currentPrice >= 0
//Post: es calcula el guany considerant el valor actual i el preu mig de compra
double Holding::getProfit(double currentPrice){
    double profit = amount * currentPrice - amount * avgCost;
    return profit;
}
