#include "../include/computer_information.h"

computer_information::computer_information(){
  get_kernel();
  get_distribution();
  get_computer_name();
  get_cpu_information();
  get_cpu_load();
}

string computer_information::get_value(string buffer){
  unsigned long colon = buffer.find(':');
  return buffer.substr(colon + 2);
}

unsigned computer_information::to_unsigned(string buffer) {
  unsigned number;
  stringstream stream;
  stream << buffer.c_str();
  stream >> number;
  return number;
}

void computer_information::output(){
  cout << "Computer name: " << computer_name << endl
  << "Distribution: " << distribution << endl
  << "Kernel: " << kernel << endl << endl
  << "CPU info:" << endl
  << "\tModel: " << cpu_info.model_name << endl
  << "\tCores: " << cpu_info.cores << endl
  << "\tCache size: " << cpu_info.cache_size << endl << endl
  << "Load process: " << endl
  << "\t1 minute: " << cpu_info.one_min << endl
  << "\t5 minutes: " << cpu_info.five_min << endl
  << "\t10 minutes: " << cpu_info.ten_min << endl
  << "\tRun: " << cpu_info.run << endl
  << "\tAll: " << cpu_info.all <<endl;
}

void computer_information::get_kernel(){
  ifstream fin(KERNEL_PATH);
  if(!fin.is_open()){
    kernel = MESSAGE;
    perror(KERNEL_PATH);
    return;
  }

  getline(fin, kernel);
  fin.close();
}

void computer_information::get_distribution(){
  ifstream fin(DISTRIBUTION_PATH);
  if(!fin.is_open()){
    distribution = MESSAGE;
    perror(DISTRIBUTION_PATH);
    return;
  }

  getline(fin, distribution);
  fin.close();
}

void computer_information::get_computer_name(){
  ifstream fin(COMPUTER_NAME_PATH);
  if(!fin.is_open()){
    computer_name = MESSAGE;
    perror(COMPUTER_NAME_PATH);
    return;
  }

  getline(fin, computer_name);
  fin.close();
}

void computer_information::get_cpu_information(){
  ifstream fin(CPU_INFO_PATH);
  if(!fin.is_open()){
    cpu_info.model_name = MESSAGE;
    cpu_info.cache_size = 0;
    cpu_info.cores = 0;
    perror(CPU_INFO_PATH);
    return;
  }

  string buffer;
  while(!fin.eof()){
    getline(fin, buffer);
    if(fin.eof()) break;

    if(buffer.empty()) break;

    unsigned long first_space = buffer.find(' ', 0);
    if(buffer.substr(0, first_space) == "cpu"){
      if(buffer.substr(first_space + 1, buffer.find('\t', first_space)
                                        - first_space - 1) == "cores"){
        cpu_info.cores = to_unsigned(get_value(buffer));
      }
    }

    if(buffer.substr(0, first_space) == "model"){
      if(buffer.substr(first_space + 1, buffer.find('\t', first_space + 1)
                                        - first_space - 1) == "name"){
        cpu_info.model_name = get_value(buffer);
      }
    }

    if(buffer.substr(0, first_space) == "cache"){
      cpu_info.cache_size = to_unsigned(get_value(buffer));
    }
  }
  fin.close();


}

void computer_information::get_cpu_load() {
  ifstream fin(CPU_LOAD_PATH);
  if(!fin.is_open()){
    cpu_info.one_min = 0;
    cpu_info.five_min = 0;
    cpu_info.ten_min = 0;
    cpu_info.run = 0;
    cpu_info.all = 0;
    perror(CPU_LOAD_PATH);
    return;
  }

  string buffer;
  getline(fin, buffer);
  unsigned long start = 0;
  unsigned long end = buffer.find(' ');
  cpu_info.one_min = atof(buffer.substr(start, end - start).c_str());
  start = end + 1;
  end = buffer.find(' ', start);
  cpu_info.five_min = atof(buffer.substr(start, end - start).c_str());
  start = end + 1;
  end = buffer.find(' ', start);
  cpu_info.ten_min = atof(buffer.substr(start, end - start).c_str());
  start = end + 1;
  end = buffer.find('/', start);
  cpu_info.run = to_unsigned(buffer.substr(start, end - start));
  start = end + 1;
  end = buffer.find(' ', start);
  cpu_info.all = to_unsigned(buffer.substr(start, end - start));

  fin.close();
}

extern "C" int start(){
  return 0;
}

extern "C" void result(){
  computer_information info;
  info.output();
}