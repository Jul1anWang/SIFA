
#include "ctrl.h"

// generate random 16*8 bytes
void random_gen(uint8_t *text)
{
    int i;
    //srand((unsigned )time(NULL));
    for (i = 0;i < 16;i++)text[i] = (uint8_t)rand();
}

void input_gen(int nums){
    FILE *file;
    int i;
    file = fopen("../plain.txt", "wb");
    for (i = 0;i < nums;i++) {
        uint8_t text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        random_gen(text);
//        int i;
//        printf("写入:\n");
//        for(i = 0;i < 16;i++)printf("%02x", text[i]);
//        printf("\n");
        int num = fwrite(text, sizeof(uint8_t), 16, file);
        //printf("write %d nums", num);
    }
    fclose(file);
}

// 每次读一条，是不是还需要记录指针位置
void read(FILE *file, uint8_t *p)
{
    fread(p, sizeof(uint8_t), 16, file);
}


// detection based
int detect_encrypt(uint8_t* plaintext, uint8_t* key, uint8_t *cipher){
    uint8_t c1[16], c2[16];
    uint8_t i, flag = 0;
    for (i = 0;i < 16;i++){
        c1[i] = plaintext[i];
        c2[i] = plaintext[i];
    }
    encrypt(c1, key, 1);
    encrypt(c2, key, 0);
    if (c1[0] == c2[0]) {
        for (i = 0;i < 16;i++)cipher[i] = c1[i];
        flag = 1;
    }
    return flag;
}

uint8_t hyp_re(uint8_t *c, uint8_t *k){
    add_Round_key(c, k);
    inv_ShiftRows(c);
    substitute(c, 1);
    return c[0];
}

//void gen_data(){
//    uint8_t k;
//    for (k = 0;k < 256;k++){
//        for (c : cs):
//            hyp_re(c, k);
//        save(c, "k.txt");
//    }
//}
