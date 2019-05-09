#ifndef TJA_PLAYER_VITA_CONSTANTS_H
#define TJA_PLAYER_VITA_CONSTANTS_H

// ================================================ //
// || Framerate Limiter                          || //
// ================================================ //
#define MAX_DELAY_MICROSECONDS 16667

// ================================================ //
// || Paths & Extensions                         || //
// ================================================ //

#define DEFAULT_LOG_PATH  "ux0:/data/tjapvita/logs"
#define DEFAULT_TJA_PATH  "ux0:/data/tjapvita/tja"
#define TJA_EXTENSION     ".tja"

// ================================================ //
// || Maximum open-able folders when scanning    || //
// ================================================ //

#define MAX_DEPTH_LEVEL  2

// ================================================ //
// || Default value when data isn't found.       || //
// ================================================ //

#define DATA_NOT_FOUND  0

// ================================================ //
// || Buffer size for TJA parsing                || //
// ================================================ //

#define BUFFER_SIZE  4096

// ================================================ //
// || Used for string conversion                 || //
// ================================================ //

#define SJIS_TABLE_SIZE   25088

// ================================================ //
// || TJA Metadata headers                       || //
// ================================================ //

#define TITLE_HEADER      "TITLE:"
#define SUBTITLE_HEADER   "SUBTITLE:"
#define BPM_HEADER        "BPM:"
#define OFFSET_HEADER     "OFFSET:"
#define SONGVOL_HEADER    "SONGVOL:"
#define SEVOL_HEADER      "SEVOL:"
#define DEMOSTART_HEADER  "DEMOSTART:"
#define SCOREMODE_HEADER  "SCOREMODE:"
#define MUSIC_FILE_HEADER "WAVE:"

#define EDIT_LEVEL_HEADER   "COURSE:Edit\r\n"
#define ONI_LEVEL_HEADER    "COURSE:Oni\r\n"
#define HARD_LEVEL_HEADER   "COURSE:Hard\r\n"
#define NORMAL_LEVEL_HEADER "COURSE:Normal\r\n"
#define EASY_LEVEL_HEADER   "COURSE:Easy\r\n"

#define LEVEL_HEADER "LEVEL:"

// ================================================ //
// || TJA Score Modes                            || //
// ================================================ //

#define SCOREMODE_DONDERFUL 0
#define SCOREMODE_OLDARCADE 1
#define SCOREMODE_NEWARCADE 2

// ================================================ //
// || Difficulty Levels (for selection)          || //
// ================================================ //

#define DIFFICULTY_EDIT   4
#define DIFFICULTY_ONI    3
#define DIFFICULTY_HARD   2
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_EASY   0

// ================================================ //
// || TJA Note Types                             || //
// ================================================ //

/**
 * Represents the various notes that can appear when playing.
 * @example NOTETYPE_DON: A small Don note.
 * @example NOTETYPE_KAT: A small Kat note.
 * @example NOTETYPE_BIG_DON: A big Don note.
 * @example NOTETYPE_BIG_KAT: A big Kat note.
 * @example NOTETYPE_DRUMROLL_START: Represents the start of a drumroll.
 * @example NOTETYPE_BIG_DRUMROLL_START: Represents the start of a big note drumroll.
 * @example NOTETYPE_BALLOON_START: Represents the start of a balloon drumroll.
 * @example NOTETYPE_BALLOON_END: Represents the end of a balloon drumroll. Also used to end a standard drumroll or a
 * potato drumroll.
 * @example NOTETYPE_POTATO_START: Represents the start of a potato drumroll.
 */
#define NOTETYPE_NONE                0
#define NOTETYPE_DON                 1
#define NOTETYPE_KAT                 2
#define NOTETYPE_BIG_DON             3
#define NOTETYPE_BIG_KAT             4
#define NOTETYPE_DRUMROLL_START      5
#define NOTETYPE_BIG_DRUMROLL_START  6
#define NOTETYPE_BALLOON_START       7
#define NOTETYPE_BALLOON_END         8
#define NOTETYPE_POTATO_START        9

// ================================================ //
// || ASCII names for genre folders              || //
// ================================================ //

#define TJAFOLDER_GENRE_ANIME_ASCII          "Anime"
#define TJAFOLDER_GENRE_CLASSIC_ASCII        "Classic"
#define TJAFOLDER_GENRE_GAME_MUSIC_ASCII     "Game Music"
#define TJAFOLDER_GENRE_JPOP_ASCII           "J-Pop"
#define TJAFOLDER_GENRE_NAMCO_ORIGINAL_ASCII "Namco Original"
#define TJAFOLDER_GENRE_VARIETY_ASCII        "Variety"
#define TJAFOLDER_GENRE_VOCALOID_ASCII       "Vocaloid"

// ================================================ //
// || Japanese names for genre folders           || //
// ================================================ //

#define TJAFOLDER_GENRE_ANIME_JP          "アニメ"
#define TJAFOLDER_GENRE_CLASSIC_JP        "クラシック"
#define TJAFOLDER_GENRE_GAME_MUSIC_JP     "ゲームミュージック"
#define TJAFOLDER_GENRE_JPOP_JP           "J-Pop"
#define TJAFOLDER_GENRE_NAMCO_ORIGINAL_JP "ナムコオリジナル"
#define TJAFOLDER_GENRE_VARIETY_JP        "バラエティ"
#define TJAFOLDER_GENRE_VOCALOID_JP       "ボ－カロイド"

// ================================================ //
// || Extra slots to allocate for TJA Folders    || //
// ================================================ //

#define TJAFOLDER_EXTRA_FILE_SLOTS   32

// ================================================ //
// || SongSelectState Constants (Paths, etc.)    || //
// ================================================ //
#define SONGSELECTSTATE_BG_EASY    "ux0:/data/tjapvita/gfx/songselect_bg_easy.png"
#define SONGSELECTSTATE_BG_NORMAL  "ux0:/data/tjapvita/gfx/songselect_bg_normal.png"
#define SONGSELECTSTATE_BG_HARD    "ux0:/data/tjapvita/gfx/songselect_bg_hard.png"
#define SONGSELECTSTATE_BG_ONI     "ux0:/data/tjapvita/gfx/songselect_bg_oni.png"

#define SONGSELECTSTATE_LTRIGGER_SPRITE     "ux0:/data/tjapvita/gfx/l_trigger.png"
#define SONGSELECTSTATE_RTRIGGER_SPRITE     "ux0:/data/tjapvita/gfx/r_trigger.png"

// ================================================ //
// || Logging Utilities                          || //
// ================================================ //

#define TJAFILE_SPRINTF_FORMAT "TjaFile: [filePath=%s; title=%s; subtitle=%s; musicFile=%s; diffEasy=%d; diffNormal=%d;"\
                               "diffHard=%d; diffOni=%d; diffEdit=%d; bpm=%.2f musicVolume=%d; soundEffectVolume=%d;"\
                               "scoreMode=%d; subtitleEffect=%d; offset=%.2f; demoStart=%.2f]"

#define TJADATA_SPRINTF_FORMAT "TjaData: [file=%p; notes=%p; note_count=%d; balloon_hits=%p; balloon_count=%d; bpm_change=%p;"\
                               "bpm_change_count=%d; scroll_change=%p; scroll_change_count=%d]"

#endif //TJA_PLAYER_VITA_CONSTANTS_H
