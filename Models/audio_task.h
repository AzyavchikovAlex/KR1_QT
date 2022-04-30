#ifndef AUDIO_TASK_H
#define AUDIO_TASK_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>

class AudioTask : public QWidget {
 Q_OBJECT

 public:
  explicit AudioTask(QWidget* parent = nullptr);

 private:
  friend class Controller;

  QPixmap sound_icon_;
  QRadioButton* variant_1_;
  QRadioButton* variant_2_;
  QRadioButton* variant_3_;
  QRadioButton* variant_4_;

  void ManageLayout();

};

#endif //AUDIO_TASK_H
