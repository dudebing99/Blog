let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

abi =
[{"constant":true,"inputs":[],"name":"minter","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[{"name":"","type":"address"}],"name":"balances","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"receiver","type":"address"},{"name":"amount","type":"uint256"}],"name":"mint","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[{"name":"receiver","type":"address"},{"name":"amount","type":"uint256"}],"name":"send","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"inputs":[],"payable":false,"stateMutability":"nonpayable","type":"constructor"},{"anonymous":false,"inputs":[{"indexed":false,"name":"from","type":"address"},{"indexed":false,"name":"to","type":"address"},{"indexed":false,"name":"amount","type":"uint256"}],"name":"Sent","type":"event"}];

hex =
"0x608060405234801561001057600080fd5b5060008054600160a060020a03191633179055610228806100326000396000f3006080604052600436106100615763ffffffff7c010000000000000000000000000000000000000000000000000000000060003504166307546172811461006657806327e235e31461009757806340c10f19146100ca578063d0679d34146100f0575b600080fd5b34801561007257600080fd5b5061007b610114565b60408051600160a060020a039092168252519081900360200190f35b3480156100a357600080fd5b506100b8600160a060020a0360043516610123565b60408051918252519081900360200190f35b3480156100d657600080fd5b506100ee600160a060020a0360043516602435610135565b005b3480156100fc57600080fd5b506100ee600160a060020a036004351660243561016f565b600054600160a060020a031681565b60016020526000908152604090205481565b600054600160a060020a0316331461014c5761016b565b600160a060020a03821660009081526001602052604090208054820190555b5050565b3360009081526001602052604090205481111561018b5761016b565b33600081815260016020908152604080832080548690039055600160a060020a03861680845292819020805486019055805193845290830191909152818101839052517f3990db2d31862302a685e8086b5755072a6e2b5b780af1ee81ece35ee3cd33459181900360600190a150505600a165627a7a72305820fe58024a89da1f5b69179153bb71e9de59619ce87e0f71226fc39c6786afa63b0029"; 

subcurrencyContract = web3.eth.contract(abi);

subcurrency = subcurrencyContract.new({from:web3.eth.accounts[0], data:hex, gas:3000000});
//console.log(subcurrency);

recpt = web3.eth.getTransactionReceipt(subcurrency.transactionHash);
//console.log(recpt);

contract_ = subcurrencyContract.at(recpt.contractAddress);
//console.log(contract_);


contract_.Sent().watch(function(error, result) {
    if (!error) {
        console.log("\nCoin transfer: " + result.args.amount +
            " coins were sent from " + result.args.from +
            " to " + result.args.to + ".");
        console.log("Sender: " + contract_.balances.call(result.args.from) +
            ", Receiver: " + contract_.balances.call(result.args.to) + "\n");
    }
})

console.log("mint's hash: ", contract_.mint(web3.eth.accounts[0], 666, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("mint's hash ", contract_.send(web3.eth.accounts[3], 99, {from: web3.eth.accounts[0],
gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("receiver's balance: ", contract_.balances.call(web3.eth.accounts[3]));

setTimeout(function() {
    process.exit(0);
}, 5000);