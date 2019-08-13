#ifndef _SONG_SELECT_H_
#define _SONG_SELECT_H_

#define MUSIC_BOX_WIDTH                 480
#define MUSIC_BOX_HEIGHT                80
#define MUSIC_CURRENT_SONG_BOX_HEIGHT   128

#define SONGSELECT_STATUS_CONTINUE          0
#define SONGSELECT_STATUS_EXIT_TO_TITLE     1

void prepareSongSelectData();
void updateSongSelect();
void drawMusicBoxes();
void drawMusicTitles();
void songSelectHandleInput();
void moveToNextSong();
void moveToPreviousSong();
void destroySongSelectData();

#endif //_SONG_SELECT_H_