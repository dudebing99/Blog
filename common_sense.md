[TOC]

------

## 编程相关

### 术语

#### ACK、utACK

- `Concept ACK`

  Agree with the idea and overall direction, but haven't reviewed the code changes or tested them.

- `utACK (untested ACK)`

  Reviewed and agree with the code changes but haven't actually tested them.

- `Tested ACK`

  Reviewed the code changes and have verified the functionality or bug fix.

- `ACK`

  A loose ACK can be confusing. It's best to avoid them unless it's a documentation/comment only change in which case there is nothing to test/verify; therefore the tested/untested distinction is not there.

- `NACK`

  Disagree with the code changes/concept. Should be accompanied by an explanation.

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

#### 合约函数可见性修饰符

- **public** - all can access
- **external** - Cannot be accessed internally, only externally
- **internal** - only this contract and contracts deriving from it can access
- **private** - can be accessed only from this contract

#### How to get contract internal transactions?

There's not currently any way to do this using the web3 API. Internal transactions, despite the name (which isn't part of the yellowpaper; it's a convention people have settled on) aren't actual transactions, and aren't included directly in the blockchain; they're value transfers that were initiated by executing a contract.

As such, they're not stored explicitly anywhere: they're the effects of running the transaction in question on the blockchain state. Blockchain explorers like etherscan obtain them by running a modified node with an instrumented EVM, which record all the value transfers that took place as part of transaction execution, storing them separately.

### Bitcoin

#### minrelaytxfee、mintxfee

> 参考资料：https://bitcointalk.org/index.php?topic=2045575.0

- minrelaytxfee is used to define what the minimum fee should be on a transaction for your node to relay it

- mintxfee is the minimum fee that the client will *create* a transaction with

> So, if minrelaytxfee is set to 0.00001 your node will happily relay any transactions with that fee or higher (ie. yours and other peoples txes)... however, if you then set mintxfee to 0.00005, then any transaction you create will have that value as the minimum possible fee, but you'll still relay other peoples txes with fees of only 0.00001. 

### Ethereum

#### Can I Speed Up My Transaction?

> 可通过 [https://ethgasstation.info/](https://ethgasstation.info/) 查看最近交易的平均交易费，以及交易费对应的优先级、大概确认时间等信息。

可以通过设置高额的 `gas price` 提高交易处理的优先级，进而达到加快交易确认速度。

> You can actually choose the priority level of your transaction. Miners will “work on” and execute transactions that offer a **higher gas price**, as they’ll get to keep the fees that you pay. Therefore, they will be incentivized to prioritize transactions that have a higher Gwei.
>
> If you want your transaction to be executed at a faster speed, then you have to be willing to pay a higher gas price. You’re essentially “jumping the line”, beating everybody that paid a lower gas price. 

### 数据库

#### SQL 注入

SQL 注入攻击（SQL Injection），简称注入攻击，是 Web 开发中最常见的一种安全漏洞。可以用它来从数据库获取敏感信息，或者利用数据库的特性执行添加用户，导出文件等一系列恶意操作，甚至有可能获取数据库乃至系统用户最高权限。而造成 SQL 注入的原因是因为程序没有有效过滤用户的输入，使攻击者成功的向服务器提交恶意的 SQL 查询代码，程序在接收后错误的将攻击者的输入作为查询语句的一部分执行，导致原始的查询逻辑被改变，额外的执行了攻击者精心构造的恶意代码。

假设有如下登陆表单：

```html
<form action="/login" method="POST">
<p>Username: <input type="text" name="username" /></p>
<p>Password: <input type="password" name="password" /></p>
<p><input type="submit" value="登陆" /></p>
</form>
```

登陆逻辑的 SQL 可能是这样的：

```go
username:=r.Form.Get("username")
password:=r.Form.Get("password")
sql:="SELECT * FROM user WHERE username='"+username+"' AND password='"+password+"'"
```

如果用户的输入的用户名如下，密码任意

```bash
myuser' or 'foo' = 'foo' --
```

那么我们的 SQL 就变成了如下所示

```sql
SELECT * FROM user WHERE username='myuser' or 'foo' = 'foo' --'' AND password='xxx'
```

在 SQL 里面 `--` 是注释标记，所以查询语句会在此中断。这就让攻击者在不知道任何合法用户名和密码的情况下成功登录了。

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

## 计算机网络

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

## 数据通信

### 单工、半双工、全双工

> 根据数据信息在传输线上的传送方向，数据通信方式分为单工通信 半双工通信和全双工通信 3 种。

- 单工通信

数据信息在通信线上始终向一个方向传输，数据信息永远从发送端传输到接收端，任何时候都不能改变信号的传输方向。例如，计算机发送打印数据给打印机，打印机只能从计算机接收数据信息，不能进行相反方向的信息传输。

- 半双工通信

数据信息可以双向传输，但必须交替进行，同一时刻只允许信号在**一个信道**上单向传输。半双工通信要求两端都具有发送装置和接受装置，因此，半双工通信实际上是一种可切换方向的单工通信。例如，对讲机通信就是典型的半双工通信方式，由于对讲机传送和接收使用相同的频率，在一方讲话的时候另一方不能讲话（只能听），但双方可以交互切换模式（讲或听）。

- 全双工通信

全双工通信允许数据同时在两个方向的传输，即有**两个信道**，可同时进行双向的数据传输。全双工通信是两个单工通信的结合，要求收发双方都有独立的接收和发送能力。全双工通信效率高，控制简单，但造价高。例如，计算机之间的通信是全双工方式。

## 社会经济学

### 马太效应

> 马太效应的名字就来源于圣经《新约·马太福音》中的一则寓言：从前，一个国王要出门远行，临行前，交给 3个仆人每人一锭银子，吩咐道:“你们去做生意，等我回来时，再来见我。”国王回来时，第一个仆人说:“主人，你交给我的一锭银子，我已赚了 10 锭。”于是，国王奖励他 10 座城邑。第二个仆人报告:“主人，你给我的一锭银子，我已赚了 5 锭。”于是，国王奖励他 5 座城邑。第三仆人报告说:“主人，你给我的 1 锭银子，我一直包在手帕里，怕丢失，一直没有拿出来。”于是，国王命令将第三个仆人的1锭银子赏给第一个仆人，说:“凡是少的，就连他所有的，也要夺过来。凡是多的，还要给他，叫他多多益善。”这就是“马太效应”，反映当今社会中存在的一个普遍现象，即赢家通吃 。

马太效应（Matthew Effect），指强者愈强、弱者愈弱的现象，广泛应用于社会心理学、教育、金融以及科学领域。马太效应，是社会学家和经济学家们常用的术语，反映的社会现象是两极分化，富的更富，穷的更穷。
马太效应，名字来自圣经《新约·马太福音》一则寓言： “凡有的，还要加倍给他叫他多余；没有的，连他所有的也要夺过来”。表面看起来“马太效应”与“平衡之道”相悖，与“二八定则”类似，但是实则它只不过是“平衡之道”的一极。