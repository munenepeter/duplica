#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

void print_files_recursively(const char* dir_path) {

   DIR* dir = opendir(dir_path);
   if (dir == NULL) {
      fprintf(stderr, "E: Could not open directory %s: %s\n", dir_path, strerror(errno));
      exit(1);
   }

   errno = 0;

   struct dirent* ent = readdir(dir);
   while (ent != NULL) {
      if (ent->d_type == DT_DIR) {
         print_files_recursively(concat(dir_path, ent->d_name));
      }
      else {
         printf("file: %s\n", ent->d_name);
      }
      ent = readdir(dir);
   }

   if (errno != 0) {
      fprintf(stderr, "E: could not read directory %s: %s \n", dir_path, strerror(errno));
      exit(1);
   }


   closedir(dir);
}


int main(int argc, char** argv) {

   (void)argc;
   (void)argv;

   const char* dir_path = ".";
   print_files_recursively(dir_path);
   return 0;
}
