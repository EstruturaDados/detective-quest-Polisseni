#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.



    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------- STRUCT --------------------

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ---------------- FUNÇÕES ---------------------

Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void conectarSalas(Sala* origem, Sala* esquerda, Sala* direita) {
    origem->esquerda = esquerda;
    origem->direita = direita;
}

void explorarSalas(Sala* atual) {
    char opcao;

    while (1) {
        printf("\nVocê está na sala: %s\n", atual->nome);
        printf("Ir para a esquerda (e)\n");
        printf("Ir para a direita (d)\n");
        printf("Sair (s)\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\nNão há sala à esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\nNão há sala à direita!\n");
            }
        }
        else if (opcao == 's') {
            printf("\nExploração encerrada.\n");
            break;
        }
        else {
            printf("\nOpção inválida!\n");
        }
    }
}

// -------------------- MAIN --------------------

int main() {

    // Criando as salas (árvore fixa)
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porão");

    // Conectando as salas
    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, jardim);
    conectarSalas(cozinha, porao, NULL);

    // Iniciando exploração
    explorarSalas(hall);

    // Liberando memória
    free(hall);
    free(biblioteca);
    free(cozinha);
    free(sotao);
    free(jardim);
    free(porao);

    return 0;
}


    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= STRUCTS =================

typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// ================= BST - PISTAS =================

Pista* criarPista(char texto[]) {
    Pista* nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

Pista* inserirPista(Pista* raiz, char texto[]) {
    if (raiz == NULL) {
        return criarPista(texto);
    }

    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    }
    else if (strcmp(texto, raiz->texto) > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    // Se for igual, não insere novamente

    return raiz;
}

void emOrdem(Pista* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        emOrdem(raiz->direita);
    }
}

void listarPistas(Pista* raiz) {
    if (raiz == NULL) {
        printf("\nNenhuma pista coletada ainda.\n");
    } else {
        printf("\n===== PISTAS COLETADAS (Ordem Alfabética) =====\n");
        emOrdem(raiz);
    }
}

// ================= SALAS =================

Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void conectarSalas(Sala* origem, Sala* esquerda, Sala* direita) {
    origem->esquerda = esquerda;
    origem->direita = direita;
}

// ================= EXPLORAÇÃO =================

void explorarSalas(Sala* atual, Pista** arvorePistas) {
    char opcao;

    while (1) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Gerar pistas automaticamente ao entrar em certas salas
        if (strcmp(atual->nome, "Biblioteca") == 0) {
            *arvorePistas = inserirPista(*arvorePistas, "Livro antigo com páginas rasgadas");
        }
        if (strcmp(atual->nome, "Cozinha") == 0) {
            *arvorePistas = inserirPista(*arvorePistas, "Faca com manchas suspeitas");
        }
        if (strcmp(atual->nome, "Sótão") == 0) {
            *arvorePistas = inserirPista(*arvorePistas, "Caixa trancada com iniciais");
        }
        if (strcmp(atual->nome, "Porão") == 0) {
            *arvorePistas = inserirPista(*arvorePistas, "Pegadas lamacentas no chão");
        }

        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("p - Ver pistas coletadas\n");
        printf("s - Sair da exploração\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\nNão há sala à esquerda!\n");
            }
        }
        else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\nNão há sala à direita!\n");
            }
        }
        else if (opcao == 'p') {
            listarPistas(*arvorePistas);
        }
        else if (opcao == 's') {
            printf("\nExploração encerrada.\n");
            break;
        }
        else {
            printf("\nOpção inválida!\n");
        }
    }
}

// ================= MAIN =================

int main() {

    // Árvore das pistas
    Pista* raizPistas = NULL;

    // Criando as salas
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* sotao = criarSala("Sótão");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porão");

    // Conectando
    conectarSalas(hall, biblioteca, cozinha);
    conectarSalas(biblioteca, sotao, jardim);
    conectarSalas(cozinha, porao, NULL);

    // Exploração
    explorarSalas(hall, &raizPistas);

    // Liberar memória das salas
    free(hall);
    free(biblioteca);
    free(cozinha);
    free(sotao);
    free(jardim);
    free(porao);

    return 0;
}

    

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 26

/* ======================== STRUCTS ========================= */

typedef struct Pista {
    char texto[100];
    struct Pista *prox;
} Pista;

typedef struct Suspeito {
    char nome[50];
    Pista *listaPistas;
    int contador;
    struct Suspeito *prox; // tratamento de colisão
} Suspeito;

/* ======================== TABELA HASH ========================= */

Suspeito *tabelaHash[TAM_HASH];

/* ======================== FUNÇÃO HASH ========================= */

int funcaoHash(char *nome) {
    if (nome[0] >= 'a' && nome[0] <= 'z')
        return nome[0] - 'a';
    if (nome[0] >= 'A' && nome[0] <= 'Z')
        return nome[0] - 'A';

    return 0;
}

/* ======================== INICIALIZAR ========================= */

void inicializarHash() {
    for (int i = 0; i < TAM_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

/* ======================== PISTA ========================= */

Pista* criarPista(char *texto) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->prox = NULL;
    return nova;
}

/* ======================== SUSPEITO ========================= */

Suspeito* criarSuspeito(char *nome) {
    Suspeito *novo = (Suspeito*) malloc(sizeof(Suspeito));
    strcpy(novo->nome, nome);
    novo->listaPistas = NULL;
    novo->contador = 0;
    novo->prox = NULL;
    return novo;
}

/* ======================== BUSCAR ========================= */

Suspeito* buscarSuspeito(char *nome) {
    int chave = funcaoHash(nome);

    Suspeito *aux = tabelaHash[chave];
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

/* ======================== INSERIR SUSPEITO NA HASH ========================= */

void inserirSuspeitoHash(char *nome) {
    int chave = funcaoHash(nome);

    Suspeito *novo = criarSuspeito(nome);

    if (tabelaHash[chave] == NULL) {
        tabelaHash[chave] = novo;
    } else {
        novo->prox = tabelaHash[chave];
        tabelaHash[chave] = novo;
    }
}

/* ======================== FUNÇÃO PRINCIPAL: INSERIR NA HASH ========================= */

void inserirHash(char *nomeSuspeito, char *textoPista) {
    Suspeito *suspeito = buscarSuspeito(nomeSuspeito);

    // Se não existe, cria
    if (suspeito == NULL) {
        inserirSuspeitoHash(nomeSuspeito);
        suspeito = buscarSuspeito(nomeSuspeito);
    }

    // Cria a pista
    Pista *nova = criarPista(textoPista);

    // Insere no início da lista
    nova->prox = suspeito->listaPistas;
    suspeito->listaPistas = nova;

    suspeito->contador++;
}

/* ======================== LISTAR ========================= */

void listarAssociacoes() {
    printf("\n========== LISTA DE SUSPEITOS ==========\n");

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *s = tabelaHash[i];

        while (s != NULL) {
            printf("\nSuspeito: %s (%d pistas)\n", s->nome, s->contador);

            Pista *p = s->listaPistas;
            while (p != NULL) {
                printf("  • %s\n", p->texto);
                p = p->prox;
            }

            s = s->prox;
        }
    }
}

/* ======================== MAIS PROVÁVEL ========================= */

void suspeitoMaisProvavel() {
    Suspeito *mais = NULL;

    for (int i = 0; i < TAM_HASH; i++) {
        Suspeito *s = tabelaHash[i];

        while (s != NULL) {
            if (mais == NULL || s->contador > mais->contador) {
                mais = s;
            }
            s = s->prox;
        }
    }

    if (mais != NULL) {
        printf("\n=== SUSPEITO MAIS PROVÁVEL ===\n");
        printf("Nome: %s\nPistas: %d\n", mais->nome, mais->contador);
    } else {
        printf("\nNenhum suspeito registrado.\n");
    }
}

/* ======================== MAIN TESTE ========================= */

int main() {

    inicializarHash();

    inserirHash("Carlos", "Foi visto perto do local do crime");
    inserirHash("Ana", "Pegadas encontradas na sala");
    inserirHash("Carlos", "Discussão com a vítima");
    inserirHash("Bruno", "Impressão digital no copo");
    inserirHash("Ana", "Imagem próxima às 22h");
    inserirHash("Carlos", "Motivo financeiro aparente");

    listarAssociacoes();
    suspeitoMaisProvavel();

    return 0;
}
