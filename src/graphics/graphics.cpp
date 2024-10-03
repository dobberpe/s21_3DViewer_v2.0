#include "graphics.h"
#include "command/command.h"

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3dViewer");
  worker = new Worker();
  loadModel(start_file);
}

void Viewer::loadModel(QString filename) {
  worker->parse_file(filename.toUtf8().constData());
  std::vector<double> values{worker->get_x_min(), worker->get_y_min(), worker->get_z_min(),
                             worker->get_x_max(), worker->get_y_max(), worker->get_z_max()};
  const auto [min, max] = std::minmax_element(begin(values), end(values));
  move_coef = (*max - *min) * 1.4;
  update();
}

Worker *Viewer::get_worker() { return worker; }

Viewer::~Viewer() {
  delete worker;
}

void Viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Viewer::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  if (event->buttons() & Qt::LeftButton) {
    CommandManager::instance().combineCommand(new RotateCommand(this, new_pos.x() * 0.00001 * move_coef, -new_pos.y() * 0.00001 * move_coef, 0, false));
    update();
  } else if (event->buttons() & Qt::RightButton) {
    CommandManager::instance().combineCommand(new MoveCommand(this, new_pos.y() * 0.005, new_pos.x() * 0.005, 0, false));
    update();
  }
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) || (event->buttons() & Qt::RightButton)) CommandManager::instance().combinedCommandFinished();
}

void Viewer::wheelEvent(QWheelEvent *event) {
  CommandManager::instance().combineCommand(new ScaleCommand(this, event->angleDelta().y(), false));
  update();
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
    glFrustum(-aspect, aspect, -1.0f, 1.0f, 1.0f, move_coef * 8);
    glTranslatef(0, 0, -move_coef / 2);
  } else {
    float left = -move_coef * aspect;
    float right = move_coef * aspect;
    float bottom = -move_coef;
    float top = move_coef;
    glOrtho(left, right, bottom, top, -move_coef, move_coef * 100);
  }

  // Рисование
  glEnableClientState(GL_VERTEX_ARRAY);
  if (vertex_type != NONE) {
    if (vertex_type == ROUND) glEnable(GL_POINT_SMOOTH);
    glVertexPointer(3, GL_DOUBLE, 0, get<0>(worker->get_vertex_array()));
    glPointSize(vertex_size);
    glColor3f(vertex_r, vertex_g, vertex_b);
    glDrawArrays(GL_POINTS, 0, worker->get_n_vertices());
    if (vertex_type == ROUND) glDisable(GL_POINT_SMOOTH);
  }

  if (line_type == DASH_LINE) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 255);
  }
  glLineWidth(line_width);
  glColor3f(polygon_r, polygon_g, polygon_b);
  auto [polygon_array, n_polygons] = worker->get_polygon_array();
  for (size_t i = 0; i < n_polygons; ++i)
    glDrawElements(GL_LINES, polygon_array[i].n_points, GL_UNSIGNED_INT,
                     polygon_array[i].points.data());
  if (line_type == DASH_LINE) glDisable(GL_LINE_STIPPLE);
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
