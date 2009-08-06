/******************************************************
 * Ngaro
 *
 * Written by Charles Childers, released into the public
 * domain
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <curses.h>

#include "functions.h"
#include "vm.h"

FILE *input[64];
int isp=0;


/******************************************************
 * Display a character.
 *
 * Will clear the display if a negative value is passed
 ******************************************************/
void dev_putch(int c)
{
  if (c >= 0)
  {
    addch((char)c);
  }
  else
  {
    clear();
  }
}


/******************************************************
 * Update the display
 ******************************************************/
void dev_refresh()
{
  refresh();
}


/******************************************************
 * Read a character from an input source
 ******************************************************/
int dev_getch()
{
  int c;

  if ((c = getc(input[isp])) == EOF && input[isp] != stdin)
  {
    fclose(input[isp]);
    isp--;
    return 0;
  }

  if (c == EOF && input[isp] == stdin)
  {
    exit(0);
  }

  if (input[isp] != stdin)
  {
    if (c == 10 || c == 13 || c == 9)
      c = 32;
  }

  if (c == 10)
    c = 0;

  return c;
}


/******************************************************
 * Add a file to the input source list
 ******************************************************/
void dev_include(char *s)
{
  FILE *file;

  file = fopen(s, "r");

  if (file)
  {
    isp++;
    input[isp] = file;
  }
}


/******************************************************
 * Prepare real I/O hardware for the emulator
 ******************************************************/
void dev_init(int level)
{
  if (level == OUTPUT)
  {
    initscr();                /* initialize the curses library */
    cbreak();                 /* take input chars one at a time, no wait for \n */
    scrollok(stdscr, TRUE);   /* Allow the display to scroll */
  }
  if (level == INPUT)
  {
    isp = 0;
    input[isp] = stdin;
  }
}


/******************************************************
 * Cleanup real I/O hardware settings
 ******************************************************/
void dev_cleanup()
{
  endwin();
}
