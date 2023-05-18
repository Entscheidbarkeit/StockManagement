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


![image](https://github.com/Entscheidbarkeit/StockManagement/assets/119282401/ef06341c-a6db-43a9-b5f4-09741ec2558e)


user must input an file name to load data. here we use "data.dat" as input
(on no file loaded, the system will prompt the user to input a data name,and the menu will be regenerated and nothing will be done no matter what option is chosen)


![image](https://github.com/Entscheidbarkeit/StockManagement/assets/119282401/08b778df-5fc3-47a9-b528-77fdf6f677eb)


then the user can chose different funtionality given. 
by 1 , the user can check all the product information

![image](https://github.com/Entscheidbarkeit/StockManagement/assets/119282401/30ec88b2-5c32-4b6e-a071-cd2960549a52)

by further input of row number, the detail of chose product will be printed

![image](https://github.com/Entscheidbarkeit/StockManagement/assets/119282401/64f76a33-7ee5-416b-9442-e5d9daea38b9)
  
user can also add new product with all the information or delete an product with given sku or instructions
  
futher functionalities act alike or as the name of options.
