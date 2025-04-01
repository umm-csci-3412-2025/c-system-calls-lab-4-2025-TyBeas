#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define MAX_WORD_LENGTH 1024

bool is_vowel(char c) {
  const char* vowels = "aeiouAEIOU";
  for (int i = 0; i < 10; i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

int copy_non_vowels(char* num_chars, char* in_buf, char* out_buf) {
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
  char in_buf[MAX_WORD_LENGTH];
  char out_buf[MAX_WORD_LENGTH];
  int num_chars = fread(in_buf, sizeof(char), MAX_WORD_LENGTH, inputFile);
  while(num_chars != 0) {
    int num_consonants = copy_non_vowels(num_chars, in_buf, out_buf);
    fwrite(out_buf, sizeof(char), num_consonants, outputFile);
    num_chars = fread(in_buf, sizeof(char), MAX_WORD_LENGTH, inputFile);
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
  }
  
  if (argc == 2) {
    inputFile = fopen(argv[1], "r");
    outputFile = stdout;
  }
  
  if (argc == 3) {
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
  }

  disemvowel(inputFile, outputFile);

  fclose(inputFile);
  fclose(outputFile);
  return 0;
}

