#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDataStream>
#include <QAudioFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPort(new QSerialPort(this))
{
    ui->setupUi(this);

    // Populate serial ports in the combo box
    listSerialPorts();

    // Connect buttons to their respective slots
    connect(ui->recordButton, &QPushButton::clicked, this, &MainWindow::startRecording);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopRecording);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveAsWav);
    connect(ui->zoomInButton, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->zoomOutButton, &QPushButton::clicked, this, &MainWindow::zoomOut);

    // Disable Stop and Save buttons initially
    ui->stopButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listSerialPorts()
{
    ui->serialPortComboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialPortComboBox->addItem(info.portName());
    }
}

void MainWindow::startRecording()
{
    QString portName = ui->serialPortComboBox->currentText();
    if (portName.isEmpty()) {
        ui->statusLabel->setText("No port selected.");
        return;
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200); // Adjust if needed
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadOnly)) {
        dataFile.setFileName("recordedData.bin");
        if (!dataFile.open(QIODevice::WriteOnly)) {
            ui->statusLabel->setText("Failed to open file for recording.");
            serialPort->close();
            return;
        }

        isRecording = true;
        ui->statusLabel->setText("Recording started...");
        ui->recordButton->setEnabled(false);
        ui->stopButton->setEnabled(true);

        connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    } else {
        ui->statusLabel->setText("Failed to open serial port.");
    }
}

void MainWindow::readSerialData()
{
    if (isRecording && serialPort->bytesAvailable() > 0) {
        QByteArray data = serialPort->readAll();
        dataFile.write(data);
    }
}

void MainWindow::stopRecording()
{
    if (isRecording) {
        isRecording = false;
        serialPort->close();
        dataFile.close();

        ui->statusLabel->setText("Recording stopped.");
        ui->recordButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        ui->saveButton->setEnabled(true);

        QString tempWavFile = "output.wav"; // Temporary WAV file

        if (processRecordedData(tempWavFile)) {
            visualizeWav(tempWavFile);
        } else {
            ui->statusLabel->setText("Failed to process and visualize WAV file.");
        }
    }
}

void MainWindow::saveAsWav()
{
    QString savePath = QFileDialog::getSaveFileName(this, "Save File", "", "WAV Files (*.wav)");
    if (savePath.isEmpty()) return;

    QString dataFile = "recordedData.bin";

    QFile inputFile(dataFile);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        ui->statusLabel->setText("Failed to read recorded data.");
        return;
    }

    QByteArray rawData = inputFile.readAll();
    inputFile.close();

    QVector<qint16> samples;
    QDataStream stream(rawData);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        qint16 sample;
        stream >> sample;
        samples.append(sample + 32768); // Convert to unsigned offset binary
    }

    QFile outputFile(savePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        ui->statusLabel->setText("Failed to save file.");
        return;
    }

    QAudioFormat format;
    format.setSampleRate(9010);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QByteArray header;
    QDataStream headerStream(&header, QIODevice::WriteOnly);
    headerStream.setByteOrder(QDataStream::LittleEndian);

    // Write the WAV file header
    headerStream.writeRawData("RIFF", 4);
    headerStream << quint32(36 + samples.size() * sizeof(qint16)); // File size
    headerStream.writeRawData("WAVE", 4);
    headerStream.writeRawData("fmt ", 4);
    headerStream << quint32(16); // PCM format chunk size
    headerStream << quint16(1);  // Audio format (1 = PCM)
    headerStream << quint16(format.channelCount());
    headerStream << quint32(format.sampleRate());
    headerStream << quint32(format.sampleRate() * format.channelCount() * (format.sampleSize() / 8)); // Byte rate
    headerStream << quint16(format.channelCount() * (format.sampleSize() / 8)); // Block align
    headerStream << quint16(format.sampleSize()); // Bits per sample
    headerStream.writeRawData("data", 4);
    headerStream << quint32(samples.size() * sizeof(qint16)); // Data chunk size

    // Write the header and samples to the output file
    outputFile.write(header);
    outputFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(qint16));
    outputFile.close();

    QFile::remove(dataFile);

    ui->statusLabel->setText("WAV file created successfully.");
}



bool MainWindow::processRecordedData(const QString& wavFilePath)
{
    QString dataFile = "recordedData.bin";

    QFile inputFile(dataFile);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        ui->statusLabel->setText("Failed to read recorded data.");
        return false;
    }

    QByteArray rawData = inputFile.readAll();
    inputFile.close();

    QVector<qint16> samples;
    QDataStream stream(rawData);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        qint16 sample;
        stream >> sample;
        samples.append(sample + 32768); // Convert to unsigned offset binary
    }

    QFile outputFile(wavFilePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        ui->statusLabel->setText("Failed to save file.");
        return false;
    }

    QAudioFormat format;
    format.setSampleRate(9010);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QByteArray header;
    QDataStream headerStream(&header, QIODevice::WriteOnly);
    headerStream.setByteOrder(QDataStream::LittleEndian);

    // Write the WAV file header
    headerStream.writeRawData("RIFF", 4);
    headerStream << quint32(36 + samples.size() * sizeof(qint16)); // File size
    headerStream.writeRawData("WAVE", 4);
    headerStream.writeRawData("fmt ", 4);
    headerStream << quint32(16); // PCM format chunk size
    headerStream << quint16(1);  // Audio format (1 = PCM)
    headerStream << quint16(format.channelCount());
    headerStream << quint32(format.sampleRate());
    headerStream << quint32(format.sampleRate() * format.channelCount() * (format.sampleSize() / 8)); // Byte rate
    headerStream << quint16(format.channelCount() * (format.sampleSize() / 8)); // Block align
    headerStream << quint16(format.sampleSize()); // Bits per sample
    headerStream.writeRawData("data", 4);
    headerStream << quint32(samples.size() * sizeof(qint16)); // Data chunk size

    // Write the header and samples to the output file
    outputFile.write(header);
    outputFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(qint16));
    outputFile.close();

    return true;
}



void MainWindow::visualizeWav(const QString &wavFilePath)
{
    // Open the WAV file for reading
    QFile wavFile(wavFilePath);
    if (!wavFile.open(QIODevice::ReadOnly)) {
        ui->statusLabel->setText("Failed to open WAV file for visualization.");
        return;
    }

    // Read the header and validate it
    QByteArray header = wavFile.read(44); // WAV header size is 44 bytes
    if (header.mid(0, 4) != "RIFF" || header.mid(8, 4) != "WAVE") {
        ui->statusLabel->setText("Invalid WAV file format.");
        wavFile.close();
        return;
    }

    // Read the audio samples
    QByteArray rawData = wavFile.readAll();
    wavFile.close();

    QVector<qint16> samples;
    QDataStream stream(rawData);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd()) {
        qint16 sample;
        stream >> sample;
        samples.append(sample);
    }
    lastSamples=samples;

    // Pass the samples to drawWaveform
    drawWaveform(samples);
}
void MainWindow::drawWaveform(const QVector<qint16> &samples)
{
    // Clear the scene of QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->waveformGraphicsView->setScene(scene);

    if (samples.isEmpty()) {
        ui->statusLabel->setText("No audio samples to display.");
        return;
    }

    int width = ui->waveformGraphicsView->width();
    int height = ui->waveformGraphicsView->height();
    int midHeight = height / 2;

    // Scale the waveform to fit within the view
    int numSamples = samples.size();
    float xScaleAdjusted = static_cast<float>(width) / numSamples * xScale;  // Apply x scale
    float yScaleAdjusted = static_cast<float>(midHeight) / 32768 * yScale;   // Apply y scale

    QPen pen(Qt::blue);
    QPainterPath path;
    path.moveTo(0, midHeight);

    for (int i = 0; i < numSamples; ++i) {
        float x = i * xScaleAdjusted;
        float y = midHeight - (samples[i] * yScaleAdjusted);
        path.lineTo(x, y);
    }

    scene->addPath(path, pen);

    ui->statusLabel->setText("Waveform visualization complete.");
}
void MainWindow::zoomIn()
{
    xScale *= zoomFactor;
    yScale *= zoomFactor;
    updateWaveform();  // Repaint the waveform with new zoom scales
}

void MainWindow::zoomOut()
{
    xScale /= zoomFactor;
    yScale /= zoomFactor;
    updateWaveform();  // Repaint the waveform with new zoom scales
}






void MainWindow::updateWaveform()
{
    // Assuming you have a vector of samples stored
    drawWaveform(lastSamples);
}
