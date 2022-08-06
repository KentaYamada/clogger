/**
 * clogger.h
 *
 * @brief Logger I/F
 * @author YamaKen
 *
 */
#ifndef _CLOGGER_H__
#define _CLOGGER_H__

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

/**
 *
 */
typedef struct clogger_t CLogger;

/**
 * ログ情報初期化
 *
 * @param [in] log_level ログ出力レベル
 * @return CLogger ログ設定情報ポインタ
 */
extern CLogger* clogger_create(LOG_LEVEL log_level);

/**
 * ログ情報破棄
 *
 * @param [in] clogger ログ情報
 * @return void
 */
extern void clogger_destroy(CLogger* clogger);

/**
 * デバッグログ出力
 *
 * @param [in] clogger ログ情報
 * @return void
 */
extern void clogger_debug(const CLogger* clogger, const char* text);

/**
 * モジュールバージョン取得
 *
 * @return char* バージョン情報
 */
extern const char* clogger_get_version();

#endif // _CLOGGER_H__
