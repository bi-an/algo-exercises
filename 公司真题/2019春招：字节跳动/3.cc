#include <bits/stdc++.h>
using namespace std;

bool ishu(const vector<int> &num) {
  bool res = false;

  if (num.empty())
    return true;
  int count0 = count(num.begin(), num.end(), num[0]);
  if (count0 >= 2 && num.size() % 3 != 0) {
    res = ishu(vector<int>(num.begin() + 2, num.end()));
  }
  if (res == false && count0 >= 3) {
    res = ishu(vector<int>(num.begin() + 3, num.end()));
  }
  if (res == false && count(num.begin(), num.end(), num[0] + 1) > 0 &&
      count(num.begin(), num.end(), num[0] + 2) > 0) {
    vector<int> subnum(num.begin() + 1, num.end());
    subnum.erase(find(subnum.begin(), subnum.end(), num[0] + 1));
    subnum.erase(find(subnum.begin(), subnum.end(), num[0] + 2));
    // sort(subnum.begin(), subnum.end());
    res = ishu(subnum);
  }
  return res;
}

bool hupai(vector<int> num, int n) {
  if (count(num.begin(), num.end(), n) == 4)
    return false;
  else {
    num.push_back(n);
    sort(num.begin(), num.end());
    return ishu(num);
  }
}

int main() {
  vector<int> num(13), res; //{1, 1, 1, 2, 2, 2, 5, 5, 5, 6, 6, 6, 9};

  for (int i = 0; i < 13; i++)
    cin >> num[i];

  for (int i = 1; i < 10; i++) {
    if (hupai(num, i))
      res.push_back(i);
  }

  if (res.empty())
    cout << "0";
  else {
    for (int i = 0; i < res.size(); i++)
      cout << res[i] << " ";
  }
  cout << endl;
}
