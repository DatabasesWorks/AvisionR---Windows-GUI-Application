# AvisionR---Windows-GUI-Application

Graphical user interface application on Windows for local business that interacts with 
3 offices through a server. Application is designed to manage store’s clients, inventory,
and revenue using QT, SQL, and C++.

Database for Clients: Stores Clients' information and their purchases. User is allowed to edit any stored preferences from client. Searching for clients can be done using their First, or Last Name, Phone number, or Account Number. Every clients' purchase has an individual transaction number that is used throughout the program. Program enables clients to store and log Deposits as well as Pay in full for the product. All lens data is saved in another database tied to the clients account number.

Database for Lens: Lens information is all stored in another database and the user can add, edit, and delete a desired lens. Lens are pulled from the database once selected from the New Purchase Screen.

Database for Frames: Frames are stored in a seperate database as well and can be pulled from the New Purchase Screen.

Database for Log: The log stores all transactions and administrative decisions by the users. A timestamp along with the user name and description of the decision is all stored and can be monitored from the Log screen.

Database for Users: Employee information is saved here and clock in/out information can be managed from here. Administrative Privileges can be granted here. Hours of users are rounded to the nearest 30 minutes as requested by Store Owner. Manual Clock out can be accessed here for simplicity but only by an adminstrator.

Database for Settings: include Address for buisness to be used for reciepts. The City, Zip Code, and Area Code are used for otpimization with new clients. Selection of database is managable from here as well. Unique databases are assigned to each location.

Logout/Clockout: Logout will logout of the program but not clock out. The employees hours are still being measured and in order for the employees shift to end, they must clock out manually or have an admin clock out for them.

Login Screen

![alt tag](http://i.imgur.com/peVwED7.png)

Main Control Panel

![alt tag](http://i.imgur.com/5dXDN1C.png)

Sample - New Purchase

![alt tag](http://i.imgur.com/fNCaEeP.png)

Sample - Print

![alt tag](http://i.imgur.com/VlFG6zg.png)
