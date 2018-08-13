#include "backgroundmusic.h"
#include <QDebug>

Musics::Musics(int volum,QString path,int mode)
{
    QMediaPlaylist * m_BGMlist;
    m_BGMlist = new QMediaPlaylist;
    m_BGMlist->addMedia(QUrl::fromLocalFile(path));
    m_BGMlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_BGMlist->setCurrentIndex(1);
    m_player.setPlaylist(m_BGMlist);
    m_player.setVolume(volum);
    m_player.play();
}

Musics::~Musics()
{

}


void Musics::SetVolum(int value)
{
   m_player.setVolume(value);
}
