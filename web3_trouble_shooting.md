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

### [Solana] 连续发送交易导致交易重复（signature 相同）

**参考资料**

- https://forums.solana.com/t/how-solana-validators-catch-duplicated-transactions-without-nonce/5139/5

**问题原因**

Solana 交易结构中不包含以太坊系列通过 `nounce` 变化达到连续发送交易而不会出现 `txid` 重复的问题，在 Solana 中，类似地，在需要短时间内连续发送多笔交易的场景，可以在交易中添加 `recentBlockhash` 来避免交易重复

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

