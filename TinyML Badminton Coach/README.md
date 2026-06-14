# TinyML Badminton Coach

This project classifies badminton smash motion using IMU data from the Arduino Nano 33 BLE Sense Rev2. The model predicts good_smash, weak_smash, or non_smash using an INT8 quantized TinyML model deployed through Edge Impulse.

## Hardware
- Arduino Nano 33 BLE Sense Rev2
- Onboard accelerometer and gyroscope

## Dataset
- 60 total IMU samples
- 47 training / 13 testing
- 1000 ms window
- 100 Hz sampling rate
- Inputs: aX, aY, aZ, gX, gY, gZ
- Classes: good_smash, weak_smash, non_smash

## Model
- Spectral Analysis + Neural Network Classifier
- Compared against raw-data classifier
- Final model: INT8 quantized spectral classifier

## Results
- Final test accuracy: 92.31%
- Weighted F1 score: 0.92
- Total RAM: 3.2 KB
- Flash: 15.8 KB
- Total latency: 35 ms

## Deployment
The final model was exported from Edge Impulse as an Arduino library and deployed on the Nano 33 BLE Sense Rev2. Inference results are printed through the Arduino Serial Monitor.

## How to Run
1. Install Arduino IDE.
2. Install the Edge Impulse Arduino library for this project.
3. Open the deployment `.ino` file in the `arduino/` folder.
4. Select Arduino Nano 33 BLE Sense Rev2.
5. Upload the sketch.
6. Open Serial Monitor to view predictions.
