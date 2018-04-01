[TOC]

------

## Windows 上帝模式：包含 Windows 常用的设置

1. 在桌面新建一个文件夹

2. 重命名为 GodMode.{ED7BA470-8E54-465E-825C-99712043E01C}
## 网页自动刷新

功能：实现每 10s 自动刷新

头部加入 \<meta http-equiv="refresh" content="10">

## vagringd 的 memcheck 工具检测内存泄露

valgrind --log-file=valgrind.log --tool=memcheck --leak-check=full --show-reachable=no --workaround-gcc296-bugs=yes ./a.out

## tcpdump 抓包之三次握手、四次挥手

### TCP 连接建立（三次握手）

客户端 A，服务器 B，初始序号 seq，确认号 ack

初始状态：B 处于监听状态，A 处于打开状态

- A -> B : seq = x （A 向 B 发送连接请求报文段，A 进入同步发送状态 SYN-SENT）
- B -> A : ack = x + 1,seq = y （B 收到报文段，向 A 发送确认，B 进入同步收到状态 SYN-RCVD）
- A -> B : ack = y+1 （A 收到 B 的确认后，再次确认，A 进入连接状态 ESTABLISHED）

连接后的状态：B 收到 A 的确认后，进入连接状态 ESTABLISHED

> **为什么要三次握手？**
>
> 防止失效的连接请求突然传到服务器端，让服务器端误认为要建立连接。

### TCP 连接释放（四次挥手）

- A -> B : seq = u （A 发出连接释放报文段，进入终止等待1状态 FIN-WAIT-1）

- B -> A : ack = u + 1, seq = v （B 收到报文段，发出确认，TCP 处于半关闭，B 还可向 A 发数据，B 进入关闭等待状态 CLOSE_WAIT）

- B -> A : seq = w （B 发出连接释放报文段，进入最后确认状态 LAST-ACK）

  ==注意：如果 B 收到 A 的 FIN 报文之后，无数据待发，上述两个步骤合并，即，B 发送一个既包含对 A 报文的确认，又包含主动发起的 FIN 报文。==

  ==B -> A : ack = u + 1, seq = w（即，FIN 报文序号为 w）==

- A -> B : ack = w + 1 （A 发出确认，进入时间等待状态 TIME-WAIT）

经过 2MSL（Maximum Segment Lifetime）后，A 才进入 CLOSED 状态

> **为什么 A 进入 TIME-WAIT 后必须等待 2MSL？**
>
> - 保证 A 发送的最后一个 ACK 报文段能达到 B
> - 防止失效的报文段出现在连接中

### tcpdump 抓包实例一（ack 相对序号）

>  **tcpdump 参数 -S：**-S     Print absolute, rather than relative, TCP sequence numbers.
>
> 默认情况下，打印的 ack 序号是相对序号。

1. 服务器端（172.13.31.14）监听 12345 端口
2. 客户端（172.13.31.15）连接服务器
3. 客户端向服务器端发送 hello
4. 服务器端向客户端发送 world
5. 服务器端主动关闭连接

![](pic/tcpdump/tcp_connect_fin.png)

### tcpdump 抓包实例二（ack 绝对序号）

1. 服务器端（172.13.31.14）监听 12345 端口
2. 客户端（172.13.31.15）连接服务器
3. 客户端向服务器端发送 nice to meet you from client
4. 服务器端向客户端发送 nice to meet you too from server
5. 服务器端主动关闭连接

![](pic/tcpdump/tcp_connect_fin_with_S_flag.png)