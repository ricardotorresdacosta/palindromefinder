#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void open_file(FILE **readfile)
{
  *readfile = fopen("readfile.txt", "r");

  if (*readfile == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
}

int get_text_size(FILE **readfile)
{
  int sizetext;
  char c;

  for (int i = 0; (c = fgetc(*readfile)) != EOF; i++)
  {
    sizetext = i;
  }
  printf("Number of characters in text is: %d\n", sizetext);

  return sizetext;
}

char *save_text_in_array(int sizetext, FILE **readfile, char arr[])
{
  rewind(*readfile);
  fread(arr, sizetext, 1, *readfile);

  return arr;
}

char *format_array(int sizetext, char text[], char formattedarr[])
{

  for (int i = 0; i < sizetext; i++)
  {
    formattedarr[i] = tolower(text[i]);
  }

  printf("The original text is '%s'.\nThe formatted text is '%s'.\nFormatted text has double the size,ie, %d, because it stores both original and formatted text.\n", text, formattedarr, sizetext * 2);

  return formattedarr;
}

void print_palindrome_found(int *i, int j, char text[])
{

  printf("\t\t\tWe found a palindrome:\t");
  int z;
  for (int k = 0; *i <= j - k; k++)
  {
    z = *i + k;
    printf("%c", text[z]);
  }
  printf("\n");
  *i = j;
}

int is_last_characters_reached(int a, int b)
{
  if (a + 1 >= b - 1)
    return 1;
  else
    return 0;
}

int is_character_accent_or_punctuation(char text[], int i)
{
  if (text[i] == ' ' || text[i] == '"' || text[i] == '\'' || text[i] == ':' || text[i] == ';' || text[i] == ',' || text[i] == '.' || text[i] == '!' || text[i] == '?')
    return 1;
  else
    return 0;
}

void check_if_subtext_is_palindrome(int *i, int j, char text[], char formattedtext[], int a, int b)
{
  ////////////////////////////////////////////////////////
  ///////////////      inner loop          ///////////////
  ////////////////////////////////////////////////////////
  for (int counter = 0; a < b; a++, b--, counter++)
  {
    if (is_character_accent_or_punctuation(formattedtext, a))
    {
      b = b + 1;

      if (is_last_characters_reached(a, b))
      {
        print_palindrome_found(&*i, j, text);
        break;
      }
      continue;
    }

    if (is_character_accent_or_punctuation(formattedtext, b))
    {
      a = a - 1;
      if (is_last_characters_reached(a, b))
      {
        print_palindrome_found(&*i, j, text);
        break;
      }
      continue;
    }

    if (formattedtext[a] == formattedtext[b])
    {
      if (is_last_characters_reached(a, b))
      {
        print_palindrome_found(&*i, j, text);
        break;
      }

      continue;
    }
    else
    {
      break;
    }
  }
}

void check_palindromes_starting_in_position_i(int *i, int sizetext, char text[], char formattedtext[])
{
  ////////////////////////////////////////////////////////
  ///////////////      middle loop         ///////////////
  ////////////////////////////////////////////////////////
  for (int j = sizetext; *i < j; j--)
  {
    int a = *i;
    int b = j;

    if (formattedtext[*i] == formattedtext[j])
    {
      check_if_subtext_is_palindrome(&*i, j, text, formattedtext, a, b);
    }
    else
    {
      continue;
    }
  }
}

void find_and_print_palindromes_in_text(int sizetext, char text[], char formattedtext[])
{
  ////////////////////////////////////////////////////////
  ///////////////      outer loop          ///////////////
  ////////////////////////////////////////////////////////
  for (int i = 0; i < sizetext; i++)
  {
    if (is_character_accent_or_punctuation(formattedtext, i))
    {
      continue;
    }

    check_palindromes_starting_in_position_i(&i, sizetext, text, formattedtext);
  }
}

int main()
{
  FILE *readfile;

  open_file(&readfile);

  int sizetext = get_text_size(&readfile);

  char arr[sizetext];
  char *text = save_text_in_array(sizetext, &readfile, arr);

  fclose(readfile);

  char formattedarr[sizetext];
  char *formattedtext = format_array(sizetext, text, formattedarr);

  find_and_print_palindromes_in_text(sizetext, text, formattedtext);
}
