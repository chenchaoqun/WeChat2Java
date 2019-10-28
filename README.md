# WeChat2Java
功能目的：截取微信消息并且与Java服务器进行信息交互<br>

C目录中分为WeChatHelper和WeChatRobot，其中Helper通过dll注入的形式<br>
Java服务器用Netty做数据接收，处理后通过SendMessage的静态方法向微信发送数据<br>
如果要修改服务器地址和端口的话，一定要两边都修改，目前Robot监听的端口有两个<br>
分别为发送艾特消息的端口，以及发送好友消息的端口。
