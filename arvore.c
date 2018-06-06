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

bool busca(TIPOCHAVE ch, PONT raiz){

    if(raiz == NULL) return(NULL);

    if(raiz->chave == ch) return(true);

    if(raiz->chave > ch){
        return(busca(ch, raiz->esq));
    } else {
        return(busca(ch, raiz->dir));
    }

}

PONT buscaParaApagarNo(PONT raiz, TIPOCHAVE ch, PONT *pai){

    PONT atual = raiz; //Atual é um ponteiro para a raiz passada
    *pai = NULL; //O valor do ponteiro pai receberá NULL

    while(atual){ //Enquanto o atual for válido

        if(atual->chave == ch){ //Se achar a chave, ela será retornada
            return(atual);
        }

        *pai = atual; //O valor onde o ponteiro pai está apontando recebe atual

        if(ch < atual->chave){ //Se a chave for menor que a chave do atual
            atual = atual->esq; //navega para a esquerda
        } else {
            atual = atual->dir;
        }
    } //Neste ponto, o valor do ponteiro pai será o valor que está acima do ponteiro atual, que será o que será retornado
        return(NULL);

}

PONT removeNo(PONT raiz, TIPOCHAVE ch){

    PONT pai, no, p, q;

    no = buscaParaApagarNo(raiz, ch, &pai); //no será o valor a ser apagado

    if(no == NULL) return(raiz); //se no for NULL, será retornada a raiz

    if(!no->esq || !no->dir){ //se não houver ou esquerda ou direita como filho de no...
        if(!no->esq){ //se não houver esquerda
            q = no->dir; //q receberá o valor da direita do no
        } else { //se não houver direita
            q = no->esq; //q receberá o valor da esquerda do no
        }
    } else { //Caso haja direita e esquerda como filho de no
        p = no; //p receberá no
        q = no->esq; //q receberá o valor a esquerda do no e será a chave q irá substituir a excluida

        while(q->dir){ //PARA IDENTIFICAR O VALOR MAIS A ESQUERDA DA SUBARVORE DA DIREITA
            p = q;
            q = p->dir;
        }

        if(p != no){ //se o p não for o no
            p->dir = q->esq; //
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }

    if(!pai){ //Se não houver pai é porque o no é a raiz
        free(no); //ele será eliminado
        return(q); //o valor de q tomará seu lugar
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

    printf("Arvore Binaria de Busca\n\n");
    printf("1 - Adicionar dado\n");
    printf("2 - Remover dado\n");
    printf("3 - Visualizar Arvore\n");
    printf("4 - Ver quantidade de itens\n");
    printf("5 - Pesquisar na Arvore\n\n");

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
                system("cls");
            } break;

            case 2:{
                printf("Chave para remover: ");
                scanf("%d", &chaveAux);

                removeNo(raiz, chaveAux);
                system("cls");
            } break;

            case 3:{
                exibirArvore(raiz);
                printf("\n");
                system("pause");
                system("cls");
            } break;

            case 4:{
                printf("%d\n",contagemNos(raiz));
                system("pause");
                system("cls");
            } break;

            case 5:{
                printf("Chave para buscar: ");
                scanf("%i", &chaveAux);

                bool achou = busca(chaveAux, raiz);

                if(achou == true){
                    printf("Achou\n");
                } else {
                    printf("Nao achou\n");
                }
                system("pause");
                system("cls");
            } break;

            default:
                break;
        }

    }
}
