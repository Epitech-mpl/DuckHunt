# DuckHunt

## Description
Base code and remote server for the Duck Hunt Epitech project

## Hierarchy

- The "Project" directory contains the base code (sources and includes) for the Duck Hunt project (game loop, and remote control). You need Python3

- The "Server" directory contains a python web server that handles the connection between a remote webpage (on your phone...) and the Duck Hunt application.

- 'Subject.pdf' is the project subject.

## How to use?

### Local use
- Launch the python web server on your computer. Output : http://0.0.0.0:[WEB_PORT].
- Compile (with 'make') and execute the binary on your computer. Output : [APP_PORT].
- Go to the webpage on your smartphone connected to the same wifi http://[COMPUTER_IP]:[WEB_PORT] and enter 127.0.0.1 for the ip address and the [APP_PORT] for the port.
- When you click on the webpage inside the rectangle, the coordinates should be writen on the standard output of the Duck Hunt application.

### Global use
- Launch the python web server on your computer for example (let say 'Device A'). It should output an URL (ex: http://0.0.0.0:8080).
- Compile (with 'make') and execute the binary on your computer (let say 'Device B' which can be the Device A too). It should output the port the application is listenning to (default: 4242).
- Go to the webpage (URL : http://[Device A ip]:[Web Server Port] the port is by default 8080) with one of your devices (smartphone) which must be connected to the same network Device A and B are connected to. Enter the ip address of the Device B and the port (by default 4242).
- When you click on the webpage inside the rectangle, the coordinates should be writen on the standard output of the Duck Hunt application.
