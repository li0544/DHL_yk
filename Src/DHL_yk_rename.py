# -*- coding: gbk -*-
'''
Created on 2014-11-10
@author: wp
@note: rename files and call the aspack compression
'''
import os
import re
import time
import datetime
import operator

name = "大灰狼远程管理"
path = "D:\\Program\\Tem_C\\0001.远控\\0110.DHL_yk_DDos\\Src\\Bin"
     
def rename_files():
    prefix = name + ".exe"
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path,file)):     #判断是否为文件
            #if re.match(prefix, file):
            #print(operator.eq(prefix, file))
            if operator.eq(prefix, file):
                print("找到文件：" + file)
                now = datetime.datetime.now()
                s1 = now.strftime('%Y-%m-%d')   #now.strftime('%Y-%m-%d %H:%M:%S')
                new_name = name + "_" + s1 + ".exe"
                bak_file = name + "_" + s1 + ".exe.bak"

                if os.path.isfile(os.path.join(path,new_name)): #判断新文件是否存在
                    print(new_name + " 已存在")
                    for i in range(98,122):
                        new_name = name + "_" + s1 + chr(i) + ".exe"
                        bak_file = name + "_" + s1 + chr(i) + ".exe.bak"
                        if not os.path.isfile(os.path.join(path,new_name)):                            
                            break
                        else:
                            print(new_name + '已存在')
                        
                    #os.remove(os.path.join(path,new_name))
                #new_name = re.sub(prefix, "", file)
                            
                newfilename = os.path.join(path, new_name)
                oldfilename = os.path.join(path, file)
                bakfilename = os.path.join(path, bak_file)
                print('rename: ' + newfilename)
                os.rename(oldfilename, newfilename)

                print('compress: ' + newfilename)
                os.system("aspack " + newfilename)  #call aspack

                #time.sleep(1) #sleep
                print('delete: ' + bakfilename)
                os.remove(bakfilename)  #delete bak file
                if not os.path.isfile(bakfilename):
                    print('delete bak file success !')

#if __name_ == '__main__':
rename_files()

