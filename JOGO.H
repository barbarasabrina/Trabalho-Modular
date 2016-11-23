#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: JGO  Jogo
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\JOGO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs , rfv, bshmc, llar
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*   5     bshmc,rfv,llar 10/10/2016		modificações do modulo de jogo
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*		Implementa um jogo de xadrez num tabuleiro 8x8.
*		Este tabuleiro possui 64 casas.
*		Sendo as linhas representadas por números de 1-8.
*		E as colunas representadas por caracteres de A-H.
*		A contagem para as coordenadas começa na posição linha 1 coluna A,
*		que será representada exatamente na parte inferior esquerda, sendo assim,
*		a posição linha 8 coluna H será representada na parte superior direita.
*
*
***************************************************************************/
#include "LISTA.H"
#include "TABULEIRO.H"
#include "PECA.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condições de retorno de um jogo
*
*
*  $ED Descrição do tipo
*		Condições de retorno das funções do jogo
*
***********************************************************************/

typedef enum {

	JGO_CondRetOK = 0,
	/* Concluiu corretamente */

	JGO_CondRetNoNaoExiste = 1,
	/* Tabuleiro não existe */

	JGO_CondRetListaVazia = 2,
	/* A lista está vazia */

	JGO_CondRetTabuleiroNaoExiste = 3,
	/* Tabuleiro não existe*/

	JGO_CondRetListaNaoExiste = 4,
	/* Lista não existe */

	JGO_CondRetNoCorrenteEhPrimeiro = 5,
	/* Nó corrente é o primeiro elemento da jogo*/

	JGO_CondRetFaltouMemoria = 6
	/* Faltou memória ao tentar criar um elemento de jogo */

} JGO_tpCondRet;

/***********************************************************************
*
*  $FC Função: JGO  &Iniciar Jogo
*
*  $ED Descrição da função
*		Dá inicio ao jogo, criando o tabuleiro e posicionando as peças nas casas corretamente.
*
*
*  $AE Assertiva de Entrada
*		Nó corrente deve apontar para pelo menos um elemento anterior ao último.
*		Caso contrário, nó corrente aponta para último elemento da jogo.
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabeça.
*
*  $AS Assertiva de Saida
*		Valem as assertivas de tabuleiro e de lista duplamente encadeada.
*		Uma lista de peças disponíveis estará disponível para o jogador.
*		Um arquivo com as peças e seus movimentos será disponibilizado pelo parametro filename.
*		Um tabuleiro estará preenchido para iniciar o jogo.
*
*
*  $EP Parâmetros
*		filename						- nome do arquivo que contém as informações das peças e seus movimentos.
*		listaPecasPossiveis				- vetor com as peças disponíveis para o jogo.
*		pTabuleiro						- ponteiro para o tabuleiro do jogo
*
*  $FV Valor retornado
*		CondRetOK						- movimentação bem sucedida
*		CondRetJogoVazia				- jogo vazia
*		CondRetNoCorrenteEhUltimo		- nó corrente é o último
*
***********************************************************************/

JGO_tpCondRet JGO_IniciarJogo(char * filename, PCA_tpVetPeca listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Função: JGO  &Finalizar jogo
*
*  $ED Descrição da função
*		Finaliza o jogo de tabuleiro.
*		O parâmetro ponteiro para o tabuleiro não é modificado.
*		Se ocorrer algum erro durante a destruição, o tabuleiro resultará
*		estruturalmente incorreto.
*		OBS. não existe previsão para possíveis falhas de execução.
*
*  $AE Assertiva de Entrada
*		Pode existir um tabuleiro.
*		Caso contrário o ponteiro para jogo não deve ser tratado para destruição.
*
*  $AS Assertiva de Saida
*		As peças e casa do tabuleiro são liberados e o tabuleiro destruído.
*
*  $EP Parâmetros
*		ptabuleiro  - ponteiro para o tabuleiro a ser manipulado
*
*  $FV Valor retornado
*		JGO_CondRetOK				- exclusão OK
*		JGO_CondRetJogoNaExiste	- jogo não existe
*
***********************************************************************/

JGO_tpCondRet JGO_FinalizarJogo(TAB_tpTabuleiro ptabuleiro);

/***********************************************************************
*
*  $FC Função: JGO  &Verifica se o jogo está em check
*
*  $ED Descrição da função
*     Verifica se o jogo está check ou check mate.
*
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro válido.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Será obtida informação de check(1), check mate(2) ou nulo(0) em relação ao estado do jogo.
*
*
*  $EP Parâmetros
*		pTabuleiro			- ponteiro para o tabuleiro
*		check				- ponteiro para informação de check(1), check mate(2) ou nulo(0)
*
***********************************************************************/

JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, int * check);

/***********************************************************************
*
*  $FC Função: JGO  &Realizar o movimento do jogo no Tabuleiro
*
*  $ED Descrição da função
*     O módulo de jogo irá obter do jogador informação do movimento que ele deseja e
*	  realizar o movimento caso o movimento seja válido.
*
*
*  $AE Assertiva de Entrada
*		Deve existir uma lista de peças disponíveis no jogo.
*		Deve existir um tabuleiro válido.
*		Valem as assertivas estruturais de tabuleiro e de lista.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro e de lista.
*		Um movimento pode ser ou não realizado.
*
*
*  $EP Parâmetros
*		listaPecasDisponiveis	- vetor com as peças disponíveis
*		pTabuleiro				- ponteiro para o tabuleiro do jogo
*
***********************************************************************/

JGO_tpCondRet JGO_RealizarMovimento(PCA_tpVetPeca listaPecasDisponiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Função: JGO  &Mostrar Tabuleiro padrão
*
*  $ED Descrição da função
*     Apresenta, na tela do jogador, o estado atual do tabuleiro do jogo.
*
*
*  $AE Assertiva de Entrada
*		Ou tabuleiro existe ou é nulo.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Pode ou não ser exibido um tabuleiro na tela do jogador.
*
*
*  $EP Parâmetros
*        ptabuleiro - ponteiro para o tabuleiro do jogo.
*
*
*  $FV Valor retornado
*		JGO_CondRetOK					- apresentação bem sucedida
*		JGO_CondRetNaoExisteTabuleiro	- não existe tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_MostrarTabuleiro(TAB_tpTabuleiro ptabuleiro);


#undef JOGO_EXT

/********** Fim do módulo de definição: JGO  Jogo de tabuleiro **********/

#else
#endif
