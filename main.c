/**
 * main.c
 */
#include "clogger.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * メインエントリポイント
 *
 * @return int 処理結果
 */
int main(void) {
    const char* clogger_ver = clogger_get_version();
    printf("clogger version: %s\n", clogger_ver);

    // clogger_debug("My name is %s", "Hello world");
    clogger_info("My name is %s", "Hello world");
    return EXIT_SUCCESS;
}
