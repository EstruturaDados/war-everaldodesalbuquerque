#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// --- Funções Auxiliares ---

// Função para limpar o buffer de entrada.
// Essencial para garantir a leitura correta de futuras entradas de texto.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Remove o caractere de nova linha ('\n') adicionado por fgets, se estiver presente.
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// ----------------------------------------------------
// 1. Definição da Struct
// ----------------------------------------------------

struct Territorio {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército
    int tropas;    // Quantidade de tropas
};
typedef struct Territorio Territorio; 

// ----------------------------------------------------
// 2. Protótipos das Funções
// ----------------------------------------------------
void exibirTerritorios(Territorio* mapa, int total);
void cadastrarTerritorios(Territorio* mapa, int total);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// ----------------------------------------------------
// 3. Funções de Implementação
// ----------------------------------------------------

// Exibe os dados de todos os territórios cadastrados.
// Utiliza índices de 1 a N para o jogador.
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n--- Situacao Atual dos Territorios ---\n");
    if (mapa == NULL || total <= 0) {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }
    
    // Acessa os dados usando ponteiros (mapa + i)
    for (int i = 0; i < total; i++) {
        // Exibe o índice começando em 1 (i + 1)
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n", 
               i + 1, 
               (mapa + i)->nome, 
               (mapa + i)->cor, 
               (mapa + i)->tropas);
    }
    printf("--------------------------------------\n");
}

// Permite ao usuário cadastrar os dados de cada território.
// Garante que a quantidade de tropas seja de no minimo 1.
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("\n--- Cadastro de Territorios ---\n");
    
    for (int i = 0; i < total; i++) {
        Territorio* Territorio = (mapa + i); // Ponteiro para o território atual
        
        printf("\nTerritorio [%d]:\n", i + 1); 
        
        printf("   Nome: ");
        // Uso de fgets para leitura segura de string, aceitando espacos.
        fgets(Territorio->nome, sizeof(Territorio->nome), stdin); 
        removerNovaLinha(Territorio->nome); // Remove o '\n' deixado pelo fgets
        
        printf("   Cor do exercito: ");
        // Uso de fgets para leitura segura de string
        fgets(Territorio->cor, sizeof(Territorio->cor), stdin);
        removerNovaLinha(Territorio->cor); // Remove o '\n' deixado pelo fgets
        
        // Entrada de tropas com validação para o mínimo de 1
        printf("   Tropas (Minimo 1): ");
        if (scanf("%d", &(Territorio->tropas)) != 1 || Territorio->tropas < 1) { 
            Territorio->tropas = 1; 
            printf("Entrada invalida ou abaixo do minimo. Tropas definidas para 1.\n");
        }
        limparBuffer(); // Mantido apos scanf("%d")
    }
}

// Simula um ataque entre dois territórios.
// Os resultados são aleatorios (dado de 1 a 6).
void atacar(Territorio* atacante, Territorio* defensor) {
    // Rola um dado de 6 faces para cada lado
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\n--- Resolucao da Batalha ---\n");
    printf("%s (Atacante - %s) rolou: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("%s (Defensor - %s) rolou: %d\n", defensor->nome, defensor->cor, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // ATACANTE VENCE: Defensor perde o controle.
        printf("\n=> O atacante %s venceu! O territorio %s foi CONQUISTADO!\n", atacante->nome, defensor->nome);
        
        // 1. Mudar a cor do Território defensor para a cor do atacante.
        strcpy(defensor->cor, atacante->cor);
        
        // 2. Transferir metade das tropas do atacante (truncado)
        int tropasTransferidas = atacante->tropas / 2;
        
        atacante->tropas -= tropasTransferidas;
        
        // O Território defensor fica com as tropas transferidas (Cor) Atacante, mas o minimo é 1.
        defensor->tropas = (tropasTransferidas > 0) ? tropasTransferidas : 1; 
        
        printf("   - %d tropas foram transferidas de %s para %s.\n", tropasTransferidas, atacante->nome, defensor->nome);
        
    } else {
        // DEFENSOR VENCE ou EMPATE: Atacante perde 1 tropa.
        printf("\n=> O defensor %s manteve o territorio. O ataque falhou.\n", defensor->nome);
        
        // O atacante perde 1 tropa, mantendo o minimo de 1.
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("   - O atacante %s perdeu 1 tropa.\n", atacante->nome);
        } else {
            printf("   - O atacante %s nao perdeu tropas, pois ja possuia apenas o minimo (1).\n", atacante->nome);
        }
    }
}

// Libera a memoria alocada dinamicamente pelo calloc.
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria alocada para os territorios liberada com sucesso.\n");
    }
}

// ----------------------------------------------------
// 4. Função Principal (main)
// ----------------------------------------------------

int main() {
    // Inicializa o gerador de numeros aleatorios
    srand(time(NULL)); 
    
    int totalTerritorios = 0;
    int indexAtacante, indexDefensor;
    Territorio* mapa = NULL; // Ponteiro que apontará para o vetor alocado

    printf("=====================================\n");
    printf("    Desafio War! Nivel Aventureiro!\n");
    printf("=====================================\n");
    printf("Instrucoes: Territorios comecam em 1. Digite 0 para sair do modo de ataque.\n");

    // 4.1. Alocacao Dinamica de Territórios
    printf("\nInforme o numero total de territorios a serem cadastrados: ");
    if (scanf("%d", &totalTerritorios) != 1 || totalTerritorios <= 0) {
        printf("Numero de territorios invalido. Encerrando o programa.\n");
        limparBuffer(); 
        return 1;
    }
    limparBuffer(); 
    
    // Aloca a memoria dinamicamente usando calloc (requisito)
    mapa = (Territorio*)calloc(totalTerritorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro ao alocar memoria. Encerrando o programa.\n");
        return 1;
    }

    // 4.2. Cadastro dos Territórios
    cadastrarTerritorios(mapa, totalTerritorios);
    
    // 4.3. Simulação de Ataques
    
    do {
        exibirTerritorios(mapa, totalTerritorios);
        
        printf("\n--- SELECAO DE ATAQUE ---\n");
        printf("Escolha no indice de: [1 a %d] PARA O TERRITORIO ATACANTE (ou digite 0 para sair): ", totalTerritorios);
        
        if (scanf("%d", &indexAtacante) != 1) {
            limparBuffer(); 
            printf("Entrada invalida. Saindo da simulacao.\n");
            break; 
        }
        limparBuffer(); 

        // Ponto de SAÍDA: 0
        if (indexAtacante == 0) {
            break; 
        }

        // Converte o índice 1-base para o índice 0-base do array
        int indexatacante = indexAtacante - 1;

        // Validacao de atacante: verifica range e tropas minimas (> 1)
        if (indexAtacante < 1 || indexAtacante > totalTerritorios || (mapa + indexatacante)->tropas <= 1) {
            printf("Escolha de atacante invalida (indice fora do range ou tropas insuficientes > 1).\n");
            continue;
        }

        printf("Escolha no indice de: [1 a %d] PARA O TERRITORIO DEFENSOR: ", totalTerritorios);
        if (scanf("%d", &indexDefensor) != 1) {
            limparBuffer(); 
            printf("Entrada invalida.\n");
            continue;
        }
        limparBuffer(); 

        // Converte o índice 1-base para o índice 0-base do array
        int indexdefensor = indexDefensor - 1;

        // Validacao de defensor
        if (indexDefensor < 1 || indexDefensor > totalTerritorios || indexAtacante == indexDefensor) {
            printf("Escolha de defensor invalida.\n");
            continue;
        }

        // Validacao: nao atacar territorio da propria cor (requisito tecnico)
        if (strcmp((mapa + indexatacante)->cor, (mapa + indexdefensor)->cor) == 0) {
            printf("ERRO: O jogador nao pode atacar um territorio da PROPRIA COR!\n");
            continue;
        }
        
        // Executa a simulacao de ataque, passando os ponteiros dos structs
        atacar((mapa + indexatacante), (mapa + indexdefensor));
        
    } while (1);

    // 4.4. Liberação de Memória
    liberarMemoria(mapa); // Libera a memoria alocada dinamicamente

    return 0;
}
