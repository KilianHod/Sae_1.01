#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

    #define NBCOL 7
    #define NBLIG 6

	const char PION_A='X';
    const char PION_B='O';
    const char VIDE=' ';
    const char INCONNU=' ';
	const int COLONNE_DEBUT=(NBCOL/2);
	
	typedef char grille[NBLIG][NBCOL];

    void  initGrille(grille g);
	void afficher(grille g, char pion, int colonne);
	bool grillePleine(grille g);
	void jouer(grille g, char pion, int *colonne, int *ligne);
	int choisirColonne(grille g, char pion, int colonne);
	int trouverLigne(grille g, int colonne);
	bool estVainqueur(grille g, int colonne, int ligne);
	void finDePartie(char pion);

int main() {
	char vainqueur;
    int ligne, colonne;
	ligne=6;
    colonne=COLONNE_DEBUT;
	grille g;
    initGrille(g); 

    vainqueur=INCONNU;

    afficher( g, PION_A, COLONNE_DEBUT);

    do{
	    jouer(g, PION_A, &ligne, &colonne);
	    afficher(g, PION_B, COLONNE_DEBUT);

        if(estVainqueur(g, ligne, colonne)){
            vainqueur=PION_A;

        } else if (!grillePleine(g)){
	    jouer(g, PION_B, &ligne, &colonne);
        afficher(g, PION_A, COLONNE_DEBUT);

            if (estVainqueur(g, ligne, colonne)){
	        vainqueur=PION_B;
            }
        }
    }while ((vainqueur==INCONNU) && (!grillePleine(g)));

    finDePartie(vainqueur);
	
	return EXIT_SUCCESS;
}

void  initGrille(grille g){
    int i, j;
    for(i=0;i<NBLIG;i++){
        for(j=0;j<NBCOL;j++){
            g[i][j]=VIDE;
        }
    }
}



void afficher(grille g, char pion, int colonne){
    int i, j, k;
    printf(" ");

    for(k=0;k<NBCOL;k++){
        if(k == colonne){
            printf("<%c>",pion);
        }else{
            printf("    "); 
        }    
    }

    printf("\n");
    for(i=0;i<NBLIG;i++){
        for(j=0;j<NBCOL;j++){
            printf("|_%c_",g[i][j]);
        }
        printf("|\n");
    }
    
}



bool grillePleine(grille g){
    int i, j, comp;
    comp=0;
    bool complet;
    complet=false;
    for(i=0;i<NBCOL;i++){
        for(j=0;j<NBLIG;j++){
            if(g[i][j]==VIDE){
                comp=comp+1;
            }
            
        }
    }
    if(comp==0){
        complet=true;
        return complet;
    }  else {
		complet=false;
        return complet;
	}
}

void jouer(grille g, char pion, int *colonne, int *ligne){
    int ligneTrouve;

    do{
        *colonne=choisirColonne(g, pion, COLONNE_DEBUT);
        *ligne=ligneTrouve=choisirColonne(g, pion, *colonne);

    }while(*ligne == -1);
    g[*ligne][*colonne]=pion;
    afficher (g, pion, colonne);
}


int choisirColonne(grille g, char pion, int colonne){
    char coup, entree;
    scanf("%c%c", &coup, &entree);
    
    do{
        if(coup=='q'){
            if(colonne-1>=0){
                colonne = colonne-1;
                afficher(g, pion, colonne);
            } else {
                printf("Vous êtes au boud de la grille\n");
                afficher(g, pion, colonne);
            }
        }
        if(coup=='d'){
            if(colonne+1<=NBCOL-1){
                colonne = colonne+1;
                afficher(g, pion, colonne);
            } else {
                printf("Vous êtes au boud de la grille\n");
                afficher(g, pion, colonne);
            }
        }
        if(coup==' '){
            return colonne; 
            afficher(g, pion, colonne);
        }
        scanf("%c%c", &coup, &entree);
    }while(coup!=' ');
    return colonne;
}

int trouverLigne(grille g, int colonne){
    int i, trouve;
    trouve=-1;
    i=NBLIG-1;

    while((i>=0)&&(trouve==1)){
        if(g[i][colonne]==VIDE){
            trouve=1;
        }
        i--;
    }
    return trouve;

}



bool estVainqueur(grille g, int colonne, int ligne){
	int i, j, comph, diag1, diag2, meme;
    bool gagne;
    gagne=false;
    i=ligne;
    j=colonne;
    comph=1;
    diag1=1;
    diag2=1;
    meme=0;

    if((g[i][j])==(g[i+1][j])&&(g[i][j])==(g[i+2][j])&&(g[i][j])==(g[i+3][j])){
        gagne=true;
    }
    
    while((meme!=1)&&(comph<4)){
        if((g[i][j])==(g[i][j+1])){
            comph=comph+1;
        } else {
            meme=1;
        }
        i++;
        j++;
    }

    while((meme!=0)&&(comph<=4)){
        if((g[i][j])==(g[i][j-1])){
            comph=comph+1;
        } else {
            meme=0;
        }
        i--;
        j--;
    }
    
    if(comph>=4){
        gagne=true;
    }

    if((g[i][j])==(g[i+1][j+1])){
            diag1++;
            if((g[i+1][j+1])==(g[i+2][j+2])){
                diag1++;
                if((g[i+2][j+2])==(g[i+3][j+3])){
                    diag1++;
                }
            }
        }
        if((g[i][j])==(g[i-1][j-1])){
            diag1++;
            if((g[i-1][j-1])==(g[i-2][j-2])){
                diag1++;
                if((g[i-2][j-2])==(g[i-3][j-3])){
                    diag1++;
                }
            }
        }
        if(diag1>=4){
            gagne=true;
        }

	if((g[i][j])==(g[i-1][j+1])){
        diag2++;
        if((g[i-1][j+1])==(g[i-2][j+2])){
            diag2++;
            if((g[i-2][j+2])==(g[i-3][j+3])){
                diag2++;
            }
        }
    }
    if((g[i][j])==(g[i+1][j-1])){
        diag2++;
        if((g[i+1][j-1])==(g[i+2][j-2])){
            diag2++;
            if((g[i+2][j-2])==(g[i+3][j-3])){
                diag2++;
            }
        }
    }
    if(diag2>=4){
        gagne=true;
    }
		
	
    return gagne;
}
	


void finDePartie(char pion){
	
    if(pion==PION_A){
        printf("Le joueur A est vainqueur");
    }
    if(pion==PION_B){
        printf("Le joueur B est vainqueur");
    }
    if(pion==INCONNU){
        printf("La grille est pleine c'est égalité");
    }
}
