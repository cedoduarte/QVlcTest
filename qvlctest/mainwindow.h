#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qvlc.h"

#include <QSlider>
#include <QToolButton>
#include <QMainWindow>
#include <QWidgetAction>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void on_actionOpen_triggered();
private:
    Ui::MainWindow *ui;
    qvlc *m_vlc;
    QSlider *m_progressSlider;
    QToolButton *m_playButton;
    QToolButton *m_pauseButton;
    QWidgetAction *m_playAction;
    QWidgetAction *m_pauseAction;
    QWidgetAction *m_progressAction;
};

#endif // MAINWINDOW_H
