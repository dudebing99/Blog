### [eth] only replay-protected (EIP-155) transactions allowed over RPC

**问题原因**

节点程序新版本中启用了 EIP-155 协议，导致向节点提交交易报错

**解决方案**

- 节点添加运行参数允许不安全的旧交易格式

```bash
--rpc.allow-unprotected-txs
```

- 使用新协议规范，交易签名中添加 `chainId` 参数

```javascript
// 旧版本签名 TransactionEncoder.signMessage(rawTransaction, credentials);
TransactionEncoder.signMessage(rawTransaction, chainId, credentials);
```

### [eth/bsc] 由于节点负载均衡策略导致获取的 nonce 重复，进而交易被丢弃

**问题原因**

为了保证业务的连续性，dapp 中会使用节点集群来提交交易。由于节点之间数据同步（pending transactions）时延的客观存在

```java
BigInteger nonce = web3j.ethGetTransactionCount(from, DefaultBlockParameterName.PENDING).send().getTransactionCount();
```

假设，负载均衡使用 RR 策略，当后台服务需要在短时间内连续发送多笔交易（例如空投），连续的两笔交易可能被发送到**两个不同的节点**：

1. 通过 rpc 从 node1 获取 nonce1 并组装交易，然后广播
2. 通过 rpc 从 node2 获取 nonce2 并组装交易，然后广播

实际上，nonce1 和 nonce2 有可能相同，从而导致最终只有一个交易有效，另外一个被丢弃

**解决方案**

- 如果后台服务的 IP 地址固定，负载均衡可使用基于 IP 地址哈希
- 如果只有两个节点，设置一主一备即可

```bash
upstream backend{
	server 192.168.1.1:8485 backup;
	server 192.168.1.1:8486;
}
```

- 自定义请求头，然后负载均衡策略基于自定义请求头去配置

### [Solana] 连续发送交易导致交易重复（signature 相同）

**参考资料**

- https://forums.solana.com/t/how-solana-validators-catch-duplicated-transactions-without-nonce/5139/5

**问题原因**

Solana 交易结构中不包含以太坊系列通过 `nonce` 变化达到连续发送交易而不会出现 `txid` 重复的问题，在 Solana 中，类似地，在需要短时间内连续发送多笔交易的场景，可以在交易中添加 `recentBlockhash` 来避免交易重复

**解决方案**

```javascript
let transaction = new Transaction().add(
  createTransferInstruction(
    from.address,
    to.address,
    feePayer.publicKey,
    new BN(amount),
    [],
    TOKEN_PROGRAM_ID
  )
);
let blockhashObj = await connection.getLatestBlockhash();
console.log("blockhashObj", blockhashObj);
transaction.recentBlockhash = blockhashObj.blockhash;

let signature = await connection.sendTransaction(transaction, [feePayer]);
```

### [quick node/eth] reate a sticky session to one fixed node when making requests

**需求来源**

quick node 提供了一个庞大的节点集群，在特定的场景下，例如，在 BSC 链上要在短时间内连续发送多笔交易，需要保证交易从同一个节点提交，否则可能获取到重复的 `nonce` 进而导致交易被丢弃

**解决方式**

we have the header, `x-session-hash; this` header provides 'stickiness,' so it should query the same node when making requests.

Inject this header with a custom session string (e.g., a GUID) into your requests; this will improve the "stickiness" of your sessions and improve the chances that you will hit the same node over and over. Below is an example using cURL, but the logic is the same for python or JS.

```javascript
curl -X POST \
  $RPC \
  --header 'Content-Type: application/json' \
  --header 'x-session-hash: 79377ed9-ad02-4154-9da3-0a07ff257c94' \
  --data-raw '{
  "method": "eth_blockNumber",
  "params": [],
  "id": 1,
  "jsonrpc": "2.0"
}'
```

### [quick node/eth] a similar output compared to `parity_getBlockReceipts`

**需求来源**

在同步服务中，一般的处理逻辑为：

1. 获取区块中交易
2. 依次获取每笔交易的收据信息，找到与自身应用相关的交易
3. 解析相关交易，入库

上述流程中，第 2 步需要对每一笔交易调用一次 `eth_getTransactionReceipt`，可能导致同步区块的速度跟不上区块增长的速度。当然，我们可以做流程的优化，第 2 步中先判断交易是否跟自身应用相关（例如，from 地址是否是我方应用合约），但问题仍然存在。

```java
public void syncBlockTransaction(int blockHeight) {
		Block block = rpc.getBlockByNumber(blockHeight, true);
		List<TransactionResult> transactionResults = block.getTransactions();

		for (TransactionResult transactionResult : transactionResults) {
			Transaction transaction = (TransactionObject) transactionResult.get();
			String txid = transaction.getHash();

			String to = transaction.getTo();
			if (StringUtils.isEmpty(to)) {
				continue;
			}

      // 跟应用无关，直接跳过
			if (!to.equalsIgnoreCase(configCache.getConfValue(ConfigCache.CONTRACT_BFC)) {
				continue;
			}

      // 交易失败，直接跳过
			TransactionReceipt transactionReceipt = rpc.getTransactionReceipt(txid);
			boolean isValid = "0x1".equalsIgnoreCase(transactionReceipt.getStatus());

			if (!isValid) {
				continue;
			}
			if (to.equalsIgnoreCase(configCache.getConfValue(ConfigCache.CONTRACT_BFC))) {
        // 解析交易
				handleTokenTransfer(block, transaction, transactionReceipt);
			}
}
```

在以太坊 parity 客户端中，有一次性获取区块中所有交易收据的 rpc：`parity_getBlockReceipts`，quick node 提供了一个类似的 rpc：`eth_getBlockReceipts`

**解决方式**

There is the method called `eth_getBlockReceipts` that you can use, this should give you a similar output compared to `parity_getBlockReceipts`

```bash
curl -X POST \
  'RPC_HERE' \
  --header 'Content-Type: application/json' \
  --data-raw '{
  "id": 1,
  "jsonrpc": "2.0",
  "params": [
    "latest"
  ],
  "method": "eth_getBlockReceipts"
}'
```

