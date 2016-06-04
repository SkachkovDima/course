#include <iostream>
#include <fstream>
#include <list>

using namespace std;

#define SUDO "/usr/bin/sudo"
#define PARTITIONS_PATH "/proc/partitions"
#define ADD "/dev/"



list<string> get_partitions();

extern "C" int start() {

  list<string> partitions = get_partitions();

  for(auto it = partitions.begin(); it != partitions.end(); ++it){
    cout << *it << endl;
//    int pid = fork();
//    switch (pid) {
//      case -1:
//        perror("fork hdd");
//        return 0;
//      case 0:
//        execl(SUDO, "sudo", "badblocks", "-s", it->c_str(), NULL);
//    }
//    waitpid(pid, 0, 0);
  }

  return 0;
}

extern "C" void result(){
  cout << "Testing of HDD end. Report contain information "
            "about statment of HDD" << endl;
}

// get name of partitions from /proc/partitions
list<string> get_partitions() {
  list<string> partitions;

  ifstream fin(PARTITIONS_PATH);
  if (!fin.is_open()) {
    perror(PARTITIONS_PATH);
    exit(-1);
  }

  string buffer;
  while (!fin.eof()) {
    getline(fin, buffer);
    if (fin.eof()) break;
    if (buffer.empty() || buffer.at(0) == 'm') continue;
    partitions.push_back(ADD + buffer.substr(buffer.find_last_of(' ') + 1));
  }

  fin.close();
  return partitions;
}
