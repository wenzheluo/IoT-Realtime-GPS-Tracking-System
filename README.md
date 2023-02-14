# IoT： Realtime GPS Tracking System


<br>
<br>
<p align="center"> George Mason University </p>
<p align="center"> Wenzhe Luo </p>
<p align="center"> Chen Chen </p>
<p align="center"> ECE-508 <b>Internet of Things</b> </p>
<p align="center"> Spring 2022 </p>

<br>

## 

This project revolves around GPS positioning. The purpose is to observe the user's positioning status, and to detect changes in speed and position in real time, so that users can have a security guarantee in specific occasions or in specific environments. This experiment should be divided into 3 major sections, GPS connection, real-time upload of GPS data to SD-card, and real-time upload of GPS data to Google Firebase under the condition of network.

**Key words: Arduino Nano 33 IoT, GPS BN-220, SD Card Reader Adapter, Google Firebase**

# Introduction

With the technology developing, GPS has been deeply integrated into our life, whether it is driving or checking tourist attractions. There are many GPS modules, in this experiment, we choose the BN-220 module. Through the combination of GPS BN-220 module and Arduino nano 33 IoT, we can also interact with GPS data. The ultimate purpose of our experiment is to collect the user's location in real time, and the data can be sent to Google firebase when there is a network (and a backup of the data to the SD card). However, when the network is missing or the network signal is weak, we can also record the data in the SD card. We use the concept of IoT with Google firebase to observe Realtime data collected by positioning GPS in time. As an integrated hardware and software system, it improves system accuracy and reduces overall power consumption. This article is divided into four parts, including the design concept, hardware selection, research results, and difficulties in the experiments. 

------------------------------

Table of Contents

------------------------------

- [Overview of Arduino Nano 33 IoT](#Overview-of-Arduino-Nano-33-IoT)
- [Design and Configuration](#Design-and-Configuration)

    - [Proposed system & Design Ideas](#Proposed-system-&-Design-Ideas)
    - [Hardware selection](#Hardware-selection)
 
- [Introduction to wiring diagram and test process](#Introduction-to-wiring-diagram-and-test-process)
- [Experimental results](#Experimental-results)


# Overview of Arduino Nano 33 IoT

The Arduino Nano 33 IoT is the easiest and cheapest entry point to enhance existing devices to become part of IoT and design piconet applications. This section will summarize the two major features of Arduino: Wi-Fi module and main processor.

<div align=center>
<img src="https://cdn.shopify.com/s/files/1/0506/1689/3647/products/ABX00027_03.front_643x483.jpg?v=1626445295"  width="350px" /> 
  </div>

<p align="center">Figure 1 Arduino Nano 33 IoT</p>
  
The board's main processor is a 32-bit SAMD21. It runs at a maximum frequency of 48MHz and achieves 2.46 CoreMark®/MHz. They are designed for easy and intuitive migration, with the same peripheral modules. Therefore, during the initial stage of the whole experiment, we installed Arduino SAMD Core by using Boards Manager on the Arduino professional software according to the specification and number of the NANO33's processor. Figure 2 shows Boards Manger which includes NANO 33 installation.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Installation%20of%20SAMD%20Board.png"  width="550px" /> 
  </div>
  
<p align="center">Figure 2 Installation of SAMD Board</P>


The Wi-Fi and Bluetooth connections of Arduino Nano 33 IoT are performed by u-blox's module NINA-W10, a low-power chipset operating in the 2.4GHz range. For this reason, the Arduino is particularly easy to connect to a Wi-Fi network. Designer can connect the development board to any type of existing Wi-Fi network or use it to create your own Arduino access point. During the experiment, we tried to use an iPhone create a mobile hotspot, and the experimental results showed that the Arduino WIFI module is also possible to connect to the iPhone hotspot. In this experiment, in order to enable network connection (Local and Internet), we first need a certain library package to assist, this is WIFININA. By using this library, designers can instantiate servers, clients and send/receive UDP packets over Wi-Fi. The board can be connected to open or encrypted networks (WEP, WPA). IP addresses can be assigned statically or via DHCP. Figure 3 shows the installation of WIFININA at Library Manager.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Installation%20of%20WIFI%20NINA%20library.png" width="550px" />
</div>

<p align="center">Figure 3 Installation of WIFI NINA library</p>

# Design and Configuration

## Proposed system & Design Ideas

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Proposed%20System.png" width="350px" />
</div>
<p align="center">Figure 4 Proposed System</p>

We have learned how to display hardware data on OLED (such as reading temperature/humidity or time countdown by coding setting, etc.), but facing the data generated by GPS, the goal of the experiment is to be able to adjust the user's latitude and longitude coordinates, as well as the coordinates of their movement frequency, as a data gathering object. Following this logical purpose, our group's initial aim is to try to create a program that can read GPS and save information to an SD card in txt format. After selecting the appropriate card reader module, we began to consider trying to interact with the google firebase platform, in order to be able to log in to firebase through computers and mobile phones to observe the real-time status of users. Therefore, the design concept is when there is a network, SD card records the real-time positioning status every second (at the same time uploading GPS data to Google Firebase, so that observers can observe the changes of real-time data through the website and analyze the user status); when there is no network, the data is simply recorded in the SD card.

## Hardware selection

### [1] GPS BN-220
In the choice of GPS module, we use Beitian's BN-220. The BN-220 GPS module has a TTL dual GPS Glonass navigation system, as well as a flash + GPS passive antenna. At the same time, the BN220 GPS module offers a significant advantage: it features a flash memory that saves the setup, eliminating the need to re-enter the data. 

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Hardware%20of%20BN-220%20(Pin%20Description).png" width=350px" />
</div>
<p align="center">Figure 5 Hardware of BN-220 (Pin Description)</p>

### [2] Pin distribution on the back of OLED
Regarding the choice of OLED module, we chose the 0.96" OLED display module produced by UCTRONICS, its advantage is that the screen size meets our experimental requirements, and it is suitable for Arduino, its specifications are: 12864 128x64 pixels SSD1306 I2C serial mini screen, it contains yellow and blue.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Pin%20distribution%20on%20the%20back%20of%20OLED.png" width=350px" />
</div>
<p align="center">Figure 6 Pin distribution on the back of OLED</p>

### [3] Micro-SD Reader Adapter Slot Socket Module
In order to successfully read the SD card, we used the Micro-SD/TF Memory Card Reader Adapter Slot Socket Module produced by pzsmocn. The module has a self-eject TF (Micro SD) card slot. The specification is a 2.54mm pitch 9Pin single-row header, which supports SDIO and SPI interfaces. At the same time, the DC 3.3V working voltage, the working current is about 10mA. Because the data format is txt format (will not take up a lot of memory), the SD card used in our experiment is 32G storage size.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Micro-SD%20Memory%20Card%20Reader.png" width="350px" />
</div>
<p align="center">Figure 7 Micro-SD/TF Memory Card Reader Adapter Slot Socket Module</p>


# Introduction to wiring diagram and test process
The procedural steps of this lab consist of the following four tasks:

**Hardware:** 
1) Arduino Nano 33 IoT;
2) GPS BN-220;
3) OLED Display;
4) Micro-SD reader Adapter Slot Socket;
5) 32G SD card.

**Software: Arduino**

**Platform: Google Firebase**

**PC system: Windows 10/11**

1) Analyze the matching status of hardware and software platforms, check whether all relevant libraries have been installed, and check the correctness of the code.
2) Make sure each piece of hardware is wired correctly to the Arduino nano 33 pins. The Figure 8 shows the fritzing of wiring diagram.
3) Upload the code to the correctly wired Arduino nano 33 and observe the light status of each module (such as the orange light of Arduino and the red light of BN-220).
4) Observe the transmission changes of data in real time (observe SD card and GOOGLE firebase) and get the result report.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Fritzing%20of%20the%20whole%20experiment.png" width="350px" />
</div>
<p align="center">Figure 8 Fritzing of the whole experiment</p>

**The following flowchart is a complete step and idea of our experiment:**

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Experiment%20Details%20Steps.png" width="300px" />
</div>
<p align="center">Figure 9 Experiment Details Steps</p>

We've learnt through experience that it's important to first check whether the GPS is receiving a signal. Our GPS modules are unable to receive GPS signals in many circumstances since the school library and many apartments can’t let us receive the GPS signals. Therefore, the first step in our group's experiments was to evaluate the order in which the modules were used: first, identify whether the GPS can receive signals, then link the OLED to the required code to check whether the GPS data is shown correctly, and last, connect the inserted SD card. The card reader module accesses the SD card with the card reading code to assess if there is an error based on the first two sections being satisfied; finally, by adding and modifying the code to realize the operation of data uploading to Google Firebase. Figure 10 shows the physical wiring diagram for our project.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Physical%20wiring%20diagram.jpg" width="350px" />
</div>
<p align="center">Figure 10 Physical wiring diagram</p>

# Experimental results

Through experiments, we learned that GPS BN-220 can only collect signals in a feasible environment. We've tested a lot of places, including spacious single-family homes, plazas and car parks. We found these locations to be able to collect GPS signals through the BN-220 module. So, we try to connect to a GPS signal before trying to get into a school library or an apartment building. During the first few minutes, the GPS continued to update the signal. After a certain point in time, the GPS positioning lost the connection (the red light was off), and both the OLED and the txt document changed the latitude and longitude data to 0.0000 after a certain point. However, all the previous data are saved. We have tested driving and walking to judge the speed change, and the results are correct. The Figure 11 shows the OLED display state (highlighted by yellow rectangle) in the normal state of the experiment (including latitude and longitude, speed, altitude, etc.)
After connecting the SD card and linking Micro-SD reader Adapter Slot Socket, then running the code, the Arduino Nano 33 uploads all the data to the SD card in the form of txt. As shown in Figure 12, a string of txt text will be generated every second. The picture shows the test of moving the BN-220 to change the speed while standing still. We must pay attention to whether the speed unit is adjusted correctly in the code. The speed unit is also a very important part in our experiment.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/the%20OLED%20display%20state%20of%20the%20result.jpg" width="300px">
</div>
<p align="center">Figure 11 the OLED display state of the result</p>

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/All%20GPS%20data%20sending%20to%20SD%20card%20(txt%20form).png" width="880px">
</div>
<p align="center">Figure 12 All GPS data sending to SD card (txt form)</p>

It has been proved by practice that there is no problem in importing our GPS data, the code is correct, the GPS module is in good condition, and the wiring of the Arduino Nano 33 has no problems.

The last step, we try to connect to Google Firebase and observe the data changes. We are running a Realtime database service provided by Firebase. Before uploading to google firebase, we need to add the reference URL and the Database Secrets in the project settings to the code with installing the libraries Firebase_Arduino_WiFiNINA and Arduino_JSON. The Figure 13 shows the real-time data status of browsing firebase web pages with a computer. One real-time data is uploaded every second. We can see through the pictures that the specific information of the subdirectories is clearly displayed. At the same time, we also tried to log in to firebase with a mobile phone to observe the data changes. 

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Realtime%20Database%20status.png" width="880px">
</div>
<p align="center">Figure 13 Realtime Database status</p>

Similarly, we can see that the real-time data is clearly displayed on the mobile phone web page through Figure 14. This gives us a lot of convenience. We can give this set of positioning devices to minors to protect their personal safety. Once there is a problem with the data or the latitude and longitude address is wrong, we can find the problem in time through the mobile phone. 
The result of our experiment met the expectations, and the next chapter will describe the difficulties and obstacles we encountered during the experiment.

<div align=center>
<img src="https://github.com/manzitlo/IoT-Realtime-GPS-Tracking-System/blob/main/images/Realtime%20Database%20status%20by%20using%20iPhone.png" width="250px">
</div>
<p align="center">Figure 14 Realtime Database status by using iPhone</p>
