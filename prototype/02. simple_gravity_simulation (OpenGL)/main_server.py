from lib.MGE_Class import GameObject, CheckShape2D, np
import json
import time

import socket, threading

_gravity = [[0, -9.8]]
gravity = CheckShape2D("gravity", _gravity)

tick = 0.0125 # 1tick for 0.125seconds

client_sockets = [] # 서버에 접속한 클라이언트 목록

# 서버 IP 및 열어줄 포트
HOST = '127.0.0.1'
PORT = 5050

# 서버 소켓 생성
print('>> Server Start')
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST, PORT))
server_socket.listen()

def GenSocket(client_socket, addr):

    # 씬 데이터 불러오기
    with open("scene_01.json", 'r') as f:
        scence_data = json.load(f)

    gameObjects = []

    for gameObject in scence_data:
        gameObjects.append(GameObject(gameObject))

    for gameObject in gameObjects:
        gameObject.SetGravity(gravity)

    # 게임 시간 설정
    start_time = time.time()
    before = start_time
    playtime = 0

    while True:
        now = time.time()
        playing_time = now - start_time

        if(playtime != 0):
            if(playing_time > playtime):
                break

        delta_time = now - before
        if(delta_time > tick):
            before = now

            send_data = []
            for gameObject in gameObjects:
                gameObject.CalFinalPos(delta_time)
                tem = {}
                tem["name"] = gameObject.name
                tem["pos"] = np.round(gameObject.pos, 4).tolist()[0]
                send_data.append(tem)
            client_socket.sendall(json.dumps(send_data).encode('UTF-8'))

    client_socket.close()
    server_socket.close()

while True:
    # 클라이언트 접속 시 초기 씬 로딩 후 시뮬레이션 시작
    client_socket, addr = server_socket.accept()
    print("Connectec by", addr)
    thread = threading.Thread(target=GenSocket, args=(client_socket, addr))
    thread.start()

    