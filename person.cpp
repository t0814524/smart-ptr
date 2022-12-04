#include "person.h"
#include <stdexcept>
#include <ostream>

// moped
// #include<string>
// #include<memory>
// #include<vector>
// #include<iostream>
// #include<map>
// #include "person.h"
// #include "license.h"

// Setzt Instanzvariablen, wobei name nicht leer sein darf.
Person::Person(string name, unsigned int wealth) : wealth{wealth}
{
    if (name.length() < 0)
    {
        throw runtime_error("name is empty");
    }
}

// Falls eine Lizenz fuer guild vorhanden ist und man diese noch benutzen kann, wird die Lizenz benutzt und die Person arbeitet fuer das auf der Lizenz gedruckte Gehalt....
void Person::work(string guild)
{
    if (licenses.find(guild) == licenses.end())
    {
        throw runtime_error("license not available");
    }

    if (!licenses[guild]->use())
    {
        throw runtime_error("license invalid");
    }
    wealth += licenses[guild]->get_salary();
}

// tojdo wtf is that
//  virtual void Person::work(unsigned int) = 0{

// }

// Erhoeht wealth um i.
void Person::increase_wealth(unsigned int i)
{
    wealth += i;
}

// Liefert name.
string Person::get_name() const
{
    return name;
}

// Sollte das Vermoegen der Person nicht ausreichen, um die Gebuehr i zu bezahlen oder i 0 sein, ist false zu liefern. Ansonsten wird das Vermoegen reduziert um i und true returniert.
bool Person::pay_fee(unsigned int i)
{
    if (wealth < i || i == 0)
        return false;

    wealth -= i;
    return true;
}

// Speichert die Lizenz l in der Map der Lizenzen der Person. Sollte es bereits eine Lizenz mit dem gleichen Namen geben, ist die alte Lizenz zu zerstoeren.
void Person::receive_license(unique_ptr<License> l)
{
    // todo check if thats right might need to std::move??
    auto name = l->get_guildname();
    if (licenses.find(name) != licenses.end())
    {
        licenses[name] = std::move(l);
    }
    else
    {
        licenses.emplace(name, l);
    }
}

// Uebergibt die Lizenz mit dem Namen l vom this-Objekt an Person p und entfernt diese aus den Lizenzen vom this-Objekt...
void Person::transfer_license(string l, shared_ptr<Person> p)
{
    if (licenses.find(l) == licenses.end())
        throw runtime_error("requested license does not exist");

    p->receive_license(std::make_unique<License>(licenses[l]));
    licenses.erase(l);
}
//  Liefert true falls eine Lizenz mit Namen l vorhanden ist und diese gueltig ist, ansonsten false.
bool Person::eligible(string l) const
{
    auto it = licenses.find(l);
    return it != licenses.end() && it->second->valid() ? true : false;
}

// todo
// Die Klasse Person hat folgendes Ausgabeformat.
// virtual ostream &Person::print(ostream &o) const
// {
// }

// Format: name, wealth Coins, {license_0, license_1, ..., license_n}]
// Gibt das Objekt auf den ostream o aus.
ostream &Person::print(ostream &o) const
{
    bool sep{false};
    o << name << ", " << std::to_string(wealth) << " Coins, {";
    for (auto &l : licenses)
    {
        if (sep)
        {
            o << ", ";
        }
        // todo
        // o << *l.second;
        sep = true;
    }
    o << "}";
    return o;
}

// todo: global shit overload <<