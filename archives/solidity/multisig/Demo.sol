
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