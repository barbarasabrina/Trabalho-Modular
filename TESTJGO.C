/***************************************************************************
*  $MCI Módulo de implementação: TJGO Teste Jogo
*
*  Arquivo gerado:              TESTJGO.c
*  Letras identificadoras:      TJGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\JOGO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bshmc, rfv, llar
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	 5	bshmc,rfv,llar  10/10/2016 implementação do muodulo de jogo
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

#include    "TABULEIRO.H"
#include	"JOGO.H"
#include	"LISTA.H"
#include	"PECA.H"


static const char RESET_JOGO_CMD[] = "=resetteste";
static const char INICIAR_JOGO_CMD[] = "=iniciarJogo";
static const char MOSTRAR_TABULEIRO_CMD[] = "=mostrarTabuleiro";
static const char REALIZAR_MOVIMENTO_CMD[] = "=realizarMovimento";
static const char FINALIZAR_JOGO_CMD[] = "=finalizarJogo";
static const char VERIFICAR_CHECK_CMD[] = "=verificarCheck";



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

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor(void * pValor);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar Jogo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 jogos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de jogos. Provoca vazamento de memória
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

		CondRet = JGO_MostrarTabuleiro(vtTabuleiro[inxTabuleiro]);

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
			"Condicao de retorno errada ao tentar verificar se o jogo está em check/check mate.");

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

} /* Fim função: TLIS &Testar jogo */


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


/********** Fim do módulo de implementação: TTAB Teste jogo  **********/

