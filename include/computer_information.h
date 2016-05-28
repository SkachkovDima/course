#ifndef COURSE_COMPUTER_INFORMATION_H
#define COURSE_COMPUTER_INFORMATION_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define DISTRIBUTION_PATH "/etc/issue.net"
#define KERNEL_PATH "/proc/version_signature"
#define COMPUTER_NAME_PATH "/etc/hostname"
#define CPU_INFO_PATH "/proc/cpuinfo"
#define CPU_LOAD_PATH "/proc/loadavg"

#define MESSAGE "No information"


// struct contain fields with main info about CPU
struct cpu_information{
  string model_name;    // contain CPU's model
  unsigned cores;       // contain number of cores
  unsigned cache_size;  // contain cache size
  double one_min;       // contain CPU's load for last minute
  double five_min;      // contain CPU's load for last five minutes
  double ten_min;       // contain CPU's load for last ten minutes
  unsigned run;         // contain number of run processes
  unsigned all;         // contain number of all system processes
};

// this class contain main info about computer
class computer_information{
private:
  string kernel;               // contain info about system kernel
  string distribution;         // contain name of system distribution
  string computer_name;        // contain computer name
  cpu_information cpu_info;    // contain main info about CPU


public:
  computer_information();
  void output();

private:
  string get_value(string);     // get value from CPU_INFO_PATH
  unsigned to_unsigned(string); // convert string to unsigned
  void get_kernel();            // get info from KERNEL_PATH
  void get_distribution();      // get info from DISTRIBUTION_PATH
  void get_computer_name();     // get info about computer's name
  void get_cpu_information();   // get info main info about CPU
  void get_cpu_load();          // get info about processes and CPU load
};



#endif //COURSE_COMPUTER_INFORMATION_H
