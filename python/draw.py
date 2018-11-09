#coding:utf-8
 
from PIL import Image, ImageDraw
#打开图片
img = Image.open("newImg001.jpg")
draw = ImageDraw.Draw(img)
 
width, height = img.size
 
#画直线,线的颜色
draw.line(((0,width/2), (width-1, height/2)), fill = 255)
img.save("newImg001.jpg")
 
#画圆
#(0,0,width-1,height-1)指定了所画弧线的界限 
#0,360是所画弧线的起始角度和终止角度
draw.arc(((0,0), (width-1, height-1)), 0, 360, fill = 255)
img.save("newImg002.jpg")

