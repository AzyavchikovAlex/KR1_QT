#ifndef INPUT_TASK_H
#define INPUT_TASK_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include <QLineEdit>

#include <vector>

class InputTask : public QWidget {
 Q_OBJECT

 public:
  explicit InputTask(QWidget* parent = nullptr);

 private:
  struct Exercise {
    Exercise() = delete;
    explicit Exercise(const QString&, const QString&);

    QString text;
    QString answer;
    bool used;
  };

  friend class Controller;
  friend class Task;

  void LoadData();

  void ShowCurrentTask();

  bool CheckCurrentTask();

  int current_task_{0};
  QTextEdit* task_text_;
  QLineEdit* answer_;
  std::vector<Exercise> exercises_;

};

#endif //INPUT_TASK_H
