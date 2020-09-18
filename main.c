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
        int count = 0; //统计无效数量
        uint8_t key[16];
        srand(98);
        random_gen(key); //√
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
                printf("第%d个无效故障\n", count);
            }
        }
        printf("在%d次加密中，无效故障共%d次", sums, count);
        fclose(r);
        fclose(w);
        fclose(wkey);
 //   }
    return 0;
}
