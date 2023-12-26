void get_files_in_dir(const char *path){
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
