# 截取微信消息以及监听Java服务器
WeChatHelper和WeChatRobot由鬼手大佬提供，他的GitHub开源地址为:<br>
<a href="https://github.com/TonyChen56/WeChatRobot">https://github.com/TonyChen56/WeChatRobot</a><br>
微信版本限制为2.6.8.52，VS编译环境限制为Win32。<br>

目录中分为WeChatHelper和WeChatRobot，其中Helper负责微信消息的HOOK以及调用call发送数据<br>
Robot则作为一个中央管理平台，能够在平台上进行聊天记录，群成员查看，艾特消息等操作<br>
在Helper中，截取数据后，向Robot发送数据的同时也通过Socket向Java发送数据<br>
C++中采用CJson用于JSON数据转换.
