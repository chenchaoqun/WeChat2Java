package remote.message;

import io.netty.util.CharsetUtil;
import org.json.JSONObject;

import java.io.IOException;
import java.net.Socket;

/**
 * 通过socket发送消息到微信上
 * @author 申劭明
 * @version 1.0
 */
public class SendMessage {
    /**
     * 接收的Ip地址
     */
    private static final String IP_ADDRESS = "127.0.0.1";
    /**
     * 接收群消息的端口
     */
    private static final int GROUP_PORT = 8090;

    /**
     * 接收个人消息的端口
     */
    private static final int PERSONAL_PORT = 8089;

    /**
     * 发送消息到朋友窗口
     *
     * @param userId 好友的微信Id
     * @param message 要发送的消息
     * @author 申劭明
     */
    public static void sendMessage2Friend(String userId, String message) throws IOException {
        JSONObject json = new JSONObject();
        json.put("userId",userId);
        json.put("message",message);
        Socket socket = new Socket(IP_ADDRESS, PERSONAL_PORT);
        socket.getOutputStream().write(json.toString().getBytes(CharsetUtil.UTF_8));
        socket.close();
    }

    /**
     * 发送艾特消息
     *
     * @param chatRoomId 聊天室(群)的Id
     * @param nickName 被艾特对象的微信名称
     * @param userId 被艾特用户的微信Id
     * @param message 要发送的信息
     * @author 申劭明
     */
    public static void atSomeOne(String chatRoomId, String userId, String nickName, String message) throws IOException {
        JSONObject json = new JSONObject();
        json.put("chatRoomId",chatRoomId);
        json.put("userId",userId);
        json.put("nickName",nickName + " ");
        json.put("message",message);
        Socket socket = new Socket(IP_ADDRESS, GROUP_PORT);
        socket.getOutputStream().write(json.toString().getBytes(CharsetUtil.UTF_8));
        socket.close();
    }

    public static void main(String[] args) {
        try {
//            atSomeOne("16580965355@chatroom","wxid_it9ii3syhui122","雪港 ","测试数据\n测试数据\n测试数据\n");
            sendMessage2Friend("wxid_it9ii3syhui122","好的");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
