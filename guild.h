#ifndef GUILD_H
#define GUILD_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <map>

class Person;
class License;

using namespace std;

struct BookEntry
{
    weak_ptr<Person> person;
    string name;
    unsigned int salary;
};

// BookEntry make_book_entry(weak_ptr<Person> person, int salary)
// {
//     string name;
//     if (std::shared_ptr<Person> spt = person.lock())
//     {
//         name = spt->get_name();
//     }
//     else
//     {
//         std::cout << "spt is expired\n";
//     }
//     return BookEntry{person, name, salary};
// }

class Guild
{
private:
    inline static vector<Guild *> instances = {};
    string name;                             // Name der Gilde. (Zur Vereinfachung darf davon ausgegangen werden, dass die Namen der Guild-Objekte eindeutig sind.)
    unsigned int fee;                        // Lizenzgebuehr.
    unsigned int salary;                     // Gehalt pro Aufgabe.
    map<string, shared_ptr<Person>> members; // Map von Gildenmitgliedern.
    vector<BookEntry> book;

public:
    static void add_book_entry(string guild, BookEntry entry);
    Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>> &members = {});
    ~Guild();
    void add_book_entry(BookEntry entry);
    bool add_member(shared_ptr<Person> p);      // Fuegt Person p der Gilde hinzu, falls nicht schon bereits vorhanden. Liefert true bei Erfolg, ansonsten false.
    bool remove_member(string n);               // Entfernt Person mit Namen n aus der Gilde. Liefert true bei Erfolg, ansonsten false.
    void grant_license(string n);               // Verkauft Gildenmitglied eine Lizenz der Gilde, sofern sich Person mit Namen n eine Lizenz leisten kann (fee) und ein Mitglied der Gilde ist.
    bool offer_job(shared_ptr<Person> p) const; //  Bietet eine Aufgabe Person p an, welche diese auch gleich abarbeitet (work).
    // Format: [name, License fee: fee, Job salary: salary, {member_name0, member_name1, ..., member_namen}]
    ostream &print(ostream &o) const;
    ostream &print_book(ostream &o) const;
};

ostream &operator<<(ostream &o, const Guild &g);

#endif
