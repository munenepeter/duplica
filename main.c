#include<stdio.h>
#include<dirent.h>

void print_files(const char *dir){
 //open the directory
 DIR *dir = opendir(dir);

 if(dir == NULL){
  fprintf(stderr, "Error: Could not open %s because of %s", dir, errno);
 exit(1);
}
 struct dirent* entry;
 
 while((entry = readdir(dir)) != NULL){
  printf("%s\n", entry->d_name;
} 

 closedir(dir);
}


int main(){

 char *dir = ".";

 print_files(dir);

 return  0;
}
