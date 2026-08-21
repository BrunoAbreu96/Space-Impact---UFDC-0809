#include "ncurses.h"
#include <stdlib.h>
#include "game.h"

void inicializar_jogo(Nave *jogador, Tiro tiros[], Inimigo inimigos[]) {
    jogador->x = MAX_LINHAS / 2;
    jogador->y = 3;
    jogador->vidas = 3;
    jogador->pontuacao = 0;

    for (int i = 0; i < MAX_TIROS; i++) tiros[i].ativo = 0;
    for (int i = 0; i < MAX_INIMIGOS; i++) {
        inimigos[i].ativo = 0;
        inimigos[i].tipo = 0;
    }
}

void processar_input(Nave *jogador, Tiro tiros[], int tecla) {
    switch (tecla) {
        case KEY_UP:    if (jogador->x > 1) jogador->x--; break;
        case KEY_DOWN:  if (jogador->x < MAX_LINHAS - 2) jogador->x++; break;
        case KEY_LEFT:  if (jogador->y > 1) jogador->y--; break;
        case KEY_RIGHT: if (jogador->y < MAX_COLUNAS - 4) jogador->y++; break;
        
        // Barra de espaço dispara laser
        case ' ':
            for (int i = 0; i < MAX_TIROS; i++) {
                if (!tiros[i].ativo) {
                    tiros[i].x = jogador->x;
                    tiros[i].y = jogador->y + 2; // Nasce à frente da nave
                    tiros[i].ativo = 1;
                    break;
                }
            }
            break;
    }
}

void atualizar_jogo(Tiro tiros[], Inimigo inimigos[], Nave *jogador) {
    // 1. Movimentação dos Tiros (Direita)
    for (int i = 0; i < MAX_TIROS; i++) {
        if (tiros[i].ativo) {
            tiros[i].y++;
            if (tiros[i].y >= MAX_COLUNAS - 1) {
                tiros[i].ativo = 0;
            }
        }
    }

    // 2. Movimentação dos Inimigos (Esquerda e Ziguezague)
    for (int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            // Todos avançam para a esquerda
            if (rand() % 2 == 0) {
                inimigos[i].y--;
            }
            
            // Se for Kamikaze (tipo 1), move-se na vertical (Ziguezague)
            if (inimigos[i].tipo == 1) {
                if (rand() % 3 == 0) {
                    inimigos[i].x += (rand() % 2 == 0) ? 1 : -1;
                    
                    // Mantém nos limites do mapa
                    if (inimigos[i].x <= 1) inimigos[i].x = 2;
                    if (inimigos[i].x >= MAX_LINHAS - 2) inimigos[i].x = MAX_LINHAS - 3;
                }
            }
            
            // Inimigo ultrapassou a defesa
            if (inimigos[i].y <= 0) {
                inimigos[i].ativo = 0;
                jogador->vidas--;
            }
        }
    }

    // 3. Geração Aleatória de Inimigos (Com tipos diferentes)
    if (rand() % 15 == 0) { 
        for (int i = 0; i < MAX_INIMIGOS; i++) {
            if (!inimigos[i].ativo) {
                inimigos[i].x = 1 + rand() % (MAX_LINHAS - 2);
                inimigos[i].y = MAX_COLUNAS - 2;
                inimigos[i].ativo = 1;
                
                // 30% de probabilidade de gerar um Kamikaze (tipo 1)
                inimigos[i].tipo = (rand() % 10 < 3) ? 1 : 0;
                break;
            }
        }
    }

    // 4. Deteção de Colisões (Tiro vs Inimigo)
    for (int t = 0; t < MAX_TIROS; t++) {
        if (!tiros[t].ativo) continue;
        
        for (int j = 0; j < MAX_INIMIGOS; j++) {
            if (!inimigos[j].ativo) continue;
            
            if (tiros[t].x == inimigos[j].x && (tiros[t].y == inimigos[j].y || tiros[t].y == inimigos[j].y + 1)) {
                tiros[t].ativo = 0;
                inimigos[j].ativo = 0;
                
                // Kamikazes dão mais pontos por serem difíceis
                jogador->pontuacao += (inimigos[j].tipo == 1) ? 20 : 10;
                break;
            }
        }
    }

    // 5. Deteção de Colisões (Inimigo vs Jogador)
    for (int j = 0; j < MAX_INIMIGOS; j++) {
        if (inimigos[j].ativo && inimigos[j].x == jogador->x && (inimigos[j].y == jogador->y || inimigos[j].y == jogador->y + 1)) {
            inimigos[j].ativo = 0;
            jogador->vidas--;
        }
    }
}

void desenhar_cenario(Nave *jogador, Tiro tiros[], Inimigo inimigos[]) {
    clear();

    // Desenha as bordas superior e inferior do Espaço
    for (int c = 0; c < MAX_COLUNAS; c++) {
        mvprintw(0, c, "#");
        mvprintw(MAX_LINHAS - 1, c, "#");
    }

    // Desenha os Tiros (Amarelo)
    attron(COLOR_PAIR(3));
    for (int i = 0; i < MAX_TIROS; i++) {
        if (tiros[i].ativo) {
            mvprintw(tiros[i].x, tiros[i].y, "-");
        }
    }
    attroff(COLOR_PAIR(3));

    // Desenha os Inimigos (Vermelho)
    attron(COLOR_PAIR(1));
    for (int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            if (inimigos[i].tipo == 1) {
                mvprintw(inimigos[i].x, inimigos[i].y, "X"); // Kamikaze
            } else {
                mvprintw(inimigos[i].x, inimigos[i].y, "<"); // Normal
            }
        }
    }
    attroff(COLOR_PAIR(1));

    // Desenha a Nave Jogador (Azul)
    attron(COLOR_PAIR(2));
    mvprintw(jogador->x, jogador->y, "=>");
    attroff(COLOR_PAIR(2));

    // Painel de Informações inferior
    mvprintw(MAX_LINHAS, 2, "VIDAS: %d  |  PONTUAÇÃO: %d  |  Preme 'q' para Sair", jogador->vidas, jogador->pontuacao);
    refresh();
}
