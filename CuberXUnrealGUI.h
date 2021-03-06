#ifndef $CU_STANDARD
#define $CU_STANDARD
#include<iostream>
#include<Windows.h>
#include <thread>
#include <conio.h>
#include <cmath>
#include <mmsystem.h> //导入声音头文件库
#pragma comment(lib,"winmm.lib")//导入声音的链接库
#pragma message("Creating CuberX UnrealGUI")
//关闭开始动画
#define $CU_TURN_OFF_OPENING_ACTION
using namespace std;

//版本
static const string $CU_VERSION = "Beta 0.1.2";

//预声明
namespace cuberx
{
    class MainWindow;
}

//Basic
namespace cuberx {
    class Base;

    //窗口信息
    class WindowInfo {
    public:
        //获取显示句柄
        static HANDLE GetDisplayHandle()
        {
            return GetStdHandle(STD_OUTPUT_HANDLE);
        }
    };
    //窗口设置
    class WindowSetting {
    private:
    public:
        WindowSetting()
        {
            //启动信息显示
#ifndef $CU_TURN_OFF_OPENING_ACTION
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            ColorSetting('F', 'C');
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | (15u + 12u * 16u));
            //设置窗口大小
            WindowArea(120, 32);
            Sleep(5);
            //隐藏光标
            setCursorVisition(false);

            PointJump(10, 0);
            cout
                << "                                                                            ========     ========   " << endl
                << "                         ======              ==                                ====       ====      " << endl
                << "                       ===    ==             ==          =====     == =====      ====   ====        " << endl
                << "                      ===         ==    ==  ========   ==    ===  =====   ==       =======          " << endl
                << "                      ===         ==    ==  ===   ===  ========    ==              =======          " << endl
                << "                       ===    ==  ==    ==  ===   ===  ==      =   ==            ====   ====        " << endl
                << "                         ======    ======    =======     ======     =          ====       ====      " << endl
                << "                                                                            ========     ========   " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    " << endl
                << "                                                                                                    ";
            PointJump(18, 35);
            cout << "========= CuberX UnrealGUI (dev) =========";
            PointJump(31, 0);
            colorOut("VERSION= ", 7, 12);
            colorOut($CU_VERSION, 7, 12);
            PointJump(31, 127);
            Sleep(800);
            system("cls");
            PointJump(0, 0);
            ColorSetting('7', '0');
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | 7u);
            //显示光标
            setCursorVisition(true);
#endif
            //设置窗口大小
            WindowArea(128, 32);
            Sleep(5);
        }
        //窗口大小
        static int WindowArea(short w, short h, bool ifcls = false)
        {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD size  = {w, h};
            SetConsoleScreenBufferSize(hOut, size);
            SMALL_RECT rc = {0, 0, static_cast<SHORT>(w - 1), static_cast<SHORT>(h - 1)};
            SetConsoleWindowInfo(hOut, 1, &rc);
            if(ifcls == 1)
                system("cls");
            return 0;
        }
        //锁定窗口大小
        static int LockWindow()
        {
            HWND hWnd = GetConsoleWindow();//获得cmd窗口句柄
            RECT rc;
            GetWindowRect(hWnd, &rc);//获得cmd窗口对应矩形
            //改变cmd窗口风格
            SetWindowLongPtr(hWnd, GWL_STYLE, (unsigned)GetWindowLong(hWnd, GWL_STYLE) & ~(unsigned)WS_THICKFRAME & ~(unsigned)WS_MAXIMIZEBOX & ~(unsigned)WS_MINIMIZEBOX);
            //因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
            SetWindowPos(hWnd, nullptr, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 0);
            return 0;
        }
        //设置全局显示颜色
        static int ColorSetting(char FontsColor = '7', char WindowColor = '0')
        {
            char SendStr[] = "color xx";
            char *p_ch     = SendStr + 6;
            *p_ch          = WindowColor;
            *(++p_ch)      = FontsColor;
            system(SendStr);
            return 0;
        }
        //光标跳转
        static void PointJump(SHORT pawnH, SHORT pawnW, HANDLE handle = WindowInfo::GetDisplayHandle())
        {
            COORD PointPawn;
            PointPawn.X = pawnW;//宽坐标
            PointPawn.Y = pawnH;//高坐标
            SetConsoleCursorPosition(handle, {static_cast<SHORT>(pawnW), static_cast<SHORT>(pawnH)});
        }

        /*彩色输出
        0 = 黑色 8 = 灰色
        1 = 蓝色 9 = 淡蓝色
        2 = 绿色 10 = 淡绿色
        3 = 浅蓝色 11 = 淡浅绿色
        4 = 红色 12 = 淡红色
        5 = 紫色 13 = 淡紫色
        6 = 黄色 14 = 淡黄色
        7 = 白色 15 = 亮白色
        https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
        */
        static void colorOut(const string &str, int FontsColorInt, int WindowColorInt)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | ((unsigned)FontsColorInt + (unsigned)WindowColorInt * 16u));
            cout << str;
            SetConsoleTextAttribute(handle, (unsigned)FOREGROUND_INTENSITY | 7u);
        }

        //显示/隐藏光标
        static void setCursorVisition(bool visible)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO CursorInfo;
            GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
            CursorInfo.bVisible = visible;            //隐藏控制台光标
            SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
        }
    };
    static WindowSetting winS;
    //可以变量设置大小的数组（内存安全需注意）
    template<class T>
            class SuperArray
                    {
                    private:
                        T** mem;
                        int HEIGHT;
                        int WIDTH;
                        bool ifON;
                    public:
                        SuperArray()
                        {
                            HEIGHT = 0;
                            WIDTH = 0;
                            ifON = false;
                        }
                        SuperArray(int height, int width)
                        {
                            HEIGHT = height;
                            WIDTH = width;
                            ifON = true;
                            mem = new T * [HEIGHT];
                            //数组mem[HEIDHT][WIDTH];
                            for (int i = 0; i < HEIGHT; i++)
                            {
                                mem[i] = new T[WIDTH];
                            }
                        }
                        void reset(int newHeight, int newWidth)
                        {
                            if (ifON == 1)
                            {
                                for (int i = 0; i < HEIGHT; i++)
                                {
                                    delete[] mem[i];
                                    mem[i] = 0;
                                }
                                delete[] mem;
                                mem = 0;
                            }
                            HEIGHT = newHeight;
                            WIDTH = newWidth;
                            ifON = true;
                            mem = new T * [HEIGHT];
                            //数组mem[HEIGHT][WIDTH];
                            for (int i = 0; i < HEIGHT; i++)
                            {
                                mem[i] = new T[WIDTH];
                            }
                        }
                        ~SuperArray()
                        {
                            for (int i = 0; i < HEIGHT; i++)
                            {
                                delete[] mem[i];
                                mem[i] = 0;
                            }
                            delete[] mem;
                            mem = 0;
                        }

                        T* operator[](int a)
                        {
                            if (a < HEIGHT)
                            {
                                return mem[a];
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    };
    //位置信息
    struct Coordinate {
        short width  = 0;
        short height = 0;
        short &x     = width;
        short &y     = height;
        Coordinate(short x, short y)
        {
            width  = x;
            height = y;
        }
        Coordinate() = default;
    };
    /* 色彩信息
        0 = 黑色 8 = 灰色
        1 = 蓝色 9 = 淡蓝色
        2 = 绿色 10 = 淡绿色
        3 = 浅绿色 11 = 淡浅绿色
        4 = 红色 12 = 淡红色
        5 = 紫色 13 = 淡紫色
        6 = 黄色 14 = 淡黄色
        7 = 白色 15 = 亮白色
        https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
    */
    struct ColorInfo{
        //此处char是为了节省内存
        char backGround = 0;
        char font = 7;
    };
    //一个纯虚函数的包装
    class CUFunction
    {
    public:
        //注意:表示Base对象的指针是this_base而不是this
        virtual void func(Base* this_base) = 0;
    };
    //任务信息
    class CUTask
            {
            private:
                unsigned short index;//序号
                unsigned int tag;//标签
                bool enable;//是否启用
                void(*runFunc)(cuberx::Base*);//运行接口函数
                cuberx::Base* RunClass;//运行接口对象
                DWORD CountDownTick;//剩余时刻
            public:
                CUTask()
                {
                    index = 0;
                    tag = 0;
                    runFunc = nullptr;
                    CountDownTick = 0;
                    RunClass = nullptr;
                    enable = false;
                }


                void setCountDownTick(DWORD newCountDownTick)
                {
                    CountDownTick = newCountDownTick;
                }
                DWORD getCountDownTick() const
                {
                    return CountDownTick;
                }
                void setIndex(unsigned short newIndex)
                {
                    this->index = newIndex;
                }
                unsigned short getIndex() const
                {
                    return index;
                }
                void setTag(unsigned int newTag)
                {
                    tag = newTag;
                }
                unsigned int getTag() const
                {
                    return tag;
                }
                void setRunFunc(void(*newRunFunc)(cuberx::Base*))
                {
                    runFunc = newRunFunc;
                }
                bool getEnable() const
                {
                    return enable;
                }
                void setEnable(bool ifEnable)
                {
                    enable = ifEnable;
                }
                //获取运行函数前者为方法本身，(cuberx::Base*)为返回的函数的参数
                void (*getRunFunc())(cuberx::Base*)
                {
                    return runFunc;
                }
                void setRunClass(cuberx::Base* newRunClass)
                {
                    RunClass = newRunClass;
                }
                //获取目标对象的指针
                cuberx::Base* getRunClass()
                {
                    return RunClass;
                }
                //将剩余时刻减少1
                void countDown()
                {
                    CountDownTick -= 1;
                }

                //运行该任务
                void run()
                {
                    //运行绑定的函数
                    runFunc(RunClass);
                }
                //清空任务
                int reset()
                {
                    index = 0;
                    tag = 0;
                    runFunc = nullptr;
                    RunClass = nullptr;
                    CountDownTick = 0;
                    setEnable(false);
                    return 0;
                }
                //设置任务
                int set(cuberx::Base* NewRunClass, int NewTag, void(*NewRun)(cuberx::Base*) = nullptr, DWORD NewCountDownTick = 0, bool ifEnable = true)
                {
                    tag = NewTag;
                    runFunc = NewRun;
                    RunClass = NewRunClass;
                    CountDownTick = NewCountDownTick;
                    enable = ifEnable;
                    return 0;
                }
            };
    //键位信息
    class Key
            {
            public:
                static const int $UP = 72;
                static const int $DOWN = 80;
                static const int $LEFT = 75;
                static const int $RIGHT = 77;
                static const int $SPACE = 32;
                static const int $BACK_SPACE = 8;
                static const int $ESC = 27;
                static const int $ENTER = 13;
                static const int $DELETE = 83;
                static const int $INSERT = 82;
            };
    static Key KEY;
    //字符串工具
    class StringTool
            {
            public:
                static string WCharToString(wchar_t* firstWChar)
                {
                    //表示为单字节时长度
                    int charLength = WideCharToMultiByte(CP_OEMCP, 0, firstWChar, (int)wcslen(firstWChar), nullptr, 0, nullptr, nullptr);
                    char* finalChar = new char[(long long)charLength + (long long)1];
                    //转换
                    WideCharToMultiByte(CP_OEMCP, 0, firstWChar, (int)wcslen(firstWChar), finalChar, charLength, nullptr, nullptr);
                    finalChar[charLength] = '\0';
                    string result = finalChar;
                    delete[] finalChar;
                    return result;
                }
                //注意释放内存
                static wchar_t* StringToWchar(const string& firstString)
                {
                    const char* firstChar = firstString.c_str();
                    //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
                    int WCharLeng = MultiByteToWideChar(CP_OEMCP, 0, firstChar, (int)strlen(firstChar) + 1, nullptr, 0);
                    auto* finalWChar = new wchar_t[WCharLeng];
                    //第二次调用将单字节字符串转换成双字节字符串
                    MultiByteToWideChar(CP_OEMCP, 0, firstChar, (int)strlen(firstChar) + 1, finalWChar, WCharLeng);
                    return finalWChar;
                }
            };
    static StringTool strT;

    //基本类
    class Base
            {
            protected:
                cuberx::Coordinate location;
                cuberx::Coordinate size;
                cuberx::Coordinate offset;
                cuberx::MainWindow* fatherMainWindow;
                string text;
                bool beChosed;
                bool canBeChosed;
                bool visible;
            public:
                Base()
                {
                    text = " ";
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                explicit Base(const string& newText)
                {
                    text = newText;
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                Base(short width, short height, short x, short y)
                {
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                Base(short width, short height)
                {
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                Base(const string& newText, short width, short height, short x, short y)
                {
                    text = newText;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                Base(const string& newText, short width, short height)
                {
                    text = newText;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    visible = true;
                    fatherMainWindow = nullptr;
                }
                virtual void draw(int offsetX, int offsetY)
                {
                
                }
                virtual void whenBeChosed()
                {
                    beChosed = true;
                }
                virtual void whenStopChosed()
                {
                    beChosed = false;
                }
                //一般规定：1表示读取成功，0表示失败
                virtual int keyAction(int newKey)
                {
                    return 0;
                }
                virtual void setText(const string& newText)
                {
                    text = newText;
                }
                virtual string getText()
                {
                    return text;
                }
                virtual bool getVisible()
                {
                    return visible;
                }
                virtual void setVisible(bool ifVisible)
                {
                    visible = ifVisible;
                }
                virtual void setSize(short width, short height)
                {
                    size.width = width;
                    size.height = height;
                }
                virtual Coordinate getSize()
                {
                    return size;
                }
                virtual void setLocation(short x, short y)
                {
                    location.x = x;
                    location.y = y;
                }
                virtual Coordinate getLocation()
                {
                    return location;
                }
                virtual void setCanBeChosed(bool ifCanBeChosed)
                {
                    canBeChosed = ifCanBeChosed;
                }
                virtual bool getCanBeChosed()
                {
                    return canBeChosed;
                }
                virtual void setBeChosed(bool ifBeChosed)
                {
                    beChosed = ifBeChosed;
                    if(ifBeChosed)
                    {
                        whenBeChosed();
                    }
                    else
                    {
                        whenStopChosed();
                    }
                }
                virtual bool getBeChosed()
                {
                    return beChosed;
                }
                //设置所属主窗口信息
                virtual void setFatherMainWindow(cuberx::MainWindow* newFatherMainWindow)
                {
                    fatherMainWindow = newFatherMainWindow;
                }
                //重置所属主窗口信息
                virtual void resetFatherMainWindow()
                {
                    fatherMainWindow = nullptr;
                }
                //获取所属主窗口
                virtual cuberx::MainWindow* getFatherMainWindow()
                {
                    return fatherMainWindow;
                }
                //设置绘制偏移量
                virtual void setOffset(short offsetX, short offsetY)
                {
                    offset.x = offsetX;
                    offset.y = offsetY;
                }
                //获取绘制偏移量
                virtual cuberx::Coordinate getOffset()
                {
                    return offset;
                }
            };

    //容器类
    class Container : public cuberx::Base
            {
            protected:
                int nowChosingObject;

            public:
                Container()
                {
                    text = " ";
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                explicit Container(const string& newText)
                {
                    text = newText;
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                Container(short width, short height, short x, short y)
                {
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                Container(short width, short height)
                {
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                Container(const string& newText, short width, short height, short x, short y)
                {
                    text = newText;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                Container(const string& newText, short width, short height)
                {
                    text = newText;
                    size.width = width;
                    size.height = height;
                    canBeChosed = false;
                    beChosed = false;
                    nowChosingObject = 0;
                }
                virtual int add(cuberx::Base* newObject)
                {
                    return 0;
                }
                virtual int add(cuberx::Base& newObject)
                {
                    return 0;
                }
                virtual void remove(cuberx::Base* newObject)
                {

                }
                virtual void remove(cuberx::Base& newObject)
                {

                }
                virtual int getNowChosingObject()
                {
                    return nowChosingObject;
                }
                //最好重写
                virtual void setNowChosingObject(int newChosingObject)
                {
                    nowChosingObject = newChosingObject;
                }
            };

    //组件类
    class Module : public cuberx::Base {
            public:
                Module() = default;
            };
}

//MainWindow
#define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT 256
#define $CU_MAINWINDOW_TOTAL_TASKS_COUNT 256
namespace cuberx {

    class MainWindow : public cuberx::Container
            {
            protected:
                string title;//窗口标题(反映在控制台上)
                bool enable;//是否启用
                bool useTickListener;//是否使用帧率管理器
                bool checkKey;//是否检测键位
                ULONGLONG lastTestTickTime;//上一次检测(运行)帧时间
                ULONGLONG timePerTick;//帧率时间(0为无限制 单位为毫秒)
                int tickListenerMode;//检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行)
                int nowChosingObject;//目前选择的CU组件(-1表示无)
                cuberx::Base* objects[$CU_MAINWINDOW_TOTAL_OBJECTS_COUNT]{};
                cuberx::CUTask tasks[$CU_MAINWINDOW_TOTAL_TASKS_COUNT];
                thread* tickListenerThread;
                bool threadEnable;
            public:
                int returnInt;
                MainWindow()
                {
                    returnInt = 0;
                    setSize(0, 0);
                    title = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
                    enable = false;
                    for(auto& object : objects)
                    {
                        object = nullptr;
                    }
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                    {
                        tasks[i].setIndex(i);
                    }
                    timePerTick = 0;
                    tickListenerMode = 2;
                    nowChosingObject = 0;
                    checkKey = true;
                    tickListenerThread = nullptr;
                    threadEnable = false;
                    useTickListener = true;
                    lastTestTickTime = 0;
                }
                explicit MainWindow(const string& title, short new_size_width = 0, short new_size_height = 0, bool enable = false) : Container(new_size_width, new_size_height)
                {
                    returnInt = 0;
                    setSize(new_size_width, new_size_height);
                    this->title = title;
                    this->enable = enable;
                    for (auto& object : objects)
                    {
                        object = nullptr;
                    }
                    timePerTick = 0;
                    tickListenerMode = 2;
                    nowChosingObject = 0;
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                    {
                        tasks[i].setIndex(i);
                    }
                    checkKey = true;
                    tickListenerThread = nullptr;
                    threadEnable = false;
                    useTickListener = true;
                    lastTestTickTime = 0;
                }
                MainWindow(short new_size_width, short new_size_height, bool enable = false) : Container(new_size_width, new_size_height)
                {
                    returnInt = 0;
                    setSize(new_size_width, new_size_height);
                    this->title = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
                    this->enable = enable;
                    for (auto & object : objects)
                    {
                        object = nullptr;
                    }
                    timePerTick = 0;
                    tickListenerMode = 2;
                    nowChosingObject = 0;
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                    {
                        tasks[i].setIndex(i);
                    }
                    checkKey = true;
                    tickListenerThread = nullptr;
                    threadEnable = false;
                    useTickListener = true;
                    lastTestTickTime = 0;
                }
                ~MainWindow()
                {
                    if (tickListenerThread != nullptr)
                    {
                        enable = false;
                        Sleep(getTimePerTick() + 10);
                        //delete tickListenerThread;
                        tickListenerThread = nullptr;
                    }
                }
                //添加对象
                int add(cuberx::Base* newObject) override
                {
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                    {
                        if (objects[i] == nullptr)
                        {
                            objects[i] = newObject;
                            newObject->setFatherMainWindow(this);
                            return i;
                        }
                    }
                    return -1;
                }
                int add(cuberx::Base& newObject) override
                {
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                    {
                        if (objects[i] == nullptr)
                        {
                            objects[i] = &newObject;
                            newObject.setFatherMainWindow(this);
                            return i;
                        }
                    }
                    return -1;
                }
                MainWindow& operator<<(cuberx::Base* newObject)
                {
                    for (auto & object : objects)
                    {
                        if (object == nullptr)
                        {
                            object = newObject;
                            newObject->setFatherMainWindow(this);
                            return *this;
                        }

                    }
                    cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
                    return *this;
                }
                MainWindow& operator<<(cuberx::Base& newObject)
                {
                    for (auto & object : objects)
                    {
                        if (object == nullptr)
                        {
                            object = &newObject;
                            newObject.setFatherMainWindow(this);
                            return *this;
                        }

                    }
                    cout << "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
                    return *this;
                }

                //移除对象
                void remove(cuberx::Base* removeObject) override
                {
                    if (removeObject != nullptr)
                    {
                        for (auto & object : objects)
                        {
                            if (object == removeObject)
                            {
                                object->resetFatherMainWindow();
                                object = nullptr;
                                draw();
                            }
                        }
                    }
                }
                void remove(cuberx::Base& removeObject) override
                {
                    cuberx::Base* pRemoveObject = &removeObject;
                    for (auto & object : objects)
                    {
                        if (object == pRemoveObject)
                        {
                            object->resetFatherMainWindow();
                            object = nullptr;
                            draw();
                        }
                    }
                }
                MainWindow& operator-=(cuberx::Base* removeObject)
                        {
                    if (removeObject != nullptr)
                    {
                        for (auto & object : objects)
                        {
                            if (object == removeObject)
                            {
                                object->resetFatherMainWindow();
                                object = nullptr;
                                draw();
                            }
                        }
                    }
                    return *this;
                        }
                MainWindow& operator-=(cuberx::Base& removeObject)
                {
                    cuberx::Base* pRemoveObject = &removeObject;
                    for (auto & object : objects)
                    {
                        if (object == pRemoveObject)
                        {
                            object->resetFatherMainWindow();
                            object = nullptr;
                            draw();
                        }
                    }

                    return *this;
                }

                virtual thread* setEnable(bool ifEnable)
                {
                    enable = ifEnable;
                    if (ifEnable)
                    {
                        //设置窗口大小
                        if (getSize().height == 0 || getSize().width == 0)//某一尺寸为零
                            {

                            }
                        else//正常尺寸(未考虑负数)  设置窗口大小 并 清屏
                        {
                            cuberx::WindowSetting::WindowArea(getSize().width, getSize().height, true);
                            //延迟，防止卡顿
                            Sleep(10);
                        }

                        //标题显示
                        char setTitleString[256] = "title ";
                        strcat(setTitleString, title.c_str());
                        system(setTitleString);

                        //隐藏光标
                        cuberx::WindowSetting::setCursorVisition(false);

                        //子组件全部绘制
                        draw();

                        //根据useTickListener 启用帧率管理器线程
                        if (useTickListener)
                        {
                            if (this->tickListenerThread != nullptr)
                            {
                                enable = false;
                                Sleep(getTimePerTick() + 1000);
                                //delete this->tickListenerThread;
                                enable = true;
                                this->tickListenerThread = nullptr;
                            }
                            auto* tickListenerThread = new thread(tickListener, this);
                            this->tickListenerThread = tickListenerThread;
                            return tickListenerThread;
                        }

                    }
                    else
                    {
                        if (tickListenerThread != nullptr)
                        {
                            Sleep(getTimePerTick() + 1000);
                            //delete tickListenerThread;
                            tickListenerThread = nullptr;
                        }
                        setLastTestTickTime(0);
                        //显示光标
                        cuberx::WindowSetting::setCursorVisition(true);

                    }
                    return nullptr;

                }
                virtual bool getEnable()
                {
                    return enable;
                }
                void draw(int drawObjectIndex = -1)
                {
                    if (drawObjectIndex <= -1)
                    {
                        for (auto & object : objects)
                        {
                            if (object != nullptr)
                            {
                                if (object->getVisible())
                                {
                                    object->draw(0,0);
                                }
                            }
                        }
                    }
                    else
                    {
                        objects[drawObjectIndex]->draw(0,0);
                    }
                }
                virtual void setTimePerTick(ULONGLONG newTimePerTick)
                {
                    timePerTick = newTimePerTick;
                }
                virtual ULONGLONG getTimePerTick()
                {
                    return timePerTick;
                }
                virtual void setUseTickListener(bool ifUseTickListener)
                {
                    useTickListener = ifUseTickListener;
                    if (enable)
                    {
                        //刷新状态，即重新启用
                        setEnable(true);
                    }
                }
                virtual bool getUseTickListener()
                {
                    return useTickListener;
                }
                virtual void setCheckKey(bool ifCheckKey)
                {
                    checkKey = ifCheckKey;
                }
                virtual bool getCheckKey()
                {
                    return checkKey;
                }
                virtual ULONGLONG getLastTestTickTime()
                {
                    return lastTestTickTime;
                }
                virtual void setLastTestTickTime(ULONGLONG newLastTestTickTime)
                {
                    lastTestTickTime = newLastTestTickTime;
                }
                virtual void setTickListenerMode(int newMode)
                {
                    tickListenerMode = newMode;
                }
                virtual int getTickListenerMode()
                {
                    return tickListenerMode;
                }
                int getNowChosingObject() override
                {
                    return nowChosingObject;
                }
                void setNowChosingObject(int newChosingObject) override
                {
                    if (objects[newChosingObject] == nullptr)
                    {
                        cout << "[CuberX]Error:The newChosingObject Has Not Be Found!";
                    }
                    else
                    {
                        if (objects[nowChosingObject] != nullptr)
                        {
                            objects[nowChosingObject]->whenStopChosed();
                        }
                        objects[newChosingObject]->whenBeChosed();
                        nowChosingObject = newChosingObject;
                    }
                }

                //根据索引获取容器内对象
                virtual cuberx::Base* getObjectFromIndex(int index)
                {
                    if (index >= 0 || index < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT)
                    {
                        return objects[index];
                    }
                    else
                    {
                        return nullptr;
                    }
                }
                virtual cuberx::Base* operator[](int index)
                {
                    if (index >= 0 || index < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT)
                    {
                        return objects[index];
                    }
                    else
                    {
                        return nullptr;
                    }
                }

                //根据索引获取任务信息
                virtual cuberx::CUTask& getTaskInfo(int tagIndex)
                {
                    return tasks[tagIndex];
                }
                //分配空任务
                virtual int getNewTask()
                {

                    //遍历寻找
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                    {
                        //寻找到空位（未启用的任务）
                        if (tasks[i].getEnable() == 0)
                        {
                            //重置该任务
                            tasks[i].reset();
                            //返回该任务的索引
                            return i;
                        }
                    }

                    //无新任务
                    return -1;
                }
                //设置任务
                virtual void setTask(int taskIndex, cuberx::Base* NewRunClass, int NewTag, void(*NewRun)(cuberx::Base*), DWORD NewCountDownTick, bool ifEnable = true)
                {
                    tasks[taskIndex].set(NewRunClass, NewTag, NewRun, NewCountDownTick, ifEnable);
               }
               
                //帧率管理器（会被作为子线程生成）
                static void tickListener(MainWindow* this_MainWindow)
                {
                    while (true)
                    {
                        //检测是否有关闭
                        if (this_MainWindow->getUseTickListener() == 0 || this_MainWindow->getEnable() == 0)
                        {
                            return;
                        }

                        //校正帧率时刻(前者不为零说明有限制,后者不为零说明不是第一次执行)
                        if (this_MainWindow->getTimePerTick() != 0)
                        {
                            if (this_MainWindow->getLastTestTickTime() != 0)
                            {
                                ULONGLONG pastTime = GetTickCount() - this_MainWindow->getLastTestTickTime();
                                //检测模式(1为不足则补齐,2为不足则补齐 且 超时则多次执行(慎用))
                                switch (this_MainWindow->getTickListenerMode())
                                {
                                    case 1:
                                    {
                                        if (pastTime < this_MainWindow->getTimePerTick())
                                        {
                                            Sleep((DWORD)this_MainWindow->getTimePerTick() - 1 - (DWORD)pastTime);
                                        }
                                        this_MainWindow->setLastTestTickTime(GetTickCount());
                                    }
                                    break;
                                    case 2:
                                    {
                                        if (pastTime <= this_MainWindow->getTimePerTick())
                                        {
                                            //不足(补齐)|恰好(补0)  (并执行)
                                            Sleep((DWORD)this_MainWindow->getTimePerTick() - (DWORD)pastTime);
                                            this_MainWindow->setLastTestTickTime(GetTickCount());
                                        }
                                        else
                                        {
                                            //超时(执行并调后[上次时间])
                                            this_MainWindow->setLastTestTickTime(this_MainWindow->getLastTestTickTime() + this_MainWindow->getTimePerTick() - 1);
                                        }
                                    }
                                    break;
                                    default:
                                        cout << "\n[CuberX]Error:Unknown TickListenerMode";
                                        break;
                                }
                            }
                            else
                            {
                                this_MainWindow->setLastTestTickTime(GetTickCount());
                            }
                        }


                        //检测键位
                        if (this_MainWindow->getCheckKey())
                        {
                            if (_kbhit())
                            {
                                int nowInputKey = _getch();
                                this_MainWindow->keyListener(nowInputKey);
                            }
                        }

                        //任务检测
                        for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
                        {
                            cuberx::CUTask& nowTask = this_MainWindow->getTaskInfo(i);
                            //若任务启用
                            if (nowTask.getEnable())
                            {
                                //已到达时间
                                if (nowTask.getCountDownTick() <= 1)
                                {
                                    //运行任务
                                    nowTask.run();
                                    //重置任务
                                    if(nowTask.getCountDownTick() == 1) {nowTask.reset();}
                                }
                                //未到达时间(0表示无限执行(每时每刻)！2及以上视为未到达)
                                else if (nowTask.getCountDownTick() > 1)
                                {
                                    //将剩余时刻减少1
                                    nowTask.countDown();
                                }
                            }
                        }

                    }
                }
                //键盘监听（一帧内）[0为无响应,1为执行成功]
                virtual void keyListener(int newKey)
                {

                    //全局键位(优先响应)



                    int result = 0;

                    //目前选中成员
                    if (getNowChosingObject() >= 0)
                    {
                        if (objects[getNowChosingObject()] != nullptr)
                        {
                            result = objects[getNowChosingObject()]->keyAction(newKey);
                            if (result == 1)
                            {
                                return;
                            }
                        }
                    }
                    //遍历其它成员
                    for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                    {
                        if (objects[i] != nullptr && i != getNowChosingObject())
                        {
                            result = objects[i]->keyAction(newKey);
                            if (result == 1)
                            {
                                return;
                            }
                        }
                    }
                    //全局键位(滞后响应)
                    switch (newKey)
                    {
                        //上(左)翻
                        case cuberx::Key::$UP:
                            case cuberx::Key::$LEFT:
                            {
                                //遍历前面部分（倒序）
                                if (getNowChosingObject() != 0)
                                {
                                    for (int i = getNowChosingObject() - 1; i >= 0; i--)
                                    {
                                        if (objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                                        {
                                            setNowChosingObject(i);
                                            return;
                                        }
                                    }
                                }
                                //遍历全部（在上面代码块未成功情况下）（倒序）
                                for (int i = $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1; i >= 0; i--)
                                {
                                    if (objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                                    {
                                        setNowChosingObject(i);
                                        return;
                                    }
                                }
                            }
                            break;

                        //下(右)翻
                        case cuberx::Key::$DOWN:
                            case cuberx::Key::$RIGHT:
                            {
                                //遍历剩余部分（正序）
                                if (getNowChosingObject() != $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1)
                                {
                                    for (int i = 1 + getNowChosingObject(); i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                                    {
                                        if (objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                                        {
                                            setNowChosingObject(i);
                                            return;
                                        }
                                    }
                                }
                                //遍历全部（在上面代码块未成功情况下）（正序）
                                for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
                                {
                                    if (objects[i] != nullptr && objects[i]->getCanBeChosed() == 1)
                                    {
                                        setNowChosingObject(i);
                                        return;
                                    }
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            };

}

//ARectFrame
namespace cuberx {
    //0.     1.┏━ 2. ┓草 3. ┗━ 4. ┛  5. ━━ 6. ┃  7. ┳━ 8. ┻━ 9. ┣━ 10. ┫  11. ╋
    static string frameChar[] = { "  ","┏━","┓ ","┗━","┛ " ,"━━","┃ ","┳━","┻━","┣━","┫ ", "╋" };
    //矩形边框
    class ARectFrame : public cuberx::Module
            {
            protected:

            public:

                ARectFrame() = default;
                ARectFrame(short width, short height, short x, short y)
                {
                    location.x  = x;
                    location.y  = y;
                    size.width  = width;
                    size.height = height;
                }
                ARectFrame(short width, short height)
                {
                    size.width  = width;
                    size.height = height;
                }


                void draw(int offsetX = 0, int offsetY = 0) override
                {
                    cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    cout << frameChar[1];
                    for(int i = 0; i < (int)floor( (float)( size.width - 2 ) / 2.0 ); i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + 2 + i * 2 + offsetX);
                        cout << frameChar[5];
                    }
                    cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + size.width - 1 + offsetX);
                    cout << frameChar[2];

                    cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + offsetX);
                    cout << frameChar[3];
                    for(int i = 0; i < (int)floor( (float)( size.width - 2 ) / 2.0 ); i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + 2 + i * 2 + offsetX);
                        cout << frameChar[5];
                    }
                    cuberx::WindowSetting::PointJump(location.y + size.height - 1 + offsetY, location.x + size.width - 1 + offsetX);
                    cout << frameChar[4];

                    for(int i = 0; i < size.y - 2; i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + 1 + i + offsetY, location.x + offsetX);
                        cout << frameChar[6];
                        cuberx::WindowSetting::PointJump(location.y + 1 + i + offsetY, location.x + size.width - 1 + offsetX);
                        cout << frameChar[6];
                    }
                    if(getFatherMainWindow() != nullptr)
                    {
                        WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
                    }
                    else
                    {
                        WindowSetting::PointJump(0, 0);
                    }
                }
    };

}

//AText
namespace cuberx {

    class AText : public cuberx::Module
            {
            public:
                AText()
                {
                    text = " ";
                }
                AText(string newText)
                {
                    text = newText;
                }
                AText(int width, int height, int x, int y)
                {
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                }
                AText(int width, int height)
                {
                    size.width = width;
                    size.height = height;
                }
                AText(string newText, int width, int height, int x, int y)
                {
                    text = newText;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                }
                AText(string newText, int width, int height)
                {
                    text = newText;
                    size.width = width;
                    size.height = height;
                }
                void draw(int offsetX = 0, int offsetY = 0)
                {
                    cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    cout << text;
                    if (getFatherMainWindow() != nullptr)
                    {
                        WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
                    }
                    else
                    {
                        WindowSetting::PointJump(0, 0);
                    }
                }
            };

}

//FrameButton
namespace cuberx {

    //0.     1.┏━ 2. ┓草 3. ┗━ 4. ┛  5. ━━ 6. ┃  7. ┳━ 8. ┻━ 9. ┣━ 10. ┫  11. ╋


    class FrameButton : public cuberx::Module
            {
            private:
                cuberx::ColorInfo textColorInfo;
                cuberx::ColorInfo frameColorInfo;
                cuberx::ColorInfo chosedTextColorInfo;
                cuberx::ColorInfo chosedFrameColorInfo;
                cuberx::ColorInfo normalTextColorInfo;
                cuberx::ColorInfo normalFrameColorInfo;
                cuberx::CUFunction* clickAction;
                static void $action(cuberx::Base* bs)
                {
                    cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
                    pButton->setTextColor(8, 7);

                    pButton->draw();
                }
                static void $action2(cuberx::Base* bs)
                {
                    cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
                    if (!pButton->getBeChosed())
                    {
                        pButton->setTextColor(0, 7);
                        pButton->setFrameColor(0, 7);
                        pButton->draw();
                    }
                }
                static void $action3(cuberx::Base* bs)
                {
                    cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
                    if (pButton->getBeChosed())
                    {
                        pButton->setTextColor(15, 0);
                        pButton->setFrameColor(0, 15);
                        pButton->draw();
                    }
                }
                static void $action4(cuberx::Base* bs)
                {
                    cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
                    pButton->setTextColor(7, 0);
                    pButton->setFrameColor(0, 7);
                    pButton->draw();
                }
                static void $action5(cuberx::Base* bs)
                {
                    cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
                    if (pButton->getBeChosed())
                    {
                        pButton->setTextColor(15, 0);
                        pButton->setFrameColor(0, 15);
                        pButton->draw();
                    }
                    else
                    {
                        pButton->setTextColor(0, 7);
                        pButton->setFrameColor(0, 7);
                        pButton->draw();
                    }
                }
            public:
                FrameButton()
                {
                    text = " ";
                    canBeChosed = 1;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = 0;
                }
                FrameButton(string newText)
                {
                    text = newText;
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = nullptr;
                }
                FrameButton(int width, int height, int x, int y)
                {
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = 1;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = 0;
                }
                FrameButton(int width, int height)
                {
                    size.width = width;
                    size.height = height;
                    canBeChosed = 1;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = nullptr;
                }
                FrameButton(string newText, int width, int height, int x, int y)
                {
                    text = newText;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = nullptr;
                }
                FrameButton(string newText, int width, int height)
                {
                    text = newText;
                    size.width = width;
                    size.height = height;
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    chosedFrameColorInfo.backGround = 0;
                    chosedFrameColorInfo.font = 7;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    normalFrameColorInfo.backGround = 0;
                    normalFrameColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    frameColorInfo = normalFrameColorInfo;
                    clickAction = nullptr;
                }
                void draw(int offsetX = 0, int offsetY = 0) override
                {
                    //绘制边框
                    cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut(frameChar[1], frameColorInfo.font, frameColorInfo.backGround);
                    for (int i = 0; i < (int)floor( (float)( size.width - 2 ) / 2.0 ); i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + 2 + i * 2);
                        WindowSetting::colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
                    }
                    cuberx::WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width - 1);
                    WindowSetting::colorOut(frameChar[2], frameColorInfo.font, frameColorInfo.backGround);

                    cuberx::WindowSetting::PointJump(location.y + offsetY + size.height - 1, location.x + offsetX);
                    WindowSetting::colorOut(frameChar[3], frameColorInfo.font, frameColorInfo.backGround);
                    for (int i = 0; i < (int)floor( (float)( size.width - 2 ) / 2.0 ); i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + offsetY + size.height - 1, location.x + offsetX + 2 + i * 2);
                        WindowSetting::colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
                    }
                    cuberx::WindowSetting::PointJump(location.y + offsetY + size.height - 1, location.x + offsetX + size.width - 1);
                    WindowSetting::colorOut(frameChar[4], frameColorInfo.font, frameColorInfo.backGround);

                    for (int i = 0; i < size.y - 2; i++)
                    {
                        cuberx::WindowSetting::PointJump(location.y + offsetY + 1 + i, location.x + offsetX);
                        WindowSetting::colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
                        cuberx::WindowSetting::PointJump(location.y + offsetY + 1 + i, location.x + offsetX + size.width - 1);
                        WindowSetting::colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
                    }
                    //显示文字
                    cuberx::WindowSetting::PointJump(location.y + offsetY + 1, location.x + offsetX + 2);
                    WindowSetting::colorOut(text, textColorInfo.font, textColorInfo.backGround);

                    if (getFatherMainWindow() != nullptr)
                    {
                        WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
                    }
                    else
                    {
                        WindowSetting::PointJump(0, 0);
                    }
                }
                void whenBeChosed() override
                {
                    beChosed = true;
                    if (getFatherMainWindow() != nullptr)
                    {
                        cuberx::MainWindow& fmw = *getFatherMainWindow();
                        //运行接口函数
                        fmw.setTask(fmw.getNewTask(), this, 1, $action, 2);
                        fmw.setTask(fmw.getNewTask(), this, 1, $action3, 5);
                    }
                    else
                    {
                        setTextColor(15, 0);
                        draw();
                    }
                }
                void whenStopChosed() override
                {
                    beChosed = false;
                    if (getFatherMainWindow() != nullptr)
                    {
                        cuberx::MainWindow& fmw = *getFatherMainWindow();
                        //运行接口函数
                        fmw.setTask(fmw.getNewTask(), this, 1, $action, 5);
                        fmw.setTask(fmw.getNewTask(), this, 1, $action2, 10);
                    }
                    else
                    {
                        setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
                        draw();
                    }

                }


                void setTextColor(int backGround, int font)
                {
                    textColorInfo.backGround = backGround;
                    textColorInfo.font = font;
                }
                void setFrameColor(int backGround, int font)
                {
                    frameColorInfo.backGround = backGround;
                    frameColorInfo.font = font;
                }
                void setBeChosed(bool newCase) override
                {
                    beChosed = newCase;
                    if (newCase)
                    {
                        whenBeChosed();
                    }
                }
                void setClickAction(cuberx::CUFunction* newFunc)
                {
                    clickAction = newFunc;
                }
                void setClickAction(cuberx::CUFunction& newFunc)
                {
                    clickAction = &newFunc;
                }
                void setClickAction(void (*func)(cuberx::Base* this_base))
                {
                    class NewAction : public cuberx::CUFunction
                            {
                        void (*pFunc)(cuberx::Base* this_base);
                            public:
                                explicit NewAction(void (*newPFunc)(cuberx::Base* this_base))
                                {
                                    pFunc = newPFunc;
                                }
                                void func(cuberx::Base* this_base) override
                                {
                                    pFunc(this_base);
                                }
                            };
                    auto* na = new NewAction(func);
                    clickAction = na;
                }
                CUFunction& getClickAction()
                {
                    return *clickAction;
                }
                int keyAction(int newKey) override
                {
                    switch (newKey)
                    {
                        case cuberx::Key::$ENTER:
                        {
                            cuberx::MainWindow* fmw = getFatherMainWindow();


                            //运行接口函数
                            if (fmw != nullptr)
                            {
                                fmw->setTask(fmw->getNewTask(), this, 1, $action4, 2);
                            }
                            if (&getClickAction() != nullptr)
                            {
                                getClickAction().func(this);
                            }
                            if (fmw != nullptr)
                            {
                                fmw->setTask(fmw->getNewTask(), this, 1, $action5, 35);
                            }
                            return 1;
                        }

                    }
                    return 0;
                }
            };

}

//TextButton 纯文本按钮
namespace cuberx {

    /// <summary>
    /// 纯文本按钮
    /// </summary>
    class TextButton : public cuberx::Module
            {
            protected:
                cuberx::ColorInfo textColorInfo;
                cuberx::ColorInfo chosedTextColorInfo;
                cuberx::ColorInfo normalTextColorInfo;
                cuberx::CUFunction* clickAction;
                //灰色
                static void $action(cuberx::Base* bs)
                {
                    cuberx::TextButton* pButton = dynamic_cast<cuberx::TextButton*>(bs);
                    pButton->setTextColor(8, 7);

                    pButton->draw();
                }
                //原色
                static void $action2(cuberx::Base* bs)
                {
                    cuberx::TextButton* pButton = dynamic_cast<cuberx::TextButton*>(bs);
                    if (!pButton->getBeChosed())
                    {
                        pButton->setTextColor(0, 7);
                        pButton->draw();
                    }
                }
                //被选择
                static void $action3(cuberx::Base* bs)
                {
                    cuberx::TextButton* pButton = dynamic_cast<cuberx::TextButton*>(bs);
                    if (pButton->getBeChosed())
                    {
                        pButton->setTextColor(15, 0);
                        pButton->draw();
                    }
                }
                //被按下
                static void $action4(cuberx::Base* bs)
                {
                    cuberx::TextButton* pButton = dynamic_cast<cuberx::TextButton*>(bs);
                    pButton->setTextColor(7, 0);
                    pButton->draw();
                }
                //被按下后弹起
                static void $action5(cuberx::Base* bs)
                {
                    cuberx::TextButton* pButton = dynamic_cast<cuberx::TextButton*>(bs);
                    if (pButton->getBeChosed())
                    {
                        pButton->setTextColor(15, 0);
                        pButton->draw();
                    }
                    else
                    {
                        pButton->setTextColor(0, 7);
                        pButton->draw();
                    }
                }
            public:
                TextButton()
                {
                    text = " ";
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    clickAction = nullptr;
                }
                TextButton(string text, int x = 0, int y = 0, int width = 8, int height = 1)
                {
                    this->text = std::move(text);
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    clickAction = nullptr;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;

                }
                TextButton(int x = 0, int y = 0, int width = 8, int height = 1)
                {
                    text = " ";
                    canBeChosed = true;
                    chosedTextColorInfo.backGround = 7;
                    chosedTextColorInfo.font = 0;
                    normalTextColorInfo.backGround = 0;
                    normalTextColorInfo.font = 7;
                    textColorInfo = normalTextColorInfo;
                    clickAction = nullptr;
                    location.x = x;
                    location.y = y;
                    size.width = width;
                    size.height = height;
                }

                /// <summary>
                /// 设置文字颜色
                /// (0:黑   8:灰
                ///  1:蓝   9:淡蓝
                ///  2:绿   10:淡绿色
                ///  3:浅绿色 11:淡浅绿色
                ///  4:红色 12:淡红色
                ///  5:紫色 13:淡紫色
                ///  6:黄色 14:淡黄色
                ///  7:白色 15:亮白色)
                /// </summary>
                /// <param name="backGround">背景色</param>
                /// <param name="font">文字色</param>
                virtual void setTextColor(int backGround, int font)
                {
                    textColorInfo.backGround = backGround;
                    textColorInfo.font = font;
                }
                virtual cuberx::ColorInfo getTextColor()
                {
                    return textColorInfo;
                }
                virtual void setBeChosed(bool newCase)
                {
                    beChosed = newCase;
                    if (newCase)
                    {
                        whenBeChosed();
                    }
                }
                virtual void setClickAction(cuberx::CUFunction* newFunc)
                {
                    clickAction = newFunc;
                }
                virtual void setClickAction(cuberx::CUFunction& newFunc)
                {
                    clickAction = &newFunc;
                }
                virtual void setClickAction(void (*func)(cuberx::Base* this_base))
                {
                    class NewAction : public cuberx::CUFunction
                            {
                        void (*pFunc)(cuberx::Base* this_base);
                            public:
                                NewAction(void (*newPFunc)(cuberx::Base* this_base))
                                {
                                    pFunc = newPFunc;
                                }
                                void func(cuberx::Base* this_base)
                                {
                                    pFunc(this_base);
                                }
                            };
                    NewAction* na = new NewAction(func);
                    clickAction = na;
                }
                virtual CUFunction& getClickAction()
                {
                    return *clickAction;
                }
                int keyAction(int newKey)
                {
                    switch (newKey)
                    {
                        case KEY.$ENTER:
                        {
                            cuberx::MainWindow& fmw = *getFatherMainWindow();


                            //运行接口函数
                            if (&fmw != nullptr)
                            {
                                fmw.setTask(fmw.getNewTask(), this, 1, $action4, 2);
                            }
                            if (&getClickAction() != 0)
                            {
                                getClickAction().func(this);
                            }
                            if (&fmw != nullptr)
                            {
                                fmw.setTask(fmw.getNewTask(), this, 1, $action5, 35);
                            }
                            return 1;
                        }

                    }
                    return 0;
                }

                virtual void draw(int offsetX = 0, int offsetY = 0)
                {
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX);
                    WindowSetting::colorOut(text, textColorInfo.font, textColorInfo.backGround);
                }
                virtual void whenBeChosed()
                {
                    beChosed = true;
                    if (getFatherMainWindow() != nullptr)
                    {
                        cuberx::MainWindow& fmw = *getFatherMainWindow();
                        //运行接口函数
                        fmw.setTask(fmw.getNewTask(), this, 1, $action, 2);
                        fmw.setTask(fmw.getNewTask(), this, 1, $action3, 5);
                    }
                    else
                    {
                        setTextColor(15, 0);
                        draw();
                    }
                }
                void whenStopChosed()
                {
                    beChosed = false;
                    if (getFatherMainWindow() != nullptr)
                    {
                        cuberx::MainWindow& fmw = *getFatherMainWindow();
                        //运行接口函数
                        fmw.setTask(fmw.getNewTask(), this, 1, $action, 4);
                        fmw.setTask(fmw.getNewTask(), this, 1, $action2, 8);
                    }
                    else
                    {
                        setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
                        draw();
                    }

                }

            };

}

//ClText 多彩文本
#define $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH 128
namespace cuberx {

    class CLText : public cuberx::Module
            {
            private:
                cuberx::ColorInfo textColorInfo[$CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH];
            public:
                CLText()
                {
                    for (int i = 0; i < $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH; i++)
                    {
                        textColorInfo[i].backGround = 0;
                        textColorInfo[i].font = 7;
                    }
                }
                /*
                 0 = 黑色	8 = 灰色
                 1 = 蓝色	9 = 淡蓝色
                 2 = 绿色	A = 淡绿色
                 3 = 浅绿色	B = 淡浅绿色
                 4 = 红色	C = 淡红色
                 5 = 紫色	D = 淡紫色
                 6 = 黄色	E = 淡黄色
                 7 = 白色	F = 亮白色
                */
                CLText(string text)
                {
                    this->text = text;
                    for (int i = 0; i < $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH; i++)
                    {
                        textColorInfo[i].backGround = 0;
                        textColorInfo[i].font = 7;
                    }
                }
                CLText(string text, string backGroundColorInfoString, string fontColorInfoString, int width = 5, int height = 1, int x = 0, int y = 0)
                {
                    this->text = text;

                    //重置
                    for (int i = 0; i < $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH; i++)
                    {
                        textColorInfo[i].backGround = 0;
                        textColorInfo[i].font = 7;
                    }
                    //读取并写入
                    for (int i = 0; i < backGroundColorInfoString.length(); i++)
                    {
                        switch (backGroundColorInfoString[i])
                        {
                            case '0':
                                textColorInfo[i].backGround = 0;
                                break;
                                case '1':
                                    textColorInfo[i].backGround = 1;
                                    break;
                                    case '2':
                                        textColorInfo[i].backGround = 2;
                                        break;
                                        case '3':
                                            textColorInfo[i].backGround = 3;
                                            break;
                                            case '4':
                                                textColorInfo[i].backGround = 4;
                                                break;
                                                case '5':
                                                    textColorInfo[i].backGround = 5;
                                                    break;
                                                    case '6':
                                                        textColorInfo[i].backGround = 6;
                                                        break;
                                                        case '7':
                                                            textColorInfo[i].backGround = 7;
                                                            break;
                                                            case '8':
                                                                textColorInfo[i].backGround = 8;
                                                                break;
                                                                case '9':
                                                                    textColorInfo[i].backGround = 9;
                                                                    break;
                                                                    case 'A':
                                                                        case 'a':
                                                                            textColorInfo[i].backGround = 10;
                                                                            break;
                                                                            case 'B':
                                                                                case 'b':
                                                                                    textColorInfo[i].backGround = 11;
                                                                                    break;
                                                                                    case 'C':
                                                                                        case 'c':
                                                                                            textColorInfo[i].backGround = 12;
                                                                                            break;
                                                                                            case 'D':
                                                                                                case 'd':
                                                                                                    textColorInfo[i].backGround = 13;
                                                                                                    break;
                                                                                                    case 'E':
                                                                                                        case 'e':
                                                                                                            textColorInfo[i].backGround = 14;
                                                                                                            break;
                                                                                                            case 'F':
                                                                                                                case 'f':
                                                                                                                    textColorInfo[i].backGround = 15;
                                                                                                                    break;
                                                                                                                    default:
                                                                                                                        break;
                        }
                    }
                    for (int i = 0; i < fontColorInfoString.length(); i++)
                    {
                        switch (fontColorInfoString[i])
                        {
                            case '0':
                                textColorInfo[i].font = 0;
                                break;
                                case '1':
                                    textColorInfo[i].font = 1;
                                    break;
                                    case '2':
                                        textColorInfo[i].font = 2;
                                        break;
                                        case '3':
                                            textColorInfo[i].font = 3;
                                            break;
                                            case '4':
                                                textColorInfo[i].font = 4;
                                                break;
                                                case '5':
                                                    textColorInfo[i].font = 5;
                                                    break;
                                                    case '6':
                                                        textColorInfo[i].font = 6;
                                                        break;
                                                        case '7':
                                                            textColorInfo[i].font = 7;
                                                            break;
                                                            case '8':
                                                                textColorInfo[i].font = 8;
                                                                break;
                                                                case '9':
                                                                    textColorInfo[i].font = 9;
                                                                    break;
                                                                    case 'A':
                                                                        case 'a':
                                                                            textColorInfo[i].font = 10;
                                                                            break;
                                                                            case 'B':
                                                                                case 'b':
                                                                                    textColorInfo[i].font = 11;
                                                                                    break;
                                                                                    case 'C':
                                                                                        case 'c':
                                                                                            textColorInfo[i].font = 12;
                                                                                            break;
                                                                                            case 'D':
                                                                                                case 'd':
                                                                                                    textColorInfo[i].font = 13;
                                                                                                    break;
                                                                                                    case 'E':
                                                                                                        case 'e':
                                                                                                            textColorInfo[i].font = 14;
                                                                                                            break;
                                                                                                            case 'F':
                                                                                                                case 'f':
                                                                                                                    textColorInfo[i].font = 15;
                                                                                                                    break;
                                                                                                                    default:
                                                                                                                        break;
                        }
                    }

                    setSize(width, height);
                    setLocation(x, y);
                }
                virtual void draw(int offsetX = 0, int offsetY = 0)
                {
                    long long strLength = text.length();
                    string temp = "";
                    WindowSetting::PointJump(getLocation().y + offsetY, getLocation().x + offsetX);
                    for (long long i = 0; i < strLength; i++)
                    {
                        temp = text[i];
                        WindowSetting::colorOut(temp, textColorInfo[i].font, textColorInfo[i].backGround);
                    }
                    if (getFatherMainWindow() != nullptr)
                    {
                        WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
                    }
                    else
                    {
                        WindowSetting::PointJump(0, 0);
                    }
                }

                /*彩色输出
                0 = 黑色 8 = 灰色
                1 = 蓝色 9 = 淡蓝色
                2 = 绿色 10 = 淡绿色
                3 = 浅绿色 11 = 淡浅绿色
                4 = 红色 12 = 淡红色
                5 = 紫色 13 = 淡紫色
                6 = 黄色 14 = 淡黄色
                7 = 白色 15 = 亮白色
                https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
                */
                virtual void setTextColorInfo(string backGroundColorInfoString, string fontColorInfoString, bool ifResetAll = 0, bool ifChangeNow = 1)
                {
                    //若变量ifResetAll为true(1)则重置
                    if (ifResetAll)
                    {
                        for (int i = 0; i < $CU_CLTEXT_TEXTCOLORINFO_MAX_LENGTH; i++)
                        {
                            textColorInfo[i].backGround = 0;
                            textColorInfo[i].font = 7;
                        }
                    }
                    //读取并写入
                    for (int i = 0; i < backGroundColorInfoString.length(); i++)
                    {
                        switch (backGroundColorInfoString[i])
                        {
                            case '0':
                                textColorInfo[i].backGround = 0;
                                break;
                                case '1':
                                    textColorInfo[i].backGround = 1;
                                    break;
                                    case '2':
                                        textColorInfo[i].backGround = 2;
                                        break;
                                        case '3':
                                            textColorInfo[i].backGround = 3;
                                            break;
                                            case '4':
                                                textColorInfo[i].backGround = 4;
                                                break;
                                                case '5':
                                                    textColorInfo[i].backGround = 5;
                                                    break;
                                                    case '6':
                                                        textColorInfo[i].backGround = 6;
                                                        break;
                                                        case '7':
                                                            textColorInfo[i].backGround = 7;
                                                            break;
                                                            case '8':
                                                                textColorInfo[i].backGround = 8;
                                                                break;
                                                                case '9':
                                                                    textColorInfo[i].backGround = 9;
                                                                    break;
                                                                    case 'A':
                                                                        case 'a':
                                                                            textColorInfo[i].backGround = 10;
                                                                            break;
                                                                            case 'B':
                                                                                case 'b':
                                                                                    textColorInfo[i].backGround = 11;
                                                                                    break;
                                                                                    case 'C':
                                                                                        case 'c':
                                                                                            textColorInfo[i].backGround = 12;
                                                                                            break;
                                                                                            case 'D':
                                                                                                case 'd':
                                                                                                    textColorInfo[i].backGround = 13;
                                                                                                    break;
                                                                                                    case 'E':
                                                                                                        case 'e':
                                                                                                            textColorInfo[i].backGround = 14;
                                                                                                            break;
                                                                                                            case 'F':
                                                                                                                case 'f':
                                                                                                                    textColorInfo[i].backGround = 15;
                                                                                                                    break;
                                                                                                                    case 'N':
                                                                                                                        case 'n':
                                                                                                                        {
                                                                                                                            ColorInfo normalColorInfo;
                                                                                                                            textColorInfo[i].backGround = normalColorInfo.backGround;
                                                                                                                            break;
                                                                                                                        }
                                                                                                                        default:
                                                                                                                            break;
                        }
                    }
                    for (int i = 0; i < fontColorInfoString.length(); i++)
                    {
                        switch (fontColorInfoString[i])
                        {
                            case '0':
                                textColorInfo[i].font = 0;
                                break;
                                case '1':
                                    textColorInfo[i].font = 1;
                                    break;
                                    case '2':
                                        textColorInfo[i].font = 2;
                                        break;
                                        case '3':
                                            textColorInfo[i].font = 3;
                                            break;
                                            case '4':
                                                textColorInfo[i].font = 4;
                                                break;
                                                case '5':
                                                    textColorInfo[i].font = 5;
                                                    break;
                                                    case '6':
                                                        textColorInfo[i].font = 6;
                                                        break;
                                                        case '7':
                                                            textColorInfo[i].font = 7;
                                                            break;
                                                            case '8':
                                                                textColorInfo[i].font = 8;
                                                                break;
                                                                case '9':
                                                                    textColorInfo[i].font = 9;
                                                                    break;
                                                                    case 'A':
                                                                        case 'a':
                                                                            textColorInfo[i].font = 10;
                                                                            break;
                                                                            case 'B':
                                                                                case 'b':
                                                                                    textColorInfo[i].font = 11;
                                                                                    break;
                                                                                    case 'C':
                                                                                        case 'c':
                                                                                            textColorInfo[i].font = 12;
                                                                                            break;
                                                                                            case 'D':
                                                                                                case 'd':
                                                                                                    textColorInfo[i].font = 13;
                                                                                                    break;
                                                                                                    case 'E':
                                                                                                        case 'e':
                                                                                                            textColorInfo[i].font = 14;
                                                                                                            break;
                                                                                                            case 'F':
                                                                                                                case 'f':
                                                                                                                    textColorInfo[i].font = 15;
                                                                                                                    break;
                                                                                                                    case 'N':
                                                                                                                        case 'n':
                                                                                                                        {
                                                                                                                            ColorInfo normalColorInfo;
                                                                                                                            textColorInfo[i].font = normalColorInfo.font;
                                                                                                                            break;
                                                                                                                        }
                                                                                                                        default:
                                                                                                                            break;
                        }
                    }
                    //立即绘制
                    if (ifChangeNow)
                    {
                        draw();
                    }
                }
            };

}

//组件群组
namespace cuberx {
    //组件群组(建议在堆内分配子组件的内存(即用new关键字),析构函数会自动回收内存)
    template<int objectCount>
    class Group : public cuberx::Container
            {
            protected:
                cuberx::Base* objects[objectCount];
            public:
                Group()
                {
                    for (int i = 0; i < objectCount; i++)
                    {
                        objects[i] = nullptr;
                    }
                }
                ~Group()
                {
                    for (int i = 0; i < objectCount; i++)
                    {
                        if (objects[i] != nullptr)
                        {
                            delete objects[i];
                            objects[i] = nullptr;
                        }
                    }
                }
                //绘制子组件，-1表示绘制所有
                virtual void draw(int index, int offsetX = 0, int offsetY = 0)
                {
                    if (index == -1)
                    {
                        for (int i = 0; i < objectCount; i++)
                        {
                            objects[i]->draw(location.x + offsetX, location.y + offsetY);
                        }
                    }
                    else if (index >= 0)
                    {
                        objects[index]->draw(location.x + offsetX, location.y + offsetY);
                    }
                }
                virtual void draw(int offsetX = 0, int offsetY = 0)
                {
                    for (int i = 0; i < objectCount; i++)
                    {
                        objects[i]->draw(location.x + offsetX, location.y + offsetY);
                    }
                }
                virtual void setNowChosingObject(int newChoingObject)
                {
                    if (objects[nowChosingObject] != nullptr)
                    {
                        objects[nowChosingObject]->whenStopChosed();
                    }
                    if (objects[newChoingObject] != nullptr)
                    {
                        objects[newChoingObject]->whenBeChosed();
                    }
                    nowChosingObject = newChoingObject;
                }
                //键位反应
                int keyAction(int newKey)
                {
                    //
                    int result = 0;
                    for (int i = 0; i < objectCount; i++)
                    {
                        result = objects[i]->keyAction(newKey);
                        if (result == 1)
                        {
                            return result;
                        }
                    }
                    return result;
                }
                //设置所属主窗口信息(同步到子组件)
                virtual void setFatherMainWindow(cuberx::MainWindow* newFatherMainWindow)
                {
                    fatherMainWindow = newFatherMainWindow;
                    for (int i = 0; i < objectCount; i++)
                    {
                        if (objects[i] != nullptr)
                        {
                            objects[i]->setFatherMainWindow(newFatherMainWindow);
                        }
                    }
                }
                //重置所属主窗口信息(同步到子组件)
                virtual void resetFatherMainWindow()
                {
                    fatherMainWindow = nullptr;
                    for (int i = 0; i < objectCount; i++)
                    {
                        if (objects[i] != nullptr)
                        {
                            objects[i]->resetFatherMainWindow();
                        }
                    }
                }
            };

}

//测试组件:黑白标题+彩色内容+自动伸缩边框
namespace cuberx {

    class TipBar : public cuberx::Group<3>
            {
            protected:
                cuberx::ARectFrame* arf;
                cuberx::AText* at;
                cuberx::CLText* clt;
                bool autoSize;
                bool frameVisible;
            public:
                TipBar()
                {
                    autoSize = 1;
                    arf = new cuberx::ARectFrame;
                    at = new cuberx::AText("提示: ", 6, 1, 2, 1);
                    clt = new cuberx::CLText("无", "00", "cc", 2, 1, at->getText().length() + 2, 1);
                    runAutoSize();
                    objects[0] = arf;
                    objects[1] = at;
                    objects[2] = clt;
                    frameVisible = 1;
                }
                TipBar(string title, string tip, string tipBackGroundColorInfo = "", string tipFontColorInfo = "", int x = 0, int y = 0, bool frameVisible = 1, bool ifUseAutoSize = 1, int width = 10, int height = 3)
                {
                    autoSize = ifUseAutoSize;
                    arf = new cuberx::ARectFrame(width, height);
                    at = new cuberx::AText(title, title.length(), 1, 2, 1);
                    clt = new cuberx::CLText(tip, tipBackGroundColorInfo, tipFontColorInfo, tip.length(), 1, at->getText().length() + 2, 1);
                    setLocation(x, y);
                    setSize(width, height);
                    if (ifUseAutoSize)
                    {
                        runAutoSize();
                    }
                    objects[0] = arf;
                    objects[1] = at;
                    objects[2] = clt;
                    this->frameVisible = frameVisible;
                }
                virtual void runAutoSize()
                {
                    arf->setSize(at->getText().length() + clt->getText().length() + 3, 3);
                    clt->setLocation(2 + at->getText().length(), 1);
                }
                virtual void setAutoSize(bool ifAutoSize)
                {
                    autoSize = ifAutoSize;
                    if (ifAutoSize)
                    {
                        runAutoSize();
                        draw();
                    }
                }
                virtual void setAText(string newText)
                {
                    at->setText(newText);
                    if (autoSize)
                    {
                        runAutoSize();
                    }
                    draw();
                }
                virtual void setCLText(string newText, string tipBackGroundColorInfo = "", string tipFontColorInfo = "")
                {
                    clt->setText(newText);
                    clt->setTextColorInfo(tipBackGroundColorInfo, tipFontColorInfo, true, false);
                    if (autoSize)
                    {
                        runAutoSize();
                    }
                    draw();
                }
                virtual void setFrameSize(int width, int height)
                {
                    arf->setSize(width, height);
                    draw();
                }
                virtual void draw(int offsetX = 0, int offsetY = 0)
                {
                    if (frameVisible)
                    {
                        objects[0]->draw(location.x + offsetX, location.y + offsetY);
                    }
                    for (int i = 1; i < 3; i++)
                    {
                        objects[i]->draw(location.x + offsetX, location.y + offsetY);
                    }
                }
            };

}

//PGBar 进度条
namespace cuberx {
    //进度条字符(9种,从"  "到"█")
    static string ProgressChar[] = { "  ","▏","▎","▍","▌" ,"▋","▊" ,"▉" ,"█" };

    class PGBar : public cuberx::Module
            {
            protected:
                int ProgressCount;
                int lastFullCount;
                int lastHungryCountLevel;
                long double maxValue;
                long double minValue;
                long double nowValue;
                bool ifDrawPercentage;
                double percentage;
                cuberx::ColorInfo ProgressColor;
            public:
                PGBar()
                {
                    ProgressCount = 8;
                    maxValue = 100;
                    minValue = 0;
                    nowValue = 0;
                    ifDrawPercentage = 1;
                    percentage = (nowValue - minValue) / (maxValue - minValue);
                    lastHungryCountLevel = 0;
                    lastFullCount = 0;
                }
                /// <summary>
                /// 进度条
                /// </summary>
                /// <param name="ProgressCount">进度条总格数</param>
                /// <param name="x">坐标X位置</param>
                /// <param name="y">坐标Y位置</param>
                /// <param name="maxValue">最大值</param>
                /// <param name="minValue">最小值</param>
                /// <param name="nowValue">当前值</param>
                /// <param name="ifDrawPercentage">是否在进度条右侧显示百分比</param>
                /// <param name="progressBackgroundColor">进度条的背景色</param>
                /// <param name="progressFontColor">进度条本身的颜色</param>
                PGBar(int ProgressCount, int x, int y, long double maxValue = 100, long double minValue = 0, long double nowValue = 0, bool ifDrawPercentage = 1, int progressBackgroundColor = 0, int progressFontColor = 7)
                {
                    location.x = x;
                    location.y = y;
                    size.width = ProgressCount * 2;
                    size.height = 1;
                    this->ProgressCount = ProgressCount;
                    this->maxValue = maxValue;
                    this->minValue = minValue;
                    this->nowValue = nowValue;
                    this->ifDrawPercentage = ifDrawPercentage;
                    percentage = (nowValue - minValue) / (maxValue - minValue);
                    ProgressColor.backGround = progressBackgroundColor;
                    ProgressColor.font = progressFontColor;
                    lastFullCount = 0;
                    lastHungryCountLevel = 0;
                }
                /// <summary>
                /// 绘制进度条
                /// </summary>
                /// <param name="offsetX">坐标X偏移量</param>
                /// <param name="offsetY">坐标Y偏移量</param>
                virtual void draw(int offsetX = 0, int offsetY = 0)
                {
                    //清空当前显示内容并铺上背景色
                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + lastFullCount * 2);
                    for (int i = lastFullCount * 2; i < size.width; i++)
                    {
                        WindowSetting::colorOut(" ", ProgressColor.font, ProgressColor.backGround);
                    }

                    //正式绘制
                    if (nowValue >= minValue && nowValue <= maxValue)
                    {
                        double disCount = ProgressCount * percentage;

                        //确定fullCount
                        int fullCount = floor(disCount);

                        // 确定hungryCountLevel
                        int hungryCountLevel = 0;
                        {
                            double hungryCount = disCount - fullCount;
                            if (hungryCount == 0 || hungryCount <= 0.0625)
                            {
                                hungryCountLevel = 0;
                            }
                            else if (hungryCount <= 0.1875)
                            {
                                hungryCountLevel = 1;
                            }
                            else if (hungryCount <= 0.3125)
                            {
                                hungryCountLevel = 2;
                            }
                            else if (hungryCount <= 0.4375)
                            {
                                hungryCountLevel = 3;
                            }
                            else if (hungryCount <= 0.5625)
                            {
                                hungryCountLevel = 4;
                            }
                            else if (hungryCount <= 0.6875)
                            {
                                hungryCountLevel = 5;
                            }
                            else if (hungryCount <= 0.8125)
                            {
                                hungryCountLevel = 6;
                            }
                            else if (hungryCount <= 0.9375)
                            {
                                hungryCountLevel = 7;
                            }
                            else
                            {
                                hungryCountLevel = 8;
                            }
                        }

                        //绘制Full部分
                        {
                            //与 last 相等(无需绘制)
                            if (fullCount == lastFullCount)
                            {

                            }
                            //比 last 小(清除多余部分[hungry所占部分除外])
                            else if (fullCount < lastFullCount)
                            {
                                for (int i = fullCount + 1; i < lastFullCount; i++)
                                {
                                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                                    WindowSetting::colorOut("  ", ProgressColor.font, ProgressColor.backGround);
                                }
                            }
                            //比 last 大(显示缺失部分)
                            else
                            {
                                for (int i = lastFullCount; i < fullCount; i++)
                                {
                                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                                    WindowSetting::colorOut(ProgressChar[8], ProgressColor.font, ProgressColor.backGround);
                                }
                            }
                        }

                        //绘制Hungry部分
                        {
                            //位置不变, 直接覆盖
                            if (fullCount == lastFullCount)
                            {
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + fullCount * 2);
                                WindowSetting::colorOut(ProgressChar[hungryCountLevel], ProgressColor.font, ProgressColor.backGround);
                            }
                            //位置有变, 清除之前的再重新显示
                            else
                            {
                                if (lastFullCount > fullCount)
                                {
                                    WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + lastFullCount * 2);
                                    WindowSetting::colorOut("  ", ProgressColor.font, ProgressColor.backGround);
                                }
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + fullCount * 2);
                                WindowSetting::colorOut(ProgressChar[hungryCountLevel], ProgressColor.font, ProgressColor.backGround);
                            }
                        }

                        //刷新last信息
                        lastFullCount = fullCount;
                        lastHungryCountLevel = hungryCountLevel;
                    }
                    //当前值小于最小值
                    else if (nowValue <= minValue)
                    {

                    }
                    //当前值大于最大值
                    else
                    {
                        for (int i = lastFullCount; i < ProgressCount; i++)
                        {
                            WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + i * 2);
                            WindowSetting::colorOut(ProgressChar[8], ProgressColor.font, ProgressColor.backGround);
                        }
                        lastFullCount = ProgressCount;
                    }

                    //显示百分比
                    {
                        if (ifDrawPercentage)
                        {
                            if (percentage <= 0)
                            {
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                                cout << "0  %";
                            }
                            else if (percentage >= 1)
                            {
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                                cout << "100%";
                            }
                            else
                            {
                                string disMem = "            ";
                                disMem = (percentage * 100);
                                string finalDisMem = "             ";
                                if (disMem.length() >= 0)finalDisMem[0] = disMem[0];
                                if (disMem.length() >= 1)finalDisMem[1] = disMem[1];
                                if (disMem.length() >= 2)finalDisMem[2] = disMem[2];
                                if (disMem.length() >= 3)finalDisMem[3] = disMem[3];
                                if (disMem.length() >= 4)finalDisMem[4] = '%';
                                finalDisMem[5] = 0;
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                                cout << "     ";
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width);
                                cout << ceil(percentage * 100);
                                WindowSetting::PointJump(location.y + offsetY, location.x + offsetX + size.width + 3);
                                cout << "%";
                            }
                        }
                    }
                    if (getFatherMainWindow() != nullptr)
                    {
                        WindowSetting::PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
                    }
                    else
                    {
                        WindowSetting::PointJump(0, 0);
                    }

                }
                virtual int getProgressCount()
                {
                    return ProgressCount;
                }
                virtual void setProgressCount(int newProgressCount, bool ifChangeNow = 1)
                {
                    ProgressCount = newProgressCount;
                    size.width = ProgressCount * 2;
                    if (ifChangeNow) { draw(); }
                }
                virtual long double getMaxValue()
                {
                    return maxValue;
                }
                virtual void setMaxValue(long double newMaxValue, bool ifChangeNow = 1)
                {
                    maxValue = newMaxValue;
                    percentage = (nowValue - minValue) / (maxValue - minValue);
                    if (ifChangeNow) { draw(); }
                }
                virtual long double getMinValue()
                {
                    return minValue;
                }
                virtual void setMinValue(long double newMinValue, bool ifChangeNow = 1)
                {
                    minValue = newMinValue;
                    percentage = (nowValue - minValue) / (maxValue - minValue);
                    if (ifChangeNow) { draw(); }
                }
                virtual long double getNowValue()
                {
                    return nowValue;
                }
                virtual void setNowValue(long double newNowValue, bool ifChangeNow = 1)
                {
                    nowValue = newNowValue;
                    percentage = (nowValue - minValue) / (maxValue - minValue);
                    if (ifChangeNow) { draw(); }
                }
                virtual bool getIfDrawPercentage()
                {
                    return ifDrawPercentage;
                }
                virtual void setIfDrawPercentage(bool ifDrawPercentage, bool ifChangeNow = 1)
                {
                    this->ifDrawPercentage = ifDrawPercentage;
                    if (ifChangeNow) { draw(); }
                }
                virtual cuberx::ColorInfo getProgressColor()
                {
                    return ProgressColor;
                }
                virtual void setProgressColor(int backGroundColor, int fontColor, bool ifChangeNow = 1)
                {
                    ProgressColor.backGround = backGroundColor;
                    ProgressColor.font = fontColor;
                    if (ifChangeNow) { draw(); }
                }
            };

}

//WAVSoundPlayer WAV音频播放器
namespace cuberx {

    //WAV音频播放器
    class WAVSoundPlayer : public cuberx::Module
            {
            private:
                string soundFile;
                bool useNewThread;//是否使用多线程播放(可以实现多个声音并行播放)
                thread* newThr;
                static void $playSound(string fileName)
                {
                    //若为局部路径则转换为绝对路径
                    if (fileName.length() > 2)
                    {
                        if (fileName[1] != ':')
                        {
                            char temp[1024];
                            _fullpath(temp, fileName.c_str(), 1024);
                            fileName = temp;
                        }
                    }
                    //播放
                    string strOpenCommand = "open ";
                    strOpenCommand = strOpenCommand + fileName;
                    wchar_t* wcharOpenCommand = strT.StringToWchar(strOpenCommand);
                    string strPlayCommand = "play ";
                    strPlayCommand = strPlayCommand + fileName;
                    wchar_t* wcharPlayCommand = strT.StringToWchar(strPlayCommand);
                    //mciSendString(reinterpret_cast<LPCSTR>(wcharOpenCommand), NULL, 0, 0);
                    //mciSendString(reinterpret_cast<LPCSTR>(wcharPlayCommand), NULL, 0, 0);
                    delete[] wcharOpenCommand;
                    delete[] wcharPlayCommand;
                }
            public:
                WAVSoundPlayer()
                {
                    soundFile = "";
                    useNewThread = 1;
                    newThr = nullptr;
                }
                WAVSoundPlayer(string newSoundFile, bool ifUseNewThread = 1)
                {
                    soundFile = newSoundFile;
                    useNewThread = ifUseNewThread;
                    newThr = nullptr;
                }

                static thread* playSoundTool(string fileName, bool ifUseNewThread = 1)
                {
                    if (ifUseNewThread)
                    {
                        thread* thr = new thread($playSound, fileName);
                        return thr;
                    }
                    else
                    {
                        $playSound(fileName);
                    }
                    return nullptr;
                }

                virtual void playSound()
                {
                    if (newThr != nullptr)
                    {
                        //TODO: 此处应删除该线程
                        newThr = nullptr;
                    }
                    thread* tempThr;
                    tempThr = playSoundTool(soundFile, useNewThread);
                    if (tempThr != nullptr)
                    {
                        newThr = tempThr;
                    }
                }
                virtual void setSoundFile(string newSoundFile)
                {
                    soundFile = newSoundFile;
                }
                virtual string getSoundFile()
                {
                    return soundFile;
                }
                virtual void setIfUseNewThread(bool ifUseNewThread)
                {
                    useNewThread = ifUseNewThread;
                }
                virtual bool getIfUseNewThread()
                {
                    return useNewThread;
                }
            };

}

//ASwitch 开关按钮
namespace cuberx
{
    //ASwitch 开关按钮
    class ASwitch : public cuberx::Module
    {
    protected:
        bool condition; // On(true) | Off(false)
        Coordinate offset;
        //中间
        static void $action1(cuberx::Base* this_base)
        {
            auto* this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x
                );
            WindowSetting::colorOut(" ■ ",7,6);
        }
        //开启
        static void $action2(cuberx::Base* this_base)
        {
            auto* this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x
                );
            if(this_aOnOff->getBeChosed())
            {
                WindowSetting::colorOut("  ■", 7, 10);
            }
            else
            {
                WindowSetting::colorOut("  ■", 8, 10);
            }
        }
        //关闭
        static void $action3(cuberx::Base* this_base)
        {
            auto* this_aOnOff = dynamic_cast<cuberx::ASwitch *>(this_base);
            WindowSetting::PointJump(
                this_aOnOff->getLocation().y + this_aOnOff->getOffset().y,
                this_aOnOff->getLocation().x + this_aOnOff->getOffset().x
                );
            if(this_aOnOff->getBeChosed())
            {
                WindowSetting::colorOut("■  ", 7, 12);
            }
            else
            {
                WindowSetting::colorOut("■  ", 8, 12);
            }
        }
    public:
        ASwitch()
        {
            location.x = 0;
            location.y = 0;
            condition = false;
            canBeChosed = true;
        }
        ASwitch(short x, short y, bool defaultCondition = false)
        {
            location.x = x;
            location.y = y;
            condition = defaultCondition;
            canBeChosed = true;
        }
        void draw(int offsetX, int offsetY) override
        {
            WindowSetting::PointJump(location.y + offsetX, location.x + offsetY);
            if(condition)
            {
                // On
                if(beChosed)
                {
                    WindowSetting::colorOut("  ■", 7, 10);
                }
                else
                {
                    WindowSetting::colorOut("  ■", 8, 10);
                }
            }
            else
            {
                // Off
                if(beChosed)
                {
                    WindowSetting::colorOut("■  ", 7, 12);
                }
                else
                {
                    WindowSetting::colorOut("■  ", 8, 12);
                }
            }
        }
        int keyAction(int newKey) override
        {
            int result = 0;
            cuberx::MainWindow* fmw = getFatherMainWindow();
            switch(newKey)
            {
            case Key::$LEFT:
            {
                if(condition)
                {
                    condition = false;
                    if(fmw != nullptr && fmw->getUseTickListener())
                    {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(),this,7,$action1,5);
                        fmw->setTask(fmw->getNewTask(),this,7,$action3,10);
                    }
                    else
                    {
                        // No Action
                        draw(offset.x,offset.y);
                    }
                }
                result = 1;
            }
            break;
            case Key::$RIGHT:
            {
                if(!condition)
                {
                    condition = true;
                    if(fmw != nullptr && fmw->getUseTickListener())
                    {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(),this,7,$action1,5);
                        fmw->setTask(fmw->getNewTask(),this,7,$action2,10);
                    }
                    else
                    {
                        // No Action
                        draw(offset.x,offset.y);
                    }
                }
                result = 1;
            }
            break;
            case Key::$ENTER:
            {
                if(condition)
                {
                    // On => Off
                    condition = false;
                    if(fmw != nullptr && fmw->getUseTickListener())
                    {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(),this,7,$action1,5);
                        fmw->setTask(fmw->getNewTask(),this,7,$action3,10);
                    }
                    else
                    {
                        // No Action
                        draw(offset.x,offset.y);
                    }
                }
                else
                {
                    // Off => On
                    condition = true;
                    if(fmw != nullptr && fmw->getUseTickListener())
                    {
                        // Use Action
                        fmw->setTask(fmw->getNewTask(),this,7,$action1,5);
                        fmw->setTask(fmw->getNewTask(),this,7,$action2,10);
                    }
                    else
                    {
                        // No Action
                        draw(offset.x,offset.y);
                    }
                }
                result = 1;
            }
            break;
            default:
                break;
            }
            return result;
        }
        void whenBeChosed() override
        {
            beChosed = true;
            draw(offset.x, offset.y);
        }
        void whenStopChosed() override
        {
            beChosed = false;
            draw(offset.x, offset.y);
        }
    };
}

//TextSwitch (组件群组)带文字的开关按钮
namespace cuberx
{
    //TextSwitch (组件群组)带文字的开关按钮
    class TextSwitch : public cuberx::Group<2> {
    protected:
        cuberx::CLText*    cltText;
        cuberx::ASwitch*   aSwitch;

    public:
        TextSwitch(const string& text = "", short width = 4, short height = 1, short x = 0, short y = 0, bool defaultCondition = false)
        {
            cltText = new cuberx::CLText(
                text,
                "",
                "8888888888888888888888888888888888888888",
                width,
                height,
                x,
                y
                );
            aSwitch = new cuberx::ASwitch((short)(x + width - 4), y, defaultCondition);
            objects[0] = cltText;
            objects[1] = aSwitch;
            canBeChosed = true;
        }
        void whenBeChosed() override
        {
            beChosed = true;
            cltText->setTextColorInfo("","7777777777777777777777777777777777777777",false,true);
            aSwitch->whenBeChosed();
        }
        void whenStopChosed() override
        {
            beChosed = false;
            cltText->setTextColorInfo("","8888888888888888888888888888888888888888",false,true);
            aSwitch->whenStopChosed();
        }
    };
}

#endif
