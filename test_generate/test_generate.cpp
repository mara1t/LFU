#include <iostream>
#include <sstream>
#include <stdio.h>

int test_generate(const int n) 
{
    for (int i = 0; i < n; i++) {
        char str[100];
        sprintf(str, "%s%d%s", "tests/data", i, ".dat");
        FILE *tmp_file = fopen(str, "w");

        int page_num = i / 3 + 5;
        int cache_size = (i % 4) * page_num / 4 + 2;

        fprintf(tmp_file, "%d %d ", page_num, cache_size);

        for (int j = 0; j < page_num; j++) {
            fprintf(tmp_file, "%d ", rand() % page_num + 1);
    
        }
        fprintf(tmp_file, "\n");
        fclose(tmp_file);
    }
    return 0;
}

int main() 
{
    test_generate(1000);
    return 0;
}