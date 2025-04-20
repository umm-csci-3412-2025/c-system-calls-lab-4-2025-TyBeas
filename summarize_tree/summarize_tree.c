#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  struct stat buf;

  if (stat(path, &buf) == 0) {
    int checkDir = S_ISDIR(buf.st_mode);
    if (checkDir!=0) {
      return true;
    } else {
      return false;
    }
  } else {
    printf("Problem with Path");
    return false;
  }
}

void process_path(const char*);

void process_directory(const char* path) {
  DIR* dirStream;

  struct dirent* content;

  char* dname;

  dirStream = opendir(path);

  if(dirStream!=NULL){
  chdir(path);
  while ((content = readdir(dirStream))) {
    dname = content->d_name;
    if (strcmp(dname, ".") != 0 && strcmp(dname, "..") != 0) {
      process_path(dname);
      }
    }
    num_dirs++;
    chdir("..");
  }

  closedir(dirStream);
}

  void process_file(const char* path) {
    num_regular++;
  }

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
