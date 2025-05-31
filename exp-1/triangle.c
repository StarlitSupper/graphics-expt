#include <glut.h>

// 函数声明
void renderScene(void);
void SetupRC(void);
void changeSize(int w, int h);
void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

// 全局变量

// 三角形中心位置
GLfloat x = 0.0f;
GLfloat y = 0.0f;

// 每次移动步长
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// 窗口尺寸
GLfloat windowWidth;
GLfloat windowHeight;

// 当前颜色（初始为红色）
GLfloat red = 1.0f;
GLfloat green = 0.0f;
GLfloat blue = 0.0f;

// 速度因子
GLfloat speedFactor = 1.0f;

// 主函数
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Triangle");

    // 注册回调函数
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutTimerFunc(23, TimerFunction, 1);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    SetupRC();
    glutMainLoop();

    return 0;
}

// 函数实现

// 渲染函数
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + 25, y - 50);
    glVertex2f(x - 25, y - 50);
    glEnd();

    glutSwapBuffers();
}

// 初始化背景颜色
void SetupRC(void) {
    glClearColor(0.9f, 0.9f, 0.9f, 0.9f); // 灰白色背景
}

// 窗口尺寸变化
void changeSize(int w, int h) {
    GLfloat aspectRatio;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
    }
    else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
    }

    glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// 定时器函数，控制自动移动和反弹
void TimerFunction(int value) {
    // 移动三角形
    x += xstep * speedFactor;
    y += ystep * speedFactor;

    // 触碰左右边界时反弹
    if (x + 25 > windowWidth) {
        x = windowWidth - 25;
        xstep = -xstep;
    }
    else if (x - 25 < -windowWidth) {
        x = -windowWidth + 25;
        xstep = -xstep;
    }

    // 触碰上下边界时反弹
    if (y > windowHeight) {
        y = windowHeight;
        ystep = -ystep;
    }
    else if (y - 50 < -windowHeight) {
        y = -windowHeight + 50;
        ystep = -ystep;
    }

    glutPostRedisplay();
    glutTimerFunc(23, TimerFunction, 1);
}

// 普通按键控制颜色
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        red = 1.0f; green = 0.0f; blue = 0.0f;
        break;
    case 'g':
        red = 0.0f; green = 1.0f; blue = 0.0f;
        break;
    case 'b':
        red = 0.0f; green = 0.0f; blue = 1.0f;
        break;
    case 'c': // 按照红、绿、蓝的顺序循环切换颜色
        if (red == 1.0f) {
            red = 0.0f; green = 1.0f; blue = 0.0f;
        }
        else if (green == 1.0f) {
            red = 0.0f; green = 0.0f; blue = 1.0f;
        }
        else {
            red = 1.0f; green = 0.0f; blue = 0.0f;
        }
        break;
    }
}

// 方向键控制速度
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:   // 加速
        speedFactor += 0.1f;
        break;
    case GLUT_KEY_DOWN: // 减速
        if (speedFactor > 0.2f)
            speedFactor -= 0.1f;
        break;
    }
}
