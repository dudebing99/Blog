[TOC]

------

> **参考资料：**
>
> - [比特币白皮书中英文对照版](http://www.ehcoo.com/A%20Peer-to-Peer%20Electronic%20Cash%20System.html)
> - [精通比特币](http://zhibimo.com/read/wang-miao/mastering-bitcoin/index.html)
> - [区块链技术指南](http://book.8btc.com/blockchain_guide)
> - [区块链维基百科](https://en.wikipedia.org/wiki/Blockchain)
> - [深度解析挖矿的逻辑和技术实现](https://blog.csdn.net/taifei/article/details/72895903)
> - [stratum 协议原理](http://www.8btc.com/stratum_protocol)
> - [图灵完备维基百科](https://en.wikipedia.org/wiki/Turing_completeness)

## 比特币 bitcoin

### 比特币测试网络

1. 查看版本

```bash
kevin@ubuntu:~$ cat /etc/issue
Ubuntu 14.04.5 LTS \n \l
kevin@ubuntu:/usr/local/bin$ bitcoind -version
Bitcoin Core Daemon version v0.16.99.0-7c32b41
Copyright (C) 2009-2018 The Bitcoin Core developers

Please contribute if you find Bitcoin Core useful. Visit
<https://bitcoincore.org> for further information about the software.
The source code is available from <https://github.com/bitcoin/bitcoin>.

This is experimental software.
Distributed under the MIT software license, see the accompanying file COPYING
or <https://opensource.org/licenses/MIT>

This product includes software developed by the OpenSSL Project for use in the
OpenSSL Toolkit <https://www.openssl.org> and cryptographic software written by
Eric Young and UPnP software written by Thomas Bernard.
```

2. 运行 bitcoind

```bash
kevin@ubuntu:~$ bitcoind -testnet
```

3. 运行 bitcoin-cli

> **API 接口：**https://en.bitcoin.it/wiki/Original_Bitcoin_client/API_calls_list

- 获取状态信息

```bash
kevin@ubuntu:~$ bitcoin-cli -testnet -getinfo
{
  "version": 169900,
  "protocolversion": 70015,
  "walletversion": 169900,
  "balance": 1.65000000,
  "blocks": 1325293,
  "timeoffset": 3,
  "connections": 5,
  "proxy": "",
  "difficulty": 47237276.6179756,
  "testnet": true,
  "keypoololdest": 1528804513,
  "keypoolsize": 1000,
  "paytxfee": 0.00000000,
  "relayfee": 0.00001000,
  "warnings": "This is a pre-release test build - use at your own risk - do not use for mining or merchant applications"
}
```

- 获取钱包信息

> 可通过 https://testnet.manu.backend.hamburg/faucet 获取免费的测试币
>
> ![](pic/blockchain/faucet.png)

```bash
kevin@ubuntu:~$ bitcoin-cli -testnet getwalletinfo
{
  "walletname": "",
  "walletversion": 169900,
  "balance": 1.65000000,
  "unconfirmed_balance": 0.00000000,
  "immature_balance": 0.00000000,
  "txcount": 2,
  "keypoololdest": 1528804513,
  "keypoolsize": 1000,
  "keypoolsize_hd_internal": 1000,
  "paytxfee": 0.00000000,
  "hdseedid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "hdmasterkeyid": "44f0e603435bf5f58481b24fd597e8bd9180c840"
}
```

- 查询交易信息

```bash
kevin@ubuntu:~$ bitcoin-cli -testnet listtransactions
[
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "category": "receive",
    "amount": 1.10000000,
    "label": "",
    "vout": 0,
    "confirmations": 106,
    "blockhash": "0000000000003f000137e5a3c5c8664b559c598b4edf293dac821dcbd24ba905",
    "blockindex": 39,
    "blocktime": 1528857252,
    "txid": "93ee4409e3adb0954c799cf7705d3c09a8d619c3f1ef3808472b6a5d9cc93ccd",
    "walletconflicts": [
    ],
    "time": 1528854102,
    "timereceived": 1528854102,
    "bip125-replaceable": "no"
  },
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "category": "receive",
    "amount": 0.55000000,
    "label": "",
    "vout": 0,
    "confirmations": 105,
    "blockhash": "000000000000002bf6b26f415d62c1c8a55b4463de8abb9ee1d467da86c77082",
    "blockindex": 5,
    "blocktime": 1528857923,
    "txid": "7db5ac458ac204ceef8c23564f729ae1a3846e27815352d1d8e9275649ef5b9b",
    "walletconflicts": [
    ],
    "time": 1528857557,
    "timereceived": 1528857557,
    "bip125-replaceable": "no"
  }
]
```

- 获取对等节点连接信息

```bash
$ ./bitcoin-cli.exe -testnet getpeerinfo
[
    {
        "addr" : "88.196.208.18:18333",
        "addrlocal" : "[2001:0:9d38:953c:347f:a0a9:8ea6:9fa3]:18333",
        "services" : "0000000d",
        "lastsend" : 1529043904,
        "lastrecv" : 1529043889,
        "bytessent" : 72605,
        "bytesrecv" : 105714,
        "conntime" : 1529028404,
        "pingtime" : 0.00000000,
        "version" : 70015,
        "subver" : "/Satoshi:0.15.1/",
        "inbound" : false,
        "startingheight" : 1325463,
        "banscore" : 10,
        "syncnode" : true
    },
    {
        "addr" : "46.101.233.205:18333",
        "addrlocal" : "[2001:0:9d38:953c:347f:a0a9:8ea6:9fa3]:18333",
        "services" : "0000040d",
        "lastsend" : 1529043904,
        "lastrecv" : 1529043898,
        "bytessent" : 71706,
        "bytesrecv" : 463017,
        "conntime" : 1529028422,
        "pingtime" : 0.00000000,
        "version" : 70015,
        "subver" : "/Satoshi:0.16.0/",
        "inbound" : false,
        "startingheight" : 1325463,
        "banscore" : 10,
        "syncnode" : false
    }
]
```

- 获取最长区块链的区块数目

```bash
$ ./bitcoin-cli.exe -testnet getblockcount
1325482
```

### 密钥和地址

​	一个比特币钱包中包含一系列的密钥对，每个密钥对包括一个私钥和一个公钥。私钥（k）是一个数字，通常是随机选出的。有了私钥，我们就可以使用椭圆曲线乘法这个单向加密函数产生一个公钥（K）。有了公钥（K），我们就可以使 用一个单向加密哈希函数生成比特币地址（A）。在本节中，我们将从生成私钥开始，讲述如何使用椭圆曲线运算将私 钥生成公钥，并最终由公钥生成比特币地址。

#### 钱包地址的生成

![img](pic/bitcoin/wallet_address.jpg) 

1. 首先使用随机数发生器生成一个『私钥』。一般来说这是一个256 bits 的数，拥有了这串数字就可以对相应『钱包地址』中的比特币进行操作，所以必须被安全地保存起来。
2. 『私钥』经过 SECP256K1 算法处理生成了『公钥』。SECP256K1 是一种椭圆曲线算法，通过一个已知『私钥』时可以算得『公钥』，而『公钥』已知时却无法反向计算出『私钥』。这是保障比特币安全的算法基础
3.  同 SHA256 一样，RIPEMD160 也是一种 Hash 算法，由『公钥』可以计算得到『公钥哈希』，而反过来是行不通的。
4. 将一个字节的地址版本号连接到『公钥哈希』头部（对于比特币网络的 pubkey 地址，这一字节为“0”），然后对其进行两次 SHA256 运算，将结果的前 4 字节作为『公钥哈希』的校验值，连接在其尾部。
5. 将上一步结果使用 BASE58 进行编码(比特币定制版本)，就得到了『钱包地址』。

#### 私钥、公钥、钱包地址之间的关系

![img](pic/bitcoin/private_public_address.jpg) 

​	通过『私钥』可以得到上述计算过程中所有的值。 『公钥哈希』和『钱包地址』可以通过互逆运算进行转换，所以它们是等价的。 

### 比特币网络

#### p2p 网络架构

#### 节点类型及分工

- 钱包
- 矿工
- 完整区块链
- 网络路由节点

### 区块链

#### 区块结构

​	区块是一种被包含在公开账簿（区块链）里的聚合了交易信息的容器数据结构。它由一个包含元数据的区块头和紧跟其后的构成区块主体的一长串交易组成。区块头是 80 字节，而平均每个交易至少是 250 字节，而且平均每个区块至少包含超过 500 个交易。因此，一个包含所有交易的完整区块比区块头的 1000 倍还要大。

| 大小             | 字段       | 描述                             |
| ---------------- | ---------- | -------------------------------- |
| 4 字节           | 区块大小   | 用字节表示的该字段之后的区块大小 |
| 80 字节          | 区块头     | 组成区块头的几个字段             |
| 1-9 （可变整数） | 交易计数器 | 交易的数量                       |
| 可变的           | 交易       | 记录在区块里的交易信息           |

#### 区块头

​	区块头由三组区块元数据组成。首先是一组引用父区块哈希值的数据，这组元数据用于将该区块与区块链中前一区块相连接。第二组元数据，即难度、时间戳和 nonce，与挖矿竞争相关。第三组元数据是 merkle 树根（一种用来有效地总结区块中所有交易的数据结构）。

| 大小    | 字段         | 描述                                           |
| ------- | ------------ | ---------------------------------------------- |
| 4 字节  | 版本         | 版本号，用于跟踪软件/协议的更新                |
| 32 字节 | 父区块哈希值 | 引用区块链中父区块的哈希值                     |
| 32 字节 | Merkle 根    | 该区块中交易的 merkle 树根的哈希值             |
| 4 字节  | 时间戳       | 该区块产生的近似时间（精确到秒的 Unix 时间戳） |
| 4 字节  | 难度目标     | 该区块工作量证明算法的难度目标                 |
| 4 字节  | Nonce        | 用于工作量证明算法的计数器                     |

#### 区块标识符

​	区块标识符：包括区块头哈希值和区块高度。

​	区块主标识符是它的加密哈希值，一个通过SHA256算法对区块头进行二次哈希计算而得到的数字指纹。产生的32字节哈希值被称为区块哈希值，但是更准确的名称是：区块头哈希值，因为只有区块头被用于计算。例如:000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 是第一个比特币区块的区块哈希值。区块哈希值可以唯一、明确地标识一个区块，并且任何节点通过简单地对区块头进行哈希计算都可以独立地获取该区块哈希值。

​	注意：**区块哈希值实际上并不包含在区块的数据结构里**，不管是该区块在网络上传输时，抑或是它作为区块链的一部分被存储在某节点的永久性存储设备上时。相反，区块哈希值是当该区块从网络被接收时由每个节点计算出来的。**区块的哈希值可能会作为区块元数据的一部分被存储在一个独立的数据库表中，以便于索引和更快地从磁盘检索区块。**

​	第二种识别区块的方式是通过该区块在区块链中的位置，即“区块高度（block height）”。第一个区块，其区块高度为0，和之前哈希值 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 所引用的区块为同一个区块。因此，区块可以通过两种方式被识别：区块哈希值或者区块高度。每一个随后被存储在第一个区块之上的区块在区块链中都比前一区块“高”出一个位置，就像箱子一个接一个堆叠在其他箱子之上。

​	注意：**区块高度也不是区块数据结构的一部分**，它并不被存储在区块里。当节点接收来自比特币网络的区块时，会动态地识别该区块在区块链里的位置（区块高度）。**区块高度也可作为元数据存储在一个索引数据库表中以便快速检索。**

> 一个区块的区块哈希值总是能唯一地识别出一个特定区块。一个区块也总是有特定的区块高度。但是，一个特定的区块高度并不一定总是能唯一地识别出一个特定区块。更确切地说，两个或者更多数量的区块也许会为了区块链中的一个位置而竞争。

#### 创世区块

​	区块链里的第一个区块创建于2009年，被称为创世区块。它是区块链里面所有区块的共同祖先，这意味着你从任一区块，循链向后回溯，最终都将到达创世区块。

​	因为创世区块被编入到比特币客户端软件里，所以每一个节点都始于至少包含一个区块的区块链，这能确保创世区块不会被改变。每一个节点都“知道”创世区块的哈希值、结构、被创建的时间和里面的一个交易。因此，每个节点都把该区块作为区块链的首区块，从而构建了一个安全的、可信的区块链的根。

#### 区块的连接

> 区块通过引用父区块的区块头哈希值的方式，以链条的形式进行相连

​	比特币的完整节点保存了区块链从创世区块起的一个本地副本。随着新的区块的产生，该区块链的本地副本会不断地更新用于扩展这个链条。当一个节点从网络接收传入的区块时，它会验证这些区块，然后链接到现有的区块链上。为建立一个连接，一个节点将检查传入的区块头并寻找该区块的“父区块哈希值”。 

#### Merkle 树

​	Merkle 树是一种哈希二叉树，它是一种用作快速归纳和校验大规模数据完整性的数据结构。这种二叉树包含加密哈希值。 

​	在比特币网络中，Merkle 树被用来归纳一个区块中的所有交易，同时生成整个交易集合的数字指纹，且提供了一种校验区块是否存在某交易的高效途径。生成一棵完整的 Merkle 树需要递归地对哈希节点对进行哈希，并将新生成的哈希节点插入到 Merkle 树中，直到只剩一个哈希节点，该节点就是 Merkle 树的根。在比特币的 Merkle树中两次使用到了 SHA256 算法，因此其加密哈希算法也被称为 double-SHA256。

​	当N个数据元素经过加密后插入 Merkle 树时，你至多计算 2*log2(N) 次就能检查出任意某数据元素是否在该树中，这使得该数据结构非常高效。

### 挖矿与共识

## 区块链技术

### 定义

​	区块链：**由使用密码学原理使之连接和保证安全的块**所组成的一个不断增长的数据记录列表。每一个区块包含一个前一个区块的密码学哈希值、一个时间戳，和交易数据。

### 应用场景

​	区块链属于一种去中心化的记录技术。参与到系统上的节点，可能不属于同一组织，彼此互不信任；区块链数据由所有节点共同维护，每个参与维护节点都能复制获得一份完整记录的拷贝。跟传统的数据库技术相比，其特点应该包括：

- 维护一条不断增长的链，只可能添加记录，而发生过的记录都不可篡改

- 去中心化，或者说多中心化，无集中的控制，实现上尽量分布式
- 可以通过密码学的机制来确保交易无法抵赖和破坏，并尽量保护用户信息和记录的隐私性


​	更进一步的，还可以将智能合约跟区块链结合到一起，让其提供除了交易功能外更灵活的合约功能，执行更为复杂的操作（实际上，比特币区块链已经支持简单的脚本计算）。这样扩展之后的区块链，已经超越了单纯数据记录的功能了，实际上带有“普适计算”的意味了。

| 定位             | 功能     | 智能合约           | 一致性       | 权限 | 类型   | 性能   | 代表        |
| ---------------- | -------- | ------------------ | ------------ | ---- | ------ | ------ | ----------- |
| 公信的数字货币   | 记账功能 | 不带有或较弱       | PoW          | 无   | 公有链 | 较低   | 比特币      |
| 公信的交易处理   | 智能合约 | 图灵完备           | PoW、PoS     | 无   | 公有链 | 受限   | 以太坊      |
| 带权限的交易处理 | 商业处理 | 多种语言，图灵完备 | 多种，可插拔 | 支持 | 联盟链 | 可扩展 | Hyperledger |

### 分类

​	根据参与者的不同，可以分为公开（Public）链、联盟（Consortium）链和私有（Private）链。

公开链，顾名思义，任何人都可以参与使用和维护，典型的如比特币区块链，信息是完全公开的。

​	如果引入许可机制，包括私有链和联盟链两种。

​	私有链，则是集中管理者进行限制，只能得到内部少数人可以使用，信息不公开。

​	联盟链则介于两者之间，由若干组织一起合作维护一条区块链，该区块链的使用必须是有权限的管理，相关信息会得到保护，典型如银联组织。

### 商业价值

​	现代商业的典型模式为，交易方通过协商和执行合约，完成交易过程。区块链擅长的正是如何管理合约，确保合约的顺利执行。根据类别和应用场景不同，区块链所体现的特点和价值也不同。

​	从技术特点上，区块链一般被认为具有：

- 分布式容错性：网络极其鲁棒，容错 1/3 左右节点的异常状态

- 不可篡改性：一致提交后的数据会一直存在，不可被销毁或修改

- 隐私保护性：密码学保证了未经授权者能访问到数据，但无法解析

  随之带来的业务特性将可能包括：

- 可信任性：区块链技术可以提供天然可信的分布式账本平台，不需要额外第三方中介机构

- 降低成本：跟传统技术相比，区块链技术可能带来更短的时间、更少的人力和维护成本

- 增强安全：区块链技术将有利于安全可靠的审计管理和账目清算，减少犯罪可能性，和各种风险

### 理论

#### 图灵完全

​	图灵完全性通常指具有无限存储能力的通用物理机器或编程语言。简单来说，一切可计算的问题都能计算（给定足够的时间和存储），这样的虚拟机或者编程语言就叫图灵完备的。