#include "pick_task.h"

PickTask::PickTask(QWidget* parent)
    : QWidget(parent) {
  task_text_ = new QTextEdit(this);
  variant_a_ = new QRadioButton("A", this);
  variant_b_ = new QRadioButton("B", this);
  variant_c_ = new QRadioButton("C", this);

  task_text_->setText("some pick task");

  ManageLayout();
}

void PickTask::ManageLayout() {
  auto layout1 = new QVBoxLayout();
  layout1->addWidget(variant_a_);
  layout1->addWidget(variant_b_);
  layout1->addWidget(variant_c_);
  layout1->addStretch(1);

  auto layout2 = new QHBoxLayout(this);
  layout2->addWidget(task_text_, 1);
  layout2->addLayout(layout1, 0);
}
