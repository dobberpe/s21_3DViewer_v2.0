#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qgifimage.h>

#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

#include "graphics/graphics.h"
#include "../command/command.h"

#define ROTATE true
#define MOVE false

namespace s21 {

    class main_window : public QMainWindow {
        Q_OBJECT
    public:
        explicit main_window(QWidget *parent = nullptr);
        ~main_window();

    private slots:
        void on_loadButton_clicked();
        void on_rotationXSlider_valueChanged(int value);
        void on_rotationYSlider_valueChanged(int value);
        void on_rotationZSlider_valueChanged(int value);
        void on_rotationXSpinBox_valueChanged(int value);
        void on_rotationYSpinBox_valueChanged(int value);
        void on_rotationZSpinBox_valueChanged(int value);
        void on_moveXSlider_valueChanged(int value);
        void on_moveYSlider_valueChanged(int value);
        void on_moveZSlider_valueChanged(int value);
        void on_moveXSpinBox_valueChanged(int value);
        void on_moveYSpinBox_valueChanged(int value);
        void on_moveZSpinBox_valueChanged(int value);
        void on_scaleSlider_valueChanged(int value);
        void on_transformSlider_sliderReleased();
        void on_increaseScaleButton_clicked();
        void on_decreaseScaleButton_clicked();
        void on_backgroundColorButton_clicked();
        void on_vertexColorButton_clicked();
        void on_edgesColorButton_clicked();
        void on_vertexSizeSlider_valueChanged(int value);
        void on_edgesWidthSlider_valueChanged(int value);
        void on_vertexSizeSlider_sliderReleased();
        void on_edgesWidthSlider_sliderReleased();
        void on_projectionTypeComboBox_indexChanged(int index);
        void on_vertexTypeComboBox_indexChanged(int index);
        void on_edgesTypeComboBox_indexChanged(int index);
        void on_screenshotButton_clicked();
        void on_gifButton_clicked();
        void on_timer_timeout();
        void on_gifAction_triggered();

    protected:
        void keyPressEvent(QKeyEvent *event) override;

    private:
        void setup_shortcuts();
        void rotation_setup();
        void move_setup();
        void scale_setup();
        void appearance_setup();
        void save_settings();
        void load_settings();
        void setupUI();
        void setupSliderBox(QVBoxLayout *rightColumnLayout, bool rotate);
        void setupSettings(QVBoxLayout *rightColumnLayout);
        void setupFileInfo(QVBoxLayout *rightColumnLayout);
        void sliderSetValueMuted(QSlider *slider, int value);
        void spinBoxSetValueMuted(QSpinBox *spinBox, int value);
        void comboBoxSetValueMuted(QComboBox *comboBox, int value);

        Viewer *v;

        bool syncUpdate = false;
        ICommand* firstCommand = nullptr;
        ICommand* lastCommand = nullptr;

        QPushButton *loadButton;
        QSlider *rotationXSlider;
        QSlider *rotationYSlider;
        QSlider *rotationZSlider;
        QSpinBox *rotationXSpinBox;
        QSpinBox *rotationYSpinBox;
        QSpinBox *rotationZSpinBox;
        QSlider *moveXSlider;
        QSlider *moveYSlider;
        QSlider *moveZSlider;
        QSpinBox *moveXSpinBox;
        QSpinBox *moveYSpinBox;
        QSpinBox *moveZSpinBox;
        QSlider *scaleSlider;
        QPushButton *increaseScaleButton;
        QPushButton *decreaseScaleButton;
        QPushButton *backgroundColorButton;
        QPushButton *vertexColorButton;
        QPushButton *edgesColorButton;
        QSlider *vertexSizeSlider;
        QSlider *edgesWidthSlider;
        QComboBox *projectionTypeComboBox;
        QComboBox *vertexTypeComboBox;
        QComboBox *edgesTypeComboBox;
        QPushButton *screenshotButton;
        QLabel *fnameLabel;
        QLabel *amountVnumberLabel;
        QLabel *amountEnumberLabel;

        QPushButton *gifButton;
        QGifImage *gifImage;
        QTimer *timer;

        const int fps = 10;
        const int duration = 5;
        const int totalFrames = fps * duration;
        int currentFrame = 0;
        QList<QImage> capturedFrames;

        int curr_moveX = 0;
        int curr_moveY = 0;
        int curr_moveZ = 0;
        int curr_rotateX = 0;
        int curr_rotateY = 0;
        int curr_rotateZ = 0;
        int curr_scale = 0;
    };
}

#endif  // MAIN_WINDOW_H
