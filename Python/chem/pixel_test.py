from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import time
import picamera

my_dpi=160 # Rpi 7'LCD dpi
#-------------------------------------------------------------
# capturing the image
with picamera.PiCamera() as camera:
    camera.resolution = (2560, 1920)
    print(camera.resolution)
    camera.start_preview()
    time.sleep(2)
    camera.capture('image1.jpg')
    camera.stop_preview()
#-------------------------------------------------------------
# croppint the image fragment
plt.rcParams['toolbar'] = 'None'
im = Image.open('image1.jpg')#'2_strips.jpg')
width_l,height_l = im.size
im2 = im.crop((850, 450, 1700, 1300))
im2.save('crop.jpg')
width_s,height_s = im2.size
print(im2.size)
#-------------------------------------------------------------
pix_data = []   # array to store Y pixel scan summ values
noise_level = 0 # noise level
# scanning the image
for i in range(0,width_s):
    sum = 0
    #print i
    for j in range(0,height_s):
        sum += im2.getpixel((i,j))[0]
    pix_data.append(int(sum))#-noise_level))
y_pos = np.arange(len(pix_data))
#-------------------------------------------------------------
# plotting scan result
plt.figure(figsize=(400/my_dpi, 300/my_dpi), dpi=160)
plt.bar(y_pos, pix_data)#,marker='o', ms = 10, alpha=1, color='b')
plt.tick_params(
    axis='both', 
    which='both', 
    bottom='off', top='off', 
    labelbottom='off', 
    right='off', 
    left='off', 
    labelleft='off')

#plt.ylabel('Summ pixel value')
#plt.title('Strip intensity profile')
plt.savefig('result.jpg', dpi=160)
plt.show()
# plt.clf()