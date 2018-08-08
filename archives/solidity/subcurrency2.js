let Web3 = require('web3');
let web3;

if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
} else {
    // set the provider you want from Web3.providers
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}

abi = [{"constant":true,"inputs":[],"name":"minter","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[{"name":"","type":"address"}],"name":"balances","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"receiver","type":"address"},{"name":"amount","type":"uint256"}],"name":"mint","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[],"name":"kill","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"constant":false,"inputs":[{"name":"receiver","type":"address"},{"name":"amount","type":"uint256"}],"name":"send","outputs":[],"payable":false,"stateMutability":"nonpayable","type":"function"},{"inputs":[],"payable":false,"stateMutability":"nonpayable","type":"constructor"},{"anonymous":false,"inputs":[{"indexed":false,"name":"from","type":"address"},{"indexed":false,"name":"to","type":"address"},{"indexed":false,"name":"amount","type":"uint256"}],"name":"Sent","type":"event"}];

hex =
"0x608060405234801561001057600080fd5b5060008054600160a060020a0319163317905561026b806100326000396000f30060806040526004361061006c5763ffffffff7c010000000000000000000000000000000000000000000000000000000060003504166307546172811461007157806327e235e3146100a257806340c10f19146100d557806341c0e1b5146100fb578063d0679d3414610110575b600080fd5b34801561007d57600080fd5b50610086610134565b60408051600160a060020a039092168252519081900360200190f35b3480156100ae57600080fd5b506100c3600160a060020a0360043516610143565b60408051918252519081900360200190f35b3480156100e157600080fd5b506100f9600160a060020a0360043516602435610155565b005b34801561010757600080fd5b506100f961018f565b34801561011c57600080fd5b506100f9600160a060020a03600435166024356101b2565b600054600160a060020a031681565b60016020526000908152604090205481565b600054600160a060020a0316331461016c5761018b565b600160a060020a03821660009081526001602052604090208054820190555b5050565b600054600160a060020a03163314156101b057600054600160a060020a0316ff5b565b336000908152600160205260409020548111156101ce5761018b565b33600081815260016020908152604080832080548690039055600160a060020a03861680845292819020805486019055805193845290830191909152818101839052517f3990db2d31862302a685e8086b5755072a6e2b5b780af1ee81ece35ee3cd33459181900360600190a150505600a165627a7a7230582020c3da8f368ae70ded4cf3bb492856f485bb4740c8cf4edcbee720bd34f227c90029"; 

subcurrencyContract = web3.eth.contract(abi);

// 根据上一个脚本运行结果获取合约地址
contract_ = subcurrencyContract.at('0x6c26a63139497d5fd5f1acbb4a35e0b0798b9fb2');
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

console.log("mint's hash: ", contract_.mint(web3.eth.accounts[0], 666, {from: web3.eth.accounts[0], gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("mint's hash ", contract_.send(web3.eth.accounts[3], 99, {from: web3.eth.accounts[0], gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("receiver's balance: ", contract_.balances.call(web3.eth.accounts[3]));
console.log("kill's hash: ", contract_.kill({from: web3.eth.accounts[0], gas:3000000}));
console.log("minter's balance: ", contract_.balances.call(web3.eth.accounts[0]));
console.log("receiver's balance: ", contract_.balances.call(web3.eth.accounts[3]));

setTimeout(function() {
    process.exit(0);
}, 5000);