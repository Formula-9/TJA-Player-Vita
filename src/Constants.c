#include "Constants.h"

const char *DEFAULT_DATABASE_PATH = "ux0:/data/tjapvita/songdb.db";
const char *DEFAULT_LOG_PATH = "ux0:/data/tjapvita/logs";
const char *DEFAULT_TJA_PATH = "ux0:/data/tjapvita/tja";
const char *TJA_EXTENSION = ".tja";

const int MAX_DEPTH_LEVEL = 2;

const int DATA_NOT_FOUND = 0;

const char *TITLE_HEADER = "TITLE:";
const char *SUBTITLE_HEADER = "SUBTITLE:";
const char *BPM_HEADER = "BPM:";
const char *OFFSET_HEADER = "OFFSET:";
const char *SONGVOL_HEADER = "SONGVOL:";
const char *SEVOL_HEADER = "SEVOL:";
const char *DEMOSTART_HEADER = "DEMOSTART:";
const char *SCOREMODE_HEADER = "SCOREMODE:";
const char *MUSIC_FILE_HEADER = "WAVE:";

const char *EDIT_LEVEL_HEADER = "COURSE:Edit\r\n";
const char *ONI_LEVEL_HEADER = "COURSE:Oni\r\n";
const char *HARD_LEVEL_HEADER = "COURSE:Hard\r\n";
const char *NORMAL_LEVEL_HEADER = "COURSE:Normal\r\n";
const char *EASY_LEVEL_HEADER = "COURSE:Easy\r\n";

const char *LEVEL_HEADER = "LEVEL:";

const char *TJAFILE_SPRINTF_FORMAT = "TjaFile: [filePath=%s; title=%s; subtitle=%s; musicFile=%s; diffEasy=%d; diffNormal=%d;"
                                     "diffHard=%d; diffOni=%d; diffEdit=%d; bpm=%d; musicVolume=%d; soundEffectVolume=%d;"
                                     "scoreMode=%d; offset=%f; demoStart=%f]";