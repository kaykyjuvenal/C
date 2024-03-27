#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct musica
{
    int id;
    char titulo[200];
    int id_artista;
    int duracao; // segundos
} musica;

typedef struct artista
{
    int id;
    char nome[200];
    char genero[200];
} artista;

typedef struct musica_no
{
    musica *musica;
    int altura;
    struct musica_no *esq;
    struct musica_no *dir;
} musica_no;

typedef struct artista_no
{
    artista *artista;
    struct artista_no *prox;
} artista_no;
typedef struct playlist_no{
    musica *musica;
    struct playlist_no *prox;
} playlist_no;
typedef struct Listaplaylists_no{
    int id;
    char nome[200];
    playlist_no *musicas;
    struct Listaplaylists_no *prox ;
} Listaplaylists_no;
typedef struct musica_no* ArvAVL;

ArvAVL * cria_ArvoreAVLMusica(){
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz; 
}
int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}
int altura_NO(struct musica_no * no){
    if (no == NULL)
    {
        return -1;
    }
    else{
        return no->altura;
    }
    
}
int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
    {
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
    {
        return (alt_esq +1);
    }else{
        return(alt_dir +1);
    }
    
}
int fatorBalanceamento_musicano(struct musica_no* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}
void RotacaoLL(ArvAVL *A){//LL
    printf("RotacaoLL\n");
    struct musica_no *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}
void RotacaoRR(ArvAVL *A){//RR
    printf("RotacaoRR\n");
    struct musica_no *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}
void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}
void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

void cadastraArtista(artista_no *inicio, int idRecebido){
    artista *Novo_Artista;
    Novo_Artista = malloc(sizeof(musica));
    Novo_Artista->id=idRecebido;

    printf("\n-----OPCAO CADASTRA SELECIONADA!-----\n");

    printf("Informe o Nome do Artista: \n");
    scanf("%s",Novo_Artista->nome);
    fflush(stdin);

    printf("Digite o Genero do Artista: \n");
    scanf("%s",&(Novo_Artista->genero));
    fflush(stdin);

    artista_no *Artista_lista;
    Artista_lista = malloc(sizeof(musica_no));
    Artista_lista ->artista = Novo_Artista;

    if(inicio->prox==NULL){
        inicio->prox=Artista_lista;
        Artista_lista->prox=NULL;
    }
    else{
        Artista_lista ->prox=inicio->prox;
        inicio->prox=Artista_lista ;
    }
}
void imprimeListaArtista(artista_no *ini){
    artista_no *leitura;
    leitura = ini->prox;
    printf("\nIMPRIMINDO A LISTA...");
    while(leitura){
        printf("\n------------------------------------------------");
        printf("\n ID     : %d \t ",leitura->artista->id);
        printf("\n Nome : %s \t ",leitura->artista->nome);
        printf("\nGenero: %s \t ",leitura->artista->genero);
        printf("\n------------------------------------------------");

        leitura = leitura->prox;
    }
}

int cadastraMusica(ArvAVL*raiz, int idArtist,int idRecebido){
    int res;
    if(*raiz == NULL){
        musica *Nova_musica;

        Nova_musica = malloc(sizeof(musica));
        Nova_musica->id=idRecebido;
        printf("\n-----OPCAO CADASTRA SELECIONADA!-----");

        printf("\nInforme o Titulo: ");
        scanf("%s",Nova_musica->titulo);
        fflush(stdin);

        Nova_musica->id_artista = idArtist;

        printf("Informe a duracao em segundos: ");
        scanf("%d",&(Nova_musica->duracao));
        fflush(stdin);
        musica_no *Musica_lista;
        Musica_lista = malloc(sizeof(musica_no));
        if(Musica_lista == NULL){
            return 0;
        }
        Musica_lista->musica = Nova_musica;
        Musica_lista->altura = 0;
        Musica_lista->esq = NULL;
        Musica_lista->dir = NULL;
        *raiz = Musica_lista;
        return 1;
    }

    struct musica_no * atual = *raiz;
    if (idRecebido < atual->musica->id)
    {
       if((res = cadastraMusica(&(atual->esq),idArtist, idRecebido)) == 1) {
            if(fatorBalanceamento_musicano(atual) >= 2){
                if (idRecebido < (*raiz)->esq->musica->id)
                {
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }               
            }
        }
    }else{
        if(idRecebido > atual->musica->id){
            if((res = cadastraMusica(&(atual->dir),idArtist, idRecebido)) ==1) {
                if(fatorBalanceamento_musicano(atual) >= 2){
                    if ((*raiz)->dir->musica->id < idRecebido)
                    {
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }               
                }
            }
        }else{
            printf("Valor Duplicado!\n");
            return 0;
        }
    }
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) +1;
    return res;
}


void imprimeListaMusica(ArvAVL *raiz){
    printf("\nIMPRIMINDO A LISTA...\n");
    if(raiz == NULL){
        return;
    }
    if(*raiz!= NULL){
        int hora,minuto,segundo;
        imprimeListaMusica(&((*raiz)->esq));
        imprimeListaMusica(&((*raiz)->dir));
        hora = (*raiz)->musica->duracao / 3600;
        minuto = ((*raiz)->musica->duracao % 3600)/60;
        segundo = ((*raiz)->musica->duracao % 3600) %60;
        printf("Impressão: \n");
        printf("Musica numero: %d\n", (*raiz)->musica->id);
        printf("Título: %s\n", (*raiz)->musica->titulo);
        printf("Id do Artista: %d\n", (*raiz)->musica->id_artista);
        printf("Duração: %d Horas , %d Minutos, %d Segundos.\n", hora,minuto,segundo);
    }
}
struct musica_no * procuraMenor(struct musica_no *atual){
    struct musica_no *no1 = atual;
    struct musica_no *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
int removeMusicaLista(ArvAVL *raiz,int idRecebido){
    imprimeListaMusica(raiz);
    int IdEscolhido;
    printf("Informe o id que deseja remover: \n");
    scanf("%d",&IdEscolhido);
    fflush(stdin);
    if(*raiz == NULL){
        printf("Valor inexistente.\n");
        return 0;
    }
    int res;
    if(IdEscolhido < (*raiz)->musica->id){
        if((res = removeMusicaLista(&(*raiz)->esq,IdEscolhido)) == 1){
            if (fatorBalanceamento_musicano(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                {
                    RotacaoRR(raiz);
                }
                else{
                    RotacaoRL(raiz);
                }
            }
        }
    }
    if ((*raiz)->musica->id <IdEscolhido)
    {
        if(res = removeMusicaLista(&(*raiz)->dir,IdEscolhido)){
            if (fatorBalanceamento_musicano(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }
    
    if ((*raiz)->musica->id == IdEscolhido){
        if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
            struct musica_no *old_no = (*raiz);
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            }
            else{
                *raiz =  (*raiz)->dir;
            }
            free(old_no);
        }else{
            struct musica_no *temp = procuraMenor((*raiz)->dir);
            (*raiz)->musica->id = temp->musica->id;
            removeMusicaLista(&(*raiz)->dir, (*raiz)->musica->id);
            if (fatorBalanceamento_musicano(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esq->dir)<= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }   
        }
        if (*raiz != NULL)
            (*raiz) ->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) +1;
        return 1;
    }
    (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) +1;

    return res;
}

void removeArtista(artista_no *Listaartista, ArvAVL *raiz){
    imprimeListaArtista(Listaartista);
    int idescolhido;
    printf("\n Informe o ID do artista que vai ser removido: \n");
    scanf("%d",&idescolhido);
    fflush(stdin);
    artista_no * leituraArtista;
    
    leituraArtista = Listaartista->prox;
    while(leituraArtista){
        if(leituraArtista->artista->id == idescolhido){
            if (leituraArtista->prox == NULL)
            {
                Listaartista->prox=NULL;
                Listaartista->artista=NULL;
                removeMusicaLista(raiz,idescolhido);
            }
            
        }
        leituraArtista = leituraArtista->prox;
    }
    printf("Artistas Deletados.\n");
    printf("Musicas Deletadas.\n");
}

playlist_no *criarPlayList(ArvAVL *raiz, Listaplaylists_no *minhasPlayList){// SO CADASTRA UMA MUSICA

    playlist_no *InicPlayList;
    InicPlayList = malloc(sizeof(playlist_no));
    InicPlayList->prox=NULL;
    InicPlayList->musica=NULL;

    int Quantidade_Musicas=0;
    printf("\nQuantas musicas deseja adcionar: ");
    scanf("%d",&Quantidade_Musicas);
    fflush(stdin);

    int idMusica;
    for (int i=0; i < Quantidade_Musicas; i++) {
        printf("\nInforme o id da musica %d : ",i+1);
        scanf("%d",&idMusica);
        fflush(stdin);

        playlist_no *NovaPlayList;
        NovaPlayList = malloc(sizeof(playlist_no));
        while(raiz){
            if((*raiz)->musica->id==idMusica){
                NovaPlayList->musica=(*raiz)->musica;
                printf("\n--------------------------------- \n");
                printf("\nAdicionando musica a playlist...  \n");
                printf("\n--------------------------------- \n");
                if(InicPlayList->prox==NULL){
                    InicPlayList->prox=NovaPlayList;
                    NovaPlayList->prox=NULL;
                } else {
                    NovaPlayList->prox=InicPlayList->prox;
                    InicPlayList->prox=NovaPlayList;
                }
                break;
            }else{
                printf("Id Inexistente.\n");
                break;
            }
        }
    }
    minhasPlayList->musicas=InicPlayList;
    printf("\n-----------PLAYLIST CRIADA COM SUCESSO!!---------- \n");
    return InicPlayList;
}

void ImprimirPlayList(Listaplaylists_no *minhasPlayList){
    Listaplaylists_no *leitura;
    leitura = minhasPlayList->prox;
    while(leitura){
        printf("\n\nPlaylist: %s",leitura->nome);
        printf("\nID Da Playlist = %d",leitura->id);
        leitura = leitura->prox;
    }
    printf("\n\nEscolha o id que voce deseja imprimir: ");
    int idPlaylistEscolhida;
    scanf("%d",&idPlaylistEscolhida);
    fflush(stdin);

    leitura = minhasPlayList->prox;
    while(leitura){
        if(leitura->id==idPlaylistEscolhida){
            playlist_no *leituraPlayList;
            leituraPlayList = leitura->musicas->prox;
            printf("\n======= MUSICA DA PLAYLIST %s =======",leitura->nome);
            int h,m,s;
            while(leituraPlayList){
                h = (leituraPlayList->musica->duracao / 3600);
                m = (leituraPlayList->musica->duracao % 3600) / 60;
                s = (leituraPlayList->musica->duracao % 3600) % 60;
                printf("\n\nID da musica: %d",leituraPlayList->musica->id);
                printf("\n========================");
                printf("\nNome : %s",leituraPlayList->musica->titulo);
                printf("\nID Artista : %d",leituraPlayList->musica->id_artista);
                printf("\nA duracao e de : %d Horas %d Minutos e %d Segundos", h, m, s);
                leituraPlayList=leituraPlayList->prox;
                printf("\n========================");
            }
            printf("\n===================================\n");
        }
        leitura = leitura->prox;
    }
}

void RemoveMusicaPlayList(Listaplaylists_no *minhasPlayList){

    ImprimirPlayList(minhasPlayList);

    printf("Digite novamente o id que vai ser deletado: \n");
    int id;
    scanf("%d",&id);
    fflush(stdin);

    int encontrou = 0;
    Listaplaylists_no *leitura;
    leitura = minhasPlayList->prox;

    while(leitura){
        if(leitura->id==id){
            encontrou++;
            playlist_no *leituraPlayList;
            leituraPlayList = leitura->musicas;
            leituraPlayList =  leituraPlayList->prox;

            //playlist escolhida
            printf("\nPLAYLIST ENCONTRADA!: \n\n");
            while(leituraPlayList){
                printf("\n==============================");
                printf("\nID : %d",leituraPlayList->musica->id);
                printf("\nTitulo : %s",leituraPlayList->musica->titulo);
                printf("\nId do Artista : %d",leituraPlayList->musica->id_artista);
                printf("\n==============================");
                leituraPlayList = leituraPlayList->prox;
            }
            printf("\n\nDigite o id da musica que vai ser deletada: ");
            int Id_deletar;
            scanf("%d",&Id_deletar);
            fflush(stdin);

            leituraPlayList = leitura->musicas;
            leituraPlayList =  leituraPlayList->prox;
            //a musica anterior liga a anterior ao próximo da que será deletada
            playlist_no *PlayListAnterior;
            PlayListAnterior= leitura->musicas;
            while(leituraPlayList){
                if(leituraPlayList->musica->id==Id_deletar){
                    PlayListAnterior->prox=leituraPlayList->prox;
                    free(leituraPlayList->musica);
                    printf("\n Musica deletada com sucesso ");
                }
                leituraPlayList = leituraPlayList->prox;
                PlayListAnterior = PlayListAnterior->prox;
            }
        }
        leitura = leitura->prox;
    }
    if(encontrou==0){
        printf("Não existe playlist com esse ID");
    }
}

void menu(){
    printf("\n\n ####### MENU DE MUSICAS #######");
    printf("\n ===========ESCOLHA UMA OPCAO============");
    printf("\n [1]- Inserir Musica na lista            ");
    printf("\n [2]- Imprima a lista muisca             ");
    printf("\n [3]- Remover uma musica da lista        ");
    printf("\n [4]- Criar Playlist                     ");
    printf("\n [5]- Imprimir Playlist                  ");
    printf("\n [6]- Remover musica da playlist"         );
    printf("\n [7]- Cadastrar Artista                  ");
    printf("\n [8]- Imprimir Artistas                  ");
    printf("\n [9]- Apagar um artista e suas musicas   ");
    printf("\n [0]- Digite 0 para sair                 ");
}

int main() {
    //lista inicial de musicas
    ArvAVL * avl;
    avl = cria_ArvoreAVLMusica();
    

    //lista inicial de artistas
    artista_no * listaArtista;
    listaArtista = malloc(sizeof(artista_no));
    listaArtista->prox = NULL;
    listaArtista->artista = NULL;

    //listas de playlist
    int idListasPlaylist=0;

    Listaplaylists_no *minhasPlayList;
    minhasPlayList = malloc(sizeof(Listaplaylists_no));
    minhasPlayList->musicas=NULL;
    minhasPlayList->prox=NULL;
    strcpy(minhasPlayList->nome,"MINHA LISTA DE PLAYLIST");
    minhasPlayList->id=1;

    int idArtista;
    int idartista;
    int idmusica= 0;
    int opcao=-1;
    while(opcao!=0){
        menu();
        printf("\nESCOLHA UMA OPCAO: ");
        scanf("%d",&opcao);
        fflush(stdin);
        int res;

        if (opcao==1) {
            idmusica++;
            printf("Inserindo nova musica: ");
            printf("Digite um id para o artista: ");
            scanf("%d",&idArtista);
            res = cadastraMusica(avl,idArtista,idmusica);
            imprimeListaMusica(avl);
        }
        else if(opcao==2){
            imprimeListaMusica(avl);
        }
        else if (opcao==3) {
            int idMusicaDeletada;
            printf("Qual o id da musica: ");
            scanf("%d",&idMusicaDeletada);
            removeMusicaLista(avl,idMusicaDeletada);
        }
        else if (opcao==4) {
            Listaplaylists_no *Novo_lplaylist;
            Novo_lplaylist = malloc(sizeof(Listaplaylists_no ));
            idListasPlaylist++;
            Novo_lplaylist->id=idListasPlaylist;

            printf("\nCRIANDO PLAYLIST...");
            char nome[100];
            printf("\nDigite um nome para a playlist: ");
            scanf("%s",nome);
            fflush(stdin);
            strcpy(Novo_lplaylist->nome,nome);

            criarPlayList(avl,Novo_lplaylist);

            if(minhasPlayList->prox == NULL){
                minhasPlayList->prox = Novo_lplaylist;
                Novo_lplaylist->prox = NULL;
                printf("\nA primeira lista foi criada.");
                printf("\n############################# ");
            } else {
                Novo_lplaylist->prox = minhasPlayList->prox;
                minhasPlayList->prox = Novo_lplaylist;
                printf("\nProxima Lista foi criada ");
            }
        }
        else if (opcao==5) {
            ImprimirPlayList(minhasPlayList);
        }
        else if (opcao==6){
            RemoveMusicaPlayList(minhasPlayList);
        }
        else if (opcao==7){
            idartista++;
            cadastraArtista(listaArtista,idartista);
        }
        else if (opcao==8){
            imprimeListaArtista(listaArtista);
        }
        else if(opcao==9){
            removeArtista(listaArtista,avl);
        }
    }
return 0;
}
