#ifndef NCURSES_H
#define NCURSES_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Usa o comando CLS nativo do Windows que limpa o ecrã sem deixar vestígios nem breaks
#define clear() system("cls")
#define mvprintw(x, y, ...) printf("\033[%d;%dH" __VA_ARGS__, (x)+1, (y)+1)
#define refresh() fflush(stdout)
#define start_color()
#define init_pair(...)
#define attron(...)
#define attroff(...)
#define COLOR_PAIR(...) 0
#define curs_set(...)
#define initscr() printf("\033[?25l") // Esconde o cursor piscante
#define endwin() printf("\033[?25h")  // Mostra o cursor ao sair
#define cbreak()
#define noecho()
#define keypad(...)
#define timeout(...)

#define getch() obter_tecla()

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

static int obter_tecla(void) {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            return _getch(); // Captura as setas corretamente no Windows
        }
        return ch;
    }
    Sleep(30); // 30ms é o equilíbrio perfeito para o jogo correr fluido e sem breaks
    return -1;
}

#endif
