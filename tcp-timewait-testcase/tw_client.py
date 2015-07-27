#!/usr/bin/python
#coding=utf-8

# 制造erver和client同时发送FIN包的场景，测试双边同时进入TIME-WAIT状态的情况
# 服务器端代码逻辑: 当连接建立后，立即关闭连接
# 客户端代码逻辑:   当连接建立后，等待半个RTT后关闭连接
# 网络必须设置一个较大的RTT，比如200ms

import socket
import time

HOST = '221.168.20.22'
PORT = 8068
DELAY = 0.1   # which means RTT = 200ms

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
time.sleep(DELAY)
s.close()
