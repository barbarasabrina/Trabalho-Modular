/***************************************************************************
*  $MCI Módulo de implementação: TPCA Teste Pecas de tabuleiro
*
*  Arquivo gerado:              TestPCA.c
*  Letras identificadoras:      TPCA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       llar  16/nov/2016 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Peca.h"

static const char INICIALIZAR_PECAS_CMD  [ ] = "=inicializarPecas"	;
static const char PEGAR_PECA_CMD         [ ] = "=pegarPecaDoVetor"	;
static const char OBTER_COR_CMD          [ ] = "=obterCor"			;
static const char OBTER_NOME_CMD         [ ] = "=obterNome"			;
static const char VALIDAR_MOVIMENTO_CMD  [ ] = "=validarMovimento"	;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VALOR 100


PCA_tpPeca PecaCorrente = NULL;

PCA_tpVetPeca VetPecasPossiveis = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPCA &Testar peca
*
*  $ED Descrição da função
*     Testa os métodos utilizando o arquivo "PecasPossiveis.txt" 
*
*     Comandos disponíveis:
*
*     =inicializarPecas
*     =pegarPecaDoVetor
*     =obterCor
*     =obterNome
*     =validarMovimento
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	FILE* aux = fopen("resultados.txt", "w");

	int numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet ;

	char StringDado [DIM_VALOR], *pDado ;
	char	nomeDado, nomeRecebido ,
			corDada,  corRecebida  ;

	int dx, dy, atk;

	int ValEsp = -1 ;

	int numElem = -1 ;



	/* Testar Inicializar Pecas */

	if ( strcmp( ComandoTeste , INICIALIZAR_PECAS_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "si" ,
			StringDado, &CondRetEsp ) ;

		if ( numLidos != 2 )
		{
			return TST_CondRetParm ;
		} /* if */

		pDado = (char *)malloc(strlen(StringDado) + 1);

		if (pDado == NULL)
		{
			return TST_CondRetMemoria;
		} /* if */

		strcpy(pDado, StringDado);

		CondRet = PCA_InicializarPecas(pDado, &VetPecasPossiveis);

		free(pDado);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao inicializar pecas.");

	} /* fim ativa: Testar InicializarPecas */

	/* Testar pegar peca do vetor*/

	else if ( strcmp( ComandoTeste , PEGAR_PECA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "cci" ,
			 &nomeDado, &corDada, &CondRetEsp) ;

		if ( numLidos != 3 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = PCA_PegarPecaDoVetor (VetPecasPossiveis ,&PecaCorrente, nomeDado, corDada);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao obter peca.");

	} /* fim ativa: Testar Obter Peca */

	/* Testar Obter Cor */

	else if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ci" ,
			&corDada, &CondRetEsp ) ;

		if  ( numLidos != 2 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = PCA_ObterCor (PecaCorrente, &corRecebida) ;

		if (CondRet != 0)
			return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao obter cor da peca");

		return TST_CompararChar(corDada, corRecebida,
			"Cor recebida diferente da cor dada.");;

	} /* fim ativa: Obter Cor */

	/* Testar Obter Nome */

	else if ( strcmp( ComandoTeste , OBTER_NOME_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ci" ,
			&nomeDado, &CondRetEsp ) ;

		if  ( numLidos != 2 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = PCA_ObterCor (PecaCorrente, &nomeRecebido) ;

		if (CondRet != 0)
			return TST_CompararInt(CondRetEsp, CondRet, "Condicao de retorno errada ao obter nome da peca");

		return TST_CompararChar(nomeDado, nomeRecebido,
			"Nome recebido diferente do nome dado.");;

	} /* fim ativa: Obter Nome */

	/* Testar Validar Movimento */

	else if ( strcmp( ComandoTeste , VALIDAR_MOVIMENTO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "iiii" ,
			&dx , &dy, &atk, &CondRetEsp ) ;

		if ( numLidos != 3 )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = PCA_ValidarMovimento(PecaCorrente, dx, dy, atk) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
			"Condicao de retorno errada ao validar movimento."                   ) ;

	} /* fim ativa: Testar validar movimento */

	return TST_CondRetNaoConhec ;

} /* Fim função: TLIS &Testar peca */


/*****  Código das funções encapsuladas no módulo  *****/


/********** Fim do módulo de implementação: TPCA Teste peca **********/
