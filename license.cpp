#include "license.h"
#include <string>
#include <stdexcept>
#include <iostream>

// thats in moped
// #include<memory>
// #include<vector>
// #include<map>
// #include "license.h"
// #include<string>
// #include<iostream>

using namespace std;

// Setzt Instanzvariablen. Name darf nicht leer und salary muss groesser als 0 sein. Sollte ein Parameter nicht den vorgegebenen Werten entsprechen, ist eine Exception vom Typ runtime_error zu werfen.
License::License(string name, unsigned int salary)
{
    if (name.length() < 1)
        throw runtime_error("name is empty");
    if (salary < 1)
        throw runtime_error("salary has to be bigger than 0");

    this->name = name;
    this->salary = salary;
}

//  Liefert den Namen der ausstellenden Gilde.
string License::get_guildname() const
{
    return name;
}

// Liefert den Lohn einer Aufgabe.
unsigned int License::get_salary() const
{
    return salary;
}

// Liefert true, falls maximal 3 Aufgaben erst getaetigt wurden, ansonsten false.
bool License::valid() const
{
    return counter <= 3;
}

// Liefert false, falls die Lizenz nicht mehr gueltig ist. Ansonsten wird die Anzahl der getaetigten Aufgaben um eins erhoeht und true zurueckgeliefert.
bool License::use()
{
    if (valid())
    {
        ++counter;
        return true;
    }
    else
    {
        return false;
    }
}

ostream &License::print(ostream &o) const
{
    return o << "[License for " << get_guildname() << ", Salary: " << get_salary() << ", Used: " << counter << ']';
}

ostream &operator<<(ostream &o, const License &l)
{
    return l.print(o);
}