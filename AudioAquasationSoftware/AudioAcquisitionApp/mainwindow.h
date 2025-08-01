#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QFile dataFile;
    bool isRecording = false;


    void listSerialPorts();
    void startRecording();
    void readSerialData();
    void stopRecording();
    void saveAsWav();



    QVector<qint16> lastSamples; // Stores the last saved WAV samples for visualization

    bool processRecordedData(const QString &wavFilePath);
    void visualizeWav(const QString &wavFilePath);
    void drawWaveform(const QVector<qint16> &samples);
    void zoomIn();
    void zoomOut();
    void updateWaveform();
    float xScale = 1.0f;      // Horizontal zoom scale
    float yScale = 1.0f;      // Vertical zoom scale
    const float zoomFactor = 1.2f;  // Zoom factor (e.g., 1.2 means 20% zoom in/out)



};

#endif // MAINWINDOW_H
