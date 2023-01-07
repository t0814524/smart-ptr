
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
    Superworker sw = Superworker(5, "sw1", 10);
    // w.work(5);
    // sw.work(3);
    vector<shared_ptr<Person>> v;
    std::shared_ptr<Person> s1{std::make_shared<Superworker>(3, "Weatherwax", 10)};
    std::shared_ptr<Person> s2{std::make_shared<Worker>("Weatherwix", 20)};
    std::shared_ptr<Person> s3{std::make_shared<Worker>("Weatherwaxxer", 30)};
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    Guild g = Guild("guild1", 3, 4, v);
    Guild g3 = Guild("guild44", 3, 4, v);

    {

        Guild g2 = Guild("guild2", 3, 4, v);
    }

    // s1->work(33);
    // s2->work(33);
    // Guild::add_book_entry("guild44", {weak_ptr<Person>(s2), s2->get_name(), 33});
    // g3.print_book(cout);
    License l{"guild44", 3};
    License l2{"guild44", 3};
    s1->receive_license(make_unique<License>(l));
    s2->receive_license(make_unique<License>(l2));
    cout << " bfbooks ";
    s1->work("guild44");
    s1->work("guild44");
    // s2->work("guild44");
    g3.add_member(s3);
    g3.print_book(cout);
    g3.offer_job(s3);

    {
        std::shared_ptr<Person> s4{std::make_shared<Worker>("worker4", 30)};
        s4->receive_license(make_unique<License>(l2));
        g3.add_member(s4); // add member has shared ptr so s4 is not expired after this scope
        try
        {
            s4->work("guild44");
            s4->work("guild44");
            s4->receive_license(make_unique<License>(l2));
            s4->work("guild44");
            s4->work("guild44");
            s4->work("guild44");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    cout << " book2 ";
    g3.print_book(cout);
    string current_top_worker = g3.get_top_worker();
    cout << "current not expired top worker of guild: " + current_top_worker;

    return 0;
}