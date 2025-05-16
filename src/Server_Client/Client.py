# Client.py
import socket
import sys
if len(sys.argv) != 3:
    print("Usage: python3 Client.py <host IP> <port>")
    sys.exit(1)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = sys.argv[1]
port = int(sys.argv[2])
s.connect((host, port))
msg = input()
while True:
    s.send(bytes(msg, 'utf-8'))
    data = s.recv(4096)
    print(data.decode('utf-8'))
    msg = input()
s.close