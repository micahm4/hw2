#include "book.h"
#include <sstream>
#include "util.h"

using namespace std;


Book::Book(string name, double price, int qty, string isbn, string author)
: Product("book", name, price, qty), isbn_(isbn), author_(author)
{

}

//use product constructor (above)

Book::~Book() {

}

set<string> Book::keywords() const {
  set<string> names = parseStringToWords(name_);
  set<string> authors = parseStringToWords(author_);

  set<string> result = setUnion(names, authors);
  result.insert(isbn_); //just add as it comes

  return result;

}

string Book::displayString() const {

  stringstream result;

  //put information into result
  result << name_ << endl;
  result << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  result << price_ << " " << qty_ << " left.";

  return result.str(); //return result as string

}

void Book::dump(ostream & os) const {
  Product::dump(os); //use product's functional --> void func
  
  //output book specifics (not included)
  os << isbn_ << endl;
  os << author_ << endl;
}