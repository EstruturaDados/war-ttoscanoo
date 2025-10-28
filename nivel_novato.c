// ============================================================================
//         PROJETO WAR ESTRUTURADO - NÍVEL NOVATO
// ============================================================================

#include <stdio.h>
#include <string.h> 

// 2. Definição da Struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio mapa[], int numTerritorios) {
    printf("WAR ESTRUTURADO - CADASTRO INICIAL\n\n");
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

void exibirMapa(const struct Territorio mapa[], int numTerritorios) {
    printf("\nMAPA DO MUNDO - ESTADO ATUAL\n");
    printf("===================================================\n");

    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("===================================================\n");
}

int main() {
    int numTerritorios = 5;
    struct Territorio mapa[numTerritorios];

    cadastrarTerritorios(mapa, numTerritorios);

    exibirMapa(mapa, numTerritorios);
    
    return 0;
}