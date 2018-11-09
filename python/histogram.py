#coding:utf-8
 
from PIL import Image
#打开图片
img = Image.open("J8_600.jpg")
 
#调整图片大小，原来的图书是200*200，Image.BILINEAR表示使用双线性法对像素点插值
newImg = img.resize((100,100), Image.BILINEAR)
newImg.save("newImg001.jpg")
 
#旋转图片
rotImg = newImg.rotate(90)
rotImg.save("rotImg.jpg") #若想进行格式转换，可直接改后缀名，PIL会自动完成
 
#对图片像素点进行直方图统计,运行后会看到
print len(newImg.histogram())

