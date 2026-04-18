# Smart Glove for Sign Language Recognition

## Overview
This project presents a smart glove system designed to recognize sign language gestures using a combination of flex sensors and a motion sensor. The glove captures finger movements and hand orientation, processes the data, and converts recognized gestures into text output. It aims to provide a low-cost, portable, and real-time communication solution for bridging the gap between speech-impaired and hearing individuals.

## Features
- Real-time sign language gesture recognition  
- Wireless data transmission via Bluetooth  
- Lightweight and portable design  
- Cost-effective implementation  
- Expandable and modular architecture  

## Hardware Components
- **Microcontroller** (e.g., Arduino)
- **4 Flex Sensors** – to measure finger bending
- **MPU6050** – accelerometer and gyroscope for motion tracking
- **HC-05 Bluetooth Module** – for wireless communication
- Power supply (battery)

## System Description
The glove uses four flex sensors to detect finger bending and an MPU6050 sensor to capture hand orientation and movement. The microcontroller reads:

- **Analog inputs** from the flex sensors  
- **Digital data** from the MPU6050 via I2C communication  

Each gesture is defined by a unique combination of finger positions and hand orientation. These inputs are processed and matched with predefined gesture patterns in the software.

Once a gesture is recognized, the corresponding text output is generated and transmitted wirelessly using the HC-05 Bluetooth module. The output can be displayed on a connected smartphone or computer, enabling seamless interaction.

## Working Principle
1. Flex sensors detect finger bending.
2. MPU6050 captures hand motion and orientation.
3. Microcontroller processes sensor data.
4. Gesture patterns are matched with predefined mappings.
5. Recognized gestures are converted into text.
6. Text is transmitted via Bluetooth to an external device.

## Applications
- Assistive communication for speech-impaired individuals  
- Educational projects and demonstrations  
- Human-computer interaction research  
- Wearable technology development  

## Future Enhancements
- Integration of additional sensors for complex gestures  
- Implementation of machine learning for adaptive gesture recognition  
- Support for user-specific gesture training  
- Voice output integration for multimodal communication  
- Mobile app interface for enhanced usability  

## Advantages
- Low-cost solution  
- Real-time performance  
- Portable and user-friendly  
- Expandable design  

## Conclusion
This smart glove system demonstrates an effective approach to translating sign language into text using sensor-based input and wireless communication. Its modular and open-source nature makes it suitable for further development in assistive technology, education, and innovation projects.

---
