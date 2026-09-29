#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  set<string> words;
  string currWord;

  rawWords = convToLower(rawWords); //make all words lowercase

  for(size_t i = 0; i < rawWords.size(); i++) {

    unsigned char currChar = static_cast<unsigned char>(rawWords[i]);

    if (isalnum(currChar)) { //use cctype class 
      currWord +=rawWords[i];
    }
    else {
      if (currWord.size() >= 2) { //must be greater than 2 (won't include 's)
        words.insert(currWord);
      }

      currWord = ""; //reset word
    }
  }

  if (currWord.size() >= 2) { //last word
    words.insert(currWord);
  }

  return words;

} 

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
