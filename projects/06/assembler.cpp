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
class Code {
    private:
        map<string, string> destRes, compRes, jumpRes;
    public:
        //注意遍历这个map的时候要用引用以免复制一遍
        void init() {
            destRes[""] = "000";
            destRes["M"] = "001";
            destRes["D"] = "010";
            destRes["MD"] = destRes["DM"] = "011";
            destRes["A"] = "100";
            destRes["AM"] = destRes["MA"] = "101";
            destRes["AD"] = destRes["DA"] = "110";
            destRes["AMD"] = destRes["ADM"] = destRes["MAD"] = destRes["MDA"] = destRes["DAM"] = destRes["DMA"] = "111";
            compRes["0"] = "0101010";
            compRes["1"] = "0111111";
            compRes["-1"] = "0111010";
            compRes["D"] = "0001100";
            compRes["A"] = "0110000";
            compRes["!D"] = "0001101";
            compRes["!A"] = "0110001";
            compRes["-D"] = "0001111";
            compRes["-A"] = "0110011";
            compRes["D+1"] = compRes["1+D"] = "0011111";
            compRes["A+1"] = compRes["1+A"] = "0110111";
            compRes["D-1"] = "0001110";
            compRes["A-1"] = "0110010";
            compRes["D+A"] = compRes["A+D"] = "0000010";
            compRes["D-A"] = "0010011";
            compRes["A-D"] = "0000111";
            compRes["D&A"] = compRes["A&D"] = "0000000";
            compRes["D|A"] = compRes["A|D"] = "0010101";
            compRes["M"] = "1110000";
            compRes["!M"] = "1110001";
            compRes["-M"] = "1110011";
            compRes["M+1"] = compRes["1+M"] = "1110111";
            compRes["M-1"] = "1110010";
            compRes["D+M"] = compRes["M+D"] = "1000010";
            compRes["D-M"] = "1010011";
            compRes["M-D"] = "1000111";
            compRes["D&M"] = compRes["M&D"] = "1000000";
            compRes["D|M"] = compRes["M|D"] = "1010101";
            jumpRes[""] = "000";
            jumpRes["JGT"] = "001";
            jumpRes["JEQ"] = "010";
            jumpRes["JGE"] = "011";
            jumpRes["JLT"] = "100";
            jumpRes["JNE"] = "101";
            jumpRes["JLE"] = "110";
            jumpRes["JMP"] = "111";
        }
        string dest(string destIn) {
            //返回dest对应的3位二进制码
            return destRes[destIn];
        }
        string comp(string compIn) {
            //返回comp对应的7位二进制码
            return compRes[compIn];
        }
        string jump(string jumpIn) {
            return jumpRes[jumpIn];
        }
}
