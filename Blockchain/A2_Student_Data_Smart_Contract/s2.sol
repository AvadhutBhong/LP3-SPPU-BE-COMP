// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

contract StudentRecords {

    // --------- STRUCTURE ----------
    struct Student {
        uint256 id;
        string name;
        uint8 age;
        string course;
    }

    // --------- STORAGE ----------
    Student[] private students;
    uint256 private nextId = 1;            // auto-increment student ID
    mapping(uint256 => uint256) private indexOfStudent;   // mapping (id → index in array)

    // --------- EVENTS (used to observe gas + tx fee in Remix console) ----------
    event StudentAdded(uint256 id, string name);
    event StudentUpdated(uint256 id);
    event StudentDeleted(uint256 id);
    event GasUsed(uint256 indexed gasValue, string action);

    event EtherReceived(address from, uint256 amount);
    event FallbackCalled(address from, uint256 amount, bytes data);

    
    // --------- ADD STUDENT ----------
    function addStudent(string calldata _name, uint8 _age, string calldata _course) external {
        students.push(Student(nextId, _name, _age, _course));
        indexOfStudent[nextId] = students.length - 1;

        emit StudentAdded(nextId, _name);
        emit GasUsed(gasleft(), "Add Student");

        nextId++;
    }

    // --------- VIEW STUDENT ----------
    function getStudent(uint256 _id) public view returns (Student memory) {
        require(_id > 0 && _id < nextId, "Invalid student ID");

        uint256 idx = indexOfStudent[_id];
        return students[idx];
    }

    // --------- UPDATE STUDENT ----------
    function updateStudent(uint256 _id, string calldata _newName, uint8 _newAge, string calldata _newCourse) external {
        require(_id > 0 && _id < nextId, "Invalid student ID");

        uint256 idx = indexOfStudent[_id];
        students[idx].name = _newName;
        students[idx].age = _newAge;
        students[idx].course = _newCourse;

        emit StudentUpdated(_id);
        emit GasUsed(gasleft(), "Update Student");
    }

    // --------- DELETE STUDENT ----------
    function deleteStudent(uint256 _id) external {
        require(_id > 0 && _id < nextId, "Invalid student ID");

        uint256 idxToDelete = indexOfStudent[_id];
        uint256 lastIdx = students.length - 1;

        // Replace delete position with last element (avoids array gap)
        if (idxToDelete != lastIdx) {
            Student memory lastStudent = students[lastIdx];
            students[idxToDelete] = lastStudent;
            indexOfStudent[lastStudent.id] = idxToDelete;
        }

        students.pop();
        delete indexOfStudent[_id];

        emit StudentDeleted(_id);
        emit GasUsed(gasleft(), "Delete Student");
    }

    // --------- VIEW ALL STUDENTS ----------
    function getAllStudents() public view returns (Student[] memory) {
        return students;
    }

    function totalStudents() public view returns (uint256) {
        return students.length;
    }

    // --------- RECEIVE & FALLBACK (used to observe gas on Ether transfer) ----------
    receive() external payable {
        emit EtherReceived(msg.sender, msg.value);
    }

    fallback() external payable {
        emit FallbackCalled(msg.sender, msg.value, msg.data);
    }
}
