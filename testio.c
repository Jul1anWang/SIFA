#include <stdio.h>
#include <stdlib.h>
#define uint8_t unsigned char 

void random_gen(uint8_t *text)
{
    int i;
    for (i = 0;i < 16;i++)text[i] = (uint8_t)rand();
}

void input_gen(int nums){
    FILE *file;
    int i;
    file = fopen("./plain.txt", "a+");
    for (i = 0;i < nums;i++) {
        uint8_t text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        random_gen(text);  
        fwrite(text, sizeof(uint8_t), 16, file);
    }
    fclose(file);
}

int main()
{
    input_gen(2);
    int i;
    FILE *r = fopen("plain.txt", "r");
    unsigned char b[16];
    fread(b, sizeof(unsigned char), 16, r);
    for(i = 0;i < 16;i++)printf("%02x", b[i]);
    printf("\n");
    //fseek(r, 16, SEEK_CUR);
    //r += 16;
    uint8_t text[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    fread(text, sizeof(unsigned char), 16, r);
    for(i = 0;i < 16;i++)printf("%02x", text[i]);
    printf("\n");
    return 0;
}