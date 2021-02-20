/*******************************************************************
 * Name: aes
 * Author: Marquez Jones
 * Desc: implementation of AES256 encryption/decryption for incognito project
 *******************************************************************/
#pragma once

#include <stdlib.h>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

class __aes__
{
pubic: 
  static const int AES_KEY_SIZE = 32; //bytes
  static const int AES_BLOCK_SIZE = 16; //bytes
protected: 
  __aes__() {}
  unsigned char *key = NULL;
  unsigned char *iv  = NULL; //init vector
}


class DecryptionAES : public __aes__
{
public:
  DecryptionAES();
  DecryptionAES();
  //_out msg malloc, return -1 on failure
  int Decrypt(int _flen, unsigned char *_encrypted, unsigned char *_out);
  int DecryptSetKey(unsigned char *key);
}

class EncryptionAES : public __aes__
{
public:
  EncryptionAES();
  ~EncryptionAES();
  //_out malloc, return -1 on failure
  int Encrypt(int _msg_len,unsigned char *_msg, unsigned char *_out);
  int EncryptMsgSize();
  void EncrypteSetKey(unsigned char *key);
private:
  int _msg_size = -1;
  int GenerateIV(void); //generated randomly each time
}
