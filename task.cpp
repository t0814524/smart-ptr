#ifndef TASKS_H
#define TASKS_H
#include<iostream>
#include<memory>
#include<vector>
#include<experimental/iterator>
#include<iterator>
#include<numeric>
#include<algorithm>
#include<cstdlib>
#include<set>
#include "license.h"
#include "guild.h"
#include "person.h"


using namespace std;

// Task 1

vector<shared_ptr<Guild>> task1(const vector<Guild>& v){
  vector<shared_ptr<Guild>> res;
  if(v.size()<1)return res;
  
  auto salary = std::accumulate(v.begin(),v.end(), 0, [](unsigned int acc, const Guild & g){
  	return acc + g.get_salary();
  });
  
  auto max_el = max_element(v.begin(), v.end(), [](const Guild a, const Guild b){
  	return a.get_fee() < b.get_fee();
  });
  
  unsigned int fee = max_el->get_fee();
  
  for(auto it = v.rbegin(); it != v.rend(); ++it){
    auto name = it->get_name();
    res.push_back(std::make_shared<Guild>(name,fee,salary));
  }
  return res;
};


// Task 4
class Syndicate{
private:
   vector<weak_ptr<Person>> v;
public:
	Syndicate(const vector<weak_ptr<Person>>& v): v{v}{
  }
  
  bool can_execute(vector<string> licenses) const{
  	if( licenses.size() == 0) return true;
    bool ret = true;
    std::for_each(licenses.begin(),licenses.end(),[&](string l){
			for(auto p: v){
      	if (std::shared_ptr<Person> spt = p.lock()) {
        	if(spt->eligible(l)){
          	return;
          }
    		}
      }
      ret = false;
    });
   return ret; 
  }
};
#endif
