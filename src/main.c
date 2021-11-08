/*
 *  lballoons - A terminal "screensaver" written in C
 *  Version 1.2.2
 *  Github: https://github.com/LordOfTrident/lballoons
 *
 *  This is the "art" source code and the one used
 *  by makefile, shaped into a hand holding a balloon.
 *  If you want to see the formatted readable one, look
 *  at readable.c
 */

#include <stdlib.h> // malloc, realloc, free, rand
#include <time.h> // usleep
#include <ncurses.h> // Terminal i/o

#define LB_VERSION_MAJOR 1
#define LB_VERSION_MINOR 2
#define LB_VERSION_PATCH 3

                     //lballoons
                int usleep(unsigned u);
             typedef struct{int x,y;char c
         ;}b;typedef struct{char h,c;}p;const
       char of[6]={1,0,0,1,1,1};const char br[6]
     [4]={"_","/#\\","\\_/","\\","/","\\"};b*o;p*
    r;int a,c,d,e,f,s,l=0,g,m;void n(){int x=0,y=0
  ;for(int i=0;i<s;++i){o[i].x=x*6+rand()%4;o[i].y=
  y*7+rand()%4;o[i].c=rand()%7+1;if(x>=c){x=0;++y;}\
 else++x;}}void t(){o=(b*)malloc(sizeof(b)*s);n();}//
void u(){r=(p*)malloc(sizeof(p)*l);for(int i=0;i<l;++i
){r[i].h=32;r[i].c=1;}}void v(){a=getmaxx(stdscr);c=a/
6;m=getmaxy(stdscr);d=m/7;f=d+2;e=7*(d+1);s=f*(c+1);g=
l;l=a*m;}int main(void){initscr();noecho();start_color
();use_default_colors();curs_set(0);timeout(0);raw();\
cbreak();init_pair(1,7,0);init_pair(2,4,0);init_pair(3
,1,0);init_pair(4,2,0);init_pair(5,3,0);init_pair(6,6,
 0);init_pair(7,5,0);v();t();u();char z=1;while(z){//
 int x=0;for(int i=0;i<s;++i){--o[i].y;if(o[i].y<-6){
  o[i].x=x*6+rand()%4;o[i].y=e;o[i].c=rand()%7+1;}b*
   _=&o[i];for(int i=0;i<6;++i){if((_->y+i)<0||(_->
    y+i)>=m)continue;for(int j=0;br[i][j]!=0&&j<4\
     ;++j){int p=of[i]+j;if((_->x+p)>=a||(_->x+p)
      <0)break;int pos=(_->y+i)*a+_->x+p;r[pos]\
        .h=br[i][j];if(i<3)r[pos].c=_->c;}}if(
          x>=c)x=0;else++x;}move(0,0);for(int
            i=0;i<l;++i){attron(COLOR_PAIR(
             r[i].c));addch(r[i].h);attroff
                (COLOR_PAIR(r[i].c));r\
                   [i].h=32;r[i].c=1
                      ;}refresh();
                          int
                         in=//
                         getch
                           ();
                          switch
                           (in)
                           {case
                            410
                            :v();
                            void
                            *tmp
                            =
                           realloc
                           (o,
                           sizeof
                            (b)*
                             s);
                              if(
                              tmp
                               ==
                               NULL
                               ){
                              free
                              (o);
                              t()
                             ;}
                            else
                            {o=
                            (b*)
                            tmp
                            ;n(
                             );}
                             tmp=
                           realloc
                     (r,sizeof(p)*a*m);\
                   if(tmp==NULL){free//23r3t//3t3f
                  (r);u();}else{r=/*[]'\/.'*///232r33
                    (p*)tmp;if(g<l) {for//rw3rwd--{*9}
                  (int i=g;i<l;++i)/*!@#$%^3rw*///4tawd
                    {r[i].h=32;r[i].c=1;//3428*][--'']
                   }}}break;case'q'&31://2343t38*(64)
                     z=0;}usleep(100000);}/**/\
                   free/*abcdefghijklm_2-*/
                    /*nopqrstuvxyz123*/
                            (o);
                            free
                             (r);
                             endwin
                              ();}
