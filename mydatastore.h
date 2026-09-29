#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "datastore.h"
#include "product.h"
#include "user.h"

using namespace std;

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    virtual ~MyDataStore();

    void addProduct(Product * p);
    void addUser(User* u);
    vector<Product*> search(vector<string>& prods, int type);

    void dump(ostream& file);

    //amazon functions
    bool addToCart(string username, Product* product);
    bool viewCart(string username);
    bool buyCart(string username);
  
  private:
    vector<Product*> prods_; //add products
    map<string, vector<Product*> > carts_; //username to cart
    map<string, set<Product*> > keyMap; // keyword to products
    map<string, User*> users_; //username to user
};

#endif