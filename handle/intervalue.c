#include "../ctrl.h"
#include "../aes.h"
#include<string.h>
#include <stdlib.h>
#include<stdio.h>



int main()
{
    FILE *w, *r, *rkey;
    int num = 40, count = 0, right_key=0;
    uint8_t i;
    uint8_t seed_key[16];
    rkey = fopen("../key.txt", "rb");
    fread(seed_key, sizeof(uint8_t), 16, rkey);
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
    
    w = fopen("data/data.txt", "w");
    r = fopen("../cipher.txt", "rb");
    for(i = 0;i < 254;i++){
        //w = fopen(strcat(strcat(strcat(filename, "data/"), s), ".txt"), "a");
        uint8_t cipher[16];
        last[0] = i;
        rewind(r);
        num = 40, count=0;
        while (num--){
            fread(cipher, sizeof(uint8_t), 16, r);
            uint8_t inter =  hyp_re(cipher, last);
            if (inter == 0)++count;
            if (count == num){right_key = i;break;}
            fprintf(w, "guess:%d,  result: %d\n", i, inter);
            //printf("written %d!\n", i);
        }
    }
    printf("end loop\n");
    fclose(w);
    fclose(r);
    printf("right key is: %02x\n", right_key);
    return 0;
}