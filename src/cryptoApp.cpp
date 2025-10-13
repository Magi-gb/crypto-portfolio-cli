#include <regex>
#include <sstream>

#include "cryptoApp.hpp"

//Pre: cert
//Post: el resultat és un CryptoApp
CryptoApp::CryptoApp(){

}

//Destructor

//Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
CryptoApp::~CryptoApp(){

}

//Pre: cert
//Post: el resultat és un Asset amb els valors dels atributs, comprovats, passats per entrada estandar, o un missatge d'error amb el throw corresponent
int CryptoApp::createAsset(){
    Asset a;
    cin>>a;

    if(isValidAssetSymbol(a.getAssetSymbol())==false){
        throw runtime_error("Error al crear Actiu " + a.getAssetSymbol()+ ". L'actiu no pot estar buit\n");
    }
    else if(isUniqueAssetSymbol(a.getAssetSymbol())==false){
        throw runtime_error("Error al crear Actiu " + a.getAssetSymbol()+". L'Actiu ja existeix\n");
    }else if(isValidNumDecimals(a.getAssetNumDecimals())==false){
        throw runtime_error("Error al crear Actiu "+a.getAssetSymbol()+". Nombre de decimals invàlid.\n");
    }else if((int)vec_assets.size()==5000){
        throw runtime_error("Error al crear Actiu"+a.getAssetSymbol()+". S'ha arribat al limit d'actius\n");

    }else{
        cout << "Actiu " << a.getAssetSymbol()<< " creat correctament\n";
        vec_assets.push_back(a);
    }
    return a.getAssetId();
}

//Pre: cert
//Post: el resultat és un Price amb els valors dels atributs, comprovats, passats per entrada estandar, o un missatge d'error amb el throw corresponent
int CryptoApp::createPrice(){

    string assetSymbol, dataISO;
    double price;
    cin>> assetSymbol>>dataISO;
    int aux=0;

    if(cin>>price){
        if(existsAsset(assetSymbol)){
            int assetId=convertAssetSymbolToAssetId(assetSymbol);
            if(isValidAssetSymbol(assetSymbol)==false){
                throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". L'actiu no existeix.\n");
            }else if(isValidDateFormat(dataISO)==false){
                throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". La data incorrecte en format.\n");
            }else if(isValidPrice(price)==false){
                throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". El preu està en format incorrecte.\n");
            }else if(existsPrice(assetSymbol, dataISO)==true){
                throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". Ja s'ha introduït un preu per a aquest actiu i data\n");
            }else if(assetSymbol=="EUR"){
                throw runtime_error("Error al crear Preu de " + assetSymbol + " a " + dataISO + ". No es permet crear preus per a EUR\n");
            }else{
                Price p(assetId, dataISO, price);
                aux=p.getId();
                getAssetById(assetId).addPrice(p);
                cout << "Preu de " << assetSymbol << " a " << dataISO << " creat correctament\n";
            }
        }else{
            throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". L'actiu no existeix\n" );
        }
    }else{
        cin.clear();
        cin.ignore(10000, '\n');
        throw runtime_error("Error al crear Preu de " +assetSymbol+ " a " +dataISO+ ". El preu està en format incorrecte.\n");
    }


    return aux;
}

//Pre: cert
//Post: el resultat és un User amb els valors dels atributs, comprovats, passats per entrada estandar, o un missatge d'error amb el throw corresponent
int CryptoApp::createUser(){
    User u;
    cin>>u;

    if(u.getName().length() > 50){
        throw runtime_error("Error al crear Usuari. Nom > 50 caràcters\n");
    }
    else if(isValidEmail(u.getEmail())==false){
        throw runtime_error("Error al crear Usuari. Email incorrecte\n");
    }
    else if(u.getPassword().length()>50){
        throw runtime_error("Error al crear Usuari. Contrasenya >50 caràcters\n");
    }
    else if((int)vec_users.size()==5000){
        throw runtime_error("Error al crear Usuari. S'ha arribat al limit d'usuaris\n");
    }else if(existsUserWithNameAndEmail(u.getName(), u.getEmail())){
        throw runtime_error("Error al crear Usuari "+u.getName()+"\n");
    }
    else{
        if((u.getId()==0)&&(isUniqueAssetSymbol("EUR"))){
            Asset eur("EUR", "Euro", 2);
            vec_assets.push_back(eur);
        }
        cout << "Usuari " << u.getName() << " amb email "<< u.getEmail() << " creat correctament\n";
        vec_users.push_back(u);
        createHolding(u.getId(), "EUR", 0, 1);
    }
    return u.getId();
}

//Pre: cert
//Post: el resultat és un Address amb els valors dels atributs, comprovats, passats per entrada estandar, o un missatge d'error amb el throw corresponent
int CryptoApp::createAddress(){

    string line;
    getline(cin, line);

    string name, assetSymbol, address, label;
    istringstream ss(line);
    ss>>name>>assetSymbol>>address;
    getline(ss, label);

    if (!label.empty() && label.front() == '"')
        label.erase(0, 1);

    int aux=0;

    if(existsUser(name)){
        int userId=convertUserNameToUserId(name);
        if(existsAddress(userId, assetSymbol, address)){
            throw runtime_error("Error al crear Adreça. Adreça duplicada per aquest Usuari i Actiu\n");
        }else{
            cout << "Adreça afegida a " << name << endl;
            label.pop_back();
            label.erase(0,2);
            Address ad(userId, assetSymbol,address, label);
            aux=ad.getId();
            getUserByUserId(userId).addAddress(ad);
        }
    }else{
        throw runtime_error("Error al crear Adreça. L'usuari " +name+ " no existeix\n");
    }

    return aux;
}

//Pre: els atributs han de ser certs i correctes (amount > 0, pricePerUnit >= 0)
//Post: el resultat és un Holding amb els valors dels atributs passats per paramentre
void CryptoApp::createHolding(const int userId, const string assetSymbol, const double amount, const double pricePerUnit){

    Holding h(userId, convertAssetSymbolToAssetId(assetSymbol), amount, pricePerUnit);
    vec_holdings.push_back(h);

}

//Pre: cert
//Post: es mostren tots els Assets creats per la sortida estandar
void CryptoApp::listAssets(){
    cout<<"--------------------\n";
    for(int i=0; i<(int)vec_assets.size(); i++){
        cout << vec_assets[i];
    }
    cout<<"--------------------\n";
}

//Pre: cert
//Post: es mostren tots els Prices creats per la sortida estandar
void CryptoApp::listPrices(){

    string assetSymbol;
    cin>>assetSymbol;

    if(existsAsset(assetSymbol)){
        int assetId=convertAssetSymbolToAssetId(assetSymbol);
        if(getAssetById(assetId).getAssetVecPrice().empty()){
            throw runtime_error("Error al mostrar Preus. Actiu " +assetSymbol+ " no te preus\n");
        }
        cout<<"--------------------\n";
        int size = (int)getAssetById(assetId).getAssetVecPrice().size();
        for(int i=0;i<size;i++){
            cout << assetSymbol<< " "<<getAssetById(assetId).getAssetVecPrice()[i] <<endl;
        }
        cout<<"--------------------\n";
    }
    else{
        throw runtime_error("Error al mostrar Preus. Actiu " +assetSymbol+ " no existeix\n");
    }
}

//Pre: cert
//Post: es mostren tots els Prices creats per la sortida estandar
void CryptoApp::listUsers(){
    cout<<"--------------------\n";
    for(int i=0; i<(int)vec_users.size();i++){
        cout << vec_users[i];
    }
    cout<<"--------------------\n";
}

//Pre: cert
//Post: es mostren totes les Addresses creats per la sortida estandar
void CryptoApp::listAddresses(){

    string name;
    cin>>name;

    cout<<"--------------------\n";
    if(existsUser(name)){
        int userId=convertUserNameToUserId(name);

        for(int i=0; i<(int)getUserByUserId(userId).getVec_addresses().size();i++){
            cout << getUserByUserId(userId).getVec_addresses()[i] <<endl;
        }

    }else{
        throw runtime_error("Error al mostrar Adreces. Usuari " +name+ " no existeix\n");
    }
}

//Pre: cert
//Post: es mostren tots els Holdings creats per la sortida estandar, sempre que existeixi un usuari corresponent a l'entrada
void CryptoApp::listHoldings(){
    string name;
    cin>>name;

    if(existsUser(name)==false){
        throw runtime_error("Error al mostrar tenencies per l'usuari: "+name+"\n");
    }else{
        int userId=convertUserNameToUserId(name);
        cout<<"--------------------\n";
        for(int i=0; i<(int)vec_holdings.size();i++){
            if(vec_holdings[i].getHoldingUserId()==userId){
                int assetId=vec_holdings[i].getHoldingAssetId();
                string assetSymbol=getAssetById(assetId).getAssetSymbol();
                if(getAssetById(assetId).getAssetSymbol()=="EUR"){
                    cout << "EUR - amount: " << vec_holdings[i].getAmount()<<endl;
                }else{
                    cout << assetSymbol  << " - amount: " << vec_holdings[i].getAmount() << " - avgCost: "<< vec_holdings[i].getAvgCost()<< " - preuActual: " << priceAsset(assetSymbol)<<endl;
                }
            }
        }

        cout<<"Total avgCost: "<< totalAvgCost(userId) <<" - Total preuActual: "<<evaluatePortfolio(userId)<<" - Guany total: "<< profitAsset(userId)<<endl;
        cout<<"--------------------\n";
    }

}

//Pre: cert
//Post: es suma la quantitat passada per entrada de la crypto a la cartera del usuari passat per entrada, els atributs d'entrada són comprovats,
//i de ser erronis es llença un throw adient
void CryptoApp::buy(){

    string name, assetSymbol;
    double quantity;

    cin>>name>>assetSymbol;

    if(cin>>quantity){
        if(existsUser(name)==false){
            throw runtime_error("Error al comprar " +assetSymbol+ ". Usuari " +name+ " no existeix\n");
        }
        else if(existsAsset(assetSymbol)==false){
            throw runtime_error("Error al comprar " +assetSymbol+ ". Actiu " +assetSymbol+ " no existeix\n");
        }
        else if(getAssetById(convertAssetSymbolToAssetId(assetSymbol)).getAssetVecPrice().empty()){
            throw runtime_error("Error al comprar " +assetSymbol+ ". Actiu " +assetSymbol+ " no té un preu actual\n");
        }else if(existsAsset("EUR")==false){
            throw runtime_error("Error al comprar "+assetSymbol+". Actiu Euro no existeix\n");
        }else{

            int userId=convertUserNameToUserId(name);
            int idEUR=convertAssetSymbolToAssetId("EUR");
            double initialEUR = getHoldingByUserIdAssetId(userId, idEUR).getAmount();

            if((quantity*priceAsset(assetSymbol))>initialEUR){
                throw runtime_error("Error al comprar "+assetSymbol+". L'usuari no disposa de fons suficients\n");
            }else{

                double pricePerUnit= priceAsset(assetSymbol);
                double eursToSubstract = quantity*pricePerUnit;

                if(existsHolding(userId, assetSymbol)==true){
                    int assetId=convertAssetSymbolToAssetId(assetSymbol);
                    getHoldingByUserIdAssetId(userId, assetId).buy(quantity, pricePerUnit);
                }else{
                    createHolding(userId,assetSymbol, quantity, pricePerUnit);
                }
                getHoldingByUserIdAssetId(userId, idEUR).setAmount(initialEUR-eursToSubstract);
                cout << "Compra de " << quantity << " unitats registrada per " << name << " en " << assetSymbol <<endl;
            }
        }
    }else{
        throw runtime_error("Error al comprar "+assetSymbol+". La quantitat està en format incorrecte\n");
    }


}

//Pre: cert
//Post: es resta la quantitat passada per entrada de la crypto a la cartera del usuari passat per entrada, els atributs d'entrada són comprovats,
//i de ser erronis es llença un throw adient
void CryptoApp::sell(){

    string name, assetSymbol;
    double quantity;

    cin>>name>> assetSymbol;
    if(cin>>quantity){
        if(existsUser(name)==false){
            throw runtime_error("Error al vendre " +assetSymbol+ ". Usuari " +name+ " no existeix\n");
        }
        else if(existsAsset(assetSymbol)==false){
            throw runtime_error("Error al vendre " +assetSymbol+ ". Actiu " +assetSymbol+ " no existeix\n");
        }
        else if(existsHolding(convertUserNameToUserId(name), assetSymbol)==false){
            throw runtime_error("Error al vendre " +assetSymbol+ ". L’usuari no posseeix l’actiu " +assetSymbol+ "\n");
        }
        else if(getAssetById(convertAssetSymbolToAssetId(assetSymbol)).getAssetVecPrice().empty()){
            throw runtime_error("Error al vendre " +assetSymbol+ ". Actiu " +assetSymbol+ " no té un preu actual\n");
        }
        else{

            int userId=convertUserNameToUserId(name);
            int assetId=convertAssetSymbolToAssetId(assetSymbol);
            int idEUR=convertAssetSymbolToAssetId("EUR");
            double initialEUR = getHoldingByUserIdAssetId(userId, idEUR).getAmount();

            if(quantity>getHoldingByUserIdAssetId(userId, assetId).getAmount()){
                quantity=getHoldingByUserIdAssetId(userId, assetId).getAmount();
            }
            double eursToAdd=quantity*priceAsset(assetSymbol);

            getHoldingByUserIdAssetId(userId, assetId).sell(quantity);
            getHoldingByUserIdAssetId(userId, idEUR).setAmount(initialEUR+eursToAdd);

            cout << "Venda de "<<quantity<<" unitats registrada per " <<name<< " en " <<assetSymbol<< "\n";
        }
    }else{
        throw runtime_error("Error al vendre "+assetSymbol+". La quantitat està en format incorrecte\n");
    }


}

//Pre: cert
//Post: es suma la quantitat d'EUR passada per entrada a la cartera del usuari passat per entrada, els atributs d'entrada són comprovats, 
//i de ser erronis es llença un throw adient
void CryptoApp::addEuro(){

    string name;
    double quantity;

    cin>>name;

    if(cin>>quantity){
        if((existsUser(name)==false)){
            throw runtime_error("Error al afegir Euros a l'usuari " +name+ ". L'usuari no existeix\n");
        }
        else if(quantity < 0){
            throw runtime_error("Error al afegir Euros a l'usuari " +name+ ". Quantitat incorrecte\n");
        }
        else if(existsAsset("EUR")==false){
            throw runtime_error("Error al afegir Euros a l’usuari "+name+". Actiu Euro no existeix\n");
        }
        else{
            cout << quantity << " Euros afegits correctament a l'usuari " << name << endl;
            int userId=convertUserNameToUserId(name);
            int idEUR=convertAssetSymbolToAssetId("EUR");
            double initialEUR = getHoldingByUserIdAssetId(userId, idEUR).getAmount();

            if (initialEUR==0){
                getHoldingByUserIdAssetId(userId, idEUR).setAmount(quantity);
            }
            else{
                getHoldingByUserIdAssetId(userId, idEUR).setAmount(initialEUR+quantity);
            }
        }
    }else{
        throw runtime_error("Error al afegir Euros. La quantitat està en format incorrecte\n");
    }

}

//Pre: cert
//Post: es resta la quantitat d'EUR passada per entrada (o menys si el capital és menor a la quantitat demanada) a la cartera del usuari passat per entrada, 
//els atributs d'entrada són comprovats, i de ser erronis es llença un throw adient
void CryptoApp::substractEuro(){

    string name;
    double quantity;
    cin>>name;

    if(cin>>quantity){
        if(existsUser(name)==false){
        throw runtime_error("Error al retirar Euros a l'usuari " +name+ ". L'usuari no existeix\n");
    }
    else if(quantity < 0){
        throw runtime_error("Error al retirar Euros a l'usuari " +name+ ". Quantitat incorrecte\n");
    }
    else if(existsAsset("EUR")==false){
        throw runtime_error("Error al retirar Euros a l'usuari "+name+". Actiu Euro no existeix\n");
    }
    else{
        int userId=convertUserNameToUserId(name);
        int idEUR=convertAssetSymbolToAssetId("EUR");

        double initialEUR = getHoldingByUserIdAssetId(userId, idEUR).getAmount();

        if(quantity>initialEUR){
            getHoldingByUserIdAssetId(userId, idEUR).setAmount(0);
            cout << initialEUR <<  " Euros retirats correctament a l'usuari " << name << endl;
        }else{
            getHoldingByUserIdAssetId(userId, idEUR).setAmount(initialEUR-quantity);
            cout << quantity <<  " Euros retirats correctament a l'usuari " << name << endl;
            }
        }
    }else{
        throw runtime_error("Error al afegir Euros. La quantitat està en format incorrecte\n");
    }
}

//Pre: assetSymbol és valid i existent
//Post: retorna l'últim preu del vector del asset corresponent a assetSymbol
double CryptoApp::priceAsset(const string assetSymbol){
    int assetId=convertAssetSymbolToAssetId(assetSymbol);
    double priceAsset= getAssetById(assetId).getAssetLastPrice();
    return priceAsset;
}

//Pre: cert
//Post: es mostra per la sortida estandar l'últim preu registrat relacionat amb l'assetSymbol que entra per l'entrada, que serà comporvat disn la funció
void CryptoApp::displayLastPriceAsset(){
    string assetSymbol;
    cin>>assetSymbol;

    if(existsAsset(assetSymbol)==false){
        throw runtime_error("Error al mostrar preu actual de l'actiu "+assetSymbol+". Actiu no existent\n");
    }else if(getAssetById(convertAssetSymbolToAssetId(assetSymbol)).getAssetVecPrice().empty()){
        throw runtime_error("Error al mostrar preu actual de l'actiu "+assetSymbol+". L'actu no té històric de preus.\n");
    }else{
        int assetId=convertAssetSymbolToAssetId(assetSymbol);
        int size = getAssetById(assetId).getAssetVecPrice().size();
        cout<<"--------------------\n"<<assetSymbol<<" "<<getAssetById(assetId).getAssetVecPrice()[size-1]<<"\n"<<"--------------------\n";
    }
    
}

//Pre: existeix un usuari amb l'ID passat per parametre
//Post: el resultat és la suma dels valors de tots els actius del usuari
double CryptoApp::evaluatePortfolio(const int userId){

    double portfolioValue=0;

    for(int i=0;i<(int)vec_holdings.size();i++){
        if(vec_holdings[i].getHoldingUserId()==userId){
            int assetId = vec_holdings[i].getHoldingAssetId();
            if(getAssetById(assetId).getAssetSymbol()=="EUR"){
                portfolioValue=portfolioValue+vec_holdings[i].getAmount();
            }else{
                portfolioValue= portfolioValue + (priceAsset(getAssetById(assetId).getAssetSymbol())*vec_holdings[i].getAmount());
            }

        }
    }

    return portfolioValue;
}

//Pre: existeix un usuari amb l'ID passat per parametre
//Post: el resultat es la mitja del cost de totes les operacions fetes per l'usuari
double CryptoApp::totalAvgCost(const int userId){
    double portfolioAvgCost=0;

    for(int i=0;i<(int)vec_holdings.size();i++){
        if(vec_holdings[i].getHoldingUserId()==userId){
            int assetId = vec_holdings[i].getHoldingAssetId();
            if(getAssetById(assetId).getAssetSymbol()=="EUR"){
                portfolioAvgCost=portfolioAvgCost+vec_holdings[i].getAmount();
            }else{
                portfolioAvgCost= portfolioAvgCost + (vec_holdings[i].getAvgCost()*vec_holdings[i].getAmount());
            }

        }
    }

    return portfolioAvgCost;
}

//Pre: existeix un usuari amb l'ID passat per parametre
//Post: el resultat és el benefici actual que tindria l'usuari si retira els actius
double CryptoApp::profitAsset(const int userId){
    double profit=evaluatePortfolio(userId)-totalAvgCost(userId);
    return profit;
}

//Pre: el assetSymbol és valid
//Post: el resultat indica si assetSymbol és únic o no
bool CryptoApp::isUniqueAssetSymbol(const string assetSymbol){

    int i=0;
    bool found = false;

    while(i < (int)vec_assets.size() && !found){
        if(vec_assets[i].getAssetSymbol() == assetSymbol){
            found = true;
        }
        i++;
    }
    return !found;
}

//Pre: el email és valid
//Post: el resultat indica si email és únic o no
bool CryptoApp::isUniqueEmail(const string email){

    int i=0;
    bool found = false;

    while(i < (int)vec_users.size() && !found){
        if(vec_users[i].getEmail() == email){
            found = true;
        }
        i++;
    }
    return !found;
}

//Pre: el userId és valid
//Post: el resultat indica si userId és únic o no
bool CryptoApp::isUniqueUserId(const int userId){

    int i=0;
    bool found = false;

    while(i < (int)vec_users.size() && !found){
        if(vec_users[i].getId() == userId){
            found = true;
        }
        i++;
    }
    return !found;
}

//Pre: el address és valid
//Post: el resultat indica si address és únic o no
bool CryptoApp::isUniqueAddress(const Address &ad){

    int i=0;
    bool found = false;

    while(i < (int)vec_users.size() && !found){
        if(vec_users[i].getVec_addresses()[i] == ad){
            found = true;
        }
        i++;
    }
    return !found;
}

//Pre: el userName és valid
//Post: el resultat indica si userName és únic o no
bool CryptoApp::isUniqueUserName(const string name){
    int i=0;
    bool found = false;

    while(i<(int)vec_users.size() && !found){
        if(vec_users[i].getName() == name){
            found = true;
        }
        i++;
    }
    return !found;
}

//Pre: cert
//Post: el resultat indica si assetSymbol compleix el format o no
bool CryptoApp::isValidAssetSymbol(const string assetSymbol){
    bool isValid=true;
    if (assetSymbol==" "){
        isValid=false;
    }

    return isValid;

}

//Pre: cert
//Post: el resultat indica si dataISO compleix el format o no
bool CryptoApp::isValidDateFormat(const string dataISO){

    vector<int> dayXMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    regex format("^\\d{4}-\\d{2}-\\d{2}$");

    if(!regex_match(dataISO, format)){
        return false;
    }

    int year = stoi(dataISO.substr(0, 4));
    int month  = stoi(dataISO.substr(5, 2));
    int day  = stoi(dataISO.substr(8, 2));

    //Comprobem si l'any de traspàs
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        dayXMonth[1] = 29;
    }

    if(year > 2025){
        return false;
    } else if(month < 1 or month > 12){
        return false;
    } else if(day < 1 or day > dayXMonth[month-1]){
        return false;
    } else {
        return true;
    }

}

//Pre: cert
//Post: el resultat indica si email compleix el format o no
bool CryptoApp::isValidEmail(const string email){
    bool isValid=true;
    if(regex_match(email, regex(R"(.+@.+)"))==false){
        isValid=false;
    }
    return isValid;
}

//Pre: cert
//Post: el resultat indica si price compleix el format o no
bool CryptoApp::isValidPrice(const double price){
    bool isValid=true;

    if((price<0)){
        isValid=false;
    }

    return isValid;
}

//Pre: cert
//Post: el resultat indica si amount compleix el format o no
bool CryptoApp::isValidAmount(const double amount){
    bool isValid=true;

    if(amount<0){
        isValid=false;
    }

    return isValid;
}

//Pre: cert
//Post: el resultat indica si avgCost compleix el format o no
bool CryptoApp::isValidAvgCost(const double avgCost){
    bool isValid=true;

    if(avgCost<0){
        isValid=false;
    }

    return isValid;
}

//Pre: cert
//Post: el resultat indica si numDecimal compleix el format o no
bool CryptoApp::isValidNumDecimals(const int num_decimals){
    bool isValid=true;

    if((num_decimals<0)||(num_decimals>18)){
        isValid=false;
    }

    return isValid;
}

//Pre: assetSymbol és valid
//Pro: el resultat és si hi ha un objecte de la classe Asset amb aquest assetSymbol
bool CryptoApp::existsAsset(const string assetSymbol){

    bool exists = false;
    int i=0;

    while (i < (int)vec_assets.size()&&exists==false) {
        if (vec_assets[i].getAssetSymbol() == assetSymbol){
            exists=true;
        }else{
            i++;
        }
    }

    return exists;
}

//Pre: name és valid
//Pro: el resultat és si hi ha un objecte de la classe User amb aquest name
bool CryptoApp::existsUser(const string name){

    bool exists = false;
    int i=0;

    while (i < (int)vec_users.size()&&exists==false) {
        if (vec_users[i].getName() == name){
            exists=true;
        }else{
            i++;
        }
    }

    return exists;
}

//Pre: assetSymbol i dataISO són valids
//Pro: el resultat és si hi ha un objecte de la classe Price amb aquest assetSymbol i dataISO
bool CryptoApp::existsPrice(const string assetSymbol, const string dataISO){
    bool found= false;
    int i=0;
    int assetId = convertAssetSymbolToAssetId(assetSymbol);
    int size=(int)getAssetById(assetId).getAssetVecPrice().size();

    while((found == false) && (i<size)){
        if(getAssetById(assetId).hasDataISO(dataISO)&&getAssetById(assetId).getAssetSymbol()==assetSymbol){
            found = true;
        }else{
            i++;
        }
    }

    return found;
}

//Pre: userId, assetSymbol i address s.on valids
//Post: el resultat és si hi ha un objecte de la classe Address amb aquets parametres 
bool CryptoApp::existsAddress(const int userId, const string assetSymbol, const string address){

    bool found= false;
    int i=0;
    int size=(int)getUserByUserId(userId).getVec_addresses().size();

    while((found == false) && (i<size)){
        if((getUserByUserId(userId).getVec_addresses()[i].getAddress()==address)&&(getUserByUserId(userId).getVec_addresses()[i].getAssetSymbol()==assetSymbol)){
            found = true;
        }else{
            i++;
        }
    }

    return found;
}

//Pre: assetSymbol i userID són valids i existents
//Pro: el resultat és si hi ha un objecte de la classe Holding amb aquest assetSymbol i userID
bool CryptoApp::existsHolding(const int userId, const string assetSymbol){
    int i=0;
    int assetId= convertAssetSymbolToAssetId(assetSymbol);

    while(i <(int)vec_holdings.size()){
        if(((vec_holdings[i].getHoldingUserId())==userId)&&((vec_holdings[i].getHoldingAssetId())==(assetId))){
            return true;
        }else{
            i++;
        }
    }
    return false;
}

//Pre: name i email són valids
//Pro: el resultat és si hi ha un objecte de la classe User amb aquest name i email
bool CryptoApp::existsUserWithNameAndEmail(const string name, const string email){
    for (int i=0;i<(int)vec_users.size();i++) {
        if (getUserByUserId(convertUserNameToUserId(name)).getName() == name && getUserByUserId(convertUserNameToUserId(name)).getEmail() == email) {
            return true;
        }
    }
    return false;
}

//Pre: assetSymbol existeix i és valid
//Post: el resultat és l'assetId vinculat al assetSymbol passat per parametre
int CryptoApp::convertAssetSymbolToAssetId(const string assetSymbol){
    int i=0;
    int assetId=-1;

    while(i<(int)vec_assets.size()){
        if(vec_assets[i].getAssetSymbol()==assetSymbol){
            return vec_assets[i].getAssetId();
        }
        else{
            i++;
        }
    }
    return assetId;
}

//Pre: name existeix i és valid
//Post: el resultat és l'userId vinculat al name passat per parametre
int CryptoApp::convertUserNameToUserId(const string name){
    int i=0;
    int userId=-1;

    while(i<(int)vec_users.size()){
        if(vec_users[i].getName()==name){
            return vec_users[i].getId();
        }
        else{
            i++;
        }
    }
    return userId;
}

//Pre: assetId existeix
//Post: el resultat és l'objecte Asset vinculat al assetId passat per parametre
Asset& CryptoApp::getAssetById(const int assetId){

    int index = 0;

    for(int i=0; i<(int)vec_assets.size();i++){
        if(vec_assets[i].getAssetId()==assetId){
            index=i;
        }
    }

    return vec_assets[index];
}

//Pre: userId existeix
//Post: el resultat és l'objecte User vinculat al userId passat per parametre
User& CryptoApp::getUserByUserId(const int userId){
    int index = 0;

    for(int i=0; i<(int)vec_users.size();i++){
        if(vec_users[i].getId()==userId){
            index=i;
        }
    }

    return vec_users[index];
}

//Pre: userId i assetId existeix
//Post: el resultat és l'objecte Holding vinculat al userId i assetId passats per parametre
Holding& CryptoApp::getHoldingByUserIdAssetId(const int userId, const int assetId){

    int index = 0;

    for(int i=0; i<(int)vec_holdings.size();i++){
        if((vec_holdings[i].getHoldingUserId()==(userId))&&(vec_holdings[i].getHoldingAssetId()==(assetId))){
            index=i;
        }
    }

    return vec_holdings[index];
}
