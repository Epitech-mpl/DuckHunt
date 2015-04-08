#!/usr/bin/python3
from http.server import SimpleHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
import os
import cgi
import socket
import threading
import select
import time

servedItem = ["/index.html", "/", "/jquery-1.11.2.min.js", "/jquery-migrate-1.2.1.min.js"]
currentConnections = {}
socketMutex = threading.Lock()
continueServer = True

class HttpHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        for ext in servedItem:
            if self.path.lower() == ext.lower():
                return super(self.__class__, self).do_GET()
        parsed = urlparse(self.path)
        print(parsed)
        return self.send_error(404)

    def do_POST(self):
        print("POST")
        if self.path == "/on_click":
            form = cgi.FieldStorage(
                fp=self.rfile, 
                headers=self.headers,
                environ={'REQUEST_METHOD':'POST',
                         'CONTENT_TYPE':self.headers['Content-Type'],
                     })
            errorValue = ""
            try:
                errorValue = "Missing parameter"
                if not ("ip" in form and "port" in form and "x" in form
                        and "y" in form):
                    raise Exception('Bad Request')
                ip = form["ip"]
                port = form["port"]
                x = form["x"]
                y = form["y"]
                errorValue = "Bad Form format"
                if ip.filename or port.filename or x.filename or y.filename:
                    raise Exception('Bad Request')
                ip = ip.value
                port = int(port.value)
                x = float(x.value)
                y = float(y.value)
                socket.inet_aton(ip)
                if (port <= 0 or port > 65535 or x < 0 or
                    x > 1 or y < 0 or y > 1):
                    raise Exception('Bad Request')
                errorValue = "Bad Value Type"
                sock = None
                ipConnections = None
                print("Start Lock")
                socketMutex.acquire()
                print("Unlocked")
                if ip in currentConnections:
                    ipConnections = currentConnections[ip]
                    if port in ipConnections:
                        sock = ipConnections[port]
                if sock == None:
                    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    errorValue = "Can't connect to " + ip + ":" + str(port)
                    sock.connect((ip, port))
                    if ipConnections == None:
                        ipConnections = {port: sock}
                    else:
                        ipConnections[port] = sock
                    currentConnections[ip] = ipConnections
                try:
                    sock.sendall(bytes(str(x) + " " +
                                              str(y) + "\n", "UTF-8"))
                except:
                    pass
                currentConnections[ip][port] = sock
                print(currentConnections)
            except Exception as e:
                print(e)
                self.send_response(400, errorValue)
                self.end_headers()
                return                
            self.send_response(201)
            self.end_headers()
            socketMutex.release()
        else:
            self.send_error(404)

def socketFunction():
    while continueServer:
        socketMutex.acquire()
        inputs = []
        ref = []
        for ip in currentConnections.keys():
            ipConnections = currentConnections[ip]
            for port in ipConnections.keys():
                sock = ipConnections[port]
                if sock is not None:
                    inputs.append(sock)
                    ref.append((ip, port))
        try:
            readable, writeable, exceptional = select.select(inputs, [],
                                                             inputs, 0.1)
        except:
            print(inputs)
        i = 0
        for sock in readable:
            data = sock.recv(1024)
            if not data:
                sock.close()
                ip, port = ref[i]
                currentConnections[ip][port] = None
            ++i
        socketMutex.release()
        time.sleep(0.1)

try:
    server = HTTPServer(('', 8080), HttpHandler)
    info = server.socket.getsockname()
    print("Serving on http://", info[0], ":", info[1], sep='')
    socketThread = threading.Thread(None, socketFunction)
    socketThread.start()
    server.serve_forever()

except KeyboardInterrupt:
    socketMutex.acquire()    
    continueServer = False
    socketMutex.release()
    server.socket.close()
