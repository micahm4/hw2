#include <iostream>
#include "mydatastore.h"
#include "util.h"
#include <iomanip>

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
  for (vector<Product*>::iterator it = prods_.begin(); it != prods_.end(); ++it) {
    delete *it;
  }

  for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete it->second;
  }
}

void MyDataStore::addUser(User* u) {
  string username = convToLower(u->getName());

  users_[username] = u;
  carts_[username] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& prods, int type) {

  vector<Product*> match;

  if(prods.size() == 0) { 
    return match;
  }

  set<Product*> answer;

  if(type == 0) {
    string fTerm = convToLower(prods[0]);

    map<string, set<Product*>>::iterator first = keyMap.find(fTerm);

    if(first == keyMap.end()) {
      return match;
    }

    answer = first->second;

    for(size_t i = 1; i < prods.size(); i++) {
      string term = convToLower(prods[i]);

      map<string, set<Product*> >::iterator found = keyMap.find(term);

      if (found == keyMap.end()) {
        answer.clear();
        break;
      }
      answer = setIntersection(answer, found->second);
    }
  }
  else{
    for(size_t i = 0; i < prods.size(); i++) {
      string term = convToLower(prods[i]);

      map<string,set<Product*>>::iterator found = keyMap.find(term);

      if (found != keyMap.end()) {
        answer = setUnion(answer, found->second);
      }
    }
  }

  for(set<Product*>::iterator it = answer.begin(); it != answer.end(); ++it) {
    match.push_back(*it);
  }

  return match;
}

void MyDataStore::addProduct(Product * p) {
  prods_.push_back(p);
  set<string> words = p->keywords(); //searchable words

  for(set<string>::iterator it = words.begin(); it != words.end(); ++it) {
    string word = convToLower(*it);
    keyMap[word].insert(p);
  }
}

bool MyDataStore::addToCart(string username, Product* product) {
  username = convToLower(username);

  //exists? valid? , end is past the end
  if(users_.find(username) == users_.end() || product == nullptr) {
    return false;
  }
  
  carts_[username].push_back(product); //add to carts

  return true;
}

bool MyDataStore::viewCart(string username) {
  username = convToLower(username);

  if(users_.find(username) == users_.end()) { //exists?
    return false;
  }
  for(size_t i = 0; i < carts_[username].size(); i++) {
    cout << "Item " << setw(3) << i + 1 << endl;
    cout <<carts_[username][i]->displayString() << endl;
    cout << endl;
  }

  return true;
}

bool MyDataStore::buyCart(string username) {
  username = convToLower(username);
  
  if (users_.find(username) == users_.end()) { //exists?
    return false; 
  }

  vector<Product*> left;

  for (size_t i = 0; i < carts_[username].size(); i++) {
    Product* currProd = carts_[username][i];

    if(users_[username]->getBalance() >= currProd->getPrice() && currProd->getQty() > 0) { //in stock + can afford

      currProd->subtractQty(1); // lower qty
      users_[username]->deductAmount(currProd->getPrice()); //subtract price -> new balance
    }
    else {
      left.push_back(currProd); //only prods not purchased added
    }
  }

  carts_[username] = left;
  return true;
}

void MyDataStore::dump(ostream& file) {
  file << "<products>" << endl;
  
  for (size_t i = 0; i < prods_.size(); i++) {
    prods_[i]->dump(file);
  }

  file << "</products>" << endl;
  file << "<users>" << endl;

  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    it->second->dump(file);
  }

  file << "</users>" << endl;
}