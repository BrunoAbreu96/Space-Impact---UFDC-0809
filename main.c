#include "ncurses.h"
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main(void) {
    srand(time(NULL));
    
    // Inicialização do ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(50); // Loop corre a cada 50ms

    // Configuração de cores
    init_pair(1, COLOR_RED, COLOR_BLACK);   // Inimigos
    init_pair(2, COLOR_BLUE, COLOR_BLACK);  // Jogador
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Lasers

    Nave jogador;
    Tiro tiros[MAX_TIROS];
    Inimigo inimigos[MAX_INIMIGOS];

    inicializar_jogo(&jogador, tiros, inimigos);

    int tecla;
    while (jogador.vidas > 0 && (tecla = getch()) != 'q') {
        processar_input(&jogador, tiros, tecla);
        atualizar_jogo(tiros, inimigos, &jogador);
        desenhar_cenario(&jogador, tiros, inimigos);
    }

    // Ecrã Final de Game Over
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(MAX_LINHAS / 2, (MAX_COLUNAS / 2) - 5, "GAME OVER");
    attroff(COLOR_PAIR(1));
    mvprintw((MAX_LINHAS / 2) + 1, (MAX_COLUNAS / 2) - 9, "Pontos Finais: %d", jogador.pontuacao);
    refresh();
    
    timeout(-1);
    getch();

    endwin();
    return 0;
}
