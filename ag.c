#include "ag.h"
#define UM_PONTO 1
#define DOIS_PONTOS 2
#define QUATRO_PONTOS 4

int manha[10] = {0,1,2,3,4,5,6,7,8,9};
int tarde[10] = {10,11,12,13,14,15,16,17,18,19};
int noite[10] = {20,21,22,23,24,25,26,27,28,29};
int somadisc = 62;
int aux;
int par,impar;

prof_aux *pf;
semestre *sm;
disc_aux *dsa;
semestre *auxsm;

int  avaliacao(indvo *ppl){

	int i,j,tam,tam2,k;
	int aparece = 0,flag = 0;
	int soma = 0;
	int *hora = (int *)malloc(sizeof(int)*5);
	int *hora2 = (int *)malloc(sizeof(int)*5);
	char nome[20];
	//Contabiliza a distribuicao dos horarios	
	for(i = 0 ; i < qtddisc;i++){
		aparece = 0;
		tam  = 0;
		flag = 0;
		
		for(j = 0; j < ppl->qtd;j++){
			if(ppl->genes_indv[j].disc == i && ppl->genes_indv[j].periodo == 2){
				for(k = 0; k < tam;k++){
					if(hora[k] == ppl->genes_indv[j].dia_sem){flag = 1;break;}
				}
				
				if(!flag){hora[tam++] = ppl->genes_indv[j].dia_sem; }		
				
			}
		
		
		
		}
		
		soma += tam;
	}
	ppl->choques = soma;	
	soma = 0;
	
	//Penaliza horarios consecutivos
	for(i = 0 ; i < qtddisc;i++){
		tam  = 0;flag = 0;aparece = 0;tam2 = 0;
		strcpy(nome,dsa[i].nome);
		for(j = 0; j < ppl->qtd;j++){
			if(ppl->genes_indv[j].disc == i && ppl->genes_indv[j].periodo == 2 &&
			   strcmp(nome,ppl->genes_indv[j].prof)==0){
				if(!flag){				
					hora[tam++] = ppl->genes_indv[j].dia_sem;flag = 1;
					//strcpy(nome,ppl->genes_indv[j].prof);
				}
				else{
					if(hora[0]+1 == ppl->genes_indv[j].dia_sem)
						hora[tam++]= ppl->genes_indv[j].dia_sem;
					else if(hora[0] - 1 == ppl->genes_indv[j].dia_sem)
						hora[tam++]= ppl->genes_indv[j].dia_sem;			
								
				}
			}
			
			
		}
		if(tam > 1)
			soma+=tam*QUATRO_PONTOS;
		//printf("soma %d", soma);
	}
	ppl->qtdpr = soma;
	
	//Verifica os horarios nao preferidos
	
	soma = 0;
	for(i = 0; i < qtddisc;i++){
		aparece = 0;
		tam  = 0;
		flag = 0;
		
		strcpy(nome,dsa[i].nome);
		for(j = 0; j < ppl->qtd;j++){
			if(ppl->genes_indv[j].disc == i && strcmp(nome,ppl->genes_indv[j].prof)==0){
				for(k = 0; k < ppl->genes_indv[j].numpref;k++)
					if(ppl->genes_indv[j].notpref[k] == ppl->genes_indv[j].dia_sem)
						tam += 1;			
			}
			
		
		}
		soma += tam;
		
	
	
	}
	ppl->qtdpr += soma;
	
	soma = 0;
	int dia;
	//Verifica horario de manha e noite no mesmo dia
	//(00,01)->(20,21), (02,03)->(22,23)
	//(04,05)->(24,25), (06,07)->(26,27)
	//(08,09)->(28,29)
	for(i = 0 ; i < qtdprof; i++){
		tam = 0;
		aparece = 0;
		strcpy(nome,pf[i].nome);
		flag = 0;
		for(j = 0; j < ppl->qtd;j++){
			if(strcmp(nome,ppl->genes_indv[j].prof)==0){
				hora[tam] = ppl->genes_indv[j].dia_sem;
				hora2[tam++] = 1;
			}
			/*if(!flag){
				dia = ppl->genes_indv[j].dia_sem;
				flag = 1;			
			}
			
			else if(strcmp(nome,ppl->genes_indv[j].prof)==0 && flag ==1){
								
				if(ppl->genes_indv[j].dia_sem==0 || ppl->genes_indv[j].dia_sem==1){
					if(dia==20 || dia==21)				
						tam++;				
				}
				else if(dia==4 || dia==5){
					if(ppl->genes_indv[j].dia_sem==24 || ppl->genes_indv[j].dia_sem==25)				
						tam++;				
				
				}
				else if(ppl->genes_indv[j].dia_sem==8 || ppl->genes_indv[j].dia_sem==9)
					if(dia==28 || dia==29)				
						tam ++;
				else if(ppl->genes_indv[j].dia_sem==2 || ppl->genes_indv[j].dia_sem==3)
					if(dia==22 || dia==23)				
						tam++;				
				
				else if(ppl->genes_indv[j].dia_sem==6 || ppl->genes_indv[j].dia_sem==7)
					if(dia==26 || dia==27)				
						tam++;
			
				dia = ppl->genes_indv[j].dia_sem;
			}*/
		
		
		}
		int l;
		for(k = 0 ; k < tam; k++){
			int count = hora[k];
			hora2[k] = 0;
			//if(hora2[k] == 0)break;
			//if(hora2[k] == 0)continue;
			for(l = 0; l < tam;l++){
				
				//if(strcmp(nome,"Braulio")==0){				
				//	printf("count %d %d %d %d / ", count,hora[l],k,l);}
					if(hora2[l] == 0)continue;
					if(k!=l){
						if(hora[l] == 20 || hora[l] == 21)
							if(count == 0 || count == 1){aparece++; hora2[l] = 0;}
						if(hora[l] == 28 || hora[l] == 29)
							if(count == 8 || count == 9){aparece++; hora2[l] = 0;}
						if(hora[l] == 22 || hora[l] == 23)
							if(count == 2 || count == 3){aparece++; hora2[l] = 0;}
						if(hora[l] == 26 || hora[l] == 27)
							if(count == 6 || count == 7){aparece++; hora2[l] = 0;}
						if(hora[l] == 24 || hora[l]==25 ){
							if(count == 4 || count==5){aparece++; hora2[l] = 0;}
					}
				}
					
			}	
		}
		
		soma += (aparece * DOIS_PONTOS);
	}
	ppl->qtdpr += soma;
	return OK;

}
int testaRestricao(indvo ppl, disc_aux t, int horario){

	//pares nao permitido (21,02) , (23,04), (25,06), (27,08)
	int i;
	for(i = 0; i<ppl.qtd;i++){
			if(ppl.genes_indv[i].dia_sem == 21 ){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==2)			
					return 0;
				
				
			}
			else if(ppl.genes_indv[i].dia_sem == 23){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==4)			
					return 0;
				
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 25) {
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==6){			
					return 0;}
				
			}
			else if(ppl.genes_indv[i].dia_sem == 27){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==8)			
					return 0;
				
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 2){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==21)			
					return 0;
				
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 4){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==23)			
					return 0;
				
				//puts("putds");
			
			}
			else if(ppl.genes_indv[i].dia_sem == 6){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==25){	
					return 0;}
				
			
			
			}
			else if(ppl.genes_indv[i].dia_sem == 8){
				if(strcmp(ppl.genes_indv[i].prof,t.nome)==0 && horario==27)			
					return 0;
				
			
			
			}
 	
	
	}
	return 1;


}
int *copiaVetor(int *a, int *b, int tam){

	int i;
	
	a = (int *)malloc(sizeof(int)*tam);
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
		if(strcmp(s1,"N2")==0)return 4;
		if(strcmp(s1,"N4")==0)return 5;
		if(strcmp(s1,"N6")==0)return 6;
		if(strcmp(s1,"N8")==0)return 7;
		if(strcmp(s1,"N10")==0)return 8;
		
		//if(strcmp(s1,"N5")==0)return 8;	
	
	}
	return -1;
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
		aux[i].sala = ss[i].sala;
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
	//printf("%d %d", aux[n].num,n);puts("oi");
	//srand((unsigned) time(NULL));
	//srand(time(NULL));	
	//g = rand() % aux[n].num;
	//printf("g : %d, %d, %d , hor: %d\n", g,aux[n].num,n,aux[n].horarios[g]); 
	//return 1;
	
	for(i = 0; i < aux[n].num;i++)
		if(aux[n].horarios[i] >= 0) return i;	
	
	
	
		
	return -1;		
	
	


}
int testaParada(int *v){

	int i;
	int flag  =0;
	for(i = 0; i < qtddisc;i++)
		if(v[i] > 0){flag = 1;break;}
		
	return flag;



}
void quicksort2(genes *vetor, int inicio, int fim){
   
   int pivo, aux, i, j, meio,k;
   genes *v1 = (genes *)malloc(sizeof(genes));
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio].dia_sem;
   
   do{
      while (vetor[i].dia_sem < pivo) i = i + 1;
      while (vetor[j].dia_sem > pivo) j = j - 1;
      
      if(i <= j){
      	v1->dia_sem = vetor[i].dia_sem;
      	v1->prof = (char *)malloc(sizeof(char)*20);
      	strcpy(v1->prof,vetor[i].prof);
      	v1->notpref = (int *)malloc(sizeof(int)*vetor[i].numpref);
      	for(k= 0; k <vetor[i].numpref;k++)
      		v1->notpref[k] = vetor[i].notpref[k];
      	v1->numpref = vetor[i].numpref;
      	v1->disc = vetor[i].disc;
      	v1->sala = vetor[i].sala;
      	v1->sala_id = vetor[i]. sala_id;
      	strcpy(v1->sem,vetor[i].sem);
         
         vetor[i].dia_sem = vetor[j].dia_sem;
         strcpy(vetor[i].prof,vetor[j].prof);
         for(k = 0; k < vetor[j].numpref;k++)
         	vetor[i].notpref[k] = vetor[j].notpref[k];
         vetor[i].numpref = vetor[j].numpref;
         vetor[i].disc = vetor[j].disc;
         vetor[i].sala  =vetor[j].sala;
         vetor[i].sala_id = vetor[j].sala_id;
         strcpy(vetor[i].sem,vetor[j].sem);
         
         vetor[j].dia_sem = v1->dia_sem;
         strcpy(vetor[j].prof,v1->prof);
         for(k = 0; k < v1->numpref;k++)
         	vetor[j].notpref[k] = v1->notpref[k];
         vetor[j].numpref = v1->numpref;
         vetor[j].disc = v1->disc;
         vetor[j].sala  =v1->sala;
         vetor[j].sala_id = v1->sala_id;
         strcpy(vetor[j].sem,v1->sem);
         
         
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) quicksort2(vetor, inicio, j);
   if(i < fim) quicksort2(vetor, i, fim);   

}

/*
//codigo quicksort em: 
//https://www.vivaolinux.com.br/script/Ordenacao-QuickSort

void quicksort(int *vetor, int inicio, int fim){
   
   int pivo, aux, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   
   do{
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;
      
      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) quicksort(vetor, inicio, j);
   if(i < fim) quicksort(vetor, i, fim);   

}
*/
int *imprimeaux(indvo *ppl, char semestre[4]){
	int i,j;
	aux = 0;
	int a = ppl->qtd;
	int *v = (int * )malloc(sizeof(int)*10);
	
	par = 0;impar =0;
	for(i = 0 ; i < a; i++){
		if(strcmp(ppl->genes_indv[i].sem,semestre)==0){
			v[aux++] = i;	
	
		
			if(ppl->genes_indv[i].dia_sem%2==0){
				if(ppl->genes_indv[i].dia_sem > par)
					par = ppl->genes_indv[i].dia_sem;
			}
			else{
				if(ppl->genes_indv[i].dia_sem > impar)
					impar = ppl->genes_indv[i].dia_sem;		
			}
	
		}
	}
	return v;
}
int *imprimeaux2(indvo *ppl, int * v){
	int j = 0;
	int i;
	int temp;
	int *v2 = (int * )malloc(sizeof(int)*10);
	int *v1 = (int * )malloc(sizeof(int)*10);
	int *v3 = (int * )malloc(sizeof(int)*10);
	for(i = 0; i < aux;i++){
		
		v1[i] = ppl->genes_indv[v[i]].dia_sem;	
	}
	
	for(i = 0; i < aux; i++){
		if(v1[i]%2 == 0){
			
			v2[j] = v1[i];
			j++;
			
		}	
		//printf("ll %d\n", v2[1]);	
	}
	
	for(i = 0 ; i < aux; i++){
		if(v1[i]%2 != 0){
			
				v2[j] = v1[i];
				j++;
			
		} 	
	}
	j = 0;i=0;
	int k = 0;
	for(k = 0; k < aux; k++){
		for(i = 0; i < aux;i++){
			if(v2[k]==v1[i]){
				v3[k] = v[i];		
				break;
			}
		}	
	}
	for(i = 0; i < aux;i++)v[i] = v3[i];
	for(i = 0; i < 20;i++){
		
	
	
	}
	//for(i = 0; i < aux;i++)printf("%d ", v2[i]);
//	printf("\n");
	//for(k = 0; k < aux;k++) {
	//			printf("%d ", v3[k]);}
	free(v1);free(v3);	
	return v2;
		

}
int pertenceA(int *v,int test){
	int i,j;
	for(i = 0; i < aux;i++){
		if(v[i] == test)return 1;
	}
	return 0;


}
void imprime(indvo *ppl, disc_aux *dd){
	
	int a = ppl->qtd;//puts(pop->individuos[0].genes_indv[a-1].sem);
	int i,j,k;
	int *v,*v2 ;
	int ispar = 2;
	/*for(i = 0; i < a;i++){
		//printf("%d ", pop->individuos[0].genes_indv[i].dia_sem);
		//if(strcmp(pop->individuos[0].genes_indv[i].sem,"V1")==0)
		//	printf("%d %s\n", pop->individuos[0].genes_indv[i].dia_sem,
		//	pop->individuos[0].genes_indv[i].prof);
		if(pop->individuos[0].genes_indv[i].dia_sem ==21){
			for(j  = 0; j < a;j++){
				if(pop->individuos[0].genes_indv[j].dia_sem==2){
					printf("%s %s\n", pop->individuos[0].genes_indv[i].prof,pop->individuos[0].genes_indv[j].prof);
				}
			}
		}
		if(pop->individuos[0].genes_indv[i].dia_sem ==23){
			for(j  = 0; j < a;j++){
				if(pop->individuos[0].genes_indv[j].dia_sem==4){
					printf("%s %s\n", pop->individuos[0].genes_indv[i].prof,pop->individuos[0].genes_indv[j].prof);
				}
			}
		}	
		if(pop->individuos[0].genes_indv[i].dia_sem ==25){
			for(j  = 0; j < a;j++){
				if(pop->individuos[0].genes_indv[j].dia_sem==6){
					printf("%s %s\n", pop->individuos[0].genes_indv[i].prof, pop->individuos[0].genes_indv[j].prof);
				
				}
			}
		}
	   if(pop->individuos[0].genes_indv[i].dia_sem ==27){
			for(j  = 0; j < a;j++){
				if(pop->individuos[0].genes_indv[j].dia_sem==8){
					printf("%s %s\n", pop->individuos[0].genes_indv[i].prof,pop->individuos[0].genes_indv[j].prof);
				}
			}
			
		}
			
	}*/
	//int k = 0;
	//for(k = 0 ; k < a;k++)
	//	printf(" %d : Disc: %s, Prof: %s, horario: %d, sala: %d \n", k+1,dd[pop->individuos[0].genes_indv[k].disc].cod,
	//	 pop->individuos[0].genes_indv[k].prof, pop->individuos[0].genes_indv[k].dia_sem,
	//	 pop->individuos[0].genes_indv[k].sala);
	int flag =0;
	for(i  = 0; i < qtdsem;i++){
		j = 0;ispar = 2;k=0;flag = 0;
		printf("\nSemestre : %s\n", sm[i].se);
		printf("----------------------------------------------------------------------------------------------------------------------|\n");
	   printf("|-----|       S         |         T       |                Q       |             Q        |             S             |\n");
	   printf("______________________________________________________________________________________________________________________|\n");
		if(strcmp(sm[i].se,"V1")==0){
			
	  		printf("13:30-|");
	  		v= imprimeaux(ppl,"V1");
			while(1){
				if(ispar%2==0 && ppl->genes_indv[v[j]].dia_sem%2 == 0){
					printf(" %s(%s)         |", dsa[ppl->genes_indv[v[j]].disc].cod,ppl->genes_indv[v[j]].prof);
					//printf("p:>%d ", ppl->genes_indv[v[j]].dia_sem);
					if(ppl->genes_indv[v[j]].dia_sem==18){
						ispar = 1;j=0;
						printf("\n");printf("15:20-|");					
					}				
				
				
				}
				else if(ispar%2!=0 && ppl->genes_indv[v[j]].dia_sem%2!=0){
					printf("  %s(%s)       |", dsa[ppl->genes_indv[v[j]].disc].cod,ppl->genes_indv[v[j]].prof);
					//printf("t:>%d ", ppl->genes_indv[v[j]].dia_sem);
					if(ppl->genes_indv[v[j]].dia_sem==19){
						ispar = 2;free(v);
						printf("\n");					
						break;
					}				
				
				
				}
				if(j == aux)j=0;
				else j++;			
				
			
			}
		}
		//else if(sm[i].se[0]=='M'){
		else if(strcmp(sm[i].se,"M3")==0){
			printf("07:30-|");
	  		v= imprimeaux(ppl,sm[i].se);
	  		//for(k = 0; k < aux;k++) {
			//	printf("%d>%d ", v[k], ppl->genes_indv[v[k]].dia_sem);}	  		
	  		//printf("\n");
	  		v2 = imprimeaux2(ppl,v);
	  		k = 0;//printf("\n");
			//for(k = 0; k < aux;k++) {
			//	printf("%d ", v2[k]);}	  		
	  		int r= 0;k=0;
			while(1){//printf("n :(%d %d %d %d %d)   ", v2[j],k,j,aux,ispar);
				if(ispar%2 == 0 && v2[j]%2==0){
					
					if(pertenceA(v2,k)==1){
						printf(" %d %s(%s)         |", v2[j],dsa[ppl->genes_indv[v[j]].disc].cod,
						ppl->genes_indv[v[j]].prof);
						
						if(v2[j] == 8){
						printf("\n");printf("10:10-|");ispar = 1;k=-1;}
						
							
						
					}
					
					else if(pertenceA(v2,k)==0){
						
						
						
						printf("     BRANCO      |");					
						if(k >= 8){printf("\n");printf("10:10-|");ispar = 1;k=-1;}
						if(ispar%2 == 0){j--;}
					}
					
				}
				else if(ispar%2!=0 && v2[j]%2!=0){
					if(pertenceA(v2,k) == 1){
						printf(" %d %s(%s)         |", v2[j],dsa[ppl->genes_indv[v[j]].disc].cod,
						ppl->genes_indv[v[j]].prof);			
						if(v2[j] == 9){
						printf("\n");ispar = 2;k=0;break;}
					}				
					else if(pertenceA(v2,k)==0){
						if(ispar%2!=0){j--;}
						printf("     BRANCO      |");					
						if(k >= 9){printf("\n");ispar = 2;k=0;break;}
											
					}
				
				
				}
			
			
			j++;
			if(j+1 == aux)j = aux-1;
			if(ispar%2 == 0){k+=2;}
			else if(ispar%2!=0){k+=2;}
			if(k>8 && ispar%2 == 0)k=8;
			else if(k > 8 && ispar%2!=0)k = 9;
			if(v2[j]%2!=0 && ispar%2==0){
				j--;
			}	
		}
		if(par > 8 || impar > 9){
			j = 0;ispar = 2; k = 10;
			printf("13:30-|");
			while(1) {
				if(v2[j] > 9){		
					if(ispar%2 == 0 && v2[j]%2==0){
						if(pertenceA(v2,k)==1){
						printf(" %d %s(%s)         |", v2[j],dsa[ppl->genes_indv[v[j]].disc].cod,
						ppl->genes_indv[v[j]].prof);
						
						if(v2[j] == 18){
						printf("\n");printf("15:20-|");ispar = 1;k=9;}
								
					  }
					  else if(pertenceA(v2,k)==0){
						
						
						
						printf("     BRANCO      |");					
						if(k >= 18){printf("\n");printf("15:20-|");ispar = 1;k=9;}
						if(ispar%2 == 0){j--;}
					} 
				}
				else if(ispar%2!=0 && v2[j]%2!=0){
					if(pertenceA(v2,k) == 1){
						printf(" %d %s(%s)         |", v2[j],dsa[ppl->genes_indv[v[j]].disc].cod,
						ppl->genes_indv[v[j]].prof);			
						if(v2[j] == 19){
						printf("\n");ispar = 2;k=0;break;}
					}				
					else if(pertenceA(v2,k)==0){
						if(ispar%2!=0){j--;}
						printf("     BRANCO      |");					
						if(k >= 19){printf("\n");ispar = 2;k=0;break;}
											
					}
				
				
				}
				
			}
			j++;
			if(j+1 == aux)j = aux-1;
			if(ispar%2 == 0){k+=2;}
			else if(ispar%2!=0){k+=2;}
			if(k>18 && ispar%2 == 0)k=18;
			else if(k > 18 && ispar%2!=0)k = 19;
			if(v2[j]%2!=0 && ispar%2==0){
				j--;
			}			
		}
		
		
		}
	}
		else{
			continue;
			printf("19:10-|");
	  		v= imprimeaux(ppl,sm[i].se);
	  		
			while(1){
				
				if(ispar%2==0 && ppl->genes_indv[v[j]].dia_sem%2 == 0){
					printf(" %d %s(%s)         |", ppl->genes_indv[v[j]].dia_sem,dsa[ppl->genes_indv[v[j]].disc].cod,ppl->genes_indv[v[j]].prof);
					//printf("p:>%d ", ppl->genes_indv[v[j]].dia_sem);
					if(ppl->genes_indv[v[j]].dia_sem==par){
						ispar = 1;j=0;
						printf("\n");printf("21:00-|");					
					}				
				
				
				}
				else if(ispar%2!=0 && ppl->genes_indv[v[j]].dia_sem%2!=0){
					printf(" %d %s(%s)          |", ppl->genes_indv[v[j]].dia_sem,dsa[ppl->genes_indv[v[j]].disc].cod,ppl->genes_indv[v[j]].prof);
					//printf("t:>%d ", ppl->genes_indv[v[j]].dia_sem);
					if(ppl->genes_indv[v[j]].dia_sem==impar){
						ispar = 2;
						printf("\n");					
						break;
					}				
				
				
				}
				
				if(j == aux)j=0;
				else j++;
				
			}
	
	
	
		}
		
	}
	puts("oitodeis");	
	//temp = (int *)malloc(sizeof(int)*a);
	//if(pop->individuos[0].genes)
	//printf("-----------------------------------\n");
	//printf("|_____  S --- T --- Q --- Q --- S-----\n");
	//printf("13:30-|");
	//for(i = 0 ; i < a;i++)
}
//nao finalizado/
int mutacao(indvo *ppl){

	int r = rand() % ppl->qtd;
	int numsala;
	int distt,i,j,flag;
	printf("MUt");
	printf("%d %s ", ppl->genes_indv[r].dia_sem,
	ppl->genes_indv[r].prof);
	
	//free(auxsm)
	auxsm = copiaEst(sm);
	if(strcmp(ppl->genes_indv[r].sem,"V1")==0){
			numsala = achaSala(ppl->genes_indv[r].sem);
	}
	else if(ppl->genes_indv[r].sem[0]=='M'){
			numsala = achaSala(ppl->genes_indv[r].sem);	
	}
	else if(ppl->genes_indv[r].sem[0]=='N'){
			numsala = achaSala(ppl->genes_indv[r].sem);	
	}
		//printf("N %d ", numsala);
		//printf("%d %d %s\n", numsala,temp,dsa[j].cod_sem);
		
	for(i = 0 ; i < auxsm[numsala].num;i++){
		for(j = 0; j < ppl->qtd;j++){
			if(strcmp(ppl->genes_indv[j].sem,auxsm[numsala].se)==0 && (ppl->genes_indv[j].dia_sem == auxsm[numsala].horarios[i]))
				auxsm[numsala].horarios[i] = -1;
		}
	}
	if(ppl->genes_indv[r].dia_sem != auxsm[numsala].horarios[auxsm[numsala].num-1]){
		for(i = 0; i < auxsm[numsala].num;i++){
			if((auxsm[numsala].horarios[i]!= -1 && 
				auxsm[numsala].horarios[i]!= ppl->genes_indv[r].dia_sem)){
					distt = i;flag = 1;break;				
				} 
		}
		
		while(1){
			flag = 1;
			if(!testaRestricao(*ppl, dsa[ppl->genes_indv[r].disc], auxsm[numsala].horarios[distt])){printf("hj");
				for(i = 0; i < auxsm[numsala].num;i++){
					if((auxsm[numsala].horarios[i]!= -1) && 
					(auxsm[numsala].horarios[i]!= auxsm[numsala].horarios[distt])){
						distt = i;flag = 0;break;				
					} 			
			
				}					
				if(distt != i)return 0;
					
			}
			for(i = 0; i < ppl->qtd;i++){
				if(ppl->genes_indv[i].dia_sem == auxsm[numsala].horarios[distt] &&
				strcmp(ppl->genes_indv[i].sem,sm[ppl->genes_indv[i].sala_id].se)==0){printf("lç");
					int dfi;				
					for(dfi = 0; dfi < qtddisc;dfi++){
					if((auxsm[numsala].horarios[dfi] != auxsm[numsala].horarios[distt]) &&
						auxsm[numsala].horarios[dfi] >= 0){distt = dfi;flag=0;printf("pppp");break;}			
						}
					if(dfi!=distt) return 0;	
					
					//continue;
				}
			}
			puts("laco");
			if(flag == 1)break;
		}
		ppl->genes_indv[r].dia_sem = auxsm[numsala].horarios[distt];
		avaliacao(ppl);
		return 1;
	}
	else return 0;
	//distt = geraSala(auxsm,numsala);
		

}


void geraIndividuos(plcao *populacao_t, char *arq){


	
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
	
	for(i =0 ; i < qtddisc;i++){
		v[i] = dsa[i].periodo; 
		//printf("%d ", v[i]);
	} 
	for(i = 0; i < 30;i++) salasd[i] = i;
	
	discomp = testaParada(v);
	srand(time(NULL));
	int x = 0;
	while(discomp){
		//Escolhe disciplina aleatoria
		int ll;		
		//srand(0);
		j = rand() %qtddisc;
		//if(x > 37){
			//for(ll = 0; ll < qtddisc;ll++)
		///	printf("%d ", v[ll]);
		//	printf("j:%d\n", j);
		//	return;
		printf("\n");
	//}
		if(v[j] < 1){
			for(i = 0; i < qtddisc;i++)		
				if(v[i] >0){ j = i;}
		}
		
		if(strcmp(dsa[j].cod_sem,"V1")==0){
			//temp = rand() % 10;turno = 0;
			numsala = achaSala(dsa[j].cod_sem);
		}
		else if(dsa[j].cod_sem[0]=='M'){
			//temp = 10 + rand() % 10;turno = 1;
			numsala = achaSala(dsa[j].cod_sem);	
		}
		else if(dsa[j].cod_sem[0]=='N'){
			//temp = 20 + rand() % 10;turno = 2;
			numsala = achaSala(dsa[j].cod_sem);	
		}
		//printf("N %d ", numsala);
		//printf("%d %d %s\n", numsala,temp,dsa[j].cod_sem);
		distt = geraSala(auxsm,numsala);
		printf("dist>%d %d", auxsm[numsala].horarios[distt],numsala);
		int l;		
		for(l = 0 ; l < auxsm[numsala].num;l++)
			printf("%d ", auxsm[numsala].horarios[l]);
		//if(ppl->individuos[0].genes_indv[j].prof)
		if(distt < 0)continue;
		
		if(!testaRestricao(ppl->individuos[0], dsa[j], auxsm[numsala].horarios[distt])){
			int dfi;
			puts("rest");
			for(dfi = 0; dfi < qtddisc;dfi++)
				if((auxsm[numsala].horarios[dfi] != auxsm[numsala].horarios[distt]) &&
					auxsm[numsala].horarios[dfi] >= 0){distt = dfi;break;}			
		
			if(dfi != distt)continue; 	
		}
		for(i = 0; i < ppl->individuos[0].qtd;i++){
			if(ppl->individuos[0].genes_indv[i].dia_sem == auxsm[numsala].horarios[distt] &&
				strcmp(ppl->individuos[0].genes_indv[i].prof,dsa[j].nome)==0){
				int dfi;				
				for(dfi = 0; dfi < qtddisc;dfi++)
				if((auxsm[numsala].horarios[dfi] != auxsm[numsala].horarios[distt]) &&
					auxsm[numsala].horarios[dfi] >= 0){distt = dfi;break;}			
						
				if(dfi!=distt)continue;	
					
					//continue;
			}		
		
			else if(ppl->individuos[0].genes_indv[i].dia_sem == auxsm[numsala].horarios[distt] &&
			strcmp(dsa[j].cod_sem,ppl->individuos[0].genes_indv[i].sem)==0){puts("oi");flag = 1; continue;;}
			
			
			/*else if(ppl->individuos[0]->genes_ind[i].dia_sem == temp &&
					 strcmp(ppl->individuos[0]->genes_ind[i].prof,dsa[j].nome)!=0){
			
			}*/
		
		}
		if(!flag){
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].dia_sem = auxsm[numsala].horarios[distt];
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].prof = (char *)malloc(sizeof(char)*strlen(dsa[j].nome));
					
			strcpy(ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].prof,dsa[j].nome);
						
			test = achaProf(pf,dsa[j].nome);//printf("%d", pf[test].horarios[2]); 			
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].notpref = 
					copiaVetor(ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].notpref,
					pf[test].horarios, pf[test].num);		
		
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].numpref = pf[test].num;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].disc = j;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala = sm[numsala].sala;
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala_id = numsala;	
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].periodo = dsa[j].periodo; 			
					
			strcpy(ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sem,dsa[j].cod_sem);		
			//auxsm[numsala].horarios[distt] = -1;			
			//printf("%d",dsa[j].periodo);
			
			if(v[j] == 1){
				v[j] = -1;			
			
			
			}
			else if(v[j] == 2) v[j]--;
			
			
			
			//Marca sala indisponivel			
			
			int ee = auxsm[numsala].sala;
			int b,a;
			for(b = 0; b < qtdsem;b++){
				if(auxsm[b].sala == ee ){
					for(a =0;a < auxsm[b].num;a++){
						if(auxsm[b].horarios[a]==auxsm[numsala].horarios[distt]){
							auxsm[b].horarios[a] = -1;
						}
					}
				}
			}
			auxsm[numsala].horarios[distt] = -1;
			/*printf("%d %d %s %d %d %d \n",ppl->individuos[0].qtd,
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].dia_sem,
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].prof,
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].disc,
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala,
			ppl->individuos[0].genes_indv[ppl->individuos[0].qtd].sala_id);
				
			*/
			//int ll;
			ppl->individuos[0].qtd++;
			discomp = testaParada(v);
			
			//printf("disc>%d ", discomp);		
			//discomp--;		
		}
		else flag = 0;
		x++;
	}
	//puts(ppl->individuos[0].genes_indv[ppl->individuos[0].qtd-1].sem);
	//imprime(ppl);
	int b;
	
	quicksort2(ppl->individuos[0].genes_indv,0,ppl->individuos[0].qtd-1);
	imprime(&ppl->individuos[0],dsa);
	avaliacao(&ppl->individuos[0]);
	printf("Quebra: %d prf >: %d", ppl->individuos[0].choques, ppl->individuos[0].qtdpr);	
	puts("okeeee");	
	if(mutacao(&ppl->individuos[0])){
		puts("h2w2e3");
		imprime(&ppl->individuos[0],dsa);}
	puts("herellll");
		puts("ok");	
	
}
int main(int argc, char *argv[ ] ){
	int i= 0;
	//printf("%s", argv[1]);
	//char a = argv[0];
//	char *t[];
	plcao *populacao;
	//populacao = (plcao *)malloc(sizeof(plcao));
	//populacao->individuos = (indvo *)malloc(sizeof(indvo));
	//populacao->individuos->genes_indv = (genes *)malloc(sizeof(genes));
	//populacao->individuos->genes_indv->notpref = (int *)malloc(sizeof(int)*5);
	
	geraIndividuos(populacao,argv[1]);
	
	//	populacao = (plcao *)malloc(sizeof(plcao));
//	populacao->individuos = (indvo *)malloc(sizeof(indvo)*3);
	return 0;
}