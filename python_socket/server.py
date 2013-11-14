import socket
import time

if __name__ == '__main__':
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.bind(('', 8008))
    sockfd.listen(1)

    while True:
        conn, addr = sockfd.accept()
        print 'Connection: ' + str(addr)
        ti = time.strftime('%Y-%m-%d %H:%M', time.localtime(time.time()))
        conn.send(ti)
        conn.close()
