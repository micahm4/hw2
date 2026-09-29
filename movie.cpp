#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(string name, double price, int qty, string genre, string rating) 
: Product("movie", name, price, qty), genre_(genre), rating_(rating) 
{

}

Movie::~Movie() {

}

set<string>Movie:: keywords() const {
  set<string> result = parseStringToWords(name_);
  result.insert(convToLower(genre_)); //add as written

  return result;
}

string Movie::displayString() const{
  
  stringstream result;

  //put information into result
  result << name_ << endl;
  result << "Genre: " << genre_ << " Rating: " << rating_ << endl;
  result << price_ << " " << qty_ << " left.";

  return result.str(); //return result as string
}

void Movie::dump(ostream& os) const {
  
  Product::dump(os); //use product's functional --> void func
  
  //output book specifics (not included)
  os << genre_ << endl;
  os << rating_ << endl;

}