#!/usr/bin/python3

import cv2
import time

cam = cv2.VideoCapture(0)
time.sleep(2)
count = 0
ret = cam.set(3,320)
ret = cam.set(4,240)
time.sleep(2)
cv2.namedWindow('image')

while True:
    success, image = cam.read()
    if not success:
        time.sleep(1)
        continue

    cv2.imshow('image', image)
    key = cv2.waitKey(40)
    key = chr(key & 255)
    if key == ' ':
        cv2.imwrite('frames/bin13frame' + str(count) + '.jpg', image)
        print('captured frames/bin13frame' + str(count) + '.jpg')
        count += 1
    elif key == 'q':
        break

cv2.destroyAllWindows()
