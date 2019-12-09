#include "bhtree.h"
#include "body.h"
#include "quad.h"
#include <stdio.h>
#include <stdlib.h>

#define THETA 0.5 // Constante de ratio max s/d

static int bhtreeExternal(BHTree *bht);
static void bhtreePrintExtra(BHTree *bht, FILE *fp, int recursion, int type);

struct BHTree_t {
  Quad *quad;     // Région correspondant à la racine de ce (sous-)arbre
  BHTree *nw;     // sous-arbre Nord-Ouest
  BHTree *ne;     // sous-arbre Nord-Est
  BHTree *sw;     // sous-arbre Sud-Ouest
  BHTree *se;     // sous-arbre Sud-Est
  Body *body;     // Particule associée ou particule équivalente (centre inertie).
};

BHTree *bhtreeCreate(Quad *q) {
  BHTree *tree = malloc(sizeof(BHTree));
  tree->quad = q;
  tree->nw = NULL;
  tree->ne = NULL;
  tree->sw = NULL;
  tree->se = NULL;
  tree->body = NULL;
  return tree;
}

void bhtreeFree(BHTree *bht) {
  if (bht == NULL) {
    printf("Erreur : free(NULL)");
    exit(-1);
  }

  if (bht->nw != NULL)
    bhtreeFree(bht->nw);
  if (bht->ne != NULL)
    bhtreeFree(bht->ne);
  if (bht->sw != NULL)
    bhtreeFree(bht->sw);
  if (bht->se != NULL)
    bhtreeFree(bht->se);
  free(bht);
}

void bhtreeInsert(BHTree *bht, Body *b) {
	if(bht == NULL || b == NULL)
		exit(-1);

	if(!quadContains(bht->quad, bodyGetrx(b), bodyGetry(b)))
		return;

	if (bht->body == NULL) { // (1) Ne contient pas de particule, 1re itération
		bht->body = b;
  	} else if (!bhtreeExternal(bht)) { // (2) Noeud interne, contient une part. équivalente
		bodyAggregate(bht->body, b);
		if(bht->nw != NULL && quadContains(bht->nw->quad, bodyGetrx(b), bodyGetry(b))) {
			bhtreeInsert(bht->nw, b);
		} else if(bht->ne != NULL && quadContains(bht->ne->quad, bodyGetrx(b), bodyGetry(b))) {
			bhtreeInsert(bht->ne, b);
		} else if(bht->sw != NULL && quadContains(bht->sw->quad, bodyGetrx(b), bodyGetry(b))) {
			bhtreeInsert(bht->sw, b);
		} else if(bht->se != NULL && quadContains(bht->se->quad, bodyGetrx(b), bodyGetry(b))) {
			bhtreeInsert(bht->se, b);
		}
	} else { // (3) Noeud externe contenant une autre particule 
		bht->nw = bhtreeCreate(quadNW(bht->quad));
		bht->ne = bhtreeCreate(quadNE(bht->quad));
		bht->sw = bhtreeCreate(quadSW(bht->quad));
		bht->se = bhtreeCreate(quadSE(bht->quad));
		Body *body = bht->body;
		// On transforme en "particule équivalente" pour le centre d'inertie
		// On la crée vide car en insérant récursivement, les masses de
		// b et body seront alors ajoutées dans la condition (2). 
		bht->body = bodyCreate(0, 0, 0, 0, 0);
		bhtreeInsert(bht, b);
		bhtreeInsert(bht, body);
  	}
}

void bhtreeUpdateForce(BHTree *bht, Body *b) {
	if(bht->body == NULL) // Feuille vide
		return;

	double s = quadLength(bht->quad);
	double d = bodyDistanceTo(bht->body, b);
	if((bhtreeExternal(bht) && bht->body != b) || s / d < THETA) {
		bodyAddForce(b, bht->body);
	} else if(!bhtreeExternal(bht)) {
		bhtreeUpdateForce(bht->nw, b);
		bhtreeUpdateForce(bht->ne, b);
		bhtreeUpdateForce(bht->sw, b);
		bhtreeUpdateForce(bht->se, b);
	}
}

void bhtreePrint(BHTree *bht, FILE *fp) {
	if(bht == NULL) {
		printf("Erreur bhtreePrint(null)");
		exit(-1);
	}

	bhtreePrintExtra(bht, fp, 0, 0);
}

/**
 * Démarre les appels récursif pour print l'arbre.
 * Donne des paramètres en + :
 * recursion: pour dessiner correctement l'espace avant les flèches.
 * type: Root (0), NW (1), NE (2), SW (3) ou SE (4).
 */
static void bhtreePrintExtra(BHTree *bht, FILE *fp, int recursion, int type) {
	if(type == 0) {
		fprintf(fp, "Root:");
	} else {
		for(int i = 0; i < recursion; i++)
			fprintf(fp, "   |");
		fprintf(fp, "-->");
		if(type == 1) fprintf(fp, "NW:");
		else if(type == 2) fprintf(fp, "NE:");
		else if(type == 3) fprintf(fp, "SW:");
		else if(type == 4) fprintf(fp, "SE:");
	}
	quadPrint(bht->quad, fp);
	if (bht->body != NULL) {
		bodyPrint(bht->body, fp);
	}
	fprintf(fp, "\n");

	if(bht->nw != NULL)
		bhtreePrintExtra(bht->nw, fp, recursion + 1, 1);
	if(bht->ne != NULL)
		bhtreePrintExtra(bht->ne, fp, recursion + 1, 2);
	if(bht->sw != NULL)
		bhtreePrintExtra(bht->sw, fp, recursion + 1, 3);
	if(bht->se != NULL)
		bhtreePrintExtra(bht->se, fp, recursion + 1, 4);
}

// Renvoie si le sous-arbre donné est un noeud externe.
static int bhtreeExternal(BHTree *bht) {
  return bht->nw == NULL && bht->ne == NULL &&
         bht->sw == NULL && bht->se == NULL;
}
