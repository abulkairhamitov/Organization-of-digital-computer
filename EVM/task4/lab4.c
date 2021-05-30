#include <conio.h>
#include <dos.h>

union REGS r;
void print_star()
{
    r.h.ah = 0x02;
    r.h.dl = '*';
    int86(0x21, &r, &r);
}

int main()
{
    int x1 = 10;
    int y1 = 8;
    int x2 = 70;
    int y2 = 18;
    int x = 0;  /*0-60*/
    int key = 0;

    clrscr();
    window(x1,y1,x2,y2);
    gotoxy(0,0);
    print_star();
    // cprintf("*");
    while(key != 1) 
    {
        if (kbhit())
        {
            r.h.ah = 0x10;
            int86(0x16, &r, &r);
            key = r.h.ah;
        }
        clrscr();
        if(key == 63)
        {
            clrscr();
            x--;
            if(x == -1)
                x = 60;
        }
        else if(key == 64)
        {
            clrscr();
            x++;
            if(x == 41)
                x = 0;
        }
        gotoxy(x+1,1);
        print_star();
        // cprintf("*");
        delay(200);
    }
    return 0;
}