this is a simple implementation of a stock management system. the user can add,remove,check,ship products with its description, exprity date and other informations. 

this is the draft for inner logic of implementation

![image](https://github.com/Entscheidbarkeit/StockManagement/assets/119282401/cfc95031-7cf6-4da6-910f-b921bb93f07e)

Date is implemented to receive a user input and output with given format
Status is implemented for a validation of all the instances, depends on the feature of the instance.
Iproduct is an interface that regulate the functionality of all products
Item represents a general products with basic information
Perishable extens the Item and add expriy date and instructions as new features
Menu shows the user interface and receive the user input for the shown functionality
StockMan realized all the shown functionality and is the main entry point of this system
in Utils many repeated used functions are implemented. eg. Interger input and validation. 

the beginning menue looks like :


Aid Management System
Date: 2022/03/31
Data file: No file
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit

user must input an file name to load data. here we use "data.dat" as input
(on no file loaded, the system will prompt the user to input a data name,and the menu will be regenerated and nothing will be done no matter what option is chosen)
> 2

****New/Open Aid Database****
Enter file name: data.dat
6 records loaded!

Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit

then the user can chose different funtionality given. 
by 1 , the user can check all the product information

> 1

****List Items****
 ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry
-----+-------+-------------------------------------+------+------+---------+-----------
   1 | 12113 | Hydrogen peroxide 100ml bottles     |  300 |  300 |    3.99 |*2023/11/11
   2 | 45678 | Sleeping Bags                       |  100 |  200 |   65.66 |
   3 | 56789 | Tents and Blankets and pillows Tent | 2000 | 2000 |   65.66 |
   4 | 44444 | Flash lights                        |  399 |  400 |   65.66 |
   5 | 12345 | Baby Formula                        |  145 |  200 |   33.99 | 2022/12/12
   6 | 11223 | Enfamil A+                          |   38 |   38 |   38.99 |*2022/11/11
-----+-------+-------------------------------------+------+------+---------+-----------
Enter row number to display details or <ENTER> to continue:

by further input of row number, the detail of chose product will be printed
> 2
AMA Item:
45678: Sleeping Bags
Quantity Needed: 200
Quantity Available: 100
Unit Price: $65.66
  
user can also add new product with all the information or delete an product with given sku or instructions
  
futher functionalities act alike or as the name of options.
