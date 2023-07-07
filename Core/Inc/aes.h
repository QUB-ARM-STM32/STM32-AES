/*
 * aes.h
 *
 *  Created on: 4 Jul 2023
 *      Author: doggi
 */

#ifndef INC_AES_H_
#define INC_AES_H_

void SubBytes(uint8_t state[4][4]);
void SubWord(uint8_t word[4]);
void RotWord(uint8_t word[4]);
void XORWords(uint8_t word[4], uint8_t xorValue[4], uint8_t res[4]);
void CopyWord(uint8_t arrayToCopyTo[4], uint8_t arrayCoppied[4]);
void GenerateKeys(uint8_t key[16], uint8_t buffer[44][4]);
void printKey(uint8_t key[44][4]);
void TransformToState(uint8_t plaintext[16], uint8_t state[4][4]);
uint8_t* Encrypt(uint8_t plaintext[16], uint8_t key[44][4]);
void printState(uint8_t state[4][4]);
void AddRoundKey(uint8_t state[4][4], uint8_t key[44][4], uint8_t round);
void ShiftRows(uint8_t state[4][4]);
void MixColumns(uint8_t state[4][4]);
void StateToArray(uint8_t state[4][4], uint8_t cipherText[16]);
void PrintWord(uint8_t word[4]);

// decryption
uint8_t* Decrypt(uint8_t cipherText[16], uint8_t key[44][4]);
void InvShiftRows(uint8_t state[4][4]);
void InvSubBytes(uint8_t state[4][4]);
void InvMixColumns(uint8_t state[4][4]);

// Util
void PrintText(uint8_t text[16]);
void PrintCharArray(char text[16]);

// Modes
void EncryptCBC(uint8_t* data, unsigned int length, uint8_t iv[16], uint8_t key[44][4], uint8_t* cipherText);
void DecryptCBC(uint8_t* cipherText, unsigned int length, uint8_t iv[16], uint8_t key[44][4], uint8_t* plainText);
void XOR16Bytes(uint8_t one[16], uint8_t two[16], uint8_t res[16]);

#endif /* INC_AES_H_ */
