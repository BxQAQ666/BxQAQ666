import difflib
import sys
import os
import cProfile
#判断文件是否存在并输出异常地址
def txt_exist(txts):
    if(os.path.exists(txts[1])):
        if(os.path.exists(txts[2])):
            if(os.path.exists(txts[3])):
                return 1
            else:
                print("文件异常 " + txts[3])
        else:
            print("文件异常 " + txts[2])
    else:
        print("文件异常 " + txts[1])
    return 0
#打开并读取文件
def read_txt(txt):
    with open(txt, "r",encoding='utf-8') as f:  # 打开文件
        data = f.read()  # 读取文件
    return data

#将文件按一句一句分开
def div(data,l):
    afdiv = [""]
    begin = end = 0
    for end in range(begin,l-1):
        if(data[end] == '。'):#or data[end] == '\n'
            afdiv.append(data[begin:end])
            begin = end + 1
    if(begin==0):
        afdiv.append(data[begin:]) 
    return afdiv

#计算重复率
def op(t1,t2,l1,l2):
    sum = 0
    i = 0
    j = 0
    while i < l1 and j < l2:
        if(difflib.SequenceMatcher(None, t1[i], t2[j]).quick_ratio()<0.15):
            if(i/l1>j/l2):
                j=j+1
            else:
                i=i+1
        else:  
            sum += difflib.SequenceMatcher(None, t1[i], t2[j]).quick_ratio()
            j=j+1
            i=i+1
    return sum/min(l1,l2)


#将结果写入ans.txt中
def write_txt(t,result):
    f = open(t, "a")
    f.write(str('%.2f'%result)+'\n')
    f.close()


#主函数
def main():
    if(txt_exist(sys.argv)):
        data1 = read_txt(sys.argv[1])
        data2 = read_txt(sys.argv[2])
        new1 = div(data1,len(data1))
        new2 = div(data2,len(data2))
        result = op(new1,new2,len(new1),len(new2))
        print(result)
        write_txt(sys.argv[3],result)

main()
cProfile.run('main()')
#单元测试
#def test(s):
#    print('%.2f'%difflib.SequenceMatcher(None, s[0], s[1]).quick_ratio())
    
#def test_txt():
#    s1 = ["反方向的钟","钟的向方反"]
#    test(s1)
#    s2 = ["今天是个好日子","明天是个坏日子"]
#    test(s2)
#    s3 = ["Why you bully me","Y u bully me"]
#    test(s3)
#    s4 = ["c++UTF-8转Unicode真的好难","Python处理txt文件简单多了"]
#    test(s4)
#    s5 = ["你好","hello"]
#    test(s5)
#    s6 = ["look at ur phone","lk a os"]
#    test(s6)
#    s7 = ["TnT","UwU"]
#    test(s7)
#    s8 = [":(",":)"]
#    test(s8)
#    s9 = ["Envy Genius","EG"]
#    test(s9)
#    s10 = ["python","Unititled-1.py"]
#    test(s10)

#test_txt()