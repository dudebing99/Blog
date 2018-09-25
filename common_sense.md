[TOC]

------

## 编程相关

### JavaScript

#### var、let、const 区别

- 使用 var 声明的变量，其作用域为该语句所在的函数内，且存在变量提升现象
- 使用 let 声明的变量，其作用域为该语句所在的代码块内，不存在变量提升
- 使用 const 声明的是常量，在后面出现的代码中不能再修改该常量的值

### Solidity

#### 不同合约中共享 enum

在合约 Supplier 中定义枚举

```javascript
contract Supplier {
  enum State { inactive, active, kaput }
  State constant DEFAULT_STATE = State.inactive

  State public status;

  function Supplier() {
    status = DEFAULT_STATE;
  }
}
```

在合约 Producer 中使用

```javascript
contract Producer {
  function addSupplier(Supplier _supplier) {
    require(_supplier.status() == Supplier.State.active);
  }
}
```

总结：使用时，加上枚举所在合约作为域前缀即可，例如 `Supplier.State.active`

### Bitcoin

#### minrelaytxfee、mintxfee

> 参考资料：https://bitcointalk.org/index.php?topic=2045575.0

- minrelaytxfee is used to define what the minimum fee should be on a transaction for your node to relay it

- mintxfee is the minimum fee that the client will *create* a transaction with

> So, if minrelaytxfee is set to 0.00001 your node will happily relay any transactions with that fee or higher (ie. yours and other peoples txes)... however, if you then set mintxfee to 0.00005, then any transaction you create will have that value as the minimum possible fee, but you'll still relay other peoples txes with fees of only 0.00001. 
>

## 计算机组成原理

### 原码、反码、补码

> **总结：**补码的补码等于原码

- 原码

原码就是符号位加上真值的绝对值，即用第一位表示符号，其余位表示值。比如如果是 8 位二进制

> [+1]~原~ = 0000 0001
>
> [-1]~原~ = 1000 0001

第一位是符号位。因为第一位是符号位，所以 8 位二进制数的取值范围就是

> [1111 1111, 0111 1111]

即

> [-127, 127]

原码是人脑最容易理解和计算的表示方式

- 反码

反码的表示方法是：正数的反码是其本身；负数的反码是在其原码的基础上，符号位不变，其余各个位取反。

> [+1] = [00000001]~原~ = [00000001]~反~
>
> [-1] = [10000001]~原~ = [11111110]~反~

可见，如果一个反码表示的是负数，人脑无法直观的看出来它的数值。通常要将其转换成原码再计算。

- 补码

补码的表示方法是：正数的补码就是其本身；负数的补码是在其原码的基础上，符号位不变，其余各位取反，最后 +1（即在反码的基础上 +1）

> [+1] = [00000001]~原~ = [00000001]~反~ = [00000001]~补~
>
> [-1] = [10000001]~原~ = [11111110]~反~ = [11111111]~补~

对于负数，补码表示方式也是人脑无法直观看出其数值的。通常也需要转换成原码再计算其数值。

## 网络编程

###  `MSL`

概念：`MSL`，`Maximum Segment Lifetime`，报文最长存活时间，是任何报文在网络上存在的最长时间，超过这个时间报文将被丢弃。

`2 MSL` 即两倍的 `MSL`，TCP 的 `TIME_WAIT` 状态也称为 `2 MSL` 等待状态，当 TCP 的一端发起主动关闭，在发出最后一个`ACK` 包后，即第 3 次握手完成后发送了第四次握手的 `ACK` 包后就进入了 `TIME_WAIT` 状态，必须在此状态上停留两倍的 `MSL` 时间，等待 `2 MSL` 时间主要目的是怕最后一个  `ACK` 包对方没收到，那么对方在超时后将重发第三次握手的 `FIN` 包，主动关闭端接到重发的 `FIN` 包后可以再发一个 `ACK` 应答包。在 `TIME_WAIT` 状态时两端的端口不能使用，要等到 `2 MSL` 时间结束才可继续使用。当连接处于 `2 MSL` 等待阶段时任何迟到的报文段都将被丢弃。在实际应用中可以通过设置 `SO_REUSEADDR` 选项达到不必等待 `2 MSL` 时间结束再使用此端口。`RFC 793` 中规定 `MSL` 为2分钟，实际应用中常用的是 30 秒，1 分钟和 2 分钟等。

###  `TTL`

概念：`TTL`，`time to live`，生存时间，IP 数据报包含 `TTL` 字段，这个生存时间是由源主机设置初始值但不是存的具体时间，而是存储了一个 IP 数据报可以经过的最大路由数，每经过一个处理它的路由器此值就减 1，当此值为 0 则数据报将被丢弃，同时发送 `ICMP` 报文通知源主机。

### `TCP_NODELAY`

`Nagle` 化在这里的含义是采用 `Nagle` 算法把较小的包组装为更大的帧。 John Nagle 是 `Nagle` 算法的发明人，后者就是用他的名字来命名的，他在 1984 年首次用这种方法来尝试解决福特汽车公司的网络拥塞问题（欲了解详情请参看 IETF RFC 896）。他解决的问题就是所谓的 `silly window syndrome`，中文称“愚蠢窗口症候群”，具体含义是，因为普遍终端应用程序每产生一次击键操作就会发送一个包，而典型情况下一个包会拥有一个字节的数据载荷以及 40 个字节长的包头，于是产生 4000% 的过载，很轻易地就能令网络发生拥塞。 `Nagle` 化后来成了一种标准并且立即在因特网上得以实现。它现在已经成为缺省配置了，但在我们看来，有些场合下把这一选项关掉也是合乎需要的。

现在让我们假设某个应用程序发出了一个请求，希望发送小块数据。我们可以选择立即发送数据或者等待产生更多的数据然后再一次发送两种策略。如果我们马上发送数据，那么交互性的以及客户/服务器型的应用程序将极大地受益。如果请求立即发出那么响应时间也会快一些。以上操作可以通过设置套接字的 `TCP_NODELAY` 选项来完成，这样就禁用了 `Nagle` 算法。

> - 在 C++ 中，可以通过 `setsockopt` 启用 `TCP_NODELAY`
>
> ```cpp
> static void _set_tcp_nodelay(int fd) {
> 	int enable = 1;
> 	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
> }
> ```
>
> - 在 Java 中，Socket 对象上有一个 `setTcpNoDelay` 的方法，直接设置成 true 即可

