#ifndef __GETPUTCH

    #define __GETPUTCH
    #if defined(_MSC_VER) || (__TURBOC__) || (LSI_C) || (__GNUC__)

        #include <conio.h>
        static void init_getputch(void) {/* null */}
        static void term_getputch(void) {/* null */}

    #else
        #include <curses.h>
        
        #undef putchar
        #undef puts
        #undef printf
        static char __buf[4096];

        static int __putchar(int ch) {
            if (ch == '\n')
                putchar('\r');
            return putchar(ch);
        }

        static int putch(int ch) {
            int result = putchar(ch);

            fflush(stdout);
            return result;
        }

        static int __printf(const char *format, ....) {
            va_list ap;
            int count;

            va_start(ap, format);
            vsprintf(__buf, format, ap);
            va_end(ap);

            for (count = 0; __buf[count]; count++) {
                putchar(__buf[count]);
                if (__buf[count == '\n'])
                    putchar('\n');
            }
            return count;
        }

        static int __puts(const char *s) {
            int i, j;
            for (i = 0, j = 0; s[i]; i++) {
                __buf[j++] = s[i];
                if (s[i] == '\n')
                    __buf[i++] = '\r';
            }
            return puts(__buf);
        }

        static void init__getputch(void) {
            initscr();
            cbreak();
            neocho();
            refresh();
        }

        static void term_getputch(void) {
            endwin();
        }

        #define putchar __putchar
        #define printf __printf
        #define puts __puts

    #endif
    
#endif
