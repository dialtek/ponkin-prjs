import time
import picamera

with picamera.PiCamera() as camera:
    camera.resolution = (2560, 1920)
    print(camera.resolution)
    camera.start_preview()
    time.sleep(3)
    im = camera.capture('image1.jpg')
    camera.stop_preview()
    w, h = im.size
    im.crop((0, 500, w, h-500)).save('crop.jpg')