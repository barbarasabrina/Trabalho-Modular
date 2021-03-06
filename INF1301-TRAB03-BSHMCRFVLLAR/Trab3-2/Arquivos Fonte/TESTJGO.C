/***************************************************************************
*  $MCI M�dulo de implementa��o: TJGO Teste Jogo
*
*  Arquivo gerado:              TESTJGO.c
*  Letras identificadoras:      TJGO
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\JOGO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bshmc, rfv, llar
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	 5	bshmc,rfv,llar  10/10/2016 implementa��o do muodulo de jogo
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "TABULEIRO.H"
#include	"JOGO.H"
#include	"LISTA.H"
#include	"PECA.H"


static const char RESET_JOGO_CMD[]			= "=resetteste";
static const char INICIAR_JOGO_CMD[]		= "=iniciarJogo";
static const char MOSTRAR_TABULEIRO_CMD[]	= "=mostrarTabuleiro";
static const char REALIZAR_MOVIMENTO_CMD[]	= "=realizarMovimento";
static const char FINALIZAR_JOGO_CMD[]		= "=finalizarJogo";
static const char VERIFICAR_CHECK_CMD[]		= "=verificarCheck";



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_CHAR			1
#define DIM_VT_LISTA		2
#define DIM_VT_TABULEIRO	2
#define DIM_VALOR			100

PCA_tpVetPeca vtLista[DIM_VT_LISTA];

TAB_tpTabuleiro vtTabuleiro[DIM_VT_TABULEIRO];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void DestruirValor(void * pValor);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar Jogo
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 jogos, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de jogos. Provoca vazamento de mem�ria
*     =criarJogo                   inxJogo	inxJogo	CondRetEsp
*     =destroiJogo					inxJogo	CondRetEsp
*     =esvaziarJogo                inxJogo
*     =irProx							inxJogo	CondRetEsp
*     =excluirelem						inxJogo	CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int inxJogo = -1,
		inxLista = -1,
		inxTabuleiro = -1,
		numLidos = -1,
		CondRetEsp = -1,
		CondRet = -1,
		check = -1;


	char StringDado[DIM_VALOR];
	char * pDado;
	int	 Linha;
	char StringObtido[DIM_VALOR];
	int ValEsp = -1;
	int i;
	LIS_tppLista pLista;


	int numElem = -1;

	StringDado[0] = 0;

	StringObtido[0] = 0;

	/* Efetuar reset de teste de jogo */

	if (strcmp(ComandoTeste, RESET_JOGO_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_TABULEIRO; i++)
		{
			vtTabuleiro[i] = NULL;
			
		} /* for */

		for (i = 0; i < DIM_VT_LISTA; i++)
		{
			vtLista[i] = NULL;

		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de jogo */

	/* Testar Iniciar Jogo */

	else if (strcmp(ComandoTeste, INICIAR_JOGO_CMD) == 0)
	{
		numLidos = LER_LerParametros("siii",
			StringDado, &inxLista, &inxTabuleiro, &CondRetEsp);

		if (numLidos != 4)
		{
			return TST_CondRetParm;
		} /* if */

		
		vtTabuleiro[inxTabuleiro] = TAB_AlocarTabuleiro(8, 'H');

		CondRet = JGO_IniciarJogo(StringDado, vtLista[inxLista], &vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao Iniciar Jogo.");

	} /* fim ativa: Testar Iniciar Jogo */

	/* Testar Mostrar tabuleiro do jogo */

	else if (strcmp(ComandoTeste, MOSTRAR_TABULEIRO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxTabuleiro, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} /* if */

		CondRet = JGO_MostrarTabuleiro(&vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar mostrat o tabuleiro do jogo.");

	} /* fim ativa: Testar Mostrar tabuleiro do jogo */


	/* Testar finalizar jogo */

	else if (strcmp(ComandoTeste, FINALIZAR_JOGO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&inxTabuleiro, &CondRetEsp);

		if (numLidos != 2)
		{
			return TST_CondRetParm;
		} /* if */


		CondRet = JGO_FinalizarJogo(&vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar finalizar o jogo.");

	} /* fim ativa: Testar finalizar jogo */

	/* Testar verificar check em jogo */

	else if (strcmp(ComandoTeste, VERIFICAR_CHECK_CMD) == 0)
	{
		int checkRecebido = -1;
		numLidos = LER_LerParametros("iii",
			&inxTabuleiro, &check, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */

		/*pDado = (char*)malloc(sizeof(StringDado));*/


		CondRet = JGO_VerificaCheck(vtTabuleiro[inxTabuleiro], &checkRecebido);

		if (CondRet == 0)
		{
			return TST_CompararInt(check, checkRecebido,
				"Condicao de retorno errada tentar obter o check/check mate do jogo");
		}

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar verificar se o jogo est� em check/check mate.");

	} /* fim ativa: Testar vrificar check em jogo */

	/* Testar Realizar movimento do jogo */

	else if (strcmp(ComandoTeste, REALIZAR_MOVIMENTO_CMD) == 0)
	{
		numLidos = LER_LerParametros("iii",
			&inxLista, &inxTabuleiro, &CondRetEsp);

		if (numLidos != 3)
		{
			return TST_CondRetParm;
		} /* if */


		CondRet = JGO_RealizarMovimento(vtLista[inxLista], vtTabuleiro[inxTabuleiro]);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao tentar realizar o movimento no jogo");

	} /* fim ativa: Testar Realizar movimento do jogo */


	return TST_CondRetNaoConhec;

} /* Fim fun��o: TLIS &Testar jogo */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TTAB -Destruir valor
*
***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim fun��o: TTAB -Destruir valor */


/********** Fim do m�dulo de implementa��o: TTAB Teste jogo  **********/

