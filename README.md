# Library_zh
代码注释中文翻译

一些库和SDK的头文件注释中文版

对于英语不太好的朋友，用一些标准库或者SDK开发程序时，由于注释全是英文，对初学者不友好，看不懂函数到底是干嘛的，要传那些参数，
只能一个函数定位到头文件，然后复制注释，到翻译网站或者用翻译app翻译后才能看懂，费时费力。

本人上传了一些SDK或者库文件的头文件中文注释版本，使用后可VS Code鼠标悬停即可查看中文注释。

使用方法：替换源文件（注意备份，以防万一），找到你的源文件，然后下载相应源文件，替换即可。


最终效果
<p align="center">
  <img src="https://raw.githubusercontent.com/DYXX-X/Library_zh/master/Demo_Picture/gpio_zh.png">
</p>


目前上传了ESP32 IDF API 头文件中文注释。
下一步计划上传  开源轻量级显示框架LVGL的中文版本。



    ESP32        
        源文件来源：platformio IDE 
        IDF版本：4.4.2
        （来源和版本号不对，请酌情使用）
    使用方法
        ESP32的替换路径 等于 ESP32IDF 路径下components文件夹，存储库中ESP32_API_zh文件夹即components文件夹，
        components文件夹内几乎所有头文件 .h 类型，存储库中ESP32_API_zh文件夹都有，对应查找即可！
        但是推荐用VS Code开发的朋友，鼠标直接右击函数，转到声明，看文件名称和路径，然后再到存储库相应路径打开相同文件，直接复制全部粘贴。
        重要提示，备份源文件，备份源文件，备份源文件，备份源文件。  




文件内容由机器翻译，不可能绝对正确。因此本存储库最好用于学习用途，以防未知问题。
如遇见错误文件，请勿使用。
