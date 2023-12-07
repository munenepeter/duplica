#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<dirent.h>

void print_files(const char *path){
 //open the directory
 DIR *dir = opendir(path);

 if(dir == NULL){
  fprintf(stderr, "Error: Could not open %s because of %d", path, errno);
  exit(1);
 }
 struct dirent* entry;
 
 while((entry = readdir(dir)) != NULL){
  printf("%s\n", entry->d_name);
 } 

 closedir(dir);
}


int main(int argc, char **argv){

   if(argc < 1){
	printf("Usage: Please provide a directory path");
	return 1;
   }
  
  
 const char *dir = ".";

 print_files(dir);

 return  0;
}
