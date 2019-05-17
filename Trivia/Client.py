import socket
import msgpack

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ("127.0.0.1",4422)
sock.connect(server_address)

data_dict = {"username":"asnjksadhk","password":"123456"}
data_str = msgpack.packb(data_dict)
number = str(len(data_str))
msg = "101".encode() + number.zfill(4).encode() + data_str
sock.sendall(msg)
server_msg = sock.recv(10000)
# print(msgpack.unpackb(server_msg))
print(server_msg.decode())
sock.close()

