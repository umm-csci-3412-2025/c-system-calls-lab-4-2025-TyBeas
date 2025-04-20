#include <ftw.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
  if (typeflag == FTW_D) {
    num_dirs++;
  } else if (typeflag == FTW_F) {
    num_regular++;
  }
  return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
        if (argc != 2) {
                printf(stderr, "Usage: %s <path>\n", argv[0]);
                printf("Where <path> is the path to the directory to be summarized.\n");
                return 1;
        }

        ftw(argv[1], callback, MAX_FTW_DEPTH);

        printf("There were %d directories.\n", num_dirs);
        printf("There were %d regular files.\n", num_regular);

        return 0;
}