#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QGroupBox>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QSoundEffect>
#include <QFile>
#include <QMediaPlayer>
#include <QAudioOutput>

class Controller;

#include "Models/main_window.h"
#include "Models/input_task.h"
#include "Models/task.h"

#include <cassert>

class Controller : public QMainWindow {
 Q_OBJECT

 public:
  explicit Controller(QWidget* parent = nullptr);

 private:
  MainWindow* main_page_;
  Task* task_;

  QMenu* settings_menu_;
  QAction* exit_action_;
  QAction* sound_on_action_;
  QAction* sound_off_action_;
  QAction* easy_tasks_action_;
  QAction* hard_tasks_action_;
  QMediaPlayer* music_player_;

  void ManageLayout();

  void ShowMainPage();
  void ShowTaskPage();

  void CreateConnections();
  void CreateActions();
  void CreateMediaPlayer();
  void CreateMenus();

  void SaveAll();

  void closeEvent(QCloseEvent*) override;

 private slots:
  void Exit();
  void SoundOn();
  void SoundOff();
  void EasyTasks();
  void HardTasks();
  void ShowInputTasksMode();
  void ShowPickTasksMode();
  void ShowAudioTasksMode();
  void ShowMixedTasksMode();
  void NextTask();
  void PrevTask();
  void CheckTask();
};

#endif //CONTROLLER_H
