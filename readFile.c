#include "ag.h"


//int qtdprof, qtddisc,qtdsem;

prof_aux *leProfessores(char arq[20]){
	int qtd =0;
	int ii,k,j,i;
	char a[6];
	char aux;
	char *t = (char *)malloc(sizeof(char)*20);	
	FILE *arqi;
	prof_aux *pf;
	
	arqi = fopen(arq,"r");
	if(!arqi) {printf("Erro na leitura"); return NULL;}
	fscanf (arqi, "%d", &qtdprof);
	pf = (prof_aux *)malloc(sizeof(prof_aux)*qtdprof);
//printf("%d\n", qtdprof);
	//printf("%d\n", i); 
	//printf("%ld\n", ftell(arqi));
	fseek(arqi,1,SEEK_CUR);
	for(j = 0;j <qtdprof;j++){
		fscanf(arqi,"%s %d", t, &ii);
	//	printf("%s %d\n", t,ii);
		pf[j].nome = (char *)malloc(sizeof(char)*strlen(t));
		strcpy(pf[j].nome,t);
		if(ii == 0) pf[j].horarios = NULL;
		else
			pf[j].horarios = (int *)malloc(sizeof(int)*ii);
		pf[j].num = ii;
		
		for(k =0;k<ii;k++){
			fscanf (arqi, "%d", &qtd);
			pf[j].horarios[k] = qtd;
				//printf("%d ", pf[j].horarios[k]);
		}
		
	}
	
	posicao_arq = ftell(arqi);
	fclose(arqi);
	free(t);	
	return pf;
}

semestre *leSemestre(char arq[20]){

	FILE *arqi;
	semestre *semn;
	char *t = (char *)malloc(sizeof(char)*5);	
	int ii,i,j,k,l;
	arqi = fopen(arq,"r");
	if(!arqi) {printf("Erro na leitura"); return NULL;}
	fseek(arqi,posicao_arq+1,SEEK_CUR);
	fscanf (arqi, "%d", &qtdsem);
	semn = (semestre *)malloc(sizeof(semestre)*qtdsem);
	//printf("%d", qtdsem);
	for(i = 0;i<qtdsem;i++){
		fscanf(arqi,"%s %d %d", t, &ii,&l);
		strcpy(semn[i].se,t);
		semn[i].sala = ii;
		semn[i].horarios = (int *)malloc(sizeof(int)*ii);
		semn[i].num = l;
		for(j = 0;j < l;j++){
			fscanf(arqi,"%d", &k);
			semn[i].horarios[j] = k;
		}
		

	}
	
	posicao_arq = ftell(arqi);
	fclose(arqi);
	free(t);
	return semn;	
}

disc_aux *leDisciplina(char arq[20]){

	FILE *arqi;
	disc_aux *discc;
	int i,j,k;
	char *t = (char *)malloc(sizeof(char)*5);	
	char *t2 = (char *)malloc(sizeof(char)*5);	
	char *t1 = (char *)malloc(sizeof(char)*20);
	
	arqi = fopen(arq,"r");
	if(!arqi) {printf("Erro na leitura"); return NULL;}
	fseek(arqi,posicao_arq+1,SEEK_CUR);

	fscanf (arqi, "%d", &qtddisc);
	discc = (disc_aux *)malloc(sizeof(disc_aux)*qtddisc);


	for(i = 0; i < qtddisc;i++){
		fscanf(arqi,"%s %d %s %s", t, &j,t2,t1);
		strcpy(discc[i].cod,t);
		discc[i].periodo = j;
		strcpy(discc[i].cod_sem,t2);
		discc[i].nome = (char *)malloc(sizeof(char)*strlen(t1));
		strcpy(discc[i].nome,t1);
	
	
	
	}
	free(t);free(t1);free(t2);
	fclose(arqi);
	return discc;

}