#ifndef trabalhoap2_h
#define trabalhoap2_h
#define TAMNOME 50
#define TAMSOBRENOME 50
#define MAXALUNOS 1000

typedef struct data{
    int dia;
    int mes;
    int ano;

} data;

typedef struct registro{
    char nome [TAMNOME];
    char sobrenome [TAMSOBRENOME];
    data datanascimento;
    int prontuario;
    char curso [4];
} aluno;
#endif