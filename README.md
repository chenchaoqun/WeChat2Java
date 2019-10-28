# WeChat2Java
功能目的：截取微信消息并且与Java服务器进行信息交互<br>

C目录中分为WeChatHelper和WeChatRobot，其中Helper通过dll注入的形式<br>
Java服务器用Netty做数据接收，处理后通过SendMessage的静态方法向微信发送数据<br>
如果要修改服务器地址和端口的话，一定要两边都修改，目前Robot监听的端口有两个<br>
分别为发送艾特消息的端口，以及发送好友消息的端口。<br>
目前有以下的问题:
<ul>
	<li>1.Helper丢失消息（高并发情况下）</li>
	<li>2.Robot调用Helper发送消息失败（不明原因）</li>
	<li>3.Helper刚启动时会有乱码问题，过一段时间再发送信息就不会有乱码问题了</li>
	<li>4.Helper运行一段时间后可能会崩溃</li>
	<li>5.微信版本必须是2.6.8.52</li>
	<li>6.文件以及图片还没有做相应的处理</li>
	<li>7.群消息不能获得用户的昵称（nickname）</li>
	<li>8.回复消息的长度问题（C++中消息用数组存储，有长度限制）</li>
</ul>
