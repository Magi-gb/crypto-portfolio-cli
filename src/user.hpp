#include <vector>
#include "address.hpp"

class User{

private:

    int id;
    string name;
    string email;
    string password;
    vector<Address> vec_addresses;

public:

    static int counter;

    //Constructors

    // Pre: cert
    //Post: el resultat es un User amb un id autoincremental i la resta d'atributs initzialitzats a 0 o buits
    User();

    // Pre: name no buit i email amb format +@+
    // Post: el resultat es un User que te com a valors id, name i email passats per parametre
    User(const  string name, const string email, const string password);

    // Pre: cert
    // Post: el resultat es un User amb els valors del User u
    User(const User &u);

    //Destructor

    // Post: esborra automaticament els objectes locals en sortir d'un àmbit de visibilitat
    ~User();

    //Getters (Consultors)

    //Pre: cert
    //Post: Dona el valor del atribut ID
    int getId() const;

    //Pre: cert
    //Post: Dona el valor del atribut name
    string getName() const;

    //Pre: cert
    //Post: Dona el valor del atribut email
    string getEmail() const;

    //Pre: cert
    //Post: Dona el valor del atribut password
    string getPassword() const;

    //Pre: cert
    //Post: el resultat retorna el vector d'Address del usuari
    vector<Address> getVec_addresses() const;

    //Pre: Address vàlid i existent
    //Post: el resultat és un nou element passat per paràmetre inclós al vector de Address del paràmetre implícit
    void addAddress(const Address &ad);

    //Operadors

    //Lectura i escriptura

    // Pre: cert
    // Post: s'han escrit els atributs de user u al canal estandard de sortida
    friend ostream& operator<<(ostream &os, const User &u);

    // Pre: cert
    // Post: el user u passa a tenir els atributs llegits del canal estandard d'entrada
    friend istream& operator>>(istream &is, User &u);
};
