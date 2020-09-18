

#ifndef SIFA_CTRL_H
#define SIFA_CTRL_H

#include "aes.h"

//generate random plaintext
void input_gen(int);

void random_gen(uint8_t *);
//void read(FILE *, uint8_t*);
int detect_encrypt(uint8_t* plaintext, uint8_t* key, uint8_t *cipher);
uint8_t hyp_re(uint8_t *c, uint8_t *k);


#endif //SIFA_CTRL_H
