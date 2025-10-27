// ============================================================================
//         PROJETO WAR ESTRUTURADO - NÍVEL NOVATO
//         Aluno: [Seu Nome Aqui]
// ============================================================================

// 1. Bibliotecas necessárias
#include <stdio.h>
#include <string.h> 

// 2. Definição da struct
/*
 * Documentação: 
 * Criação da struct Territorio para agrupar os dados
 * de cada território (nome, cor e número de tropas).
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    
    // 3. Declaração de vetor de structs
    // Cria um vetor estático com capacidade para 5 Territorios.
    struct Territorio mapa[5];
    int i; // Variável do loop

    printf("=== CADASTRO DE TERRITÓRIOS (NÍVEL NOVATO) ===\n");
    printf("Por favor, cadastre os 5 territórios:\n\n");

    // 4. Entrada dos dados
    /*
     * Laço 'for' para preencher os dados dos 5 territórios.
     * O laço roda 5 vezes (de i=0 até i=4).
     */
    for (i = 0; i < 5; i++) {
        printf("--- Território %d ---\n", i + 1);

        // Requisito: Use scanf para ler o nome
        printf("Digite o nome (sem espacos): ");
        scanf("%s", mapa[i].nome); 
        // Nota: scanf("%s", ...) só lê até o primeiro espaço em branco.

        printf("Digite a cor (sem espacos): ");
        scanf("%s", mapa[i].cor);

        // Requisito: Use scanf para ler o número de tropas
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }

    // 5. Exibição dos dados
    /*
     * Documentação:
     * Laço 'for' para percorrer o vetor e exibir os dados
     * de cada território cadastrado.
     */
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    printf("--------------------------------------------\n");
    printf("| %-20s | %-10s | %-6s |\n", "Território", "Cor", "Tropas");
    printf("--------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("| %-20s | %-10s | %-6d |\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("--------------------------------------------\n");

    
    return 0;
}