#ifndef PICK_TASK_H
#define PICK_TASK_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QRadioButton>

class PickTask : public QWidget {
 Q_OBJECT

 public:
  explicit PickTask(QWidget* parent = nullptr);

 private:
  friend class Controller;

  QTextEdit* task_text_;
  QRadioButton* variant_a_;
  QRadioButton* variant_b_;
  QRadioButton* variant_c_;

  void ManageLayout();

};

#endif //PICK_TASK_H
