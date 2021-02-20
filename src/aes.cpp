/*******************************************************************
 * Name: aes256 
 * Author: Marquez Jones
 * Desc: implementation of AES256 encryption for incognito project
 *******************************************************************/
#include <string>
#include <string.h>
#include <stdexcept>
#include <unistd.h>
#include "aes.hpp"

/***************************** DECRYPTION ****************************/
DecryptionAES::DecryptionAES()
{
  this->iv = new unsigned char[AES_KEY_SIZE];
  this->key = new unsigned char[AES_KEY_SIZE];
}


DecryptionAES::~DecryptionAES()
{
  free(this->iv);
  free(this->key);
}

int DecryptionAES::Decrypt(int _flen, unsigned char *_encrypted, unsigned char *_out)
{
}

int DecryptionAES::DecryptSetKey(unsigned char *key)
{
}

/***************************** ENCRYPTION ***************************/
EncryptionAES::EncryptionAES()
{
  this->iv = new unsigned char[AES_KEY_SIZE];
  this->key = new unsigned char[AES_KEY_SIZE];
}

EncryptionAES::~EncryptionAES()
{
  free(this->iv);
  free(this->key);
}

int EncryptionAES::Encrypt(int _msg_len,unsigned char *_msg, unsigned char *_out)
{
  
  this->_msg_size = _msg_len + ((AES_BLOCK_SIZE-_msg_len)%AES_BLOCK_SIZE);
  _out = new unsigned char[this->_msg_size];
  EVP_CIPHER_CTX *enc_ctx = EVP_CIPHER_CTX_new();
  EVP_EncryptInit(enc_ctx, EVP_aes_256_cbc(),_msg,this->key,this->iv);
  // TODO: finish
}

int EncryptionAES::EncryptMsgSize()
{
}

void EncryptionAES::EncrypteSetKey(unsigned char *key)
{

  
}

int EncryptionAES::GenerateIV()
{
    if(!RAND_Bytes(this->iv,AES_KEY_SIZE)){
        throw std::runtime_error("AES IV Generation Failed");
    }
}



