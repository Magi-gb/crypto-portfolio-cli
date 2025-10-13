#include <iostream>
#include <exception>
#include "cryptoApp.hpp"
using namespace std;

//Pre: cert
//Post: es mostra per la sortida estandar el títol de l'aplicació
void displayProgramTitle(){
    cout<<"========================================\n    Gestor de Carteres Cripto - CLI\n========================================\n";
}

//Pre: cert
//Post: es mostra per la sortida estandar el menu de l'aplicació
void displayMenu(){

    cout<<"\nSeleccioneu una opció:\n\n";

    cout<<"1. crearActiu\t\t\t- Donar d'alta un nou actiu\n2. crearPreu\t\t\t- Afegir un preu diari a un actiu\n3. mostrarActius\t\t- Llistar tots els actius\n4. mostrarPreusActiu\t\t- Mostrar tots els preus d'un actiu\n\n5. crearUsuari\t\t\t- Donar d'alta un nou usuari\n6. mostrarUsuaris\t\t- Llistar tots els usuaris\n7. crearAdreça\t\t\t- Afegir una nova adreça de wallet\n8. mostrarAdrecesUsuari\t\t- Mostrar totes les adreces d'un usuari\n\n9. afegirEuros\t\t\t- Afegir Euros al saldo d'un usuari\n10. retirarEuros\t\t- Retirar Euros del saldo d'un usuari\n\n11. comprar\t\t\t- Comprar un actiu pera un usuari\n12. vendre\t\t\t- Vendre un actiu d'un Usuari\n13. preuActualActiu\t\t- Consultar l'últim preu d'un actiu\n14. carteraDeUsuari\t\t- Consultar la cartera i el guany total d'un usuari\n\n0. acabar\t\t\t- Sortir del programa\n\n";

    cout<<"----------------------------------------\n";

}

//Pre: cert
//Post: es selecciona l'opció del menu desitjada o si l'input no es valid es torna a imprimir el menu
string optionSelector(string &selectedOption){
    // cout<<"Introduïu l'opció desitjada: ";
    cin>>selectedOption;

    return selectedOption;
}

int main(){

    string selectedOption;
    CryptoApp app;

    displayProgramTitle();
    displayMenu();
    cout<<"Introduïu l'opció desitjada: \n";
    optionSelector(selectedOption);


    while(selectedOption!="acabar"){
        if(selectedOption=="crearActiu"){
            try{
                app.createAsset();
            }catch(const runtime_error& e){
                cout<<e.what();
            }
            optionSelector(selectedOption);
        }
        else if(selectedOption=="crearPreu"){
            try{
                app.createPrice();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="mostrarActius"){
            try{
                app.listAssets();
            }catch(const runtime_error& e){
                cout<<e.what();
            }
            optionSelector(selectedOption);
        }
        else if(selectedOption=="mostrarPreusActiu"){
            try{
                app.listPrices();
            }catch(const runtime_error& e){
                cout<<e.what();
            }
            optionSelector(selectedOption);
        }
        else if(selectedOption=="crearUsuari"){
            try{
                app.createUser();
            }catch(const runtime_error& e){
                cout<<e.what();
            }
            optionSelector(selectedOption);
        }
        else if(selectedOption=="crearAdreca"){
            try{
                app.createAddress();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="mostrarUsuaris"){
            try{
                app.listUsers();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="afegirEuros"){
            try{
                app.addEuro();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="retirarEuros"){
            try{
                app.substractEuro();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="mostrarAdrecesUsuari"){
            try{
                app.listAddresses();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="comprar"){
            try{
                app.buy();
            }catch(const runtime_error& e){
                cout<<e.what();
            }
            optionSelector(selectedOption);
        }
        else if(selectedOption=="vendre"){
            try{
                app.sell();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="preuActualActiu"){
            try{
                app.displayLastPriceAsset();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else if(selectedOption=="carteraDeUsuari"){
            try{
                app.listHoldings();
            }catch(const runtime_error& e){
                cout<<e.what();
            }

            optionSelector(selectedOption);
        }
        else{
            cout<<"Opció no vàlida, seleccioneu una vàlida\n";
            displayMenu();
            cout<<"Introduïu l'opció desitjada: ";
            optionSelector(selectedOption);
        }
    }

    return 0;
}
