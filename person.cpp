// #include "person.h"
// #include <stdexcept>
// #include <ostream>

// moped
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "person.h"
#include "license.h"
#include "guild.h"

// Setzt Instanzvariablen, wobei name nicht leer sein darf.
Person::Person(string name, unsigned int wealth) : wealth{wealth}, licenses{}
{
    if (name.length() < 1)
    {
        throw runtime_error("name is empty");
    }
    this->name = name;
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
    auto sal = licenses[guild]->get_salary();
    work(guild, sal);
    // if work is called with amount(int) guild is unknown
    // offer_job does not necessarily end here and Superworker adds fee afterwards...

    // would be nice to add book entry here but its better to add it down the line in the work method of subclasses
    // because they could do special shit like superworker and Guild.offer_job also would have to be handled seperately

    /*
    if (dynamic_cast<const Superworker *>(this) != nullptr)
    {
        cout << " superworker ";
    }
    else
    {
        cout << "no super w";
    }
    */
}

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
    auto name = l->get_guildname();
    if (licenses.find(name) != licenses.end())
    {
        licenses[name] = std::move(l);
    }
    else
    {
        licenses.emplace(std::make_pair(name, std::move(l)));
    }
}

// Uebergibt die Lizenz mit dem Namen l vom this-Objekt an Person p und entfernt diese aus den Lizenzen vom this-Objekt...
void Person::transfer_license(string l, shared_ptr<Person> p)
{
    if (licenses.find(l) == licenses.end())
        throw runtime_error("requested license does not exist");

    // p->receive_license(std::make_unique<License>(licenses[l], licenses[l]->get_salary()));
    p->receive_license(std::move(licenses[l]));
    licenses.erase(l);
}
//  Liefert true falls eine Lizenz mit Namen l vorhanden ist und diese gueltig ist, ansonsten false.
bool Person::eligible(string l) const
{
    auto it = licenses.find(l);
    return it != licenses.end() && it->second->valid() ? true : false;
}

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
        o << *l.second;
        sep = true;
    }
    o << "}";
    return o;
}

ostream &operator<<(ostream &o, const Person &p)
{
    return p.print(o);
}

// Setzt Instanzvariablen durch Konstruktor der Basisklasse.
// w the point of that??
Worker::Worker(string name, unsigned int wealth) : Person(name, wealth)
{
}

// Erhoeht wealth um i.
void Worker::work(string guild, unsigned int i)
{
    Person::wealth += i;

    Guild::add_book_entry(guild, {shared_from_this(), name, i});
}

// Format: [Worker Person::print(o)
// Gibt das Objekt auf den ostream o aus.
ostream &Worker::print(ostream &o) const
{
    o << "[Worker ";
    Person::print(o);
    return o << ']';
}

// Setzt Instanzvariablen durch Konstruktor der Basisklasse. fee ist eine zusaetzliche Instanzvariable in der Superworker-Klasse.
Superworker::Superworker(unsigned int fee, string name, unsigned int wealth) : Person::Person{name, wealth}
{
    this->fee = fee;
}

// Erhoeht wealth um i+fee. (Die zusätzliche Gebuhr fee wird verrechnet, egal ob die Arbeit mit Lizenz oder als Gildenmitglied verrichtet wird.)
void Superworker::work(string guild, unsigned int i)
{
    Person::wealth += i + fee;

    Guild::add_book_entry(guild, {shared_from_this(), name, i + fee});
}

// Format: [Superworker Person::print(o)
// Gibt das Objekt auf den ostream o aus.
ostream &Superworker::print(ostream &o) const
{
    o << "[Superworker ";
    Person::print(o);
    return o << ']';
}
