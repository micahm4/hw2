#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include <iostream>
#include "product.h"

using namespace std;

class Book : public Product { //inherit from Product
  public:
    Book(string name, double price, int qty, string isbn, string author);
    virtual ~Book();

    set<string> keywords() const;
    string displayString() const;
    void dump(ostream& os) const;

  private:
    string isbn_;
    string author_;
};

#endif