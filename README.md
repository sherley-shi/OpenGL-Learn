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
sudo apt-get install build-dep glfw
sudo apt-get install cmake xorg-dev libglu1-mesa-dev

源码解压，进入目录
mkdir build ; cd build
sudo cmake ../
sudo make
sudo make install

```
## 编译
```bash
//opengl
g++ -o example example.cpp -lGL -lGLU -lglut

//glfw需要链接的库
-lGL  - lGLU  -lglfw3 -lX11 -lXxf86vm  -lXrandr -lpthread -lXi -lXcursor -lXinerama 
```

## 学习资料
>[OpenGL](http://learnopengl-cn.readthedocs.io/zh/latest/)

