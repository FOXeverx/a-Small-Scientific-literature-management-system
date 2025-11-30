#ifndef PORTER_STEMMING_H
#define PORTER_STEMMING_H

#include<QString>
#include <string.h>
#include<iostream>
#define TRUE 1
#define FALSE 0
using namespace std;
/* 变量b是一个缓冲区，用于存储待提取词干的单词。字符b[k0]、b[k0+1]直到b[k]代表了单词的字母。
 * 实际上，在这个演示程序中，k0的值为0。
 * 在提取词干的过程中，k会随着处理的进行而向下调整。在算法中实际上并没有使用零终止符。
*/



/*  判断字符是否为辅音 */

int cons(int i);

/*
 * 该函数用于计算在k0和j之间辅音序列的数量。如果c代表一个辅音序列，v代表一个元音序列，<..>表示任意存在，则：
   <c><v> 返回0
   <c>vc<v> 返回1
   <c>vcvc<v> 返回2
   <c>vcvcvc<v> 返回3
以此类推
*/
int mcount();

/*  判断k0到j之间是否包含元音 */
int vowelinstem();

/* 判断j和(j-1)是否包含双辅音 */
int doublec(int j);

/* 当且仅当i-2，i-1，i形式为辅音-元音-辅音，且第二个c不是w、x或y时，cvc(i)函数返回TRUE。这在尝试恢复短词末尾的e时被使用。
例如：
cav(e), lov(e), hop(e), crim(e) 返回TRUE
snow, box, tray 返回FALSE */
int cvc(int i);

/* 判断k0到k是否以字符串s结尾 */
int ends(const char* s);

/* 将(j+1)到k设置为字符串s中的字符，并重新调整k */
void setto(const char* s);

/*根据字符串s进一步处理 */
static void r(const char* s) { if (mcount() > 0) setto(s); }

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

void step1ab();

/* 当词干中还有另一个元音时，将末尾的y转换为i */
void step1c() ;


/* 将双后缀映射为单后缀. */
void step2() ;

/* 处理-ic-, -full, -ness等后缀 */
void step3();

/* 处理-cvc形式的单词 */
void step4();

/* 当m()>1时去掉末尾的-e，并在m()>1时将-ll变为-l*/

void step5();
/* stem(p, i, j)中，p是一个char指针，待提取词干的字符串从p[i]到p[j]（包括p[j]）.
 *  通常情况下，i是零，j是字符串的最后一个字符的偏移量，即(p[j+1] == '\0')。
 *  词干提取算法会调整p[i]到p[j]之间的字符，并返回新的字符串结束位置k。提取词干不会增加单词长度，因此i <= k <= j。
 *  为了将词干提取器转化为一个模块，需要将'stem'声明为extern，并删除本文件的其余部分。
*/

int stem(char* p, int i, int j);


/*--------------------stemmer definition ends here------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>       /* for isupper, islower, tolower */

static char* s;         /*用于传递到之前提到的缓冲区b  */
#define INC 50           /* s增加的大小单位 */
static int i_max = INC;  /* b的最大偏移量 */


#define LETTER(ch) (isupper(ch) || islower(ch))


static QString lemma(const QString&title)
{
    // 将 QString 转换为 std::string
    std::string str = title.toStdString();
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    // 将 std::string 转换为 char*
    char* cstr = const_cast<char*>(str.c_str());
    int pos=stem(cstr, 0, strlen(cstr)-1);
    string tmp=str.substr(0,pos+1);
    return QString::fromStdString(tmp);
}




#endif // PORTER_STEMMING_H
