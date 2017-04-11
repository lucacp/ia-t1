#include "ag.h"

int manha[10] = {0,1,2,3,4,5,6,7,8,9};
int tarde[10] = {10,11,12,13,14,15,16,17,18,19};
int noite[10] = {20,21,22,23,24,25,26,27,28,29};
int somadisc = 62;

int  posicaoHorario(int num){

	int i;
	for(i = 0; i < 10;i++){
			if(manha[i]==num) return 1;
			else if(tarde[i]==num) return 2;
			else if(noite[i]==num) return 3;
	
	
	}
	return 0;

}
int testaRestricao(indvo ppl, disc_aux t, int horario){

	//pares nao permitido (21,02) , (23,04), (25,06), (27,08)
	int i;
	for(i = 0; i<150;i++){
			if(ppl.genes_indv[i].dia_sem == 21 ){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==2)			
					return 0;
				else return 1;
				
			}
			else if(ppl.genes_indv[i].dia_sem == 23){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==4)			
					return 0;
				else return 1;
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 25) {
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==6)			
					return 0;
				else return 1;
			}
			else if(ppl.genes_indv[i].dia_sem == 27){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==8)			
					return 0;
				else return 1;
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 2){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==21)			
					return 0;
				else return 1;
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 4){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==23)			
					return 0;
				else return 1;
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 6){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==25)			
					return 0;
				else return 1;
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 8){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==27)			
					return 0;
				else return 1;
			
			
			}
 	
	
	}



}

int *copiaVetor(int *a, int *b, int tam){

	int i;
	for(i = 0; i < tam;i++){
		a[i] = b[i];	
	
	
	}
	return a;


}

int achaSala(char *s1){

	int i;
	for(i = 0; i < qtdsem;i++){
		if(strcmp(s1,"V1")==0)return 0;
		if(strcmp(s1,"M3")==0)return 1;
		if(strcmp(s1,"M5")==0)return 2;
		if(strcmp(s1,"M7")==0)return 3;
		if(strcmp(s1,"N1")==0)return 4;
		if(strcmp(s1,"N2")==0)return 5;
		if(strcmp(s1,"N3")==0)return 6;
		if(strcmp(s1,"N4")==0)return 7;
		if(strcmp(s1,"N5")==0)return 8;	
	
	}

}

int achaProf(prof_aux *pf, char *nome){

	int i;
	for(i = 0; i < qtdprof;i++){
		if(strcmp(pf[i].nome,nome)==0)return i;	
	}
	return -1;


}

//Copia vetor semestre
semestre *copiaEst(semestre *ss){

	semestre *aux;
	int i,j;
	aux = (semestre *)malloc(sizeof(semestre)*qtdsem);
	for(i = 0 ; i < qtdsem;i++){
		aux[i].num = ss[i].num;
		aux[i].horarios = (int *)malloc(sizeof(int)*aux[i].num);
		for( j = 0; j < aux[i].num;j++)
			aux[i].horarios[j] = ss[i].horarios[j];
	}	
	return aux;



}

//gera uma sala aleatoria

int geraSala(semestre *aux, int n){

	int i;
	int g;
	
	g = rand() % aux[n].num;
	if(aux[n].horarios[g] < 0){
		for(i = 0; i < aux[n].num;i++)
			if(aux[n].horarios[i] >= 0) return i;	
	
	
	}
		
	return -1;		
	
	


}
void geraIndividuos(plcao *populacao_t, char *arq){

	prof_aux *pf;
	semestre *sm;
	semestre *auxsm;
	disc_aux *dsa;
	int i,j,k,temp,flag = 0,turno,numsala;
	int discomp = 0, distt,test;
	plcao *ppl = NULL;
	ppl = (plcao *)malloc(sizeof(plcao));
	ppl->individuos = (indvo *)malloc(sizeof(indvo)*TAM_POPULACAO);
	ppl->individuos[0].qtd =0;
	ppl->individuos->genes_indv = (genes *)malloc(sizeof(genes)*150);
	//ppl->qtd- = (genes *)malloc(sizeof(genes)*150);
	
	
	pf = leProfessores(arq);
	sm = leSemestre(arq);
	dsa = leDisciplina(arq);
	auxsm = copiaEst(sm);
	int *v = (int *)malloc(sizeof(int)*qtddisc);
	int *salasd = (int *)malloc(sizeof(int)*30);
	for(i =0 ; i < qtddisc;i++) v[i] = i;
	for(i = 0; i < 30;i++) salasd[i] = i;

	discomp = somadisc;
	while(discomp){
		//Escolhe disciplina aleatoria
		j = rand() %qtddisc;
		if(j < 0){
			for(i = 0; i < qtddisc;i++)		
				if(i >=0){ j = i;break;}
		}
			
		if(strcmp(dsa[j].cod_sem,"V1")==0){
			temp = rand() % 10;turno = 0;
			numsala = achaSala(dsa[j].cod_sem);
		}
		else if(dsa[j].cod_sem[0]=='M'){
			temp = 10 + rand() % 10;turno = 1;
			numsala = achaSala(dsa[j].cod_sem);	
		}
		else if(dsa[j].cod_sem[0]=='N'){
			temp = 20 + rand() % 10;turno = 2;
			numsala = achaSala(dsa[j].cod_sem);	
		}
		distt = geraSala(auxsm,numsala);
		if(distt < 0)continue;
		
		//auxsm[numsala].horario[distt] = 
		//Testa restricao de horario
		if(!testaRestricao(ppl->individuos[0], dsa[j], temp))continue;
		for(i = 0; i < ppl->individuos[0].qtd;i++){
			if(ppl->individuos[0].genes_indv[i].dia_sem == temp &&
				strcmp(ppl->individuos[0].genes_indv[i].prof,dsa[j].nome)==0){flag = 1; break;}		
		
			/*else if(ppl->individuos[0]->genes_ind[i].dia_sem == temp &&
					 strcmp(ppl->individuos[0]->genes_ind[i].prof,dsa[j].nome)!=0){
			
			}*/
		
		}
		if(!flag){
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].dia_sem = temp;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].prof = (char *)malloc(sizeof(char)*strlen(dsa[j].nome));
			strcpy(ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].prof,dsa[j].nome);
			test = achaProf(pf,dsa[j].nome);			
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].notpref = 
					copiaVetor(pf[test].horarios, ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].notpref,
					pf[test].num);	
		
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].disc = j;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala = sm[distt].sala;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala_id = distt;	
			flag = 1;		
			
			ppl->individuos[0].qtd++;
			if(dsa[j].periodo == 1){
				v[j] = -1;			
			
			
			}
			
		}
		discomp--;
	}
	
	
	/*for(i=0;i<qtdprof;i++) {
		printf("Nome : %s \n",pf[i].nome);
		for(j = 0; j < pf[i].num;j++)
			printf("%d ", pf[i].horarios[j]);
		printf("\n\n");		
		}*
		
		for(i = 0; i < qtdsem;i++){
			printf("Cod : %s %d \n",sm[i].se,sm[i].num);
			for(j = 0; j < sm[i].num;j++)
				printf("%d ", sm[i].horarios[j]);
			printf("\n\n");	
		
		
		}
		
		for(i = 0; i < qtddisc;i++)
			printf("Cod : %s per: %d %s %s \n",dsa[i].cod,dsa[i].periodo, dsa[i].cod_sem,dsa[i].nome);
			
		*/
		
	


}
int main(int argc, char *argv[ ] ){
	int i= 0;
	//printf("%s", argv[1]);
	//char a = argv[0];
//	char *t[];
	plcao *populacao;
	populacao = (plcao *)malloc(sizeof(plcao));
	populacao->individuos = (indvo *)malloc(sizeof(indvo));
	populacao->individuos->genes_indv = (genes *)malloc(sizeof(genes));
	populacao->individuos->genes_indv->notpref = (int *)malloc(sizeof(int)*5);
	
	geraIndividuos(populacao,argv[1]);
	return 0;
}