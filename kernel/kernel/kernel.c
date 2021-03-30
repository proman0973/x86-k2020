#if defined(__linux__)
#error "You need to use a cross-compiler!!"
#endif

#if !defined(__i386__)
#error "Target of this kernel must be i386!!"
#endif

#include <kernel/userTerminal.h>
#include <kernel/keyboard.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/paging.h>
#include <kernel/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main()
{
    terminal_init();

    terminal_writestring("Initializing GDT Table...\n");
    gdt_init();
    terminal_writestring("Initializing IDT Table...\n");
    idt_init();
    terminal_writestring("Enabling paging...\n");
    paging_init();
    terminal_writestring("Starting shell...\n");
    if (KB_initialize() != 0)
    {
        terminal_writestring("Keyboard controller initialization suceeded\n");
    }

    UT_init();

    while (true) {
        int key = getchar();
        UT_handleUserInput(key);
    }
}