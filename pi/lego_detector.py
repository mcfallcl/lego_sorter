
# Import packages
import os
import cv2
import numpy as np
from picamera.array import PiRGBArray
from picamera import PiCamera
import tensorflow as tf
import argparse
import sys
import time

from appJar import *

from PIL import Image
import PIL.ImageTk
from Tkinter import *
from UDPserver import startmach
from UDPserver import stopmach
from UDPserver import set_bin

# Select camera type (if user enters --usbcam when calling this script,
# a USB webcam will be used)
camera_type = 'picamera'
show_camera = False
debug_mode = False
parser = argparse.ArgumentParser()
parser.add_argument('--usbcam', help='Use a USB webcam instead of picamera',
                    action='store_true')
parser.add_argument('--show_cam', help='Show the frame being processed',
                    action='store_true')
parser.add_argument('--debug', help='Shows the camera, and does not show the GUI. Control must be done via ArduinoController process CLI',
                    action='store_true')
args = parser.parse_args()
if args.usbcam:
    camera_type = 'usb'
if args.show_cam:
    show_camera = True
if args.debug:
    debug_mode = True

window = None
if not debug_mode:
    # GUI stuff
    window = Tk()

    window.title("Welcome To The Lego Sorter")

    #Background Image
    bg_image = PhotoImage(file = "Lego.gif")

    w = bg_image.width()
    h = bg_image.height()

    window.geometry("%dx%d+20+200" % (w,h))

    c = Canvas(window, height = h, width = w)
    c.pack(side = TOP, fill = "both", expand = True)

    c.create_image(0, 0, image = bg_image, anchor = 'nw')

    #code for buttons
    start = Button(c, text = "START", bg = "#00ff00", bd = 4, font = ('Twiddlestix', 25), command = lambda: startmach())
    #start.config(height = 3, width = 5)
    start.pack(side = 'left', padx = 110, pady = 10)
    stop = Button(c, text = "STOP", bg = "red", fg = "white", bd = 6, font = ('Twiddlestix', 27, 'bold'), command = lambda: stopmach())
    #stop.config(height = 6, width = 13)
    stop.pack(side = 'left', pady = 90)

    log = Button(c, text = "LOG", bg = "#00bfff", fg = "yellow", bd = 5, font = ('Twiddlestix', 23))
    #log.config(height = 3, width = 3)
    log.pack(side = 'top', pady = 120)

    window.attributes('-fullscreen', True)
    window.bind('<Escape>', lambda e: window.destroy())

cur_bin = 0
def move_to_bin():
    global cur_bin
    set_bin(cur_bin)
    cur_bin = cur_bin + 1
    if cur_bin > 13:
        cur_bin = 0
        #sort_button = Button(c, text = "SORT", command = lambda: move_to_bin())
        #sort_button.pack(side = 'left', pady=80)


# Set up camera constants
IM_WIDTH = 320
IM_HEIGHT = 240


#### Initialize TensorFlow model ####

# This is needed since the working directory is the object_detection folder.
sys.path.append('..')

# Import utilites
from utils import label_map_util
from utils import visualization_utils as vis_util

# Name of the directory containing the object detection module we're using
MODEL_PATH = 'model'

# Grab path to current working directory
CWD_PATH = os.getcwd()

# Path to frozen detection graph .pb file, which contains the model that is used
# for object detection.
PATH_TO_CKPT = os.path.join(CWD_PATH, MODEL_PATH, 'ssdlite_mobilenet_frozen_graph.pb')

# Path to label map file
PATH_TO_LABELS = os.path.join(CWD_PATH, MODEL_PATH, 'labelmap.pbtxt')

# Number of classes the object detector can identify
NUM_CLASSES = 4

## Load the label map.
# Label maps map indices to category names, so that when the convolution
# network predicts `5`, we know that this corresponds to `airplane`.
# Here we use internal utility functions, but anything that returns a
# dictionary mapping integers to appropriate string labels would be fine
label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)

# Load the Tensorflow model into memory.
detection_graph = tf.Graph()
with detection_graph.as_default():
    od_graph_def = tf.GraphDef()
    with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
        serialized_graph = fid.read()
        od_graph_def.ParseFromString(serialized_graph)
        tf.import_graph_def(od_graph_def, name='')

    sess = tf.Session(graph=detection_graph)


# Define input and output tensors (i.e. data) for the object detection classifier

# Input tensor is the image
image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')

# Output tensors are the detection boxes, scores, and classes
# Each box represents a part of the image where a particular object was detected
detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')

# Each score represents level of confidence for each of the objects.
# The score is shown on the result image, together with the class label.
detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')
detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')

# Number of objects detected
num_detections = detection_graph.get_tensor_by_name('num_detections:0')

#### Initialize other parameters ####

# Initialize frame rate calculation
frame_rate_calc = 1
freq = cv2.getTickFrequency()
font = cv2.FONT_HERSHEY_SIMPLEX

# Define inside box coordinates (top left and bottom right)
edge_limit = IM_WIDTH*0.9
TL_edge = (int(edge_limit),0)
BR_edge = (int(IM_WIDTH),int(IM_HEIGHT))

# Initialize control variables used for pet detector
at_edge = False

# minimum detection threshold
threshold = 0.5
# x point accross the screen where to the right the lego will cause the sorter to activate
sort_point = 0.5

#### Initialize camera and perform object detection ####

# The camera has to be set up and used differently depending on if it's a
# Picamera or USB webcam.

detected_legos = [['',0]] * 10
idx = 0
none_ticks = 0

### Picamera ###
if camera_type == 'picamera':
    # Initialize Picamera and grab reference to the raw capture
    camera = PiCamera()
    camera.resolution = (IM_WIDTH,IM_HEIGHT)
    camera.framerate = 10
    rawCapture = PiRGBArray(camera, size=(IM_WIDTH,IM_HEIGHT))

    # Continuously capture frames and perform object detection on them
    for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):

        t1 = cv2.getTickCount()

        # Acquire frame and expand frame dimensions to have shape: [1, None, None, 3]
        # i.e. a single-column array, where each item in the column has the pixel RGB value
        frame = np.copy(frame1.array)
        frame_expanded = np.expand_dims(frame, axis=0)

        (boxes, scores, classes, num) = sess.run(
                [detection_boxes, detection_scores, detection_classes, num_detections],
                feed_dict={image_tensor: frame_expanded})

        for (box, cls_id, conf) in zip(boxes[0], classes[0], scores[0]):
            # scores is sorted high to low, so if one is below, the rest will be too
            if conf < threshold:
                break

            detected_legos[idx][0] = str(cls_id+9)
            detected_legos[idx][1] = box[0] + box[2] / 2.
            idx += 1

        # sort lego based on lego closest to edge
        if idx > 0:
            detected_legos.sort(key=lambda tup:tup[1], reverse=True)
            if detected_legos[0] > sort_point:
                set_bin(detected_legos[0][0])
                pass
            idx = 0
            none_ticks = 0
        else:
            if none_ticks > 1:
                set_bin('00')
            none_ticks += 1

        if debug_mode:
            vis_util.visualize_boxes_and_labels_on_image_array(
                    frame,
                    np.squeeze(boxes),
                    np.squeeze(classes).astype(np.int32),
                    np.squeeze(scores),
                    category_index,
                    use_normalized_coordinates=True,
                    line_thickness=4,
                    min_score_thresh=threshold)

            # Draw FPS
            cv2.putText(frame,"FPS: {0:.2f}".format(frame_rate_calc),(30,50),font,1,(255,255,0),2,cv2.LINE_AA)

            cv2.imshow('Object detector', frame)
        # All the results have been drawn on the frame, so it's time to display it.

        # FPS calculation
        t2 = cv2.getTickCount()
        time1 = (t2-t1)/freq
        frame_rate_calc = 1/time1

        # Press 'q' to quit
        if cv2.waitKey(1) == ord('q'):
            break

        if not debug_mode:
            window.update_idletasks()
            window.update()

        rawCapture.truncate(0)

    camera.close()

### USB webcam ###

elif camera_type == 'usb':
    # Initialize USB webcam feed
    camera = cv2.VideoCapture(0)
    ret = camera.set(3,IM_WIDTH)
    ret = camera.set(4,IM_HEIGHT)
    time.sleep(2)


    # Continuously capture frames and perform object detection on them
    while(True):

        t1 = cv2.getTickCount()

        # Acquire frame and expand frame dimensions to have shape: [1, None, None, 3]
        # i.e. a single-column array, where each item in the column has the pixel RGB value
        ret, frame = camera.read()
        if not ret:
            continue

        frame_expanded = np.expand_dims(frame, axis=0)

        (boxes, scores, classes, num) = sess.run(
                [detection_boxes, detection_scores, detection_classes, num_detections],
                feed_dict={image_tensor: frame_expanded})

        vis_util.visualize_boxes_and_labels_on_image_array(
                frame,
                np.squeeze(boxes),
                np.squeeze(classes).astype(np.int32),
                np.squeeze(scores),
                category_index,
                use_normalized_coordinates=True,
                line_thickness=8,
                min_score_thresh=0.40)

        # Draw FPS
        cv2.putText(frame,"FPS: {0:.2f}".format(frame_rate_calc),(30,50),font,1,(255,255,0),2,cv2.LINE_AA)

        # All the results have been drawn on the frame, so it's time to display it.
        print('should show')
        cv2.imshow('Object detector', frame)

        # FPS calculation
        t2 = cv2.getTickCount()
        time1 = (t2-t1)/freq
        frame_rate_calc = 1/time1

        # Press 'q' to quit
        if cv2.waitKey(1) == ord('q'):
            break

    camera.release()

cv2.destroyAllWindows()
