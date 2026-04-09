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

void Atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    // printf("--- FASE DE ATAQUE ---");

    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;
    
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

char* missoes[5] = {
    "Eliminar todas as tropas de cor vermelha.",
    "Reduzir as tropas de um territorio inimigo para exatamente uma tropa.",
    "Conquistar tres territorios seguidos.",
    "Controlar ao menos 5 territorios ao mesmo tempo.",
    "Conquistar dois territorios de cores de exercito diferentes em qualquer ordem."
};

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

int verificarMissao(char* missao, Territorio* mapa, int quantidade_territorios, char* corJogador) {
    // retorna 1 se cumpriu, 0 se nao cumpriu
    //Missao 1: eliminar todas as tropas de cor vermelha
    if (strcmp(missao, "Eliminar todas as tropas de cor vermelha.") == 0) {
        for (int i = 0; i < quantidade_territorios; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 || strcmp(mapa[i].cor, "Vermelho") == 0) { 
                // Verificar sem tem territorio vermelho
                return 0;
            }
        }
        // Nao acho nenhum territorio vermelho.
        return 1;
    }

    //Missao 2: Reduzir tropas de um territorio para exatamente uma tropa
    if (strcmp(missao, "Reduzir as tropas de um territorio inimigo para exatamente uma tropa.") == 0) {
        for (int i = 0; i < quantidade_territorios; i++) {
            // identificar territorio inimigo sendo cor diferente do jogador principal
            if (strcmp(mapa[i].cor, corJogador) != 0 && mapa[i].tropas == 1) {
                return 1; // ja existe inimigo com apenas uma tropa
            } 
        }
        return 0; // condicao nao realizada
    }

    //Missao 3: conquistar tres territorios seguidos
    if (strcmp(missao, "Conquistar tres territorios seguidos.") == 0) {
        int contador = 0;
        for (int i = 0; i < quantidade_territorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }
        if (contador >= 3) {
            return 1;
        } else {
            return 0;
        }
    }

    //Missao 4: Controlar cinco territorios
    if (strcmp(missao, "Controlar ao menos 5 territorios ao mesmo tempo.") == 0) {
        int contador = 0;
        for (int i = 0; i < quantidade_territorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }
        if (contador >= 5) {
            return 1;
        } else {
            return 0;
        }
    }

    // Missao 5: conquistar dois territorios de cores diferente em qualquer ordem
    if (strcmp(missao, "Conquistar dois territorios de cores de exercito diferentes em qualquer ordem.") == 0) {
        char corInimigo1[10] = "";
        char corInimigo2[10] = "";

        for (int i = 0; i < quantidade_territorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) {
                if (corInimigo1[0] == '\0') {
                    strcpy(corInimigo1, mapa[i].cor);
                } else if (strcmp(mapa[i].cor, corInimigo1) != 0) {
                    strcpy(corInimigo2, mapa[i].cor);
                    return 1;
                } 
            }
        }
        return 0;
    }

    return 0;
}

void LiberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}


int main() {

    // malloc para missoes
    char* missaoJogador = malloc(200 * sizeof(char));

    if (missaoJogador == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }
    

    srand(time(NULL));
    // Pergunta ao usuario para saber quantidade de territorios
    int quantidade_territorios;
    int indiceAtacante, indiceDefensor;
    char corJogador[10];

    printf("Quantos territorios voce quer cadastrar? ");
    scanf("%d", &quantidade_territorios);

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

    // define cor do jogador como a cor do primeiro territorio
    strcpy(corJogador, mapa[0].cor);
    atribuirMissao(missaoJogador, missoes, 5);
    printf("Sua missao: %s\n", missaoJogador);
    printf("\n");

    ExibirTerritorios(mapa, quantidade_territorios);
    

    int opcao;

    do {
        printf("---------------------------------\n");
        printf("---WAR MESTRE---\n");
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

            if (verificarMissao(missaoJogador, mapa, quantidade_territorios, corJogador)) {
                printf("Parabens voce cumpriu sua missao!\n");
            }
            
            break;
        case 3:
            printf("Saindo do programa...\n");
            printf("\nPressione Enter para continuar...\n");
            getchar();
            break;
        default:
            printf("Opcao invalida!\n");
            printf("\nPressione Enter para continuar...\n");
            getchar();
            break;
        }
    } while (opcao != 3);
    
    ExibirTerritorios(mapa, quantidade_territorios);
    LiberarMemoria(mapa, missaoJogador);
}