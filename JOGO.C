#include "JOGO.H"
#include "TABULEIRO.H"
#include "PECA.H"




JGO_tpCondRet JGO_IniciarJogo (char* filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro){

	char resp;
	LIS_tppLista listaPecasPossiveis;
	TAB_tpTabuleiro pTabuleiro;

	pTabuleiro = TAB_AlocarTabuleiro(8, 'H');
	TAB_CriarTabuleiro (pTabuleiro);

	PCA_InicializarPecas(filename, &listaPecasPossiveis);
	printf("Padrão? S:N");
	scanf("%d", resp);
	if (resp == 'S')
		JGO_MontarTabPadrao();//Sabrina
	else
		JGO_MontarTabMod();//RUDA 

}

