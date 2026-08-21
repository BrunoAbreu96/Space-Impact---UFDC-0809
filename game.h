#ifndef GAME_H
#define GAME_H

#define MAX_LINHAS 18
#define MAX_COLUNAS 50
#define MAX_TIROS 20
#define MAX_INIMIGOS 15

typedef struct {
    int x, y;
    int ativo;
} Tiro;

typedef struct {
    int x, y;
    int ativo;
    int tipo; // 0 = Normal (<), 1 = Kamikaze (X) em Ziguezague
} Inimigo;

typedef struct {
    int x, y;
    int vidas;
    int pontuacao;
} Nave;

// Protótipos das funções do jogo
void inicializar_jogo(Nave *jogador, Tiro tiros[], Inimigo inimigos[]);
void desenhar_cenario(Nave *jogador, Tiro tiros[], Inimigo inimigos[]);
void processar_input(Nave *jogador, Tiro tiros[], int tecla);
void atualizar_jogo(Tiro tiros[], Inimigo inimigos[], Nave *jogador);

#endif
