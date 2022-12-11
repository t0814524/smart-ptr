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

class License;

Guild::Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>> &members)
{
    if (name.length() < 1)
        throw runtime_error("name is empty");
    if (fee < 1)
        throw runtime_error("fee has to be bigger than 0");
    if (sal < 1)
        throw runtime_error("salary has to be bigger than 0");

    this->name = name;
    this->fee = fee;
    this->salary = sal;
    // to check if that works
    for (shared_ptr<Person> v : members)
    {
        const auto [it, success2] = this->members.insert({v->get_name(), v});
        if (!success2)
        {
            throw runtime_error("already exists");
        }
    }
    Guild::instances.push_back(this);
}

Guild::~Guild()
{
    auto res = std::find_if(Guild::instances.begin(), Guild::instances.end(), [&](const Guild *g)
                            { return g == this; });
    if (res == Guild::instances.end())
    {
        cout << "destructor trying to delete Guild from static instances member but its not there!!!?!???";
    }
    else
    {
        // test deletion of Guilds from static instances vec:
        // cout << "erase";
        // cout << *res;
        Guild::instances.erase(res);
        // cout << "instances after erase:";
        // for (auto inst : Guild::instances)
        // {
        //     cout << *inst;
        // }
    }
}

// Fuegt Person p der Gilde hinzu, falls nicht schon bereits vorhanden. Liefert true bei Erfolg, ansonsten false.
bool Guild::add_member(shared_ptr<Person> p)
{
    if (members.find(p->get_name()) == members.end())
    {
        // add
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
        p->work(salary * 2);
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
    o << "[" << name + ", License fee: " << to_string(fee) << ", Job salary: " << to_string(salary) << ", {";
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
    return o << "}]";
}

ostream &operator<<(ostream &o, const Guild &g)
{
    return g.print(o);
}

void Guild::add_book_entry(BookEntry entry)
{
    book.push_back(entry);
    cout << " pbac ";
}
void Guild::add_book_entry(string guild, BookEntry entry)
{
    for (auto g : Guild::instances)
    {
        cout << g->name;
        if (g->name == guild)
        {
            cout << "found name";
            g->add_book_entry(entry);
            return;
        }
    }
    throw runtime_error("Cant add bookentry, Guild: " + guild + " does not exist");
}

ostream &Guild::print_book(ostream &o) const
{
    cout << "book: ";
    for (auto e : this->book)
    {
        o << "[Name: " << e.name << ", Salary: " << e.salary << "]";
    }
    return o;
}
