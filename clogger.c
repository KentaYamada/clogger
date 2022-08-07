/**
 * clogger.c
 *
 * @brief Logger module
 * @author YamaKen
 *
 */
#include "clogger.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * ファイル最大サイズ (1MB)
 */
static const unsigned int MAX_LOG_FILE_SIZE = 10000000;

/**
 * ログ設定
 */
struct clogger_config_t {
    LOG_LEVEL log_level;   //!< ログレベル
    char* log_level_text;  //!< ログレベル文字列
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
    struct clogger_config_t configs[5];   //!< ログ設定情報
};

static struct clogger_t clogger = {
    LOG_LEVEL_INFO,
    "",
    {
        { LOG_LEVEL_DEBUG,    "Debug",    LOG_TYPE_CONSOLE | LOG_TYPE_FILE, "debug.log",    MAX_LOG_FILE_SIZE },
        { LOG_LEVEL_INFO,     "Info",     LOG_TYPE_CONSOLE | LOG_TYPE_FILE, "info.log",     MAX_LOG_FILE_SIZE },
        { LOG_LEVEL_WARNING,  "Warning",  LOG_TYPE_CONSOLE | LOG_TYPE_FILE, "warning.log",  MAX_LOG_FILE_SIZE },
        { LOG_LEVEL_ERROR,    "Error",    LOG_TYPE_CONSOLE | LOG_TYPE_FILE, "erro.log",     MAX_LOG_FILE_SIZE },
        { LOG_LEVEL_CRITICAL, "Critical", LOG_TYPE_CONSOLE | LOG_TYPE_FILE, "critical.log", MAX_LOG_FILE_SIZE }
    }
};

/**
 * 現在時刻設定
 *
 * @param [out] strtime
 * @param [in] strtime_len
 * @return void
 */
static void set_now_datetime(char* strtime, size_t strtime_len) {
    time_t t = time(NULL);
    memset(strtime, 0, (sizeof strtime_len));
    strftime(strtime, strtime_len, "%Y.%m.%d %H:%M:%S", localtime(&t));
}

/**
 * 該当するログレベルの設定値取得
 *
 * @param [in] log_level ログレベル
 * @return clogger_config_t* 該当のログ設定情報領域(ポインタ)
 */
static struct clogger_config_t* get_clogger_config(const LOG_LEVEL log_level) {
    size_t length = sizeof (clogger.configs) / sizeof (struct clogger_config_t);

    for (size_t i = 0; i < length; i++) {
        if (clogger.configs[i].log_level == log_level) {
            return &clogger.configs[i];
        }
    }

    return NULL;
}

const char* clogger_get_version() {
    return CLOGGER_VER;
}

void clogger_logging(const LOG_LEVEL level, const char* filename, const int line, const char* restrict fmt, ...) {
    const struct clogger_config_t* config = get_clogger_config(level);

    if (config == NULL) {
        return;
    }
    if (config->log_level < clogger.log_level) {
        return;
    }

    // タイムスタンプ発行
    char timestamp[64];
    set_now_datetime(timestamp, sizeof(timestamp));

    // フォーマット解析
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (len < 0) {
        return;
    }

    char message[len + 1];
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    // ログ出力
    FILE *fp = NULL;

    if (config->log_type & LOG_TYPE_CONSOLE) {
        fp = config->log_level < LOG_LEVEL_WARNING ? stdout : stderr;
        fprintf(fp, "%s [%s] %s.%d %s\n", timestamp, config->log_level_text, filename, line, message);
    }
    if (config->log_type & LOG_TYPE_FILE) {
        fp = fopen(config->filename, "a");

        if (fp == NULL) {
            fprintf(stderr, "%s [Error] %s.%d Failed open file %s\n", timestamp, __FILE__, __LINE__, config->filename);
            return;
        }

        fprintf(fp, "%s [%s] %s.%d %s\n", timestamp, config->log_level_text, filename, line, message);
        fclose(fp);
    }
}

void clogger_set_log_level(const LOG_LEVEL log_level) {
    clogger.log_level = log_level;
}

void clogger_set_log_file_path(const char *path, const size_t len) {
    memset(clogger.log_path, 0, len);
    strcpy(clogger.log_path, path);
}

void clogger_set_config_log_type(const LOG_LEVEL log_level, const LOG_TYPE log_type) {
    struct clogger_config_t* config = get_clogger_config(log_level);

    if (config != NULL) {
        config->log_type = log_type;
    }
}

void clogger_set_config_filename(const LOG_LEVEL log_level, const char *filename, const size_t filename_len) {
    struct clogger_config_t* config = get_clogger_config(log_level);

    if (config != NULL) {
        memset(config->filename, 0, filename_len);
        strcpy(config->filename, filename);
    }
}

void clogger_set_config_filesize(const LOG_LEVEL log_level, const unsigned int filesize) {
    struct clogger_config_t* config = get_clogger_config(log_level);

    if (config != NULL) {
        config->filesize = filesize;
    }
}
