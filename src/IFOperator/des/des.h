#ifndef _MMDB_DES_H_
#define _MMDB_DES_H_ 1

// #include "stdio.h"
// #include "time.h"
// #include "stdlib.h"

#define OK 1;

typedef char ElemType;

/* ��ʼ�û���IP */

extern int IP_Table[64];

/* ���ʼ�û���IP^-1 */
extern int IP_1_Table[64];

/* �����û���E */
extern int E_Table[48];


/* �û�����P */
extern int P_Table[32];


/* S�� */
extern int S[8][4][16];

/* �û�ѡ��1 */
extern int PC_1[56];


/* �û�ѡ��2 */
extern int PC_2[48];

/* �����ƴ����Ĺ涨 */
extern int MOVE_TIMES[16];

int ByteToBit(ElemType ch,ElemType bit[8]);

int BitToByte(ElemType bit[8],ElemType *ch);

int Char8ToBit64(ElemType ch[8],ElemType bit[64]);

int Bit64ToChar8(ElemType bit[64],ElemType ch[8]);

int DES_MakeSubKeys(ElemType key[64],ElemType subKeys[16][48]);

int DES_PC1_Transform(ElemType key[64], ElemType tempbts[56]);

int DES_PC2_Transform(ElemType key[56], ElemType tempbts[48]);

int DES_ROL(ElemType data[56], int time);

int DES_IP_Transform(ElemType data[64]);

int DES_IP_1_Transform(ElemType data[64]);

int DES_E_Transform(ElemType data[48]);

int DES_P_Transform(ElemType data[32]);

int DES_SBOX(ElemType data[48]);

int DES_XOR(ElemType R[48], ElemType L[48],int count);

int DES_Swap(ElemType left[32],ElemType right[32]);

int DES_EncryptBlock(ElemType plainBlock[8], ElemType subKeys[16][48], ElemType cipherBlock[8]);

int DES_DecryptBlock(ElemType cipherBlock[8], ElemType subKeys[16][48], ElemType plainBlock[8]);

int DES_Encrypt(char *plainFile, char *keyStr,char *cipherFile);

int DES_Decrypt(char *cipherFile, char *keyStr,char *plainFile);

#endif
