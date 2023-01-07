#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "license.h"

// moped
// #include<string>
// #include<map>
// #include<vector>
// #include<memory>
// #include<iostream>

class License;

using namespace std;

class Person : public std::enable_shared_from_this<Person>
{
protected:
    string name; // Name der Person. (Zur Vereinfachung darf davon ausgegangen werden, dass die Namen der Person-Objekte eindeutig sind.)
    unsigned int wealth;
    map<string, unique_ptr<License>> licenses; // Map von aktuellen Lizenzen.
public:
    Person(string name, unsigned int wealth = 0); // Setzt Instanzvariablen, wobei name nicht leer sein darf.
    virtual ~Person() = default;
    void work(string guild); // Falls eine Lizenz fuer guild vorhanden ist und man diese noch benutzen kann, wird die Lizenz benutzt und die Person arbeitet fuer das auf der Lizenz gedruckte Gehalt....
    virtual void work(string guild, unsigned int) = 0;
    // virtual void work(unsigned int) = 0; todo
    void increase_wealth(unsigned int i);                  // Erhoeht wealth um i.
    string get_name() const;                               // Liefert name.
    bool pay_fee(unsigned int i);                          // Sollte das Vermoegen der Person nicht ausreichen, um die Gebuehr i zu bezahlen oder i 0 sein, ist false zu liefern. Ansonsten wird das Vermoegen reduziert um i und true returniert.
    void receive_license(unique_ptr<License> l);           // Speichert die Lizenz l in der Map der Lizenzen der Person. Sollte es bereits eine Lizenz mit dem gleichen Namen geben, ist die alte Lizenz zu zerstoeren.
    void transfer_license(string l, shared_ptr<Person> p); // Uebergibt die Lizenz mit dem Namen l vom this-Objekt an Person p und entfernt diese aus den Lizenzen vom this-Objekt...
    bool eligible(string l) const;                         //  Liefert true falls eine Lizenz mit Namen l vorhanden ist und diese gueltig ist, ansonsten false.
    virtual ostream &print(ostream &o) const;              // Die Klasse Person hat folgendes Ausgabeformat.
    // Format: name, wealth Coins, {license_0, license_1, ..., license_n}]
    // ostream &print(ostream &o) const; // Gibt das Objekt auf den ostream o aus.
};

ostream &operator<<(ostream &o, const Person &p);

class Worker : public Person
{
public:
    Worker(string name, unsigned int wealth = 0); // Setzt Instanzvariablen durch Konstruktor der Basisklasse.
    void work(string guild, unsigned int i);      // Erhoeht wealth um i.
    // Format: [Worker Person::print(o)
    ostream &print(ostream &o) const; // Gibt das Objekt auf den ostream o aus.
};

class Superworker : public Person
{
private:
    unsigned int fee;

public:
    Superworker(unsigned int fee, string name, unsigned int wealth = 0); // Setzt Instanzvariablen durch Konstruktor der Basisklasse. fee ist eine zusaetzliche Instanzvariable in der Superworker-Klasse.
    void work(string guild, unsigned int i);                             // Erhoeht wealth um i+fee. (Die zusätzliche Gebuhr fee wird verrechnet, egal ob die Arbeit mit Lizenz oder als Gildenmitglied verrichtet wird.)
    // Format: [Superworker Person::print(o)
    ostream &print(ostream &o) const; // Gibt das Objekt auf den ostream o aus.
};

#endif