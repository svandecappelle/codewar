#ifndef COMMANDES_H
#define COMMANDES_H
#include "commandes.h"


#include "../definitions.h"



void move(processeur liste_processeur[][16], adresse *ad);
void push(processeur liste_processeur[][16], adresse *ad);
void pop(processeur liste_processeur[][16], adresse *ad);
void add(processeur liste_processeur[][16], adresse *ad);
void cmp(processeur liste_processeur[][16], adresse *ad);
void sub(processeur liste_processeur[][16], adresse *ad);
void lsl(processeur liste_processeur[][16], adresse *ad);
void lsr(processeur liste_processeur[][16], adresse *ad);
void and(processeur liste_processeur[][16], adresse *ad);
void or(processeur liste_processeur[][16], adresse *ad);
void xor(processeur liste_processeur[][16], adresse *ad);
void not(processeur liste_processeur[][16], adresse *ad);
void bcc_bgt(processeur liste_processeur[][16], adresse *ad);
void bcs_blt(processeur liste_processeur[][16], adresse *ad);
void beq(processeur liste_processeur[][16], adresse *ad);
void bne(processeur liste_processeur[][16], adresse *ad);
void ble(processeur liste_processeur[][16], adresse *ad);
void bge(processeur liste_processeur[][16], adresse *ad);
void bra(processeur liste_processeur[][16], adresse *ad);
void bsr(processeur liste_processeur[][16], adresse *ad);
void jcc_jgt(processeur liste_processeur[][16], adresse *ad);
void jcs_jlt(processeur liste_processeur[][16], adresse *ad);
void jeq(processeur liste_processeur[][16], adresse *ad);
void jne(processeur liste_processeur[][16], adresse *ad);
void jle(processeur liste_processeur[][16], adresse *ad);
void jge(processeur liste_processeur[][16], adresse *ad);
void jmp(processeur liste_processeur[][16], adresse *ad);
void jsr(processeur liste_processeur[][16], adresse *ad);
void rts(processeur liste_processeur[][16], adresse *ad);
void trap(processeur liste_processeur[][16], adresse *ad);
void rte(processeur liste_processeur[][16], adresse *ad);
void rien(processeur liste_processeur[][16], adresse *ad);

void interruption (processeur *p,adresse *ad, char type);
#endif 
