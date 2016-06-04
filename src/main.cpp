#include <cstring>
#include <iostream>
#include <memory>
#include <dlfcn.h>
#include <dirent.h>

using namespace std;

#define LIB_PATH "/home/linux/University/course/build/lib/"
#define EXTENSION ".so"

int select (const struct dirent *dir) {
  if (!strcmp(".", dir->d_name) || !strcmp("..", dir->d_name)) {
    return 0;
  }

  if (!strrchr(dir->d_name, '.')) {
    return 0;
  }

  string ext = strrchr(dir->d_name, '.');

  if (strlen(EXTENSION) < ext.length()) {
    return strncmp(EXTENSION, ext.c_str(), strlen(EXTENSION)) == 0;
  } else {
    return strncmp(EXTENSION, ext.c_str(), ext.length()) == 0;
  }
}

int main(void) {
  setlocale(LC_ALL, "");

  int count;
  struct dirent **dir;

  count = scandir(LIB_PATH, &dir, select, alphasort);
  if (count == -1) {
    perror("scandir");
    return 1;
  }

  for (int i = 0; i < count; i++) {
    string path = LIB_PATH;
    path += dir[i]->d_name;
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
      cerr << dlerror() << endl;;
      return 1;
    }

    typedef void (*start_t)();
    typedef void (*result_t)();

    start_t start = (start_t) dlsym(handle, "start");
    result_t result = (result_t) dlsym(handle, "result");
    if (dlerror()) {
      cerr << dlerror() << endl;
      dlclose(handle);
      return 1;
    }

    start();
    result();
  }

  return 0;
}