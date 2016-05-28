#include "../include/nmap.h"

// check all open ports
void nmap::check() {
  unsigned port;
  string protocol;

  read_report();
  read_ports();

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
        vector<unsigned> open_ports = convert_ports(*info_it);

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
}

// output vulnerable ports;
void nmap::output(){
  if (dangerous.empty()) {
    cout << "Сurrently opened ports are not vulnerable" << endl;
  }
  else {
    cout << "Of all currently open ports are vulnerable following:" << endl;
    for (auto it = dangerous.begin();
         it != dangerous.end(); ++it) {
      cout << "   " << it->protocol << "/" << it->number << endl;
    }
  }
}

// read info about openning ports
void nmap::read_report() {
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

// read from file info of ports that vulnerable to hacker attacks
void nmap::read_ports() {
  string buffer;
  ifstream fin(PORT);

  if (!fin.is_open()) {
    perror("port");
    exit(-1);
  }

  while (!fin.eof()) {
    getline(fin, buffer);
    if (fin.eof()) break;
    if (buffer.empty() || buffer.at(0) == '#') continue;
    vulnerable_ports.push_back(buffer);
  }

  fin.close();
}

// get port's value from string
vector<unsigned> nmap::convert_ports(string buffer) {
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

extern "C" int start() {

  auto pid = fork();
  switch (pid) {
    case -1:
      perror("fork nmap");
      return 0;
    case 0:
      if (execl(SUDO, "sudo", "nmap", "-sS", "-oN", REPORT,
                "localhost", nullptr) == -1) {
        perror("execl nmap");
        return -1;
      }
  }
  waitpid(pid, 0, 0);

  return 0;
}

extern "C" void result(){
  nmap ports;
  ports.check();
  ports.output();
}