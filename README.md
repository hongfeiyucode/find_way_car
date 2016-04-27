# STM32 遥控 循迹 寻光 重力感应小车
 
 ---

## 循迹

![enter image description here](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/10%E7%A7%92%E5%BE%AA%E8%BF%B9%E5%B0%8F%E8%BD%A6.gif)

GIF演示

这只是初期程序的效果，考核的时候已经不会在直线上扭来扭去了。但其实有的人的车不调也能到达差不多的效果，但无奈我的两个马达转速差别太大，调节也无法完全走直线。所以必须用程序做到将其完全可控。 

并且程序在检测到需要转弯时两个轮子是一前一后地转动，能够以最大限度的提供动力使车身转向并且还在直线上，当检测到转过的角度到达时车会立即继续向前开动。

 
最终程序源代码：[https://github.com/hongfeiyucode/find_way_car](https://github.com/hongfeiyucode/find_way_car)

## 寻光

![car1](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/car-1.jpg)

这架在上面的是就是寻光传感器，最后考核很是蛋疼，很多人写的程序直接就是转180度然后`car_forward()` 检测到光直接停下，这种当然是最快的，但是因为前面说过的我这小车无法直行最后跑的不是很快。

但是程序的逻辑还是很具有参考价值的：
[https://github.com/hongfeiyucode/find_light_car](https://github.com/hongfeiyucode/find_light_car)

## 循迹与寻光自由切换

这个主要是利用芯片上的一个按钮将其进行程序之间的切换。程序检测一个值，检测这个键是否按下，还有什么时候弹起，来达到两个程序之间切换的功能。

也另外写了一个程序，程序还是很简洁明了的：
[https://github.com/hongfeiyucode/car_find_way_and_light](https://github.com/hongfeiyucode/car_find_way_and_light)


## Android遥控程序

这个是工程量比较大的一个项目，源代码：[https://github.com/hongfeiyucode/Car_remote_control](https://github.com/hongfeiyucode/Car_remote_control)

最后的程序大致界面，基本是重新改写了一遍。后期还加了重力感应这一功能。

![app-1](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/carremcon-1.jpg)

![app-2](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/carremcon-2.jpg)

操作说明：

- 打开程序
- 点击主界面的`打开蓝牙`
- 拖出侧面的侧边栏
- 点击`查找蓝牙设备`
- 匹配小车的蓝牙
- 连接成功后已经开始进入重力感应遥控模式了
- `右下角的按钮`可以切换重力感应与键盘操作模式
- 两种模式各有各的特点，找到自己的喜欢的就好

![app-3](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/carremcon-3.jpg)


## 重力感应模式

![app-4](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/carremcon-4.jpg)

![zlgy](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/%E9%87%8D%E5%8A%9B%E6%84%9F%E5%BA%94%E9%81%A5%E6%8E%A7%E5%B0%8F%E8%BD%A6.gif)

GIF演示

 重力感应遥控说明：

- 将手机树立起来时小车是停止状态 
- 想象手机是一个遥杆
- 往前倾（手机上端远离自己）是向前，往后是后退
- 左右倾斜分别是向左转向右转


---

很多设备调试，程序编写都是自己一个人一行一行一根线一根线调试出来的， 从中体会到了很多酸甜苦辣。其中调试小车让其识别拐弯与平时的轻度弯曲的直线之间的区别是最让人痛苦的，不过小车最后还是跑出了全专业最快的`10秒/圈`的速度。

>PS:此文中的小车的`循迹程序`，`寻光程序`，`Android遥控程序`，`重力感应程序`，`循迹与寻光自由切换程序` 已全部上传至网上。

##  最终效果

小车最终外观

![car2](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/car-2.jpg)

处理器用的是`STM32F4`

![car3](https://github.com/hongfeiyucode/Car_remote_control/blob/master/pic/car-3.jpg)

后面两个轮子为驱动轮，前面一个轮子为从动轮

