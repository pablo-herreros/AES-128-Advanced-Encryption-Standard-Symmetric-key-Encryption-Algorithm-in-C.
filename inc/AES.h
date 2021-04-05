#ifndef AES_H
#define AES_H

#define AES_KEY_BITS 128 //USED TO CHANGE AES 128 OR AES 256 ALGORITHM
#define AES_KEY_BYTES AES_KEY_BITS/8
#define SBOX_N_ELEM 16 //Matrix 16x16
#define ENCRYPT_MODE 0
#define DECRYPT_MODE 1

#include "Global.h"
#include "Operations.h"

/**
 * @brief Enum of possible errors.
 */
enum AES_ERRORS{

	AES_ERROR_OK = 0,
	AES_ERROR_NULL_VALUE,
	AES_ERROR_OUT_RANGE,
	AES_ERROR_KEY_LENGHT

}typedef AES_ERRORS;

/**
 * @brief Struct used to store rounds Keys in AES-128 decrypt
 */
struct KeyRound{

unsigned char Key[4][4];

}typedef KeyRound;

/**
 * @brief AES-128 algorithm do a AES-128 encrypt or descrypt process.
 * @param InputString String to encrypt or descrypt.
 * @param Key AES Key used to data process.
 * @param Mode 0 Encrypt 1 Decrypt.
 * @param OutputString Output String; Result String.
 * @return AES_ERRORS Enum.
 */
AES_ERRORS AES128(unsigned char * InputString, unsigned char * Key, int mode, unsigned char * OutputString);

/**
 * @brief AES-128 Encrypt
 * @param PlainText
 * @param Key
 * @param CipherText
 * @return AES_ERRORS
 */
void AES128Encrypt(unsigned char * PlainText, unsigned char * Key, unsigned char * Cryptogram);

/**
 * @brief AES-128 Decrypt
 * @param Cryptogram
 * @param Key
 * @param PlainText
 * @return AES_ERRORS
 */
void AES128Decrypt(unsigned char * Cryptogram, unsigned char * Key, unsigned char * PlainText);


#endif
