#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_LAB 100
#define LAB_LEN 10
#define FOR_NEST 25
#define SUB_NEST 25
#define PROG_SIZE 10000
#define DELIMITER 1
#define VARIABLE 2
#define NUMBER 3
#define COMMAND 4
#define STRING 5
#define QUOTE 6

#define PRINT 1
#define INPUT 2
#define IF 3
#define THEN 4
#define FOR 5
#define NEXT 6
#define TO 7
#define GOTO 8
#define EOL 9
#define FINISHED 10
#define GOSUB 11
#define RETURN 12
#define END 13

char *prog;      /* holds expression to be analyzed  */
jmp_buf e_buf;   /* hold environment for longjmp() */

int variables[26]= {  /* 26 user variables,A-Z  */
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

struct commands { /* keyword lookup table  */
    char command[20];
    char tok;
} table[] = {  /* command must be entered lowercase  */
    "print",PRINT,   /* in this table  */
    "input",INPUT,
    "if",IF,
    "then",THEN,
    "goto",GOTO,
    "for",FOR,
    "next",NEXT,
    "to",TO,
    "gosub",GOSUB,
    "return",RETURN,
    "end",END,
    NULL,END
};

char token[80];     //注意token是数组类型
char token_type,tok;

struct label {
    char name [LAB_LEN];
    char *p;    /* point to place to go in source */
};

struct label label_table[NUM_LAB];
char *find_label(),*gpop();

struct for_stack {
    int var;   /* counter variable  */
    int target;  /* target value  */
    char *loc;
} fstack[FOR_NEST];  /* stack for FOR/NEXT loop  */
struct for_stack fpop();

char *gstack[SUB_NEST];  /* stack for gosub  */
int ftos;  /* index to top of FOR stack  */
int gtos;  /* index to top of GOSUB  */

void print(),scan_labels(),find_eol(),exec_goto();
void gosub(),greturn(),gpush(),label_init(),fpush();

/* Load a program */
load_program (char *p,char *fname)
{
    FILE *fp;
    int i=0;
   
    if (!(fp=fopen(fname,"rb")))  return 0;

    i=0;
    do  {
        *p = getc(fp);
        p++;i++;
    } while (!feof(fp)&&i<PROG_SIZE);
    *(p-2) = '/0';   /* null terminate the program  */
    fclose (fp);
    return 1;
}


/* 给变量赋值  比如 a＝3  
 * 注意这里为了简化起见，我们的变量就设置为26个字母
 */
assignment()
{
    int var,value;

    /* getthe variable name */
    get_token();
    if (!isalpha(*token))  //因为变量我们用字母代替 所以必定是字母类型
    {
        serror(4);
        return;
    }

    var = toupper(*token)-'A';  //转化为大写字母  然后减去'A' 这样让变量在hash表中有了座次 比如A减去A为0 这样A字符变量在变量hash表中第一个位置

    /* get the equals sign 
     * 这里我们取a=3 中间的等号*/
    get_token();
    if (*token!='=')    //既然赋值么 肯定有等号了
    {
        serror(3);
        return;
    }

    /* a=3  等号取走了 我们来取数值  */
    get_exp(&value);
   
    /* 把我们取到的变量 比如a 值为3 存放在hash表中 */
    variables[var] = value;
}


/* execute a simple version of the BASIC PRINT statement 
 * 执行打印  这里我们还是举例说明*/
void print()
{
    int answer;
    int len=0,spaces;
    char last_delim;
   
    do  {
        get_token();  /* get next list item */
        if (tok==EOL||tok==FINISHED)  break;  //如果取到的符号是一行结束或者文件结束  自然的打印结束

                 
        //BASIC 中print一般有两种用法  第二种就是print "hello world"  打印字符串  
        if (token_type==QUOTE)  
        {  
            printf ("%s",token);
            len+=strlen(token);
            get_token();    //注意我们打印了后又取了一次符号
        }
        else   //打印变量的
        { 
            putback();
            get_exp(&answer);
            get_token();    //注意我们打印了后又取了一次符号
            len += printf ("%d",answer);
        }
        last_delim = *token;    
        
        
        /* Basic 有两种打印间隔标识 
         * 比如 print a,b 表示按标准格式打印
         * 而print a;b 表示按照紧凑格式打印  
         * 所谓标准格式简单来讲就是间隔大点儿  紧凑自然间隔小点儿  
         */
        if (*token==',')  
        {
            /* compute number of move to next tab */
            spaces = 8-(len%8);
            len += spaces;  /* add in the tabbing position */
            while (spaces)  {
                printf (" ");
                spaces--;
            }
        }
        else if (*token==';')  
            printf ("  ");
        else if (tok != EOL && tok != FINISHED) serror (0);     //print a,b 打完一次后 要么是逗号、分号 要么就是行结束或者文件结束  如果四者不居其一  必然错了
    } while (*token==';'||*token==',');     //例如 print a,b,c 如果token是逗号、分号 那么表示后面还有打印  继续来

    /* 当处于行结束或者文件结束  那么前一次分界符不能是;或者,  
     * 示例 如果 "print a," 这个明显是语法错误 a后面不应该要逗号
     * 那么打印完a取出token是逗号  我们赋值给last_delim 继续循环
     *  下一个是行结束  跳出打印但是检验出last_delim是逗号  出错 */
    if (tok==EOL||tok==FINISHED)    
    {
        if (last_delim != ';' && last_delim != ',') printf ("/n");
    }
    else serror(0);  /* error is not, or ; */
}


/* 搜索所有标签 
 * 这个函数可以说是basic里面的预处理  
 * 我们搜索源代码 找出里面的标签  将其存入标签表
 * 所谓标签label 其实C语言也有 不过一般不常用 因为label多半和goto一起出现的  而在结构化程序设计中 goto出现被人认为是绝对不能的
 * 不过内核中goto却是常常出现
 * 下面这个函数最大的困惑判断标签的特征类型 我们设置为数字  要知道这里标签我们都是设置为数字的
 * 但是如何把标签与普通数值分开呢?
 */
void scan_labels()
{
    int addr;
    char *temp;

    label_init();  /* zero all labels */
    temp = prog;  /* save poiter to top of program */

    /* 如果源代码中第一个是个数字的话  存入标签表中  不过说实话   我没理解这个有什么意义*/
    get_token();
    if (token_type==NUMBER)  
    {
        strcpy (label_table[0].name,token);
        label_table[0].p=prog;
    }
   
    find_eol();     //提行
    do  {
        get_token();
        if (token_type==NUMBER)     //如果是数字   这里是一行开头  开头的数字不可能是一个数值  
        {
            addr = get_next_label(token);
            if (addr==-1||addr==-2)  
            {
                (addr==-1) ? serror(5):serror(6);
            }
            strcpy (label_table[addr].name,token);
            label_table[addr].p = prog;  /* current point in program */
        }
        /* if not on a blank line , find next line */
        if (tok!=EOL) find_eol();
    } while (tok!=FINISHED);
    prog = temp;  /* restore to original */
}


/* find the start of next line */
void find_eol()
{
    while (*prog!='/n'&&*prog!='/0')  ++prog;
    if (*prog)  prog++;
}


/* return index of next free posion in the label array
      -1 is returned if the array is full.
      -2 is returned when duplicate label is found.
*/
get_next_label(char *s)
{
    register int t;

    for (t=0;t<NUM_LAB;++t) {
        if (label_table[t].name[0]==0)  return t;
        if (!strcmp(label_table[t].name,s)) return -2;  /* dup */
    }
    return -1;
}

/* find location of given label. A null is returned if
   label is not found; ohtherwise a pointer to the position
   of the label is returned.
*/
char *find_label(char *s)
{
    register int t;

    for (t=0;t<NUM_LAB;++t)
        if (!strcmp(label_table[t].name,s))  return label_table[t].p;
    return '/0';  /* error condition */
}


/* execute a GOTO statement. 
 * goto一般形式即是 goto label 
 */
void exec_goto()
{
    char *loc;

    get_token();  /* 这里获取标号，即是标签内容 */
    
    loc = find_label (token);  //标签是为跳转所用，所以获取标签后我们马上要想办法得到标签所代表地址
    if (loc=='/0')
        serror(7);  /* 出错 */
    else prog=loc;  /* 重新 设置prog指针  指出了下一个我们运行的地址  我们得完全听他的*/
}


/* initialize the array that holds the labels.
   by convention , a null label name indicates that
   array posiiton is unused.
*/
void label_init()
{
    register int t;

    for (t=0;t<NUM_LAB;++t)  label_table[t].name[0]='/0';
}


/* execute an IF statement 
 * 执行if语句
 */
void exec_if()
{
    int x,y,cond;
    char op;
    /* 这里我们只是处理一个简单的if  就是if (x operator y) */
    get_exp(&x);  /* 获取操作符左边数值 */

    get_token();  /* 获取操作符  "比较符" */
    if (!strcmp("<>",*token))   //这里有点儿问题  一个字符串不可能跟一个字符比较吧
    {
        serror(0);  /* not a leagal oprator */
        return;
    }
    op = *token;
    get_exp(&y);  /* 操作符右边  */

    /* determine the outcome */
    cond = 0;
    switch(op)  {
        case '<':
            if (x<y) cond=1;
            break;
        case '>':
            if (x>y) cond=1;
            break;
        case '==':      //这里也是有点儿问题，op是字符类型 怎么会可能会是'=='，而且好笑的是basic没有这个符号
            if (x==y) cond=1;
            break;
    }
    if (cond)  {  /* is true so process target of IF */
        get_token();
        if (tok != THEN)  {     //if 后面会连上then 所以有if没then是错误的
            serror(8);
            return;
        }  /* else program execution starts on next line */
    }
    else find_eol();  /* find start of next line */
}


/* execute a FOR loop
 * for 循环  其主要格式 文章第一篇已经给出  
 * for i=1 to 10
 * next i
 * 下面就引用此例了
 */
void exec_for()
{
    struct for_stack i;     //申请一个栈元素  到时候加入
    int value;

    get_token();  /*  获取标号  这里获取到变量i */
    if (!isalpha(*token))  //变量必定是字符型
    {
        serror(4);
        return;
    }

    i.var = toupper(*token) - 'A';  /* 我们是把变量放在hash表中的  所以这里来计算变量在hash表中位置   */

    get_token();  /* 这里得到了等号 */
    if (*token!='=')  
    {
        serror(3);
        return;
    }
    get_exp(&value);  /* 初始值  比如这里是1 */

    variables[i.var]=value;     //这里把初始值放在变量数组中

    get_token();

    if (tok != TO) serror(9);  /* 读取to单词 */
    get_exp(&i.target);  /* 取得最终要达到的数值  比如这里是10 */

    /* if loop can execute at least once, push into on stack */
    if (value<=i.target)  {
        i.loc = prog;       //记录要执行的语句  这里是for循环的里面要执行的语句
        fpush(i);       //压栈
    }
    else  /* otherwise, skip loop code altogether */
        while (tok!=NEXT)  get_token();     //每到next之前  都输入for循环要执行的语句   所以一直执行
}


/* execute a NEXT statement */
void next()
{
    struct for_stack i;

    i = fpop();  /*read the loop info */

    variables[i.var]++;  /* increment control variable */
    if (variables[i.var]>i.target)  return;  /* all done */
    fpush(i);   /* otherwise,return the info */
    prog = i.loc;  /* loop */
}


/* push function for the FOR stack */
void fpush(struct for_stack i)
{
    if (ftos>FOR_NEST)
    serror(10);
    fstack[ftos]=i;
    ftos++;
}


struct for_stack fpop()
{
    ftos--;
    if (ftos<0)  serror(11);
    return (fstack[ftos]);
}


/* exec a simple form of BASIC INPUT command */
void input()
{
    char str[80],var;
    int i;

    get_token();  /* see if prompt string id=s present */
    if (token_type == QUOTE)  {
        printf (token);  /* if so , print it and check for command */
        get_token();
        if (*token != ',')  serror(1);
        get_token();
    }
    else printf ("? ");  /* otherwise, prompt with / */
    var = toupper(*token) - 'A';  /* get the input var */

    scanf ("%d",&i);  /* read input */
    variables[var] = i;  /* store it */
}


/* execute a GOSUB command 
 * 这个类似c语言中的函数调用 */
void gosub()
{
    char *loc;

    get_token();
    /* find the label to call */
    loc = find_label(token);
    if (loc=='/0')
        serror(7);  /* label not defined */
    else  
    {
        gpush(prog);  /* 当前执行的地址压栈 */
        prog = loc;  /* 重新把要执行的地址赋值给prog */
    }
}


/* return from GOSUB */
void greturn()
{
    prog = gpop();
}


/* GOSUB stack push function */
void gpush(char *s)
{
    gtos++;

    if (gtos==SUB_NEST)  
    {
        serror(12);
        return;
    }

    gstack[gtos] = s;
}


/* GOSUB stack pop function */
char *gpop()
{
    if (gtos==0)  {
        serror(13);
        return 0;
    }
    return gstack[gtos--];
}

main (int argc,char *argv[])
{
    char in[80];
    int answer;
    char *p_buf;
    char *t;

    if (argc!=2)  {
        printf ("usage: run <filename>/n");
        exit (1);
    }

    /* allocate memory for the program */
    if (!(p_buf=(char *)malloc(PROG_SIZE)))  {
        printf ("allocation failure");
        exit (1);
    }

    /* load the program to execute */
    if (!load_program(p_buf,argv[1]))  exit(1);

    if (setjmp(e_buf))  exit(1); /* initialize the long jump */

    prog = p_buf;
    scan_labels();  /*  搜索所有的标签  */
    ftos = 0;  /* 初始化栈  这个是为for循环作准备的  */
    gtos = 0;  /* 初始化栈  这个是为gosub作准备的 */
    do  {
        token_type = get_token();
        /* 如果当前是变量 */
        if (token_type==VARIABLE)  {
            putback();  /* 回退prog指针到变量前 */
            assignment();  /* 赋值  */
        }
        else  /* 除了变量那就是关键字了  可能有同学会问  呃  那个比如一个数字怎么没考虑  请想想一个数字怎么会单独出现 */
            switch (tok)  {
                case PRINT:
                    print();
                    break;
                case GOTO:
                    exec_goto();
                    break;
                case IF:
                    exec_if();
                    break;
                case FOR:
                    exec_for();
                    break;
                case NEXT:
                    next();
                    break;
                case INPUT:
                    input();
                    break;
                case GOSUB:
                    gosub();
                    break;
                case RETURN:
                    greturn();
                    break;
                case END:
                    exit(0);
            }
    }while (tok != FINISHED);
}
