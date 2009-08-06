#define GCC_COMPILE "gcc -c %s %s"

void    err(char *s, char *s2);
void    add(char *dst, char *src);
time_t  filedate(char *fn);
int     dep(char *fn, time_t t);
int     build(char *fn, time_t t);
void    make(char *fn);
int     main(int argc, char **argv);
