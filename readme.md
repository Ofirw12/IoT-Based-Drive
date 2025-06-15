# IoT Based Drive

A drive available to the user from the linux directory gui, data can be written and read from it while the data isn't actually stored on the local pc itself but is seperated on many IoT devices (minions)

## Motivation
This program is made to utilize unused storage space in household IoT devices, such as a smart airconditioner controller, smart wall plug, raspberry pie device etc.
Data will be saved using following RAID01 rules, therefore secured, safe and backed-up.
Also, the data won't be accessible outside the Local Area Network.

## Intro

The IoT Based Drive is a User Space program running on Linux OS,
The drive is being mounted by the user using ``mount`` shell command


Data is being sent over TCP from the kernel space to the user space using a NBD module


This project is the final project I've built during the Infinity Labs R&D Software Development program.


## Prerequisites
In order to use the IoT Drive you must have cmake installed on your machine.

## Instructions

### minion side
to run the minion, the user must specify the wanted port as program args
### master side
before running the master, minions must be up and running,
also code inside TestMaster.cpp has to be updated according to the corresponding minions ip and port

TODO compilation steps with cmake!!!!!!!!!!!!!!!!!!!!!

in order to start the program open up a terminal and write down these lines
```bash
sudo modprobe nbd
echo 4 | sudo tee /sys/block/nbd*/queue/max_sectors_kb
```
in a second terminal run the master executable file

now back in the first terminal write down these lines
```bash
sudo mkfs.ext2 /dev/nbd0
sudo mount /dev/nbd0 ~/iot_drive/mount/
```

now the system is up and listening to any changes you make in your ```~/iot_drive/mount/``` folder

## Main Components

### Framework
Collection of generic components, which both each of them and/or the whole framework package can be reused in all sort of projects
#### Reactor
An Event-Driven component, which is responsible for observing a file descriptor, and start the chain of actions when it is ready to read.
#### ThreadPool
A component which is responsible for the Multi-Threading of the whole system, it contains a pool of threads waiting for new tasks to enter the system, when such enter, the first thread to catch the task will execute it and then go back to the queue until another task will be inserted
#### Factory
A generic component capable of creating new objects on-command, mainly being used in this project for creating r/w commands.
#### Async Injection
An asynchronous object, which is checking for a condition to be met, if met the object will destroy itself, otherwise it would run again after it's time interval ends.
#### Logger
A component in charge of writing to a log file regarding the functionality of the program
#### DirMonitor
A component responsible for watching over a directory containing Dynamically Linked Libraries,
when such library is being added to the watched directory, it activates the DLLLoader
#### DLLLoader
A component in charge of running the newly added dll into the program in runtime using the ``dlopen()`` system call.
#### Handleton
Similar to Singleton, this component role is making sure that each object used by it will exist only once per class, The main difference from Singleton is that Singleton creates the instances in the data segment while Handleton creates them directly on the heap and therefore makes the instances available to both the program's compilation unit and the runtime loaded Dlls.

#### Interfaces

* IInputProxy - defines the ``GetTaskArgs()`` method
* ITaskArgs - defines the ``GetKey()`` method
* ICommand - defines the ``Run()`` method

### Concrete
These component are specific for the needs of this project and are in charge of the functionality of the IoT Based Drive.
#### Minion Manager
A component made to send r/w commands from the master downward to the minion devices, The minion manager is the only component who knows the actual amount of minions and the size and division of the storage space in each minion.
#### Minion Proxy & Master Proxy
Components responsible on communicating between the two programs
#### Ticket
An object which track the status of the command sent to the minions, when the process is done, it forward the command result to the Response Manager
#### Response Manager
A component which gets results of commands and activate corresponding responses
#### NBD
A component which utilizes the linus nbd feature, and passes requests from kernel to user space
#### FileManager
Minion-side component responsible on accessing the actual local storage file, passing r/w commands to it