
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "person.h"
#include "guild.h"
#include "license.h"

int main()
{
    Worker w = Worker("hs", 8);
    Superworker sw = Superworker(5, "sw1", 10);
    // w.work(5);
    // sw.work(3);
    vector<shared_ptr<Person>> v;
    std::shared_ptr<Person> s1{std::make_shared<Superworker>(3, "Weatherwax", 10)};
    std::shared_ptr<Person> s2{std::make_shared<Superworker>(4, "Weatherwix", 20)};
    std::shared_ptr<Person> s3{std::make_shared<Superworker>(5, "Weatherwixxer", 30)};
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    Guild g = Guild("guild1", 3, 4, v);
    Guild g3 = Guild("guild44", 3, 4, v);

    {

        Guild g2 = Guild("guild2", 3, 4, v);
    }

    s1->work(33);
    s2->work(33);
    Guild::add_book_entry("guild44", {weak_ptr<Person>(s2), s2->get_name(), 33});
    g3.print_book(cout);
    License l{"guild44", 3};
    s1->receive_license(make_unique<License>(l));
    cout << "bfb";
    s1->work("guild44");
    cout << "wtf";
    g3.print_book(cout);
    return 0;
}