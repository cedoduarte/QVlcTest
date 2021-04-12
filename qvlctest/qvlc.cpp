/**
 * @author carlosduarte.1@hotmail.com
 * @date april 3rd 2021
 * @file qvlc.cpp
 * @brief qvlc
 */

#include "qvlc.h"

qvlc::qvlc(QObject *parent)
    : QObject(parent)
{
    m_instance = new VLC::Instance(0, nullptr);
    m_media = nullptr;
    m_player = nullptr;
    m_progressTimer = new QTimer(this);
    m_progressTimer->setSingleShot(false);
    connect(m_progressTimer, &QTimer::timeout, this, &qvlc::onProgressTimerTimeout);
}

qvlc::~qvlc()
{
    m_progressTimer->stop();
    delete m_player;
    delete m_media;
    delete m_instance;
}

void qvlc::prepare(const QString &filepath)
{
    QString location = QString("file:///%1").arg(filepath);
    if (m_player == nullptr)
    {
        if (m_media == nullptr)
        {
            m_media = new VLC::Media(*m_instance, location.toStdString(), VLC::Media::FromLocation);
            m_player = new VLC::MediaPlayer(*m_media);
        }
    }
    else
    {
        if (m_media != nullptr)
        {
            delete m_media;
            m_media = new VLC::Media(*m_instance, location.toStdString(), VLC::Media::FromLocation);
        }
    }
}

void qvlc::setVideoOutput(QWidget *video)
{
    if (m_player != nullptr)
    {
        m_player->setHwnd(reinterpret_cast<HWND>(video->winId()));
    }
}

void qvlc::play()
{
    if (m_player->isPlaying())
    {
        m_player->pause();
        m_progressTimer->stop();
    }
    else
    {
        m_player->play();
        m_progressTimer->start(1000);
    }
}

void qvlc::onProgressTimerTimeout()
{
    if (m_player != nullptr)
    {
        const float pos = m_player->position();
        if (pos < 0.0f)
        {
            // nothing to do
        }
        else
        {
            const int p = int(100 * pos);
            emit progress(p);
        }
    }
    else
    {
        m_progressTimer->stop();
    }
}
