#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->hide();
    connect(&player_, &QMediaPlayer::positionChanged, this, &MainWindow::on_position_changed);
    connect(&player_, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_media_status_changed);
    connect(&player_, &QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playback_state_changed);

    player_.setVideoOutput(ui->video_output);
    player_.setAudioOutput(&audio_output_);
    audio_output_.setVolume(1.f);
}

void MainWindow::on_position_changed(qint64 position) {
    position_changing_ = true;
    ui->sld_pos->setValue(position);
    QString time_form("%1:%2:%3/%4:%5:%6");
    QString time_text = time_form.arg(position / 3600000, 2, 10,QChar('0'))
                            .arg(position / 60000, 2, 10,QChar('0'))
                            .arg(position / 1000, 2, 10,QChar('0'))
                            .arg(dur_ / 3600000, 2, 10,QChar('0'))
                            .arg(dur_ / 60000, 2, 10,QChar('0'))
                            .arg(dur_ / 1000, 2, 10,QChar('0'));
    ui->label->setText(time_text);
    position_changing_ = false;

}

void MainWindow::on_media_status_changed(QMediaPlayer::MediaStatus) {
    dur_ =  player_.duration();
    ui->label->show();
    ui->sld_pos->setMaximum(dur_);
    ui->sld_volume->setMaximum(100);
    ui->sld_volume->setValue(100);
}

void MainWindow::on_playback_state_changed(QMediaPlayer::PlaybackState new_state) {
    if (new_state == QMediaPlayer::PlaybackState::PlayingState) {
        ui->btn_pause->setText("⏸");
    } else {
        ui->btn_pause->setText("⏵");
    }
}

void MainWindow::on_btn_choose_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QString("Открыть файл"),
        QDir::currentPath(), // QDir::currentPath — текущая папка.
        "*.mp4"
        );

    player_.setSource(QUrl::fromLocalFile(fileName));
    player_.play();

}

void MainWindow::on_btn_pause_clicked()    
{
    if (player_.playbackState() == QMediaPlayer::PlaybackState::PausedState) {
        ui->btn_pause->setText("⏵");
        player_.play();

    } else if (player_.playbackState() == QMediaPlayer::PlaybackState::StoppedState ){
        ui->btn_pause->setText("⏵");
        player_.setPosition(0);
        player_.play();
    } else {
        ui->btn_pause->setText("⏸");
        player_.pause();
    }

}

void MainWindow::on_sld_volume_valueChanged(int value)
{
    audio_output_.setVolume(value / 100.f);

}

void MainWindow::on_sld_pos_valueChanged(int value)
{
    if (position_changing_) {
        return;
    }
    player_.setPosition(value);
}

MainWindow::~MainWindow()
{
    delete ui;
}
