// ============================================================================
//              PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
// ============================================================================
// CONSTANTES GLOBAIS
// ============================================================================
#define NUM_TERRITORIOS 6
#define NUM_MISSOES 3
#define TAM_NOME 50
// ============================================================================
// ESTRUTURA DE DADOS
// ============================================================================
typedef struct {
    char nome[TAM_NOME];
    char cor[20];
    int tropas;
} Territorio;
// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================
// Setup e gerenciamento de memória
Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);
// Interface
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa);
void exibirMissao(int missao);
// Lógica do jogo
void faseDeAtaque(Territorio *mapa, const char *corJogador);
void simularAtaque(Territorio *origem, Territorio *destino,
                   const char *corJogador);
int sortearMissao();
int verificarVitoria(const Territorio *mapa,
                     const char *corJogador,
                     int missao);
// Função utilitária
void limparBufferEntrada();
// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    // Aloca memória para o mapa
    Territorio *mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para o mapa.\n");
        return 1;
    }
    // Inicializa os territórios
    inicializarTerritorios(mapa);
    // Define a cor do jogador
    char corJogador[20];
    strcpy(corJogador, "Azul");
    // Sorteia a missão
    int missao = sortearMissao();
    int opcao;
    int venceu = 0;
    // ========================================================================
    // LOOP PRINCIPAL DO JOGO
    // ========================================================================
    do {
        printf("\n");
        printf("========================================\n");
        printf("              PROJETO WAR\n");
        printf("========================================\n");
        exibirMapa(mapa);
        exibirMissao(missao);
        exibirMenuPrincipal();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, corJogador);
                break;
            case 2:
                venceu = verificarVitoria(
                    mapa,
                    corJogador,
                    missao
                );
                if (venceu) {
                    printf("\n========================================\n");
                    printf("       MISSAO CUMPRIDA!\n");
                    printf("       VOCE VENCEU O JOGO!\n");
                    printf("========================================\n");
                } else {
                    printf("\nA missao ainda nao foi cumprida.\n");
                }
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
        if (opcao != 0 && !venceu) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opcao != 0 && !venceu);
    // Libera a memória
    liberarMemoria(mapa);
    return 0;
}
// ============================================================================
// ALOCAÇÃO DO MAPA
// ============================================================================
Territorio* alocarMapa() {
    Territorio *mapa;
    mapa = (Territorio*) calloc(
        NUM_TERRITORIOS,
        sizeof(Territorio)
    );
    return mapa;
}
// ============================================================================
// INICIALIZAÇÃO DOS TERRITÓRIOS
// ============================================================================
void inicializarTerritorios(Territorio *mapa) {
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 10;
    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Azul");
    mapa[1].tropas = 8;
    strcpy(mapa[2].nome, "Chile");
    strcpy(mapa[2].cor, "Vermelho");
    mapa[2].tropas = 7;
    strcpy(mapa[3].nome, "Peru");
    strcpy(mapa[3].cor, "Vermelho");
    mapa[3].tropas = 6;
    strcpy(mapa[4].nome, "Mexico");
    strcpy(mapa[4].cor, "Verde");
    mapa[4].tropas = 5;
    strcpy(mapa[5].nome, "Canada");
    strcpy(mapa[5].cor, "Verde");
    mapa[5].tropas = 5;
}
// ============================================================================
// LIBERAÇÃO DA MEMÓRIA
// ============================================================================
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}
// ============================================================================
// EXIBIR MENU PRINCIPAL
// ============================================================================
void exibirMenuPrincipal() {
    printf("\n========================================\n");
    printf("             MENU PRINCIPAL\n");
    printf("========================================\n");
    printf("1 - Atacar territorio\n");
    printf("2 - Verificar missao\n");
    printf("0 - Sair\n");
    printf("========================================\n");
}
// ============================================================================
// EXIBIR MAPA
// ============================================================================
void exibirMapa(const Territorio *mapa) {
    int i;
    printf("\n================ MAPA ==================\n");
    printf("%-15s %-15s %-10s\n",
           "Territorio",
           "Cor",
           "Tropas");
    printf("----------------------------------------\n");
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-15s %-15s %-10d\n",
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("========================================\n");
}
// ============================================================================
// EXIBIR MISSÃO
// ============================================================================
void exibirMissao(int missao) {
    printf("\n============== SUA MISSAO ==============\n");
    if (missao == 1) {
        printf("Destruir completamente o exercito Vermelho.\n");
    } else if (missao == 2) {
        printf("Conquistar pelo menos 3 territorios.\n");
    } else if (missao == 3) {
        printf("Conquistar pelo menos 4 territorios.\n");
    }
    printf("========================================\n");
}
// ============================================================================
// FASE DE ATAQUE
// ============================================================================
void faseDeAtaque(Territorio *mapa,
                  const char *corJogador) {
    int origem;
    int destino;
    printf("\n============== ATAQUE ==================\n");
    printf("Escolha o territorio de origem:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            printf("%d - %s (%d tropas)\n",
                   i,
                   mapa[i].nome,
                   mapa[i].tropas);
        }
    }
    printf("\nDigite o numero do territorio de origem: ");
    scanf("%d", &origem);
    limparBufferEntrada();
    if (origem < 0 || origem >= NUM_TERRITORIOS) {
        printf("Territorio invalido!\n");
        return;
    }
    if (strcmp(mapa[origem].cor, corJogador) != 0) {
        printf("Voce nao controla esse territorio!\n");
        return;
    }
    if (mapa[origem].tropas <= 1) {
        printf("Voce precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }
    printf("\nEscolha o territorio que deseja atacar:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (i != origem &&
            strcmp(mapa[i].cor, corJogador) != 0) {
            printf("%d - %s (%s - %d tropas)\n",
                   i,
                   mapa[i].nome,
                   mapa[i].cor,
                   mapa[i].tropas);
        }
    }
    printf("\nDigite o numero do territorio de destino: ");
    scanf("%d", &destino);
    limparBufferEntrada();
    if (destino < 0 || destino >= NUM_TERRITORIOS) {
        printf("Territorio invalido!\n");
        return;
    }
    if (destino == origem) {
        printf("Voce nao pode atacar o proprio territorio!\n");
        return;
    }
    if (strcmp(mapa[destino].cor, corJogador) == 0) {
        printf("Esse territorio ja pertence a voce!\n");
        return;
    }
    simularAtaque(
        &mapa[origem],
        &mapa[destino],
        corJogador
    );
}
// ============================================================================
// SIMULAR ATAQUE
// ============================================================================
void simularAtaque(Territorio *origem,
                   Territorio *destino,
                   const char *corJogador) {
    int dadoAtacante;
    int dadoDefensor;
    printf("\n============== BATALHA ================\n");
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;
    printf("Atacante: %s\n", origem->nome);
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("\nDefensor: %s\n", destino->nome);
    printf("Dado do defensor: %d\n", dadoDefensor);
    if (dadoAtacante > dadoDefensor) {
        destino->tropas--;
        printf("\nO atacante venceu a rodada!\n");
        if (destino->tropas <= 0) {
            strcpy(destino->cor, corJogador);
            destino->tropas = 1;
            origem->tropas--;
            printf("\nTerritorio conquistado!\n");
            printf("O territorio %s agora pertence ao exercito %s.\n",
                   destino->nome,
                   corJogador);
        }
    } else {
        origem->tropas--;
        printf("\nO defensor venceu a rodada!\n");
        printf("O atacante perdeu uma tropa.\n");
    }
    printf("========================================\n");
}
// ============================================================================
// SORTEAR MISSÃO
// ============================================================================
int sortearMissao() {
    return (rand() % NUM_MISSOES) + 1;
}
// ============================================================================
// VERIFICAR VITÓRIA
// ============================================================================
int verificarVitoria(const Territorio *mapa,
                     const char *corJogador,
                     int missao) {
    int i;
    int territoriosJogador = 0;
    int exercitoVermelho = 0;
    // Conta os territórios do jogador
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosJogador++;
        }
        if (strcmp(mapa[i].cor, "Vermelho") == 0) {
            exercitoVermelho++;
        }
    }
    // Missão 1:
    // Destruir completamente o exército vermelho
    if (missao == 1) {
        if (exercitoVermelho == 0) {
            return 1;
        }
    }
    // Missão 2:
    // Conquistar pelo menos 3 territórios
    else if (missao == 2) {
        if (territoriosJogador >= 3) {
            return 1;
        }
    }
    // Missão 3:
    // Conquistar pelo menos 4 territórios
    else if (missao == 3) {
        if (territoriosJogador >= 4) {
            return 1;
        }
    }
    return 0;
}
// ============================================================================
// LIMPAR BUFFER DE ENTRADA
// ============================================================================
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Apenas limpa os caracteres restantes
    }
}
