#include "rsa.hpp"

void __rsa__::PubKeyAsPEMStr(std::string& _out)
{
  int pipe_fd[2] = {};
  pipe(pipe_fd);

  FILE* write_pipe = fdopen(pipe_fd[1], "w");
  if (PEM_write_RSAPublicKey(write_pipe, rsa_) != 1)
  {
    throw std::runtime_error("Error writing to pipe");
  }
  FILE* read_pipe = fdopen(pipe_fd[0], "r");
  fclose(write_pipe);
  while (!feof(read_pipe))
    _out.push_back(getc(read_pipe));
  fclose(read_pipe);
}


DecryptionRSA::DecryptionRSA()
{
  bn_ = BN_new();
  BN_set_word(bn_, RSA_F4);
  rsa_ = RSA_new();
  // TODO random seed number generator shuffle
  int rsa_gen = RSA_generate_key_ex(rsa_, __rsa__::num_key_bits, bn_, NULL);
  if (rsa_gen != 1)
  {
    throw std::runtime_error("RSA Key Generation Failed");
  }
}

DecryptionRSA::~DecryptionRSA()
{
  RSA_free(rsa_);
  BN_free(bn_);
}

void DecryptionRSA::Decrypt(int _flen, unsigned char* _encrypted, unsigned char* _out)
{
  if (RSA_private_decrypt(_flen, _encrypted, _out, rsa_, __rsa__::padding) < 0)
  {
    throw std::runtime_error("Error decrypting");
  }
}


EncryptionRSA::EncryptionRSA(RSA* _rsa)
{
  SetRSA(_rsa);
}

EncryptionRSA::EncryptionRSA()
{
}

void EncryptionRSA::SetRSA(RSA* _rsa)
{
  rsa_ = _rsa;
}

void EncryptionRSA::FromPEMStr(const char* _pem)
{
    int pipe_fd[2] = {};
    pipe(pipe_fd);
    FILE* write_pipe = fdopen(pipe_fd[1], "w");
    FILE* read_pipe = fdopen(pipe_fd[0], "r");
    fwrite(_pem, sizeof(char), strlen(_pem), write_pipe);
    fclose(write_pipe);

    RSA* rsa = PEM_read_RSAPublicKey(read_pipe, NULL, NULL, NULL);

    if (rsa == NULL)
    {
      throw std::runtime_error("Error constructing RSA from PEM key");
    }
    fclose(read_pipe);
    SetRSA(rsa);
}

void EncryptionRSA::Encrypt(int _msg_len, unsigned char* _msg, unsigned char* _out)
{
  if (rsa_ == nullptr)
      throw std::runtime_error("RSA not set\n");
  int e = RSA_public_encrypt(_msg_len, _msg, _out, rsa_, __rsa__::padding);
  if (e != RSA_size(rsa_))
  {
    throw std::runtime_error("Error encrypting");
  }
}

EncryptionRSA::~EncryptionRSA()
{
  if (rsa_ != nullptr)
    RSA_free(rsa_);
}

int EncryptionRSA::EncryptMsgSize()
{
  if (rsa_ == nullptr)
      throw std::runtime_error("RSA not set\n");
  return RSA_size(rsa_);
}
