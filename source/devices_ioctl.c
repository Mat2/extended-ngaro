/******************************************************
 * Ngaro
 *
 * Written by Charles Childers, released into the public
 * domain
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>

struct termios new_termios, old_termios;
FILE *input[8];
int isp=0;


/******************************************************
 * Display a character.
 *
 * Will clear the display if a negative value is passed
 ******************************************************/
void dev_putch(int c)
{
  if (c > 0)
  {
    putchar((char)c);
  }
  else
  {
    printf("\033[2J\033[1;1H");
  }
}


/******************************************************
 * Update the display
 ******************************************************/
void dev_refresh()
{
}



/******************************************************
 * Get input from an input source
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

  return c;
}


/******************************************************
 * Add a file to the input stack
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
 * Initialize real hardware devices
 ******************************************************/
void dev_init(int level)
{
  if (level == 2)
  {
    tcgetattr(0, &old_termios);
    new_termios = old_termios;
    new_termios.c_iflag &= ~(BRKINT+ISTRIP+IXON+IXOFF);
    new_termios.c_iflag |= (IGNBRK+IGNPAR);
    new_termios.c_lflag &= ~(ICANON+ISIG+IEXTEN+ECHO);
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_termios);
  }
  if (level == 1)
  {
    isp = 0;
    input[isp] = stdin;
  }
}


/******************************************************
 * Restore real hardware device settings
 ******************************************************/
void dev_cleanup()
{
  tcsetattr(0, TCSANOW, &old_termios);
}
