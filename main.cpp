#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <memory>

using namespace std;

#define DIR_PATH "/home/linux/University/course/"
#define EXTENSION ".out"
#define MAIN "main.out"

int select (const struct dirent *dir){
    if ( !strcmp(".", dir->d_name) || !strcmp("..", dir->d_name)){
      return 0;
    }

    if(!strrchr(dir->d_name, '.')){
        return 0;
    }

    string ext = strrchr(dir->d_name, '.');

    if(strlen(EXTENSION) < ext.length()){
        return strncmp(EXTENSION, ext.c_str(), strlen(EXTENSION)) == 0;
    } else{
        return strncmp(EXTENSION, ext.c_str(), ext.length()) == 0;
    }
}

int main(void){
    setlocale(LC_ALL, "");

    int count;
    struct dirent **dir;

    count = scandir(DIR_PATH, &dir, select, alphasort);
    if(count == -1){
        perror("scandir");
        return 1;
    }

    for(int i = 0; i < count; i++){
        if(strcmp(dir[i]->d_name, MAIN) == 0){
            continue;
        }

        int pid = fork();

        switch(pid){
        case -1:
            perror("fork");
            return 1;
        case 0:
            unique_ptr<char> path(new char[strlen(DIR_PATH) +
                    strlen(dir[i]->d_name) + 1]);

            strcpy(path.get(), DIR_PATH);
            strcat(path.get(), dir[i]->d_name);

            if(execl(path.get(),path.get(), nullptr) == -1) {
                perror("execl");
                return 1;
            }
        }

        waitpid(pid, NULL, 0);
    }

    for(int i = 0; i < count; i++){
        free(dir[i]);
    }
    free(dir);

   return 0;
}
