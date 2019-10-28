package tomcat.core;

import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import remote.entity.Message;
import remote.message.SendMessage;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

/**
 * 处理微信接收的消息
  @Author: 申劭明
 * @Date: 2019/9/17 17:45
 */
public class RequestHandler extends SimpleChannelInboundHandler {

    public RequestHandler(){
    }
    @Override
    protected void messageReceived(ChannelHandlerContext channelHandlerContext, Object o) {
        //接收数据
        Request request = new Request((ByteBuf) o);
        String message = request.getMessage();

        if (message.contains("content")){
            Message answer = new Message(message);
            System.out.println(answer);
            if(answer.isGroupMessage()){
                //如果是群消息
                try {
                    SendMessage.atSomeOne(answer.getUserId(), answer.getMessageSender(),
                            "不知道nickName", answer.getContent());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }else {
                //好友消息
                try {
                    SendMessage.sendMessage2Friend(answer.getUserId(),answer.getContent());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        channelHandlerContext.close();
    }
}