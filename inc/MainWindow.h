#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include "Scene.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
public:
  explicit MainWindow(QWidget * parent = nullptr);
  ~MainWindow() = default;
  void init(Scene* io_scene);
private slots:

private:
  Ui::MainWindow m_ui;

  Scene* m_gl = nullptr;
  void keyPressEvent(QKeyEvent *_event) override;
  void mouseMoveEvent (QMouseEvent * _event ) override;
  void mousePressEvent ( QMouseEvent *_event) override;
  void mouseReleaseEvent ( QMouseEvent *_event ) override;
  void wheelEvent( QWheelEvent *_event) override;
  void timerEvent(QTimerEvent *_event) override;
};

#endif
