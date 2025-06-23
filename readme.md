# IoT Based Drive

A Linux-based user-space program that provides a virtual drive, accessible via the native directory GUI. Although data appears to be stored locally, it is actually distributed across multiple IoT devices (referred to as *minions*) on the same local network.

---

## 🚀 Motivation

This project is designed to leverage unused storage space on common household IoT devices — such as smart air conditioner controllers, smart plugs, Raspberry Pi devices, and more.

- Data Accessible only within the Local Area Network (LAN)
- Implement RAID 01, therefore the system ensures thata data is:
  - **Secure**
  - **Backed up**
  - 
---

## 📚 Introduction

IoT-Based Drive is a user-space application for Linux systems. It allows users to mount a virtual drive using the standard `mount` shell command.

Data is transmitted via TCP from the kernel space to the user space using the Linux **Network Block Device (NBD)** module.

> 🛠 This project was developed as the final assignment in the Infinity Labs R&D Software Development Program.

---

## ✅ Prerequisites

- Linux OS
- `cmake` installed
- Root access (for loading kernel modules and mounting NBD)

---

## ⚙️ Setup & Usage

### 🛠 Compilation with CMake

To build the project:

```bash
git clone https://github.com/Ofirw12/IoT-Based-Drive.git
cd IoT-Based-Drive
mkdir build
cd build
cmake ..
make
```

> Compiled executables will be in the `build/` directory.

---

### 🔧 Minion Side

Each *minion* device must run its corresponding executable. To launch a minion, pass the desired port as a command-line argument:

```bash
./filezeroer # first usage only, will format the storage file.
./minion <PORT>
```

### 👑 Master Side

1. Ensure all minions are up and running.
2. Edit `TestMaster.cpp` to include the IP and port of each minion device.

---

#### 🔌 Mounting the Drive

1. Load the NBD kernel module:

```bash
sudo modprobe nbd
echo 4 | sudo tee /sys/block/nbd*/queue/max_sectors_kb
```

2. In a **second terminal**, run the master executable:

```bash
sudo ./master
```

3. Back in the **first terminal**, format and mount the virtual drive:

```bash
sudo mkfs.ext2 /dev/nbd0
sudo mount /dev/nbd0 ~/iot_drive/mount/
```

> Your drive is now mounted. Any file operations inside `~/iot_drive/mount/` will be distributed across the minions.

---

## 🧩 Main Components

### 🧱 Framework (Reusable Core Modules)
#### 🔁 Reactor
Monitors file descriptors and triggers events when ready to read.

#### 🧵 ThreadPool
Handles multithreading via a waitable task queue and worker threads.
#### 🏭 Factory
Dynamically generates objects on-command, mainly being used in this project for creating read/write commands.
#### ⏳ Async Injection
Repeatedly checks a condition and self-destructs if met.
#### 📝 Logger
Writes system events and errors to a log file.

#### 📁 DirMonitor
Watches a directory for new Dynamic Linked Libraries (DLLs).

#### 🧬 DLLLoader
Loads DLLs at runtime using `dlopen()`.

#### 🧩 Handleton
A Singleton-like object manager with heap allocation for runtime flexibility.

##### Interfaces

- `IInputProxy` — declares `GetTaskArgs()`
- `ITaskArgs` — declares `GetKey()`
- `ICommand` — declares `Run()`

---

### 🔌 Concrete Components (IoT-Drive-Specific)
#### 📦 Minion Manager
Distributes read/write commands to minions and manages data sharding.

#### 🔁 Minion Proxy & Master Proxy
Facilitate communication between master and minions.

#### 🎫 Ticket
Tracks execution status of commands and routes results.

#### 📬 Response Manager
Handles responses and initiates appropriate follow-up actions.

#### 🔗 NBD
Handles Linux NBD communication between kernel and user space.

#### 📂 FileManager
Handles physical read/write operations on the minion devices.

---
