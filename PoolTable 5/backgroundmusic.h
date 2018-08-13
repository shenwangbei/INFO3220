#ifndef BACKGROUNDMUSIC_H
#define BACKGROUNDMUSIC_H

#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

/**
 * @brief to create bgm when running the poolgame
 * @param number of volum
 * @param the path of bgm
 * @param the mode of bgm
 * @return the display of volum bar
 */

class Musics
{
public:

    QMediaPlayer m_player;
    Musics(int volum,QString path,int mode);
   ~Musics();

    void SetVolum(int value);
private:

 //   QSlider* m_volumSlider;
};
#endif // BACKGROUNDMUSIC_H
