#include "audio_task.h"

AudioTask::AudioTask(QWidget* parent)
    : QWidget(parent) {
  sound_icon_.load("../Resources/Images/Sound.png");
  assert(!sound_icon_.isNull());
  variant_1_ = new QRadioButton(this);
  variant_2_ = new QRadioButton(this);
  variant_3_ = new QRadioButton(this);
  variant_4_ = new QRadioButton(this);

  variant_1_->setText("Variant 1");
  variant_2_->setText("Variant 2");
  variant_3_->setText("Variant 3");
  variant_4_->setText("Variant 4");

  ManageLayout();
}

void AudioTask::ManageLayout() {
  auto layout1 = new QVBoxLayout(this);
  auto layout2 = new QHBoxLayout();
  layout2->addStretch(1);
  auto label = new QLabel(this);
  label->setPixmap(sound_icon_);
  layout2->addWidget(label, 5);
  layout2->addStretch(1);
  layout1->addLayout(layout2);
  layout1->addStretch(1);
  auto layout3 = new QVBoxLayout();
  layout3->addWidget(variant_1_);
  layout3->addWidget(variant_2_);
  layout3->addWidget(variant_3_);
  layout3->addWidget(variant_4_);
  auto layout4 = new QHBoxLayout();
  layout4->addStretch(1);
  layout4->addLayout(layout3);
  layout4->addStretch(1);
  layout1->addLayout(layout4);
  layout1->addStretch(1);
}

