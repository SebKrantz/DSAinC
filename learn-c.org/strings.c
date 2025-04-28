#include <stdio.h>
#include <string.h>

int main() {
  /* define first_name: read only string */
  char * first_name = "John";
  /* define last_name: Can be modified */
  char last_name[] = "Doe";
  char name[100];

  // first_name[0] = 'A';
  last_name[0] = 'B';
  
  // C formats: https://www.tutorialspoint.com/cprogramming/c_format_specifiers.htm (here long unsigned int)
  sprintf(name, "%s (%lu) %s (%lu)", first_name, strlen(first_name), last_name, strlen(last_name));
  printf("%s\n",name);

  // Compare the first 100 characters
  if (strncmp(name, "John Boe", 100) == 0) {
      printf("Done!\n");
  }

  /* Clear the name array */
  name[0] = '\0';

  /* Concatenate the first 4 characters of first_name */
  strncat(name, first_name, 4);

  /* Concatenate up to 20 characters of last_name */
  strncat(name, last_name, 20);

  /* Print the resulting concatenated string */
  printf("%s\n", name);

  return 0;
}