#include "AES.h"

//Do AES-128 Encrypt process
void AES128Encrypt(unsigned char * PlainText, unsigned char * Key, unsigned char * Cryptogram){

unsigned char StateMatrix [4][4] =
{
	{PlainText[0], PlainText[4], PlainText[8], PlainText[12]},
	{PlainText[1], PlainText[5], PlainText[9], PlainText[13]},
	{PlainText[2], PlainText[6], PlainText[10], PlainText[14]},
	{PlainText[3], PlainText[7], PlainText[11], PlainText[15]},
};

//For 128 key matrix bits AES-128
unsigned char KeyMatrix [4][128/32] =
{
	{Key[0], Key[4], Key[8], Key[12]},
	{Key[1], Key[5], Key[9], Key[13]},
	{Key[2], Key[6], Key[10], Key[14]},
	{Key[3], Key[7], Key[11], Key[15]},
};

//For 256 key matrix bits AES-256. Only for AES-256 bits usage.
#if AES_KEY_BITS == 256
unsigned char KeyMatrix [4][128/32] =
{
		{Key[16], Key[20], Key[24], Key[28]},
		{Key[17], Key[21], Key[25], Key[29]},
		{Key[18], Key[22], Key[26], Key[30]},
		{Key[19], Key[23], Key[27], Key[31]},
  };
#endif

	//Start AES-128 process
	//First Round (Round 0) PlainText Key (Ko) is used
	AddRoundKey((unsigned char *)KeyMatrix, (unsigned char *)StateMatrix);

	for(int i = 0; i<9; i++){ //Round 1 to 9 (used K1 to k9 Keys)

		KeyExpansion((unsigned char *)KeyMatrix, (unsigned char *)KeyMatrix, i); //Key expansion

		SubBytes((unsigned char *)StateMatrix);

		ShiftRows((unsigned char *)StateMatrix);

		MixColums((unsigned char *)StateMatrix);

		AddRoundKey((unsigned char *)KeyMatrix, (unsigned char *)StateMatrix);

	}

	//Final round
	KeyExpansion((unsigned char *)KeyMatrix, (unsigned char *)KeyMatrix, 9); //Expansion Key Round 10

	SubBytes((unsigned char *)StateMatrix);

	ShiftRows((unsigned char *)StateMatrix);

	AddRoundKey((unsigned char *)KeyMatrix, (unsigned char *)StateMatrix);
	//End AES-128 process

	//Copy to output string in readable order
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			*(Cryptogram + i*4 + j) = *((unsigned char *)StateMatrix + j*4 + i);
		}
	}

};

void AES128Decrypt(unsigned char * Cryptogram, unsigned char * Key, unsigned char * PlainText){

unsigned char StateMatrix [4][4] =
{
	{Cryptogram[0], Cryptogram[4], Cryptogram[8],  Cryptogram[12]},
	{Cryptogram[1], Cryptogram[5], Cryptogram[9],  Cryptogram[13]},
	{Cryptogram[2], Cryptogram[6], Cryptogram[10], Cryptogram[14]},
	{Cryptogram[3], Cryptogram[7], Cryptogram[11], Cryptogram[15]},
};

//For 128 key matrix bits AES-128
unsigned char KeyMatrix [4][128/32] =
{
	{Key[0], Key[4], Key[8], Key[12]},
	{Key[1], Key[5], Key[9], Key[13]},
	{Key[2], Key[6], Key[10], Key[14]},
	{Key[3], Key[7], Key[11], Key[15]},
};

struct KeyRound s_KeyRound[10]; //Store K1 to K10 expanded keys


	/*Start AES-128 decrypt process*/

	//Precalculation of Kn keys expanded for next usage on decrypt
	KeyExpansion((unsigned char *)KeyMatrix,(unsigned char *)s_KeyRound[0].Key, 0);

	for(int i = 1; i<10; i++)
	KeyExpansion((unsigned char *)s_KeyRound[i-1].Key,(unsigned char *)s_KeyRound[i].Key, i);

	//AES-128 bits FIRST ROUND decrypt. Key n10 ([9]) will be used (inverse order that encrypt).
	AddRoundKey((unsigned char *)s_KeyRound[9].Key, (unsigned char *)StateMatrix);

	InvShiftRows((unsigned char *)StateMatrix);

	InvSubBytes((unsigned char *)StateMatrix);

	//Round 1 to 9 (used K1 to k9 Keys)
	for(int i = 8; i>=0; i--){

		AddRoundKey((unsigned char *)s_KeyRound[i].Key, (unsigned char *)StateMatrix);

		InvMixColums((unsigned char *)StateMatrix);

		InvShiftRows((unsigned char *)StateMatrix);

		InvSubBytes((unsigned char *)StateMatrix);

	}

	//Final round
	AddRoundKey((unsigned char *)KeyMatrix, (unsigned char *)StateMatrix);
	//End AES-128 process

	//Copy to output string in readable order
	for(int i = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			*(PlainText + i*4 + j) = *((unsigned char *)StateMatrix + j*4 + i);
		}
	}

};

AES_ERRORS AES128(unsigned char * InputString, unsigned char * Key, int mode, unsigned char * OutputString){

AES_ERRORS e_ret = AES_ERROR_OK;


	if(mode == ENCRYPT_MODE){
		//padding
		AES128Encrypt(InputString, Key, OutputString);
	}
	if(mode == DECRYPT_MODE)
		AES128Decrypt(InputString, Key, OutputString);

return e_ret;
};
