[TOC]

------

## 比特币 bitcoin

> **参考资料：**
>
> - [精通比特币](http://zhibimo.com/read/wang-miao/mastering-bitcoin/index.html)
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

