# MVM_Medical_Vending_Machine
Source code for PIC and ESP boards in smart pharmacy machine
The software of the machine consists of three main components:
1- ESP Wi-Fi module                      2-PIC microcontroller                         3- web app server (Wasn't my task).

- The web application is supposed to receive client orders and send them to a local server
- ESP accesses the server to check for needed orders to serve.
- Orders are coded into a form that is known only for the two pairs for security purposes.
- PIC reads from the ESP the needed number of items to deliver, using UART protocol, for the customer. 
- Then, lead the actuators. Besides that, it gets some readings from sensors to make the right decisions. Like temperature using NTC sensor. PIR is used to indicate customer presence. 
----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------
/** ESP8266**/ 
1.1 How the code works 
1.	The code starts by connecting to WIFI (Local Server). 
2.	The Wi-Fi connection status is checked. 
3.	 HTTP GET request is sent with the domain name with URL path or IP address with path.
4.	We store the data that contains the order details in a string variable.
5.	The data is stored in an array after doing some operations on it.
6.	The array of orders is finally sent to the PIC microcontroller with UART protocol.
----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------
/**PIC**/ // Written from scratch (MPLAB XC8)
1- PIC represents the main brain of the machine that moves its actuators and processes the data to deliver the needed materials. 
2- The software used is built on the main loop software architecture. OS wasn’t needed as the tasks are sequential and no need for concurrent actions.
----------------------------------------------------------------------------------------------------------------------------
Software components: 

•	MCAL 
o	DIO 
o	UART 
o	ADC 
o	External interrupt

•	HAL
o	Stepper controller
o	LCD 

•	APP
o	The main loop app (as illustrated)
----------------------------------------------------------------------------------------------------------------------------
Each software components (say X) have the following files:
-	X_prog.c: contains the function definitions.
-	X_cfg.h: contains the user-defined configuration (ex: UART baud rate, IO config etc, Uart file is attached as a sample)
-	X_int.h: contains the APIs that the driver provides (public functions).
-	X_prvt.h: contains the private functions and variables.
