package tomcat.core;

import io.netty.buffer.ByteBuf;
import io.netty.util.CharsetUtil;
import org.json.JSONObject;


/**
 * @Author: 申劭明
 * @Date: 2019/9/16 17:24
 */
public class Request {
    /**
     * 接收到的用户消息
     */
    private String message;

    public Request(){

    }

    public Request(String message){
        this.message = parse(message);
    }

    public Request(ByteBuf byteBuf){
        this.message = parse(byteBuf.toString(CharsetUtil.UTF_8));
    }

    public String getMessage() {
        return message;
    }

    /**
     * 判断message是否符合JSON格式
     *
     * @author 申劭明
     * @param message 待判断的JSON字符串
     * @return 如果符合则返回该字符串，如果不符合则返回NULL指针
     */
    private String parse(String message) {
        try{
            JSONObject object = new JSONObject(message);
        }catch (Exception e){
            e.printStackTrace();
            return null;
        }
        return message;
    }
}
