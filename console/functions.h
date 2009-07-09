#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "vm.h"

/* FILE: devices.c */
extern int dev_getch();
extern void dev_refresh();
extern void dev_include(char *s);
extern void dev_putch(int c);
extern void dev_init(int level);
extern void dev_cleanup();

/* FILE: disassemble.c */
extern void display_instruction();

/* FILE: endian.c */
extern void swapEndian(VM *vm);

/* FILE: initial_image.c */
extern void initial_image(VM *vm);

/* FILE: loader.c */
extern int vm_load_image(VM *vm, char *image);
extern int vm_save_image(VM *vm, char *image);

/* FILE: ngaro.c */
extern int main(int argc, char **argv);

/* FILE: video.c */
extern void drawpixel(int x, int color);
extern int update_display(void *unused);

/* FILE: vm.c */
extern void init_vm(VM *vm);
extern void vm_process(VM *vm);
extern void init_devices(VM *vm);
extern void cleanup_devices(VM *vm);

#endif
