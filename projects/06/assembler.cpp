#include<bits/stdc++.h>
using namespace std;
class Praser {

    public:
        string command;
        bool hasMoreCommands() {
            //�������Ƿ��и�������
            advance();
            if (command == EOF) 
                return false;
            return true;
        }
        void advance() {
           //��ȡ��һ������ ���䵱������ǰ���
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
            //���ص�ǰ��������� Aָ�� ����'A' Cָ���'C' {Xxx}����'L'
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ') {
                    return (command[i] == '@' ? 'A' : (command[i] == '{' ? 'L' : 'C'));
                }
            }
        }
        string symbol() {
            //��������@Xxx ��{Xxx}�ĵ�ǰ����ķ��Ż�ʮ������ֵ
            //����commandType()��A
            string symbolRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] != ' ' && command[i] != '{' && command[i] != '}' && command[i] != '@') {
                    symbolRes += command[i];
                } 
            }
            return symbolRes;
        }
        string dest() { 
            //���ص�ǰCָ���dest
            //����commandType()��Cʱ���ܵ���
            int cntop = 0;
            string destRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //֮������з���Ҳ��ע�����
            }
            if (cntop < 2)  //û��dest��
                return "";  
            else {
                //�����dest���һ����'=',�Ѷ����Ⱥ�֮ǰ�����зǿո���������ɡ�
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
            //���ص�ǰCָ���comp
            //����commandType()��Cʱ���ܵ���
            int cntop = 0;
            string compRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //֮������з���Ҳ��ע�����
            }
            if (cntop < 2)  //û��comp��
                return "";  
            bool isComp = false;
            else {
                for (int i = 0; i < command.length(); i++) {
                    if (command[i] == '=') {
                        isComp = true;
                    }
                    if (isComp && command[i] == ';')    //ע��ֻ������ĩ ���ᱻ����
                        return compRes;
                    if (isComp && command[i] != ' ' && command[i] != '=') {
                        compRes += command[i];
                    }
                }
            }
            return '';
        }
        string jump() {
            //���ص�ǰCָ���jump
            //����commandType()��Cʱ���ܵ���
            //jump����ʱҪʶ��һ��ע��
            int cntop = 0;
            string jumpRes = '';
            for (int i = 0; i < command.length(); i++) {
                if (command[i] == ';' || command[i] == '=') 
                    cntop++;
                if (i < command.length() - 1 && command[i] == '/' && command[i+1] == '/') 
                    break;  //֮������з���Ҳ��ע�����
            }
            if (cntop == 2)  //û��jump
                return "";  
            if (cntop == 1) {
                //ֻ��jump
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