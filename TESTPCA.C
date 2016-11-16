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
#include    "Lista.h"

static const char INICIALIZAR_PECAS_CMD  [ ] = "=inicializarPecas"	;
static const char OBTER_PECA_CMD         [ ] = "=obterPeca"			;
static const char OBTER_COR_CMD          [ ] = "=obterCor"			;
static const char OBTER_NOME_CMD         [ ] = "=obterNome"			;
static const char VALIDAR_MOVIMENTO_CMD  [ ] = "=validarMovimento"	;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VALOR 100

#define FILENAME "PecasPossiveis.txt"

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
*     =obterPeca
*     =obterCor
*     =obterNome
*     =validarMovimento
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      char   nomeDado ;
	  char   corDada  ;
	  
      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

	  PCA_tpPeca PecaCorrente = NULL;

	  LIS_tppLista ListaPecasPossiveis;


      /* Testar InicializarPecas */

         if ( strcmp( ComandoTeste , INICIALIZAR_PECAS_CMD ) == 0 )
         {
			numLidos = LER_LerParametros( "i" ,
                       &CondRetEsp ) ;
			
			if ( numLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			
			CondRet = PCA_InicializarPecas(FILENAME, ListaPecasPossiveis);
						
			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao inicializar pecas.");

         } /* fim ativa: Testar InicializarPecas */

      /* Testar Obter Peca*/

         else if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "icc" ,
						&CondRetEsp, &nomeDado, &corDada ) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = PCA_ObterPeca (ListaPecasPossiveis ,PecaCorrente, nomeDado, corDada);

           return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao obter peca.");

         } /* fim ativa: Testar Obter Peca */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista, &CondRetEsp ) ;

			if  ( numLidos != 2 )
			{
               return TST_CondRetParm ;
            } /* if */
						
			CondRet = LIS_DestruirLista( vtListas[ inxLista ] ) ;
			vtListas[ inxLista ] = NULL ;

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao tentar destruir a lista.");;

         } /* fim ativa: Testar Destruir lista */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( numLidos != 2 )             
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_IrProximoElemento( vtListas[ inxLista ] ) ;

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao ir ao proximo elemento da lista.");

         } /* fim ativa: LIS  &Ir para o elemento final */

		 /* Testar inserir nó */

         else if ( strcmp( ComandoTeste , INS_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( StringDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , StringDado ) ;


            CondRet = LIS_InserirNo( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir nó */

      /* Testar excluir elemento */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

			 numLidos = LER_LerParametros("ii",
				 &inxLista, &CondRetEsp);

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ]),
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir elemento */

		 /* Testar alterar nó corrente */

		 else if (strcmp(ComandoTeste, ALTERAR_NO_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("isi",
				 &inxLista, StringDado, &CondRetEsp);

			 if ((numLidos != 3)
				 || (!ValidarInxLista(inxLista, NAO_VAZIO)))
			 {
				 return TST_CondRetParm;
			 } /* if */

			 pDado = (char *)malloc(strlen(StringDado) + 1);

			 if (pDado == NULL)
			 {
				 return TST_CondRetMemoria;
			 } /* if */

			 strcpy(pDado, StringDado);

			 return TST_CompararInt(CondRetEsp,
				 LIS_AlterarNoCorrente(vtListas[inxLista], pDado),
				 "Condição de retorno errada ao alterar valor do nó corrente.");

		 } /* fim ativa: Testar alterar nó corrente */
      
		/* LIS  &Obter No */

         else if ( strcmp( ComandoTeste , OBTER_NO ) == 0 )
         {

			 numLidos = LER_LerParametros( "isi" , &inxLista,&StringDado,&CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = (char *)malloc(strlen(StringDado) + 1);
								
			if (pDado == NULL)
			{
				return TST_CondRetMemoria;
			} /* if */

			CondRet = LIS_ObterNo(vtListas[inxLista], &pDado) ;
			
			if(CondRet==0)
			{
				if(strcmp(pDado,StringDado)==0)
					return  TST_CondRetOK;
				return TST_CompararString(StringDado, pDado, "String recebida diferente da informada");
			}

				return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao Obter No");

         } /* fim ativa: LIS  &Obter No */
	  /*LIS  &Obter ID da Lista*/

		 else if ( strcmp( ComandoTeste , OBTER_ID ) == 0 )
         {

			 numLidos = LER_LerParametros( "isi" , &inxLista, StringDado ,&CondRetEsp ) ;

            if ( ( numLidos != 3 )
              /*|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ))*/ )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = (char *)malloc(strlen(StringDado) + 1);
								
			if (pDado == NULL)
			{
				return TST_CondRetMemoria;
			} /* if */

			strcpy(pDado, StringDado);

			CondRet = LIS_idLista(vtListas[inxLista], &pDado) ;

			if(CondRet == 0)
			{
				return TST_CompararString(StringDado , pDado,
					"Valor retornado nâo foi esperado");
			}

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao Obter No");

         } /* fim ativa: LIS  &Obter ID Da Lista */

		 /*LIS  &Ir Anterior*/

		 else if ( strcmp( ComandoTeste , IR_ANT ) == 0 )
         {

			 numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = LIS_irAnt(vtListas[inxLista]) ;

			

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao Ir para no anterior");

         } /* fim ativa: LIS  &Ir Anterior */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_IrProximoElemento( vtListas[ inxLista ] ) ;

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao ir ao proximo elemento da lista.");

         } /* fim ativa: LIS  &Ir para o elemento final */
	  
	  return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/



/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

