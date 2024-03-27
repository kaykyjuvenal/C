#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhoap2.h"//arquivo na mesma pasta ""

int comparaAlunos(aluno a1, aluno a2, int criterio){
    char nomecomp1[TAMNOME+TAMSOBRENOME];
    char nomecomp2[TAMNOME+TAMSOBRENOME];
    char nome1[TAMNOME];
    char nome2[TAMNOME];
    char sobrenome1[TAMSOBRENOME];
    char sobrenome2[TAMSOBRENOME];
    char curso1[4];
    char curso2[4];
    data datanascimento1;
    data datanascimento2;
    int total1;
    int total2;
    int resultado;
    switch(criterio) {
        case 1://prontuario
            return a1.prontuario - a2.prontuario;
        case 2://nome e sobrenome
            strcpy(nomecomp1, a1.nome);
            strcat(nomecomp1, a1.sobrenome);
            strcpy(nomecomp2, a2.nome);
            strcat(nomecomp2, a2.sobrenome);
            return strcmp(nomecomp1,nomecomp2);
        case 3://nome
            strcpy(nome1, a1.nome);
            strcpy(nome2, a2.nome);
            return strcmp(nome1,nome2);
        case 4://Sobrenome
            strcpy(sobrenome1, a1.sobrenome);
            strcpy(sobrenome2, a2.nome);
            return strcmp(sobrenome1,sobrenome2);
        case 5://curso
            strcpy(curso1,a1.curso);
            strcpy(curso2,a2.curso);
            return strcmp(curso1,curso2);
        case 6://data
            datanascimento1.dia = a1.datanascimento.dia;
            datanascimento1.mes = a1.datanascimento.mes;
            datanascimento1.ano = a1.datanascimento.ano;
            datanascimento2.dia = a2.datanascimento.dia;
            datanascimento2.mes = a2.datanascimento.mes;
            datanascimento2.ano = a2.datanascimento.ano;
            total1 = datanascimento1.ano * 10000 + datanascimento1.mes * 100 + datanascimento1.dia;
            total2 = datanascimento2.ano * 10000 + datanascimento2.mes * 100 + datanascimento2.dia;
            resultado = total1 - total2; 
            return resultado;
    }
}

void limpaBuffer()
{
    while (getchar() != '\n');
}
void cadastrarData(aluno * vetorAlunos, int *posicao){
    int diaNascimento = 0;
    int mesNascimento = 0;
    int anoNascimento = 0;

    while(1 > diaNascimento || diaNascimento > 31){
        printf("Digite o dia da data de nascimento do aluno: ");
        scanf("%d", &diaNascimento);
        limpaBuffer();
        if (1 > diaNascimento || diaNascimento > 31){
        printf("dia invalido: %d, digite outra data.", diaNascimento);
        }else{
            vetorAlunos[*posicao].datanascimento.dia = diaNascimento; 
            printf("cadastrado com sucesso\n");
        }
    }
    while(mesNascimento > 12 || mesNascimento < 1){
        printf("Digite o mes da data de nascimento do aluno: ");
        scanf("%d", &mesNascimento);
        limpaBuffer();
        if (mesNascimento > 12 || mesNascimento < 1 ){//ou � ||
            printf("O Mes digitado e invalido - %d", mesNascimento);
        }else{
            vetorAlunos[*posicao].datanascimento.mes = mesNascimento; 
            printf("cadastrado com sucesso\n");
            
        }
    }
    while(anoNascimento < 1900 ||  anoNascimento >2022){
        printf("digite o ano de nascimento do aluno: ");
        scanf("%d", &anoNascimento);
        limpaBuffer();
        if ( anoNascimento < 1900 || anoNascimento > 2022){
            printf("Esta ano  e invalido- %d",  anoNascimento);
        }else{
            vetorAlunos[*posicao].datanascimento.ano = anoNascimento ;
            
        }
    }    
    printf("A data foi cadastrada com sucesso - %d/%d/%d\n", diaNascimento, mesNascimento, anoNascimento); 
}
void cadastrarAluno(aluno *vetorAlunos, int *posicao){
    printf("Digite o prontuario do aluno: ");
    scanf("%d", &vetorAlunos[*posicao].prontuario);
    limpaBuffer();
    printf("Digite o nome do aluno:");
    scanf("%s", vetorAlunos[*posicao].nome);
    limpaBuffer();                                  
    printf("Digite o sobrenome do aluno:");
    scanf("%s", vetorAlunos[*posicao].sobrenome);
    limpaBuffer();
    cadastrarData(vetorAlunos, posicao);
    printf("Digite o curso do aluno: ");
    scanf("%s", vetorAlunos[*posicao].curso);
    limpaBuffer();
    (*posicao)++;
    printf("Concluido com sucesso.");
}

void salvaArquivo(aluno *vetorAlunos, int nAlunos)
{
    FILE *arquivo;
    int i, result;

    arquivo = fopen("alunos.dat", "wb");
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return;
    }
    for (i = 0; i < nAlunos; i++)
    {
        result = fwrite(&vetorAlunos[i], sizeof(aluno), 1, arquivo);
        if (result != 1)
        {
            printf("Erro de escrita no arquivo. \n");
        }
    }
    fclose(arquivo);
}

int lerArquivo(aluno *vetorAlunos)
{
    FILE *arquivo;
    int i, result;
    arquivo = fopen("alunos.dat", "rb");
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return -1;
    }
    for (i = 0; i<MAXALUNOS; i++) {
        result = fread(&vetorAlunos[i], sizeof(aluno), 1, arquivo);
        if (result != 1) {
            if (feof(arquivo)) {
                return i;
            } else {
                printf("Erro na leitura do arquivo.\n");
                return -1;
            }
        }
    }
}
int getMenu() {
    int i;
    printf ("===MENU===\n0 - Sair\n1 - Cadastrar Dados\n2 - Imprimir Dados \n3 - Salvar Arquivo\n4 - Carregar Arquivo \n5 - Busca Especifica\n6 - Remover item por busca\n7 - Ordenacao\nDigite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}

void imprimeAlunos(aluno *vetorAlunos, int nAlunos) {
    int i;
    for (i=0; i<nAlunos; i++) {
        printf("Prontuario: %d\n", vetorAlunos[i].prontuario);
        printf("Nome do aluno: %s\n", vetorAlunos[i].nome);
        printf("Sobrenome do aluno: %s\n", vetorAlunos[i].sobrenome);
        printf("Curso: %s\n", vetorAlunos[i].curso);
        printf("Data De nascimento: %d/%d/%d\n", vetorAlunos[i].datanascimento.dia,vetorAlunos[i].datanascimento.mes,vetorAlunos[i].datanascimento.ano);
    }
}
void imprimeAluno(aluno *vetorAlunos,int i)
{
        printf("Prontuario: %d\n", vetorAlunos[i].prontuario);
        printf("Nome do aluno: %s\n", vetorAlunos[i].nome);
        printf("Sobrenome do aluno: %s\n", vetorAlunos[i].sobrenome);
        printf("Curso: %s\n", vetorAlunos[i].curso);
        printf("Data De nascimento: %d/%d/%d\n", vetorAlunos[i].datanascimento.dia,vetorAlunos[i].datanascimento.mes,vetorAlunos[i].datanascimento.ano);
}
void buscaEspecificaPorNome(aluno *vetorAlunos, int nAlunos, char *procurado)
{
    int i;
    for(i = 0; i < nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].nome) == 0)
        {
            imprimeAluno(&vetorAlunos[i], i);
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorNomeap(aluno *vetorAlunos, int *nAlunos, char *procurado)
{
    int i;
    int j;
    for(i = 0; i < *nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].nome) == 0)
        {
            for(j=i; j< *nAlunos; j++)
            {
                vetorAlunos[j]= vetorAlunos[j+1];
            }
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorSobrenome(aluno *vetorAlunos, int nAlunos, char *procurado)
{
    int i;
    for(i = 0; i < nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].sobrenome) == 0)
        {
            imprimeAluno(&vetorAlunos[i],i);
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorSobrenomeap(aluno *vetorAlunos, int *nAlunos, char *procurado)
{
    int i;
    int j;
    for(i = 0; i < *nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].sobrenome) == 0)
        {
            for(j=i; j< *nAlunos; j++)
                vetorAlunos[j]= vetorAlunos[j+1];;
        }
        
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaCurso(aluno *vetorAlunos, int nAlunos, char *procurado)
{
    int i;
    for(i = 0; i < nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].curso) == 0)
        {
            imprimeAluno(&vetorAlunos[i], i);
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaCursoap(aluno *vetorAlunos, int *nAlunos, char *procurado)
{
    int i;
    int j;

    for(i = 0; i < *nAlunos; i++)
    {
        if(strcmp(procurado, vetorAlunos[i].curso) == 0)
        {
            for(j=i; j< *nAlunos; j++)
            {
                vetorAlunos[j]= vetorAlunos[j+1];
            }
            (*nAlunos)--;
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorNomeeSobrenome(aluno *vetorAlunos, int nAlunos, char *procurado1, char *procurado2)
{
    int i;
    
    for(i = 0; i < nAlunos; i++)
    {
        if(strcmp(procurado1, vetorAlunos[i].nome) == 0)
        {
            if (strcmp(procurado2, vetorAlunos[i].sobrenome) == 0)
            {
                imprimeAluno(&vetorAlunos[i], i);
            }
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorNomeeSobrenomeap(aluno *vetorAlunos, int *nAlunos, char *procurado1, char *procurado2)
{
    int i;
    int j;

    for(i = 0; i < *nAlunos; i++)
    {
        if(strcmp(procurado1, vetorAlunos[i].nome) == 0)
        {
            if (strcmp(procurado2, vetorAlunos[i].sobrenome) == 0)
            {
                for(j=i; j< *nAlunos; j++){
                vetorAlunos[j]= vetorAlunos[j+1];
                }
            }
            (*nAlunos)--;
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorProntuario(aluno *vetorAlunos, int nAlunos, int procurado)
{
    int i;
    for ( i = 0; i < nAlunos; i++)
    {
        if (procurado == vetorAlunos[i].prontuario)
        {
            imprimeAluno(&vetorAlunos[i], i);
        }
        
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorProntuarioap(aluno *vetorAlunos, int *nAlunos, int procurado)
{
    int i;
    int j;
    for ( i = 0; i < *nAlunos; i++)
    {
        if (procurado == vetorAlunos[i].prontuario)
        {
            for(j=i; j< *nAlunos; j++)
            {
                vetorAlunos[j]= vetorAlunos[j+1];
            }
            (*nAlunos)--;
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorData(aluno *vetorAlunos, int nAlunos, data procurado)
{
    int i;
    for (i = 0; i< nAlunos; i++)
    {
        if (procurado.dia  == vetorAlunos[i].datanascimento.dia)
        {   
            if (procurado.mes == vetorAlunos[i].datanascimento.mes)
            {
                if (procurado.ano == vetorAlunos[i].datanascimento.ano)
                {
                    imprimeAluno(&vetorAlunos[i], i);
                }
            }
        }
    }
    printf("Concluido com sucesso.\n");
}
void buscaEspecificaPorDataap(aluno *vetorAlunos, int *nAlunos, data procurado)
{
    int i;
    int j;
    for (i = 0; i< *nAlunos; i++)
    {
        if (procurado.dia  == vetorAlunos[i].datanascimento.dia)
        {
            if (procurado.mes == vetorAlunos[i].datanascimento.mes)
            {
                if (procurado.ano == vetorAlunos[i].datanascimento.ano)
                {
                    for(j=i; j< *nAlunos; j++)
                    {
                        vetorAlunos[j]= vetorAlunos[j+1];
                        printf("Concluido com sucesso.\n");
                    }
                    (*nAlunos)--;
                }
            }
        }
    }
    printf("Concluido com sucesso.\n");
}
void apagarAluno(aluno *vetorAlunos, int nAlunos, int procurado){
    int i;
    int j;

    for ( i = 0; i < nAlunos; i++)
    {
        if (procurado == vetorAlunos[i].prontuario)
        {
            for(j=i; j< (nAlunos-1); j++)
            vetorAlunos[j]= vetorAlunos[j+1];
        }
        
    }
    printf("Concluido com sucesso.\n");
}
int getMenu2() {
    int i;
    printf ("===Menu De Busca: ===\n0 - Sair \n1 - Nome e Sobrenome\n2 - Nome\n3 - Sobrenome \n4 - Curso\n5 - Data de nascimento \n6- Prontuario\n Digite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}
void menubuscas(aluno *alunos,int numAlunos){
    int menubusca;
    int prontuarioc;
    data datanascimentoc;
    char nomec[TAMNOME];
    char sobrenomec[TAMSOBRENOME];
    char cursoc[4];
    do {
        menubusca = getMenu2();
        switch(menubusca){
            case 1: printf("Digite um nome: ");
                    scanf("%s", nomec);
                    printf("Digite um sobrenome: ");
                    scanf("%s", sobrenomec);
                    buscaEspecificaPorNomeeSobrenome(alunos,numAlunos,nomec,sobrenomec);
                    break;
            case 2: printf("Digite o nome a ser prcurado: ");
                    scanf("%s", nomec);
                    buscaEspecificaPorNome(alunos,numAlunos,nomec);
                    break;
            case 3: printf("Digite o sobrenome: ");
                    scanf("%s", sobrenomec);
                    buscaEspecificaPorSobrenome(alunos,numAlunos,sobrenomec);
                    break;
            case 4: printf("Digite o curso: ");
                    scanf("%s",cursoc);
                    buscaEspecificaCurso(alunos,numAlunos,cursoc);
                    break;
            case 5: printf("Digite o dia da data de nascimento: ");
                    scanf("%d",&datanascimentoc.dia);
                    printf("Digite o mes da data de nascimento: ");
                    scanf("%d",&datanascimentoc.mes);
                    printf("Digite o ano da data de nascimento: ");
                    scanf("%d",&datanascimentoc.ano);
                    buscaEspecificaPorData(alunos,numAlunos,datanascimentoc);
                    break;
            case 6: printf("Digite o prontuario: ");
                    scanf("%d", &prontuarioc);
                    buscaEspecificaPorProntuario(alunos,numAlunos,prontuarioc);
                    break;
            } 
    }while (menubusca != 0);
}
void menubuscas1(aluno *alunos,int *numAlunos){
    int menubusca1;
    int prontuariod;
    data datanascimentod;
    char nomed[TAMNOME];
    char sobrenomed[TAMSOBRENOME];
    char cursod[4];
    menubusca1 = getMenu2();
    switch(menubusca1){
        case 1: printf("Digite um nome: ");
                scanf("%s", nomed);
                printf("Digite um sobrenome: ");
                scanf("%s", sobrenomed);
                buscaEspecificaPorNomeeSobrenomeap(alunos,numAlunos,nomed,sobrenomed);
                break;
        case 2: printf("Digite o nome a ser procurado: ");
                scanf("%s", nomed);
                buscaEspecificaPorNomeap(alunos,numAlunos,nomed);
                break;
        case 3: printf("Digite o sobrenome: ");
                scanf("%s", sobrenomed);
                buscaEspecificaPorSobrenomeap(alunos,numAlunos,sobrenomed);
                break;
        case 4: printf("Digite o curso: ");
                scanf("%s",cursod);
                buscaEspecificaCursoap(alunos,numAlunos,cursod);
                break;
        case 5: printf("Digite o dia da data de nascimento: ");
                scanf("%d",&datanascimentod.dia);
                printf("Digite o mes da data de nascimento: ");
                scanf("%d",&datanascimentod.mes);
                printf("Digite o ano da data de nascimento: ");
                scanf("%d",&datanascimentod.ano);
                buscaEspecificaPorDataap(alunos,numAlunos,datanascimentod);
                break;
        case 6: printf("Digite o prontuario: ");
                scanf("%d", &prontuariod);
                buscaEspecificaPorProntuarioap(alunos,numAlunos,prontuariod);
                break;
            }
}
void trocar(aluno *a, aluno *b){
	aluno aux = *a;
	*a = *b;
	*b = aux;
}
int menorElemprontoNome(aluno *vetorAlunos, int nAlunos, char primeiro){
	int i, menor = primeiro;
    for(i=primeiro + 1; i<nAlunos; i++){
        if(strcmp(vetorAlunos[i].nome,vetorAlunos[menor].nome) < 0){
            menor = i;
        }
    }
    return menor;
}
int menorElemprontoSobrenome(aluno *vetorAlunos, int nAlunos, char primeiro){
	int i, menor = primeiro;
    for(i=primeiro + 1; i<nAlunos; i++){
        if(strcmp(vetorAlunos[i].sobrenome,vetorAlunos[menor].sobrenome) < 0){
            menor = i;
        }
    }
    return menor;
}
int menorElemprontoNSobrenome(aluno *vetorAlunos, int nAlunos, char primeiro){
	int i, menor = primeiro;
    for(i=primeiro + 1; i<nAlunos; i++){
        if(strcmp(vetorAlunos[i].nome,vetorAlunos[menor].nome) == 0){
            if(strcmp(vetorAlunos[i].sobrenome,vetorAlunos[menor].sobrenome) < 0){
                menor = i;
            }
        }else{
            if(strcmp(vetorAlunos[i].nome,vetorAlunos[menor].nome) < 0){
                if(strcmp(vetorAlunos[i].sobrenome,vetorAlunos[menor].sobrenome) < 0){
                    menor = i;
                }
            }
        }
    }
    return menor;
}
int menorElemprontoData(aluno *vetorAlunos, int nAlunos, int primeiro){
	int i, menor = primeiro;
    for(i=primeiro + 1; i<nAlunos; i++){
        if(vetorAlunos[i].datanascimento.ano  < vetorAlunos[menor].datanascimento.ano){
            if(vetorAlunos[i].datanascimento.mes < vetorAlunos[menor].datanascimento.mes){
                if(vetorAlunos[i].datanascimento.dia < vetorAlunos[menor].datanascimento.dia){
                    menor = i;
                }
            }
        }else{
            if(vetorAlunos[i].datanascimento.mes < vetorAlunos[menor].datanascimento.mes){
                if(vetorAlunos[i].datanascimento.dia < vetorAlunos[menor].datanascimento.dia){
                    menor = i;
                }
            }else{
                    if(vetorAlunos[i].datanascimento.dia < vetorAlunos[menor].datanascimento.dia){
                        menor = i;
                    }else{
                        menor = i;
                    }
            }
        }
    }
    return menor;
}
int menorElemprontoCurso(aluno *vetorAlunos, int nAlunos, char primeiro){
	int i, menor = primeiro;
    for(i=primeiro + 1; i<nAlunos; i++){
        if(strcmp(vetorAlunos[i].curso,vetorAlunos[menor].curso) < 0){
            menor = i;
        }
    }
    return menor;
}
int menorElempronto(aluno *vetorAlunos, int nAlunos, int primeiro){
	int i, menor = primeiro;
	for(i = primeiro + 1; i < nAlunos; i++){
		if(vetorAlunos[i].prontuario < vetorAlunos[menor].prontuario){
			menor = i;
		}
	}
	return menor;

}
int ordSelecaop(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElempronto(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int ordSelecaon(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElemprontoNome(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int ordSelecaos(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElemprontoSobrenome(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int ordSelecaoNS(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElemprontoNSobrenome(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int ordSelecaoC(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElemprontoCurso(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int ordSelecaoData(aluno *vetorAlunos, int nAlunos){
	int i, menor;
	for(i=0; i<nAlunos; i++){
		menor = menorElemprontoData(vetorAlunos, nAlunos, i);
		trocar(&vetorAlunos[i], &vetorAlunos[menor]);
	}
}
int posicao_elemento(aluno *vetorAlunos, int ultimo, aluno *elemento, int crit) {
    int i;
    for(i = 0;i <= ultimo && (comparaAlunos(vetorAlunos[i],*elemento,crit) <= 0); i++);
    return i;
}
void deslocar_subvetor(aluno *vetorAlunos,int primeiro,int ultimo){
    int i;
    for(i = ultimo; i >= primeiro;i--){
        vetorAlunos[i+1] = vetorAlunos[i];
    }
}
int particionar(aluno * vetorAlunos, int ini, int fim,int crit){
    aluno pivo;
    pivo = vetorAlunos[fim];
    while (ini < fim){
        while(ini<fim && comparaAlunos(vetorAlunos[ini],pivo,crit)<= 0){
            ini++;
        }
        while (ini<fim && comparaAlunos(vetorAlunos[fim],pivo,crit) > 0 ){
            fim--;
        }
        trocar(&vetorAlunos[ini], &vetorAlunos[fim]);
    }
    return ini;
}
int ordenar_insercao(aluno *vetorAlunos,int nAlunos, int crit){
    int i, posicao; 
    aluno elemento;
    for(i= 1; i< nAlunos ; i++){
        elemento = vetorAlunos[i];
        posicao = posicao_elemento(vetorAlunos,i-1, &elemento , crit);
        deslocar_subvetor(vetorAlunos,posicao,i-1);
        vetorAlunos[posicao] = elemento;
    }
}
void quick_sort(aluno *vetorAlunos,int ini,int fim, int crit){
    int pos;
    if (ini<fim){
        pos = particionar(vetorAlunos,ini,fim,crit);
        quick_sort(vetorAlunos, ini,pos-1,crit);
        quick_sort(vetorAlunos,pos,fim,crit);
    }
}

void ordenaProntup(aluno *vetorAlunos, int nAlunos){
	ordSelecaop(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
void ordenaProntun(aluno *vetorAlunos, int nAlunos){
	ordSelecaon(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
void ordenaProntus(aluno *vetorAlunos, int nAlunos){
	ordSelecaos(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
void ordenaProntuNS(aluno *vetorAlunos, int nAlunos){
	ordSelecaoNS(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
void ordenaProntuC(aluno *vetorAlunos, int nAlunos){
	ordSelecaoC(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
void ordenaProntuData(aluno *vetorAlunos, int nAlunos){
	ordSelecaoData(vetorAlunos, nAlunos);
	imprimeAlunos(vetorAlunos, nAlunos);
}
int getMenuordenacao() {
    int i;
    printf ("===Menu De Busca: ===\n0 - Sair \n1 - Nome e Sobrenome\n2 - Nome\n3 - Sobrenome \n4 - Data\n5 - Curso \n6- Prontuario\n Digite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}
int getMenuordenacaoInsert() {
    int i;
    printf ("===Menu De Busca: ===\n0 - Sair \n1 - Nome e Sobrenome\n2 - Nome\n3 - Sobrenome \n4 - Data\n5 - Curso \n6- Prontuario\n Digite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}
int getMenuordenacaoQuick(){
    int i;
    printf ("===Menu De Busca: ===\n0 - Sair \n1 - Nome e Sobrenome\n2 - Nome\n3 - Sobrenome \n4 - Data\n5 - Curso \n6- Prontuario\n Digite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}
int getMenuordenacoes() {
    int i;
    printf ("===Menu De Busca: ===\n0 - Sair \n1 - Quick Sort \n2 - Merge Sort\n3 - Insertion Sort \n4 - Selection Sort\n Digite uma  opcao: ");
    scanf("%d",&i);
    limpaBuffer();
    return i;
}
int getMenuComparacoes(){
    int i;
    printf("---Menu de Comparacoes---\n0 - Sair \n1 - Prontuario\n2 - Nome e Sobrenome\n3 - Nome\n4 - Sobrenome\n5 - Curso\n6- Data , digite uma opcao: ");
}
int insertOrdenada(aluno *alunos, int numAlunos){
	int menuOrdenacaoInsert;
	menuOrdenacaoInsert = getMenuordenacaoInsert();
	switch(menuOrdenacaoInsert){
		case 1:printf("-Ordenar por nome e sobrenome-\n");
            ordenar_insercao(alunos,numAlunos,2);
            printf("Concluido com sucesso.\n");
			break;
		case 2:printf("-Ordenar por nome-\n");
            ordenar_insercao(alunos,numAlunos,3);
            printf("Concluido com sucesso.\n");
		    break;
		case 3:printf("-Ordenar por sobrenome-\n");
            ordenar_insercao(alunos,numAlunos,4);
            printf("Concluido com sucesso.\n");
			break;
		case 4:printf("-ordenar por data de nascimento-\n");
            ordenar_insercao(alunos,numAlunos,6);
            printf("Concluido com sucesso.\n");
			break;
		case 5:printf("-Ordenar por curso-\n");
            ordenar_insercao(alunos,numAlunos,5);
            printf("Concluido com sucesso.\n");
		    break;
        case 6:printf("-Ordenar por prontuario-\n");
		    ordenar_insercao(alunos, numAlunos,1);
            printf("Concluido com sucesso.\n");
            break;
	}
}
int quickOrdenada(aluno *alunos, int numAlunos){
	int menuOrdenacaoQuick;
	menuOrdenacaoQuick = getMenuordenacaoQuick();
	switch(menuOrdenacaoQuick){
		case 1:printf("-Ordenar por nome e sobrenome-\n");
            quick_sort(alunos,0,numAlunos,2);
            printf("Concluido com sucesso.\n");
			break;
		case 2:printf("-Ordenar por nome-\n");
            quick_sort(alunos,0,numAlunos,3);
            printf("Concluido com sucesso.\n");
		    break;
		case 3:printf("-Ordenar por sobrenome-\n");
            quick_sort(alunos,0,numAlunos,4);
            printf("Concluido com sucesso.\n");
			break;
		case 4:printf("-ordenar por data de nascimento-\n");
            quick_sort(alunos,0,numAlunos,6);
            printf("Concluido com sucesso.\n");
			break;
		case 5:printf("-Ordenar por curso-\n");
            quick_sort(alunos,0,numAlunos,5);
            printf("Concluido com sucesso.\n");
		    break;
        case 6:printf("-Ordenar por prontuario-\n");
		    quick_sort(alunos,0, numAlunos,1);
            printf("Concluido com sucesso.\n");
            break;
		}
    }
int mainOrdenada(aluno *alunos, int numAlunos){
	int menuOrdenacao;
	menuOrdenacao = getMenuordenacao();
	switch(menuOrdenacao){
		case 1:printf("-Ordenar por nome e sobrenome-\n");
        ordenaProntuNS(alunos,numAlunos);
        printf("Concluido com sucesso.\n");
			break;
		case 2:printf("-Ordenar por nome-\n");
        ordenaProntun(alunos,numAlunos);
        printf("Concluido com sucesso.\n");
		    break;
		case 3:printf("-Ordenar por sobrenome-\n");
        ordenaProntus(alunos,numAlunos);
        printf("Concluido com sucesso.\n");
			break;
		case 4:printf("-ordenar por data de nascimento-\n");
        ordenaProntuData(alunos,numAlunos);
        printf("Concluido com sucesso.\n");
			break;
		case 5:printf("-Ordenar por curso-\n");
        ordenaProntuC(alunos,numAlunos);
        printf("Concluido com sucesso.\n");
		    break;
        case 6:printf("-Ordenar por prontuario-\n");
		ordenaProntup(alunos, numAlunos);
        printf("Concluido com sucesso.\n");
            break;
		}
}
int mainOrdenacoes(aluno *alunos, int numAlunos){
	int menuOrdenacoes;
	menuOrdenacoes = getMenuordenacoes();
	switch(menuOrdenacoes){
		case 1:printf("-Ordenacao Quick Sort-\n");
            quickOrdenada(alunos,numAlunos);
            printf("Concluido com sucesso.\n");
			break;
		case 2:printf("-Ordencao Merge Sort-\n");
            printf("Concluido com sucesso.\n");
		    break;
		case 3:printf("-Ordenacao Insertion Sort-\n");
            insertOrdenada(alunos,numAlunos);
			break;
		case 4:printf("-Ordenacao Selection Sort-\n");
            mainOrdenada(alunos,numAlunos);
            printf("Concluido com sucesso.\n");
			break;
		}
}
void mergeOrdenada(){

}

int main()
{
    aluno alunos[MAXALUNOS];
    int numAlunos = 0;
    int menu;
    int menubusca; 
    do {
        menu = getMenu();
        switch(menu) {
            case 1: cadastrarAluno(alunos, &numAlunos);
                    break;
            case 2: imprimeAlunos(alunos, numAlunos);
                    break;
            case 3: salvaArquivo(alunos, numAlunos);
                    break;
            case 4: numAlunos = lerArquivo(alunos);
                    break;
            case 5: menubuscas(alunos, numAlunos);
                    break;
            case 6: menubuscas1(alunos,&numAlunos);
                    break;   
            case 7: mainOrdenacoes(alunos,numAlunos);             
        }       
    } while (menu != 0);   
}