#define MAXQUEUE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue{
    int nitems;
    float *dados;
    int capacidade,primeiro,ultimo;
};

int emptyQueue(struct queue *ps)//retorna verdadeiro quando a fila está vazia
{
    return (ps->nitems==0);
}
int fullQueue(struct queue *ps)
{
    return (ps->nitems== ps->capacidade);
}
void createQueue(struct queue *ps,int c){
    ps->capacidade = c;
    ps->dados = (float *) malloc(ps->capacidade * sizeof(float));
    ps->nitems = 0;
    ps->primeiro = 0;
    ps->ultimo = -1;
}

void inserir(struct queue *ps, int x){

    if (ps -> ultimo == ps -> capacidade-1)
    {
        ps -> ultimo = -1;
    }
    ps->ultimo++;
    ps->dados[ps->ultimo] = x; //Soma ao ultimo e insere
    ps->nitems++;//mais um item
}
int popQueue(struct queue *ps){
    int temp = ps->dados[ps->primeiro++];

    if(ps->primeiro == ps -> capacidade)
    {
        ps->primeiro = 0;
    }

    ps -> nitems--;
    return temp;
}

void showQueue(struct queue *ps){
    int cont,i;
    for (cont =0,i = ps->primeiro;cont < ps->nitems;cont++){
        printf("%.2f\t",ps->dados[i++]);
        if (i==ps->capacidade)
            i = 0;
    }
}
void main(){
    int opcaoc,capa;
    float valor;
    struct queue fila;

    printf("Qual o tamanho da fila?");
    scanf("%d",&capa);
    createQueue(&fila,capa);

    while (1)
    {
        printf("1 - Inserir\n");
        printf("2 - Pop Queues\n");
        printf("3 - Show Queues\n");
        printf("0 - OUT\n");
        printf("Opcao: ");
        scanf("%d",&opcaoc);
        switch(opcaoc){
            case 1:
                if(fullQueue(&fila)){
                    printf("Erro: fila está cheia\n");
                }
                else{      
                    printf("Digite um valor: ");
                    scanf("%f",&valor);
                    inserir(&fila,valor);
                }
                break;

            case 2:
                if (emptyQueue(&fila))
                {
                    printf("Erro: fila está vazia\n");
                }
                else{
                    valor = popQueue(&fila);
                    printf("%1f Removido com sucesso\n",valor);
                }
                break;

            case 3:
                if (emptyQueue(&fila))
                {
                    printf("Erro: fila está vazia\n");
                }
                else{
                    printf("Conteudo da fila => ");
                    showQueue(&fila);
                }
                printf("\n");
                break;
            default:
                printf("Opcao invalida");
        }
    }
    
}
