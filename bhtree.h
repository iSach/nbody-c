#ifndef BHTree_h
#define BHTree_h

#include "quad.h"
#include "body.h"
#include "gifenc.h"

typedef struct BHTree_t BHTree;

BHTree *bhtreeCreate(Quad *q);
void bhtreeFree(BHTree *bht);

void bhtreeInsert(BHTree *bht, Body *b);
void bhtreeUpdateForce(BHTree *bht, Body *b);

void bhtreePrint(BHTree *bht, FILE *fp);
  
#endif
