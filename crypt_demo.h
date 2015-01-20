/* crypt_demo.h
 * Mengxiao Lin 2015-1-19
 */
#ifndef CRYPT_DEMO_H

#define CRYPT_DEMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gcrypt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LEN_OF_RETKEY 32
#define SIZE_OF_RETKEY LEN_OF_RETKEY
#define ITER 4096
#define SALT "cRyPt"
#define CIPHER_ALGO GCRY_CIPHER_AES256
#define MAGIC_STRING "233GCRYPT_DEMO1"

extern char * get_key_from_password();
extern void cipher_error_handler(int);
extern int get_file_size(char *);
#endif
