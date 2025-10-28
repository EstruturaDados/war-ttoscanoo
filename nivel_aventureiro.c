/*
 ============================================================================
         PROJETO WAR ESTRUTURADO - NÍVEL AVENTUREIRO
 ============================================================================
*/

// 1. Bibliotecas
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include <time.h>     

// 2. Definição da Struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// 3. Protótipos das Funções
struct Territorio* alocarMemoria(int numTerritorios);
void liberarMemoria(struct Territorio* mapa);
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios);
void exibirMapa(const struct Territorio* mapa, int numTerritorios);
void selecionarAtaque(struct Territorio* mapa, int numTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);


int main() {
    int numTerritorios = 5; 
    struct Territorio* mapa = NULL; // Ponteiro para o mapa

    // Requisito: Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("WAR ESTRUTURADO - CADASTRO INICIAL\n\n");

    // Requisito: Alocação dinâmica com calloc
    mapa = alocarMemoria(numTerritorios);

    // Verifica se a alocação de memória funcionou
    if (mapa == NULL) {
        printf("Erro critico: Falha ao alocar memoria para o mapa!\n");
        return 1; 
    }

    // Preenche os dados dos territórios
    cadastrarTerritorios(mapa, numTerritorios);

    exibirMapa(mapa, numTerritorios);
        
    selecionarAtaque(mapa, numTerritorios);
        
    // Requisito: Liberar a memória alocada
    liberarMemoria(mapa);
    mapa = NULL; // Boa prática: anular o ponteiro

    printf("Jogo finalizado. Memoria liberada!\n");
    return 0;
}

/*IMPLEMENTAÇÃO DAS FUNÇÕES*/

struct Territorio* alocarMemoria(int numTerritorios) {
    struct Territorio* ptr = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    return ptr;
}

void liberarMemoria(struct Territorio* mapa) {
    printf("Liberando memoria do mapa...\n");
    free(mapa);
}

void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do Exercito: ");
        scanf("%s", mapa[i].cor);
        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

void exibirMapa(const struct Territorio* mapa, int numTerritorios) {
    printf("\nMAPA DO MUNDO - ESTADO ATUAL\n");
    printf("===================================================\n");

    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===================================================\n");
}

void selecionarAtaque(struct Territorio* mapa, int numTerritorios) {
    int idAtacante, idDefensor;
    
    // Loop de ataque: continua até o usuário digitar 0
    while (1) {
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", numTerritorios);
        scanf("%d", &idAtacante);

        if (idAtacante == 0) {
            printf("Encerrando fase de ataque...\n");
            break; 
        }

        printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &idDefensor);

        // --- Validações ---

        // 1. Valida se os IDs estão no intervalo correto
        if (idAtacante < 1 || idAtacante > numTerritorios ||
            idDefensor < 1 || idDefensor > numTerritorios) {
                printf("\nErro: ID de territorio invalido! Escolha entre 1 e %d.\n", numTerritorios);
                continue; // Volta para o início do loop
        }
        
        // 2. Converte o ID para o índice do veto
        struct Territorio* atacante = &mapa[idAtacante - 1];
        struct Territorio* defensor = &mapa[idDefensor - 1];

        // 3. Valida se está atacando a si mesmo
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("\nErro: Voce nao pode atacar um territorio da sua propria cor (%s)!\n", atacante->cor);
            continue;
        }

        // 4. Valida se tem tropas suficientes (precisa de >1 tropa para atacar)
        if (atacante->tropas < 2) {
            printf("\nErro: O territorio atacante %s precisa de pelo menos 2 tropas para atacar!\n", atacante->nome);
            continue;
        }

        // Se tudo estiver OK, chama a função de batalha
        atacar(atacante, defensor);

        printf("\nPressione Enter para continuar para o proximo turno...\n");
        while (getchar() != '\n');
        getchar();

        // Exibe o mapa atualizado após a batalha 
        exibirMapa(mapa, numTerritorios);
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n--- RESULTADO DA BATALHA ---\n");

    // Simula os dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas -= 1;

        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas -= 1;
        }

    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }
}