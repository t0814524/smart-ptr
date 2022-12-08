
#ifndef LICENSE_H
#define LICENSE_H
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class License
{
private:
    string name;          // Name der austellenden Gilde.
    unsigned int salary;  // Lohn einer Aufgabe.
    unsigned int counter; // Anzahl der bereits getaetigten Aufgaben.
public:
    License(string name, unsigned int salary); // Setzt Instanzvariablen. Name darf nicht leer und salary muss groesser als 0 sein. Sollte ein Parameter nicht den vorgegebenen Werten entsprechen, ist eine Exception vom Typ runtime_error zu werfen.

    string get_guildname() const;    //  Liefert den Namen der ausstellenden Gilde.
    unsigned int get_salary() const; // Liefert den Lohn einer Aufgabe.
    bool valid() const;              // Liefert true, falls maximal 3 Aufgaben erst getaetigt wurden, ansonsten false.
    bool use();                      // Liefert false, falls die Lizenz nicht mehr gueltig ist. Ansonsten wird die Anzahl der getaetigten Aufgaben um eins erhoeht und true zurueckgeliefert.
    ostream &print(ostream &o) const;
};

ostream &operator<<(ostream &o, const License &l);

#endif
