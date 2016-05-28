#include <iostream>
#include <fstream>
#include <list>

using namespace std;

#define SWAPS_PATH "/proc/swaps"


// read info about swaps and return list<string>
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


string info;          // contain result of testing
list<string> swaps;




extern "C" int start() {
  swaps = get_swaps();

  if (swaps.empty()) {
    cout << "There is no swap" << endl;
    return 0;
  }

  if (swaps.size() - 1 == 1) {
    info = "There is 1 swap";
  }
  else {
    info = "There are " + to_string(swaps.size() - 1) + " swaps";
  }

  return 0;
}

extern "C" void result() {
  cout << info << endl;
  if (info != "There is no swap") {
    cout << endl;
    for (auto it = swaps.begin(); it != swaps.end(); ++it) {
      cout << *it << endl;
    }
  }
}







