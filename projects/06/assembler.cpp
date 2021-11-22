#include<bits/stdc++.h>
using namespace std;
class Praser {

    public:
        string command;
        bool hasMoreCommands() {
            //输入中是否还有更多命令
            advance();
            if (command == EOF) 
                return false;
            return true;
        }
        void advance() {
           //读取下一条命令 将其当作“当前命令”
            getline(cin, command);
            if (command == EOF) 
                return;
            int len = command.length();
            bool isNotEmpty = false;
            for (int i = 0; i < len; i++) {
                if (command[i] != ' ') 
                    isNotEmpty = true;
                if (i < len - 1) {
                    if (command[i] == '/' && command[i+1] == '/') {
                        advance();
                        return;
                    }
                }
            }
            if (!isNotEmpty) {
                advance();
                return;
            }
        }
        char commandType() {
            //返回当前命令的类型 A指令 返回'A' C指令返回'C' {Xxx}返回'L'
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ') {
                    return (command[i] == '@' ? 'A' : (command[i] == '{' ? 'L' : 'C'));
                }
            }
        }
        string symbol() {
            //返回形如@Xxx 或{Xxx}的当前命令的符号或十进制数值
            //仅当commandType()是A
            string symbolRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ' && command[i] != '{' && command[i] != '}' && command[i] != '@') {
                    symbolRes += command[i];
                } 
            }
            return symbolRes;
        }
        string dest() { 
            //返回当前C指令的dest
            //仅当commandType()是C时才能调用
            int cntop = 0;
            string destRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cntop < 2)  //没有dest域
                return "";  
            else {
                //如果有dest域就一定有'=',把读到等号之前的所有非空格处理出来即可。
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == '=') 
                        return destRes;
                    else if (command[i] != ' ') {
                        destRes += command[i];
                    }
                }
            }
            return '';
        }
        string comp() {
            //返回当前C指令的comp
            //仅当commandType()是C时才能调用
            int cntop = 0;
            string compRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cntop < 2)  //没有comp域
                return "";  
            bool isComp = false;
            else {
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == '=') {
                        isComp = true;
                    }
                    if (isComp && command[i] == ';')    //注释只会在行末 不会被读到
                        return compRes;
                    if (isComp && command[i] != ' ' && command[i] != '=') {
                        compRes += command[i];
                    }
                }
            }
            return '';
        }
        string jump() {
            //返回当前C指令的jump
            //仅当commandType()是C时才能调用
            //jump读入时要识别一下注释
            int cntop = 0;
            string jumpRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cntop == 2)  //没有jump
                return "";  
            if (cntop == 1) {
                //只有jump
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == ';') 
                        return jumpRes;
                    if (command[i] != ' ')
                        jumpRes += command[i];
                }
            } else if (cntop == 3) {
                bool isJump = false;
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == ';') {
                        if (isJump) 
                            return jumpRes;
                        else {
                            isJump = true;
                            continue;
                        }
                    } 
                    if (command[i] != ' ') {
                        jumpRes += command[i];
                    }
                }
            }
            return '';
        }
}