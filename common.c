#include "crypt_demo.h"

/* get key from user's input */
char* get_key_from_password(){
	//init
	char buf[40];
	printf("Input password:");
	fgets(buf,35,stdin);
	char * outbuf=(char *)malloc(SIZE_OF_RETKEY);
	memset(outbuf,0,SIZE_OF_RETKEY);
	
	//get key
	gpg_error_t err = gcry_kdf_derive(buf,strlen(buf),
					GCRY_KDF_PBKDF2,GCRY_MD_SHA512,
					SALT,sizeof(SALT),ITER,
					LEN_OF_RETKEY,outbuf);
	if (err) {
		fprintf(stderr,"a error occured in get_key_from_password()\n");
		fprintf(stderr,"error id = %d\n",err);
		exit(2);
	}
	return outbuf;
}

void cipher_error_handler(int cipher_err){
	fprintf(stderr,"An error occured! id=%d",cipher_err);
	exit(3);
}
int get_file_size(char *filename){
	struct stat file_stat;
	stat(filename,&file_stat);
	return file_stat.st_size;
}
