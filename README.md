# Car_Esp8266

##################################
# From Tran Viet An - 19CE - VKU #
# Contact: tvan.19ce@vku.udn.vn  #
##################################

# AppAndroid_apk
- File apk trong thư mục này là file cài đặt ứng dụng điều khiển xe thông qua Blutooth.
- Ứng dụng chạy trên hệ điều hành Android 8 trở lên.

# Car_ESP8266_Avoid
- Dự án sử dụng các linh kiện: 
  + Mudule ESP8266 NodeMCU.
  + Module điều khiển động cơ L298N.
  + Động cơ Servo SG90.
  + Module cảm biến siêu âm HC-SR04.
  + Khung xe 3 bánh và động cơ DC 5V.
  + Dây cắm.
- Trong thư mục này chứa file code *.ino chạy trong phần mềm Arduino IDE.
- Dự án này sử dụng module ESP8266, nên khi nạp code cho mạch cần chọn đúng Board sử dụng, và Port COM.
- File diagram.JPG là sơ đồ nối dây giữa các linh kiện (được vẽ trên Fritzing).

# Car_ESP8266_BLT
- Dự án sử dụng các linh kiện: 
  + Mudule ESP8266 NodeMCU.
  + Module điều khiển động cơ L298N.
  + Module bluetooth HC05
  + Khung xe 4 bánh và động cơ DC 5V.
  + Dây cắm.
- Trong thư mục này chứa file code *.ino chạy trong phần mềm Arduino IDE.
- Dự án này sử dụng module ESP8266, nên khi nạp code cho mạch cần chọn đúng Board sử dụng, và Port COM.
- File diagram.JPG là sơ đồ nối dây giữa các linh kiện (được vẽ trên Fritzing).

# Servo-1.1.8.zip
- Nếu khi nạp chương trình mà báo lỗi thiếu thư viện Servo thì add thư viện này vào.
- Vào Sketch -> Include Library -> Add .ZIP Labrary...
