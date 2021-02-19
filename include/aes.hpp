/*******************************************************************
 * Name: aes256 
 * Author: Marquez Jones
 * Desc: implementation of AES256 encryption for incognito project
 *******************************************************************/
#pragma once

#include <stdlib.h>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
