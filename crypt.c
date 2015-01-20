/* crypt.c 
 * Mengxiao Lin 2015-01-19
 * 
 * a demo for libgcrypt
 *
 */

#include "crypt_demo.h"
/* print usage if the argument is wrong */
void usage_print(char * command){
	printf("Usage: %s filename\n",command);
}
int main(int argc,char *argv[])
{
	if (argc!=2){
		usage_print(argv[0]);
		return 1;
	}
	
	FILE *fin=fopen(argv[1],"rb");
	FILE *fout;
	
	gcry_cipher_hd_t cipher_hd;
	gcry_error_t cipher_err;

	int file_size=get_file_size(argv[1]);
	char *input_buf= (char*)malloc(file_size); 
	memset(input_buf,0,file_size);
	// plain text buffer
	
	size_t key_size = gcry_cipher_get_algo_keylen(CIPHER_ALGO);
	size_t block_size = gcry_cipher_get_algo_blklen(CIPHER_ALGO);
	size_t block_required=file_size/block_size;
	if (file_size % block_size != 0){
		block_required++;
	}
	char *cipher_buffer=malloc(block_size*block_required);
	memset(cipher_buffer,0,block_size*block_required);
	
	char *iv=malloc(block_size);
	memset(iv,0,block_size);
	memcpy(iv,MAGIC_STRING,sizeof(MAGIC_STRING));
	
	char *key = get_key_from_password();
	//open cipher
	cipher_err=gcry_cipher_open(&cipher_hd,CIPHER_ALGO,
				GCRY_CIPHER_MODE_CBC,GCRY_CIPHER_CBC_CTS);
	if (cipher_err){
		cipher_error_handler(cipher_err);
	}

	//set key
	cipher_err=gcry_cipher_setkey(cipher_hd,key,key_size);
	if (cipher_err){
		cipher_error_handler(cipher_err);
	}

	//set iv
	cipher_err=gcry_cipher_setiv(cipher_hd, iv, block_size);
	if (cipher_err){
		cipher_error_handler(cipher_err);
	}

	char *outfilename=malloc(5+strlen(argv[1]));
	strcpy(outfilename,argv[1]);
	strcat(outfilename,".cpt");

	fout = fopen(outfilename,"wb");

	//encrypt
	fread(input_buf,1,file_size,fin);
	memcpy(cipher_buffer,input_buf,block_required*block_size);
	cipher_err=gcry_cipher_encrypt(cipher_hd,cipher_buffer,
					block_required*block_size,NULL,0);
	if (cipher_err){
		cipher_error_handler(cipher_err);
	}
	fwrite(cipher_buffer,1,block_required*block_size,fout);
	gcry_cipher_close(cipher_hd);
	fclose(fin);
	fclose(fout);
	return 0;
}	
