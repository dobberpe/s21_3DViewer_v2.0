#include "main_window.h"

using namespace s21;

main_window::main_window(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("3dViewer");
  // setMinimumSize(800, 600);

  v = new Viewer;
  v->setMinimumWidth(1024);
  v->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  loadButton = new QPushButton("Выбор файла");
  connect(loadButton, &QPushButton::clicked, this,
          &main_window::on_loadButton_clicked);

  rotation_setup();
  move_setup();  
  scale_setup();  
  appearance_setup();

  screenshotButton = new QPushButton("Снимок экрана");
  connect(screenshotButton, &QPushButton::clicked, this,
          &main_window::on_screenshotButton_clicked);

  gifButton = new QPushButton("Запись экрана");
  gifButton->setCheckable(true);
  connect(gifButton, &QPushButton::clicked, this,
          &main_window::on_gifButton_clicked);

  setupUI();

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &main_window::on_timer_timeout);
}

void main_window::rotation_setup() {
  rotationXSlider = new QSlider(Qt::Horizontal);
  rotationXSlider->setRange(-180, 180);
  connect(rotationXSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationXSlider_valueChanged);
  connect(rotationXSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  rotationYSlider = new QSlider(Qt::Horizontal);
  rotationYSlider->setRange(-180, 180);
  connect(rotationYSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationYSlider_valueChanged);
  connect(rotationYSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  rotationZSlider = new QSlider(Qt::Horizontal);
  rotationZSlider->setRange(-180, 180);
  connect(rotationZSlider, &QSlider::valueChanged, this,
          &main_window::on_rotationZSlider_valueChanged);
  connect(rotationZSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  rotationXSpinBox = new QSpinBox;
  rotationXSpinBox->setRange(-180, 180);
  connect(rotationXSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_rotationXSpinBox_valueChanged);

  rotationYSpinBox = new QSpinBox;
  rotationYSpinBox->setRange(-180, 180);
  connect(rotationYSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_rotationYSpinBox_valueChanged);

  rotationZSpinBox = new QSpinBox;
  rotationZSpinBox->setRange(-180, 180);
  connect(rotationZSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_rotationZSpinBox_valueChanged);
}

void main_window::move_setup() {
  moveXSlider = new QSlider(Qt::Horizontal);
  moveXSlider->setRange(-180, 180);
  connect(moveXSlider, &QSlider::valueChanged, this,
          &main_window::on_moveXSlider_valueChanged);
  connect(moveXSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  moveYSlider = new QSlider(Qt::Horizontal);
  moveYSlider->setRange(-180, 180);
  connect(moveYSlider, &QSlider::valueChanged, this,
          &main_window::on_moveYSlider_valueChanged);
  connect(moveYSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  moveZSlider = new QSlider(Qt::Horizontal);
  moveZSlider->setRange(-180, 180);
  connect(moveZSlider, &QSlider::valueChanged, this,
          &main_window::on_moveZSlider_valueChanged);
  connect(moveZSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  moveXSpinBox = new QSpinBox;
  moveXSpinBox->setRange(-10000, 10000);
  connect(moveXSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_moveXSpinBox_valueChanged);

  moveYSpinBox = new QSpinBox;
  moveYSpinBox->setRange(-10000, 10000);
  connect(moveYSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_moveYSpinBox_valueChanged);

  moveZSpinBox = new QSpinBox;
  moveZSpinBox->setRange(-10000, 10000);
  connect(moveZSpinBox, &QSpinBox::valueChanged, this,
          &main_window::on_moveZSpinBox_valueChanged);
}

void main_window::scale_setup() {
  scaleSlider = new QSlider(Qt::Horizontal);
  scaleSlider->setRange(-180, 180);
  connect(scaleSlider, &QSlider::valueChanged, this,
          &main_window::on_scaleSlider_valueChanged);
  connect(scaleSlider, &QSlider::sliderReleased, this,
          &main_window::on_transformSlider_sliderReleased);

  increaseScaleButton = new QPushButton("+");
  increaseScaleButton->setFixedSize(QSize(20, 20));
  connect(increaseScaleButton, &QPushButton::clicked, this,
          &main_window::on_increaseScaleButton_clicked);

  decreaseScaleButton = new QPushButton("-");
  decreaseScaleButton->setFixedSize(QSize(20, 20));
  connect(decreaseScaleButton, &QPushButton::clicked, this,
          &main_window::on_decreaseScaleButton_clicked);
}

void main_window::appearance_setup() {
  backgroundColorButton = new QPushButton("Фон");
  connect(backgroundColorButton, &QPushButton::clicked, this,
          &main_window::on_backgroundColorButton_clicked);

  vertexColorButton = new QPushButton("Вершины");
  connect(vertexColorButton, &QPushButton::clicked, this,
          &main_window::on_vertexColorButton_clicked);

  edgesColorButton = new QPushButton("Ребра");
  connect(edgesColorButton, &QPushButton::clicked, this,
          &main_window::on_edgesColorButton_clicked);

  vertexSizeSlider = new QSlider(Qt::Horizontal);
  vertexSizeSlider->setRange(1, 20);
  connect(vertexSizeSlider, &QSlider::valueChanged, this,
          &main_window::on_vertexSizeSlider_valueChanged);
  connect(vertexSizeSlider, &QSlider::sliderReleased, this,
          &main_window::on_vertexSizeSlider_sliderReleased);

  edgesWidthSlider = new QSlider(Qt::Horizontal);
  edgesWidthSlider->setRange(1, 20);
  connect(edgesWidthSlider, &QSlider::valueChanged, this,
          &main_window::on_edgesWidthSlider_valueChanged);
  connect(edgesWidthSlider, &QSlider::sliderReleased, this,
          &main_window::on_edgesWidthSlider_sliderReleased);

  projectionTypeComboBox = new QComboBox;
  projectionTypeComboBox->addItem("Центральная");
  projectionTypeComboBox->addItem("Параллельная");
  connect(projectionTypeComboBox, &QComboBox::currentIndexChanged, this,
          &main_window::on_projectionTypeComboBox_indexChanged);

  vertexTypeComboBox = new QComboBox;
  vertexTypeComboBox->addItem("Отсутствуют");
  vertexTypeComboBox->addItem("Круг");
  vertexTypeComboBox->addItem("Квадрат");
  connect(vertexTypeComboBox, &QComboBox::currentIndexChanged, this,
          &main_window::on_vertexTypeComboBox_indexChanged);

  edgesTypeComboBox = new QComboBox;
  edgesTypeComboBox->addItem("Сплошные");
  edgesTypeComboBox->addItem("Штриховка");
  connect(edgesTypeComboBox, &QComboBox::currentIndexChanged, this,
          &main_window::on_edgesTypeComboBox_indexChanged);

  load_settings();
}

main_window::~main_window() {
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

void main_window::on_loadButton_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Open Model File", "",
                                                  "OBJ Files (*.obj)");
  if (!fileName.isEmpty()) {
    rotationXSlider->setValue(0);
    rotationYSlider->setValue(0);
    rotationZSlider->setValue(0);
    moveXSlider->setValue(0);
    moveYSlider->setValue(0);
    moveZSlider->setValue(0);
    scaleSlider->setValue(0);
    curr_rotateX = 0;
    curr_rotateY = 0;
    curr_rotateZ = 0;
    curr_moveX = 0;
    curr_moveY = 0;
    curr_moveZ = 0;
    curr_scale = 0;
    v->loadModel(fileName);
    fnameLabel->setText(QFileInfo(fileName).fileName());
    amountVnumberLabel->setText(QString::number(v->new_data->amount_vertex));
    amountEnumberLabel->setText(
        QString::number(v->new_data->amount_polygon_edges));
    CommandManager::get_CommandManager()->clear();
  }
}

void main_window::on_rotationXSlider_valueChanged(int value) {
    lastCommand = new RotateCommand(v, value - curr_rotateX, 0, 0);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new RotateCommand(*(dynamic_cast<RotateCommand*>(firstCommand)), *(dynamic_cast<RotateCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_rotateX = value;

    spinBoxSetValueMuted(rotationXSpinBox, value);
}

void main_window::on_rotationYSlider_valueChanged(int value) {
    lastCommand = new RotateCommand(v, 0, value - curr_rotateY, 0);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new RotateCommand(*(dynamic_cast<RotateCommand*>(firstCommand)), *(dynamic_cast<RotateCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_rotateY = value;

    spinBoxSetValueMuted(rotationYSpinBox, value);
}

void main_window::on_rotationZSlider_valueChanged(int value) {
    lastCommand = new RotateCommand(v, 0, 0, value - curr_rotateZ);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new RotateCommand(*(dynamic_cast<RotateCommand*>(firstCommand)), *(dynamic_cast<RotateCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_rotateZ = value;

    spinBoxSetValueMuted(rotationZSpinBox, value);
}

void main_window::on_rotationXSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new RotateCommand(v, value - curr_rotateX, 0, 0));
    curr_rotateX = value;

    sliderSetValueMuted(rotationXSlider, value);
}

void main_window::on_rotationYSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new RotateCommand(v, 0, value - curr_rotateY, 0));
    curr_rotateY = value;

    sliderSetValueMuted(rotationYSlider, value);
}

void main_window::on_rotationZSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new RotateCommand(v, 0, 0, value - curr_rotateZ));
    curr_rotateZ = value;

    sliderSetValueMuted(rotationZSlider, value);
}

void main_window::on_moveXSlider_valueChanged(int value) {
    lastCommand = new MoveCommand(v, value - curr_moveX, 0, 0);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new MoveCommand(*(dynamic_cast<MoveCommand*>(firstCommand)), *(dynamic_cast<MoveCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_moveX = value;

    spinBoxSetValueMuted(moveXSpinBox, value);
}

void main_window::on_moveYSlider_valueChanged(int value) {
    lastCommand = new MoveCommand(v, 0, value - curr_moveY, 0);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new MoveCommand(*(dynamic_cast<MoveCommand*>(firstCommand)), *(dynamic_cast<MoveCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_moveY = value;

    spinBoxSetValueMuted(moveYSpinBox, value);
}

void main_window::on_moveZSlider_valueChanged(int value) {
    lastCommand = new MoveCommand(v, 0, 0, value - curr_moveX);
    lastCommand->execute();
    if (!firstCommand) firstCommand = lastCommand;
    else {
        ICommand *tmp = new MoveCommand(*(dynamic_cast<MoveCommand*>(firstCommand)), *(dynamic_cast<MoveCommand*>(lastCommand)));
        delete firstCommand;
        delete lastCommand;
        lastCommand = nullptr;
        firstCommand = tmp;
    }

    curr_moveZ = value;

    spinBoxSetValueMuted(moveZSpinBox, value);
}

void main_window::on_moveXSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new MoveCommand(v, value - curr_moveX, 0, 0));
    curr_moveX = value;

    sliderSetValueMuted(moveXSlider, (value < -180) ? -180 : (value > 180) ? 180 : value);
}

void main_window::on_moveYSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new MoveCommand(v, 0, value - curr_moveY, 0));
    curr_moveY = value;

    sliderSetValueMuted(moveYSlider, (value < -180) ? -180 : (value > 180) ? 180 : value);
}

void main_window::on_moveZSpinBox_valueChanged(int value) {
    CommandManager::get_CommandManager()->executeCommand(new MoveCommand(v, 0, 0, value - curr_moveZ));
    curr_moveZ = value;

    sliderSetValueMuted(moveZSlider, (value < -180) ? -180 : (value > 180) ? 180 : value);
}

void main_window::on_scaleSlider_valueChanged(int value) {
  lastCommand = new ScaleCommand(v, value - curr_scale);
  lastCommand->execute();
  if (!firstCommand) firstCommand = lastCommand;
  else {
      ICommand *tmp = new ScaleCommand(*(dynamic_cast<ScaleCommand*>(firstCommand)), *(dynamic_cast<ScaleCommand*>(lastCommand)));
      delete firstCommand;
      delete lastCommand;
      firstCommand = tmp;
  }

  curr_scale = value;
}

void main_window::on_transformSlider_sliderReleased() {
    CommandManager::get_CommandManager()->addCommand(firstCommand);
    firstCommand = nullptr;
    lastCommand = nullptr;
}

void main_window::on_increaseScaleButton_clicked() {
  scaleSlider->setValue(scaleSlider->value() + 1);
  on_transformSlider_sliderReleased();
}

void main_window::on_decreaseScaleButton_clicked() {
  scaleSlider->setValue(scaleSlider->value() - 1);
  on_transformSlider_sliderReleased();
}

void main_window::on_backgroundColorButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета фона");

  if (color.isValid()) CommandManager::get_CommandManager()->executeCommand(new BgColorCommand(v, color.redF(), color.greenF(), color.blueF()));
}

void main_window::on_vertexColorButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета вершин");

  if (color.isValid()) CommandManager::get_CommandManager()->executeCommand(new VertexColorCommand(v, color.redF(), color.greenF(), color.blueF()));
}

void main_window::on_edgesColorButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Выбор цвета ребер");

  if (color.isValid()) CommandManager::get_CommandManager()->executeCommand(new PolygonColorCommand(v, color.redF(), color.greenF(), color.blueF()));
}

void main_window::on_vertexSizeSlider_valueChanged(int value) {
    if (syncUpdate) VertexSizeCommand(v, value).execute();
    else {
        if (lastCommand && lastCommand != firstCommand) delete lastCommand;
        lastCommand = new VertexSizeCommand(v, value);
        lastCommand->execute();
        if (!firstCommand) firstCommand = lastCommand;
    }
}

void main_window::on_edgesWidthSlider_valueChanged(int value) {
    if (syncUpdate) LineWidthCommand(v, value).execute();
    else {
        if (lastCommand && lastCommand != firstCommand) delete lastCommand;
        lastCommand = new LineWidthCommand(v, value);
        lastCommand->execute();
        if (!firstCommand) firstCommand = lastCommand;
    }
}

void main_window::on_vertexSizeSlider_sliderReleased() {
    CommandManager::get_CommandManager()->executeCommand(new VertexSizeCommand(*(dynamic_cast<VertexSizeCommand*>(firstCommand)), *(dynamic_cast<VertexSizeCommand*>(lastCommand))));
    delete firstCommand;
    firstCommand = nullptr;
    if (lastCommand) delete lastCommand;
    lastCommand = nullptr;
}

void main_window::on_edgesWidthSlider_sliderReleased() {
    CommandManager::get_CommandManager()->executeCommand(new LineWidthCommand(*(dynamic_cast<LineWidthCommand*>(firstCommand)), *(dynamic_cast<LineWidthCommand*>(lastCommand))));
    delete firstCommand;
    firstCommand = nullptr;
    if (lastCommand) delete lastCommand;
    lastCommand = nullptr;
}

void main_window::on_projectionTypeComboBox_indexChanged(int index) {
  if (syncUpdate) ProjectionTypeCommand(v, index).execute();
  else CommandManager::get_CommandManager()->executeCommand(new ProjectionTypeCommand(v, index));
}

void main_window::on_vertexTypeComboBox_indexChanged(int index) {
  if (syncUpdate) VertexTypeCommand(v, index).execute();
  else CommandManager::get_CommandManager()->executeCommand(new VertexTypeCommand(v, index));
}

void main_window::on_edgesTypeComboBox_indexChanged(int index) {
  if (syncUpdate) LineTypeCommand(v, index).execute();
  else CommandManager::get_CommandManager()->executeCommand(new LineTypeCommand(v, index));
}

void main_window::on_screenshotButton_clicked() {
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

void main_window::on_gifButton_clicked() {
  if (!timer->isActive()) {
    gifImage = new QGifImage();
    gifImage->setDefaultDelay(100);
    timer->start(100);
  }
}

void main_window::on_timer_timeout() {
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

void main_window::keyPressEvent(QKeyEvent *event) {
    firstCommand = nullptr;

    if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier)
        firstCommand = CommandManager::get_CommandManager()->undoCommand();  // Обработка Ctrl + Z
    else if (event->key() == Qt::Key_Y && event->modifiers() == Qt::ControlModifier)
        firstCommand = CommandManager::get_CommandManager()->redoCommand();  // Обработка Ctrl + Y

    if (firstCommand) {
        if (dynamic_cast<RotateCommand*>(firstCommand)) {
            auto [x, y, z] = dynamic_cast<RotateCommand*>(firstCommand)->get_angle();

            if (x) {
                curr_rotateX -= x;
                sliderSetValueMuted(rotationXSlider, curr_rotateX);
                spinBoxSetValueMuted(rotationXSpinBox, curr_rotateX);
            } else if (y) {
                curr_rotateY -= y;
                sliderSetValueMuted(rotationYSlider, curr_rotateY);
                spinBoxSetValueMuted(rotationYSpinBox, curr_rotateY);
            } else {
                curr_rotateZ -= z;
                sliderSetValueMuted(rotationZSlider, curr_rotateZ);
                spinBoxSetValueMuted(rotationZSpinBox, curr_rotateZ);
            }
        } else if (dynamic_cast<MoveCommand*>(firstCommand)) {
            auto [x, y, z] = dynamic_cast<MoveCommand*>(firstCommand)->get_shift();

            if (x) {
                curr_moveX -= x;
                sliderSetValueMuted(moveXSlider, (curr_moveX < -180) ? -180 : (curr_moveX > 180) ? 180 : curr_moveX);
                spinBoxSetValueMuted(moveXSpinBox, curr_moveX);
            } else if (y) {
                curr_moveY -= y;
                sliderSetValueMuted(moveYSlider, (curr_moveY < -180) ? -180 : (curr_moveY > 180) ? 180 : curr_moveY);
                spinBoxSetValueMuted(moveYSpinBox, curr_moveY);
            } else {
                curr_moveZ -= z;
                sliderSetValueMuted(moveZSlider, (curr_moveZ < -180) ? -180 : (curr_moveZ > 180) ? 180 : curr_moveZ);
                spinBoxSetValueMuted(moveZSpinBox, curr_moveZ);
            }
        } else if (dynamic_cast<ScaleCommand*>(firstCommand)) {
            double scale = dynamic_cast<ScaleCommand*>(firstCommand)->get_scale();

            curr_scale -= scale;
            sliderSetValueMuted(scaleSlider, curr_scale);
        } else if (dynamic_cast<VertexSizeCommand*>(firstCommand)) sliderSetValueMuted(vertexSizeSlider, dynamic_cast<VertexSizeCommand*>(firstCommand)->get_prev());
        else if (dynamic_cast<LineWidthCommand*>(firstCommand)) sliderSetValueMuted(edgesWidthSlider, dynamic_cast<LineWidthCommand*>(firstCommand)->get_prev());
        else if (dynamic_cast<ProjectionTypeCommand*>(firstCommand)) comboBoxSetValueMuted(projectionTypeComboBox, dynamic_cast<ProjectionTypeCommand*>(firstCommand)->get_type());
        else if (dynamic_cast<VertexTypeCommand*>(firstCommand)) comboBoxSetValueMuted(vertexTypeComboBox, dynamic_cast<VertexTypeCommand*>(firstCommand)->get_type());
        else if (dynamic_cast<LineTypeCommand*>(firstCommand)) comboBoxSetValueMuted(edgesTypeComboBox, dynamic_cast<LineTypeCommand*>(firstCommand)->get_type());
    }

    firstCommand = nullptr;
}

void main_window::save_settings() {
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

void main_window::load_settings() {
  QSettings settings("School21", "3DViewer_v1.0");
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
  syncUpdate = true;
  vertexSizeSlider->setValue(settings.value("vSize", 1).toInt());
  edgesWidthSlider->setValue(settings.value("eWidth", 1).toInt());
  projectionTypeComboBox->setCurrentIndex(settings.value("pType", 0).toInt());
  vertexTypeComboBox->setCurrentIndex(settings.value("vType", 0).toInt());
  edgesTypeComboBox->setCurrentIndex(settings.value("eType", 0).toInt());
  syncUpdate = false;
}

void main_window::rotate_event(double rotate_X, double rotate_Y,
                               double rotate_Z) {
  v->new_data->alpha_x = rotate_X;
  v->new_data->alpha_y = rotate_Y;
  v->new_data->alpha_z = rotate_Z;
  rotate_figure(v->new_data);
  v->update();
}

void main_window::move_event(double move_X, double move_Y, double move_Z) {
  v->new_data->trv.move_vector[crd::x] = move_X;
  v->new_data->trv.move_vector[crd::y] = move_Y;
  v->new_data->trv.move_vector[crd::z] = move_Z;
  move_figure(v->new_data);
  v->update();
}

void main_window::setupUI() {
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

void main_window::setupSliderBox(QVBoxLayout *rightColumnLayout, bool rotate) {
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

void main_window::setupSettings(QVBoxLayout *rightColumnLayout) {
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

void main_window::setupFileInfo(QVBoxLayout *rightColumnLayout) {
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
  amountVnumberLabel = new QLabel(QString::number(v->new_data->amount_vertex));

  QHBoxLayout *amountVLayout = new QHBoxLayout;
  amountVLayout->addWidget(amountVLabel);
  amountVLayout->addItem(amountVSpacer);
  amountVLayout->addWidget(amountVnumberLabel);

  QLabel *amountELabel = new QLabel("Ребер:");
  QSpacerItem *amountESpacer =
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  amountEnumberLabel =
      new QLabel(QString::number(v->new_data->amount_polygon_edges));

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

void main_window::sliderSetValueMuted(QSlider *slider, int value) {
    slider->blockSignals(true);
    slider->setValue(value);
    slider->blockSignals(false);
}

void main_window::spinBoxSetValueMuted(QSpinBox *spinBox, int value) {
    spinBox->blockSignals(true);
    spinBox->setValue(value);
    spinBox->blockSignals(false);
}

void main_window::comboBoxSetValueMuted(QComboBox *comboBox, int value) {
    comboBox->blockSignals(true);
    comboBox->setCurrentIndex(value);
    comboBox->blockSignals(false);
}
