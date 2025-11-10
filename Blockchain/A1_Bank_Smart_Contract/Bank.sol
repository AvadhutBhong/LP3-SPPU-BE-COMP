// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.18;

contract MyBank {

    address public customer;      // account owner
    uint256 private accountBalance;

    event MoneyDeposited(address indexed sender, uint256 amount);
    event MoneyWithdrawn(address indexed sender, uint256 amount);

    constructor() {
        customer = msg.sender;    // whoever deploys the contract becomes the owner
        accountBalance = 0;
    }

    modifier onlyCustomer() {
        require(msg.sender == customer, "Access denied: Not account owner");
        _;
    }

    // deposit ETH into smart contract
    function deposit() external payable onlyCustomer {
        require(msg.value > 0, "Amount must be greater than 0");
        accountBalance += msg.value;
        emit MoneyDeposited(msg.sender, msg.value);
    }

    // withdraw ETH from contract to owner's wallet
    function withdraw(uint256 amount) external onlyCustomer {
        require(amount > 0, "Invalid withdraw amount");
        require(amount <= accountBalance, "Insufficient funds");

        accountBalance -= amount;
        payable(customer).transfer(amount);

        emit MoneyWithdrawn(msg.sender, amount);
    }

    // view balance stored in contract
    function showBalance() external view returns (uint256) {
        return accountBalance;
    }
}
