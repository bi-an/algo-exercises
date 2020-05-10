/**
 * 删除多余空格
 * 如果有标点符号，删除标点之前的空格
 */

// C++ program to implement custom trim() function
#include <algorithm>
#include <iostream>
using namespace std;

// Function to in-place trim all spaces in the
// string such that all words should contain only
// a single space between them.
void removeSpaces(string &str) {
  // n is length of the original string
  int n = str.length();

  // i points to next position to be filled in
  // output string/ j points to next character
  // in the original stringi
  int i = 0, j = -1;

  // flag that sets to true is space is found
  bool spaceFound = false;

  // Handles leading spaces
  while (++j < n && str[j] == ' ')
    ;

  // read all characters of original string
  while (j < n) {
    // if current characters is non-space
    if (str[j] != ' ') {
      // remove preceding spaces before dot,
      // comma & question mark
      if ((str[j] == '.' || str[j] == ',' || str[j] == '?') && i - 1 >= 0 &&
          str[i - 1] == ' ')
        str[i - 1] = str[j++];

      else
        // copy current character at index i
        // and increment both i and j
        //        str[i++] = str[j++];
        swap(str[i++], str[j++]);

      // set space flag to false when any
      // non-space character is found
      spaceFound = false;
    }
    // if current character is a space
    else if (str[j++] == ' ') {
      // If space is encountered for the first
      // time after a word, put one space in the
      // output and set space flag to true
      if (!spaceFound) {
        str[i++] = ' ';
        spaceFound = true;
      }
    }
  }

  // Remove trailing spaces
  //  if (i <= 1)
  //    str.erase(str.begin() + i, str.end());
  //  else
  //    str.erase(str.begin() + i - 1, str.end());
  i = n - 1;
  while (i < n && str[i] == ' ') i--;
  str.erase(str.begin() + i + 1, str.end());
}

void test(int id, string in, string out) {
  cout << id << ":";
  removeSpaces(in);
  if (in == out) {
    cout << "right" << endl;
  } else {
    cout << "false" << endl;
  }
}

// Driver Code
int main() {
  test(1, "I", "I");
  test(2, "I ", "I");
  test(3, " I", "I");
  test(4, " I ", "I");
  test(5, "I am", "I am");
  test(6, " I am", "I am");
  test(7, "I am ", "I am");
  test(8, "  I am  ", "I am");
  test(9, "   ", "");
  test(10, "", "");
  test(11, ".", ".");
  test(12, "  .  ", ".");
  test(13, ".  ", ".");
  test(14, "  .", ".");

  return 0;
}

