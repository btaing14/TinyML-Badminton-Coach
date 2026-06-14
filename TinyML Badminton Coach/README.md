# TinyML Badminton Coach

This project classifies badminton swing quality using IMU data collected from the Arduino Nano 33 BLE Sense Rev2. The system uses accelerometer and gyroscope measurements to classify a motion as one of three categories:

- `good_smash`
- `weak_smash`
- `non_smash`

The final model was developed using Edge Impulse and deployed as an INT8-quantized TinyML model running directly on the Arduino Nano 33 BLE Sense Rev2.

---

## Hardware

- Arduino Nano 33 BLE Sense Rev2
- Onboard BMI270 accelerometer
- Onboard BMI270 gyroscope

---

## Dataset

### Dataset Statistics

- 60 total IMU samples
- 47 training samples
- 13 testing samples
- 1000 ms window length
- 100 Hz sampling rate
- 6 IMU channels

### Input Features

- aX
- aY
- aZ
- gX
- gY
- gZ

### Output Classes

- good_smash
- weak_smash
- non_smash

---

## Data Collection

Raw IMU data was collected using:

```text
imu_data_collection.ino
```

The sketch runs on the Arduino Nano 33 BLE Sense Rev2 and continuously monitors accelerometer and gyroscope measurements. When motion exceeds a predefined threshold, the sketch records a fixed-length IMU window and outputs the data through the Serial Monitor in CSV format.

### Data Collection Features

- Motion-triggered recording
- 100 samples per swing window
- 100 Hz sampling rate
- Accelerometer and gyroscope measurements
- CSV export through Serial Monitor

Example output:

```csv
aX,aY,aZ,gX,gY,gZ
-0.0327,-0.1763,3.9999,-199.7681,344.8486,194.7632
...
```

---

## Dataset Formatting for Edge Impulse

The original dataset was converted into an Edge Impulse-compatible format using:

```text
change_format.py
```

This script:

- Processes all CSV files in the dataset
- Adds a timestamp column required for Edge Impulse time-series import
- Preserves the class folder structure
- Generates a new dataset for Edge Impulse training

Example conversion:

Before:

```csv
aX,aY,aZ,gX,gY,gZ
...
```

After:

```csv
timestamp,aX,aY,aZ,gX,gY,gZ
0,...
10,...
20,...
...
990,...
```

Output directory:

```text
dataset_edgeimpulse/
```

---

## Model Development

Edge Impulse was used for:

- Feature extraction
- Neural network training
- Model evaluation
- INT8 quantization
- Arduino deployment

### Baseline Model

Pipeline:

```text
IMU Data
→ Spectral Analysis
→ Neural Network Classifier
```

Training configuration:

- Window size: 1000 ms
- Sampling rate: 100 Hz
- Training cycles: 100
- Learning rate: 0.005

---

## Advanced Components

### 1. Multiple Model Pipelines

Two model pipelines were evaluated.

#### Spectral Analysis + Classifier

- Accuracy: 90.0%
- Weighted F1: 0.90
- RAM: 1.4 KB
- Flash: 15.8 KB

#### Raw Data + Classifier

- Accuracy: 80.0%
- Weighted F1: 0.80
- RAM: 2.0 KB
- Flash: 26.0 KB

The spectral-feature model achieved higher accuracy while using fewer resources and was selected for deployment.

### 2. INT8 Quantization

The selected spectral model was converted into an INT8 TensorFlow Lite model.

| Metric | Float32 | INT8 |
|----------|----------|----------|
| Accuracy | 92.31% | 92.31% |
| Classifier RAM | 1.6 KB | 1.4 KB |
| Flash | 17.7 KB | 15.8 KB |
| Latency | 35 ms | 35 ms |

The INT8 model maintained identical accuracy while reducing memory usage.

---

## Results

### Final Quantized Spectral Classifier

- Test Accuracy: 92.31%
- Weighted Precision: 0.94
- Weighted Recall: 0.92
- Weighted F1 Score: 0.92
- Total RAM: 3.2 KB
- Flash Usage: 15.8 KB
- Total Latency: 35 ms

The final model correctly classified all `good_smash` and `non_smash` test samples. One `weak_smash` sample was misclassified as `non_smash`, resulting in a test accuracy of 92.31%.

---

## Deployment

The final model was exported from Edge Impulse as an Arduino library and deployed on the Nano 33 BLE Sense Rev2.

Deployment pipeline:

```text
IMU Data
→ Spectral Feature Extraction
→ INT8 Neural Network
→ Prediction
→ Serial Monitor Output
```

Inference runs entirely on-device without requiring cloud connectivity.

---

## Repository Structure

```text
TinyML Badminton Coach/
├── README.md
├── imu_data_collection.ino
├── change_format.py
├── dataset/
├── dataset_edgeimpulse/
└── deployment/
```

---

## How to Run

### 1. Collect Data

1. Open `imu_data_collection.ino`
2. Upload to Arduino Nano 33 BLE Sense Rev2
3. Open Serial Monitor
4. Perform badminton swings
5. Save the generated CSV files

### 2. Format Dataset

Run:

```bash
python3 change_format.py
```

This generates the Edge Impulse-compatible dataset in:

```text
dataset_edgeimpulse/
```

### 3. Train in Edge Impulse

1. Upload the formatted dataset
2. Configure:
   - Spectral Analysis
   - Classification
3. Train the model
4. Evaluate performance
5. Export the Arduino library

### 4. Deploy Model

1. Open the deployment Arduino sketch
2. Install the exported Edge Impulse library
3. Select Arduino Nano 33 BLE Sense Rev2
4. Upload the sketch
5. Open Serial Monitor

Example output:

```text
good_smash: 0.92
weak_smash: 0.05
non_smash: 0.03

Prediction: good_smash
```

---

## Authors

University of Washington – EE446 TinyML

TinyML Badminton Coach Team
