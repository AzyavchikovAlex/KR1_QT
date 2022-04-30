#include "task.h"

Task::Task(QWidget* parent)
    : QWidget(parent),
      next_task_(new QPushButton("Next task", this)),
      prev_task_(new QPushButton("Previous task", this)),
      ready_(new QPushButton("Ready", this)),
      to_main_page_(new QPushButton("Get to the main page", this)),
      input_task_(new InputTask(this)),
      pick_task_(new PickTask(this)),
      audio_task_(new AudioTask(this)),
      progress_(new QProgressBar(this)),
      score_(new QLabel(this)),
      attempts_(new QLabel(this)) {

  input_mode_.tasks_number = input_task_->exercises_.size();

  SetVisibleTasks(false, false, false, false);
  UpdateProgress();

  ManageLayout();
}

void Task::ManageLayout() {
  auto layout1 = new QHBoxLayout();
  layout1->addStretch(1);
  layout1->addWidget(prev_task_);
  layout1->addWidget(ready_);
  layout1->addWidget(next_task_);
  layout1->addStretch(1);
  layout1->addWidget(to_main_page_);

  auto layout2 = new QHBoxLayout();
  layout2->addWidget(input_task_);
  layout2->addWidget(pick_task_);
  layout2->addWidget(audio_task_);

  auto layout3 = new QVBoxLayout(this);
  auto layout4 = new QHBoxLayout();
  layout4->addWidget(score_);
  layout4->addStretch(1);
  layout4->addWidget(attempts_);
  layout4->addStretch(1);
  layout4->addWidget(progress_);
  layout3->addLayout(layout4, 0);
  layout3->addStretch(1);
  layout3->addLayout(layout2, 10);
  layout3->addStretch(1);
  layout3->addLayout(layout1);
}

void Task::SetVisibleTasks(bool input_mode,
                           bool pick_mode,
                           bool audio_mode,
                           bool mixed_mode) {
  if (input_mode_.is_using) {
    assert(!(pick_mode_.is_using || audio_mode_.is_using
        || mixed_mode_.is_using));
  }
  if (pick_mode_.is_using) {
    assert(!(input_mode_.is_using || audio_mode_.is_using
        || mixed_mode_.is_using));
  }
  if (audio_mode_.is_using) {
    assert(!(input_mode_.is_using || pick_mode_.is_using
        || mixed_mode_.is_using));
  }
  if (mixed_mode_.is_using) {
    assert(!(input_mode_.is_using || pick_mode_.is_using
        || audio_mode_.is_using));
  }

  input_mode_.is_using = input_mode;
  pick_mode_.is_using = pick_mode;
  audio_mode_.is_using = audio_mode;
  mixed_mode_.is_using = mixed_mode;
  input_task_->setVisible(input_mode);
  pick_task_->setVisible(pick_mode);
  audio_task_->setVisible(audio_mode);

  if (mixed_mode_.is_using) {
    // to do
  }
}

void Task::ShowCurrentTask() {
  if (input_mode_.is_using) {
    input_task_->ShowCurrentTask();
    prev_task_->setEnabled(input_task_->current_task_ != 0);

    next_task_->setEnabled(
        input_task_->current_task_ != input_task_->exercises_.size() - 1);

    ready_->setEnabled(
        !input_task_->exercises_[input_task_->current_task_].used);
  }
  UpdateProgress();
}

void Task::ShowNextTask() {
  if (input_mode_.is_using) {
    ++input_task_->current_task_;
    ShowCurrentTask();
  }
}

void Task::ShowPrevTask() {
  if (input_mode_.is_using) {
    --input_task_->current_task_;
    ShowCurrentTask();
    return;
  }
}

void Task::CheckCurrentTask() {
  ready_->setEnabled(false);
  if (input_mode_.is_using) {
    if (input_task_->CheckCurrentTask()) {
      PlayHappySong();
      ++input_mode_.correct_tasks;
    } else {
      PlaySadSong();
    }
    --input_mode_.attempts;
  }
  UpdateProgress();
}

void Task::PlayHappySong() {
  auto music_player = new QMediaPlayer(this);
  auto* audioOutput = new QAudioOutput(this);
  music_player->setAudioOutput(audioOutput);
  music_player->setSource(QUrl::fromLocalFile(
      "../Resources/Music/sound2.mp3"));
  audioOutput->setVolume(60);
  music_player->setLoops(1);
  music_player->play();
}

void Task::PlaySadSong() {
  auto music_player = new QMediaPlayer(this);
  auto* audioOutput = new QAudioOutput(this);
  music_player->setAudioOutput(audioOutput);
  music_player->setSource(QUrl::fromLocalFile(
      "../Resources/Music/sound3.mp3"));
  audioOutput->setVolume(60);
  music_player->setLoops(1);
  music_player->play();
}

void Task::UpdateProgress() {
  if (input_mode_.is_using) {
    assert(input_mode_.tasks_number > 0);
    progress_->setValue(
        (100 * input_mode_.correct_tasks) / input_mode_.tasks_number);
    score_->setText("Score: " + QString::number(input_mode_.correct_tasks));
    attempts_->setText("Attempts: " + QString::number(input_mode_.attempts));
  }
}
