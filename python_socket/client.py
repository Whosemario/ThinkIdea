import sys
import socket

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(-1)

    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.connect((sys.argv[1], 8008))
    ti = sockfd.recv(1024)
    print ti
    sockfd.close()
