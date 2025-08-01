### Serial-to-WAV Converter with Visualization

This project is a desktop application built with C++ and the Qt framework that provides a simple and intuitive way to record data from a serial port, convert it into a standard `.wav` audio file, and visualize the waveform in real time.

This tool is useful for anyone working with devices that output audio or sensor data over a serial connection. For example, it can be used to capture audio from an analog-to-digital converter (ADC) or a custom sensor and analyze its waveform.

---

### Features

- **Serial Port Data Capture:** Connect to any available serial port and capture incoming data.
- **Real-Time Visualization:** View a live waveform of the captured data as it is being recorded.
- **WAV File Conversion:** Convert the recorded serial data into a standard 16-bit, mono `.wav` file with a configurable sample rate.
- **Waveform Zoom:** Easily zoom in and out on the visualization to inspect specific sections of the waveform.
- **User-Friendly GUI:** A clear and simple graphical interface makes the process of recording and saving data straightforward.

---

### How to Use

1.  **Connect Your Device:** Plug your serial device into your computer.
2.  **Select Port:** Launch the application and select the correct serial port from the dropdown menu.
3.  **Start Recording:** Click the **"Record"** button to begin capturing data from the serial port. The application will create a temporary file to store the raw data.
4.  **Stop Recording:** Click the **"Stop"** button to end the recording session. The captured data will be processed and the waveform will be displayed in the visualization window.
5.  **Visualize and Inspect:** Use the **"Zoom In"** and **"Zoom Out"** buttons to get a closer look at the details of the waveform.
6.  **Save as WAV:** Click the **"Save"** button to save the captured data as a `.wav` file to a location of your choice.

---

### Getting Started

#### Prerequisites

- **Qt Framework:** This project requires the Qt 5 or 6 framework to be installed. You can download it from the official Qt website.
- **C++ Compiler:** A C++ compiler (like g++ or MSVC) is necessary to build the project.


### Customization

-   **Baud Rate:** The current baud rate is set to 115200. You can easily change this in the `startRecording()` function in `mainwindow.cpp` to match your device's settings.
-   **Sample Rate:** The `.wav` file's sample rate is currently hardcoded to 9010 Hz. You can modify this in the `saveAsWav()` and `processRecordedData()` functions.
-   **Visualization:** The colors and styling of the waveform can be customized by changing the `QPen` properties in the `drawWaveform()` function.

README

1. Input Data Format (Serial Port)

The application makes the following assumptions about the data stream received from the serial port:

    Format: The incoming data is a continuous, raw stream of bytes.

    Sample Size: Each individual audio sample is represented by a 16-bit value.

    Endianness: The data is assumed to be in Little-Endian byte order. This means for each 16-bit sample, the least significant byte is transmitted first, followed by the most significant byte.

The readSerialData() function captures this raw byte stream and saves it to a temporary file (recordedData.bin) without any initial processing.
2. Internal Data Processing

The conversion from raw bytes to meaningful audio samples occurs in the processRecordedData() and saveAsWav() functions.

Key Processing Steps:

    A QFile object opens the recordedData.bin file.

    The entire content is read into a QByteArray.

    A QDataStream is initialized with this QByteArray, and its byte order is explicitly set:

    QDataStream stream(rawData);
    stream.setByteOrder(QDataStream::LittleEndian);

    The stream is iterated, reading two bytes at a time and interpreting them as a single qint16 (signed 16-bit integer).

    A fixed offset is applied to each sample, as shown below. This suggests the input data from the serial device is in a format where the zero point is not at 0, but rather at -32768. The code adds 32768 to shift the values to a 0-65535 range before storing them in the final samples vector. <<<SPECIFIC  HARDWARE DESIGN RELEVENT HERE >>

    qint16 sample;
    stream >> sample;
    samples.append(sample + 32768); 


3. WAV File Output Format

The saveAsWav() function constructs a standard WAV file header and writes the processed data. The header ensures compatibility with most audio players and editors.

WAV Header Specifications:

    Header Type: RIFF (Resource Interchange File Format)

    Format: PCM (uncompressed)

    Channels: Mono (1 channel)

    Sample Rate: 9010 Hz (This is a hardcoded value in the QAudioFormat object).

    Bits Per Sample: 16 bits

    Byte Order: Little-Endian

    Sample Type: Signed integers (QAudioFormat::SignedInt)

The WAV header is manually constructed and then the QVector<qint16> of processed samples is written directly after the header.
