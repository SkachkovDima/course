#ifndef COURSE_NMAP_H
#define COURSE_NMAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <wait.h>
#include <list>

using namespace std;

#define SUDO "/usr/bin/sudo"
#define REPORT "/tmp/nmap report"
#define PORT "/home/linux/University/course/port"

struct port_info{
  unsigned number;      // number of port
  string protocol;      // name of protocol
};

class nmap{
private:
  list<port_info> dangerous;      // ports, that opened on PC and vulnerable to
  // hacker's attack
  list<string> report;            // info about opened ports
  list<string> vulnerable_ports;  // info about vulnerable ports

public:
  void output();    // output info about dangerous ports
  void check();     // check ports, that vulnerable to hacker's attack

private:
  void read_report();  // read info about opened ports
  void read_ports();   // read_information about vulnerable ports
  vector<unsigned> convert_ports(string);  // get port's valur from string
  unsigned to_unsigned(string);            // convert string to unsigned
};

// convert string to unsigned
unsigned nmap::to_unsigned(string buffer) {
  unsigned number;
  stringstream stream;
  stream << buffer.c_str();
  stream >> number;
  return number;
}

#endif //COURSE_NMAP_H
