[TOC]

------

## 比特币 bitcoin

> **参考资料：**
>
> - [精通比特币](http://zhibimo.com/read/wang-miao/mastering-bitcoin/index.html)
> - [区块链技术指南](http://book.8btc.com/blockchain_guide)
> - [深度解析挖矿的逻辑和技术实现](https://blog.csdn.net/taifei/article/details/72895903)
> - [stratum 协议原理](http://www.8btc.com/stratum_protocol)

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

#### 区块标识符：区块头哈希值和区块高度

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



