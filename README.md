# HollowKnight_nju

程序设计实训某开发组使用

# 每个人修改时在这里写好修改了什么和日期，只维护自己的代码，其他人的问题联系他人解决

# 用的C++11标准

#### 2024.9.16 谷羽：

1. 创建了项目

2. 写了Timer类

3. 加入了一些资源文件

4. 随便写了一个主循环

#### 2024.9.19 谷羽：

1. 写了Atlas类（图集类）
2. 优化了Timer类的格式
3. 写了Animation类

#### 2024.9.24 谷羽：

1. 写了二维向量Vector2类
2. 写了Camera类

#### 2024.10.10 张子晗：

1. 施工完毕了player类（暂时）
2. 写了一些knight和hornet类

#### 2024.10.10谷羽：

1. 对Knight类进行了一些更新
2. 对于Timer类，Atlas类，Vector2类，Animation类的重复调用bug进行了修复
3. 添加了resourses.cpp
4. 写了一个资源加载函数

#### 2024.10.11谷羽：

1. 可以显示小骑士的idle动画了（但是会闪，已经修复）
2. 将images文件夹移到了cmakedebug下面，这样可以用相对路径了
3. 将scene类的on_update方法全部加上了delta参数
4. 小骑士可以正确转向了
5. 小骑士可以跑了（但是会跑步过程中闪，已经修复）
6. Player类可以设置初始位置了

#### 2024.10.11胡云迪：

1. 完成了Scene相关类的基本框架
2. 调整了background的图片大小

#### 2024.10.12谷羽

1. 小骑士跑步动作优化，不会不停磕头了
2. 改成了120帧，继续优化小骑士跑步动作
3. 可以跳跃了
4. 现在跳跃长按可以跳得更高

#### 2024.10.12汤子恒

1. 完成了碰撞箱的框架

#### 2024.10.13谷羽

1. 完成了小骑士跳跃动画
1. 优化了落地动画
1. 完成了小骑士正常攻击动画

#### 2024.20.13 汤子恒

1. 完成了黄蜂女的道具类实现（部分）
2. 完成了部分黄蜂女类
3. 增加了素材
4. 完成了黄蜂女类

#### 2024.10.13 张子晗：

1. 对状态转移进行了施工

#### 2024.10.14谷羽

1. 小骑士攻击特效以及判定框位置
1. 使用全新的攻击动画bug修复方法
1. 可以上劈了
1. 小骑士受伤动画以及无敌时间完成

#### 2024.10.14 张子晗：

1. 完成了状态转移以及AI逻辑生成

#### 2024.10.15 汤子恒

1. 真正完成了状态转移以及AI逻辑生成并改错
2. 黄蜂女可以扔剑，召唤刺球，跳，移动，受伤，死亡
3. 修复了黄蜂女的bug
4. 修复了黄蜂女的攻击判定框
5. 修复了黄蜂女的攻击动画
6. 修复了黄蜂女的受伤动画
7. 增加了调试模式，可以操控黄蜂女

#### 2024.10.15 胡云迪：

1. 完成了开始界面背景的绘制
2. 完成了血条

#### 2024.10.15谷羽

1. 完成了下劈，劈地面可以使自己弹起来
2. 优化劈砍动画
3. 修了一堆攻击有关bug

#### 2024.10.15 汤子恒

1. 修复了黄蜂女的bug
2. 修复了黄蜂女的攻击判定框，增加了剑气的判定框
3. 修复了黄蜂女的剑气动画
4. 微调了黄蜂女的状态切换概率，使其更有攻击性

#### 2024.10.16 汤子恒

1. 增加了所有敌人的音效
2. 修改了飞剑的速度
3. 完善了背景音乐的播放