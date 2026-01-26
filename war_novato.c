#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Criacao da struct usando typedef para facilicitar na chamada e criacao
// do vetor t
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} territorio;

// Funcao para evitar erros de entrada
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // vetor com cinco territorios(t)
    territorio t[5]; 

    // For de 0 a 4 para cadastrar o territorios(t)
    for (int i = 0; i < 5; i++)
    {      
        printf("==================================\n");
        printf("\n");
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do territorio: ");
        scanf(" %s", t[i].nome);
        limparbufferentrada(); // Limpeza de buffer para evitar erro
        printf("Cor do exercito (ex: Azul, Verde): ");
        fgets(t[i].cor, 10, stdin);
        printf("Numero de Tropas: ");
        scanf("%d", &t[i].tropas);
        limparbufferentrada();
        printf("\n");
    }


    printf("Cadastro inicial concluido com sucesso!");
    printf("\n");
    printf("\n");
    printf("==================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==================================\n");

    // For para exibir os territorios(t)
    for (int i = 0; i < 5; i++) {
        printf("TERRITORIO %d\n", i + 1);
        printf("\t- Nome: %s\n", t[i].nome);
        printf("\t- Dominado por: %s", t[i].cor);
        printf("\t- Tropas: %d\n", t[i].tropas);
    }

}