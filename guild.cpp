#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <set>
#include <algorithm>
#include <map>
#include "guild.h"
#include "license.h"
#include "person.h"

using namespace std;

Guild::Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>> &members)
{
    if (name.length() < 1)
        throw runtime_error("name is empty");
    if (fee < 1)
        throw runtime_error("fee has to be bigger than 0");
    if (salary < 1)
        throw runtime_error("salary has to be bigger than 0");

    this->name = name;
    this->fee = fee;
    this->salary = sal;
    // to check if that works
    for (shared_ptr<Person> v : members)
    {
        this->members.emplace(v->get_name(), v);
    }
}

// Fuegt Person p der Gilde hinzu, falls nicht schon bereits vorhanden. Liefert true bei Erfolg, ansonsten false.
bool Guild::add_member(shared_ptr<Person> p)
{
    if (members.find(p->get_name()) != members.end())
    {
        // add
        // todo check if works in fkn moped
        // members.insert({p->get_name(), p});
        members.emplace(p->get_name(), p);
        return true;
    }
    else
    {
        return false;
    }
}

// Entfernt Person mit Namen n aus der Gilde. Liefert true bei Erfolg, ansonsten false.
bool Guild::remove_member(string n)
{
    return members.erase(n);
}

// Verkauft Gildenmitglied eine Lizenz der Gilde, sofern sich Person mit Namen n eine Lizenz leisten kann (fee) und ein Mitglied der Gilde ist.
void Guild::grant_license(string n)
{
    if (members.find(n) == members.end())
        throw runtime_error("person " + n + " is not a member of guild");

    if (members[n]->pay_fee(fee))
    {
        // todo could be wrong
        // unique_ptr<License> up = std::make_unique<License>(name, salary);
        members[n]->receive_license(std::make_unique<License>(name, salary));
    }
    else
    {
        throw runtime_error("Person " + n + " cant afford fee of " + std::to_string(fee));
    }
}

//  Bietet eine Aufgabe Person p an, welche diese auch gleich abarbeitet (work).
bool Guild::offer_job(shared_ptr<Person> p) const
{
    // guild members:
    if (members.find(p->get_name()) != members.end())
    {
        // member of guild get 2x salary and dont need a license, so just increase wealth
        p->increase_wealth(salary * 2);
        return true;
    }
    else
    {
        try
        {
            // try to work, if theres no valid license work throws
            p->work(name);
        }
        catch (const std::exception &e)
        { // persons without license or membership
            return false;
        }
        return true;
    }
}

// Format: [name, License fee: fee, Job salary: salary, {member_name0, member_name1, ..., member_namen}]
ostream &Guild::print(ostream &o) const
{
    o << "[" << name + ", License fee: " << to_string(fee) << ", Job Salary: " << to_string(salary);
    bool sep{false};
    for (auto m : members)
    {
        if (sep)
        {
            o << ", ";
        }
        o << m.second->get_name();
        sep = true;
    }
    return o;
}

// todo
//  Beispiel: [City watch, License fee: 6, Job salary: 5, {Carrot Ironfoundersson, Samuel Vimes}]
//  operator<<