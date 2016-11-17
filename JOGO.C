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

void JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas)
{
	int i,k;
	char  j, *nome, *cor;
	PCA_tpPeca *peca = (PCA_tpPeca*)malloc(PCA_tpPeca);

	LIS_ObterNo(pecas,peca);

	while (pecas!=NULL)
	{
		PCA_ObterCor(peca,cor);
		PCA_ObterNome(peca,nome);
		while (peca != NULL)
		{
			printf("onde por a peça %c de cor %c", cor, nome);
			scanf("%d %c", &i, &j);
			k = TAB_InserirPeca(ptabuleiro, i, j, peca);
			while (k != 0) {
				if (k == 1)
				{
					printf("casa ocupada tente novamente\n");
					scanf("%d %c", &i, &j);
					k = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
				else if (k == 4)
				{
					printf("coordenada nao existe tente novamente\n");
					scanf("%d %c", &i &j);
					k = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
			}
		}

	}
}

