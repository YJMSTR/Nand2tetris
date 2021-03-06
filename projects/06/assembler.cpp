#include<bits/stdc++.h>
using namespace std;
class SymbolTable {
    public:
        map<string, int> symbolTable;
        int tot = 16, cnt = 0;
        void init() {
            addEntry("SP", 0);
            addEntry("LCL", 1);
            addEntry("ARG", 2);
            addEntry("THIS", 3);
            addEntry("THAT", 4);
            addEntry("R0", 0);
            addEntry("R1", 1);
            addEntry("R2", 2);
            addEntry("R3", 3);
            addEntry("R4", 4);
            addEntry("R5", 5);
            addEntry("R6", 6);
            addEntry("R7", 7);
            addEntry("R8", 8);
            addEntry("R9", 9);
            addEntry("R10", 10);
            addEntry("R11", 11);
            addEntry("R12", 12);
            addEntry("R13", 13);
            addEntry("R14", 14);
            addEntry("R15", 15);
            addEntry("SCREEN", 16384);
            addEntry("KBD", 24576);
        }
        void addEntry(const string& symbol, int address) {
            symbolTable[symbol] = address;
        }
        bool contains(const string& symbol) {
            return symbolTable.count(symbol);
        }
        int GetAddress(const string& symbol) {
            return symbolTable[symbol];
        }
};
class Praser {
    public:
        string command;
        queue<string> inputs;
        bool hasMoreCommands() {
            //输入中是否还有更多命令
            advance();
            if (command[0] == EOF) 
                return false;
            return true;
        }
        void advance() {
           //读取下一条命令 将其当作“当前命令”
            if (inputs.empty()) {
                command[0] = EOF;
                return;
            }
            command = inputs.front();
            inputs.pop();
            if (command[0] == EOF) 
                return;
            int len = command.length();
            bool isNotEmpty = false, isNotComment = true;
            for (int i = 0; i < len; i++) {
                if (i < len - 1) {
                    if (command[i] == '/' && command[i+1] == '/') {
                        isNotComment = false;
                        if (!isNotEmpty) {
                            advance();
                            return;
                        }
                        break;
                    }
                }
                if (command[i] != ' ') 
                    isNotEmpty = true;
            }
            if (!isNotEmpty) {
                advance();
                return;
            }
        }
        char commandType() {
            //返回当前命令的类型 A指令 返回'A' C指令返回'C' (Xxx)返回'L'
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ') {
                    return (command[i] == '@' ? 'A' : (command[i] == '(' ? 'L' : 'C'));
                }
            }
            return '\0';
        }
        string symbol() {
            //返回形如@Xxx 或(Xxx)的当前命令的符号或十进制数值
            //仅当commandType()是A
            string symbolRes = "";
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ' && command[i] != '(' && command[i] != ')' && command[i] != '@') {
                    symbolRes += command[i];
                } 
            }
            return symbolRes;
        }
        string dest() { 
            //返回当前C指令的dest
            //仅当commandType()是C时才能调用
            int cntop = 0, cnteq = 0;
            string destRes = "";
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';') 
                    cntop++;
                if (command[i] == '=') 
                    cnteq++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cnteq != 1)  //没有dest域 形如JMP
                return "";  
            else {
                //如果有dest域就一定有'=',把读到等号之前的所有非空格处理出来即可。
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == '=') 
                        break;
                    else if (command[i] != ' ') {
                        destRes += command[i];
                    }
                }
            }
            //if (dest)
            return destRes;
        }
        string comp() {
            //返回当前C指令的comp
            //仅当commandType()是C时才能调用
            //comp不会为空
            int cntop = 0, cnteq = 0;
            string compRes = "";
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';') 
                    cntop++;
                if (command[i] == '=') 
                    cnteq++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cnteq == 0)  { //没有dest
                if (cntop == 0) {
                    for (int i = 0; i < command.length(); i++) {
                        if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                            break;  //之后如果有符号也是注释里的
                        if (command[i] != ' ') {
                            compRes += command[i];
                        }
                    } 
                } else {
                    for (int i = 0; i < command.length(); i++) {//如果有jump
                        if (command[i] == ';') 
                            break;
                        if (command[i] != ' ') {
                            compRes += command[i];
                        }
                    } 
                }
            } else {    //有dest 讨论有没有jump
                if (cntop == 1) {
                    bool isComp = false;
                    for (int i = 0; i < command.length(); i++) {
                        if (command[i] == '=') {
                            isComp = true;
                            continue;
                        }
                        if (isComp && command[i] == ';')    //注释只会在行末 不会被读到
                            break;
                        if (isComp && command[i] != ' ') {
                            compRes += command[i];
                        }
                    }
                } else {
                    bool isComp = false;
                    for (int i = 0; i < command.length(); i++) {
                        if (command[i] == '=') {
                            isComp = true;
                            continue;
                        }
                        if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                            break;  //之后如果有符号也是注释里的
                        if (isComp && command[i] != ' ') {
                            compRes += command[i];
                        }
                    }
                }
            }
            return compRes;
        }
        string jump() {
            //返回当前C指令的jump
            //仅当commandType()是C时才能调用
            //jump读入时要识别一下注释
            int cnteq = 0, cntop = 0;
            string jumpRes = "";
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == '=') 
                    cnteq++;
                if (command[i] == ';')
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //之后如果有符号也是注释里的
            }
            if (cnteq == 1 && cntop == 0)  //没有jump
                return "";  
            if (cnteq == 0 && cntop == 0) {
                //只有jump 
                for (int i = 0; i < command.length(); i++) {
                    if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                        return jumpRes;  //之后如果有符号也是注释里的
                    if (command[i] != ' ')
                        jumpRes += command[i];
                }
            } else if (cntop == 1) {
                bool isJump = false;
                for (int i = 0; i < command.length(); i++) {
                    if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                        break;  //之后如果有符号也是注释里的
                    if (command[i] == ';') {
                        isJump = true;
                        continue;
                    } 
                    if (isJump && command[i] != ' ') {
                        jumpRes += command[i];
                    }
                }
            } 
            return jumpRes;
        }
};

class Code {
    public:
        //注意遍历这个map的时候要用引用以免复制一遍
        map<string, string> destRes, compRes, jumpRes;
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
        string dest(const string& destIn) {
            //返回dest对应的3位二进制码
            //cout << "destIn == " << destIn << " destRes == " << destRes[destIn] << "\n";
            return destRes[destIn];
        }
        string comp(const string& compIn) {
            //返回comp对应的7位二进制码
            //cout << "compIn == " << compIn << " compRes == " << compRes[compIn] << "\n";
            return compRes[compIn];
        }
        string jump(const string& jumpIn) {
            //cout << "jumpIn == " << jumpIn << " jumpRes == " << jumpRes[jumpIn] << "\n";
            return jumpRes[jumpIn];
        }
};

int main() {
    Praser praser;
    Code code;
    SymbolTable symboltable;
    code.init();
    symboltable.init();
    string tmp;
    queue<string> inputs;
    while (getline(cin, tmp)) {
        praser.inputs.push(tmp);
        inputs.push(tmp);
    }
    while (praser.hasMoreCommands()) {
        char commandType = praser.commandType();
        if (commandType != 'L') {
            symboltable.cnt++;
        } else {
            string symbol = praser.symbol();
            symboltable.addEntry(symbol, symboltable.cnt);
        }
    }
    praser.inputs = inputs;
    while (praser.hasMoreCommands()) {
        char commandType = praser.commandType();
        if (commandType == 'A') {
            string Avalue = praser.symbol();
            //int AintValue = 0;
            bool isInt = true;
            for (int i = 0; i < Avalue.length(); i++) {
                //AintValue = AintValue * 10 + Avalue[i] - '0';
                if (!isdigit(Avalue[i])) {
                    isInt = false;
                    break;
                }
            }
            if (!isInt) {
                if (!symboltable.contains(Avalue)) {
                    symboltable.addEntry(Avalue, symboltable.tot++);
                }
            }
        }
    }
    bool flag = 0;
    praser.inputs = inputs;
    int cnt = 0;
    while(praser.hasMoreCommands()) {
        //cout << "++cnt = " << ++cnt << "\n";
        if (flag) {
            cout << "\n";
        } else flag = 1;
        string output = "";
        char commandType = praser.commandType();
        //cout << "commandT = " << commandType << "\n";
        if (commandType == 'A') {
            string Avalue = praser.symbol();
            int AintValue = 0;
            bool isInt = true;
            for (int i = 0; i < Avalue.length(); i++) {
                AintValue = AintValue * 10 + Avalue[i] - '0';
                if (!isdigit(Avalue[i])) {
                    isInt = false;
                    break;
                }
            }
            if (!isInt) {
                if (!symboltable.contains(Avalue)) {
                    symboltable.addEntry(Avalue, symboltable.tot++);
                }
                AintValue = symboltable.GetAddress(Avalue);
                //printf("Aintvalue = %d\n", AintValue);
            }
            for (int i = 15; i > 0; i--) {
                output = output + ((AintValue & 1) ? '1' : '0');
                AintValue >>= 1;
            }
            reverse(output.begin(), output.end());
            output = "0" + output;
        } else if (commandType == 'C') {
            output = "111";
            output += code.comp(praser.comp());
            output += code.dest(praser.dest());
            output += code.jump(praser.jump());
            //cout << "output == " << output << endl;
        } else if (commandType == 'L') {
            flag = 0;   
            //没有输出 不要输出换行符
        }
        cout << output;
    }
}