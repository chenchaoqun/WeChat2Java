package remote.entity;


import org.json.JSONObject;

import java.util.Objects;

/**
 * 用户发来的消息
 * @author 申劭明
 */
public class Message {
    /**
     * 微信ID/群ID
     */
    private String userId;
    /**
     * 消息类型
     */
    private String messageType;
    /**
     * 消息来源(群消息，好友消息)
     */
    private String source;
    /**
     * 消息的发送人
     */
    private String messageSender;
    /**
     * 发送的内容
     */
    private String content;
    /**
     * 是否为转账消息
     */
    private boolean isMoney;

    public Message(String message){
        JSONObject json = new JSONObject(message);
        if (message.contains("content")){
            //截取发送的内容
            this.content = json.get("content").toString();
            if (this.content.contains("@")){
                String[] s = this.content.split(" ");
                if (s.length > 1){
                    this.content = s[1];
                }else if (s.length == 1){
                    this.content = s[0];
                }
            }
        }
        if (message.contains("source")){
            this.source = json.get("source").toString();
        }
        if (message.contains("userId")){
            //截取发送人的Id,可能是好友Id，也可能是群Id
            String userId = json.get("userId").toString();
            if (userId.contains("@chatroom")){
                //如果是群消息,获取发送人的Id
                String messageSender = json.get("messageSender").toString();
                this.messageSender = messageSender.equalsIgnoreCase("NULL") ? null : messageSender;
            }else{
                //意外数据，用日志记录下来
            }
            this.userId = userId;
        }
        if (message.contains("isMoney ")){
            this.isMoney = Boolean.valueOf( json.get("isMoney ").toString());
        }
        if (message.contains("messageType")){
            this.messageType = json.get("messageType").toString();
        }
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getMessageType() {
        return messageType;
    }

    public void setMessageType(String messageType) {
        this.messageType = messageType;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getMessageSender() {
        return messageSender;
    }

    public void setMessageSender(String messageSender) {
        this.messageSender = messageSender;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public boolean isMoney() {
        return isMoney;
    }

    public void setMoney(boolean money) {
        isMoney = money;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Message message = (Message) o;
        return isMoney == message.isMoney &&
                Objects.equals(userId, message.userId) &&
                Objects.equals(messageType, message.messageType) &&
                Objects.equals(source, message.source) &&
                Objects.equals(messageSender, message.messageSender) &&
                Objects.equals(content, message.content);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userId, messageType, source, messageSender, content, isMoney);
    }

    @Override
    public String toString() {
        return "Message{" +
                "userId='" + userId + '\'' +
                ", messageType='" + messageType + '\'' +
                ", source='" + source + '\'' +
                ", messageSender='" + messageSender + '\'' +
                ", content='" + content + '\'' +
                ", isMoney=" + isMoney +
                '}';
    }

    /**
     * @Description : 判断是否为群消息
     *
     * @Return : 是|否
     * @Author : 申劭明
     * @Date : 2019/10/27 10:26
    */
    public boolean isGroupMessage(){
        return this.source.equals("群消息") ;
    }
}
