pragma solidity ^0.4.11;
 
contract HelloWorld
{
    address creator;
    string greeting;

    constructor(string _greeting) public
    {
        creator = msg.sender;
        greeting = _greeting;
    }

    function greet() public view returns (string)
    {
        return greeting;
    }

    function setGreeting(string _newgreeting) public
    {
        greeting = _newgreeting;
    }

    // Standard kill() function to recover funds
    function kill() public
    {
        if (msg.sender == creator)
        {
            // kills this contract and sends remaining funds back to creator
            selfdestruct(creator);  
        }
    }
}