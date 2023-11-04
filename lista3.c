#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Livro {
    char titulo[100];
    char autor[100];
    struct Livro* proximo;
} Livro;


typedef struct FilaDeLivros {
    Livro* frente;
    Livro* fim;
} FilaDeLivros;


typedef struct PilhaDeLivros {
    Livro* topo;
} PilhaDeLivros;


void inicializaFilaDeLivros(FilaDeLivros* fila) {
    fila->frente = fila->fim = NULL;
}

void insereLivroNaFila(FilaDeLivros* fila, const char* titulo, const char* autor) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->proximo = NULL;

    if (fila->fim == NULL) {
        fila->frente = fila->fim = novoLivro;
    } else {
        fila->fim->proximo = novoLivro;
        fila->fim = novoLivro;
    }
}

Livro* removeLivroDaFila(FilaDeLivros* fila) {
    if (fila->frente == NULL) {
        return NULL;  // Queue is empty
    }

    Livro* livro = fila->frente;
    fila->frente = livro->proximo;

    if (fila->frente == NULL) {
        fila->fim = NULL;
    }

    return livro;
}

void inicializaPilhaDeLivros(PilhaDeLivros* pilha) {
    pilha->topo = NULL;
}

void insereLivroNaPilha(PilhaDeLivros* pilha, const char* titulo, const char* autor) {
    Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->proximo = pilha->topo;
    pilha->topo = novoLivro;
}

Livro* removeLivroDaPilha(PilhaDeLivros* pilha) {
    if (pilha->topo == NULL) {
        return NULL; 
    }

    Livro* livro = pilha->topo;
    pilha->topo = livro->proximo;
    return livro;
}

void exibeFilaDeLivros(FilaDeLivros fila) {
    Livro* livro = fila.frente;
    while (livro != NULL) {
        printf("Livro: %s; Autor: %s\n", livro->titulo, livro->autor);
        livro = livro->proximo;
    }
}

void exibePilhaDeLivros(PilhaDeLivros pilha) {
    Livro* livro = pilha.topo;
    while (livro != NULL) {
        printf("Livro: %s; Autor: %s\n", livro->titulo, livro->autor);
        livro = livro->proximo;
    }
}

void escreveFilaParaArquivo(FilaDeLivros fila, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
        return;
    }

    Livro* livro = fila.frente;
    while (livro != NULL) {
        fprintf(file, "%s;%s\n", livro->titulo, livro->autor);
        livro = livro->proximo;
    }

    fclose(file);
}

void escrevePilhaParaArquivo(PilhaDeLivros pilha, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        printf("Erro na abertura do arquivo %s\n", nomeArquivo);
        return;
    }

    Livro* livro = pilha.topo;
    while (livro != NULL) {
        fprintf(file, "%s;%s\n", livro->titulo, livro->autor);
        livro = livro->proximo;
    }

    fclose(file);
}

int main() {

    FilaDeLivros fila;
    PilhaDeLivros pilha;
    inicializaFilaDeLivros(&fila);
    inicializaPilhaDeLivros(&pilha);

    FILE* filaFile = fopen("fila-de-livros.txt", "r");
    if (filaFile == NULL) {
        printf("Erro na abertura do arquivo fila_de_livros.txt\n");
        return 1;
    }

    char titulo[100];
    char autor[100];
    while (fscanf(filaFile, "%[^;];%[^\n]\n", titulo, autor) != EOF) {
        insereLivroNaFila(&fila, titulo, autor);
    }
    fclose(filaFile);

    FILE* pilhaFile = fopen("pilha-de-livros.txt", "r");
    if (pilhaFile == NULL) {
        printf("Erro na abertura do arquivo pilha-de-livros.txt\n");
        return 1;
    }

    while (fscanf(pilhaFile, "%[^;];%[^\n]\n", titulo, autor) != EOF) {
        insereLivroNaPilha(&pilha, titulo, autor);
    }
    fclose(pilhaFile);

    int escolha;
    char novoTitulo[100];
    char novoAutor[100];
    do {
        printf("\nMenu:\n");
        printf("1. Exibição da fila de livros\n");
        printf("2. Inserção de novos livros na fila\n");
        printf("3. Inserção de novos livros na pilha\n");
        printf("4. Remoção de um livro da fila\n");
        printf("5. Remoção de um livro da pilha\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("\nFila de Livros:\n");
                exibeFilaDeLivros(fila);
                break;

            case 2:
                printf("Digite o título do novo livro (NÃO UTILIZE CARACTERES ESPECIAIS): ");
                fflush(stdin);
                scanf("%[^\n]s",novoTitulo);
                printf(novoTitulo);
                printf("Digite o autor do novo livro (NÃO UTILIZE CARACTERES ESPECIAIS): ");
                fflush(stdin);
                scanf("%[^\n]s",novoAutor);
                insereLivroNaFila(&fila, novoTitulo, novoAutor);
                escreveFilaParaArquivo(fila, "fila-de-livros.txt");
                break;

            case 3: 
                printf("Digite o título do novo livro (NÃO UTILIZE CARACTERES ESPECIAIS): ");
                fflush(stdin);
                scanf(" %[^\n]s", novoTitulo);
                printf("Digite o autor do novo livro (NÃO UTILIZE CARACTERES ESPECIAIS): ");
                fflush(stdin);
                scanf(" %[^\n]s", novoAutor);
                insereLivroNaPilha(&pilha, novoTitulo, novoAutor);
                escrevePilhaParaArquivo(pilha, "pilha-de-livros.txt");
                break;

            case 4: 
                {
                    Livro* livroRemovido = removeLivroDaFila(&fila);
                    if (livroRemovido != NULL) {
                        printf("Livro removido da fila:\n");
                        printf("Título: %s\n", livroRemovido->titulo);
                        printf("Autor: %s\n", livroRemovido->autor);
                        free(livroRemovido);
                        escreveFilaParaArquivo(fila, "fila-de-livros.txt");
                    } else {
                        printf("A fila de livros está vazia.\n");
                    }
                }
                break;

            case 5: 
                {
                    Livro* livroRemovido = removeLivroDaPilha(&pilha);
                    if (livroRemovido != NULL) {
                        printf("Livro removido da pilha:\n");
                        printf("Título: %s\n", livroRemovido->titulo);
                        printf("Autor: %s\n", livroRemovido->autor);
                        free(livroRemovido);
                        escrevePilhaParaArquivo(pilha, "pilha-de-livros.txt");
                    } else {
                        printf("A pilha de livros está vazia.\n");
                    }
                }
                break;

            case 0: 
                break;

            default:
                printf("Escolha inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
