let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

abi =
[{"constant":false,"inputs":[],"name":"kill","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[{"name":"_newgreeting","type":"string"}],"name":"setGreeting","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":true,"inputs":[],"name":"greet","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"inputs":[{"name":"_greeting","type":"string"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}];

hex =
"0x608060405234801561001057600080fd5b5060405161040038038061040083398101604052805160008054600160a060020a0319163317905501805161004c906001906020840190610053565b50506100ee565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f1061009457805160ff19168380011785556100c1565b828001600101855582156100c1579182015b828111156100c15782518255916020019190600101906100a6565b506100cd9291506100d1565b5090565b6100eb91905b808211156100cd57600081556001016100d7565b90565b610303806100fd6000396000f3006080604052600436106100565763ffffffff7c010000000000000000000000000000000000000000000000000000000060003504166341c0e1b5811461005b578063a413686214610072578063cfae3217146100cb575b600080fd5b34801561006757600080fd5b50610070610155565b005b34801561007e57600080fd5b506040805160206004803580820135601f81018490048402850184019095528484526100709436949293602493928401919081908401838280828437509497506101929650505050505050565b3480156100d757600080fd5b506100e06101a9565b6040805160208082528351818301528351919283929083019185019080838360005b8381101561011a578181015183820152602001610102565b50505050905090810190601f1680156101475780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b60005473ffffffffffffffffffffffffffffffffffffffff163314156101905760005473ffffffffffffffffffffffffffffffffffffffff16ff5b565b80516101a590600190602084019061023f565b5050565b60018054604080516020601f600260001961010087891615020190951694909404938401819004810282018101909252828152606093909290918301828280156102345780601f1061020957610100808354040283529160200191610234565b820191906000526020600020905b81548152906001019060200180831161021757829003601f168201915b505050505090505b90565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f1061028057805160ff19168380011785556102ad565b828001600101855582156102ad579182015b828111156102ad578251825591602001919060010190610292565b506102b99291506102bd565b5090565b61023c91905b808211156102b957600081556001016102c35600a165627a7a72305820565e009caf97424b1c531eba83ef96d9242a835ead6e7f9fdffd963ef1d6213d0029";

helloworldContract = web3.eth.contract(abi);

helloworld = helloworldContract.new('hello world', {from:web3.eth.accounts[0], data:hex, gas:3000000});
//console.log(helloworld);

recpt = web3.eth.getTransactionReceipt(helloworld.transactionHash);
//console.log(recpt);

contract_ = helloworldContract.at(recpt.contractAddress);
//console.log(contract_);

console.log(contract_.greet.call());

// 调用 setGreeting()，修改问候语
//contract_.setGreeting.sendTransaction('bala bala', {from:web3.eth.accounts[0], gas:3000000})
//console.log(contract_.greet.call());

process.exit(0);