import socket
from _thread import *
import json

import turtle

HOST = '127.0.0.1'
PORT = 5050

global count, num, recv_data
count = 0
num = 0

client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

def recv_data(client_socket) :
    global count, num, recv_data
    while True :
        data = client_socket.recv(1024)
        recv_data = json.loads(data)
        print("recive : ",repr(data.decode()))
        count += 1

start_new_thread(recv_data, (client_socket,))
print ('>> Connect Server')

with open("color.json", 'r') as f:
    color_data = json.load(f)

turtle.hideturtle()
turtle.speed(10)

while True:
    if(count > num):
        num = count
        for gameObject in recv_data:
            turtle.penup()
            turtle.goto(gameObject['pos'][0], gameObject['pos'][1])
            turtle.pendown()
            turtle.dot(5, color_data[gameObject['name']]['color'])
            turtle.end_fill()


client_socket.close()