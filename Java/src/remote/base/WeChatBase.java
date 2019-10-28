package remote.base;

import com.sun.istack.internal.NotNull;

import java.util.Objects;

/**
 * 所有微信消息的基类
 * @author 申劭明
 */
public class WeChatBase {
    /**
     * 微信用户的唯一标识Id
     */
    private String userId;

    public String getUserId() {
        return userId;
    }

    public void setUserId(@NotNull String userId) {
        this.userId = userId;
    }

    @Override
    public boolean equals(Object obj) {
        //如果
        if (obj == this){
            return true;
        }
        if (!(obj instanceof WeChatBase)){
            return false;
        }
        return userId.equals(((WeChatBase) obj).userId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(userId);
    }
}
