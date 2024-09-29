#include "graphics.h"
#include "render_strategy.h"

Viewer::Viewer(QWidget *parent) : QOpenGLWidget(parent) {
  
  setWindowTitle("3dViewer");
  loadModel(start_file);

  CompositeRenderStrategy* compose  = new CompositeRenderStrategy();
  compose->addStrategy(new VertexRenderStrategy());
  compose->addStrategy(new PolygonRenderStrategy());
  setRenderStrategy(compose);

  w = new Worker();
}

void Viewer::loadModel(QString filename) {

  w->parse_file(filename.toUtf8().constData());
  std::vector<double> values{w->get_x_min(), w->get_y_min(), w->get_z_min(),
                             w->get_x_max(), w->get_y_max(), w->get_z_max()};
  const auto [min, max] = std::minmax_element(begin(values), end(values));
  move_coef = (*max - *min) * 1.4;
  update();
}

Viewer::~Viewer() {
  if (render_strategy) {
        delete render_strategy;
    }
}

void Viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Viewer::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  if (event->buttons() & Qt::LeftButton) {
    double x = new_pos.x() * 0.00001 * move_coef;
    double y = -new_pos.y() * 0.00001 * move_coef;
    w->move_figure(x, y, 0);
    update();
  } else if (event->buttons() & Qt::RightButton) {
    double alpha_x = new_pos.y() * 0.005;
    double alpha_y = new_pos.x() * 0.005;
    w->rotate_figure(alpha_x, alpha_y, 0);
    update();
  }
}

void Viewer::wheelEvent(QWheelEvent *event) {
  int num_degrees = event->angleDelta().y();
  curr_scale *= num_degrees < 0 ? 0.99 : 1.01;
  w->scale(curr_scale);
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


void Viewer::setRenderStrategy(RenderStrategy* strategy) {
    if (render_strategy) {
        delete render_strategy;
    }
    render_strategy = strategy;
}