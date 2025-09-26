#include <stdio.h>
#include <string.h>

/* 
   Estrutura Territorio:
   Armazena informações de um território no jogo.
   Campos:
   - nome: nome do território
   - cor: cor do exército associado ao território
   - tropas: quantidade de tropas presentes
*/
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    
        // Mensagem inicial do jogo
    printf("=====================================\n");
    printf("    Desafio War! Nível Novato!\n");
    printf("=====================================\n");   
    
    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf("%s", &territorios[i].nome); 

        printf("Digite a cor do exército: ");
        scanf("%s", &territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos territórios cadastrados
    printf("\n===== Territórios Cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}