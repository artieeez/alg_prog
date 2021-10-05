#include <conio2.h>
#include <stdlib.h>

int main()
{
    struct text_info info;
    int i;

    /* get the info about screen */
    gettextinfo( &info );

    /* set normal cursor */
    _setcursortype( _NORMALCURSOR );

    /* clear the screen */
    clrscr();

    /* paint border around screen */
    gotoxy( 1, 1 );
    for (i = 1; i <= info.screenwidth; i++) putch( '*' );
    gotoxy( 1, info.screenheight );
    for (i = 1; i < info.screenwidth; i++) putch( '*' );
    for (i = 2; i < info.screenheight; i++)
    {
        putchxy( 1, i, '*' );
        putchxy( info.screenwidth, i, '*' );
    }

    int exit = 0;
    int x = 10;
    int y = 10;
    putchxy( x, y, '*' );
    do
    {
        if (kbhit())
        {
            char c = getch();
            if ((int) c == -32)
            {
                putchxy( x, y, ' ' );
                switch(getch())
                {
                case 72:
                    y -= 1;

                    if (y < 1) {
                        y = info.screenheight;
                    }
                    putchxy( x, y, '^' );
                    // code for arrow up
                    break;
                case 80:
                    y += 1;
                    putchxy( x, y, 'v' );
                    // code for arrow down
                    break;
                case 77:
                    x += 2;
                    putchxy( x, y, '>' );
                    // code for arrow right
                    break;
                case 75:
                    x -= 2;
                    putchxy( x, y, '<' );
                    // code for arrow left
                    break;
                }
                gotoxy( 1, 1 );
            }

        }
        // gotoxy( 2, 10 );
    }
    while(!exit);

    return 0;
}


