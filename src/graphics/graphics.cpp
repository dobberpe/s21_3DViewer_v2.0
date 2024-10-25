#include "graphics.hpp"

#include "../command/command.hpp"
#include "render_strategy.hpp"

using namespace s21;

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3dViewer");
  worker = new Worker();
  loadModel(start_file);
}

void Viewer::loadModel(QString filename) {
  worker->parse_file(filename.toUtf8().constData());
  move_coef = worker->get_move_coeff();
  update();
}

Worker *Viewer::get_worker() { return worker; }

Viewer::~Viewer() {
  delete worker;
  if (render_strategy) {
    delete render_strategy;
  }
}

void Viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Viewer::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  Logger::instance().log("new pos " + QString::number(new_pos.x()) + " " +
                         QString::number(new_pos.y()));
  if (event->buttons() & Qt::LeftButton) {
    Logger::instance().log("mouse rotate");
    CommandManager::instance().executeCommand(
        new RotateCommand(this, new_pos.y(), new_pos.x(), 0));
    emit mouseRotate(new_pos.y(), new_pos.x());
  } else if (event->buttons() & Qt::RightButton) {
    Logger::instance().log("mouse move");
    CommandManager::instance().combineCommand(
        new MoveCommand(this, new_pos.x(), -new_pos.y(), 0));
    emit mouseMove(new_pos.x(), -new_pos.y());
  }
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
  Logger::instance().log("mouse release");
  if ((event->button() == Qt::LeftButton) ||
      (event->button() == Qt::RightButton))
    CommandManager::instance().combinedCommandFinished();
}

void Viewer::wheelEvent(QWheelEvent *event) {
  CommandManager::instance().combineCommand(
      new ScaleCommand(this, event->angleDelta().y() / 120));
  emit wheelScale(event->angleDelta().y() / 120);
}

void Viewer::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

void Viewer::paintGL() {
  glClearColor(bg_r, bg_g, bg_b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = static_cast<float>(width()) / static_cast<float>(height());

  if (projection_type == CENTRAL_PR) {
    glFrustum(-aspect, aspect, -1.0f, 1.0f, 1.0f, move_coef * 80);
    glTranslatef(0, 0, -move_coef * 1.2f);
  } else {
    float left = -move_coef * aspect;
    float right = move_coef * aspect;
    float bottom = -move_coef;
    float top = move_coef;
    glOrtho(left, right, bottom, top, -move_coef * 400, move_coef * 400);
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  render_strategy->render(this);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = static_cast<float>(w) / static_cast<float>(h);

  if (projection_type == CENTRAL_PR) {
    glFrustum(-aspect, aspect, -1.0f, 1.0f, 1.0f, move_coef * 8);
    glTranslatef(0, 0, -move_coef / 2);
  } else {
    float left = -move_coef * aspect;
    float right = move_coef * aspect;
    float bottom = -move_coef;
    float top = move_coef;
    glOrtho(left, right, bottom, top, -move_coef, move_coef * 100);
  }
}

void Viewer::setRenderStrategy(RenderStrategy *strategy) {
  if (render_strategy) {
    delete render_strategy;
  }
  render_strategy = strategy;
}
