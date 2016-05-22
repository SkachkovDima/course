#include <iostream>
#include <fstream>
#include <list>

using namespace std;

#define SWAPS_PATH "/proc/swaps"

list<string> get_swaps();

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");

  list<string> swaps = get_swaps();

  if(swaps.empty()){
    cout << "There is no swap" << endl;
    return 0;
  }

  if(swaps.size() - 1 == 1) {
    cout << "There is 1 swap" << endl;
  }
  else{
    cout << "There are " << swaps.size() - 1 << " swaps" << endl;
  }

  for(auto it = swaps.begin(); it != swaps.end(); ++it){
    cout << *it << endl;
  }

  return 0;
}

// read information about swaps and return list<string>
list<string> get_swaps(){
  list<string> swaps;

  ifstream fin(SWAPS_PATH);
  if (!fin.is_open()) {
    perror(SWAPS_PATH);
    exit(-1);
  }

  string buffer;
  while(!fin.eof()){
    getline(fin, buffer);
    if(fin.eof()) break;
    if(!buffer.empty())
      swaps.push_back(buffer);
  }

  fin.close();
  return swaps;
}
