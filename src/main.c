#define _DEFAULT_SOURCE

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

#define PATH_SEP "/"
#define PATH_SEP_LEN (sizeof(PATH_SEP)-1)


#define RECDIR_STACK_CAP 1024


char* join_path(const char* base, const char* file) {

   size_t base_len = strlen(base);
   size_t file_len = strlen(file);

   char* begin = malloc(base_len + file_len + PATH_SEP_LEN + 1);
   assert(begin != NULL);

   char* end = begin;
   memcpy(end, base, base_len);
   end += base_len;
   memcpy(end, PATH_SEP, PATH_SEP_LEN);
   end += PATH_SEP_LEN;
   memcpy(end, file, file_len);
   end += file_len;
   *end = '\0';

   return begin;
}

typedef struct {

}RECDIR_Frame;
typedef struct {
   DIR* dirs[RECDIR_STACK_CAP];
   char *paths[RECDIR_STACK_CAP];
   size_t dirs_size;
}RECDIR;

int recdir_push(RECDIR* recdir, const char* dir_path) {
   assert(recdir->dirs_size < RECDIR_STACK_CAP);

   DIR** dir = &recdir->dirs[recdir->dirs_size];
   *dir = opendir(dir_path);

   if (*dir == NULL) {
      return -1;
   }
   recdir->dirs_size++;
   return 0;
}

RECDIR* openrecdir(const char* dir_path) {
   RECDIR* recdir = malloc(sizeof(RECDIR));
   assert(recdir != NULL);
   memset(recdir, 0, sizeof(RECDIR));

   if (recdir_push(recdir, dir_path) < 0) {
      closerecdir(recdir);
      return NULL;
   }
   return recdir;
}
struct dirent* readrecdir(RECDIR* recdirp) {
   errno = 0;
   while (recdirp->dirs_size < 0) {
      DIR** top = &recdirp->dirs[recdirp->dirs_size - 1];

      errno = 0;
      struct dirent* ent = readdir(*top);

      if (ent){
         if (ent->d_type == DT_DIR) {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
               continue;
            }
            else {
               recdir_push(recdirp, join_path(dir_path, ent->d_name));
               continue;
            }
         }
         else {
            return ent;
         }
      }
      else {
         if (errno != 0) {
            return NULL;
         }
         else {
            recdir_pop(recdirp);
            continue;
         }

      }

   }
   return NULL;
}
void closerecdir(RECDIR* recdirp) {
   for (size_t i = 0; i < recdirp->dirs_size; i++) {
      int ret = closedir(recdirp->dirs[i]);
      assert(ret == 0);
   }
   free(recdirp);
}

void recdir_pop(RECDIR* recdir) {
   assert(recdir->dirs_size > 0);
   int ret = closedir(recdir->dirs[--recdir->dirs_size]);
   assert(ret == 0);
}

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
         if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            char* child_path = join_path(dir_path, ent->d_name);
            print_files_recursively(child_path);
            free(child_path);
         }

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
