#include "quad.h"
#include <stdio.h>
#include <stdlib.h>

struct Quad_t {
	double center_x;
	double center_y;
	double radius;
};

Quad *quadCreate(double xmid, double ymid, double length) {
	if(length < 0) {		
		printf("quadCreate: Longueur invalide\n");		
		exit(-1);
	}	

	Quad *quad = malloc(sizeof(Quad));

	if (quad == NULL) {		
		printf("Erreur malloc");		
		exit(-1);
	}	

	quad->center_x = xmid;
	quad->center_y = ymid;
	quad->radius = length / 2;	

	return quad;
}

void quadFree(Quad *q) {
	if(q == NULL) exit(-1);

	free(q);
}

int quadContains(Quad *q, double x, double y) {
	if(q == NULL) {
		printf("Erreur\n");
		exit(-1);
	}

	return (q->center_x - q->radius < x && x <= q->center_x + q->radius
		&& q->center_y - q->radius < y && y <= q->center_y + q->radius);
}

double quadLength(Quad *q) {
	if(q == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	return 2 * q->radius;
}

Quad *quadNW(Quad *q) {
	if(q == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	return quadCreate(q->center_x - q->radius / 2, q->center_y + q->radius / 2, q->radius);
}

Quad *quadNE(Quad *q) {
	if(q == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	return quadCreate(q->center_x + q->radius / 2, q->center_y + q->radius / 2, q->radius);
}

Quad *quadSW(Quad *q) {
	if(q == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	return quadCreate(q->center_x - q->radius / 2, q->center_y - q->radius / 2, q->radius);
}

Quad *quadSE(Quad *q) {
	if(q == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	return quadCreate(q->center_x + q->radius / 2, q->center_y - q->radius / 2, q->radius);
}

void quadPrint(Quad *q, FILE *fp) {
	if(q == NULL || fp == NULL) {
		printf("Erreur d'argument\n");
		exit(-1);
	}
	fprintf(fp, "[Q (%.2e,%.2e),%.2e]", q->center_x, q->center_y, 2 * q->radius);
}
