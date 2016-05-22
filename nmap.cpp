#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <wait.h>
#include <list>

using namespace std;

#define SUDO "/usr/bin/sudo"
#define REPORT "/home/linux/University/course/nmap report"
#define PORT "/home/linux/University/course/port"

struct port_info{
    unsigned number;
    string protocol;
};

void read_report(list<string>&);
void read_ports(list<string>&);
unsigned to_unsigned(string);
vector<unsigned> get_ports(string);
list<port_info> find_vulnerable();

int main(int argc, char* argv[]){

    auto pid = fork();

    switch(pid){
        case -1:
            perror("fork nmap");
            return 0;
        case 0:
            if(execl(SUDO, "sudo", "nmap", "-sS", "-oN", REPORT,
                     "localhost", nullptr) == -1){
                perror("execl nmap");
                return -1;
            }
    }
    waitpid(pid, 0, 0);

    list<port_info> vulnerable_ports = find_vulnerable();

    if(vulnerable_ports.empty()){
        cout << "Сurrently opened ports are not vulnerable" << endl;
    }
    else {
      cout << "Of all currently open ports are vulnerable following:" << endl;
      for (auto it = vulnerable_ports.begin();
           it != vulnerable_ports.end(); ++it) {
        cout << "   " << it->protocol << "/" << it->number << endl;
      }
    }

    return 0;
}

// check opened ports on PC, and return list of vulnerable ports
list<port_info> find_vulnerable() {
  string protocol;
  unsigned port;
  list<port_info> dangerous;

  list<string> report;
  read_report(report);

  list<string> vulnerable_ports;
  read_ports(vulnerable_ports);

  for (auto report_it = report.begin(); report_it != report.end();
       ++report_it) {

    port = to_unsigned(report_it->substr(0, report_it->find('\\', 0)));

    unsigned long begin = report_it->find('/', 0) + 1;
    unsigned long count = report_it->find(' ', 0) -
                          report_it->find('/', 0) - 1;
    protocol = report_it->substr(begin, count);

    for (auto info_it = vulnerable_ports.begin();
         info_it != vulnerable_ports.end(); ++info_it) {

      if (info_it->substr(0, info_it->find(' ', 0)).compare(protocol) == 0) {
        vector<unsigned> open_ports = get_ports(*info_it);

        for (auto number = open_ports.begin();
             number != open_ports.end(); ++number) {

          if (*number == port) {
            port_info info;
            info.number = port;
            info.protocol = protocol;
            dangerous.push_back(info);
            break;
          }
        }
      }
    }
  }

  return dangerous;
}

//read from file report of using nmap
void read_report(list<string>& report) {
  string buffer;
  ifstream fin(REPORT);

  if (!fin.is_open()) {
    perror("nmap_report");
    exit(-1);
  }

  while (!fin.eof()) {
    getline(fin, buffer);
    if (fin.eof()) break;
    if (buffer.empty() || (buffer.at(0) < '0' && buffer.at(0) > '9'))
      continue;
    report.push_back(buffer);
  }

  fin.close();
}

// read from file information of ports that vulnerable to hacker attacks
void read_ports(list<string>& vulnerable_ports) {
  string buffer;
  ifstream fin(PORT);

  if (!fin.is_open()) {
    perror("port");
    exit(-1);
  }

  while (!fin.eof()) {
    getline(fin, buffer);
    if (fin.eof()) break;
    if (buffer.empty() || buffer.at(0) == '/') continue;
    vulnerable_ports.push_back(buffer);
  }

  fin.close();
}

// convert string whith information on ports into vector<unsigned> that contain
// number of vulnerable ports
vector<unsigned> get_ports(string buffer) {
  vector<unsigned> ports_number;
  string separator(" ");
  size_t prev = 0;
  size_t next;

  while ((next = buffer.find(separator, prev)) != string::npos) {
    ports_number.push_back(to_unsigned(buffer.substr(prev, next - prev)));
    prev = next + 1;
  }
  ports_number.push_back(to_unsigned(buffer.substr(prev)));

  return ports_number;
}

// convert string to unsigned
unsigned to_unsigned(string buffer) {
  unsigned port;
  stringstream stream;
  stream << buffer.c_str();
  stream >> port;
  return port;
}
