#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
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
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*		Implementa listas genéricas duplamente encadeadas.
*		Podem existir n listas em operação simultaneamente.
*		As listas possuem uma cabeça encapsulando o seu estado.
*
*		Cada lista é homogênea quanto ao tipo dos dados que armazena.
*		Cada elemento da lista referencia o valor que contém.
*
*		Os ponteiros para os dados são copiados para elementos da lista.
*       Não é copiado o valor apontado por estes ponteiros.
*
*		O controle da destruição do valor de um elemento a ser excluído
*       é realizado por uma função fornecida pelo usuário.
*
*		Cada lista referencia uma função que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A função de liberação dos valores contidos nos elementos deve
*       assegurar a liberação de todos os espaços referênciados pelo
*       valor contido em um elemento.
*       Esta função é chamada antes de se desalocar um elemento
*       de uma lista.
*       Caso não seja necessário desalocar o valor referenciado pelo
*       elemento, o ponteiro para a função de liberação poderá ser NULL .
*       Caso o elemento da lista seja a única âncora do valor referenciado,
*       esta função deve promover a destruição (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*		Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetNoNaoExiste = 1,
               /* Nó não existe na lista */

		 LIS_CondRetListaVazia = 2,
			  /* A lista não contém elementos */

         LIS_CondRetListaNaoExiste = 3,
               /* Lista não existe*/

		 LIS_CondRetNoCorrenteEhUltimo = 4,
				/* Nó corrente é o ultimo elemento da lista*/
		
		 LIS_CondRetNoCorrenteEhPrimeiro = 5,
				/* Nó corrente é o primeiro elemento da lista*/

         LIS_CondRetFaltouMemoria = 6
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*		Cria uma lista genérica duplamente encadeada.
*		Os possíveis tipos são desconhecidos a priori.
*		A tipagem é implicita.
*		Não existe identificador de tipo associado à lista.
*
*  $AS Assertiva de Saida
*		O ponteiro para lista fornecida como parametro passa a apontar para a lista criada 
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
*		Se executou corretamente retorna o ponteiro para a lista.
*		Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*		Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*		a função retornará NULL.
*		Não será dada mais informação quanto ao problema ocorrido.
*
*  $FV Valor retornado
*		LIS_CondRetOK				- criação de lista bem sucedida
*		LIS_CondRetFaltouMemoria	- faltou memoria
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(
	   void(*ExcluirValor) (char * pDado), char * idLista, LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Ir próximo elemento
*
*  $ED Descrição da função
*		Avança o elemento corrente para o próximo elemento na lista
*		Se existir um próximo elemento, o ponteiro corrente avança.
*		Se não existir um próximo elemento, o ponteiro corrente permanece como ultimo
*		Se nó corrente não existir, a lista está vazia
*
*  $AE Assertiva de Entrada
*		A lista existe. 
*		A lista deve ter pelo menos um elemento. 
*		Caso contrário, a lista está vazia.
*		Nó corrente deve apontar para pelo menos um elemento anterior ao último.
*		Caso contrário, nó corrente aponta para último elemento da lista.
*		Valem as assertivas estruturais de lista duplamente encadeada com cabeça.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de lista duplamente encadeada com cabeça.		
*		Nos casos onde há mais de um elemento na lista e o nó estiver em qualquer posição 
*		exceto o último, a movimentação foi bem sucedida.
*		Caso esteja no último elemento ou a lista apenas possuia um elemento, não houve movimentação
*		e nó é o último elemento da lista.
*		Caso não possua elementos, a lista estava vazia e também não houve movimentação.
*
*
*  $EP Parâmetros
*		pLista  - ponteiro para a lista a ser manipulada
*		numElem - o número de elementos a andar
*
*  $FV Valor retornado
*		CondRetOK						- movimentação bem sucedida
*		CondRetListaVazia				- lista vazia
*		CondRetNoCorrenteEhUltimo		- nó corrente é o último
*
***********************************************************************/

   LIS_tpCondRet LIS_IrProximoElemento(LIS_tppLista pLista);

   
/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*		Destrói a lista fornecida.
*		O parâmetro ponteiro para a lista não é modificado.
*		Se ocorrer algum erro durante a destruição, a lista resultará
*		estruturalmente incorreta.
*		OBS. não existe previsão para possíveis falhas de execução.
*
*  $AE Assertiva de Entrada
*		O ponteiro para a lista fornecida como parametro deve conter uma lista para ser excluida.
*		Caso contrário o ponteiro para lista não deve ser tratado para destruição.
*
*  $AS Assertiva de Saida
*		A lista fornecida como parametro se existia, foi destruída. Caso contrário, 
*		a lista já não existe.
*
*  $EP Parâmetros
*		pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*		LIS_CondRetOK				- exclusão OK
*		LIS_CondRetListaNaExiste	- lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;

 
/***********************************************************************
*
*  $FC Função: LIS  &Alocar memoria para lista
*
*  $ED Descrição da função
*		Aloca memória para uma lista duplamente encadeada com cabeça
*
*  $AS Assertiva de Saida
*		Uma lista devidamente alocada é retornada.
*
*  $FV Valor retornado
*		LIS_tppLista	-ponteiro para a lista devidamente alocada
*
***********************************************************************/

   LIS_tppLista LIS_AlocarLista();


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista(LIS_tppLista pLista);


#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
