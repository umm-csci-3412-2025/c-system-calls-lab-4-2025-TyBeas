#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_WORD_LENGTH 1024

bool is_vowel(char vowel) {
  return (vowel == 'a' || vowel == 'e' || vowel == 'i' || vowel == 'o' || vowel == 'u' ||
          vowel == 'A' || vowel == 'E' || vowel == 'I' || vowel == 'O' || vowel == 'U');
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
  int j = 0;
  for (int i = 0; i < num_chars; i++) {
    if (!is_vowel(in_buf[i])) {
      out_buf[j] = in_buf[i];
      j++;
    }
  }
  return j;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
  char* in_buf = (char*) calloc(MAX_WORD_LENGTH, sizeof(char));
  char* out_buf = (char*) calloc(MAX_WORD_LENGTH, sizeof(char));

  while(!feof (inputFile)) {
    int elements_read = fread(in_buf, sizeof(char), MAX_WORD_LENGTH, inputFile);
    int consonants = copy_non_vowels(elements_read, in_buf, out_buf);
    fwrite (out_buf, sizeof(char), consonants, outputFile);
  }
  free(in_buf);
  free(out_buf);
}

int main(int argc, char *argv[]) {
  FILE *inputFile;
  FILE *outputFile;

  if (argc == 1) {
    inputFile = stdin;
    outputFile = stdout;
  } else if (argc == 2) {
    inputFile = fopen(argv[1], "r");
    outputFile = stdout;
  } else if (argc == 3) {
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
  } else {
    printf("Nothing");  
  }

  disemvowel(inputFile, outputFile);

  fclose(inputFile);
  fclose(outputFile);

  return 0;
}

