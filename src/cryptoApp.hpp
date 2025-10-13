#include "holding.hpp"
#include "asset.hpp"
#include "user.hpp"

class CryptoApp{

    private:
        vector<Asset> vec_assets;
        vector<User> vec_users;
        vector<Holding> vec_holdings;

    public:

        //Constructor

        //Pre: cert
        //Post: el resultat és un CryptoApp
        CryptoApp();

        //Destructor

        //Post: esborra automaticament els objectes locals en sortir d'un ambit de visibilitat
        ~CryptoApp();

        //Pre: cert
        //Post: el resultat és un Asset amb els valors dels atributs, comprovats, passats per entrada estandar, 
        //o un missatge d'error amb el throw corresponent
        int createAsset();

        //Pre: cert
        //Post: el resultat és un Price amb els valors dels atributs, comprovats, passats per entrada estandar, 
        //o un missatge d'error amb el throw corresponent
        int createPrice();

        //Pre: cert
        //Post: el resultat és un User amb els valors dels atributs, comprovats, passats per entrada estandar, 
        //o un missatge d'error amb el throw corresponent
        int createUser();

        //Pre: cert
        //Post: el resultat és un Address amb els valors dels atributs, comprovats, passats per entrada estandar, 
        //o un missatge d'error amb el throw corresponent
        int createAddress();

        //Pre: els atributs han de ser certs i correctes (amount > 0, pricePerUnit >= 0)
        //Post: el resultat és un Holding amb els valors dels atributs passats per paramentre
        void createHolding(const int userId, const string assetSymbol, const double amount, const double pricePerUnit);

        //Pre: cert
        //Post: es mostren tots els Assets creats per la sortida estandar
        void listAssets();

        //Pre: cert
        //Post: es mostren tots els Prices creats per la sortida estandar
        void listPrices();

        //Pre: cert
        //Post: es mostren tots els Prices creats per la sortida estandar
        void listUsers();

        //Pre: cert
        //Post: es mostren totes les Addresses creats per la sortida estandar
        void listAddresses();

        //Pre: cert
        //Post: es mostren tots els Holdings creats per la sortida estandar, sempre que existeixi un usuari corresponent a l'entrada
        void listHoldings();

        //Operacions de negoci
        
        //Pre: cert
        //Post: es suma la quantitat passada per entrada de la crypto a la cartera del usuari passat per entrada, 
        //els atributs d'entrada són comprovats, i de ser erronis es llença un throw adient
        void buy();

        //Pre: cert
        //Post: es resta la quantitat passada per entrada de la crypto a la cartera del usuari passat per entrada, 
        //els atributs d'entrada són comprovats, i de ser erronis es llença un throw adient
        void sell();

        //Pre: cert
        //Post: es suma la quantitat d'EUR passada per entrada a la cartera del usuari passat per entrada, 
        //els atributs d'entrada són comprovats, i de ser erronis es llença un throw adient
        void addEuro();

        //Pre: cert
        //Post: es resta la quantitat d'EUR passada per entrada (o menys si el capital és menor a la quantitat demanada) a la cartera del usuari passat per entrada, 
        //els atributs d'entrada són comprovats, i de ser erronis es llença un throw adient
        void substractEuro();

        //Consultes

        //Pre: assetSymbol és valid i existent
        //Post: retorna l'últim preu del vector del asset corresponent a assetSymbol
        double priceAsset(const string assetSymbol);

        //Pre: cert
        //Post: es mostra per la sortida estandar l'últim preu registrat relacionat amb l'assetSymbol que entra per l'entrada, 
        //que serà comporvat disn la funció
        void displayLastPriceAsset();

        //Pre: existeix un usuari amb l'ID passat per parametre
        //Post: el resultat és la suma dels valors de tots els actius del usuari
        double evaluatePortfolio(const int userId);

        //Pre: existeix un usuari amb l'ID passat per parametre
        //Post: el resultat es la mitja del cost de totes les operacions fetes per l'usuari
        double totalAvgCost(const int userId);

        //Pre: existeix un usuari amb l'ID passat per parametre
        //Post: el resultat és el benefici actual que tindria l'usuari si retira els actius
        double profitAsset(const int userId);

        //Validacions

        //Pre: el assetSymbol és valid
        //Post: el resultat indica si assetSymbol és únic o no
        bool isUniqueAssetSymbol(const string assetSymbol);

        //Pre: el email és valid
        //Post: el resultat indica si email és únic o no
        bool isUniqueEmail(const string email);

        //Pre: el userId és valid
        //Post: el resultat indica si userId és únic o no
        bool isUniqueUserId(const int userId);

        //Pre: el address és valid
        //Post: el resultat indica si address és únic o no
        bool isUniqueAddress(const Address &ad);

        //Pre: el userName és valid
        //Post: el resultat indica si userName és únic o no
        bool isUniqueUserName(const string name);

        //Pre: cert
        //Post: el resultat indica si assetSymbol compleix el format o no
        bool isValidAssetSymbol(const string assetSymbol);

        //Pre: cert
        //Post: el resultat indica si dataISO compleix el format o no
        bool isValidDateFormat(const string dataISO);

        //Pre: cert
        //Post: el resultat indica si email compleix el format o no
        bool isValidEmail(const string email);

        //Pre: cert
        //Post: el resultat indica si price compleix el format o no
        bool isValidPrice(const double price);

        //Pre: cert
        //Post: el resultat indica si amount compleix el format o no
        bool isValidAmount(const double amount);

        //Pre: cert
        //Post: el resultat indica si avgCost compleix el format o no
        bool isValidAvgCost(const double avgCost);

        //Pre: cert
        //Post: el resultat indica si numDecimal compleix el format o no
        bool isValidNumDecimals(const int num_decimals);

        //Pre: assetSymbol és valid
        //Pro: el resultat és si hi ha un objecte de la classe Asset amb aquest assetSymbol
        bool existsAsset(const string assetSymbol);

        //Pre: name és valid
        //Pro: el resultat és si hi ha un objecte de la classe User amb aquest name
        bool existsUser(const string name);

        //Pre: assetSymbol i dataISO són valids
        //Pro: el resultat és si hi ha un objecte de la classe Price amb aquest assetSymbol i dataISO
        bool existsPrice(const string assetSymbol, const string dataISO);

        //Pre: userId, assetSymbol i address s.on valids
        //Post: el resultat és si hi ha un objecte de la classe Address amb aquets parametres 
        bool existsAddress(const int userId, const string assetSymbol, const string address);

        //Pre: assetSymbol i userID són valids i existents
        //Pro: el resultat és si hi ha un objecte de la classe Holding amb aquest assetSymbol i userID
        bool existsHolding(const int userId, const string assetSymbol);

        //Pre: name i email són valids
        //Pro: el resultat és si hi ha un objecte de la classe User amb aquest name i email
        bool existsUserWithNameAndEmail(const string name, const string email);

        //Utilitats internes

        //Pre: assetSymbol existeix i és valid
        //Post: el resultat és l'assetId vinculat al assetSymbol passat per parametre
        int convertAssetSymbolToAssetId(const string assetSymbol);

        //Pre: name existeix i és valid
        //Post: el resultat és l'userId vinculat al name passat per parametre
        int convertUserNameToUserId(const string name);

        //Pre: assetId existeix
        //Post: el resultat és l'objecte Asset vinculat al assetId passat per parametre
        Asset& getAssetById(const int assetId);

        //Pre: userId existeix
        //Post: el resultat és l'objecte User vinculat al userId passat per parametre
        User& getUserByUserId(const int userId);

        //Pre: userId i assetId existeix
        //Post: el resultat és l'objecte Holding vinculat al userId i assetId passats per parametre
        Holding& getHoldingByUserIdAssetId(const int userId, const int assetId);
};
