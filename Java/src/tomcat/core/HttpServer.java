package tomcat.core;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;

/**
 * Netty监听微信发来的消息
 *
 * @author 申劭明
 * @date 2019/9/16 17:21
 * @version 1.0
 */
public class HttpServer {
    /**
     * 监听端口
     */
    private static int port = 8080;

    public static void main(String[] args) {
        HttpServer httpServer = new HttpServer();
        httpServer.acceptWait();
    }

    /**
     * @Description : Netty监听数据请求
     * @author : 申劭明
     * @date : 2019/9/17 10:29
     */
    public void acceptWait() {
        //监听请求
        EventLoopGroup listenGroup = new NioEventLoopGroup();
        //请求处理
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        ServerBootstrap bootstrap = new ServerBootstrap();

        //绑定监听请求和处理请求的group
        bootstrap.group(listenGroup, workerGroup)
                .channel(NioServerSocketChannel.class)
                .childHandler(new ChannelInitializer<SocketChannel>() {
                    @Override
                    protected void initChannel(SocketChannel socketChannel) throws Exception {
                        socketChannel.pipeline().addLast(new RequestHandler());
                    }
                });
        ChannelFuture future = null;
        try {
            future = bootstrap.bind(port).sync();
            future.channel().closeFuture().sync();

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            listenGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }
}