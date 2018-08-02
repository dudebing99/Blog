[TOC]

------

> **参考资料：**
>
> - [比特币白皮书中英文对照版](http://www.ehcoo.com/A%20Peer-to-Peer%20Electronic%20Cash%20System.html)
> - [精通比特币](http://book.8btc.com/books/1/master_bitcoin/_book/)
> - [精通比特币第二版](http://book.8btc.com/books/6/masterbitcoin2cn/_book/)
> - [区块链技术指南](http://book.8btc.com/blockchain_guide)
> - [区块链维基百科](https://en.wikipedia.org/wiki/Blockchain)
> - [深度解析挖矿的逻辑和技术实现](https://blog.csdn.net/taifei/article/details/72895903)
> - [stratum 协议原理](http://www.8btc.com/stratum_protocol)
> - [图灵完备维基百科](https://en.wikipedia.org/wiki/Turing_completeness)
> - [基于区块链的存证业务构想](https://zhuanlan.zhihu.com/p/33462619)
> - [以太坊 Web3.js 开发基础](https://www.jianshu.com/p/f3f36447546e)
> - [Web3.js API 中文文档](http://web3.tryblockchain.org/index.html)
> - [Web3 tutorial](https://github.com/cooleye/web3tutorial)
> - [Solidity 中文开发文档](http://solidity-cn.readthedocs.io/zh/develop/index.html)
> - [Solidity 英文开发文档](http://solidity.readthedocs.io/en/v0.4.24/)
> - [Contract tutorial](https://github.com/ethereum/go-ethereum/wiki/Contract-Tutorial)
> - [Learning-Bitcoin-from-the-Command-Line](https://github.com/ChristopherA/Learning-Bitcoin-from-the-Command-Line)

## DIY

### 比特币测试网络

> **OS: **Ubuntu 14.04.5 LTS
>
> **Bitcoin Code Daemon:** v0.16.99.0-7c32b41

#### 运行 bitcoind

```bash
kevin@ubuntu:~$ bitcoind -testnet
```

#### 运行 bitcoin-cli

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

### 以太坊初步探索

> **OS:** Ubuntu 14.04.5 LTS
>
> **geth: **1.8.13-unstable
>
> **solc:** 0.4.24+commit.e67f0147.Linux.g++
>
> **golang:** 1.10.3

#### 启动 geth

```bash
root:bin# ./geth --datadir "./data" --dev console
INFO [07-25|09:49:34.448] Maximum peer count                       ETH=25 LES=0 total=25
INFO [07-25|09:49:35.293] Using developer account                  address=0x04f14C835B74f79B7dEf175C4e481929f9800501
INFO [07-25|09:49:35.293] Starting peer-to-peer node               instance=Geth/v1.8.13-unstable-040dd5bd/linux-amd64/go1.10.3
INFO [07-25|09:49:35.293] Allocated cache and file handles         database=/root/go/src/github.com/ethereum/go-ethereum/build/bin/data/geth/chaindata cache=768 handles=512
INFO [07-25|09:49:35.326] Persisted trie from memory database      nodes=11 size=1.71kB time=30.048µs gcnodes=0 gcsize=0.00B gctime=0s livenodes=1 livesize=0.00B
INFO [07-25|09:49:35.326] Initialised chain configuration          config="{ChainID: 1337 Homestead: 0 DAO: <nil> DAOSupport: false EIP150: 0 EIP155: 0 EIP158: 0 Byzantium: 0 Constantinople: <nil> Engine: clique}"
INFO [07-25|09:49:35.326] Initialising Ethereum protocol           versions="[63 62]" network=1337
INFO [07-25|09:49:35.327] Loaded most recent local header          number=0 hash=8f3035…7124e0 td=1
INFO [07-25|09:49:35.327] Loaded most recent local full block      number=0 hash=8f3035…7124e0 td=1
INFO [07-25|09:49:35.327] Loaded most recent local fast block      number=0 hash=8f3035…7124e0 td=1
INFO [07-25|09:49:35.327] Loaded local transaction journal         transactions=0 dropped=0
INFO [07-25|09:49:35.327] Regenerated local transaction journal    transactions=0 accounts=0
INFO [07-25|09:49:35.327] Starting P2P networking 
INFO [07-25|09:49:35.328] started whisper v.6.0 
INFO [07-25|09:49:35.328] RLPx listener up                         self="enode://ad026d00f9ae6a7c2fae54aec6fe1692818a372aeae28418a1a0d5787809637e2b74c24038c15b734ef25a1b128915fbd75ae74aacedc428163b37346d872245@[::]:35685?discport=0"
INFO [07-25|09:49:35.329] IPC endpoint opened                      url=/root/go/src/github.com/ethereum/go-ethereum/build/bin/data/geth.ipc
INFO [07-25|09:49:35.329] Transaction pool price threshold updated price=18000000000
INFO [07-25|09:49:35.329] Etherbase automatically configured       address=0x04f14C835B74f79B7dEf175C4e481929f9800501
INFO [07-25|09:49:35.329] Starting mining operation 
INFO [07-25|09:49:35.329] Commit new mining work                   number=1 txs=0 uncles=0 elapsed=58.163µs
WARN [07-25|09:49:35.330] Block sealing failed                     err="waiting for transactions"
Welcome to the Geth JavaScript console!

instance: Geth/v1.8.13-unstable-040dd5bd/linux-amd64/go1.10.3
coinbase: 0x04f14c835b74f79b7def175c4e481929f9800501
at block: 0 (Thu, 01 Jan 1970 08:00:00 CST)
 datadir: /root/go/src/github.com/ethereum/go-ethereum/build/bin/data
 modules: admin:1.0 clique:1.0 debug:1.0 eth:1.0 miner:1.0 net:1.0 personal:1.0 rpc:1.0 shh:1.0 txpool:1.0 web3:1.0
```

#### 查看系统变量

- eth 全局变量

```bash
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

- personal 变量

```bash
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

- miner 变量

```bash
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

#### 账户操作

- 查看系统所有用户

```bash
> eth.accounts
["0x04f14c835b74f79b7def175c4e481929f9800501"]
```

- 创建新用户

```bash
> personal.newAccount('123456')
"0xa5f833dd93979f15d67392ce78ad78829e5a97e1"
> eth.accounts
["0x04f14c835b74f79b7def175c4e481929f9800501", "0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"]
```

​	创建成功后，会展示创建成功的地址，其中上面的表达式中，中间传入的 123456 为密码 。再次查看系统所有用户，可以看到共有两个用户。

- 给用户取别名

```bash
> user1 = eth.accounts[0]
"0x04f14c835b74f79b7def175c4e481929f9800501"
> user2 = eth.accounts[1]
"0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"
> user1
"0x04f14c835b74f79b7def175c4e481929f9800501"
> user2
"0xe9db1b66197355d0f05534a53f6b7dcf0c873c76"
```

​	操作成功后，用户别名 user1、user2 已经成功赋值

- 对账户进行解锁

```bash
> personal.unlockAccount(user2, '123')
Error: could not decrypt key with given passphrase
> personal.unlockAccount(user2, '123456')
true
```

​	为了安全起见，一般一个用户在创建的时候都处于锁定状态，输入密码进行解锁。

​	如果不解锁，直接对用户操作，例如，对用户转账，则报错如下：

```bash
> eth.sendTransaction({from:user1, to:user2, value:666})
Error: authentication needed: password or unlock
    at web3.js:3143:20
    at web3.js:6347:15
    at web3.js:5081:36
    at <anonymous>:1:1
```

- 检查账户余额

```bash
> eth.getBalance(user1)
1.15792089237316195423570985008687907853269984665640564039457584007913129639927e+77
> eth.getBalance(user2)
0
```

- 转账

```bash
> eth.sendTransaction({from:user1, to:user2, value:100})
INFO [07-25|16:58:43.662] Submitted transaction                    fullhash=0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa recipient=0xE9DB1b66197355D0f05534A53F6B7DcF0c873c76
"0x4daf7f1fa1b7c8e8b0c5770fdeaf1d0945782027646399822dbf2a303b1adaaa"
> eth.getBalance(user2)
0
```

​	转账之后，账户余额仍然没变。此时，需要启动挖矿使交易加入到区块链中。

```bash
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

- 查看交易信息

```bash
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

#### 合约

- 编写 Solidity 合约脚本

```basic
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

- 编译脚本，生成 ABI 接口和合约的二进制代码 

> 备注：利用 [Remix](https://remix.ethereum.org) 在线编译合约

```basic
root:ethereum# solc --optimize --abi --bin sample.sol

======= sample.sol:Sample =======
Binary: 
608060405234801561001057600080fd5b50604051602080610114833981016040525160005560e1806100336000396000f30060806040526004361060525763ffffffff7c01000000000000000000000000000000000000000000000000000000006000350416633fa4f2458114605757806360fe47b114607b5780636d4ce63c146092575b600080fd5b348015606257600080fd5b50606960a4565b60408051918252519081900360200190f35b348015608657600080fd5b50609060043560aa565b005b348015609d57600080fd5b50606960af565b60005481565b600055565b600054905600a165627a7a723058207098d9dc5ae86fe75d1016078954658c002f112da516ed90f64c901feb340d870029
Contract JSON ABI 
[{"constant":true,"inputs":[],"name":"value","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"v","type":"uint256"}],"name":"set","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"get","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"v","type":"uint256"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}]
```

- 定义合约

```basic
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

> hex = "0x608060405234801561001057600080fd5b50604051602080610114833981016040525160005560e1806100336000396000f30060806040526004361060525763ffffffff7c01000000000000000000000000000000000000000000000000000000006000350416633fa4f2458114605757806360fe47b114607b5780636d4ce63c146092575b600080fd5b348015606257600080fd5b50606960a4565b60408051918252519081900360200190f35b348015608657600080fd5b50609060043560aa565b005b348015609d57600080fd5b50606960af565b60005481565b600055565b600054905600a165627a7a723058207098d9dc5ae86fe75d1016078954658c002f112da516ed90f64c901feb340d870029"
"0x608060405234801561001057600080fd5b50604051602080610114833981016040525160005560e1806100336000396000f30060806040526004361060525763ffffffff7c01000000000000000000000000000000000000000000000000000000006000350416633fa4f2458114605757806360fe47b114607b5780636d4ce63c146092575b600080fd5b348015606257600080fd5b50606960a4565b60408051918252519081900360200190f35b348015608657600080fd5b50609060043560aa565b005b348015609d57600080fd5b50606960af565b60005481565b600055565b600054905600a165627a7a723058207098d9dc5ae86fe75d1016078954658c002f112da516ed90f64c901feb340d870029"

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
    accounts: ["0x2f3efd9475fb969eecfdade75a1dae02dbd92e25"],
    blockNumber: 0,
    coinbase: "0x2f3efd9475fb969eecfdade75a1dae02dbd92e25",
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
  },
  at: function(address, callback),
  getData: function(),
  new: function()
}
```

- 把合约代码部署上链

> 合约部署上链时，给构造函数传参  99，即赋初值 99

```basic
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
  }, INFO [07-26|22:33:47.302] Commit new mining work                   number=2 txs=0 uncles=0 elapsed=1.098ms
{
      constant: true,
      inputs: [],
      name: "get",
      outputs: [{...}],
      payable: false,
      stateMutability: "view",
      type: "function"
  }, WARN [07-26|22:33:47.303] Block sealing failed                     err="waiting for transactions"
{
      inputs: [{...}],
      payable: false,
      stateMutability: "nonpayable",
      type: "constructor"
  }],
  address: undefined,
  transactionHash: "0x2280fe5f44756e44f0c7e9740f254ab18261d3b7836d801b43678ddf442480a0"
}
```

- 查看交易细节

> 根据交易 hash 查看交易细节

```basic
> samplerecpt = eth.getTransactionReceipt("0x2280fe5f44756e44f0c7e9740f254ab18261d3b7836d801b43678ddf442480a0")
{
  blockHash: "0x3656ba77328cd78087d3f5a61287d95241fba76d7de606868f1561f147a17dc1",
  blockNumber: 1,
  contractAddress: "0x1ce836d1d1839f1ed07b01ae152a4c5f0ee2a041",
  cumulativeGasUsed: 134093,
  from: "0x2f3efd9475fb969eecfdade75a1dae02dbd92e25",
  gasUsed: 134093,
  logs: [],
  logsBloom: "0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  status: "0x1",
  to: null,
  transactionHash: "0x2280fe5f44756e44f0c7e9740f254ab18261d3b7836d801b43678ddf442480a0",
  transactionIndex: 0
}
```

- 合约命名

> 交易信息中，contractAddress 表示合约地址

``` basic
> samplecontract = sample.at("0x1ce836d1d1839f1ed07b01ae152a4c5f0ee2a041")
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

- 执行合约 get 函数

```basic
> samplecontract.get.call()
99
```

- 执行合约 set 函数

```basic
> samplecontract.set.sendTransaction(1001, {from:eth.accounts[0], gas:3000000})
"0x528209c6bcdbbb4a636eebd90cfc918eb8e463fed1f0cb3bbd8ef19df0654808"
```

- 执行合约 get 函数

```basic
> samplecontract.get.call()
1001
```

### 以太坊 Web3.js 开发基础

> **OS:** Ubuntu 14.04.5 LTS
>
> **NPM:** 5.6.0
>
> **nodejs:** 8.11.3
>
> **web3:** 0.20.1（**注意：不同版本接口不兼容**）

#### 简介

​	web3.js 是一个通过 [RPC 调用](https://github.com/ethereum/wiki/wiki/JSON-RPC) 和本地以太坊节点进行通信的 js 库。web3.js 可以与任何暴露了 RPC 接口的以太坊节点连接。 web3 中提供了 eth 对象 -- web3.eth 来与以太坊区块链进行交互。

#### 安装 testrpc

> - ethereumjs-testrpc 库后续被重命名为 ganache-cli
> - testrpc 不同于 geth，geth 是真正的以太坊环境，testrpc 是在本地使用内存模拟的一个以太坊环境，对于开发调试来说，更为方便快捷，当合约在 testrpc 中测试通过后，再部署到 geth 中去。 

```bash
root:~#  npm install -g ethereumjs-testrpc
npm WARN deprecated ethereumjs-testrpc@6.0.3: ethereumjs-testrpc has been renamed to ganache-cli, please use this package from now on.
/usr/local/bin/testrpc -> /usr/local/lib/node_modules/ethereumjs-testrpc/build/cli.node.js
npm WARN optional SKIPPING OPTIONAL DEPENDENCY: fsevents@1.2.4 (node_modules/ethereumjs-testrpc/node_modules/fsevents):
npm WARN notsup SKIPPING OPTIONAL DEPENDENCY: Unsupported platform for fsevents@1.2.4: wanted {"os":"darwin","arch":"any"} (current: {"os":"linux","arch":"x64"})
+ ethereumjs-testrpc@6.0.3
updated 1 package in 11.83s
```

#### 启动 testrpc

> 会自动创建 10 个账户，每个账户默认有 100 个以太币 

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

#### 方式一：交互式操作

- 初始化 web3

> 执行 node 进入交互式环境，输入（复制 + 粘贴）如下代码

```javascript
let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}
```

- 查看账户

```basic
> web3.eth.accounts
[ '0x931a85a8b24e00e5aa56651a64dd55f3c849fe14',
  '0x7a74f95c7b520f498b31fedcbffaa9a1b12a7dea',
  '0xe4ef6200839fd673eb1dd42db3842bb4cbf1450b',
  '0x9444971ba35b6dcbca9909021cb6463902940dc6',
  '0x79d39a05ec5afda98ccd435ba0124de32a186619',
  '0xeaef1169fdb348b44efe860228666a35f2a33476',
  '0xb7e4e662bf202c16c4d2e6c9b8254f3dc771f9b2',
  '0xf887537611c4f20b788c0448e912e29cbc46e398',
  '0x33687b265c9910ae865334735959f9d02c874db2',
  '0x20587c3c3609c4cd954364c828b85077d68357cd' ]
```

- 查看账户余额

```basic
> web3.eth.getBalance('0x931a85a8b24e00e5aa56651a64dd55f3c849fe14')
BigNumber { s: 1, e: 20, c: [ 1000000 ] }
```

#### 方式二：运行 js 脚本

- 创建包含操作的 js 脚本

```javascript
let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

version = web3.version.api
console.log(version);

console.log(web3.eth.accounts);

console.log(web3.eth.getBalance('0x3ead381b015ee447e753081f96b918350861417e'));
```

- 执行脚本

```bash
root:ethereum# node test.js 
0.20.1
[ '0x931a85a8b24e00e5aa56651a64dd55f3c849fe14',
  '0x7a74f95c7b520f498b31fedcbffaa9a1b12a7dea',
  '0xe4ef6200839fd673eb1dd42db3842bb4cbf1450b',
  '0x9444971ba35b6dcbca9909021cb6463902940dc6',
  '0x79d39a05ec5afda98ccd435ba0124de32a186619',
  '0xeaef1169fdb348b44efe860228666a35f2a33476',
  '0xb7e4e662bf202c16c4d2e6c9b8254f3dc771f9b2',
  '0xf887537611c4f20b788c0448e912e29cbc46e398',
  '0x33687b265c9910ae865334735959f9d02c874db2',
  '0x20587c3c3609c4cd954364c828b85077d68357cd',
  '0xb272afb0246c0b29768976384713d277ab09a92d',
  '0x1a671ee00f4233dcd572c92f88a187a0f134aeca' ]
BigNumber { s: 1, e: 0, c: [ 0 ] }
```

## 比特币 bitcoin

### 密钥和地址

​	一个比特币钱包中包含一系列的密钥对，每个密钥对包括一个私钥和一个公钥。私钥（k）是一个数字，通常是随机选出的。有了私钥，我们就可以使用椭圆曲线乘法这个单向加密函数产生一个公钥（K）。有了公钥（K），我们就可以使 用一个单向加密哈希函数生成比特币地址（A）。在本节中，我们将从生成私钥开始，讲述如何使用椭圆曲线运算将私 钥生成公钥，并最终由公钥生成比特币地址。

#### 钱包地址的生成

![img](pic/bitcoin/wallet_address.jpg)

1. 首先使用随机数发生器生成一个『私钥』。一般来说这是一个256 bits 的数，拥有了这串数字就可以对相应『钱包地址』中的比特币进行操作，所以必须被安全地保存起来。
2. 『私钥』经过 SECP256K1 算法处理生成了『公钥』。SECP256K1 是一种椭圆曲线算法，通过一个已知『私钥』时可以算得『公钥』，而『公钥』已知时却无法反向计算出『私钥』。这是保障比特币安全的算法基础
3.  同 SHA256 一样，RIPEMD160 也是一种 Hash 算法，由『公钥』可以计算得到『公钥哈希』，而反过来是行不通的。
4. 将一个字节的地址版本号连接到『公钥哈希』头部（对于比特币网络的 pubkey 地址，这一字节为“0”），然后对其进行两次 SHA256 运算，将结果的前 4 字节作为『公钥哈希』的校验值，连接在其尾部。
5. 将上一步结果使用 BASE58 进行编码（比特币定制版本），就得到了『钱包地址』。

#### 私钥、公钥、钱包地址

![img](pic/bitcoin/private_public_address.jpg)

​	通过『私钥』可以得到上述计算过程中所有的值。 『公钥哈希』和『钱包地址』可以通过互逆运算进行转换，所以它们是等价的。

#### 使用『私钥』对交易进行签名

![img](pic/bitcoin/transaction.jpg)

​	比特币钱包间的转账是通过交易（Transaction）实现的。交易数据是由转出钱包『私钥』的所有者生成，也就是说有了『私钥』就可以花费该钱包的比特币余额。生成交易的过程如下：

1. 交易的原始数据包括“转账数额”和“转入钱包地址”，但是仅有这些是不够的，因为无法证明交易的生成者对“转出钱包地址”余额有动用的权利。所以需要用『私钥』对原始数据进行签名。
2. 生成“转出钱包公钥”，这一过程与生成『钱包地址』的第 2 步是一样的。
3. 将“转出签名”和“转出公钥”添加到原始交易数据中，生成了正式的交易数据，这样它就可以被广播到比特币网络进行转账了。

#### 使用『公钥』对签名进行验证

![img](pic/bitcoin/verify.jpg)

​	交易数据被广播到比特币网络后，节点会对这个交易数据进行检验，其中就包括对签名的校验。如果校验正确，那么这笔余额就成功地从“转出钱包”转移到“转入钱包”了。

#### 结论

> 本文仅讨论标准 P2PKH（对公钥哈希的付款 ） 交易方式，P2SH 不在讨论范围内。

​	如果一个『钱包地址』从未曾发送余额到其他『钱包地址』，那么它的『公钥』是不会暴露在比特币网络上的。而公钥生成算法（SECP256K1）是不可逆的，即使『公钥』暴露，也很难对『私钥』的安全性造成影响（难易取决于『私钥』的生成算法）。

​	『私钥』用来生成『公钥』和『钱包地址』，也用来对交易进行签名。拥有了『私钥』就是拥有了对这个钱包余额的一切操作权力。

​	所以，保护『私钥』是所有比特币钱包应用最基本也是最重要的功能。

### 钱包

​	“钱包”一词在比特币中有多重含义。 广义上，钱包是一个应用程序，为用户提供交互界面。 钱包控制用户访问权限，管理密钥和地址，跟踪余额以及创建和签名交易。 狭义上，即从程序员的角度来看，“钱包”是指用于存储和管理用户密钥的数据结构。

#### 非确定性钱包

​        **非确定性钱包（nondeterministic wallet）**，其中每个密钥都是从随机数独立生成的。密钥彼此无关。这种钱包也被称为“Just a Bunch Of Keys（一堆密钥）”，简称 JBOK 钱包

#### 确定性钱包

​        **确定性钱包（deterministic wallet）**，其中所有的密钥都是从一个主密钥派生出来，这个主密钥即为种子（seed）。该类型钱包中所有密钥都相互关联，如果有原始种子，则可以再次生成全部密钥。确定性钱包中使用了许多不同的密钥推导方法。最常用的推导方法是使用树状结构，称为分级确定性钱包或 HD 钱包。

### 交易

> 比特币交易是比特币系统中最重要的部分。根据比特币系统的设计原理，系统中任何其他的部分都是为了确保比特币交易可以被生成、能在比特币网络中得以传播和通过验证，并最终添加入全球比特币交易总账簿（比特币区块链）。比特币交易的本质是数据结构，这些数据结构中含有比特币交易参与者价值转移的相关信息。比特币区块链是一本全球复式记账总账簿，每个比特币交易都是在比特币区块链上的一个公开记录。

​	通过 Bitcoin Core 解码的一笔标准的交易信息如下：

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

​	比特币交易中的基础构建单元是交易输出。 交易输出是比特币不可分割的基本组合，记录在区块上，并被整个网络识别为有效。 比特币完整节点跟踪所有可找到的和可使用的输出，称为 “未花费的交易输出”（unspent transaction outputs），即 UTXO。 所有 UTXO 的集合被称为 UTXO 集，目前有数百万个 UTXO。 当新的 UTXO被创建，UTXO 集就会变大，当 UTXO 被消耗时，UTXO 集会随着缩小。每一个交易都代表 UTXO 集的变化（状态转换） 。

​	一笔交易会消耗先前的已被记录（存在）的 UTXO，并创建新的 UTXO 以备未来的交易消耗。通过这种方式，一定数量的比特币价值在不同所有者之间转移，并在交易链中消耗和创建 UTXO。一笔比特币交易通过使用所有者的签名来解锁 UTXO，并通过使用新的所有者的比特币地址来锁定并创建 UTXO。

​	从交易的输出与输入链角度来看，有一个例外，即存在一种被称为“创币交易”（Coinbase Transaction）的特殊交易，它是每个区块中的第一笔交易，这种交易存在的原因是作为对挖矿的奖励，创造出全新的可花费比特币用来支付给“赢家”矿工。

#### 交易输出

​	每一笔比特币交易都会创造输出，并被比特币账簿记录下来。除特例之外（见“数据输出操作符”（OP_RETURN）），几乎所有的输出都能创造一定数量的可用于支付的比特币，也就是 UTXO。这些 UTXO 被整个网络识别，所有者可在未来的交易中使用它们。

​	UTXO 在 UTXO 集（UTXOset）中被每一个全节点比特币客户端追踪。 新的交易从UTXO 集中消耗（花费）一个或多个输出。

| 尺寸                   | 字段         | 说明                                |
| ---------------------- | ------------ | ----------------------------------- |
| 8 个字节               | 总量         | 用聪表示的比特币值（10^-8^ 比特币） |
| 1–9 个字节（可变整数） | 锁定脚本尺寸 | 用字节表示的后面的锁定脚本长度      |
| 变长                   | 锁定脚本     | 一个定义了支付输出所需条件的脚本    |

- 一定量的比特币，面值为“聪”（satoshis），是最小的比特币单位

- 确定花费输出所需条件的加密难题（cryptographic puzzle）。这个加密难题也被称为锁定脚本（locking script）, 见证脚本（witness script）, 或脚本公钥 （scriptPubKey）

#### 交易输入

​	交易输入将 UTXO（通过引用）标记为将被消费，并通过解锁脚本提供所有权证明。

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

​	大多数交易包含交易费（矿工费），这是为了确保网络安全而给比特币矿工的一种补偿。费用本身也作为一个安全机制，使经济上不利于攻击者通过交易来淹没网络。

​	交易费作为矿工打包（挖矿）一笔交易到下一个区块中的一种激励；同时作为一种抑制因素，通过对每一笔交易收取小额费用来防止对系统的滥用。成功挖到某区块的矿工将得到该区内包含的矿工费， 并将该区块添加至区块链中。

​	交易费是基于交易的千字节规模来计算的，而不是比特币交易的价值。总的来说，交易费是根据比特币网络中的市场力量确定的。矿工会依据许多不同的标准对交易进行优先级排序，包括费用，他们甚至可能在某些特定情况下免费处理交易。但大多数情况下，交易费影响处理优先级，这意味着有足够费用的交易会更可能被打包进下一个挖出的区块中；反之交易费不足或者没有交易费的交易可能会被推迟，基于尽力而为的原则在几个区块之后被处理，甚至可能根本不被处理。交易费不是强制的，而且没有交易费的交易最终也可能会被处理，但是，交易费将提高处理优先级。

#### 交易脚本和脚本语言

> 比特币交易验证并不基于静态模式**，**而是通过脚本语言的执行来实现的。这种语言允许表达几乎无限的各种条件。这也是比特币作为一种“可编程的货币”所拥有的力量。

##### 图灵非完备性

​	比特币脚本语言包含许多操作码，但都故意限定为一种重要的模式——**除了有条件的流控制以外，没有循环或复杂流控制能力**。这样就保证了脚本语言的图灵非完备性，这意味着**脚本有限的复杂性和可预见的执行次数**。脚本并不是一种通用语言，这些限制**确保该语言不被用于创造无限循环或其它类型的逻辑炸弹**，这样的炸弹可以植入在一笔交易中，引起针对比特币网络的“拒绝服务”攻击。记住，每一笔交易都会被网络中的全节点验证，受限制的语言能防止交易验证机制被作为一个漏洞而加以利用。

##### 去中心化验证

​	比特币交易脚本语言是没有中心化主体的，没有任何中心主体能凌驾于脚本之上，也没有中心主体会在脚本被执行后对其进行保存。所以执行脚本所需信息都已包含在脚本中。可以预见的是，一个脚本能在任何系统上以相同的方式执行。如果您的系统验证了一个脚本，可以确信的是每一个比特币网络中的其他系统也将验证这个脚本，这意味着一个有效的交易对每个人而言都是有效的，而且每一个人都知道这一点。这种结果可预见性是比特币系统的一项至关重要的良性特征。

##### 脚本构建（锁定与解锁）

​	比特币的交易验证引擎依赖于两类脚本来验证比特币交易：锁定脚本和解锁脚本。

​	锁定脚本是一个放置在输出上面的花费条件：它指定了今后花费这笔输出必须要满足的条件。 由于锁定脚本往往含有一个公钥或比特币地址（公钥哈希值），在历史上它曾被称为脚本公钥（scriptPubKey）。

​	解锁脚本是一个“解决”或满足被锁定脚本在一个输出上设定的花费条件的脚本，它将允许输出被消费。解锁脚本是每一笔比特币交易输入的一部分，而且往往含有一个由用户的比特币钱包（通过用户的私钥）生成的数字签名。由于解锁脚本常常包含一个数字签名，因此它曾被称作 ScriptSig。但并非所有解锁脚本都一定会包含签名。

​	每一个比特币验证节点会通过同时执行锁定和解锁脚本来验证一笔交易。每个输入都包含一个解锁脚本，并引用了之前存在的 UTXO。 验证软件将复制解锁脚本，检索输入所引用的 UTXO，并从该 UTXO 复制锁定脚本。 然后依次执行解锁和锁定脚本。 如果解锁脚本满足锁定脚本条件，则输入有效。 所有输入都是独立验证的，作为交易总体验证的一部分。

##### 脚本执行堆栈

​	比特币的脚本语言被称为基于堆栈的语言，因为它使用一种被称为堆栈的数据结构。堆栈是一个非常简单的数据结构，可以被视为一叠卡片。栈允许两个操作：push 和pop（推送和弹出）。 Push（推送）在堆栈顶部添加一个项目。 Pop（弹出）从堆栈中删除最顶端的项。栈上的操作只能作用于栈最顶端项目。堆栈数据结构也被称为“后进先出”（ Last-In-First-Out）或 “LIFO” 队列。

​	脚本语言通过从左到右处理每个项目来执行脚本。数字（数据常量）被推到堆栈上。操作码（Operators）从堆栈中推送或弹出一个或多个参数，对其进行操作，并可能将结果推送到堆栈上。例如，操作码 OP_ADD 将从堆栈中弹出两个项目，添加它们，并将结果的总和推送到堆栈上。

​	条件操作码（Conditional operators）对一个条件进行评估，产生一个 TRUE 或 FALSE 的布尔结果（boolean result）。例如， OP_EQUAL 从堆栈中弹出两个项目，如果它们相等，则推送为 TRUE（由数字1表示），否则推送为 FALSE（由数字0表示）。比特币交易脚本通常包含条件操作码，以便它们可以产生用来表示有效交易的 TRUE 结果。

##### P2PKH（Pay-to-Public-Key-Hash）

​	比特币网络处理的大多数交易花费的都是由“付款至公钥哈希”（或 P2PKH）脚本锁定的输出，这些输出都含有一个锁定脚本，将输入锁定为一个公钥哈希值，即我们常说的比特币地址。由 P2PKH 脚本锁定的输出可以通过提供一个公钥和由相应私钥创建的数字签名来解锁（使用）。

​	例如，我们可以再次回顾一下 Alice 向 Bob 咖啡馆支付的案例。Alice 下达了向 Bob 咖啡馆的比特币地址支付0.015 比特币的支付指令，该笔交易的输出内容为以下形式的锁定脚本：

```
OP_DUP OP_HASH160 <Cafe Public Key Hash> OP_EQUALVERIFY OP_CHECKSIG
```

脚本中的 Cafe Public Key Hash 即为咖啡馆的比特币地址，但该地址不是基于 Base58Check 编码。事实上，大多数比特币地址的公钥哈希值都显示为十六进制码，而不是大家所熟知的以1开头的基于 Bsase58Check 编码的比特币地址。

上述锁定脚本相应的解锁脚本是：

```
<Cafe Signature> <Cafe Public Key>
```

将两个脚本结合起来可以形成如下组合验证脚本：

```
<Cafe Signature> <Cafe Public Key> OP_DUP OP_HASH160
<Cafe Public Key Hash> OP_EQUALVERIFY OP_CHECKSIG
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

#### 区块标识符

​	区块标识符：包括区块头哈希值和区块高度。

​	区块主标识符是它的加密哈希值，一个通过 SHA256 算法对区块头进行二次哈希计算而得到的数字指纹。产生的 32 字节哈希值被称为区块哈希值，但是更准确的名称是：区块头哈希值，因为只有区块头被用于计算。例如：000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 是第一个比特币区块的区块哈希值。区块哈希值可以唯一、明确地标识一个区块，并且任何节点通过简单地对区块头进行哈希计算都可以独立地获取该区块哈希值。

​	注意：**区块哈希值实际上并不包含在区块的数据结构里**，不管是该区块在网络上传输时，抑或是它作为区块链的一部分被存储在某节点的永久性存储设备上时。相反，区块哈希值是当该区块从网络被接收时由每个节点计算出来的。**区块的哈希值可能会作为区块元数据的一部分被存储在一个独立的数据库表中，以便于索引和更快地从磁盘检索区块。**

​	第二种识别区块的方式是通过该区块在区块链中的位置，即“区块高度（block height）”。第一个区块，其区块高度为 0，和之前哈希值 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f 所引用的区块为同一个区块。因此，区块可以通过两种方式被识别：区块哈希值或者区块高度。每一个随后被存储在第一个区块之上的区块在区块链中都比前一区块“高”出一个位置，就像箱子一个接一个堆叠在其他箱子之上。

​	注意：**区块高度也不是区块数据结构的一部分**，它并不被存储在区块里。当节点接收来自比特币网络的区块时，会动态地识别该区块在区块链里的位置（区块高度）。**区块高度也可作为元数据存储在一个索引数据库表中以便快速检索。**

> 一个区块的区块哈希值总是能唯一地识别出一个特定区块。一个区块也总是有特定的区块高度。但是，一个特定的区块高度并不一定总是能唯一地识别出一个特定区块。更确切地说，两个或者更多数量的区块也许会为了区块链中的一个位置而竞争。

#### 创世区块

​	区块链里的第一个区块创建于 2009 年，被称为创世区块。它是区块链里面所有区块的共同祖先，这意味着你从任一区块，循链向后回溯，最终都将到达创世区块。

​	因为创世区块被编入到比特币客户端软件里，所以每一个节点都始于至少包含一个区块的区块链，这能确保创世区块不会被改变。每一个节点都“知道”创世区块的哈希值、结构、被创建的时间和里面的一个交易。因此，每个节点都把该区块作为区块链的首区块，从而构建了一个安全的、可信的区块链的根。

#### 区块的连接

> 区块通过引用父区块的区块头哈希值的方式，以链条的形式进行相连

​	比特币的完整节点保存了区块链从创世区块起的一个本地副本。随着新的区块的产生，该区块链的本地副本会不断地更新用于扩展这个链条。当一个节点从网络接收传入的区块时，它会验证这些区块，然后链接到现有的区块链上。为建立一个连接，一个节点将检查传入的区块头并寻找该区块的“父区块哈希值”。

#### Merkle 树

​	Merkle 树是一种哈希二叉树，它是一种用作快速归纳和校验大规模数据完整性的数据结构。这种二叉树包含加密哈希值。

​	在比特币网络中，Merkle 树被用来归纳一个区块中的所有交易，同时生成整个交易集合的数字指纹，且提供了一种校验区块是否存在某交易的高效途径。生成一棵完整的 Merkle 树需要递归地对哈希节点对进行哈希，并将新生成的哈希节点插入到 Merkle 树中，直到只剩一个哈希节点，该节点就是 Merkle 树的根。在比特币的 Merkle树中两次使用到了 SHA256 算法，因此其加密哈希算法也被称为 double-SHA256。

​	当 N 个数据元素经过加密后插入 Merkle 树时，你至多计算 2*log2(N) 次就能检查出任意某数据元素是否在该树中，这使得该数据结构非常高效。

### 挖矿与共识

## 维基链（智能合约）

### 获取节点信息

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

### 生成测试地址、充值、激活地址

#### 生成测试地址

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

#### 充值

```
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. sendtoaddress wKkoeBCynvuDmkS9XebY5vAUQC6aLVbznC 100000000000
{
    "hash" : "334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb"
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. sendtoaddress whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 100000000000
{
    "hash" : "2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012"
}
```

#### 查询余额

> 充值后，需要出块之后才能到账，可以通过查询交易信息确认是否到账，可以查询到包含上述交易 hash：
>
> 334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb、2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012
>
> ```bash
> root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. listtx
> {
>     "ConfirmTx" : [
>         "2ab57b070aa87aac85afaf21fd18e4e4211017f7104ab18980ccef287d750012",
>         "334f447dfd284b2a084560f57d3c4ad044cde1fc41470c68ffeae55aefe270fb",
>         "8ebdb18e325ae00259e6072f5c5b403dd02c3b1847c16a3f59a2c3e46c4e5cb4",
>         "f37c59ed4b4af2a85b072a823cd3c720a8fd39f8903138a1ff41d29579a9a78e",
>         "bba67872503e0eeb65b83c8e932778e7aae7cd8b379645a5cb766a072a0ad561"
>     ],
>     "UnConfirmTx" : [
>     ]
> }
> ```

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

#### 激活地址

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

#### 确认地址已激活

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

### 注册应用脚本

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

### 充值

> - 合约中，包含总金额、自由余额、每月冻结金额。（初始）自由金额实时转移到合约接收方账户，每月冻结金额将逐步解冻，变成自有金额，并转移到合约接收方账户。
>
> - 解冻逻辑：执行合约后，可以看到如下信息
>
>   ```json
>   "vFreezedFund" : [
>           {
>               "value" : 500000000,
>               "nHeight" : 538,
>               "vTag" : ""
>           },
>           {
>               "value" : 500000000,
>               "nHeight" : 543,
>               "vTag" : ""
>           }
>   ]
>   ```
>
>   多有新的区块加入时，检查当前区块高度是否大于等于合约中冻结金额的 nHeight，如果是，将该比冻结金额解冻，变成自有金额，并转移到合约接收方账户。
>
>   同时，可以借助于出块的速度，设置达到多少块高度某笔金额解冻，实现合约冻结解冻逻辑。

#### 计算合约内容

> 合约内容 = 前缀 1 字节（0xff）+ 操作类型 1 字节（0x02）+ 充值地址 34 字节（whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1）+ 充值总金额 8 字节（10000000000）+ 自由金额 8 字节（500000000）+ 每月冻结金额 8 字节（500000000）

将合约内容转换成16进制字符串

​	前缀（0xff）=> ff

​	操作类型（0x02）=> 02



充值地址（whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1）=> 77686d44344d3851387162457836523567554c626362355a6b656462635244475931

```bash
root@ubuntu:~/wikichain/tmp/node1# echo -n "whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1"|xxd -p
77686d44344d3851387162457836523567554c626362355a6b656462635244475931 
```



充值总金额（10000000000）=> 

利用计算器转成 16 进制为 2540be400，补齐 8 字节后为 00000002540be400，按照内存中逆序后为00e40b5402000000

 

自由金额（500000000）=>

利用计算器转成 16 进制为 1dcd6500，补齐 8 字节后为 000000001dcd6500，按照内存中逆序后为0065cd1d00000000

 

每月冻结金额（500000000）=>

利用计算器转成 16 进制为 1dcd6500，补齐 8 字节后为 000000001dcd6500，按照内存中逆序后为0065cd1d00000000

 

将这些字段组合在一起，形成合约内容：

ff0277686d44344d3851387162457836523567554c626362355a6b65646263524447593100e40b54020000000065cd1d000000000065cd1d00000000

#### 充值

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

#### 查询应用账户信息

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

### 提现

#### 查看当前余额

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1004.99900000
}
```

#### 提现

将自由金额（5个币），提现到地址 whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1

 

合约内容 = 前缀 1 字节（0xff）+ 操作类型 1 字节（0x01）+ 账户类型 1 字节（0x02）+ 提现金额 8 字节（500000000）

 

将合约内容转换成16进制字符串

前缀（0xff）=> ff

操作类型（0x02）=> 01

账户类型（0x02）=> 02

提现金额（500000000）=>

利用计算器转成 16 进制为1dcd6500，补齐 8 字节后为 000000001dcd6500，按照内存中逆序后为0065cd1d00000000

 

将这些字段组合在一起，形成合约内容：

ff01020065cd1d00000000

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. createcontracttx whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 117-1 0 ff01020065cd1d00000000 100000 0
{
    "hash" : "502ed951f0e88f8e25d71e0332c315e837b72c390194cd0d64f2be49c75578a2"
}
```

#### 再次查看当前余额

> 1004.99900000 + 95.00000000 - 0.00100000 = 1099.99800000
>
> **备注：**参数指定提取自由余额 5.00000000，实际上，一次性将所有自由余额 95.00000000 全部提取

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getbalance whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "balance" : 1099.99800000
}
```

### 图示余额变化

![](pic/blockchain/free_values.png)

### 脚本出错处理

​	当应用账户余额为零时，提现操作将会失败，实现信息已 json 格式输出，具体如下所示：

```bash
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. getappaccinfo 117-1 whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1
{
    "mAccUserID" : "77686d44344d3851387162457836523567554c626362355a6b656462635244475931",
    "FreeValues" : 0,
    "vFreezedFund" : [
    ]
}
root@ubuntu:~/wikichain/tmp/node1# ./node1 -datadir=. createcontracttx whmD4M8Q8qbEx6R5gULbcb5ZkedbcRDGY1 117-1 0 ff01020065cd1d00000000 100000 0
error: {"code":-4,"message":"Error:run-script-error:luaL_loadbuffer fail:[string \"line\"]:375: Account balance is 0.\n"}
```

## 以太坊

​	以太坊的目的是基于脚本、竞争币和链上元协议（on-chain meta-protocol）概念进行整合和提高，使得开发者能够创建任意的基于共识的、可扩展的、标准化的、特性完备的、易于开发的和协同的应用。以太坊通过建立终极的抽象的基础层-内置有图灵完备编程语言的区块链-使得任何人都能够创建合约和去中心化应用，并在其中设立他们自由定义的所有权规则、交易方式和状态转换函数。域名币的主体框架只需要两行代码就可以实现，诸如货币和信誉系统等其它协议只需要不到二十行代码就可以实现。智能合约-包含价值而且只有满足某些条件才能打开的加密箱子-也能在我们的平台上创建，并且因为图灵完备性、价值知晓（value-awareness）、区块链知晓（blockchain-awareness）和多状态所增加的力量，而比比特币脚本所能提供的智能合约强大得多。

## Hyperledger Fabric

​	Hyperledger Fabric 是 Hyperledger 中的一个区块链项目。与其他区块链技术类似，Hyperledger Fabric 包含一个账本，使用智能合约并且是一个通过所有参与者管理交易的系统。

​	Hyperledger Fabric 与其他区块链系统最大的不同体现在**私有**和**许可**。与开放无需许可的网络系统允许未知身份的参与者加入网络不同（需要通过工作量证明协议来保证交易有效并维护网络的安全），Hyperledger Fabric 通过**Membership Service Provider(MSP)**来登记所有的成员。

​	Hyperledger Fabric 也提供了多个可拔插选项。账本数据可被存储为多种格式，共识机制可被接入或者断开，同时支持多种不同的 MSP。

​	Hyperledger Fabric 提供了建立 **channel** 的功能，这允许参与者为交易新建一个单独的账本。当网络中的一些参与者是竞争对手时，这个功能变得尤为重要。因为这些参与者并不希望所有的交易信息——比如提供给部分客户的特定价格信息——都对网络中所有参与者公开。只有在同一个 channel 中的参与者，才会拥有该 channel 中的账本，而其他不在此 channel 中的参与者则看不到这个账本。

## 区块链技术

### 定义

​	区块链：**由使用密码学原理使之连接和保证安全的块**所组成的一个不断增长的数据记录列表。每一个区块包含一个前一个区块的密码学哈希值、一个时间戳，和交易数据。

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

### 理论/技术点

#### 图灵完全

​	图灵完全性通常指具有无限存储能力的通用物理机器或编程语言。简单来说，一切可计算的问题都能计算（给定足够的时间和存储），这样的虚拟机或者编程语言就叫图灵完备的。

#### base58

​	用于 bitcoin 中使用的一种独特的编码方式，主要用于产生 bitcoin  的钱包地址。相比 base64，base58 不使用数字"0"，字母大写"O"，字母大写"I"，和字母小写"l"，以及"+"和"/"符号。
设计 base58 主要的目的是：

1. 避免混淆。在某些字体下，数字 0 和字母大写 O，以及字母大写 I 和字母小写 l 会非常相似。
2. 不使用"+"和"/"的原因是非字母或数字的字符串作为帐号较难被接受。
3. 没有标点符号，通常不会被从中间分行。
4. 大部分的软件支持双击选择整个字符串。

​        **base58 与 base64 的差异：**base64 编码中使用直接截取 3 个字符转 4 个字符的方法进行转换，而是采用我们数学上经常使用的进制转换方法——辗转相除法。

### 应用场景

​	区块链属于一种去中心化的记录技术。参与到系统上的节点，可能不属于同一组织，彼此互不信任；区块链数据由所有节点共同维护，每个参与维护节点都能复制获得一份完整记录的拷贝。跟传统的数据库技术相比，其特点应该包括：

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

​	存证业务的流程相当明晰，首先是双方基于电子签名技术，在电子合同上签约，第三方存证平台提供一个服务，将合同文件进行哈希后，将哈希值妥善存储即可。

​	但这里存在一个问题，那就是第三方平台本身的信用。第三方平台出于某种利益，是否会更改合同的哈希值，一旦更改，该合同的有效性就会受到质疑，从而引发纠纷。

​	为了解决这个问题，公证通（Factom）等公司选择将文件的哈希值存入比特币的区块链中，由于比特币区块链的不可更改性，即便是公证通这家存证公司本身都无法篡改其哈希值，从而在根本上保障了合同真伪校验的有效性。

​	但是，使用公有链依然具有局限性，一是公有链的确认速度很慢，二是公有链的交易手续费会越来越高，导致业务成本高企。

​	因此，我建议将联盟链置于用户数据和公有链之间。如下图所示，是保全网的方案，采用了 Factom 的技术，而联盟链公司可以将中间的锚定链替换为自身的联盟链，从而提高用户存证的确认速度，并且多个数据最终做一次哈希，可大大降低比特币网络的交易次数，从而降低成本。

![img](pic/blockchain/deposit.png) 

**联盟链的作用和公有链的作用**

​	最终必然有一个疑问，既然底层最终锚定了公有链，那么联盟链的作用在哪里。我认为联盟链的作用有三个，一是，如果某个机构希望在本地拥有其文件的哈希数据，那么只需要布置一个联盟链的节点即可。二是，联盟链可以大大提高存证的确认速度，同时联盟链未来可以支持更高的存证并发数。三是，即便最终想要切断联盟链和公有链的联系，有一个联盟链在中间层做保障，也是非常方便的一件事。

​	当联盟链中的节点足够多之后，其存证的公信力也将愈发强大，但在联盟链推动的初期，若没有底层公有链的信用加成，前期推动的难度非常大，要花费极多的口舌去进行市场教育，这也是联盟链公司一个不可忽视的机会成本。

**电子合同及合同存证的巨大价值**

​	人类社会之所以得到发展，“契约精神”起到了不可磨灭的作用，但是持续了几千年的纸质“契约”，纸质合同，已经难以跟上这个飞速发展的互联网世界。

​	设想一个人从小到大的成长过程，要接触各种各样的合同：入学有合同、银行开户有合同、买房有合同、买车有合同，说得夸张一些，可谓是“凡事皆契约”，“一切皆合同”。甚至我让同事帮我买一杯奶茶，欠个15块钱，本质上也是一个口头契约。但如果所有的合同都是纸质的，谁又能保存和检索如此多的纸质合同呢？

​	对企业来说更是如此，仅仅是员工的聘用合同，这一类的合同，就需要整个HR部门花费巨大的力气保存和检索，万一丢失纸质合同，又会引发一系列的纷争。所以，这是一个亟待解决的重要问题。

​	电子合同的网上签约、第三方存管、合同真伪查询、一站式的合同模板提供、合同规范性的校验，这些都是一个大大的蓝海市场，切不可错过。

**存证业务的进一步拓展**

​	电子合同仅仅是存证业务中的一种而已，之所以选择从合同的存证切入市场，是因为这个场景确实在现阶段成为了企业和个人的一个痛点。

​	未来，除了合同以外的任何电子证据都可以存储在区块链存证平台中，例如人的身份证明，或者票据、学历证明、工作履历等等。

​	因此，区块链可以成为整个社会信用体系得以构建的底层基础设施。

#### 数据记录

​	比特币的去中心特点和时间戳账本机制，即区块链技术，其潜在运用将大大超越支付领域。许多开发者试图充分发挥交易脚本语言的安全性和可恢复性优势，将其运用于电子公证服务、证券认证和智能合约等领域。很多早期的开发者利用比特币这种能将交易数据放到区块链上的技术进行了很多尝试，例如，为文件记录电子指纹，则任何人都可以通过该机制在特定的日期建立关于文档存在性的证明。

​	运用比特币的区块链技术存储与比特币支付不相关数据的做法是一个有争议的话题。许多开发者认为其有滥用的嫌疑，因而试图予以阻止。另一些开发者则将之视为区块链技术强大功能的有力证明，从而试图给予大力支持。那些反对非支付相关应用的开发者认为这样做将引致“区块链膨胀”，因为所有的区块链节点都将以消耗磁盘存储空间为成本，负担存储此类 数据的任务。

​	更为严重的是，此类交易仅将比特币地址当作自由组合的 20个字节而使用，进而会产生不能用于交易的UTXO。因为比特币地址只是被当作数据使用，并不与私钥相匹配，所以会导致 UTXO 不能被用于交易，因而是一种伪支付行为。因此，这些交易永远不会被花费，所以永远不会从 UTXO 集中删除，并导致 UTXO 数据库的大小永远增加或“膨胀”。

​	在 0.9 版的比特币核心客户端上，通过采用 RETURN 操作符最终实现了妥协。RETURN 允许开发者在交易输出上增加 80 字节的非交易数据。然后，与伪交易型的 UTXO 不同，Return 创造了一种明确的可复查的非交易型输出，此类数据无需存储于 UTXO 集。RETURN 输出被记录在区块链上，它们会消耗磁盘空间，也会导致区块链规模的增加，但 它们不存储在 UTXO 集中，因此也不会使得 UTXO 内存膨胀，更不会以消耗代价高昂的内存为代价使全节点都不堪重负。 RETURN 脚本的样式：

```
  RETURN <data>
```

​	“data”部分被限制为 80 字节，且多以哈希方式呈现，如 32 字节的 SHA256 算法输出。许多应用都在其前面加上前缀以辅助认定。例如，电子公正服务的证明材料采用8个字节的前缀“DOCPROOF”，在十六进制算法中，相应的 ASCII 码为 44 4f 43 50 52 4f 4f 46。

请记住 RETURN 不涉及可用于支付的解锁脚本的特点， RETURN 不能使用其输出中所锁定的资金，因此它也就没有必要记录在蕴含潜在成本的 UTXO 集中，所以 RETURN 实际是没有成本的。

​	RETURN 常为一个金额为 0 的比特币输出， 因为任何与该输出相对应的比特币都会永久消失。假如一笔 RETURN 被作为一笔交易的输入，脚本验证引擎将会阻止验证脚本的执行，将标记交易为无效。如果你碰巧将 RETURN 的输出作为另一笔交易的输入，则该交易是无效的。

**举例**

> [交易 0xb17a027a8f7ae0db4ddbaa58927d0f254e97fce63b7e57e8e50957d3dad2e66e](https://www.blockchain.com/btc/tx/b17a027a8f7ae0db4ddbaa58927d0f254e97fce63b7e57e8e50957d3dad2e66e) 
>
> [交易 0xe89e09ac184e1a175ce748775b3e63686cb1e5fe948365236aac3b3aef3fedd0](https://www.blockchain.com/btc/tx/e89e09ac184e1a175ce748775b3e63686cb1e5fe948365236aac3b3aef3fedd0)

​	如下，两个交易输出脚本只包含数据（十六进制），解码分别对应

 `Yuki will you marry me ? Tetsu.`

 `Yes I will. Yuki.`

![](pic/blockchain/op_return1.png)

![](pic/blockchain/op_return2.png)