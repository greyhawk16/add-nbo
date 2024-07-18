#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>


uint32_t read_bytes_from_file(const char *file_name) {
    FILE *file = fopen(file_name, "rb");

    // 파일이 존재하지 않을 경우
    if(!file) {
        printf("File %s does not exist.\n", file_name);      
        exit(EXIT_FAILURE);
    }

    // 주어진 파일의 크기 파악
    fseek(file, 0, SEEK_END);   
    size_t file_size = ftell(file);
    rewind(file);        // 파일 포인터를 처음으로 이동

    // 파일 크기가 4바이트 이하라면
    if (file_size < 4) {
        printf("File %s's size is less than 4 bytes\n", file_name);
        exit(EXIT_FAILURE);
    }
    
    uint32_t n;

    size_t read_size = fread(&n, sizeof(uint32_t), 1, file);

    // 파일을 제대로 읽을 수 없다면
    if (read_size != 1) {
        printf("Error occured while reading file %s\n", file_name);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // 여기에서 n을 little endian 에서 big endian으로 변경 
    n = ntohl(n);
    fclose(file);

    return n;
}


int main(int argc, char *argv[]) {
    char name[] = "양준헌";
    printf("[bob13][개발]add-nbo[%s]\n", name);

    if (argc != 3) {
        printf("Requires 2 arguments\n");
        return 0;
    }

    uint32_t a = read_bytes_from_file(argv[1]);
    uint32_t b = read_bytes_from_file(argv[2]);

    printf("First number: 0x%X\n", a);
    printf("Second number: 0x%X\n", b);

    uint32_t ans = a + b;

    printf("Result: 0x%X\n", ans);
    return 0;
}