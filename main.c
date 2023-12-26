#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char** argv) {

   (void)argc;
   (void)argv;

   const char* dir_path = ".";

   DIR* dir = opendir(dir_path);
   if (dir == NULL) {
      fprintf(stderr, "E: Could not open directory %s: %s\n", dir_path, strerror(errno));
      exit(1);
   }

   errno = 0;

   struct dirent* ent = readdir(dir);
   while (ent != NULL) {
      printf("file: %s\n", ent->d_name);
   }

   return 0;
}
