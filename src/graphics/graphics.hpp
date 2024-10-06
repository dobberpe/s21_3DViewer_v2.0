#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QtOpenGL>

#define CENTRAL_PR 0
#define PARALLEL_PR 1
#define SOLID_LINE 0
#define DASH_LINE 1
#define NONE 0
#define ROUND 1
#define SQUARE 2

#include "../controller/worker.hpp"
#include "../logger/logger.hpp"

namespace s21 {

class RenderStrategy;

class Viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  Worker *worker;
  RenderStrategy *render_strategy = NULL;

  explicit Viewer(QWidget *parent = nullptr);
  ~Viewer();
  void loadModel(QString filename);
  void setRenderStrategy(RenderStrategy *strategy);
  Worker *get_worker();

  double vertex_r = 0, vertex_g = 0, vertex_b = 1;
  double polygon_r = 0, polygon_g = 1, polygon_b = 0;
  double bg_r = 1, bg_g = 1, bg_b = 1;
  double line_width = 1, vertex_size = 3;
  int projection_type = CENTRAL_PR;  // PARALLEL_PR
  int line_type = SOLID_LINE;        // DASH_LINE
  int vertex_type = SQUARE;          // NONE, ROUND

 signals:
  void mouseRotate(int x, int y);
  void mouseMove(int x, int y);
  void wheelScale(int s);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  QPoint cur_pos;
  QPoint new_pos;
  QString start_file = QString("./obj_files/3dviewer.obj");
  double move_coef;

  Worker *w;
};

}  // namespace s21

#endif  // VIEWER_H
