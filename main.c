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
    CLogger* clogger = clogger_create(LOG_LEVEL_DEBUG);
    const char* clogger_ver = clogger_get_version();
    printf("clogger version: %s\n", clogger_ver);
    clogger_debug(clogger, "Hello world");
    clogger_destroy(clogger);

    return EXIT_SUCCESS;
}
