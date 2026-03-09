#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Criacao da struct usando typedef para facilicitar na chamada e criacao
// do vetor t
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funcao para evitar erros de entrada
void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funcao para cadastro de territorios
void CadastrarTerritorios(Territorio* mapa, int quantidade_de_territorios) {
    for (int i = 0; i < quantidade_de_territorios; i++)
    {      
        printf("==================================\n");
        printf("\n");
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do territorio: ");
        scanf(" %s", mapa[i].nome);
        limparbufferentrada(); // Limpeza de buffer para evitar erro
        printf("Cor do exercito (ex: Azul, Verde): ");
        fgets(mapa[i].cor, 10, stdin);
        // Tirando '\n' do final para melhor exibicao do territorio
        int teste = strlen(mapa[i].cor);
        mapa[i].cor[teste - 1] = '\0';
        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparbufferentrada();
        printf("\n");
    }
    printf("Cadastro inicial concluido com sucesso!");
    printf("\n");
}

// Funcao Exibicao de territorios
void ExibirTerritorios(Territorio* mapa, int quantidade_territorios) {
    printf("============================================\n");
    printf("        MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("============================================\n");
    for (int i = 0; i < quantidade_territorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1,
             mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

//Funcao para ataque
void Atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    // Dando valores aleatorios ao dados
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;
    
    //Checando se territorios pentecem a mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Os territorios pertecem a mesma cor.\n");
        limparbufferentrada();
        getchar();
    } else {
        if (dadoAtacante > dadoDefensor) {
            printf("--- RESULTADO DA BATALHA ---\n");
            printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
            printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);
            printf("VITORIA DO ATAQUE!, o defensor perdeu uma tropa.\n");
            defensor->tropas = defensor->tropas - 1;
            if (defensor->tropas == 0) {
                printf("CONQUISTA!, O territorio %s for dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
                strcpy(defensor->cor, atacante->cor);
                defensor->tropas = defensor->tropas + 1;
            } 
        } else if (dadoAtacante < dadoDefensor) {
            printf("--- RESULTADO DA BATALHA ---\n");
            printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
            printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);
            printf("VITORIA DA DEFESA!, o atacante perdeu uma tropa.\n");
            atacante->tropas = atacante->tropas - 1;
            if (atacante->tropas == 1) {
                printf("Suas tropas acabaram!\n");
            }
        } else {
            printf("Houve um empate, ninguem perde!\n");
        }
    }
}

void LiberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));
    // Pergunta ao usuario para saber quantidade de territorios
    int quantidade_territorios;
    int indiceAtacante, indiceDefensor;
    printf("Quantos territorios voce quer cadastrar? ");
    scanf("%d", &quantidade_territorios);

    //Caso a quantidade de territorios seja um valor impossivel
    while (quantidade_territorios < 2)
    {
        printf("Quantidade invalida!, tente novamente\n");
        printf("Quantos territorios voce quer cadastrar? ");
        scanf("%d", &quantidade_territorios);
    }

    // Alocacao dinamica para ter uma qunatidade de territorios variavel
    Territorio* mapa = (Territorio*)calloc(quantidade_territorios, sizeof(Territorio)); 
    // Verificando se alocacao deu certo.
    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; // Retorna 1 para indicar um erro.
    }

    CadastrarTerritorios(mapa, quantidade_territorios);
    ExibirTerritorios(mapa, quantidade_territorios);

    int opcao;

    do {
        printf("---------------------------------\n");
        printf("---WAR AVENTUREIRO---\n");
        printf("Escolha uma opcao: \n");
        printf("1. Exibir territorios atuais\n");
        printf("2. Fase de ataque\n");
        printf("3. Sair do programa\n");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            ExibirTerritorios(mapa, quantidade_territorios);
            printf("\nPressione Enter para continuar...\n");
            limparbufferentrada();
            getchar();
            break;
        case 2:
            printf("--- FASE DE ATAQUE ---\n");
            printf("Escolha o territorio atacante (1 a %d): ", quantidade_territorios);
            scanf("%d", &indiceAtacante);
            printf("Escolha o territorio defensor (1 a %d): ", quantidade_territorios);
            scanf("%d", &indiceDefensor);
            if ((indiceAtacante < 1 || indiceAtacante > quantidade_territorios) || (indiceDefensor < 1 || indiceDefensor > quantidade_territorios)) {
                printf("Territorio nao existe!\n");
                break;
            } else {
                Atacar(&mapa[indiceAtacante - 1], &mapa[indiceDefensor - 1]);
                printf("\nPressione Enter para continuar...\n");
                limparbufferentrada();
                getchar();
            }
            break;
        case 3:
            printf("Saindo do programa...\n");
            printf("\nPressione Enter para continuar...\n");
            getchar();
        default:
            printf("Opcao invalida!\n");
            printf("\nPressione Enter para continuar...\n");
            getchar();
            break;
        }
    } while (opcao != 3);
    
    ExibirTerritorios(mapa, quantidade_territorios);
    LiberarMemoria(mapa);
}