/**
 * clogger.h
 *
 * @brief Logger I/F
 * @author YamaKen
 *
 */
#ifndef _CLOGGER_H__
#define _CLOGGER_H__

#include <stdio.h>

/** モジュールバージョン */
#define CLOGGER_VER "1.0.0"

/**
 * ログレベル
 */
typedef enum {
    LOG_LEVEL_DEBUG = 0, //!< デバッグ
    LOG_LEVEL_INFO,      //!< インフォ
    LOG_LEVEL_WARNING,   //!< ワーニング
    LOG_LEVEL_ERROR,     //!< エラー
    LOG_LEVEL_CRITICAL   //!< クリティカル
} LOG_LEVEL;

/**
 * ログ出力種別
 */
typedef enum {
    LOG_TYPE_CONSOLE = 0x01, //!< コンソール出力
    LOG_TYPE_FILE = 0x02     //!< ファイル出力
} LOG_TYPE;

/** デバッグ出力 */
#define clogger_debug(...) clogger_logging(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

/** インフォ出力 */
#define clogger_info(...) clogger_logging(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)

/** ワーニング出力 */
#define clogger_warning(...) clogger_logging(LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)

/** エラー出力 */
#define clogger_error(...) clogger_logging(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)

/** クリティカル出力 */
#define clogger_critical(...) clogger_logging(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)

/**
 * モジュールバージョン取得
 *
 * @return char* バージョン情報
 */
extern const char* clogger_get_version();

/**
 * ログ出力
 *
 * @param [in] level ログレベル
 * @param [in] file ファイル名
 * @param [in] line ログ出力したプログラムの行数
 * @return void
 */
void clogger_logging(const LOG_LEVEL level, const char* filename, const int line, const char* fmt, ...);

/**
 * ログファイルパス設定
 *
 * @param [in] path ファイルパス
 * @param [in] len ファイルパス領域のサイズ
 * @return void
 */
extern void clogger_set_log_file_path(const char* path, const size_t len);

/**
 * ログレベル設定
 *
 * @param [in] path ファイルパス
 * @return void
 */
extern void clogger_set_log_level(const LOG_LEVEL log_level);

/**
 * 対象ログレベルの出力種別設定
 *
 * @param [in] log_level ログレベル
 * @param [in] log_type ログ種別
 * @return void
 */
extern void clogger_set_config_log_type(const LOG_LEVEL log_level, const LOG_TYPE log_type);

/**
 * 対象ログレベルのファイル名設定
 *
 * @param [in] log_level ログレベル
 * @param [in] filename ファイル名
 * @param [in] filename_len ファイル名領域のサイズ
 * @return void
 */
extern void clogger_set_config_filename(const LOG_LEVEL log_level, const char* filename, const size_t filename_len);

/**
 * 対象ログレベルのファイルサイズ設定
 *
 * @param [in] log_level ログレベル
 * @param [in] filesize ファイルサイズ
 * @return void
 */
extern void clogger_set_config_filesize(const LOG_LEVEL log_level, const unsigned int filesize);

#endif // _CLOGGER_H__
