# coding-practice
This repository is my personal coding playground where I experiment with algorithms, data structures, and various programming challenges. Feel free to explore the code, provide feedback, or even challenge me with new problems! 🤓💻


1. Design design on the framework, and tools.
    I assumed the application would run on both desktop and mobile operating systems, and choosing the Qt framework aligns with this objective for several reasons. Firstly, Qt is renowned for being a cross-platform development tool, enabling the creation of applications that can seamlessly run on various operating systems, ensuring a wider reach and user accessibility. I have added SQLite db support due to the quick setup and local data storage in desktop applications. Its easier for the prototype stage later we can change to mySQL db.
   But if at all, if we need task management should be a web application like Jira then I would choose Angular or react UI framework with Non-SQL DB and node-js backend server. Mainly the real-time collaboration feature provided by frameworks like Angular or React, coupled with a NoSQL database and Node.js backend, contributes to a more interactive and responsive task management system and provides the collaborative feature.

2. Clearly outline the steps to run your application locally.
   
3. Work Breakdown: Provide a list of work tasks (e.g., like Jira ticket) derived from the product
  1. Create a task management project skeleton 
  2. Add Qt framework-related files and settings
  3. I would start by creating tickets for each UI screen like, all these tickets can be finished by use of dummy data. 
       a. Add User settings screen
       b. Add Task list screen
       c. Add task detail screen
       d. Add task creation screen..
       other more...
     Creating tickets for each screen helps to maintain the UI requirement very well.
  4. Add a Data Model for the Task for the DB support.
  5. Add DB APIS with Unit test support
  6. Backend Design: Provide a list of backend endpoints (e.g., REST APIs) that we would want to

4. implement to support your client's implementation. Note, just provide the endpoint names and
payloads (e.g., GET task <object Task>), no need to implement the backend.

----------- In the case of SQLite DB API, I have implemented those APIs in the code.

----------- REST API in case of NoSQL and web-based application
// TO get All the task
GET /tasks

// TO get the task using taskId
GET /tasks/{taskId}

// To delete the task
DELETE /tasks/{taskId}

//To apply partial modifications to a resource.
PATCH /tasks/{taskId}

// To apply full modification
PUT /tasks/{taskId}

//POST is employed to transmit data to a server to create or update a resource. The data transmitted via POST is stored within the request body of the HTTP request.
POST /tasks/
  
5. Task Management architecture, which I used for this QT application.

<img width="1092" alt="image" src="https://github.com/pgupta212-virus/coding-practice/assets/154770651/96c869d0-6ce6-4f97-b3c7-c3fda623ee0d">
