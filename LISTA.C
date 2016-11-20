/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: BSHMC, RFV, LLAR, AVS
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5BSHMC,RFV,LLAR 10/10/2016	modificação dos modulos de lista
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

	char * pValor;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx;
	/* Ponteiro para o elemento sucessor */

} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr;
	/* Ponteiro para o elemento corrente da lista */

	int numElem;
	/* Número de elementos da lista */

	char * idLista;
	/* Caracteres que identificam a lista */

	void(*ExcluirValor) (char * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} LIS_tpLista;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,
	char *       pValor);

static void LimparCabeca(LIS_tppLista pLista);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

LIS_tpCondRet LIS_CriarLista(void(*ExcluirValor)(char * pValor),
	char * idLista, LIS_tppLista pLista)
{
	if (pLista == NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */

	LimparCabeca(pLista);

	pLista->ExcluirValor = ExcluirValor;

	pLista->idLista = (char *)malloc(sizeof(idLista) + 1);

	strcpy(pLista->idLista, idLista);

	return LIS_CondRetOK;

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Obter ID da Lista
*
*  ************************************************************************/

LIS_tpCondRet LIS_idLista(LIS_tppLista pLista, void** pvalor)
{
	if (pLista == NULL)
		return LIS_CondRetListaNaoExiste;
	*pvalor = pLista->idLista;
	return LIS_CondRetOK;
}

/* Fim função: LIS  &Obter ID da Lista */

/***************************************************************************
*
*  Função: LIS  &Obter No da lista
*
*  ************************************************************************/

LIS_tpCondRet LIS_ObterNo(LIS_tppLista pLista, void** pvalor)
{
	if (pLista->pOrigemLista == NULL)
		return LIS_CondRetListaVazia;
	if (pLista->pElemCorr==NULL)
		return LIS_CondRetNoNaoExiste;

	*pvalor=pLista->pElemCorr->pValor;
	return LIS_CondRetOK;
} /* Fim função: LIS  &Obter No da Lista */

/***************************************************************************
*
*  Função: LIS  &Ir Elemento anterior
*
*  ************************************************************************/

LIS_tpCondRet LIS_irAnt (LIS_tppLista pLista)
{
	if (pLista->pOrigemLista == NULL)
		return LIS_CondRetListaVazia;
	else if (pLista->pElemCorr->pAnt == NULL)
		return LIS_CondRetNoCorrenteEhPrimeiro;
	else if(pLista->pElemCorr = pLista->pElemCorr->pAnt){
		return LIS_CondRetOK;
	}
	return LIS_CondRetListaVazia;
} /* Fim função: LIS  &Ir Elemento Anterior */
/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*
*  ************************************************************************/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */
   
/*************************************************************************** Testar
*
*  Função: LIS  &Inserir nó
*  ****/

LIS_tpCondRet LIS_InserirNo( LIS_tppLista pLista ,
	void * pValor        )
{

	tpElemLista * pElem ;


	/* Criar elemento a inserir após */

	pElem = CriarElemento(pLista, pValor);
	if (pElem==NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */


	/* Encadear o novo elemento após o elemento corrente */

	if ( pLista->pElemCorr == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		if ( pLista->pElemCorr->pProx != NULL )
		{
			pElem->pProx  = pLista->pElemCorr->pProx ;
			pLista->pElemCorr->pProx->pAnt = pElem ;
		} else
		{
			pLista->pFimLista = pElem ;
		} /* if */
		pElem->pAnt = pLista->pElemCorr ;
		pLista->pElemCorr->pProx = pElem ;

	} /* if */

	pLista->pElemCorr = pElem ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Inserir elemento após */

/*************************************************************************** Testar
*
*  Função: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
{

	tpElemLista * pElem ;

#ifdef _DEBUG
	assert( pLista  != NULL ) ;
#endif

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pElemCorr ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx   = pElem->pProx ;
		pLista->pElemCorr    = pElem->pAnt ;
	} else {
		pLista->pElemCorr    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pElemCorr ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */

	LiberarElemento( pLista , pElem ) ;

	return LIS_CondRetOK ;

} /* Fim função: LIS  &Excluir elemento */

/*************************************************************************** Testar
*
*  Função: LIS  &Alterar nó corrente
*  ****/

LIS_tpCondRet LIS_AlterarNoCorrente( LIS_tppLista pLista , void * nValor)
{

	if ( pLista == NULL )
	{
		return LIS_CondRetListaNaoExiste;
	} /* if */

	if ( pLista->pElemCorr == NULL )
	{
		return LIS_CondRetListaVazia ;
	} /* if */

	pLista->pElemCorr->pValor=nValor;
	return LIS_CondRetOK;
	
} /* Fim função: LIS  &Alterar nó corrente */


/***************************************************************************
*
*	Função: LIS &Ir Próximo elemento
*	*****/

LIS_tpCondRet LIS_IrProximoElemento(LIS_tppLista pLista)
{
	tpElemLista * pElem;
#ifdef _DEBUG
	assert(pLista != NULL);
#endif
	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	}

	/* Tratar lista vazia */
	pElem = pLista->pElemCorr;
	if (pElem == NULL)
	{
		return LIS_CondRetListaVazia;
	} /* fim ativa: Tratar lista vazia */

	pElem = pElem->pProx;

	if (pElem != NULL)
	{
		pLista->pElemCorr = pElem;
		return LIS_CondRetOK;
	} /* if */

	pLista->pElemCorr = pLista->pFimLista;
	return LIS_CondRetNoCorrenteEhUltimo;

} /* Fim função: LIS &Ir Próximo elemento */


/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista)
{

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	}
	
	LIS_EsvaziarLista(pLista);
	
	free(pLista);

	return LIS_CondRetOK;
} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Alocar lista
*  ****/

LIS_tppLista LIS_AlocarLista()
{
	LIS_tppLista plista = (LIS_tppLista)malloc(sizeof(LIS_tpLista));
	return plista;
} /* Fim função: LIS  &Alocar lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista(LIS_tppLista pLista)
{

	tpElemLista * pElem;
	tpElemLista * pProx;

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

	pElem = pLista->pOrigemLista;
	while (pElem != NULL)
	{
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */

	LimparCabeca(pLista);

} /* Fim função: LIS  &Esvaziar lista */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem)
{

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	free(pElem);

	pLista->numElem--;

} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista,
	char *       pValor)
{

	tpElemLista * pElem;

	pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		return NULL;
	} /* if */

	pElem->pValor = pValor;
	pElem->pAnt = NULL;
	pElem->pProx = NULL;

	pLista->numElem++;

	return pElem;

} /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{

	pLista->pOrigemLista = NULL;
	pLista->pFimLista = NULL;
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;
	pLista->idLista = NULL;

} /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

