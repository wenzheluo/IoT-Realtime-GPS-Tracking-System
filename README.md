# IoT： Realtime GPS Tracking System

This project revolves around GPS positioning. The purpose is to observe the user's positioning status, and to detect changes in speed and position in real time, so that users can have a security guarantee in specific occasions or in specific environments. This experiment should be divided into 3 major sections, GPS connection, real-time upload of GPS data to SD-card, and real-time upload of GPS data to Google Firebase under the condition of network.

**Key words: Arduino Nano 33 IoT, GPS BN-220, SD Card Reader Adapter, Google Firebase**

# Introduction

With the technology developing, GPS has been deeply integrated into our life, whether it is driving or checking tourist attractions. There are many GPS modules, in this experiment, we choose the BN-220 module. Through the combination of GPS BN-220 module and Arduino nano 33 IoT, we can also interact with GPS data. The ultimate purpose of our experiment is to collect the user's location in real time, and the data can be sent to Google firebase when there is a network (and a backup of the data to the SD card). However, when the network is missing or the network signal is weak, we can also record the data in the SD card. We use the concept of IoT with Google firebase to observe Realtime data collected by positioning GPS in time. As an integrated hardware and software system, it improves system accuracy and reduces overall power consumption. This article is divided into four parts, including the design concept, hardware selection, research results, and difficulties in the experiments. 

# Overview of Arduino Nano 33 IoT

The Arduino Nano 33 IoT is the easiest and cheapest entry point to enhance existing devices to become part of IoT and design piconet applications. This section will summarize the two major features of Arduino: Wi-Fi module and main processor.

<div align=center>
<img src="https://cdn.shopify.com/s/files/1/0506/1689/3647/products/ABX00027_03.front_643x483.jpg?v=1626445295"  width="300px" /> 
  </div>
  
The board's main processor is a 32-bit SAMD21. It runs at a maximum frequency of 48MHz and achieves 2.46 CoreMark®/MHz. They are designed for easy and intuitive migration, with the same peripheral modules. Therefore, during the initial stage of the whole experiment, we installed Arduino SAMD Core by using Boards Manager on the Arduino professional software according to the specification and number of the NANO33's processor. Figure 2 shows Boards Manger which includes NANO 33 installation.

