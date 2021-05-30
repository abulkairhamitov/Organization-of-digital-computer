#include <conio.h>

#include <dos.h>

const char* const colors[]= {
  "BLACK",
  "BLUE",
  "GREEN",
  "CYAN",
  "RED",
  "MAGENTA",
  "BROWN",
  "LIGHTGRAY",

  "DARKGRAY",
  "LIGHTBLUE",
  "LIGHTGREEN",
  "LIGHTCYAN",
  "LIGHTRED",
  "LIGHTMAGENTA",
  "YELLOW",
  "WHITE"
}; 

void main()
{

  int i, j;
  short T = 600;

  int x1 = 25, y1 = 5, 
      x2 = 55, y2 = 15;

  union REGS regs;

  regs.h.ah = 7;
  regs.h.al = (unsigned char) 1;
  regs.h.cl = (unsigned char) (x1-1);
  regs.h.ch = (unsigned char) (y1-1);
  regs.h.dl = (unsigned char) (x2-1);
  regs.h.dh = (unsigned char) (y2-1);

  clrscr();
  window(x1, y1, x2, y2);

  gotoxy(1, 1);

  for (j = 0; j < 8; j++)
  {
    textbackground(j);
    for (i = 0; i < 16; i++)
    {
      textcolor(i);
      cprintf("S: %s, B: %s", colors[i], colors[j]);
      delay(T);

      int86(0x10, & regs, & regs);

      gotoxy(1, 1);
    }
  }
  delay(T);
}