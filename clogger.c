/**
 * clogger.c
 *
 * @brief Logger module
 * @author YamaKen
 *
 */
#include "clogger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
 * ファイル最大サイズ (1MB)
 */
static unsigned int MAX_LOG_FILE_SIZE = 10000000;


/**
 * ログ設定
 */
struct clogger_config_t {
    LOG_TYPE log_type;     //!< ログ出力種別(複数可)
    char filename[256];    //!< ファイル名
    unsigned int filesize; //!< ファイルサイズ
};


/**
 * Logger構造体
 */
struct clogger_t {
    LOG_LEVEL log_level;                  //!< ログレベル
    char log_path[256];                   //!< ログ出力パス
    struct clogger_config_t debug_config; //!< デバッグ設定情報
};


/**
 * 文字列が空白かどうか
 *
 * @param [in] text 文字列
 * @return bool
 */
static bool is_empty_text(const char* text) {
    return (text == NULL || text[0] == '\0');
}


/**
 * ログ出力レベルかどうか
 *
 * @param [in] clogger
 * @param [in] log_level
 * @return bool
 */
static bool can_log_level(const CLogger* clogger, const LOG_LEVEL log_level) {
    return log_level <= clogger->log_level;
}


/**
 * 現在時刻設定
 *
 * @param [out] strtime
 * @param [in] strtime_len
 * @return void
 */
static void set_localetime(char* strtime, size_t strtime_len) {
    time_t t = time(NULL);
    strftime(strtime, strtime_len, "%Y.%m.%d %H:%M:%S", localtime(&t));
}

/**
 * ログメッセージをファイル出力する
 *
 * @param [in] filename
 * @param [in] text
 * @return void
 */
static void clogger_output_file(const char* filename, const char* text) {
    FILE *fd = fopen(filename, "a");

    if (fd == NULL) {
        fprintf(stderr, "[Error] Failed open log file: %s\n", filename);
        return;
    }

    fprintf(fd, "%s\n", text);
    fclose(fd);
}

/**
 * ログ出力設定情報更新
 *
 * @param [in] log_type ログ出力種別
 * @param [in] filesize ファイルサイズ
 * @param [in] filename ログファイル名
 * @return void
 */
static void update_clogger_config_t(struct clogger_config_t* config, const LOG_TYPE log_type, const unsigned int filesize, const char* filename) {
    config->log_type = log_type;
    config->filesize = filesize;
    memset(config->filename, 0, sizeof(config->filename));
    strcpy(config->filename, filename);
}


CLogger* clogger_create(LOG_LEVEL log_level) {
    CLogger* clogger = (CLogger*)malloc(sizeof(CLogger));

    if (clogger == NULL) {
        fprintf(stderr, "[Error] %s Failed create CLogger object\n", __FILE__);
        return NULL;
    }

    clogger->log_level = log_level;
    memset(clogger->log_path, 0, sizeof(clogger->log_path));

    // デバッグ出力設定
    update_clogger_config_t(&clogger->debug_config, LOG_TYPE_CONSOLE | LOG_TYPE_FILE, MAX_LOG_FILE_SIZE, "debug.log");

    return clogger;
}


void clogger_destroy(CLogger *clogger) {
    free(clogger);
}


void clogger_debug(const CLogger *clogger, const char* text) {
    if (clogger == NULL) {
        // todo return operation status
        fprintf(stderr, "[Error] %s CLogger object is null\n", __FILE__);
        return;
    }
    if (can_log_level(clogger, LOG_LEVEL_DEBUG) && !is_empty_text(text)) {
        char message[1024];
        char timestamp[64];
        memset(message, 0, sizeof(message));
        memset(timestamp, 0, sizeof(timestamp));
        set_localetime(timestamp, sizeof(timestamp));
        sprintf(message, "%s [Debug] %s.%d %s", timestamp, __FILE__, __LINE__, text);

        if (clogger->debug_config.log_type & LOG_TYPE_CONSOLE) {
            fprintf(stdout, "%s\n", message);
        }
        if (clogger->debug_config.log_type & LOG_TYPE_FILE) {
            clogger_output_file(clogger->debug_config.filename, message);
        }
    }
}


const char* clogger_get_version() {
    return CLOGGER_VER;
}
