#include "main_window.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent),
      input_answer_button_(new QPushButton("Input answer tasks", this)),
      pick_an_option_button_(new QPushButton("Pick an option tasks", this)),
      audio_button_(new QPushButton("Audio tasks", this)),
      mixed_button_(new QPushButton("Mixed tasks", this)),
      exit_button_(new QPushButton("Exit", this)),
      input_tasks_progress_(new QLabel(this)),
      pick_tasks_progress_(new QLabel(this)),
      audio_tasks_progress_(new QLabel(this)),
      mixed_tasks_progress_(new QLabel(this)) {

  ManageLayout();

  UpdateScore();
}

void MainWindow::ManageLayout() {
  auto layout1 = new QVBoxLayout(this);
  layout1->addStretch(1);
  auto layout2 = new QHBoxLayout();
  layout2->addWidget(input_answer_button_, 10);
  layout2->addWidget(input_tasks_progress_, 3);
  layout1->addLayout(layout2);

  auto layout3 = new QHBoxLayout();
  layout3->addWidget(pick_an_option_button_, 10);
  layout3->addWidget(pick_tasks_progress_, 3);
  layout1->addLayout(layout3);

  auto layout4 = new QHBoxLayout();
  layout4->addWidget(audio_button_, 10);
  layout4->addWidget(audio_tasks_progress_, 3);
  layout1->addLayout(layout4);

  auto layout5 = new QHBoxLayout();
  layout5->addWidget(mixed_button_, 10);
  layout5->addWidget(mixed_tasks_progress_, 3);
  layout1->addLayout(layout5);

  layout1->addStretch(1);
  layout1->addWidget(exit_button_);

}

void MainWindow::UpdateScore() {
  QSettings settings("MyCompany", "Duolingo");
  settings.beginGroup("Sound settings");
  settings.endGroup();
  settings.beginGroup("Best results");

  QString buffer;
  buffer = settings.value("InputMode").toString();
  input_tasks_progress_->setText("Best progress: " + buffer);
  buffer = settings.value("PickMode").toString();
  pick_tasks_progress_->setText("Best progress: " + buffer);
  buffer = settings.value("AudioMode").toString();
  audio_tasks_progress_->setText("Best progress: " + buffer);
  buffer = settings.value("MixedMode").toString();
  mixed_tasks_progress_->setText("Best progress: " + buffer);
  settings.endGroup();

  settings.beginGroup("Current results");
  buffer = settings.value("InputMode").toString();
  input_tasks_progress_->setText(
      input_tasks_progress_->text() + ", Current result: " + buffer);
  buffer = settings.value("PickMode").toString();
  pick_tasks_progress_->setText(
      pick_tasks_progress_->text() + ", Current result: " + buffer);
  buffer = settings.value("AudioMode").toString();
  audio_tasks_progress_->setText(
      audio_tasks_progress_->text() + ", Current result: " + buffer);
  buffer = settings.value("MixedMode").toString();
  mixed_tasks_progress_->setText(
      mixed_tasks_progress_->text() + ", Current result: " + buffer);
  settings.endGroup();
}
