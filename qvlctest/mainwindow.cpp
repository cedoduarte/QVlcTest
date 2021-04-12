#include "qvlc.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_vlc = new qvlc(this);
    m_progressSlider = new QSlider(Qt::Horizontal, this);
    m_progressSlider->setRange(0, 100);
    m_playButton = new QToolButton(this);
    m_playButton->setIcon(QIcon(":/img/play.png"));
    m_playAction = new QWidgetAction(this);
    m_progressAction = new QWidgetAction(this);
    m_playAction->setDefaultWidget(m_playButton);
    m_progressAction->setDefaultWidget(m_progressSlider);
    ui->toolBar->addAction(m_playAction);
    ui->toolBar->addAction(m_progressAction);
    setCentralWidget(ui->video1);
    connect(m_playButton, &QToolButton::clicked, m_vlc, &qvlc::play);
    connect(m_vlc, &qvlc::progress, m_progressSlider, &QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "/", "Any file (*.*)");
    if (!filepath.isEmpty())
    {
        m_vlc->prepare(filepath);
        m_vlc->setVideoOutput(ui->video1);
        m_vlc->play();
    }
}
