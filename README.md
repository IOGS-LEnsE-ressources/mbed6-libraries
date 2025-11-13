# Libraries for MBED-OS 6

This repository contains different **libraries** and project examples for **Nucleo boards** (based on *MBED-OS 6.13* or higher).
  
---


## Repository structure overview

You will find different directories in this repository.

- **libs** : contains libraries for mbed-os 6 projects (grouped by functionality : communication, display...)
- **keil_projects** : contains **Keil uVision projects** (based on mbed-os 6.17)
  - for specific Nucleo boards
  - for LEnsE platforms
- **smt32_projects** : contains **STM32 projects** based on HAL   

---

## Requirements

- **Mbed OS:** 6.13 or higher  
- **Hardware:** Nucleo boards (G431KB, L432KC, L476RG...)  

---

## Download

You can download the entire repository (or clone it) on your hard disk.

You can also get a specific library from the different directories by downloading the archived file of the library (zip file).

---

## How to use

Copy the directory of the library (ex. MyLib) in the *Keil µVision* project directory.

For example :

Project/
├─ Core/
├─ Drivers/
├─ MyLib/
└─ ...

In *Keil µVision* : Project → Add Existing Files to Group 'User' (for example).

Select all the .c files. Click on Add, then Close.

In : Project → Options for Target → C/C++ (tab)

In Include Paths, add the path to the directory containing .h files. 

.\MyLib\


