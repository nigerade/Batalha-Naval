// BIBLIOTECAS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
// FIM BIBLIOTECAS


// DEFININDO  VARIÁVEIS
#define AGUA  0
#define NAVIO  1
#define TIRONAGUA  10
#define TIRONAVIO  11
#define ALEATORIO 01
#define INTELIGENTE 02
#define DIREITA 03
#define ESQUERDA 04
// FIM DEFININDO  VARIÁVEIS

int main() // COMEÇO PROGRAMA 
{	
    srand(time(NULL)); // TEMPO INDEFINIDO PARA ENCERRAR O PROGRAMA
	setlocale(LC_ALL, "Portuguese"); // PORTUGUÊS COMO LINGUAGEM PRINCIPAL

    // DECLARANDO VARIÁVEIS
	int tabuleiroHumano[10][10];
	int tabuleiroComputador[10][10];
	int l, c, i;
	int pontosHumano = 0, pontosComputador = 0;
	int modoComputador = ALEATORIO;
	int ultimoL, ultimoC; 
	int contTiros = 0;
	int sentido = DIREITA;
    // FIM DECLARANDO VARIÁVEIS

	
	// PREENCHENDO AS MATRIZES COM ÁGUA
	for(l=0; l<10; l++)
	{	
        for(c=0; c<10; c++)
		{	
            tabuleiroHumano[l][c] = AGUA;
			tabuleiroComputador[l][c] = AGUA;
		}
	}
    // FIM PREENCHENDO AS MATRIZES COM ÁGUA

	
	// ENTRADA DOS NAVIOS NO TABULEIRO DO HUMANO
	for(i=1; i<=6; i++) //Sao 6 navios
	{	
	    do{
	        printf("Entre com as coordenadas de Linha e Coluna do %d o. Navio:\n", i);
		    scanf("%d%d", &l, &c);
		    if(tabuleiroHumano[l][c] == NAVIO || tabuleiroHumano[l][c+1] == NAVIO || tabuleiroHumano[l][c+2] == NAVIO)
		        printf("Erro! Já existe navio nesta coordenada....\n");
	    } while(tabuleiroHumano[l][c] == NAVIO || tabuleiroHumano[l][c+1] == NAVIO || tabuleiroHumano[l][c+2] == NAVIO);
		
		tabuleiroHumano[l][c] = NAVIO;   //o navio e formado por 3 partes
		tabuleiroHumano[l][c+1] = NAVIO;
		tabuleiroHumano[l][c+2] = NAVIO;
     }
    // FIM ENTRADA DOS NAVIOS NO TABULEIRO DO HUMANO



	// SORTEIO DOS NAVIOS NO TABULEIRO DO COMPUTADOR
	for(i=1; i<=6; i++) //Sao 6 navios
	{	
        do{
	        l = rand()%10;
		    c = rand()%8;
	    } while(tabuleiroComputador[l][c] == NAVIO || tabuleiroComputador[l][c+1] == NAVIO || tabuleiroComputador[l][c+2] == NAVIO);
		
		tabuleiroComputador[l][c] = NAVIO; // o navio e formado por 3 partes
		tabuleiroComputador[l][c+1] = NAVIO; // coluna +1 
		tabuleiroComputador[l][c+2] = NAVIO; // coluna +2
	}
    // FIM SORTEIO DOS NAVIOS NO TABULEIRO DO COMPUTADOR



    // LOOP QUE FAZ O JOGO CONTINUAR ENQUANTO NÃO ATINGIR 18 PONTOS (TODOS NAVIOS)
	while(pontosHumano<18 && pontosComputador<18)
	{	// Tiro do Humano
		do
		 {	
            printf("Entre com as coordenadas de linha e coluna do tiro:\n");
		    scanf("%d%d", &l, &c);

		    if  (tabuleiroComputador [l][c] == TIRONAVIO || tabuleiroComputador [l][c] ==TIRONAGUA)
    		{  
    		    printf("Você já atirou nesta posição!!\n"); // Não deixa Atirar no mesmo Lugar
    		}  
        
		} while  (tabuleiroComputador [l][c] == TIRONAVIO || tabuleiroComputador [l][c] ==TIRONAGUA);
                  // Se o Humano errar preenche com Água, caso contrário, preenche com Acerto


		if(tabuleiroComputador[l][c] == AGUA) // Se o computador errar preenche com Água 
		{	
		    printf("Errou!!\n");
		    tabuleiroComputador[l][c] = TIRONAGUA;
		}

		else if (tabuleiroComputador[l][c] == NAVIO) // Se o computador errar preenche com Acerto
		{  
             pontosHumano++;
		    printf("Acertou!!\n");
		    tabuleiroComputador[l][c] = TIRONAVIO;   
		}
	

		//Tiro do Computador
		if (modoComputador ==  ALEATORIO)
		{ 
    		do{
    		    l = rand()%10;
    		    c = rand()%10;
    		} while(tabuleiroHumano [l][c] == TIRONAVIO || tabuleiroHumano [l][c] ==TIRONAGUA);
		}  

	   else // modointeligente
	   {
	      l = ultimoL;
	      if (sentido == DIREITA)  c = ultimoC+1;
	      if (sentido == ESQUERDA) c = ultimoC-1;
	   }
		
		printf("Eu estou atirando nas coordenadas %d, %d\n", l, c);
	    if(tabuleiroHumano[l][c] == AGUA)
	    {   
            if(contTiros > 0)
    	    {  
                 sentido = ESQUERDA;
    	        ultimoC = c  - contTiros;
    	    }
		    printf("Errei!!\n");
		    tabuleiroHumano[l][c] = TIRONAGUA;
		}

		else if(tabuleiroHumano[l][c] == NAVIO)
		{   
            pontosComputador++;
		    contTiros ++;
		    tabuleiroHumano[l][c] = TIRONAVIO;
		    printf("Acertei!!\n");
		    ultimoL = l;
		    ultimoC = c;
		    modoComputador = INTELIGENTE;

		    if (contTiros == 3)
		    {   
                modoComputador = ALEATORIO;
		        contTiros = 0;
		        sentido = DIREITA;
		    }
		}  
		
		printf("\nTabuleiro do Humano:\n");
		printf("    0 1 2 3 4 5 6 7 8 9\n\n");
		for(l=0; l < 10; l++) // LIMITA A 10 POSIÇÕES (10x10) - LINHA
		{	
            printf("%d  |", l);
			for(c=0; c < 10; c++) // LIMITA A 10 POSIÇÕES (10x10) - COLUNA
			{	
                if(tabuleiroHumano[l][c]==TIRONAGUA)
					printf("A|"); // ACERTO

				else if(tabuleiroHumano[l][c]==TIRONAVIO) 
					printf("X|"); // ERRO

				else printf(" |"); // PAREDE
			}

			printf("\n");
		
		}
		
		printf("\nTabuleiro do Computador:\n");
		printf("    0 1 2 3 4 5 6 7 8 9\n\n");
		for(l=0; l < 10; l++) // LIMITA A 10 POSIÇÕES (10x10) - LINHA
		{	
            printf("%d  |", l);
			for(c=0; c < 10; c++) // LIMITA A 10 POSIÇÕES (10x10) - COLUNA
			{	
                if(tabuleiroComputador[l][c]==TIRONAGUA)
					printf("A|"); // ERRO

				else if(tabuleiroComputador[l][c]==TIRONAVIO)
					printf("X|"); // ACERTO

				else printf(" |"); // PAREDE
			}

			printf("\n");
		}
	}
    // FIM LOOP QUE FAZ O JOGO CONTINUAR ENQUANTO NÃO ATINGIR 18 PONTOS (TODOS NAVIOS)


    // CONDICIONAL (SE ATINGIR 18 PONTOS, O JOGO ACABA)
	if(pontosHumano == 18) printf("Você ganhou!!!!\n");
	else printf("Eu ganhei, patinho!!!!\n");
    // FIM CONDICIONAL (SE ATINGIR 18 PONTOS, O JOGO ACABA)     


	return 0;
	}