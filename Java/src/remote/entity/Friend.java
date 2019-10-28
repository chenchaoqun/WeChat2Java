package remote.entity;

import org.json.JSONObject;
import remote.base.WeChatBase;

/**
 * 获取好友列表时的类
 * @author 申劭明
 */
public class Friend extends WeChatBase {
    /**
     * 昵称
     */
    private String nickName;

    /**
     * 微信号
     */
    private String userNumber;

    /**
     * 备注
     */
    private String userRemark;

    public Friend(String message){
        JSONObject jsonObject = new JSONObject(message);
        this.nickName = jsonObject.get("nickName").toString();
        this.userNumber = jsonObject.get("userNumber").toString();
        this.userRemark = jsonObject.get("userRemark").toString();
    }

    public String getUserNickName() {
        return nickName;
    }

    public void setUserNickName(String userNickName) {
        this.nickName = userNickName;
    }

    public String getUserNumber() {
        return userNumber;
    }

    public void setUserNumber(String userNumber) {
        this.userNumber = userNumber;
    }

    public String getUserRemark() {
        return userRemark;
    }

    public void setUserRemark(String userRemark) {
        this.userRemark = userRemark;
    }
}
