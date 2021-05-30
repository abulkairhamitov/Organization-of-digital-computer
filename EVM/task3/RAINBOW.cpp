#include <stdio.h>
#include <dos.h>
#include "graphics.h"
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#define pi 3.14159265358979323846
#define dx 100
#define dy 100
#define x0 10
#define y0 10
#define Maxx 7
#define Minx 0.5
int main(void){
int graph_driver,
graph_mode,
graph_error_code,
midx,
midy;
int k=0, i=0, j=0;
char str[3], str2[16];
double x1, y1, max=0, mashtabx = dx/pi, x,y;
clrscr();
graph_driver = DETECT;
initgraph(&graph_driver,&graph_mode, "C:\\TURBOC3\\BGI");
graph_error_code = graphresult();
if (graph_error_code != grOk){
printf("error%s\n", grapherrormsg(graph_error_code));
getch();
return 0;
}
midx = getmaxx();
midy = getmaxy()/2 - y0*y0;
setviewport(0, 0, midx, midy, 1);
line(x0, midy-y0*y0, midx, midy-y0*y0);
line(x0, midy, midx, midy);
for(i = dx; k <= Maxx; i+=dx)
{
k++;
sprintf(str, "pi", k);
outtextxy(i-15, midy-20, str);
line(i, midy+5, i, midy-5);
}
k=1;
for (j = y0+28; k>=-1; j+=dy)
{
 sprintf(str, "%d", k);
 outtextxy(0, j-7, str);
 line(x0, j, x0+5, j);
 k--;
}
setviewport(0, 0, midx, midy, 0);
x1 = Minx*pi;
do
{
y1 = sin(x1)*sin(x1)*sin(x1) - cos(x1)*cos(x1)*cos(x1);
x = x1 * mashtabx;
y = y1 * dy;
putpixel(x, midy - y, 5);
if(y1 > max)
max = y1;
x1 += 0.0001;
} while (x <= Maxx * dx);
+sprintf(str2, "Max value is %f", max);
outtextxy(0, midy+midy, str2);
getch();
//gerchar();
closegraph();
return 0;
}