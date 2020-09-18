
#include "aes.h"

// key_length:128, 192, 256
// block_length: 128
// irreducible polynomial: m(x) = x^8 + x^4 + x^3 + x + 1

/*
 * use in MixColumns;
 * in GF(2^8):
 * addition is the bitwise XOR operation;
 * multiplication of a value by {02} can be implemented as a 1-bit left shift  followed
 * by a conditional bitwise XOR with (0001 1011) if the leftmost bit is 1
 */
uint8_t mul(uint8_t scalar, uint8_t s){
    uint8_t p = 0, i = 0, hbs = 0;
    for (i = 0; i < 8; i++) {
        if (scalar & 1) {
            p ^= s;
        }
        hbs = s & 0x80;
        s <<= 1;
        if (hbs) s ^= 0x1b; // 0000 0001 0001 1011
        scalar >>= 1;
    }
    return (uint8_t)p;
}


/*
 * the leftmost 4 bits of the byte are used as a row value
 * the rightmost 4 bits are used as a column value
 */
 void substitute(uint8_t *state, int inv){
    int i;
    for(i = 0;i < 16;i++){
        //row
        unsigned row = state[i] >> 4;
        //col
        unsigned col = state[i] & 0x0f;
        if(!inv)state[i] = s_box[row*16+col];
        else state[i] = inv_s_box[row*16+col];
    }
}


/*
 * the shift row transformation is more substantial than it may first appear;
 * this is because the State is treated as an array of four 4-byte columns;
 * Furthermore, the round key is applied to State column by column;
 * so, shift row make a difference;
 * 使原来单列中的4byte分布到了4列中
 */
static void ShiftRows(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = state[0];
    temp[1] = state[5];
    temp[2] = state[10];
    temp[3] = state[15];
    temp[4] = state[4];
    temp[5] = state[9];
    temp[6] = state[14];
    temp[7] = state[3];
    temp[8] = state[8];
    temp[9] = state[13];
    temp[10] = state[2];
    temp[11] = state[7];
    temp[12] = state[12];
    temp[13] = state[1];
    temp[14] = state[6];
    temp[15] = state[11];
    for(i = 0;i < 16;i++)state[i] = temp[i];
}

void inv_ShiftRows(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = state[0];
    temp[1] = state[13];
    temp[2] = state[10];
    temp[3] = state[7];
    temp[4] = state[4];
    temp[5] = state[1];
    temp[6] = state[14];
    temp[7] = state[11];
    temp[8] = state[8];
    temp[9] = state[5];
    temp[10] = state[2];
    temp[11] = state[15];
    temp[12] = state[12];
    temp[13] = state[9];
    temp[14] = state[6];
    temp[15] = state[3];
    for(i = 0;i < 16;i++)state[i] = temp[i];
}


void MixColumns(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = mul(2, state[0]) ^ mul(3, state[1]) ^ state[2] ^ state[3];
    temp[1] = state[0] ^ mul(2, state[1]) ^ mul(3, state[2]) ^ state[3];
    temp[2] = state[0] ^ state[1] ^ mul(2, state[2]) ^ mul(3, state[3]);
    temp[3] = mul(3, state[0]) ^ state[1] ^ state[2] ^ mul(2, state[3]);
    temp[4] = mul(2, state[4]) ^ mul(3, state[5]) ^ state[6] ^ state[7];
    temp[5] = state[4] ^ mul(2, state[5]) ^ mul(3, state[6]) ^ state[7];
    temp[6] = state[4] ^ state[5] ^ mul(2, state[6]) ^ mul(3, state[7]);
    temp[7] = mul(3, state[4]) ^ state[5] ^ state[6] ^ mul(2, state[7]);
    temp[8] = mul(2, state[8]) ^ mul(3, state[9]) ^ state[10] ^ state[11];
    temp[9] = state[8] ^ mul(2, state[9]) ^ mul(3, state[10]) ^ state[11];
    temp[10] = state[8] ^ state[9] ^ mul(2, state[10]) ^ mul(3, state[11]);
    temp[11] = mul(3, state[8]) ^ state[9] ^ state[10] ^ mul(2, state[11]);
    temp[12] = mul(2, state[12]) ^ mul(3, state[13]) ^ state[14] ^ state[15];
    temp[13] = state[12] ^ mul(2, state[13]) ^ mul(3, state[14]) ^ state[15];
    temp[14] = state[12] ^ state[13] ^ mul(2, state[14]) ^ mul(3, state[15]);
    temp[15] = mul(3, state[12]) ^ state[13] ^ state[14] ^ mul(2, state[15]);
    for(i = 0;i < 16;i++)state[i] = temp[i];
}

void inv_MixColumns(uint8_t *state){
    uint8_t temp[16];
    uint8_t i;
    temp[0] = mul(0x0e, state[0]) ^ mul(0x0b, state[1]) ^ mul(0x0d, state[2]) ^ mul(0x09, state[3]);
    temp[4] = mul(0x0e, state[4]) ^ mul(0x0b, state[5]) ^ mul(0x0d, state[6]) ^ mul(0x09, state[7]);
    temp[8] = mul(0x0e, state[8]) ^ mul(0x0b, state[9]) ^ mul(0x0d, state[10]) ^ mul(0x09, state[11]);
    temp[12] = mul(0x0e, state[12]) ^ mul(0x0b, state[13]) ^ mul(0x0d, state[14]) ^ mul(0x09, state[15]);
    temp[1] = mul(0x09, state[0]) ^ mul(0x0e, state[1]) ^ mul(0x0b, state[2]) ^ mul(0x0d, state[3]);
    temp[5] = mul(0x09, state[4]) ^ mul(0x0e, state[5]) ^ mul(0x0b, state[6]) ^ mul(0x0d, state[7]);
    temp[9] = mul(0x09, state[8]) ^ mul(0x0e, state[9]) ^ mul(0x0b, state[10]) ^ mul(0x0d, state[11]);
    temp[13] = mul(0x09, state[12]) ^ mul(0x0e, state[13]) ^ mul(0x0b, state[14]) ^ mul(0x0d, state[15]);
    temp[2] = mul(0x0d, state[0]) ^ mul(0x09, state[1]) ^ mul(0x0e, state[2]) ^ mul(0x0b, state[3]);
    temp[6] = mul(0x0d, state[4]) ^ mul(0x09, state[5]) ^ mul(0x0e, state[6]) ^ mul(0x0b, state[7]);
    temp[10] = mul(0x0d, state[8]) ^ mul(0x09, state[9]) ^ mul(0x0e, state[10]) ^ mul(0x0b, state[11]);
    temp[14] = mul(0x0d, state[12]) ^ mul(0x09, state[13]) ^ mul(0x0e, state[14]) ^ mul(0x0b, state[15]);
    temp[3] = mul(0x0b, state[0]) ^ mul(0x0d, state[1]) ^ mul(0x09, state[2]) ^ mul(0x0e, state[3]);
    temp[7] = mul(0x0b, state[4]) ^ mul(0x0d, state[5]) ^ mul(  0x09, state[6]) ^ mul(0x0e, state[7]);
    temp[11] = mul(0x0b, state[8]) ^ mul(0x0d, state[9]) ^ mul(0x09, state[10]) ^ mul(0x0e, state[11]);
    temp[15] = mul(0x0b, state[12]) ^ mul(0x0d, state[13]) ^ mul(0x09, state[14]) ^ mul(0x0e, state[15]);
    for(i = 0;i < 16;i++)state[i] = temp[i];
}

/*
 * precomp round key
 * use 16*n memory
 */

void key_expansion(uint8_t *seed, word *keys){
    uint8_t i, j;
    uint8_t row, col;
    uint8_t round_constant = 1;
    for(i = 0;i < 4;i++){
        for(j = 0;j < 4;j++){
            keys[i][j] = seed[i*4+j];
        }
    }
    for(i = 4;i < 44;i++){
        if (i % 4 == 0){
            //RotWord
            for(j = 0;j < 4;j++){
                keys[i][j] = keys[i-1][(j+1)%4];
            }
            //SubWord
            for(j = 0;j < 4;j++){
                row = keys[i][j] >> 4;
                col = (keys[i][j] & 0x0f);
                keys[i][j] = s_box[row*16+col];
            }
            //add RCon
            keys[i][0] ^= round_constant;
            if (round_constant & 0x80)round_constant = (round_constant << 1) ^ 0x1b;
            else round_constant <<= 1;
            // add w[i-4]
            for(j = 0;j < 4;j++)keys[i][j] ^= keys[i-4][j];
        }
        else {
            for(j = 0;j < 4;j++){
                keys[i][j] = keys[i-1][j] ^ keys[i-4][j];
            }
        }
    }
}

void add_Round_key(uint8_t *state, const uint8_t *round_key){
    unsigned i;
    for (i = 0;i < 16;i++)state[i] ^= round_key[i];
}


// single block encrypt
void encrypt(uint8_t *plaintext, uint8_t *seed_key, uint8_t fault){
    //printf("round 0:");
    //printf("\nstart of round: ");
    unsigned i, j, k;
    //for(i = 0;i < 16;i++)printf("%02x", plaintext[i]);
    word keys[44];
    uint8_t round_key[16];
    key_expansion(seed_key, keys);
    add_Round_key(plaintext, seed_key);
    //for(i = 0;i < 16;i++)printf("%02x", plaintext[i]);
    //printf("\n");
    for (i = 0;i < 10;i++){
        //printf("\nround %d: ", i+1);
        //printf("\n  start of round: ");
        //for(j = 0;j < 16;j++)printf("%02x", plaintext[j]);
        for(j = 0;j < 4;j++){
            for (k = 0;k < 4;k++){
                round_key[j*4+k] = keys[4+4*i+j][k];
            }
        }
        substitute(plaintext, 0);
        //printf("\n  After SubBytes: ");
        //for(j = 0;j < 16;j++)printf("%02x", plaintext[i]);
        ShiftRows(plaintext);
        //printf("\n After ShiftRows: ");
        //for(j = 0;j < 16;j++)printf("%02x", plaintext[i]);
        // last round don't have mix column
        if (i != 9){
            MixColumns(plaintext);
            //printf("\nAfter MixColumns: ");
            //for(j = 0;j < 16;j++)printf("%02x", plaintext[i]);
        }
        add_Round_key(plaintext, round_key);
        // 在这里进行故障注入，注入到第九轮末尾
        if (fault && i == 8) {
            plaintext[0] = 0x00;
        }
    }
}

static int get_diff(uint8_t *p1, uint8_t *p2){
    int count = 0, i, temp = 0;
    for (i = 0;i < 16;++i){
        temp =  p1[i] ^ p2[i];
        while (temp){
            if (temp&1 == 1)++count;
            temp >>= 1;
        }
    }
    return count;
}


void decrypt(uint8_t *cipher, uint8_t *seed_key){
    unsigned i, j, k;
    word keys[44];
    uint8_t round_key[16];
    key_expansion(seed_key, keys);
    for (i = 0;i < 4;i++){
        for (j = 0;j < 4;j++){
            round_key[i*4+j] = keys[40+i][j];
        }
    }
    add_Round_key(cipher, round_key);
    // printf("\n--------------add_init_key----------------\n");
    // for(i = 0;i < 16;i++)printf("%02x", cipher[i]);
    for (i = 0;i < 10;i++){
        // printf("\n--------------round_%d----------------\n", i+1);
        for(j = 0;j < 4;j++){
            for (k = 0;k < 4;k++){
                round_key[j*4+k] = keys[36-i*4+j][k];
                // printf("%02x", keys[36-i*4+j][k]);
            }
        }
        // printf("\n");
        inv_ShiftRows(cipher);
        substitute(cipher, 1);
        add_Round_key(cipher, round_key);
        // last round don't have mix column
        if (i != 9)inv_MixColumns(cipher);
        // for(j = 0;j < 16;j++)printf("%02x", cipher[j]);
    }
}

