#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE; //Pode ser qualquer tipo de chave

typedef struct aux {
    TIPOCHAVE chave; //chave do tipo TIPOCHAVE que é int
    /*DADOS ARMAZENADOS VÃO AQUI*/
    struct aux *esq, *dir;
} NO;

typedef NO* PONT; //Ponteiro para a estrutura

PONT inicializa(){
    return(NULL);
}

PONT criaNovoNo(TIPOCHAVE ch){

    PONT novoNo = (PONT)malloc(sizeof(NO)); //Aloca um espaço na memória para a estrutura NO
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;

    return(novoNo);

}

PONT adiciona(PONT raiz, PONT no){ //Passa a raiz e o nó com a chave nova

    if(raiz == NULL) return(no); //Se a raiz passada for NULL, retorne o nó passado.

    if(no->chave < raiz->chave){
        raiz->esq = adiciona(raiz->esq, no); //O ponteiro esq irá apontar para o local de memória que está a estrutura no
    } else {
        raiz->dir = adiciona(raiz->dir, no); //idem esq
    }
    //Chaves iguais estão sendo ignoradas:
    return(raiz);
}

PONT busca(TIPOCHAVE ch, PONT raiz){

    if(raiz == NULL) return(NULL);

    if(raiz->chave == ch) return(raiz);

    if(raiz->chave > ch){
        return(busca(ch, raiz->esq));
    } else {
        return(busca(ch, raiz->dir));
    }

}

PONT buscaParaApagarNo(PONT raiz, TIPOCHAVE ch, PONT *pai){

    PONT atual = raiz;
    *pai = NULL;

    while(atual){

        if(atual->chave == ch){
            return(atual);
        }

        *pai = atual;

        if(ch < atual->chave){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }

        return(NULL);
    }

}

PONT removeNo(PONT raiz, TIPOCHAVE ch){

    PONT pai, no, p, q;

    no = buscaParaApagarNo(raiz, ch, &pai);

    if(no == NULL) return(raiz);

    if(!no->esq || !no->dir){
        if(!no->esq){
            q = no->dir;
        } else {
            q = no->esq;
        }
    } else {
        p = no;
        q = no->esq;

        while(q->dir){
            p = q;
            q = no->dir;
        }

        if(p != no){
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }

    if(!pai){
        free(no);
        return(q);
    }

    if (ch < pai->chave){
        pai->esq = q;
    } else {
        pai->dir = q;
    }

    free(no);
    return(raiz);
}

int contagemNos(PONT raiz){

    if(!raiz){
        return 0;
    } else {
        return(
            contagemNos(raiz->esq) + 1 + contagemNos(raiz->dir)
        );
    }

}

void exibirArvore(PONT raiz){

    if(raiz != NULL){

        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");

    }

}

int menu(){

    int op;

    printf("Árvore Binária de Busca\n\n");
    printf("1 - Adicionar dado\n");
    printf("2 - Remover dado\n");
    printf("3 - Visualizar Árvore\n");
    printf("4 - Ver quantidade de itens\n");
    printf("5 - Pesquisar na árvore\n\n");

    printf("Opcao: ");
    scanf("%i", &op);
    
    system("cls");
    return(op);

}

int main(){

    PONT raiz = inicializa();
    PONT no;
    PONT chaveAux;
    int op;

    while(op != 9){
        op = menu();

        switch (op){
            case 1:{
                printf("Chave para adicionar: ");
                scanf("%d", &chaveAux);

                no = criaNovoNo(chaveAux);

                raiz = adiciona(raiz, no);
            } break;

            case 2:{
                printf("Chave para remover: ");
                scanf("%d", &chaveAux);

                removeNo(raiz, chaveAux);
            } break;

            case 3:{
                exibirArvore(raiz);
            } break;

            case 4:{
                printf("%d\n",contagemNos(raiz));
            } break;

            case 5:{
                printf("Chave para buscar: ");
                scanf("%i", &chaveAux);
            } break;

            default:
                break;
        }
     //O ponteiro raiz está apontando para NULL

     //O ponteiro no está apontando para a estrutura que foi criada no método

     /*Passa a raiz e o endereço da memória que o no
    está apontando, ou seja, a estrutura criada*/
    }
    //PONT pesquisa = busca(23, raiz); //Passa a chave e o ponteiro para a raiz



}
