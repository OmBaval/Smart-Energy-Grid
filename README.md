
# Smart Energy Grid

[![MIT License](https://img.shields.io/badge/license-MIT-green)](LICENSE)

### A smart energy management and electricity theft detection system using Machine Learning and Big Data.

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [System Design](#system-design)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Contributors](#contributors)
- [License](#license)

---

## Introduction

This Smart Energy Grid project addresses energy distribution and theft detection challenges using data from the **Gorwa Sub Division, MGVCL**. The project employs **Machine Learning** for detecting anomalies in energy consumption and leverages **Big Data** analytics for real-time monitoring.

The system helps optimize energy distribution, improve grid reliability, and reduce losses by analyzing historical and real-time data.

![Smart Meter Setup](https://github.com/OmBaval/Smart-Energy-Grid/blob/main/images/smart_meter_setup.jpg)

## Features

- **Real-Time Monitoring**: Collects and analyzes live data from smart meters and sensors.
- **Anomaly Detection**: Identifies electricity theft and irregular consumption using Machine Learning.
- **Predictive Analytics**: Forecasts energy demand and optimizes distribution.
- **Visualization Dashboards**: Real-time energy insights using PowerBI.

![PowerBI Dashboard](https://github.com/OmBaval/Smart-Energy-Grid/images/dashboard.png)

## System Design

The system consists of several interconnected components:

1. **Data Acquisition**: Collects data from smart meters and sensors in real-time.
2. **Data Processing**: Processes data using Machine Learning models for real-time analysis.
3. **Visualization**: Displays results on a PowerBI dashboard for utility providers.

### System Architecture

The architecture is modular and scalable, enabling easy integration with smart meters and sensors. It uses **NodeMCU ESP32** for data collection and transmission.

![System Architecture](https://github.com/OmBaval/Smart-Energy-Grid/images/system_architecture.png)

### Hardware Components

- **NodeMCU ESP32**: Handles wireless communication and data processing.
- **ZMTP101B AC Voltage Sensor**: Measures voltage in real-time.
- **ACS712 Current Sensor**: Measures current flow and monitors power consumption.

![NodeMCU ESP32](https://github.com/OmBaval/Smart-Energy-Grid/images/nodemcu_esp32.png)

## Technologies Used

- **Machine Learning**: Isolation Forest for anomaly detection.
- **Data Processing**: Python (pandas, scikit-learn) for data analysis.
- **Visualization**: PowerBI for dashboards and real-time monitoring.

## Project Structure

```plaintext
Smart-Energy-Grid/
│
├── data/               # Data files and logs
├── models/             # Trained machine learning models
├── scripts/            # Python scripts for data processing and ML
├── images/             # Images used in README and documentation
├── dashboards/         # PowerBI dashboard files
├── README.md           # This file
└── LICENSE             # License file
```

## Setup and Installation

### Prerequisites

- **Python 3.x**
- **NodeMCU ESP32**
- **PowerBI Desktop** for dashboard visualization

### Installation Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/OmBaval/Smart-Energy-Grid.git
   cd Smart-Energy-Grid
   ```

2. Install the required Python libraries by running the following command:
   ```bash
   pip install -r requirements.txt
   ```

3. Connect the NodeMCU ESP32 to your system and configure it for data collection. Ensure that the voltage and current sensors (ZMTP101B and ACS712) are properly connected to the NodeMCU.

4. Upload real-time data from the NodeMCU ESP32 to your local machine. The data will be stored in the `data/` folder for analysis.

5. Open the PowerBI dashboard by launching the `.pbix` file located in the `dashboards/` directory:
   - You will be able to visualize real-time energy consumption, anomaly detection results, and other relevant metrics in the PowerBI dashboard.

## Usage

1. **Start Data Collection**:
   - Upload real-time data from the NodeMCU ESP32 to your local storage.

2. **Run Machine Learning Model**:
   ```bash
   python scripts/detect_anomalies.py
   ```

3. **View Dashboard**:
   Open the PowerBI dashboard to visualize real-time data and anomaly reports.

## Contributors

- **Honey Patel**
- **Yash Rank**
- **Surani Smit**
- **Aviral**

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
