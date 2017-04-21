#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define TAM_POPULACAO 10
#define ERRONALEITURA 1
#define OK 2

//#define QTDPROF
//#define QTDDISC//
//#define QTDSALA 

//para freeMem
#define SEMESTRE 101
#define PROF_AUX 102
#define DISC_AUX 103
#define PLCAO 104
#define INDVO 105
#define GENES 106

//variaveis globais
int qtdprof,qtdsem,qtddisc;
int posicao_arq;

//int tam_populacao = 10;

typedef struct gene{

	int dia_sem;	
	char *prof;
	int *notpref;
	int numpref;
	int disc;
	int sala;
	int sala_id;
	int periodo;
	char sem[4];
	//outres *test;
}genes;

typedef struct ind{

	genes *genes_indv;
	int qtdpr;
	int choques;
	int qtd; 

}indvo;

typedef struct pop{
//	int *qtd;
	indvo *individuos;

}plcao;



//auxiliar
typedef struct teac{

	char *nome;
	int num;
	int *horarios;


}prof_aux;

typedef struct sem{
	char se[3];
	int num;
	int sala;
	int *horarios;

}semestre;

typedef struct disc{

	char cod[6];
	int periodo;
	char cod_sem[3];
	char *nome;

}disc_aux;


prof_aux *leProfessores(char arq[20]);
semestre *leSemestre(char arq[20]);
disc_aux *leDisciplina(char arq[20]);

void freeMem(void *algo,int component);

int testaParada(int *v);
