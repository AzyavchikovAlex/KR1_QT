#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QAction>
#include <QSettings>
#include <QContextMenuEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <iostream>

class MainWindow : public QWidget {
 Q_OBJECT
 public:
  MainWindow(QWidget* parent = nullptr);

 private:
  friend class Controller;

  void ManageLayout();

  void UpdateScore();

  QPushButton* pick_an_option_button_;
  QPushButton* input_answer_button_;
  QPushButton* audio_button_;
  QPushButton* mixed_button_;
  QPushButton* exit_button_;
  QLabel* input_tasks_progress_;
  QLabel* pick_tasks_progress_;
  QLabel* audio_tasks_progress_;
  QLabel* mixed_tasks_progress_;

};

#endif //MAIN_WINDOW_H
