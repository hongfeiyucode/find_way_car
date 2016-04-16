利用红外对管实现小车循迹行驶
加入ucos的计时器systick，加入PWM，加入GPIO输入


本实验未经修改完全可以适用于learn.apk，实验采用郑州产小板，并且未接KEY，

本实验将实现如下功能：
1,通过STM32F4的USART3连接ATK-HC05蓝牙模块,检测并显示蓝牙模块的状态.
2,通过KEY0按键可以开启/关闭定时向ATK-HC05蓝牙模块发送数据(ALIENTEK HC05 xx)测试蓝牙模块的数据发送.
3,可以通过KEY_UP按键设置ATK-HC05蓝牙模块的主从工作模式.
4,可以通过LCD显示ATK-HC05蓝牙模块接收到的数据.
5,可以通过USMART对ATK-HC05蓝牙模块进行AT指令查询和设置.
6,结合手机端蓝牙软件(蓝牙串口助手 v1.97.apk),可以实现手机无线控制开发板(点亮和关闭LED1).

硬件连接:
STM32开发板-->ATK-HC05蓝牙模块
       PB10-->RXD
       PB11-->TXD
        PF6-->KEY
        PC0-->LED
        GND-->GND
    5V/3.3V-->VCC 



注意事项:
1,请确保ATK-HC05蓝牙模块的通信波特率为9600.
2,最好有2个ATK-HC05蓝牙串口模块,一主一从,方便测试.否则就得通过其他设备(必须有蓝牙)同ATK-HC05蓝牙模块进行对接测试.
3，务必短接探索者STM32F4开发板P10的USART3_RX和GBC_TX以及USART3_TX和GBC_RX
4，本例程详细说明，见光盘：9，增值资料\1，ALIENTEK 产品资料\1，ATK-HC05蓝牙串口模块\ATK-HC05蓝牙串口模块使用说明(F4版)_AN1408A.pdf



               	正点原子@ALIENTEK
               	2014-10-25
		广州市星翼电子科技有限公司
                电话：020-38271790
                传真：020-36773971
	       	购买：http://shop62103354.taobao.com
                      http://shop62057469.taobao.com
                公司网站：www.alientek.com
         	技术论坛：www.openedv.com