#ifndef TASK_H
#define TASK_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QProgressBar>

class Task;

#include "Models/input_task.h"
#include "Models/pick_task.h"
#include "Models/audio_task.h"

class Task : public QWidget {
 Q_OBJECT

 public:
  explicit Task(QWidget* parent = nullptr);

 private:
  friend class Controller;

  struct Mode {
    bool is_using;
    int correct_tasks{0};
    int tasks_number;
    int attempts{0};
  };

  Mode input_mode_{};
  Mode pick_mode_{};
  Mode audio_mode_{};
  Mode mixed_mode_{};

  InputTask* input_task_;
  PickTask* pick_task_;
  AudioTask* audio_task_;

  QPushButton* next_task_;
  QPushButton* prev_task_;
  QPushButton* ready_;
  QPushButton* to_main_page_;
  QProgressBar* progress_;
  QLabel* score_;
  QLabel* attempts_;

  void ManageLayout();

  void SetVisibleTasks(bool, bool, bool, bool);

  void ShowCurrentTask();
  void ShowNextTask();
  void ShowPrevTask();

  void CheckCurrentTask();

  void PlayHappySong();
  void PlaySadSong();

  void UpdateProgress();
};

#endif //TASK_H
