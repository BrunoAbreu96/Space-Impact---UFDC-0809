# Registo de Sessões - Space Impact em C

## Sessão 1 – 21/08/2026 (09:00 - 10:00)
**Funcionalidades implementadas hoje:**
- Planeamento inicial do jogo Space Impact.
- Estruturação modular em múltiplos ficheiros (`main.c`, `game.c`, `game.h`).
- Integração da biblioteca ncurses e configuração inicial das janelas e cores.

**Maior dificuldade encontrada e como resolvi (ou não resolvi):**
- Configurar o ambiente do ncurses para responder no terminal sem atrasos. Resolvido com as diretivas `cbreak()` e `noecho()`.

**Próximo passo planeado:**
- Desenvolver a nave do jogador e os controlos de movimentação por teclado.

**Linhas de código escritas hoje (estimativa):**
- 55 linhas.

---

## Sessão 2 – 21/08/2026 (10:00 - 11:00)
**Funcionalidades implementadas hoje:**
- Adicionado o objeto da Nave do jogador utilizando estruturas (`struct`).
- Mapeamento das setas do teclado (`KEY_UP`, `KEY_DOWN`, etc.) para mover o jogador no ecrã.
- Implementação de limites físicos no cenário para impedir a nave de sair do mapa.

**Maior dificuldade encontrada e como resolvi (ou não resolvi):**
- Impedir que a nave ultrapassasse as bordas desenhadas. Resolvido adicionando condições lógicas de verificação antes de alterar as coordenadas `x` e `y`.

**Próximo passo planeado:**
- Desenvolver o sistema dinâmico de disparos de lasers.

**Linhas de código escritas hoje (estimativa):**
- 40 linhas.

---

## Sessão 3 – 21/08/2026 (11:00 - 12:00)
**Funcionalidades implementadas hoje:**
- Criação de uma matriz/array de estruturas para gerir múltiplos tiros ativos em simultâneo.
- Vinculação da tecla Espaço (' ') para instanciar novos tiros.
- Criação e movimentação autónoma dos inimigos surgindo a partir do lado direito do cenário.

**Maior dificuldade encontrada e como resolvi :**
- Fazer o jogo correr continuamente sem congelar o ecrã à espera que o utilizador carregasse numa tecla. Resolvido com a função `timeout(50)`.

**Próximo passo planeado:**
- Desenvolver o motor de colisões base e o painel de vidas.

---

## Sessão 4 – 21/08/2026 (12:00 - 13:00)
**Funcionalidades implementadas hoje:**
- Desenvolvimento do algoritmo de deteção de colisões (Tiro vs Inimigo).
- Sistema de pontuação acumulada por abates e ecrã básico de Game Over.
- Organização do código e teste geral de estabilidade.

**Maior dificuldade encontrada e como resolvi :**
- Sincronizar as posições na matriz do ecrã para as colisões registarem corretamente no ncurses. Resolvido ajustando a margem de colisão.

**Próximo passo planeado (Para a próxima sessão em casa):**
- Iniciar a personalização gráfica avançada: desenhar sprites complexos em ASCII, implementar inimigos com padrões de movimento em ziguezague e preparar a mecânica do Boss Final.

**Linhas de código escritas hoje (estimativa):**
- 50 linhas.
