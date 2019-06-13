import socket
import json

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ("127.0.0.1",4422)
sock.connect(server_address)


data_dict = {"username":"asnjksadhk","password":"123456", "email" : "a@gmail.com"}
data_str = json.dumps(data_dict)
number = str(len(data_str))
msg = "101" + number.zfill(4) + data_str
sock.sendall(msg.encode())
server_msg = sock.recv(10000)
print(server_msg.decode())

data_dict = {"room_name":"hi","max_players": 3, "question_count" : 2, "time_per_question" : 10, "type": 2}
data_str = json.dumps(data_dict)
number = str(len(data_str))
msg = "103" + number.zfill(4) + data_str
sock.sendall(msg.encode())
server_msg = sock.recv(10000)
print(server_msg.decode())

data_dict = {"room_id" : 0}
data_str = json.dumps(data_dict)
number = str(len(data_str))
msg = "104" + number.zfill(4) + data_str
sock.sendall(msg.encode())
server_msg = sock.recv(10000)
print(server_msg.decode())

data_dict = {"room_id" : 0}
data_str = json.dumps(data_dict)
number = str(len(data_str))
msg = "106" + number.zfill(4) + data_str
sock.sendall(msg.encode())
server_msg = sock.recv(10000)
print(server_msg.decode())

msg = "105" + "0".zfill(4)
sock.sendall(msg.encode())
server_msg = sock.recv(10000)
print(server_msg.decode())

sock.close()

