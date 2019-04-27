﻿#!/usr/bin/python
# -*- coding: utf-8 -*-
import cv2
import sys
import json
import time
import numpy as np
import operator
import statistics
from statistics import mode, StatisticsError
import os
from keras.models import model_from_json

emotion_labels = [
    'angry',
    'fear',
    'happy',
    'sad',
    'surprise',
    'neutral',
    ]
cascPath = sys.argv[1]
l = []
faceCascade = cv2.CascadeClassifier(cascPath)

if os.path.exists("emotion.txt"):
  os.remove("emotion.txt")
if os.path.exists("emotionCheck.txt"):
  os.remove("emotionCheck.txt")

# load json and create model arch

json_file = open('model.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
model = model_from_json(loaded_model_json)

# load weights into new model

model.load_weights('model.h5')


def predict_emotion(face_image_gray):  # a single cropped face
    resized_img = cv2.resize(face_image_gray, (48, 48),
                             interpolation=cv2.INTER_AREA)

    # cv2.imwrite(str(index)+'.png', resized_img)

    image = resized_img.reshape(1, 1, 48, 48)
    list_of_list = model.predict(image, batch_size=1, verbose=1)
    (
        angry,
        fear,
        happy,
        sad,
        surprise,
        neutral,
        ) = [prob for lst in list_of_list for prob in lst]
    return [
        angry,
        fear,
        happy,
        sad,
        surprise,
        neutral,
        ]


video_capture = cv2.VideoCapture(0)
video_capture.set(cv2.CAP_PROP_FRAME_WIDTH, 360);
video_capture.set(cv2.CAP_PROP_FRAME_HEIGHT, 200);
while True:

    # Capture frame-by-frame

    (ret, frame) = video_capture.read()
    img_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY, 1)

    faces = faceCascade.detectMultiScale(img_gray, scaleFactor=1.1,
            minNeighbors=5, minSize=(30, 30),
            flags=cv2.CASCADE_SCALE_IMAGE)

    emotions = []

    # Draw a rectangle around the faces

   
    for (x, y, w, h) in faces:

        face_image_gray = img_gray[y:y + h, x:x + w]

        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0xFF, 0), 2)
        (
            angry,
            fear,
            happy,
            sad,
            surprise,
            neutral,
            ) = predict_emotion(face_image_gray)
        exp_list = [
            angry,
            fear,
            happy,
            sad,
            surprise,
            neutral,
            ]
        (index, value) = max(enumerate(exp_list),
                             key=operator.itemgetter(1))
        l.append(index)
        print(l)
        if len(l) == 20:
            try:
               exp = statistics.mode(l)
               with open('emotion.txt', 'a+') as f:
                  f.write('{}\n'.format(exp))
               with open('emotionCheck.txt', 'a+') as f:
                  f.write('{},{}\n'.format(exp,time.time()))
            except StatisticsError:
               exp=5;
               with open('emotion.txt', 'a+') as f:
                  f.write('{}\n'.format(exp))
               with open('emotionCheck.txt', 'a+') as f:
                 f.write('{},{}\n'.format(exp,time.time()))
            del l[0:19]
            

# f.write('{},{},{}\n'.format(index,value*100,time.time()))

    # Display the resulting frame

    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture

video_capture.release()
cv2.destroyAllWindows()
