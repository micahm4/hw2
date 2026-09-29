#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(string name, double price, int qty, string size, string brand)
: Product("clothing", name, price ,qty), size_(size), brand_(brand)
{

}

Clothing::~Clothing() {

}

set<string> Clothing:: keywords() const {
  set<string> names = parseStringToWords(name_);
  set<string> brands = parseStringToWords(brand_);

  return setUnion(names, brands);

}

string Clothing::displayString() const{
  
  stringstream result;

  //put information into result
  result << name_ << endl;
  result << "Size: " << size_ << " Brand: " << brand_ << endl;
  result << price_ << " " << qty_ << " left.";

  return result.str(); //return result as string
}

void Clothing::dump(ostream& os) const {
  
  Product::dump(os); //use product's functional --> void func
  
  //output book specifics (not included)
  os << size_ << endl;
  os << brand_ << endl;

}