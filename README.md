# OpenGL-Learn

## 不学习? 哼

## 想找工作不? 哼

## 还想要媳妇不? 哼

# 进入正题

## OpenGL安装(ubuntu16.04)
```bash
sudo apt-get install build-essential
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglu1-mesa-dev
sudo apt-get install freeglut3-dev
```

## glfw安装(ubuntu16.04)

```bash
首先下载源码
sudo apt-get build-dep glfw
sudo apt-get install cmake xorg-dev libglu1-mesa-dev

源码解压，进入目录
mkdir build ; cd build
sudo cmake ../
sudo make
sudo make install

```
## glew 安装
```bash
sudo apt-cache search glew
将列出来的都安装
```
## 编译
```bash
//opengl
g++ -o example example.cpp -lGL -lGLU -lglut

//glfw, glew需要链接的库
-lGLEW -lglfw3 -lGL -lm -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread
可以将这些编译用的链接库放到文件中，编译时使用: g++ xxx `cat file`
```

## 学习资料
>[OpenGL](http://learnopengl-cn.readthedocs.io/zh/latest/)

