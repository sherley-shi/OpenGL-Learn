#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
const GLint WIDTH=800, HEIGHT=600;

//做着色器
const GLchar* veShader="#version 330 core\n"
    "layout (location=0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position=vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragment="#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color=vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\n\0";

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TRANGLE", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    glewInit();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //定义顶点数据
    /*
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    GLuint VBO;
    //顶点缓冲对象, 有一个单独的ID
    //生成一个vbo对象 vertex buffer object
    glGenBuffers(1, &VBO);
    //顶点缓冲对象的类型是GL_ARRAY_BUFFER, 绑定一个缓冲类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    */
    //创建爱着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &veShader, NULL);
    glCompileShader(vertexShader);
    //检测编译是否成功
    GLint success;
    GLchar infolog[512];
    //下面的函数检测编译是否成功
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if( !success ){
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        cout << "ERROR:" << infolog << endl;
    }
    //片段着色器,表示最终的输出颜色
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, NULL);
    glCompileShader(fragmentShader);
    //着色器程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //链接程序也需要检查是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        cout << "program link error";
    }
    //在把着色器对象链接到程序后，这个对象可以删除了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    //因为对缓冲类型操作就是对绑定在上面的缓冲对象操作, 所以先绑定vbo;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //绘制第一个是图元，第二个参数是开始的位置，第三个参数读取的定点的数量.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //接绑操作哟
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
