// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> // Para o setlocale

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 5
#define COR_JOGADOR "Azul" // Cor do jogador principal

// Vetor global com a descrição das missões
const char* MISSOES_DESCRICAO[NUM_MISSOES] = {
    "Conquistar 3 territorios",
    "Eliminar todas as tropas da cor Vermelha",
    "Conquistar o territorio Asia",
    "Ter 10 tropas no territorio Brasil",
    "Conquistar todos os 5 territorios"
};

// --- Estrutura de Dados ---
// Define a estrutura para um território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas

// Funções de setup e gerenciamento de memória:
struct Territorio* alocarMapa();
void inicializarTerritorios(struct Territorio* mapa);
void liberarMemoria(struct Territorio* mapa);
int sortearMissao();

// Funções de interface com o usuário:
void exibirMenuPrincipal();
void exibirMapa(const struct Territorio* mapa, int numTerritorios);
void exibirMissao(int missaoID, const char* missoes[]);

// Funções de lógica principal do jogo:
void faseDeAtaque(struct Territorio* mapa, int numTerritorios);
void simularAtaque(struct Territorio* atacante, struct Territorio* defensor);
int verificarVitoria(int missaoID, const struct Territorio* mapa, int numTerritorios);

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo
int main() {
    // 1. Configuração Inicial (Setup):
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    // Aloca a memória para o mapa do mundo
    struct Territorio* mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro critico: Falha ao alocar memoria para o mapa!\n");
        return 1;
    }

    inicializarTerritorios(mapa); // Preenche os territórios com dados iniciais
    
    // Define a cor do jogador e sorteia sua missão secreta
    printf("====================================================\n");
    printf("       BEM-VINDO AO WAR ESTRUTURADO - MESTRE        \n");
    printf("====================================================\n");
    printf("Voce e o comandante do Exercito %s.\n", COR_JOGADOR);
    int missaoID = sortearMissao();
    
    // Variáveis do loop
    int opcao = -1;
    int vitoria = 0;

    // 2. Laço Principal do Jogo (Game Loop):
    // Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    do {
        // A cada iteração, exibe o mapa e o menu de ações.
        exibirMapa(mapa, NUM_TERRITORIOS);
        exibirMissao(missaoID, MISSOES_DESCRICAO);
        exibirMenuPrincipal();
        
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o "Enter"

        // Lê a escolha do jogador e usa um 'switch'
        switch(opcao) {
            case 1:
                // Opção 1: Inicia a fase de ataque.
                faseDeAtaque(mapa, NUM_TERRITORIOS);
                break;
            case 2:
                // Opção 2: Verifica se a condição de vitória foi alcançada
                vitoria = verificarVitoria(missaoID, mapa, NUM_TERRITORIOS);
                if (vitoria) {
                    printf("\n****************************************************\n");
                    printf("  VITORIA! Voce completou sua missao!\n");
                    printf("****************************************************\n");
                } else {
                    printf("\n----------------------------------------------------\n");
                    printf("  Voce ainda nao cumpriu sua missao.\n");
                    printf("----------------------------------------------------\n");
                }
                break;
            case 0:
                // Opção 0: Encerra o jogo.
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        
        // Pausa a execução para que o jogador possa ler os resultados
        if (opcao != 0 && vitoria == 0) {
            printf("\nPressione Enter para continuar...\n");
            limparBufferEntrada();
        }

    } while (opcao != 0 && vitoria == 0); // Continua se 'opcao' não for 0 E 'vitoria' for 0

    // 3. Limpeza:
    // Ao final do jogo, libera a memória alocada para o mapa
    liberarMemoria(mapa);
    mapa = NULL;
    printf("Jogo finalizado. Memoria liberada.\n");

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
struct Territorio* alocarMapa() {
    return (struct Territorio*) calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor, tropas).
void inicializarTerritorios(struct Territorio* mapa) {
    printf("Inicializando territorios...\n");
    // Dados de exemplo
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Azul");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Verde");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor, "Vermelha");
    mapa[2].tropas = 4;

    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].cor, "Amarela");
    mapa[3].tropas = 3;

    strcpy(mapa[4].nome, "Europa");
    strcpy(mapa[4].cor, "Branca");
    mapa[4].tropas = 4;
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal() {
    printf("\n--- MENU DE ACOES ---\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missao\n");
    printf("0. Sair do Jogo\n");
    printf("Escolha sua acao: ");
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa.
// Usa 'const' para garantir que a função apenas leia os dados (const correctness).
void exibirMapa(const struct Territorio* mapa, int numTerritorios) {
    printf("\nMAPA DO MUNDO - ESTADO ATUAL\n");
    printf("===================================================\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 
            i + 1, 
            mapa[i].nome, 
            mapa[i].cor, 
            mapa[i].tropas);
    }
    printf("===================================================\n");
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
void exibirMissao(int missaoID, const char* missoes[]) {
    // 'const' para garantir que a função só lê
    printf("Sua missao: ** %s **\n", missoes[missaoID]);
}

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando os territórios.
void faseDeAtaque(struct Territorio* mapa, int numTerritorios) {
    int idAtacante, idDefensor;
    
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1 a %d): ", numTerritorios);
    scanf("%d", &idAtacante);
    printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
    scanf("%d", &idDefensor);
    limparBufferEntrada(); // Limpa o "Enter"

    // Validações
    if (idAtacante < 1 || idAtacante > numTerritorios ||
        idDefensor < 1 || idDefensor > numTerritorios || idAtacante == idDefensor) {
        printf("Erro: IDs invalidos!\n");
        return;
    }

    // Passagem por referência (ponteiros)
    struct Territorio* atacante = &mapa[idAtacante - 1];
    struct Territorio* defensor = &mapa[idDefensor - 1];

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Voce nao pode atacar sua propria cor!\n");
        return;
    }
    if (atacante->tropas < 2) {
        printf("Erro: O territorio atacante precisa de pelo menos 2 tropas!\n");
        return;
    }

    // Chama a função simularAtaque() para executar a lógica da batalha.
    simularAtaque(atacante, defensor);
}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
void simularAtaque(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n--- RESULTADO DA BATALHA ---\n");
    // Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    printf("Dado Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) { 
        printf("VITORIA DO ATAQUE! %s conquistou %s!\n", atacante->nome, defensor->nome);
        
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas == 0) tropasTransferidas = 1; 

        atacante->tropas -= tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;
        
        printf("%s agora tem %d tropas.\n", defensor->nome, defensor->tropas);
        printf("%s ficou com %d tropas.\n", atacante->nome, atacante->tropas);

    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
        printf("%s (atacante) ficou com %d tropas.\n", atacante->nome, atacante->tropas);
    }
}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
int sortearMissao() {
    return rand() % NUM_MISSOES;
}

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
int verificarVitoria(int missaoID, const struct Territorio* mapa, int numTerritorios) {
    // Pega o texto da missão usando o ID
    const char* missao = MISSOES_DESCRICAO[missaoID];
    
    // Missão 1: "Conquistar 3 territorios"
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int contagem = 0;
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                contagem++;
            }
        }
        return (contagem >= 3); // Retorna 1 (true) se a contagem for 3+
    }

    // Missão 2: "Eliminar todas as tropas da cor Vermelha"
    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelha") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Vermelha") == 0) {
                return 0; // Achou um Vermelho, missão incompleta
            }
        }
        return 1; // Loop terminou, nenhum Vermelho encontrado
    }

    // Missão 3: "Conquistar o territorio Asia"
    if (strcmp(missao, "Conquistar o territorio Asia") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].nome, "Asia") == 0 && strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                return 1;
            }
        }
        return 0;
    }
    
    // Missão 4: "Ter 10 tropas no territorio Brasil"
    if (strcmp(missao, "Ter 10 tropas no territorio Brasil") == 0) {
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].nome, "Brasil") == 0 && 
                strcmp(mapa[i].cor, COR_JOGADOR) == 0 && 
                mapa[i].tropas >= 10) {
                return 1;
            }
        }
        return 0;
    }

    // Missão 5: "Conquistar todos os 5 territorios"
    if (strcmp(missao, "Conquistar todos os 5 territorios") == 0) {
        int contagem = 0;
        for (int i = 0; i < numTerritorios; i++) {
            if (strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                contagem++;
            }
        }
        return (contagem == 5);
    }
    
    return 0; // Nenhuma missão conhecida
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}