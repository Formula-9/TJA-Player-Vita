#ifndef TJA_PLAYER_VITA_CONSTANTS_H
#define TJA_PLAYER_VITA_CONSTANTS_H

#define DEFAULT_LOG_PATH  "ux0:/data/tjapvita/logs"
#define DEFAULT_TJA_PATH  "ux0:/data/tjapvita/tja"
#define TJA_EXTENSION     ".tja"

#define MAX_DEPTH_LEVEL  2

#define DATA_NOT_FOUND  0

#define BUFFER_SIZE  4096

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

#define SCOREMODE_DONDERFUL 0
#define SCOREMODE_OLDARCADE 1
#define SCOREMODE_NEWARCADE 2

#define DIFFICULTY_EDIT   4
#define DIFFICULTY_ONI    3
#define DIFFICULTY_HARD   2
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_EASY   0

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

#define TJAFILE_SPRINTF_FORMAT "TjaFile: [filePath=%s; title=%s; subtitle=%s; musicFile=%s; diffEasy=%d; diffNormal=%d;"\
                               "diffHard=%d; diffOni=%d; diffEdit=%d; bpm=%.2f musicVolume=%d; soundEffectVolume=%d;"\
                               "scoreMode=%d; subtitleEffect=%d; offset=%.2f; demoStart=%.2f]"

#define TJADATA_SPRINTF_FORMAT "TjaData: [file=%p; notes=%p; note_count=%d; balloon_hits=%p; balloon_count=%d; bpm_change=%p;"\
                               "bpm_change_count=%d; scroll_change=%p; scroll_change_count=%d]"

#endif //TJA_PLAYER_VITA_CONSTANTS_H
