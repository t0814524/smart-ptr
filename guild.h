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

class Guild
{
private:
    string name;                             // Name der Gilde. (Zur Vereinfachung darf davon ausgegangen werden, dass die Namen der Guild-Objekte eindeutig sind.)
    unsigned int fee;                        // Lizenzgebuehr.
    unsigned int salary;                     // Gehalt pro Aufgabe.
    map<string, shared_ptr<Person>> members; // Map von Gildenmitgliedern.
public:
    Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>> &members = {});
    bool add_member(shared_ptr<Person> p);      // Fuegt Person p der Gilde hinzu, falls nicht schon bereits vorhanden. Liefert true bei Erfolg, ansonsten false.
    bool remove_member(string n);               // Entfernt Person mit Namen n aus der Gilde. Liefert true bei Erfolg, ansonsten false.
    void grant_license(string n);               // Verkauft Gildenmitglied eine Lizenz der Gilde, sofern sich Person mit Namen n eine Lizenz leisten kann (fee) und ein Mitglied der Gilde ist.
    bool offer_job(shared_ptr<Person> p) const; //  Bietet eine Aufgabe Person p an, welche diese auch gleich abarbeitet (work).
    // Format: [name, License fee: fee, Job salary: salary, {member_name0, member_name1, ..., member_namen}]
    ostream &print(ostream &o) const;
};

// todo
//  Beispiel: [City watch, License fee: 6, Job salary: 5, {Carrot Ironfoundersson, Samuel Vimes}]
//  operator<<

#endif
