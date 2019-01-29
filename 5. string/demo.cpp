#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::vector;
using std::getline;

template<class outType, class inType>
void convert(outType& out, const inType& in)
{
  static stringstream g_ss;
  g_ss << in; g_ss >> out; g_ss.clear();
}

void split(vector<string>& out, const string& in, const char delim)
{
  stringstream ssin(in);
  for(string s; getline(ssin, s, delim);)
    out.push_back(s);
}

int main(void)
{
  // convertion between number and string
  string s1;
  float a1;
  convert<string, float>(s1, 9.9);
  convert<float, string>(a1, s1);
  cout << s1 << ", " << a1 << ", " << endl;
  // string split 
  stringstream sinput("12,30,\n13,31");
  vector<string> vinput;
  for(string line; getline(sinput, line, '\n');)
    split(vinput, line, ',');
  // string append
  string output;
  for(int i=0; i<vinput.size(); ++i)
  {
    output += vinput[i];
    output += "::";
  }
  cout << output << endl;

  return 0;
}
