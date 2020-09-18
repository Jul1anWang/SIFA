#include <stdio.h>
#include "ctrl.h"

int main(int argc, char **argv) {
////    //if (*(argv[1]) == "--gen"){
        input_gen(10000);
        printf("write competed!\n");
////    //}

////    if (*argv[1] == "--run"){
        FILE *r = fopen("../plain.txt", "rb");
        FILE *w = fopen("../cipher.txt", "wb");
        FILE *wkey = fopen("../key.txt", "wb");
        int count = 0; //ͳ����Ч����
        uint8_t key[16];
        srand(98);
        random_gen(key); //��
        fwrite(key, sizeof(uint8_t), 16, wkey);
        printf("start:\n");
        int sums = 0;
        while (1) {
            uint8_t p[16];
            uint8_t c[16];
            int flag = 0;
            int num = fread(p, sizeof(uint8_t), 16, r);
            if (num != 16)break;
            ++sums;
            flag = detect_encrypt(p, key, c);
            if (flag == 1) {
                fwrite(c, sizeof(uint8_t), 16, w);
                ++count;
                printf("��%d����Ч����\n", count);
            }
        }
        printf("��%d�μ����У���Ч���Ϲ�%d��", sums, count);
        fclose(r);
        fclose(w);
        fclose(wkey);
 //   }
    return 0;
}
