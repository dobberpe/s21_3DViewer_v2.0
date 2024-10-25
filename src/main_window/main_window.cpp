#include "main_window.hpp"

#include "../graphics/render_strategy.hpp"
#include "../logger/logger.hpp"

using namespace s21;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("3dViewer");
  // setMinimumSize(800, 600);

  v = new Viewer;
  CompositeRenderStrategy *compose = new CompositeRenderStrategy();
  compose->addStrategy(new VertexRenderStrategy());
  compose->addStrategy(new PolygonRenderStrategy());
  v->setRenderStrategy(compose);

  connect(v, &Viewer::mouseRotate, this, &MainWindow::on_viewer_mouseRotate);
  connect(v, &Viewer::mouseMove, this, &MainWindow::on_viewer_mouseMove);
  connect(v, &Viewer::wheelScale, this, &MainWindow::on_viewer_wheelScale);

  v->setMinimumWidth(1024);
  v->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  loadButton = new QPushButton("Выбор файла");
  loadButton->setToolTip("Ctrl+O");
  connect(loadButton, &QPushButton::clicked, this,
          &MainWindow::on_loadButton_clicked);

  setup_shortcuts();
  rotation_setup();
  move_setup();
  scale_setup();
  appearance_setup();

  screenshotButton = new QPushButton("Снимок экрана");
  screenshotButton->setToolTip("Ctrl+S");
  connect(screenshotButton, &QPushButton::clicked, this,
          &MainWindow::on_screenshotButton_clicked);

  gifButton = new QPushButton("Запись экрана");
  gifButton->setCheckable(true);
  gifButton->setToolTip("Ctrl+R");
  connect(gifButton, &QPushButton::clicked, this,
          &MainWindow::on_gifButton_clicked);

  setupUI();

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
}

void MainWindow::rotation_setup() {
  rotationXSlider = new QSlider(Qt::Horizontal);
  rotationXSlider->setRange(-18000, 18000);
  connect(rotationXSlider, &QSlider::valueChanged, this,
          &MainWindow::on_rotationXSlider_valueChanged);
  connect(rotationXSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  rotationYSlider = new QSlider(Qt::Horizontal);
  rotationYSlider->setRange(-18000, 18000);
  connect(rotationYSlider, &QSlider::valueChanged, this,
          &MainWindow::on_rotationYSlider_valueChanged);
  connect(rotationYSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  rotationZSlider = new QSlider(Qt::Horizontal);
  rotationZSlider->setRange(-18000, 18000);
  connect(rotationZSlider, &QSlider::valueChanged, this,
          &MainWindow::on_rotationZSlider_valueChanged);
  connect(rotationZSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  rotationXSpinBox = new MySpinBox(this);
  rotationXSpinBox->setRange(-180, 180);
  connect(rotationXSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_rotationXSpinBox_valueChanged);
  connect(rotationXSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);

  rotationYSpinBox = new MySpinBox(this);
  rotationYSpinBox->setRange(-180, 180);
  connect(rotationYSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_rotationYSpinBox_valueChanged);
  connect(rotationYSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);

  rotationZSpinBox = new MySpinBox(this);
  rotationZSpinBox->setRange(-180, 180);
  connect(rotationZSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_rotationZSpinBox_valueChanged);
  connect(rotationZSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);
}

void MainWindow::move_setup() {
  moveXSlider = new QSlider(Qt::Horizontal);
  moveXSlider->setRange(-10000, 10000);
  connect(moveXSlider, &QSlider::valueChanged, this,
          &MainWindow::on_moveXSlider_valueChanged);
  connect(moveXSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  moveYSlider = new QSlider(Qt::Horizontal);
  moveYSlider->setRange(-10000, 10000);
  connect(moveYSlider, &QSlider::valueChanged, this,
          &MainWindow::on_moveYSlider_valueChanged);
  connect(moveYSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  moveZSlider = new QSlider(Qt::Horizontal);
  moveZSlider->setRange(-10000, 10000);
  connect(moveZSlider, &QSlider::valueChanged, this,
          &MainWindow::on_moveZSlider_valueChanged);
  connect(moveZSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  moveXSpinBox = new MySpinBox(this);
  moveXSpinBox->setRange(-10000, 10000);
  connect(moveXSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_moveXSpinBox_valueChanged);
  connect(moveXSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);

  moveYSpinBox = new MySpinBox(this);
  moveYSpinBox->setRange(-10000, 10000);
  connect(moveYSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_moveYSpinBox_valueChanged);
  connect(moveYSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);

  moveZSpinBox = new MySpinBox(this);
  moveZSpinBox->setRange(-10000, 10000);
  connect(moveZSpinBox, &QSpinBox::valueChanged, this,
          &MainWindow::on_moveZSpinBox_valueChanged);
  connect(moveZSpinBox, &MySpinBox::focusLost, this,
          &MainWindow::on_spinBox_focusLost);
}

void MainWindow::scale_setup() {
  scaleSlider = new QSlider(Qt::Horizontal);
  scaleSlider->setRange(-50, 50);
  connect(scaleSlider, &QSlider::valueChanged, this,
          &MainWindow::on_scaleSlider_valueChanged);
  connect(scaleSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  increaseScaleButton = new QPushButton("+");
  increaseScaleButton->setFixedSize(QSize(20, 20));
  connect(increaseScaleButton, &QPushButton::clicked, this,
          &MainWindow::on_increaseScaleButton_clicked);

  decreaseScaleButton = new QPushButton("-");
  decreaseScaleButton->setFixedSize(QSize(20, 20));
  connect(decreaseScaleButton, &QPushButton::clicked, this,
          &MainWindow::on_decreaseScaleButton_clicked);
}

void MainWindow::appearance_setup() {
  backgroundColorButton = new QPushButton("Фон");
  connect(backgroundColorButton, &QPushButton::clicked, this,
          &MainWindow::on_backgroundColorButton_clicked);

  vertexColorButton = new QPushButton("Вершины");
  connect(vertexColorButton, &QPushButton::clicked, this,
          &MainWindow::on_vertexColorButton_clicked);

  edgesColorButton = new QPushButton("Ребра");
  connect(edgesColorButton, &QPushButton::clicked, this,
          &MainWindow::on_edgesColorButton_clicked);

  vertexSizeSlider = new QSlider(Qt::Horizontal);
  vertexSizeSlider->setRange(1, 20);
  connect(vertexSizeSlider, &QSlider::valueChanged, this,
          &MainWindow::on_vertexSizeSlider_valueChanged);
  connect(vertexSizeSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  edgesWidthSlider = new QSlider(Qt::Horizontal);
  edgesWidthSlider->setRange(1, 20);
  connect(edgesWidthSlider, &QSlider::valueChanged, this,
          &MainWindow::on_edgesWidthSlider_valueChanged);
  connect(edgesWidthSlider, &QSlider::sliderReleased, this,
          &MainWindow::on_transformSlider_sliderReleased);

  projectionTypeComboBox = new QComboBox;
  projectionTypeComboBox->addItem("Центральная");
  projectionTypeComboBox->addItem("Параллельная");
  connect(projectionTypeComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_projectionTypeComboBox_indexChanged);

  vertexTypeComboBox = new QComboBox;
  vertexTypeComboBox->addItem("Отсутствуют");
  vertexTypeComboBox->addItem("Круг");
  vertexTypeComboBox->addItem("Квадрат");
  connect(vertexTypeComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_vertexTypeComboBox_indexChanged);

  edgesTypeComboBox = new QComboBox;
  edgesTypeComboBox->addItem("Сплошные");
  edgesTypeComboBox->addItem("Штриховка");
  connect(edgesTypeComboBox, &QComboBox::currentIndexChanged, this,
          &MainWindow::on_edgesTypeComboBox_indexChanged);

  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  delete v;
  delete loadButton;
  delete rotationXSlider;
  delete rotationYSlider;
  delete rotationZSlider;
  delete rotationXSpinBox;
  delete rotationYSpinBox;
  delete rotationZSpinBox;
  delete moveXSlider;
  delete moveYSlider;
  delete moveZSlider;
  delete moveXSpinBox;
  delete moveYSpinBox;
  delete moveZSpinBox;
  delete scaleSlider;
  delete increaseScaleButton;
  delete decreaseScaleButton;
  delete backgroundColorButton;
  delete vertexColorButton;
  delete edgesColorButton;
  delete vertexSizeSlider;
  delete edgesWidthSlider;
  delete projectionTypeComboBox;
  delete vertexTypeComboBox;
  delete edgesTypeComboBox;
  delete screenshotButton;
  delete fnameLabel;
  delete amountVnumberLabel;
  delete amountEnumberLabel;
  delete gifButton;
  if (gifImage != nullptr) delete gifImage;
  if (timer->isActive()) timer->stop();
  delete timer;
}

void MainWindow::on_loadButton_clicked() {
  Logger::instance().log("load file");
  QString fileName = QFileDialog::getOpenFileName(this, "Open Model File", "",
                                                  "OBJ Files (*.obj)");
  if (!fileName.isEmpty()) {
    Logger::instance().log("fname not empty");
    sliderSetValueMuted(rotationXSlider, 0);
    sliderSetValueMuted(rotationYSlider, 0);
    sliderSetValueMuted(rotationZSlider, 0);
    sliderSetValueMuted(moveXSlider, 0);
    sliderSetValueMuted(moveYSlider, 0);
    sliderSetValueMuted(moveZSlider, 0);
    sliderSetValueMuted(scaleSlider, 0);
    curr_rotateX = 0;
    curr_rotateY = 0;
    curr_rotateZ = 0;
    curr_moveX = 0;
    curr_moveY = 0;
    curr_moveZ = 0;
    curr_scale = 0;
    v->loadModel(fileName);
    Logger::instance().log("model loaded");
    fnameLabel->setText(QFileInfo(fileName).fileName());
    amountVnumberLabel->setText(
        QString::number(v->get_worker()->get_n_vertices()));
    amountEnumberLabel->setText(
        QString::number(v->get_worker()->get_n_polygons_edges()));
    Logger::instance().log("info set");
    CommandManager::instance().clear();
  }
}

void MainWindow::on_rotationXSlider_valueChanged(int value) {
  Logger::instance().log("rotate x slider");
  CommandManager::instance().combineCommand(
      new RotateCommand(v, value - curr_rotateX, 0, 0));
  spinBoxSetValueMuted(rotationXSpinBox, value / 100);
  curr_rotateX = value;
}

void MainWindow::on_rotationYSlider_valueChanged(int value) {
  Logger::instance().log("rotate y slider");
  CommandManager::instance().combineCommand(
      new RotateCommand(v, 0, value - curr_rotateY, 0));
  spinBoxSetValueMuted(rotationYSpinBox, value / 100);
  curr_rotateY = value;
}

void MainWindow::on_rotationZSlider_valueChanged(int value) {
  Logger::instance().log("rotate z slider");
  CommandManager::instance().combineCommand(
      new RotateCommand(v, 0, 0, value - curr_rotateZ));
  spinBoxSetValueMuted(rotationZSpinBox, value / 100);
  curr_rotateZ = value;
}

void MainWindow::on_rotationXSpinBox_valueChanged(int value) {
  Logger::instance().log("rotate x spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new RotateCommand(v, value - curr_rotateX, 0, 0));
  curr_rotateX = value;

  sliderSetValueMuted(rotationXSlider, value);
}

void MainWindow::on_rotationYSpinBox_valueChanged(int value) {
  Logger::instance().log("rotate y spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new RotateCommand(v, 0, value - curr_rotateY, 0));
  curr_rotateY = value;

  sliderSetValueMuted(rotationYSlider, value);
}

void MainWindow::on_rotationZSpinBox_valueChanged(int value) {
  Logger::instance().log("rotate z spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new RotateCommand(v, 0, 0, value - curr_rotateZ));
  curr_rotateZ = value;

  sliderSetValueMuted(rotationZSlider, value);
}

void MainWindow::on_viewer_mouseRotate(int x, int y) {
  Logger::instance().log("sync rotate interface " + QString::number(x) + " " +
                         QString::number(y));
  curr_rotateX = (curr_rotateX + x) % 36000;
  curr_rotateY = (curr_rotateY + y) % 36000;
  if (abs(curr_rotateX) > 18000)
    curr_rotateX = (36000 - abs(curr_rotateX)) * NEG_SIGN(curr_rotateX);
  if (abs(curr_rotateY) > 18000)
    curr_rotateY = (36000 - abs(curr_rotateY)) * NEG_SIGN(curr_rotateY);

  sliderSetValueMuted(rotationXSlider, curr_rotateX);
  sliderSetValueMuted(rotationYSlider, curr_rotateY);
  spinBoxSetValueMuted(rotationXSpinBox, curr_rotateX / 100);
  spinBoxSetValueMuted(rotationYSpinBox, curr_rotateY / 100);
}

void MainWindow::on_moveXSlider_valueChanged(int value) {
  Logger::instance().log("move x slider");
  CommandManager::instance().combineCommand(
      new MoveCommand(v, value - curr_moveX, 0, 0));
  spinBoxSetValueMuted(moveXSpinBox, value / 100);
  curr_moveX = value;
}

void MainWindow::on_moveYSlider_valueChanged(int value) {
  Logger::instance().log("move y slider");
  CommandManager::instance().combineCommand(
      new MoveCommand(v, 0, value - curr_moveY, 0));
  spinBoxSetValueMuted(moveYSpinBox, value / 100);
  curr_moveY = value;
}

void MainWindow::on_moveZSlider_valueChanged(int value) {
  Logger::instance().log("move z slider");
  CommandManager::instance().combineCommand(
      new MoveCommand(v, 0, 0, value - curr_moveZ));
  spinBoxSetValueMuted(moveZSpinBox, value / 100);
  curr_moveZ = value;
}

void MainWindow::on_moveXSpinBox_valueChanged(int value) {
  Logger::instance().log("move x spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new MoveCommand(v, value - curr_moveX, 0, 0));
  curr_moveX = value;

  sliderSetValueMuted(moveXSlider, value);
}

void MainWindow::on_moveYSpinBox_valueChanged(int value) {
  Logger::instance().log("move y spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new MoveCommand(v, 0, value - curr_moveY, 0));
  curr_moveY = value;

  sliderSetValueMuted(moveYSlider, value);
}

void MainWindow::on_moveZSpinBox_valueChanged(int value) {
  Logger::instance().log("move z spin");
  value *= 100;
  CommandManager::instance().combineCommand(
      new MoveCommand(v, 0, 0, value - curr_moveZ));
  curr_moveZ = value;

  sliderSetValueMuted(moveZSlider, value);
}

void MainWindow::on_viewer_mouseMove(int x, int y) {
  Logger::instance().log("sync move interface" + QString::number(x) + " " +
                         QString::number(y));
  curr_moveX += x;
  Logger::instance().log("curr_moveX = " + QString::number(curr_moveX));
  curr_moveY += y;
  Logger::instance().log("curr_moveY = " + QString::number(curr_moveY));

  sliderSetValueMuted(moveXSlider, curr_moveX);
  sliderSetValueMuted(moveYSlider, curr_moveY);
  spinBoxSetValueMuted(moveXSpinBox, curr_moveX / 100);
  spinBoxSetValueMuted(moveYSpinBox, curr_moveY / 100);
}

void MainWindow::on_spinBox_focusLost() {
  CommandManager::instance().combinedCommandFinished();
}

void MainWindow::on_scaleSlider_valueChanged(int value) {
  Logger::instance().log("scale slider");
  CommandManager::instance().combineCommand(
      new ScaleCommand(v, value - curr_scale));

  curr_scale = value;
}

void MainWindow::on_transformSlider_sliderReleased() {
  CommandManager::instance().combinedCommandFinished();
}

void MainWindow::on_increaseScaleButton_clicked() {
  Logger::instance().log("+ scale");
  scaleSlider->setValue(scaleSlider->value() + 1);
  on_transformSlider_sliderReleased();
}

void MainWindow::on_decreaseScaleButton_clicked() {
  Logger::instance().log("- scale");
  scaleSlider->setValue(scaleSlider->value() - 1);
  on_transformSlider_sliderReleased();
}

void MainWindow::on_resetScaleAction_triggered() {
  CommandManager::instance().combinedCommandFinished();
  scaleSlider->setValue(0);
  on_transformSlider_sliderReleased();
}

void MainWindow::on_viewer_wheelScale(int scale) {
  Logger::instance().log("sync scale interface" + QString::number(scale));
  curr_scale += scale;
  sliderSetValueMuted(scaleSlider, curr_scale);
}

void MainWindow::on_backgroundColorButton_clicked() {
  Logger::instance().log("bg color button");
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета фона");

  if (color.isValid())
    CommandManager::instance().executeCommand(
        new BgColorCommand(v, color.redF(), color.greenF(), color.blueF()));
}

void MainWindow::on_vertexColorButton_clicked() {
  Logger::instance().log("vertex color button");
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета вершин");

  if (color.isValid())
    CommandManager::instance().executeCommand(
        new VertexColorCommand(v, color.redF(), color.greenF(), color.blueF()));
}

void MainWindow::on_edgesColorButton_clicked() {
  Logger::instance().log("edges color button");
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета ребер");

  if (color.isValid())
    CommandManager::instance().executeCommand(new PolygonColorCommand(
        v, color.redF(), color.greenF(), color.blueF()));
}

void MainWindow::on_vertexSizeSlider_valueChanged(int value) {
  if (syncUpdate)
    VertexSizeCommand(v, value).execute();
  else {
    Logger::instance().log("vertex size slider");
    CommandManager::instance().combineCommand(new VertexSizeCommand(v, value));
  }
}

void MainWindow::on_edgesWidthSlider_valueChanged(int value) {
  if (syncUpdate)
    LineWidthCommand(v, value).execute();
  else {
    Logger::instance().log("edges width slider");
    CommandManager::instance().combineCommand(new LineWidthCommand(v, value));
  }
}

void MainWindow::on_projectionTypeComboBox_indexChanged(int index) {
  if (syncUpdate)
    ProjectionTypeCommand(v, index).execute();
  else {
    Logger::instance().log("pr type box");
    CommandManager::instance().executeCommand(
        new ProjectionTypeCommand(v, index));
  }
}

void MainWindow::on_vertexTypeComboBox_indexChanged(int index) {
  if (syncUpdate)
    VertexTypeCommand(v, index).execute();
  else {
    Logger::instance().log("vertex type box");
    CommandManager::instance().executeCommand(new VertexTypeCommand(v, index));
  }
}

void MainWindow::on_edgesTypeComboBox_indexChanged(int index) {
  if (syncUpdate)
    LineTypeCommand(v, index).execute();
  else {
    Logger::instance().log("edges type box");
    CommandManager::instance().executeCommand(new LineTypeCommand(v, index));
  }
}

void MainWindow::on_screenshotButton_clicked() {
  Logger::instance().log("screenshot button");
  // Создание QPixmap для захвата виджета viewer
  QPixmap pixmap(v->size());
  v->render(&pixmap);

  QStringList filters;
  filters << "JPEG Files (*.jpg)"
          << "BMP Files (*.bmp)";

  QFileDialog dialog(this);
  dialog.setNameFilters(filters);

  QString fileName;
  if (dialog.exec()) {
    fileName = dialog.selectedFiles().first();
    QString selectedFilter = dialog.selectedNameFilter();

    // Определяем формат в зависимости от выбранного фильтра
    QString format;
    if (selectedFilter.contains("*.jpg")) {
      format = "JPEG";
    } else if (selectedFilter.contains("*.bmp")) {
      format = "BMP";
    }

    // Сохранение файла
    if (!fileName.isEmpty()) {
      pixmap.save(fileName, format.toUtf8().constData());
    }
  }
}

void MainWindow::on_gifButton_clicked() {
  Logger::instance().log("gif button");
  if (!timer->isActive()) {
    gifImage = new QGifImage();
    gifImage->setDefaultDelay(100);
    timer->start(100);
  }
}

void MainWindow::on_timer_timeout() {
  Logger::instance().log("gif timeout");
  if (currentFrame < totalFrames) {
    QPixmap pixmap(v->size());
    v->render(&pixmap);
    QImage scaledImage =
        pixmap
            .scaled(pixmap.width() * 0.625, pixmap.height() * 0.625,
                    Qt::KeepAspectRatio)
            .toImage();
    gifImage->addFrame(scaledImage);
    currentFrame++;
  } else {
    timer->stop();
    gifButton->setChecked(false);
    currentFrame = 0;
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранение GIF",
                                                    "", "GIF Files (*.gif)");
    if (!fileName.isEmpty()) {
      gifImage->save(fileName);
    }
    delete gifImage;
    gifImage = nullptr;
  }
}

void MainWindow::on_gifAction_triggered() {
  Logger::instance().log("gif action");
  gifButton->setChecked(true);
  on_gifButton_clicked();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  bool undo = true;

  ICommand *command = nullptr;
  if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier) {
    Logger::instance().log("ctrl z");
    command = CommandManager::instance().undoCommand();  // Обработка Ctrl + Z
  } else if (event->key() == Qt::Key_Y &&
             event->modifiers() == Qt::ControlModifier) {
    Logger::instance().log("ctrl y");
    undo = false;
    command = CommandManager::instance().redoCommand();  // Обработка Ctrl + Y
  } else if (event->key() == Qt::Key_W &&
             event->modifiers() == Qt::ControlModifier) {
    Logger::instance().log("ctrl w");
    close();
  }

  if (command) undo_UI(command, undo);
}

void MainWindow::undo_UI(ICommand *command, bool undo) {
  Logger::instance().log("undo ui");
  if (!undo_transform(command, undo)) undo_appearance(command);
}

bool MainWindow::undo_transform(ICommand *command, bool undo) {
  bool done = false;

  if (dynamic_cast<RotateCommand *>(command)) {
    auto [x, y, z] = dynamic_cast<RotateCommand *>(command)->get_angle();

    if (x) {
      curr_rotateX = undo ? curr_rotateX - x : curr_rotateX + x;
      undo_rotateUI(curr_rotateX, rotationXSlider, rotationXSpinBox);
    }
    if (y) {
      curr_rotateY = undo ? curr_rotateY - y : curr_rotateY + y;
      undo_rotateUI(curr_rotateY, rotationYSlider, rotationYSpinBox);
    }
    if (z) {
      curr_rotateZ = undo ? curr_rotateZ - z : curr_rotateZ + z;
      undo_rotateUI(curr_rotateZ, rotationZSlider, rotationZSpinBox);
    }

    done = true;
  } else if (dynamic_cast<MoveCommand *>(command)) {
    auto [x, y, z] = dynamic_cast<MoveCommand *>(command)->get_shift();

    if (x) {
      curr_moveX = undo ? curr_moveX - x : curr_moveX + x;
      undo_moveUI(curr_moveX, moveXSlider, moveXSpinBox);
    }
    if (y) {
      curr_moveY = undo ? curr_moveY - y : curr_moveY + y;
      undo_moveUI(curr_moveY, moveYSlider, moveYSpinBox);
    }
    if (z) {
      curr_moveZ = undo ? curr_moveZ - z : curr_moveZ + z;
      undo_moveUI(curr_moveZ, moveZSlider, moveZSpinBox);
    }

    done = true;
  } else if (dynamic_cast<ScaleCommand *>(command)) {
    double scale = dynamic_cast<ScaleCommand *>(command)->get_scale();

    curr_scale = undo ? curr_scale - scale : curr_scale + scale;
    sliderSetValueMuted(scaleSlider, curr_scale);

    done = true;
  }

  return done;
}

void MainWindow::undo_appearance(ICommand *command) {
  if (dynamic_cast<VertexSizeCommand *>(command))
    sliderSetValueMuted(vertexSizeSlider,
                        dynamic_cast<VertexSizeCommand *>(command)->get_prev());
  else if (dynamic_cast<LineWidthCommand *>(command))
    sliderSetValueMuted(edgesWidthSlider,
                        dynamic_cast<LineWidthCommand *>(command)->get_prev());
  else if (dynamic_cast<ProjectionTypeCommand *>(command))
    comboBoxSetValueMuted(
        projectionTypeComboBox,
        dynamic_cast<ProjectionTypeCommand *>(command)->get_type());
  else if (dynamic_cast<VertexTypeCommand *>(command))
    comboBoxSetValueMuted(
        vertexTypeComboBox,
        dynamic_cast<VertexTypeCommand *>(command)->get_type());
  else if (dynamic_cast<LineTypeCommand *>(command))
    comboBoxSetValueMuted(edgesTypeComboBox,
                          dynamic_cast<LineTypeCommand *>(command)->get_type());
}

void MainWindow::undo_rotateUI(int &curr_rotate, QSlider *slider,
                               MySpinBox *spinbox) {
  curr_rotate %= 36000;
  if (abs(curr_rotate) > 18000)
    curr_rotate = (36000 - abs(curr_rotate)) * NEG_SIGN(curr_rotate);
  sliderSetValueMuted(slider, curr_rotate);
  spinBoxSetValueMuted(spinbox, curr_rotate / 100);
}

void MainWindow::undo_moveUI(const int &curr_move, QSlider *slider,
                             MySpinBox *spinbox) {
  sliderSetValueMuted(slider, curr_move);
  spinBoxSetValueMuted(spinbox, curr_move / 100);
}

void MainWindow::setup_shortcuts() {
  QAction *screenshotAction = new QAction(this);
  screenshotAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

  connect(screenshotAction, &QAction::triggered, this,
          &MainWindow::on_screenshotButton_clicked);

  QAction *gifAction = new QAction(this);
  gifAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));

  connect(gifAction, &QAction::triggered, this,
          &MainWindow::on_gifAction_triggered);

  QAction *loadAction = new QAction(this);
  loadAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

  connect(loadAction, &QAction::triggered, this,
          &MainWindow::on_loadButton_clicked);

  QAction *increaseScaleAction = new QAction(this);
  increaseScaleAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Equal));

  connect(increaseScaleAction, &QAction::triggered, this,
          &MainWindow::on_increaseScaleButton_clicked);

  QAction *decreaseScaleAction = new QAction(this);
  decreaseScaleAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));

  connect(decreaseScaleAction, &QAction::triggered, this,
          &MainWindow::on_decreaseScaleButton_clicked);

  QAction *resetScaleAction = new QAction(this);
  resetScaleAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));

  connect(resetScaleAction, &QAction::triggered, this,
          &MainWindow::on_resetScaleAction_triggered);

  addAction(screenshotAction);
  addAction(gifAction);
  addAction(loadAction);
  addAction(increaseScaleAction);
  addAction(decreaseScaleAction);
  addAction(resetScaleAction);
}

void MainWindow::save_settings() {
  Logger::instance().log("save settings");
  QSettings settings("School21", "3DViewer_v1.0");
  settings.setValue("bgColor", QColor(static_cast<int>(v->bg_r * 255),
                                      static_cast<int>(v->bg_g * 255),
                                      static_cast<int>(v->bg_b * 255)));
  settings.setValue("vColor", QColor(static_cast<int>(v->vertex_r * 255),
                                     static_cast<int>(v->vertex_g * 255),
                                     static_cast<int>(v->vertex_b * 255)));
  settings.setValue("eColor", QColor(static_cast<int>(v->polygon_r * 255),
                                     static_cast<int>(v->polygon_g * 255),
                                     static_cast<int>(v->polygon_b * 255)));
  settings.setValue("vSize", v->vertex_size);
  settings.setValue("eWidth", v->line_width);
  settings.setValue("pType", v->projection_type);
  settings.setValue("vType", v->vertex_type);
  settings.setValue("eType", v->line_type);
}

void MainWindow::load_settings() {
  Logger::instance().log("load settings");
  QSettings settings("School21", "3DViewer_v1.0");
  Logger::instance().log("settings opened");
  QColor bgColor(settings.value("bgColor", "#FFFFFF").toString());
  QColor vColor(settings.value("vColor", "#00FF00").toString());
  QColor eColor(settings.value("eColor", "#0000FF").toString());
  v->bg_r = bgColor.redF();
  v->bg_g = bgColor.greenF();
  v->bg_b = bgColor.blueF();
  v->vertex_r = vColor.redF();
  v->vertex_g = vColor.greenF();
  v->vertex_b = vColor.blueF();
  v->polygon_r = eColor.redF();
  v->polygon_g = eColor.greenF();
  v->polygon_b = eColor.blueF();
  Logger::instance().log("color set");
  syncUpdate = true;
  vertexSizeSlider->setValue(settings.value("vSize", 1).toInt());
  edgesWidthSlider->setValue(settings.value("eWidth", 1).toInt());
  Logger::instance().log("size sliders set");
  projectionTypeComboBox->setCurrentIndex(settings.value("pType", 0).toInt());
  vertexTypeComboBox->setCurrentIndex(settings.value("vType", 0).toInt());
  edgesTypeComboBox->setCurrentIndex(settings.value("eType", 0).toInt());
  Logger::instance().log("type set");
  syncUpdate = false;
}

void MainWindow::setupUI() {
  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  QGridLayout *mainLayout = new QGridLayout(centralWidget);
  mainLayout->addWidget(v, 0, 0, 1, 1);  // Занимает весь левый столбец

  QLabel *scaleLabel = new QLabel("Масштабирование");
  QHBoxLayout *scaleLayout = new QHBoxLayout;
  scaleLayout->addWidget(decreaseScaleButton);
  scaleLayout->addWidget(scaleSlider);
  scaleLayout->addWidget(increaseScaleButton);

  QSpacerItem *spacer =
      new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  // Компоновка для правого столбца
  QVBoxLayout *rightColumnLayout = new QVBoxLayout;
  rightColumnLayout->addWidget(loadButton);
  setupSliderBox(rightColumnLayout, ROTATE);
  setupSliderBox(rightColumnLayout, MOVE);
  rightColumnLayout->addWidget(scaleLabel);
  rightColumnLayout->addLayout(scaleLayout);
  setupSettings(rightColumnLayout);
  rightColumnLayout->addWidget(screenshotButton);
  rightColumnLayout->addWidget(gifButton);
  rightColumnLayout->addItem(spacer);
  setupFileInfo(rightColumnLayout);

  // Добавляем правый столбец в компоновку
  mainLayout->addLayout(rightColumnLayout, 0, 1);

  // Устанавливаем вес столбцов
  mainLayout->setColumnStretch(0, 9);
  mainLayout->setColumnStretch(1, 1);
}

void MainWindow::setupSliderBox(QVBoxLayout *rightColumnLayout, bool rotate) {
  QLabel *label = new QLabel(rotate ? "Поворот" : "Перемещение");

  QLabel *xLabel = new QLabel("x:");
  QHBoxLayout *xSliderLayout = new QHBoxLayout;
  xSliderLayout->addWidget(xLabel);
  xSliderLayout->addWidget(rotate ? rotationXSlider : moveXSlider);
  xSliderLayout->addWidget(rotate ? rotationXSpinBox : moveXSpinBox);

  QLabel *yLabel = new QLabel("y:");
  QHBoxLayout *ySliderLayout = new QHBoxLayout;
  ySliderLayout->addWidget(yLabel);
  ySliderLayout->addWidget(rotate ? rotationYSlider : moveYSlider);
  ySliderLayout->addWidget(rotate ? rotationYSpinBox : moveYSpinBox);

  QLabel *zLabel = new QLabel("z:");
  QHBoxLayout *zSliderLayout = new QHBoxLayout;
  zSliderLayout->addWidget(zLabel);
  zSliderLayout->addWidget(rotate ? rotationZSlider : moveZSlider);
  zSliderLayout->addWidget(rotate ? rotationZSpinBox : moveZSpinBox);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  layout->addLayout(xSliderLayout);
  layout->addLayout(ySliderLayout);
  layout->addLayout(zSliderLayout);

  QFrame *frame = new QFrame;
  frame->setFrameShape(QFrame::Box);
  frame->setLineWidth(1);
  frame->setLayout(layout);

  rightColumnLayout->addWidget(frame);
}

void MainWindow::setupSettings(QVBoxLayout *rightColumnLayout) {
  QLabel *colorLabel = new QLabel("Цветовая палитра");
  QHBoxLayout *colorButtonsLayout = new QHBoxLayout;
  colorButtonsLayout->addWidget(backgroundColorButton);
  colorButtonsLayout->addWidget(vertexColorButton);
  colorButtonsLayout->addWidget(edgesColorButton);

  QVBoxLayout *colorLayout = new QVBoxLayout;
  colorLayout->addWidget(colorLabel);
  colorLayout->addLayout(colorButtonsLayout);

  QFrame *colorFrame = new QFrame;
  colorFrame->setFrameShape(QFrame::Box);
  colorFrame->setLineWidth(1);
  colorFrame->setLayout(colorLayout);

  QLabel *vertexSizeLabel = new QLabel("Размер вершин:");
  QLabel *edgesWidthLabel = new QLabel("Толщина ребер:");

  QGridLayout *resizeLayout = new QGridLayout;
  resizeLayout->addWidget(vertexSizeLabel, 0, 0);
  resizeLayout->addWidget(vertexSizeSlider, 0, 1);
  resizeLayout->addWidget(edgesWidthLabel, 1, 0);
  resizeLayout->addWidget(edgesWidthSlider, 1, 1);

  QLabel *typeLabel = new QLabel("Настройка отображения");

  QLabel *projectionTypeLabel = new QLabel("Проекция:");
  QHBoxLayout *projectionTypeLayout = new QHBoxLayout;
  projectionTypeLayout->addWidget(projectionTypeLabel);
  projectionTypeLayout->addWidget(projectionTypeComboBox);

  QLabel *vertexTypeLabel = new QLabel("Вершины:");
  QHBoxLayout *vertexTypeLayout = new QHBoxLayout;
  vertexTypeLayout->addWidget(vertexTypeLabel);
  vertexTypeLayout->addWidget(vertexTypeComboBox);

  QLabel *edgesTypeLabel = new QLabel("Ребра:");
  QHBoxLayout *edgesTypeLayout = new QHBoxLayout;
  edgesTypeLayout->addWidget(edgesTypeLabel);
  edgesTypeLayout->addWidget(edgesTypeComboBox);

  QVBoxLayout *typeLayout = new QVBoxLayout;
  typeLayout->addWidget(typeLabel);
  typeLayout->addLayout(projectionTypeLayout);
  typeLayout->addLayout(vertexTypeLayout);
  typeLayout->addLayout(edgesTypeLayout);

  QFrame *typeFrame = new QFrame;
  typeFrame->setFrameShape(QFrame::Box);
  typeFrame->setLineWidth(1);
  typeFrame->setLayout(typeLayout);

  rightColumnLayout->addWidget(colorFrame);
  rightColumnLayout->addLayout(resizeLayout);
  rightColumnLayout->addWidget(typeFrame);
}

void MainWindow::setupFileInfo(QVBoxLayout *rightColumnLayout) {
  QLabel *filenameLabel = new QLabel("Имя файла:");
  QSpacerItem *fnameSpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  fnameLabel = new QLabel(QString("3dviewer.obj"));

  QHBoxLayout *fnameLayout = new QHBoxLayout;
  fnameLayout->addWidget(filenameLabel);
  fnameLayout->addItem(fnameSpacer);
  fnameLayout->addWidget(fnameLabel);

  QLabel *amountVLabel = new QLabel("Вершин:");
  QSpacerItem *amountVSpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  amountVnumberLabel =
      new QLabel(QString::number(v->get_worker()->get_n_vertices()));

  QHBoxLayout *amountVLayout = new QHBoxLayout;
  amountVLayout->addWidget(amountVLabel);
  amountVLayout->addItem(amountVSpacer);
  amountVLayout->addWidget(amountVnumberLabel);

  QLabel *amountELabel = new QLabel("Ребер:");
  QSpacerItem *amountESpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  amountEnumberLabel =
      new QLabel(QString::number(v->get_worker()->get_n_polygons_edges()));

  QHBoxLayout *amountELayout = new QHBoxLayout;
  amountELayout->addWidget(amountELabel);
  amountELayout->addItem(amountESpacer);
  amountELayout->addWidget(amountEnumberLabel);

  QVBoxLayout *fileinfoLayout = new QVBoxLayout;
  fileinfoLayout->addLayout(fnameLayout);
  fileinfoLayout->addLayout(amountVLayout);
  fileinfoLayout->addLayout(amountELayout);

  QFrame *frame = new QFrame;
  frame->setFrameShape(QFrame::Box);
  frame->setLineWidth(1);
  frame->setLayout(fileinfoLayout);

  rightColumnLayout->addWidget(frame);
}

void MainWindow::sliderSetValueMuted(QSlider *slider, int value) {
  slider->blockSignals(true);
  slider->setValue(value);
  slider->blockSignals(false);
}

void MainWindow::spinBoxSetValueMuted(QSpinBox *spinBox, int value) {
  spinBox->blockSignals(true);
  spinBox->setValue(value);
  spinBox->blockSignals(false);
}

void MainWindow::comboBoxSetValueMuted(QComboBox *comboBox, int value) {
  comboBox->blockSignals(true);
  comboBox->setCurrentIndex(value);
  comboBox->blockSignals(false);
}

MySpinBox::MySpinBox(MainWindow *w, QWidget *parent)
    : QSpinBox(parent), window(w) {}

void MySpinBox::keyPressEvent(QKeyEvent *event) {
  Logger::instance().log("MySpinBox keyPressEvent");
  if ((event->key() == Qt::Key_Z &&
       event->modifiers() == Qt::ControlModifier) ||
      (event->key() == Qt::Key_Y &&
       event->modifiers() == Qt::ControlModifier) ||
      (event->key() == Qt::Key_W &&
       event->modifiers() == Qt::ControlModifier)) {
    CommandManager::instance().combinedCommandFinished();
    window->keyPressEvent(event);
  } else
    QSpinBox::keyPressEvent(event);
}

void MySpinBox::focusOutEvent(QFocusEvent *event) {
  QSpinBox::focusOutEvent(event);
  emit focusLost();
}
