This part includes the communication of iPad and linux server. 

server part
The server part is written in python, which used twisted library. It'll get the socket from iOS part and perform the socket communication. Also, it'll get the income data from QT and send it to iPad through socket communication.

	Definition of the Protocol:
		There'll be two different signals come from QT part, one is a indicator of different video streams, which will begin with a header as "video". After getting this signal, the python server will parse the content and set a "video" as the header and send it to the ios part. Another is a indicator of different objects, which will begin with a header as "msg". After getting this signal, the python server will parse the content and set a "image" as the header and send it to the ios part. 

iOS part
The screen consist of 5 view controllers, which are menu view controller, first view controller, second view controller, third view controller. Also there're two library, one is NVGallery which show the pictures of the objects on the screen in an gally view. Another library is RESideMenu, which give the fancy show of menu controller. 

	Menu View Controller
		The main controller which include all the other view controllers. If other view controllers needed to be added, they should be added here.

	First View controller
		For the socket communication with the server and show the image objects from the video streams. When come into this view controller, it'll initialize the network communication. After initialize the network communication, it'll have different event handler to deal with different events. The server will send image indicators or video indicators. The iOS part will get these indicators and get the images and urls from the nodejs server. Then it'll show the content according to different objects.

	Second View Controller
		This is the login view controller, which use the database in nodejs server. It'll need verification from users. Once login, there'll be users' profile showing. And users can change their user profiles and preferences on video streams accordingly. 

	Third View Controller
		This is the register view controller, which use the database in nodejs server. It'll need users' information for registeration. After registered, users can get into their profile to change their profile or preference on video streams. 

 
