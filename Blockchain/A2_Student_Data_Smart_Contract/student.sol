// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.18;

contract StudentRecord {

    struct Student {
        uint256 id;
        string name;
        uint8 age;
        string course;
    }

    Student[] public studentList;
    uint256 public nextId = 1;

    event StudentAdded(uint256 id, string name);
    event EtherReceived(address sender, uint amount);
    event FallbackCalled(address sender, uint amount);

    function addStudent(string memory _name, uint8 _age, string memory _course) public {
        studentList.push(Student(nextId, _name, _age, _course));
        emit StudentAdded(nextId, _name);
        nextId++;
    }

    function getStudent(uint256 index) public view returns (uint256, string memory, uint8, string memory) {
        require(index < studentList.length, "Invalid index");
        Student memory s = studentList[index];
        return (s.id, s.name, s.age, s.course);
    }

    function totalStudents() public view returns (uint256) {
        return studentList.length;
    }

    receive() external payable {
        emit EtherReceived(msg.sender, msg.value);
    }

    fallback() external payable {
        emit FallbackCalled(msg.sender, msg.value);
    }
}
