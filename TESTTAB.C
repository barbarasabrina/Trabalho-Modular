/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste tabuleiro genérico
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bshmc, rfv, llar
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	 5	bshmc,rfv,llar  10/10/2016 implementação do muodulo de tabuleiro
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"
#include	"LISTA.H"



static const char RESET_TABULEIRO_CMD[]		= "=resetteste"			;
static const char CRIAR_TABULEIRO_CMD[]		= "=criarTabuleiro"		;
static const char INSERIR_PECA_CMD[]		= "=inserirPeca"		;
static const char OBTER_PECA_CMD[]			= "=obterPeca"			;
static const char DESTRUIR_TABULEIRO_CMD[]  = "=destroiTabuleiro"	;
static const char ESVAZIAR_TABULEIRO_CMD[]  = "=esvaziarTabuleiro"	;
static const char RETIRAR_PECA_CMD[]		= "=retirarPeca"		;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TABULEIRO   2
#define DIM_CHAR	1
#define DIM_VALOR     100

TAB_tpTabuleiro  vtTabuleiro[DIM_VT_TABULEIRO];

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor(void * pValor);

static int ValidarInxTabuleiro(int inxTabuleiro, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar Tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 10 tabuleiros, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de tabuleiros. Provoca vazamento de memória
*     =criarTabuleiro                   inxTabuleiro	inxTabuleiro	CondRetEsp
*     =destroiTabuleiro					inxTabuleiro	CondRetEsp
*     =esvaziarTabuleiro                inxTabuleiro
*     =irProx							inxTabuleiro	CondRetEsp
*     =excluirelem						inxTabuleiro	CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxTabuleiro = -1,
		numLidos = -1,
		CondRetEsp = -1;

	TST_tpCondRet CondRet;

	char   StringDado[DIM_VALOR];
	char * pDado;
	int	 Linha;
	char	 Coluna[DIM_VALOR];
	int	 LinhaDestino = -1;
	char ColunaDestino[DIM_VALOR];
	int ValEsp = -1;
	void * PecaObtida;
	int i;
	LIS_tppLista pLista;


	int numElem = -1;

	StringDado[0] = 0;


	/* Efetuar reset de teste de tabuleiro */

	if (strcmp(ComandoTeste, RESET_TABULEIRO_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_TABULEIRO; i++)
		{
			vtTabuleiro[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de tabuleiro */
	
	/* Testar Mover peça do tabuleiro */

	else if (strcmp(ComandoTeste, MOVER_PECA_CMD) == 0)
	{

		numLidos = LER_LerParametros("iisisi",
			&inxTabuleiro, &Linha, Coluna, &LinhaDestino, ColunaDestino , &CondRetEsp);

		if (numLidos != 6)
		{
			return TST_CondRetParm;
		} /* if */

		
		CondRet = TAB_MoverPeca(vtTabuleiro[inxTabuleiro],Linha,Coluna[0],LinhaDestino, ColunaDestino[0]);
		
		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar mover a peça.");

	} /* fim ativa: Testar Mover peça do tabuleiro */

	/* Testar CriarTabuleiro */

	else if (strcmp(ComandoTeste, CRIAR_TABULEIRO_CMD) == 0)
	{
		numLidos = LER_LerParametros("iisi",
			&inxTabuleiro, &Linha, Coluna, &CondRetEsp);

		if ((numLidos != 4)
			|| (!ValidarInxTabuleiro(inxTabuleiro, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtTabuleiro[inxTabuleiro] = TAB_AlocarTabuleiro(Linha, Coluna[0]);

		CondRet = TAB_CriarTabuleiro(vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao criar tabuleiro.");

	} /* fim ativa: Testar CriarTabuleiro */

	/* Testar Inserir peça no tabuleiro */

	else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
	{

		numLidos = LER_LerParametros("iissi",
			&inxTabuleiro, &Linha, Coluna, StringDado, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = TAB_InserirPeca(vtTabuleiro[inxTabuleiro], Linha, Coluna[0], StringDado);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar inserir uma peça no tabuleiro.");

	} /* fim ativa: Testar destruir tabuleiro */

	else if (strcmp(ComandoTeste, DESTRUIR_TABULEIRO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxTabuleiro, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} /* if */


		CondRet = TAB_DestruirTabuleiro(&vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar destruir tabuleiro.");

	} /* fim ativa: Testar destruir tabuleiro */

	/* Testar Obter peça do tabuleiro */

	else if (strcmp(ComandoTeste, OBTER_PECA_CMD) == 0)
	{
		numLidos = LER_LerParametros("iissi",
			&inxTabuleiro, &Linha, Coluna, StringDado, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */
		
		PecaObtida = (char*)malloc(sizeof(char));
		
		CondRet = TAB_ObterPeca(vtTabuleiro[inxTabuleiro], Linha, Coluna[0], &PecaObtida);
		
		if (CondRet == 0)
		{
			return TST_CompararChar(StringDado[0], PecaObtida,
					"Condicao de retorno errada tentar obter peca");			
		}

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar obter peca");

	} /* fim ativa: Testar Obter peça do tabuleiro */
	
	/* Testar Obter ameaçados */

	else if (strcmp(ComandoTeste, OBTER_AMEACADOS_CMD) == 0)
	{

		numLidos = LER_LerParametros("iissi",
			&inxTabuleiro, &Linha, Coluna, StringDado, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = TAB_ObterListaAmeacados(vtTabuleiro[inxTabuleiro], Linha, Coluna[0], &pLista);
		
		if (CondRet!=0)
			return CondRet;
		

		pDado = (char *)malloc(strlen(StringDado) + 1);
		strcpy(pDado, StringDado);

		CondRet = LIS_idLista(pLista, &pDado);

	

		if(CondRet == 0)
		{
			return TST_CompararString(StringDado , pDado,
					"Valor retornado nâo foi esperado");
		}

		return TST_CompararInt(CondRetEsp, CondRet,
		"Condicao de retorno errada ao Obter Lista de Ameaçados");

	} /* fim ativa: Testar Obter ameaçados */

	/* Testar Obter ameaçantes */

	else if (strcmp(ComandoTeste, OBTER_AMEACANTES_CMD) == 0)
	{

		numLidos = LER_LerParametros("iissi",
			&inxTabuleiro, &Linha, Coluna, StringDado, &CondRetEsp);

		if (numLidos != 5)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = TAB_ObterListaAmeacantes(vtTabuleiro[inxTabuleiro], Linha, Coluna[0], &pLista);
		if (CondRet!=0)
			return CondRet;


		pDado = (char *)malloc(strlen(StringDado) + 1);
		strcpy(pDado, StringDado);

		CondRet = LIS_idLista(pLista, &pDado);

		if(CondRet == 0)
		{
			return TST_CompararString(StringDado , pDado,
					"Valor retornado nâo foi esperado");
		}

		return TST_CompararInt(CondRetEsp, CondRet,
		"Condicao de retorno errada ao Obter Lista de Ameaçantes");

	} /* fim ativa: Testar Obter ameaçantes */


	/* Testar Retirar peça do tabuleiro */

	else if (strcmp(ComandoTeste, RETIRAR_PECA_CMD) == 0)
	{

		numLidos = LER_LerParametros("iisi",
			&inxTabuleiro, &Linha, Coluna, &CondRetEsp);

		if (numLidos != 4)
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp, TAB_RetirarPeca(vtTabuleiro[inxTabuleiro], Linha, Coluna[0]),
			"Condicao de retorno errada ao retirar peca");

	} /* fim ativa: Testar Retirar peça do tabuleiro */



	return TST_CondRetNaoConhec;

} /* Fim função: TLIS &Testar tabuleiro */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB -Destruir valor
*
***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim função: TTAB -Destruir valor */


/***********************************************************************
*
*  $FC Função: TTAB -Validar indice de tabuleiro
*
***********************************************************************/

int ValidarInxTabuleiro(int inxTabuleiro, int Modo)
{

	if ((inxTabuleiro < 0)
		|| (inxTabuleiro >= DIM_VT_TABULEIRO))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtTabuleiro[inxTabuleiro] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtTabuleiro[inxTabuleiro] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TTAB -Validar indice de tabuleiro */

/********** Fim do módulo de implementação: TTAB Teste tabuleiro genérico **********/

