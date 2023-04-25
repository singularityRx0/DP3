# DP3
- Allow residents to generate a QR code for their visitors.
- Residents must first register their account on the App before allowing visitors.
- QR code generated is then saved in MySQL database.
- QR code will expire after 24hours and it is only single use.
- Visitors will show the generated QR code to a ESP32-cam microcontroller to be decoded
- ESP32-cam microcontroller will parse the QR data and serial send it to a esp8266 connected to the API and database to determine validity.

## Use the files avaliable in `AppPrototype`
- Copy paste the `AndroidManifest.xml`, `build.gredle (Module:app)`, and `settings.gradle` into your project directory. They contain the settings and libraries used
- Change database setting in `1_connectDB.php`
- Import `appprototype.sql` for mysql table settings
- Change the `url` in the `.java` files to your ip exp: http://192.0.1.102/a/b where `a` is your php folder name in the hdocs and `b` your php script name
- To find your ipconfig, open command prompt and type ipconfig. Its your ipv4 address

## TASK LIST
- [x] Connect app to server
- [x] Connect MySQL Database to server and app
- [x] API development for app actions
- [x] App Login Module 
- [x] App Register Resident Module
- [x] App Create QR Module
- [ ] Microcontroller QR code/decoder
- [ ] Yay All Finish :tada:

## TOOLS AND LIBRARIES REQUIRED

### TOOLS

| TOOLS | VERSION |
| --- | --- |
| [XAMPP](https://www.apachefriends.org/download.html) | 8.2.4 |
| [Android Studio](https://developer.android.com/studio) | Electric Eel 2022.1.1 |
| [Visual Studio Code](https://code.visualstudio.com/download) | 1.77.2|

### LIBRARIES
- [QRGenerator](https://github.com/androidmads/QRGenerator)
- [Google Volley Android](https://www.codeseasy.com/google-volley-android/)

**Android 8.0 Oreo is the app OS version**

## SETTING UP XAMPP
- As per instructions do not save XAMPP folder in the `C:\progranfiles` local drive. If possible save it in its own directory.
- After installing make a shortcut of XAMPP on the desktop. Set the shortcut permission to always **admin**
- Save your PHP scripts in the **hdocs** folder in your xampp directory
- Useful links to help: [link1](https://people.utm.my/shaharil/access-pc-localhost-xampp-server-from-mobile/), [link2](https://www.austincc.edu/rmartin6/coursecontent/inew2338/07-XAMPPSetup.pdf), [link3](https://www.simplilearn.com/tutorials/php-tutorial/php-using-xampp#:~:text=Before%20running%20a%20PHP%20script,web%20pages%20will%20be%20stored.)

## WHAT IT LOOKS LIKE NOW
### LOGIN PAGE
<img align="left" src="https://user-images.githubusercontent.com/94662590/234260879-3d4d29e5-9ba3-4745-8250-fbdbf2cf89ad.png" width=20% height=20%>

<img align="center" src="https://user-images.githubusercontent.com/94662590/234262954-85307232-c79b-428f-8ed1-e5059548c5e7.png" width=20% height=20%>

### MAIN MENU

<img src="https://user-images.githubusercontent.com/94662590/234264574-786a394e-5fce-4852-a290-98192cf79626.png" width=20% height=20%>


### GENERATE QR CODE
<img align="left" src="https://user-images.githubusercontent.com/94662590/234264766-c51c0901-d3c5-4811-aefc-fc1a1f8e4f7b.png" width=20% height=20%>
<img align="center" src="https://user-images.githubusercontent.com/94662590/234265002-fe10e084-3810-4099-a95d-89dd4ffdf0dc.png" width=20% height=20%>
<img align="right" src="https://user-images.githubusercontent.com/94662590/234265412-4eb10fe7-a227-431e-a3aa-e0da91f26f45.png" width=20% height=20%>
