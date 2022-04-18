#include "input_task.h"

InputTask::InputTask(QWidget* parent)
    : QWidget(parent) {
  task_text_ = new QTextEdit(this);
  task_text_->setReadOnly(true);
  answer_ = new QLineEdit(this);

  LoadData();
  current_task_ = 0;
  ShowCurrentTask();

  auto layout1 = new QVBoxLayout(this);
  layout1->addWidget(task_text_, 10);
  layout1->addStretch(1);
  layout1->addWidget(answer_, 0);
}

InputTask::Exercise::Exercise(const QString& text,
                              const QString& answer) {
  this->text = text;
  this->answer = answer;
  used = false;
}

void InputTask::LoadData() {
  QFile data("../Resources/InputTasks/EasyInputTasks.txt");
  assert(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QTextStream fin(&data);
  int tasks_number;
  fin >> tasks_number;

  QString buffer;
  QString task_text;
  QString task_answer;
  QString spacing;
  exercises_.clear();
  for (int i = 0; i < tasks_number; ++i) {
    fin >> buffer;
    assert(buffer == "#QUESTION_IS#");
    fin.readLineInto(&spacing);
    fin.readLineInto(&task_text);
    fin >> buffer;
    assert(buffer == "#ANSWER_IS#");
    fin.readLineInto(&spacing);
    fin.readLineInto(&task_answer);
    exercises_.emplace_back(task_text,
                                  task_answer);
  }
}

void InputTask::ShowCurrentTask() {
  assert(current_task_ >= 0 && current_task_ < exercises_.size());
  if (exercises_[current_task_].used) {
    task_text_->setText(exercises_[current_task_].text + "\nCorrect answer: "
                            + exercises_[current_task_].answer);
  } else {
    task_text_->setText(exercises_[current_task_].text);
  }
  answer_->setText("");
}

bool InputTask::CheckCurrentTask() {
  assert(!exercises_[current_task_].used);
  exercises_[current_task_].used = true;
  task_text_->setText(exercises_[current_task_].text + "\nCorrect answer: "
                          + exercises_[current_task_].answer);
  return (answer_->text().toUpper()
      == exercises_[current_task_].answer.toUpper());
}
