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
*		Implementa jogos de tabuleiro.
*		Podem existir n jogos em operação simultaneamente.
*		As jogos possuem uma cabeça encapsulando o seu estado.
*
*		Cada jogo é homogêneo quanto ao tipo dos dados que armazena.
*		Cada elemento da jogo referencia o valor que contém.
*
*		Os ponteiros para os dados são copiados para elementos da jogo.
*       Não é copiado o valor apontado por estes ponteiros.
*
*		O controle da destruição do valor de um elemento a ser excluído
*       é realizado por uma função fornecida pelo usuário.
*
*		Cada jogo referencia uma função que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A função de liberação dos valores contidos nos elementos deve
*       assegurar a liberação de todos os espaços referênciados pelo
*       valor contido em um elemento.
*       Esta função é chamada antes de se desalocar um elemento
*       de uma jogo.
*       Caso não seja necessário desalocar o valor referenciado pelo
*       elemento, o ponteiro para a função de liberação poderá ser NULL .
*       Caso o elemento da jogo seja a única âncora do valor referenciado,
*       esta função deve promover a destruição (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/
#include "LISTA.H"
#include "TABULEIRO.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma jogo */

typedef struct JGO_tagJogo * JGO_tppJogo;

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condições de retorno
*
*
*  $ED Descrição do tipo
*		Condições de retorno das funções da jogo
*
***********************************************************************/

typedef enum {

	JGO_CondRetOK = 0,
	/* Concluiu corretamente */

	JGO_CondRetNoNaoExiste = 1,
	/* Foi atingido o fim de jogo */

	JGO_CondRetJogoVazia = 2,
	/* A jogo não contém elementos */

	JGO_CondRetJogoNaoExiste = 3,
	/* Jogo não existe*/

	JGO_CondRetNoCorrenteEhUltimo = 4,
	/* Nó corrente é o ultimo elemento da jogo*/

	JGO_CondRetNoCorrenteEhPrimeiro = 5,
	/* Nó corrente é o primeiro elemento da jogo*/

	JGO_CondRetFaltouMemoria = 6,
	/* Faltou memória ao tentar criar um elemento de jogo */
	JGO_CondRetTabuleiroNaoExiste = 7

} JGO_tpCondRet;


/***********************************************************************
*
*  $FC Função: JGO  &Criar jogo
*
*  $ED Descrição da função
*		Cria uma jogo duplamente encadeada.
*		É fornecido um identificador e este é associado à jogo.
*
*  $AS Assertiva de Saida
*		O ponteiro para jogo fornecida como parametro passa a apontar para a jogo criada
*		cujo identificador são os caracteres que foram fornecidos também como parametro.
*		Em caso de falta de memória, o ponteiro apontará para um ponteiro nulo.
*
*  $EP Parâmetros
*		ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*		Se executou corretamente retorna o ponteiro para a jogo e a condição de retorno de movimentação bem sucedida.
*		Este ponteiro será utilizado pelas funções que manipulem esta jogo.
*
*		Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*		a função retornará NULL e a condição de retorno faltou memória.
*		Não será dada mais informação quanto ao problema ocorrido.
*
*  $FV Valor retornado
*		JGO_CondRetOK				- criação de jogo bem sucedida
*		JGO_CondRetFaltouMemoria	- faltou memoria
*
***********************************************************************/

JGO_tpCondRet JGO_CriarJogo(
	void(*ExcluirValor) (char * pDado), char * idJogo, JGO_tppJogo pJogo);

/***********************************************************************
*
*  $FC Função: JGO  &Iniciar Jogo
*
*  $ED Descrição da função
*		Avança o elemento corrente para o próximo elemento na jogo
*		Se existir um próximo elemento, o ponteiro corrente avança.
*		Se não existir um próximo elemento, o ponteiro corrente permanece como ultimo
*		Se nó corrente não existir, a jogo está vazia
*
*  $AE Assertiva de Entrada
*		A jogo existe.
*		A jogo deve ter pelo menos um elemento.
*		Caso contrário, a jogo está vazia.
*		Nó corrente deve apontar para pelo menos um elemento anterior ao último.
*		Caso contrário, nó corrente aponta para último elemento da jogo.
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabeça.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabeça.
*		Nos casos onde há mais de um elemento na jogo e o nó estiver em qualquer posição
*		exceto o último, a movimentação foi bem sucedida.
*		Caso esteja no último elemento ou a jogo apenas possuia um elemento, não houve movimentação
*		e nó é o último elemento da jogo.
*		Caso não possua elementos, a jogo estava vazia e também não houve movimentação.
*
*
*  $EP Parâmetros
*		pJogo  - ponteiro para a jogo a ser manipulada
*		numElem - o número de elementos a andar
*
*  $FV Valor retornado
*		CondRetOK						- movimentação bem sucedida
*		CondRetJogoVazia				- jogo vazia
*		CondRetNoCorrenteEhUltimo		- nó corrente é o último
*
***********************************************************************/

JGO_tpCondRet JGO_IniciarJogo(char * filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Função: JGO  &Finalizar jogo
*
*  $ED Descrição da função
*		Destrói o jogo fornecido.
*		O parâmetro ponteiro para a jogo não é modificado.
*		Se ocorrer algum erro durante a destruição, a jogo resultará
*		estruturalmente incorreta.
*		OBS. não existe previsão para possíveis falhas de execução.
*
*  $AE Assertiva de Entrada
*		O ponteiro para a jogo fornecida como parametro deve conter uma jogo para ser excluida.
*		Caso contrário o ponteiro para jogo não deve ser tratado para destruição.
*
*  $AS Assertiva de Saida
*		A jogo fornecida como parametro se existia, foi destruída. Caso contrário,
*		a jogo já não existe.
*
*  $EP Parâmetros
*		pJogo  - ponteiro para a jogo a ser manipulada
*
*  $FV Valor retornado
*		JGO_CondRetOK				- exclusão OK
*		JGO_CondRetJogoNaExiste	- jogo não existe
*
***********************************************************************/

JGO_tpCondRet JGO_FinalizarJogo(JGO_tppJogo pJogo);

/***********************************************************************
*
*  $FC Função: JGO  &Verifica se o jogo está em check
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a jogo
*
*  $EP Parâmetros
*     pJogo - ponteiro para a jogo a ser esvaziada
*
***********************************************************************/

JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, int * check, char* cor);

/***********************************************************************
*
*  $FC Função: JGO  &Realizar o movimento do jogo no Tabuleiro
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a jogo
*
*  $EP Parâmetros
*     pJogo - ponteiro para a jogo a ser esvaziada
*
***********************************************************************/

JGO_tpCondRet JGO_RealizarMovimento(LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Função: JGO  &Mostrar Tabuleiro padrão
*
*  $ED Descrição da função
*     Apresenta, na tela do jogador, o tabuleiro.
*
*
*  $AE Assertiva de Entrada
*		Um tabuleiro existe.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Será exibido um tabuleiro na tela do jogador.
*       
*
*  $EP Parâmetros
*        ptabuleiro - ponteiro para o tabuleiro do jogo (?PODE SER NULL?)
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
