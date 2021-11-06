/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <Turma 04> - Prof. Luciano Antonio Digiampietri               **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   <Elivelton Cruz de Santana>                   <7652592>       **/
/**                                                                 **/
/*********************************************************************/
#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}





bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
	int x;
	PONT atual;
	if (buscarID(l,id)!=NULL || tipo<0 ||tipo>=NUMTIPOS ||id<0 || quantidade <0 ||valor <0 ){
			return false;
	}
	if (l->LISTADELISTAS[tipo]->proxProd==NULL){
		l->LISTADELISTAS[tipo]->proxProd=(PONT) malloc(sizeof(REGISTRO));
    	l->LISTADELISTAS[tipo]->proxProd->id=id;
    	l->LISTADELISTAS[tipo]->proxProd->quantidade=quantidade;
    	l->LISTADELISTAS[tipo]->proxProd->valorUnitario=valor;
    	l->LISTADELISTAS[tipo]->proxProd->proxProd=NULL;
    	return true;
		}		
		else if ( (l->LISTADELISTAS[tipo]->proxProd->quantidade * l->LISTADELISTAS[tipo]->proxProd->valorUnitario) >= (valor *  quantidade)){
			
			atual = l->LISTADELISTAS[tipo]->proxProd;
			l->LISTADELISTAS[tipo]->proxProd=(PONT) malloc(sizeof(REGISTRO));
    		l->LISTADELISTAS[tipo]->proxProd->id=id;
    		l->LISTADELISTAS[tipo]->proxProd->quantidade=quantidade;
    		l->LISTADELISTAS[tipo]->proxProd->valorUnitario=valor;
    		l->LISTADELISTAS[tipo]->proxProd->proxProd=atual;
    		return true;
    		
			}
			else     {		
				atual=l->LISTADELISTAS[tipo]->proxProd;
				while( (atual->quantidade * atual->valorUnitario)>(quantidade * valor) && (atual->proxProd != NULL) && (atual->proxProd->quantidade * atual->proxProd->valorUnitario)!=(valor * quantidade)){
					 atual = atual->proxProd;
				}	
					PONT temp;
					temp=atual->proxProd;
					atual->proxProd = (PONT) malloc(sizeof(REGISTRO));
					atual->proxProd->id=id;
					atual->proxProd->quantidade=quantidade;
					atual->proxProd->valorUnitario=valor;
					atual->proxProd->proxProd=temp;
				}
				
		

  return true;
}



bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
	if (buscarID(l,id)==NULL || quantidade <= 0 || buscarID(l, id)->quantidade < quantidade ){
		return false;	
		
	}
	PONT atual;
	atual = buscarID(l, id);
	atual->quantidade= atual->quantidade - quantidade;
	PONT temp;
	PONT temp2;
	int x;	
	
	if(atual->quantidade == 0){ 			
		temp=atual->proxProd;		
		for (x=0; x<NUMTIPOS ;x++){	
				if (l->LISTADELISTAS[x]->proxProd == atual){
				l->LISTADELISTAS[x]->proxProd=temp;
				free (atual);
				return true;
			}
			temp2 = l->LISTADELISTAS[x]->proxProd;
    		while (temp2) {
    			if(temp2->proxProd->id==id){
    				temp2->proxProd=temp;
    				free(atual);
					return true;	
				}
      			temp2 = temp2->proxProd;
        	}
		
		}
	}
	
	else {
		
		int idt, valort, quantidadet;
		idt= atual->id;
		valort= atual->valorUnitario;
		quantidadet= atual->quantidade;
		temp=atual->proxProd;	
		
		for (x=0; x<NUMTIPOS ;x++){	
			
				if (l->LISTADELISTAS[x]->proxProd == atual){
				l->LISTADELISTAS[x]->proxProd=temp;
				
				free (atual);
				inserirNovoProduto(l, idt, x, quantidadet, valort);
				
				return true;
			}
			 
			temp2 = l->LISTADELISTAS[x]->proxProd;
    		while (temp2) {
    			if(temp2->proxProd==atual){
    				temp2->proxProd=temp;
    				free(atual);
    				inserirNovoProduto(l, idt, x, quantidadet, valort);
					return true;	
				}
      			temp2 = temp2->proxProd;
        	}
		
		}
				
		
	}
 

  return true;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){
	if (buscarID(l,id)==NULL || valor <= 0 ){
		return false;	
		
	}
	PONT atual;
	atual = buscarID(l, id);
	atual->valorUnitario = valor;
	PONT temp;
	PONT temp2;
	int x;	
	
	int idt, valort, quantidadet;
		idt= atual->id;
		valort= atual->valorUnitario;
		quantidadet= atual->quantidade;
		temp=atual->proxProd;	
		
		for (x=0; x<NUMTIPOS ;x++){	
			
				if (l->LISTADELISTAS[x]->proxProd == atual){
				l->LISTADELISTAS[x]->proxProd=temp;
				
				free (atual);
				inserirNovoProduto(l, idt, x, quantidadet, valort);
				
				return true;
			}
			
			temp2 = l->LISTADELISTAS[x]->proxProd;
    		while (temp2) {
    			if(temp2->proxProd==atual){
    				temp2->proxProd=temp;
    				free(atual);
    				inserirNovoProduto(l, idt, x, quantidadet, valort);
					return true;	
				}
      			temp2 = temp2->proxProd;
        	}
		
		}
		

  
  return false;
}
