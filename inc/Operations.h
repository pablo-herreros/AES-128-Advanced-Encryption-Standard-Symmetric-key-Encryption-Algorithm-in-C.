#ifndef OPERATIONS_H
#define OPERATIONS_H

void MixColums(unsigned char * StateMatrix);

void ShiftRows(unsigned char * StateMatrix);

void SubBytes(unsigned char * StateMatrix);

void AddRoundKey(unsigned char * KeyMatrix, unsigned char * StateMatrix);

void InvMixColums(unsigned char * StateMatrix);

void InvShiftRows(unsigned char * StateMatrix);

void InvSubBytes(unsigned char * StateMatrix);

void KeyExpansion(unsigned char * KeyMatrix, unsigned char * NextKeyMatrix, int round);

#endif
