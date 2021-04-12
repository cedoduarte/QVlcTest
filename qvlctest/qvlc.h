/**
 * @author carlosduarte.1@hotmail.com
 * @date april 3rd 2021
 * @file qvlc.h
 * @brief qvlc
 */

#ifndef QVLC_H
#define QVLC_H

#include <vlc.hpp>
#include <QObject>
#include <QWidget>
#include <QTimer>

/** qvlc */
class qvlc : public QObject
{
    Q_OBJECT
public:
    /** constructor */
    explicit qvlc(QObject *parent = nullptr);

    /** constructor */
    virtual ~qvlc();
signals:
    /** media progress from 0 to 1000 */
    void progress(int p);
public slots:
    /** prepare media */
    void prepare(const QString &filepath);

    /** set video output */
    void setVideoOutput(QWidget *video);

    /** play/pause */
    void play();
private slots:
    /** progress timer timeout */
    void onProgressTimerTimeout();
private:
    VLC::Instance *m_instance;
    VLC::Media *m_media;
    VLC::MediaPlayer *m_player;
    QTimer *m_progressTimer;
};

#endif // QVLC_H
