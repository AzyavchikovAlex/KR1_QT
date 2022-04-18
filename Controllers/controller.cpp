#include "controller.h"

Controller::Controller(QWidget* parent)
    : QMainWindow(parent),
      main_page_(new MainWindow(this)),
      task_(new Task(this)),
      music_player_(new QMediaPlayer(this)) {
  CreateMediaPlayer();

  CreateActions();

  CreateMenus();

  CreateConnections();

  ManageLayout();

  if (sound_on_action_->isChecked()) {
    SoundOn();
  }

  ShowMainPage();
}

void Controller::ManageLayout() {
  auto* box = new QGroupBox(this);
  auto layout1 = new QHBoxLayout(box);
  layout1->addWidget(main_page_);
  layout1->addWidget(task_);
  this->setCentralWidget(box);
}

void Controller::CreateMenus() {
  settings_menu_ = menuBar()->addMenu("Menu");
  settings_menu_->addAction(exit_action_);
  settings_menu_->addSeparator();
  settings_menu_->addAction(sound_on_action_);
  settings_menu_->addAction(sound_off_action_);
  settings_menu_->addSeparator();
  settings_menu_->addAction(easy_tasks_action_);
  settings_menu_->addAction(hard_tasks_action_);
  settings_menu_->addSeparator();
}

void Controller::ShowTaskPage() {
  main_page_->hide();
  task_->show();
  task_->ShowCurrentTask();
}

void Controller::CreateConnections() {
  connect(main_page_->input_answer_button_, &QPushButton::clicked,
          this, &Controller::ShowInputTasksMode);
  connect(main_page_->pick_an_option_button_, &QPushButton::clicked,
          this, &Controller::ShowPickTasksMode);
  connect(main_page_->audio_button_, &QPushButton::clicked,
          this, &Controller::ShowAudioTasksMode);
  connect(main_page_->mixed_button_, &QPushButton::clicked,
          this, &Controller::ShowMixedTasksMode);

  connect(main_page_->exit_button_, &QPushButton::clicked,
          this, &Controller::Exit);

  connect(task_->next_task_, &QPushButton::clicked,
          this, &Controller::NextTask);
  connect(task_->prev_task_, &QPushButton::clicked,
          this, &Controller::PrevTask);
  connect(task_->ready_, &QPushButton::clicked,
          this, &Controller::CheckTask);
  connect(task_->to_main_page_, &QPushButton::clicked,
          this, &Controller::ShowMainPage);
}

void Controller::ShowMainPage() {
  main_page_->show();
  main_page_->UpdateScore();
  task_->hide();
  task_->next_task_->setEnabled(true);
  task_->prev_task_->setEnabled(true);
}

void Controller::CreateActions() {
  exit_action_ = new QAction(tr("&Close"), this);
  exit_action_->setShortcuts(QKeySequence::Close);
  connect(exit_action_, &QAction::triggered, this, &Controller::Exit);

  bool sound_on;
  QSettings settings("MyCompany", "Duolingo");
  settings.beginGroup("Sound settings");
  sound_on = settings.value("sound").toBool();
  settings.endGroup();
  sound_on_action_ = new QAction("SoundOn", this);
  sound_on_action_->setCheckable(true);
  sound_on_action_->setChecked(sound_on);
  connect(sound_on_action_, &QAction::triggered, this, &Controller::SoundOn);

  sound_off_action_ = new QAction("SoundOff", this);
  sound_off_action_->setCheckable(true);
  sound_off_action_->setChecked(!sound_on);
  connect(sound_off_action_, &QAction::triggered, this, &Controller::SoundOff);

  easy_tasks_action_ = new QAction("Easy tasks", this);
  easy_tasks_action_->setCheckable(true);
  easy_tasks_action_->setChecked(true);
  connect(sound_off_action_, &QAction::triggered, this, &Controller::EasyTasks);

  hard_tasks_action_ = new QAction("Hard tasks", this);
  hard_tasks_action_->setCheckable(true);
  connect(sound_off_action_, &QAction::triggered, this, &Controller::HardTasks);

}

void Controller::CreateMediaPlayer() {
  auto* audioOutput = new QAudioOutput(this);
  music_player_->setAudioOutput(audioOutput);
  music_player_->setSource(QUrl::fromLocalFile(
      "../Resources/Music/sound1.mp3"));
  audioOutput->setVolume(10);
  music_player_->setLoops(QMediaPlayer::Infinite);
}

void Controller::closeEvent(QCloseEvent* event) {
  auto answer = QMessageBox::question(this,
                                      "Confirm Exit",
                                      "Are you sure you want to exit?");
  if (answer == QMessageBox::Yes) {
    this->close();
  } else {
    event->ignore();
  }
}

void Controller::Exit() {
  auto answer = QMessageBox::question(this,
                                      "Confirm Exit",
                                      "Are you sure you want to exit?");
  if (answer == QMessageBox::Yes) {
    this->close();
  }
}

void Controller::SoundOn() {
  music_player_->play();
  sound_on_action_->setChecked(true);
  sound_off_action_->setChecked(false);
  QSettings settings("MyCompany", "Duolingo");
  settings.beginGroup("Sound settings");
  settings.setValue("sound", true);
  settings.endGroup();
}

void Controller::SoundOff() {
  music_player_->pause();
  sound_on_action_->setChecked(false);
  sound_off_action_->setChecked(true);
  QSettings settings("MyCompany", "Duolingo");
  settings.beginGroup("Sound settings");
  settings.setValue("sound", false);
  settings.endGroup();
}

void Controller::EasyTasks() {

}

void Controller::HardTasks() {

}

void Controller::ShowInputTasksMode() {
  task_->SetVisibleTasks(true, false, false, false);
  ShowTaskPage();
}

void Controller::ShowPickTasksMode() {
  task_->SetVisibleTasks(false, true, false, false);
  ShowTaskPage();
}

void Controller::ShowAudioTasksMode() {
  task_->SetVisibleTasks(false, false, true, false);
  ShowTaskPage();
}

void Controller::ShowMixedTasksMode() {
  task_->SetVisibleTasks(false, false, false, true);
  ShowTaskPage();
}

void Controller::NextTask() {
  task_->ShowNextTask();
}

void Controller::PrevTask() {
  task_->ShowPrevTask();
}

void Controller::CheckTask() {
  task_->CheckCurrentTask();
  SaveAll();
}

void Controller::SaveAll() {
  QSettings settings("MyCompany", "Duolingo");
  settings.beginGroup("Sound settings");
  settings.setValue("sound", sound_on_action_->isChecked());
  settings.endGroup();
  settings.beginGroup("Best results");
  // to do
  // settings.setValue("InputMode",task_->);
  // buffer = settings.value("PickMode").toString();
  // buffer = settings.value("AudioMode").toString();
  // buffer = settings.value("MixedMode").toString();
  settings.endGroup();

  settings.beginGroup("Current results");
  settings.setValue("InputMode", task_->input_mode_.correct_tasks);
  settings.setValue("PickMode", task_->pick_mode_.correct_tasks);
  settings.setValue("AudioMode", task_->audio_mode_.correct_tasks);
  settings.setValue("MixedMode", task_->mixed_mode_.correct_tasks);
  settings.endGroup();
}
