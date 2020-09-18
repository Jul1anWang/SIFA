#include "../../aes.h"
#include "../../ctrl.h"
#include<stdio.h>


int main()
{
    uint8_t seed_key[16] = {0xa8, 0xcc, 0x58, 0xf9, 0xb6, 0x53, 0xf4, 0xd6, 0x4d, 0x43, 0x45, 0xc1, 0x34, 0xd6, 0xeb, 0xe8};
    uint8_t last[16];
    // 获取末轮轮密钥
    word keys[44];
    key_expansion(seed_key, keys);
    int j,k;
    for(j = 0;j < 4;j++){
            for (k = 0;k < 4;k++){
                last[j*4+k] = keys[4+4*9+j][k];
            }
        }
    FILE *r = fopen("data.txt", "rb");
    uint8_t cipher[16];
    fread(cipher, sizeof(uint8_t), 16, r);
    uint8_t result = hyp_re(cipher, last);
    printf("%d\n", result);
    fread(cipher, sizeof(uint8_t), 16, r);
    result = hyp_re(cipher, last);
    printf("%d\n", result);
    fread(cipher, sizeof(uint8_t), 16, r);
    result = hyp_re(cipher, last);
    printf("%d\n", result);
    return 0;
}